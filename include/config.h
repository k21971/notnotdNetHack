/*	SCCS Id: @(#)config.h	3.4	2003/12/06	*/
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef CONFIG_H /* make sure the compiler does not see the typedefs twice */
#define CONFIG_H

#define DNETHACK /* Identifies this varient for patch-based utilities like Pinobot */

/*
 * Section 1:	Operating and window systems selection.
 *		Select the version of the OS you are using.
 */

#define UNIX		/* delete if no fork(), exec() available */

/* #define MINIMAL_TERM */
			/* if a terminal handles highlighting or tabs poorly,
			   try this define, used in pager.c and termcap.c */

#include "config1.h"	/* should auto-detect MSDOS, MAC, AMIGA, and WIN32 */


/* Windowing systems...
 * Define all of those you want supported in your binary.
 * Some combinations make no sense.  See the installation document.
 */
#define TTY_GRAPHICS	/* good old tty based graphics */
#define CURSES_GRAPHICS     /* Proper curses interface */

#define TTY_TILES_PATCH

#ifdef TTY_TILES_PATCH
#ifndef USE_TILES
#define USE_TILES
#endif
#endif

/*
 * Define the default window system.  This should be one that is compiled
 * into your system (see defines above).  Known window systems are:
 *
 *	tty, curses
 */

#ifndef DEFAULT_WINDOW_SYS
# define DEFAULT_WINDOW_SYS "tty"
#endif

/*
 * Section 2:	Some global parameters and filenames.
 *		Commenting out WIZARD, LOGFILE, NEWS or PANICLOG removes that
 *		feature from the game; otherwise set the appropriate wizard
 *		name.  LOGFILE, NEWS and PANICLOG refer to files in the
 *		playground.
 */

#ifndef WIZARD		/* allow for compile-time or Makefile changes */
# define WIZARD  "nethack" /* the person allowed to use the -D option */
#endif

#define LOGFILE "logfile"	/* larger file for debugging purposes */
#define NEWS "news"		/* the file containing the latest hack news */
#define PANICLOG "paniclog"	/* log of panic and impossible events */

/*
 *	If COMPRESS is defined, it should contain the full path name of your
 *	'compress' program.  Defining INTERNAL_COMP causes NetHack to do
 *	simpler byte-stream compression internally.  Both COMPRESS and
 *	INTERNAL_COMP create smaller bones/level/save files, but require
 *	additional code and time.  Currently, only UNIX fully implements
 *	COMPRESS; other ports should be able to uncompress save files a
 *	la unixmain.c if so inclined.
 *	If you define COMPRESS, you must also define COMPRESS_EXTENSION
 *	as the extension your compressor appends to filenames after
 *	compression.
 */

#if 0
#ifdef UNIX
/* path and file name extension for compression program */
/* #define COMPRESS "/usr/bin/compress" */	/* Lempel-Ziv compression */
/* #define COMPRESS_EXTENSION ".Z" */		/* compress's extension */
/* An example of one alternative you might want to use: */
#define COMPRESS "/bin/gzip"	/* FSF gzip compression */
#define COMPRESS_EXTENSION ".gz"		/* normal gzip extension */
#endif

#ifndef COMPRESS
# define INTERNAL_COMP	/* control use of NetHack's compression routines */
#endif
#endif

/*
 *	Defining INSURANCE slows down level changes, but allows games that
 *	died due to program or system crashes to be resumed from the point
 *	of the last level change, after running a utility program.
 */
#define INSURANCE	/* allow crashed game recovery */

/*
 * If you define HACKDIR, then this will be the default playground;
 * otherwise it will be the current directory.
 */
#ifndef HACKDIR
# define HACKDIR "."
#endif

/*
 * Some system administrators are stupid enough to make Hack suid root
 * or suid daemon, where daemon has other powers besides that of reading or
 * writing Hack files.	In such cases one should be careful with chdir's
 * since the user might create files in a directory of his choice.
 * Of course SECURE is meaningful only if HACKDIR is defined.
 */
#define SECURE		/* do setuid(getuid()) after chdir() */

/*
 * If it is desirable to limit the number of people that can play Hack
 * simultaneously, define HACKDIR, SECURE and MAX_NR_OF_PLAYERS.
 * #define MAX_NR_OF_PLAYERS 6
 */

/*
 * Limits the game to at most 100 inputs per second, and command
 * repeats to 200.  This should be enabled on hardfought to avoid the
 * high CPU usage kill script, but not when playing locally or CPU
 * usage is properly limited with cgroups.
 */
/* #define LIMIT_IPS */

/*
 * Section 3:	Definitions that may vary with system type.
 *		For example, both schar and uchar should be short ints on
 *		the AT&T 3B2/3B5/etc. family.
 */

#include "tradstdc.h"

/*
 * type schar: small signed integers (8 bits suffice) (eg. TOS)
 *
 *	typedef char	schar;
 *
 *	will do when you have signed characters; otherwise use
 *
 *	typedef short int schar;
 */
typedef signed char	schar;

/*
 * type uchar: small unsigned integers (8 bits suffice - but 7 bits do not)
 *
 *	typedef unsigned char	uchar;
 *
 *	will be satisfactory if you have an "unsigned char" type;
 *	otherwise use
 *
 *	typedef unsigned short int uchar;
 */
typedef unsigned char	uchar;

typedef uint32_t glyph_t;

/*
 * Various structures have the option of using bitfields to save space.
 * If your C compiler handles bitfields well (e.g., it can initialize structs
 * containing bitfields), you can define BITFIELDS.  Otherwise, the game will
 * allocate a separate character for each bitfield.  (The bitfields used never
 * have more than 7 bits, and most are only 1 bit.)
 */
#define BITFIELDS	/* Good bitfield handling */

/* #define STRNCMPI */	/* compiler/library has the strncmpi function */

/*
 * Section 4:  THE FUN STUFF!!!
 *
 * Conditional compilation of special options are controlled here.
 * If you define the following flags, you will add not only to the
 * complexity of the game but also to the size of the load module.
 */

/* dungeon features */
/* dungeon levels */
/* #define REINCARNATION */	/* Special Rogue-like levels */
/* monsters & objects */
#define SEDUCE		/* Succubi/incubi seduction, by KAA, suggested by IM */
/* difficulty */
/* I/O */

/*
 * Section 5:  EXPERIMENTAL STUFF
 *
 * Conditional compilation of new or experimental options are controlled here.
 * Enable any of these at your own risk -- there are almost certainly
 * bugs left here.
 */

/*
 * Enable support for playing user-specified sounds using libsndfile
 * and portaudio.  Make sure to add -lsndfile -lportaudio to GAMELIBS
 * if you enable this.
 */
/* #define USER_SOUNDS */

#ifdef TTY_GRAPHICS
# define WIN_EDGE	/* windows aligned left&top */
#endif

/*#define GOLDOBJ */	/* Gold is kept on obj chains - Helge Hafting */

#define DUMP_LOG        /* Dump game end information to a file */
#ifndef DUMP_FN
#define DUMP_FN "./dumplog/%t"      /* Fixed dumpfile name, if you want
                                   * to prevent definition by users */
#endif
#ifndef DUMPMSGS
#define DUMPMSGS 20     /* Number of latest messages in the dump file  */
#endif

/* In the following filename definitions, you can use the some string substitutions:
  %n = player's name
  %N = first character of player's name
  %t = character's starting time, in unix epoch format
*/

/* Filename for the wizard-mode command for dumping the map data.
   Can be left undefined, in which case the wiz-mode command does nothing. */
/* #define MAPDUMP_FN "/dgldir/userdata/%N/%n/dnao.mapdump" */

/* Filename for where HUPping a game is saved.
   Can be left undefined, in which case HUPping doesn't write the data. */
#ifndef HUPLIST_FN
#define HUPLIST_FN "./hangup"
#endif

/* Filename for dgamelaunch extra info field.
   Can be left undefined for not writing extrainfo. */
/* #define EXTRAINFO_FN "/dgldir/extrainfo-dnao/%n.extrainfo" */

#define SIMPLE_MAIL /* dgamelaunch simple mail */

/* If this file exists, players get a message from the user defined
   in the file.  The file format is "username:message to be shown" all
   in one line.  Can be left undefined to disable the feature.
   Requires UNIX
*/
#define SERVER_ADMIN_MSG "admin_msg"

#define LIVELOGFILE "livelog"

#define XLOGFILE "xlogfile"  /* even larger logfile */

/* Write out player's current location to this file.
   Can be left undefined, which will disable the feature. */
#define WHEREIS_FILE "whereis/%n.whereis"

#define USER_DUNGEONCOLOR

#define BONES_POOL /* Multiple bones files per level */

/* End of Section 5 */

#include "global.h"	/* Define everything else according to choices above */

#endif /* CONFIG_H */
