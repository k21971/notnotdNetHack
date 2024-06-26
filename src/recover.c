/*	SCCS Id: @(#)recover.c	3.4	1999/10/23	*/
/*	Copyright (c) Janet Walz, 1992.				  */
/* NetHack may be freely redistributed.  See license for details. */

/*
 *  Utility for reconstructing NetHack save file from a set of individual
 *  level files.  Requires that the `checkpoint' option be enabled at the
 *  time NetHack creates those level files.
 */
#include "config.h"
#if !defined(O_WRONLY)
#include <fcntl.h>
#endif


int recover_main(int, char **);
int restore_savefile(char *, const char *);
static void set_levelfile_name(int);
static int open_levelfile(int, const char *);
static int create_savefile(const char *);
void copy_bytes(int,int);

#define Fprintf	(void)fprintf

#define Close	(void)close

#ifdef UNIX
#define SAVESIZE	(PL_NSIZ + 13)	/* save/99999player.e */
#else
#define SAVESIZE	FILENAME	/* from macconf.h or pcconf.h */
#endif

#if defined(EXEPATH)
char *exepath(char *);
#endif

char savename[SAVESIZE]; /* holds relative path of save file from playground */

int
recover_main(int argc, char *argv[])
{
	int argno;
	const char *dir = (char *)0;


	if (!dir) dir = getenv("NETHACKDIR");
	if (!dir) dir = getenv("HACKDIR");
#if defined(EXEPATH)
	if (!dir) dir = exepath(argv[0]);
#endif
	if (argc == 1 || (argc == 2 && !strcmp(argv[1], "-"))) {
	    Fprintf(stderr,
		"Usage: %s [ -d directory ] base1 [ base2 ... ]\n", argv[0]);
	    exit(EXIT_FAILURE);
	}

	argno = 1;
	if (!strncmp(argv[argno], "-d", 2)) {
		dir = argv[argno]+2;
		if (*dir == '=' || *dir == ':') dir++;
		if (!*dir && argc > argno) {
			argno++;
			dir = argv[argno];
		}
		if (!*dir) {
		    Fprintf(stderr,
			"%s: flag -d must be followed by a directory name.\n",
			argv[0]);
		    exit(EXIT_FAILURE);
		}
		argno++;
	}
#if defined(SECURE)
	if (dir
# ifdef HACKDIR
		&& strcmp(dir, HACKDIR)
# endif
		) {
		(void) setgid(getgid());
		(void) setuid(getuid());
	}
#endif	/* SECURE */

#ifdef HACKDIR
	if (!dir) dir = HACKDIR;
#endif

	if (dir && chdir((char *) dir) < 0) {
		Fprintf(stderr, "%s: cannot chdir to %s.\n", argv[0], dir);
		exit(EXIT_FAILURE);
	}

	while (argc > argno) {
	    if (restore_savefile(argv[argno], dir) == 0)
		    Fprintf(stderr, "recovered \"%s\" to %s\n",
			    argv[argno], savename);
		argno++;
	}
	exit(EXIT_SUCCESS);
	/*NOTREACHED*/
	return 0;
}

static char lock[256];

static void
set_levelfile_name(int lev)
{
	char *tf;

	tf = rindex(lock, '.');
	if (!tf) tf = lock + strlen(lock);
	(void) sprintf(tf, ".%d", lev);
}

static int
open_levelfile(int lev, const char *directory)
{
	int fd;
	char levelfile[BUFSIZ];
	set_levelfile_name(lev);
	if (directory) {
	    snprintf(levelfile, BUFSIZ, "%s/%s", directory, lock);
	} else {
	    strcpy(levelfile, lock);
	}
	fd = open(levelfile, O_RDONLY, 0);
	return fd;
}

static int
create_savefile(const char *directory)
{
	int fd;
	char savefile[BUFSIZ];
	if (directory) {
		sprintf(savefile, "%s/%s", directory, savename);
	} else {
		strcpy(savefile, savename);
	}
	fd = creat(savefile, FCMASK);
	return fd;
}

void
copy_bytes(int ifd, int ofd)
{
	char buf[BUFSIZ];
	int nfrom, nto;

	do {
		nfrom = read(ifd, buf, BUFSIZ);
		nto = write(ofd, buf, nfrom);
		if (nto != nfrom) {
			Fprintf(stderr, "file copy failed!\n");
			exit(EXIT_FAILURE);
		}
	} while (nfrom == BUFSIZ);
}

int
restore_savefile(char *basename, const char *directory)
{
	int gfd, lfd, sfd;
	int lev, savelev, hpid;
	int levc;
	struct version_info version_data;

	/* level 0 file contains:
	 *	pid of creating process (ignored here)
	 *	level number for current level of save file
	 *	name of save file nethack would have created
	 *	and game state
	 */

	(void) strcpy(lock, basename);
	gfd = open_levelfile(0, directory);
	if (gfd < 0) {
	    Fprintf(stderr, "Cannot open level 0 for %s.\n", basename);
	    return(-1);
	}
	if (read(gfd, (void *) &hpid, sizeof hpid) != sizeof hpid) {
	    Fprintf(stderr, "%s\n%s%s%s\n",
	     "Checkpoint data incompletely written or subsequently clobbered;",
		    "recovery for \"", basename, "\" impossible.");
	    Close(gfd);
	    return(-1);
	}
	if (read(gfd, (void *) &savelev, sizeof(savelev))
							!= sizeof(savelev)) {
	    Fprintf(stderr,
	    "Checkpointing was not in effect for %s -- recovery impossible.\n",
		    basename);
	    Close(gfd);
	    return(-1);
	}
	if ((read(gfd, (void *) savename, sizeof savename)
		!= sizeof savename) ||
	    (read(gfd, (void *) &version_data, sizeof version_data)
		!= sizeof version_data)) {
	    Fprintf(stderr, "Error reading %s -- can't recover.\n", lock);
	    Close(gfd);
	    return(-1);
	}

	/* save file should contain:
	 *	version info
	 *	current level (including pets)
	 *	(non-level-based) game state
	 *	other levels
	 */
	sfd = create_savefile(directory);
	if (sfd < 0) {
	    Fprintf(stderr, "Cannot create savefile %s.\n", savename);
	    Close(gfd);
	    return(-1);
	}

	lfd = open_levelfile(savelev, directory);
	if (lfd < 0) {
	    Fprintf(stderr, "Cannot open level of save for %s.\n", basename);
	    Close(gfd);
	    Close(sfd);
	    return(-1);
	}

	if (write(sfd, (void *) &version_data, sizeof version_data)
		!= sizeof version_data) {
	    Fprintf(stderr, "Error writing %s; recovery failed.\n", savename);
	    Close(gfd);
	    Close(sfd);
	    return(-1);
	}

	copy_bytes(lfd, sfd);
	Close(lfd);
	(void) unlink(lock);

	copy_bytes(gfd, sfd);
	Close(gfd);
	set_levelfile_name(0);
	(void) unlink(lock);

	for (lev = 1; lev < 2000; lev++) {
		/* level numbers are kept in xchars in save.c, so the
		 * maximum level number (for the endlevel) must be < 256
		 */
		if (lev != savelev) {
		    lfd = open_levelfile(lev, directory);
			if (lfd >= 0) {
				/* any or all of these may not exist */
				levc = (int) lev;
				write(sfd, (void *) &levc, sizeof(levc));
				copy_bytes(lfd, sfd);
				Close(lfd);
				(void) unlink(lock);
			}
		}
	}

	Close(sfd);

#if 0 /* OBSOLETE, HackWB is no longer in use */
#endif
	return(0);
}

#ifdef EXEPATH
#define PATH_SEPARATOR '\\'

#define EXEPATHBUFSZ 256
char exepathbuf[EXEPATHBUFSZ];

char *
exepath(char *str)
{
	char *tmp, *tmp2;
	int bsize;

	if (!str) return (char *)0;
	bsize = EXEPATHBUFSZ;
	tmp = exepathbuf;
	strcpy (tmp, str);
	tmp2 = strrchr(tmp, PATH_SEPARATOR);
	if (tmp2) *tmp2 = '\0';
	return tmp;
}
#endif /* EXEPATH */



/*recover.c*/
