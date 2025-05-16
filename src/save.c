/*	SCCS Id: @(#)save.c	3.4	2003/11/14	*/
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"
#include "lev.h"
#include "quest.h"

#ifndef NO_SIGNAL
#include <signal.h>
#endif
#if !defined(O_WRONLY)
#include <fcntl.h>
#endif

extern boolean saving_game;



#ifdef ZEROCOMP
static void bputc(int);
#endif
static void savelevchn(int,int);
static void savedamage(int,int);
static void saveobjchn(int,struct obj *,int);
static void savemonchn(int,struct monst *,int);
static void savetrapchn(int,struct trap *,int);
static void savegamestate(int,int);

#if defined(UNIX)
#define HUP	if (!program_state.done_hup)
#else
#define HUP
#endif

extern struct menucoloring *menu_colorings;

extern const struct percent_color_option *hp_colors;
extern const struct percent_color_option *pw_colors;
extern const struct text_color_option *text_colors;

/* need to preserve these during save to avoid accessing freed memory */
static unsigned ustuck_id = 0, usteed_id = 0;

int
dosave(void)
{
	if (iflags.debug_fuzzer)
		return MOVE_CANCELLED;
	clear_nhwindow(WIN_MESSAGE);
	if(yn("Really save?") == 'n') {
		clear_nhwindow(WIN_MESSAGE);
		if(multi > 0) nomul(0, NULL);
	} else {
		clear_nhwindow(WIN_MESSAGE);
		pline("Saving...");
#if defined(UNIX)
		program_state.done_hup = 0;
#endif
		if(dosave0()) {
			program_state.something_worth_saving = 0;
			u.uhp = -1;		/* universal game's over indicator */
			/* make sure they see the Saving message */
			display_nhwindow(WIN_MESSAGE, TRUE);
			exit_nhwindows("Be seeing you...");
			terminate(EXIT_SUCCESS);
		} else (void)doredraw();
	}
	return MOVE_CANCELLED;
}


#if defined(UNIX)
/*ARGSUSED*/
void
hangup(  /* called as signal() handler, so sent at least one arg */
	int sig_unused)
{
# ifdef NOSAVEONHANGUP
	(void) signal(SIGINT, SIG_IGN);
	clearlocks();
	terminate(EXIT_FAILURE);
# else	/* SAVEONHANGUP */
	if (!program_state.done_hup++) {
	    if (program_state.something_worth_saving) {
		write_HUP_file();
		(void) dosave0();
	    }
	    {
		clearlocks();
		terminate(EXIT_FAILURE);
	    }
	}
# endif
	return;
}
#endif

/* returns 1 if save successful */
int
dosave0(void)
{
	const char *fq_save;
	register int fd, ofd;
	int ltmp;
	d_level uz_save;
	char whynot[BUFSZ];

	if (!SAVEF[0])
		return 0;
	
	saving_game = TRUE; /*Some deeply buryied code calls curses redraw stuff that will crash.*/
	
	fq_save = fqname(SAVEF, SAVEPREFIX, 1);	/* level files take 0 */

#if defined(UNIX)
	(void) signal(SIGHUP, SIG_IGN);
#endif
#ifndef NO_SIGNAL
	(void) signal(SIGINT, SIG_IGN);
#endif


	HUP if (iflags.window_inited) {
	    uncompress(fq_save);
	    fd = open_savefile();
	    if (fd > 0) {
		(void) close(fd);
		clear_nhwindow(WIN_MESSAGE);
		There("seems to be an old save file.");
		if (yn("Overwrite the old file?") == 'n') {
		    compress(fq_save);
			saving_game = FALSE;
		    return 0;
		}
	    }
	}

	HUP mark_synch();	/* flush any buffered screen output */

	fd = create_savefile();
	if(fd < 0) {
		HUP pline("Cannot open save file.");
		(void) delete_savefile();	/* ab@unido */
		saving_game = FALSE;
		return(0);
	}

#ifdef WHEREIS_FILE
	touch_whereis();
#endif

	vision_recalc(2);	/* shut down vision to prevent problems
				   in the event of an impossible() call */
	
	/* undo date-dependent luck adjustments made at startup time */
	if(flags.moonphase == FULL_MOON)	/* ut-sally!fletcher */
		change_luck(-1);		/* and unido!ab */
	if(flags.moonphase == HUNTING_MOON)
		change_luck(-2);
	if(flags.friday13)
		change_luck(1);
	if(iflags.window_inited)
	    HUP clear_nhwindow(WIN_MESSAGE);


	store_version(fd);
#ifdef STORE_PLNAME_IN_FILE
	bwrite(fd, (void *) plname, PL_NSIZ);
#endif
	ustuck_id = (u.ustuck ? u.ustuck->m_id : 0);
	usteed_id = (u.usteed ? u.usteed->m_id : 0);
	savelev(fd, ledger_no(&u.uz), WRITE_SAVE | FREE_SAVE);
	savegamestate(fd, WRITE_SAVE | FREE_SAVE);

	/* While copying level files around, zero out u.uz to keep
	 * parts of the restore code from completely initializing all
	 * in-core data structures, since all we're doing is copying.
	 * This also avoids at least one nasty core dump.
	 */
	uz_save = u.uz;
	u.uz.dnum = u.uz.dlevel = 0;
	/* these pointers are no longer valid, and at least u.usteed
	 * may mislead place_monster() on other levels
	 */
	u.ustuck = (struct monst *)0;
	u.usteed = (struct monst *)0;

	for(ltmp = (int)1; ltmp <= maxledgerno(); ltmp++) {
		if (ltmp == ledger_no(&uz_save)) continue;
		if (!(level_info[ltmp].flags & LFILE_EXISTS)) continue;
		ofd = open_levelfile(ltmp, whynot);
		if (ofd < 0) {
		    HUP pline("%s", whynot);
			abort();
		    (void) close(fd);
		    (void) delete_savefile();
		    HUP killer = whynot;
		    HUP done(TRICKED);
			saving_game = FALSE;
		    return(0);
		}
		minit();	/* ZEROCOMP */
		getlev(ofd, hackpid, ltmp, FALSE);
		(void) close(ofd);
		bwrite(fd, (void *) &ltmp, sizeof ltmp); /* level number*/
		savelev(fd, ltmp, WRITE_SAVE | FREE_SAVE);     /* actual level*/
		delete_levelfile(ltmp);
	}
	bclose(fd);

	u.uz = uz_save;

	/* get rid of current level --jgm */
	delete_levelfile(ledger_no(&u.uz));
	delete_levelfile(0);
#ifdef WHEREIS_FILE
        delete_whereis();
#endif
	compress(fq_save);
	saving_game = FALSE;
	return(1);
}

static void
savegamestate(register int fd, register int mode)
{
	int uid,i;
	struct obj * bc_objs = (struct obj *)0;
	time_t realtime;


	uid = getuid();
	bwrite(fd, (void *) &uid, sizeof uid);
	flags.end_around = has_loaded_bones;
	bwrite(fd, (void *) &flags, sizeof(struct flag));
	bwrite(fd, (void *) &u, sizeof(struct you));
	bwrite(fd, (void *) &youmonst, sizeof(struct monst));
	if (youmonst.light)
		save_lightsource(youmonst.light, fd, mode);
	
	/* save random monsters*/
	bwrite(fd, (void *) &mons[PM_SHAMBLING_HORROR], sizeof(struct permonst));
	bwrite(fd, (void *) &mons[PM_STUMBLING_HORROR], sizeof(struct permonst));
	bwrite(fd, (void *) &mons[PM_WANDERING_HORROR], sizeof(struct permonst));

	if (CHAIN_IN_MON) {
		uchain->nobj = bc_objs;
		bc_objs = uchain;
	}
	if (BALL_IN_MON) {
		uball->nobj = bc_objs;
		bc_objs = uball;
	}
	save_gods(fd);
	save_artifacts(fd);
	saveobjchn(fd, invent, mode);
	saveobjchn(fd, bc_objs, mode);
	for(i=0;i<10;i++){
		saveobjchn(fd, magic_chest_objs[i], mode);
		if(release_data(mode)){ /*then saveobjchn freed all these objects*/
			magic_chest_objs[i] = (struct obj *) 0;
		}
	}
	saveobjchn(fd, migrating_objs, mode);
	savemonchn(fd, migrating_mons, mode);
	if (release_data(mode)) {
	    invent = 0;
	    migrating_objs = 0;
	    migrating_mons = 0;
	}
	bwrite(fd, (void *) mvitals, sizeof(mvitals));

	save_dungeon(fd, (boolean)!!perform_bwrite(mode),
			 (boolean)!!release_data(mode));
	savelevchn(fd, mode);
	bwrite(fd, (void *) &moves, sizeof moves);
	bwrite(fd, (void *) &monstermoves, sizeof monstermoves);
	bwrite(fd, (void *) &quest_status, sizeof(struct q_score));
	bwrite(fd, (void *) spl_book,
				sizeof(struct spell) * (MAXSPELL + 1));
	save_oracles(fd, mode);
	if(ustuck_id)
	    bwrite(fd, (void *) &ustuck_id, sizeof ustuck_id);
	if(usteed_id)
	    bwrite(fd, (void *) &usteed_id, sizeof usteed_id);
	bwrite(fd, (void *) pl_character, sizeof pl_character);
	bwrite(fd, (void *) pl_fruit, sizeof pl_fruit);
	bwrite(fd, (void *) &current_fruit, sizeof current_fruit);
	savefruitchn(fd, mode);
	savenames(fd, mode);
	save_waterlevel(fd, mode);
	bwrite(fd, (void *) &achieve, sizeof achieve);
	realtime = get_realtime();
	bwrite(fd, (void *) &realtime, sizeof realtime);
	bflush(fd);
}

#ifdef INSURANCE
void
savestateinlock(void)
{
	int fd, hpid;
	static boolean havestate = TRUE;
	char whynot[BUFSZ];

	/* When checkpointing is on, the full state needs to be written
	 * on each checkpoint.  When checkpointing is off, only the pid
	 * needs to be in the level.0 file, so it does not need to be
	 * constantly rewritten.  When checkpointing is turned off during
	 * a game, however, the file has to be rewritten once to truncate
	 * it and avoid restoring from outdated information.
	 *
	 * Restricting havestate to this routine means that an additional
	 * noop pid rewriting will take place on the first "checkpoint" after
	 * the game is started or restored, if checkpointing is off.
	 */
	if (flags.ins_chkpt || havestate) {
		/* save the rest of the current game state in the lock file,
		 * following the original int pid, the current level number,
		 * and the current savefile name, which should not be subject
		 * to any internal compression schemes since they must be
		 * readable by an external utility
		 */
		fd = open_levelfile(0, whynot);
		if (fd < 0) {
		    pline("%s", whynot);
		    pline("Probably someone removed it.");
		    killer = whynot;
		    done(TRICKED);
		    return;
		}

		(void) read(fd, (void *) &hpid, sizeof(hpid));
		if (hackpid != hpid) {
		    Sprintf(whynot,
			    "Level #0 pid (%d) doesn't match ours (%d)!",
			    hpid, hackpid);
		    pline("%s", whynot);
		    killer = whynot;
		    done(TRICKED);
		}
		(void) close(fd);

		fd = create_levelfile(0, whynot);
		if (fd < 0) {
		    pline("%s", whynot);
		    killer = whynot;
		    done(TRICKED);
		    return;
		}
		(void) write(fd, (void *) &hackpid, sizeof(hackpid));
		if (flags.ins_chkpt) {
		    int currlev = ledger_no(&u.uz);

		    (void) write(fd, (void *) &currlev, sizeof(currlev));
		    save_savefile_name(fd);
		    store_version(fd);
#ifdef STORE_PLNAME_IN_FILE
		    bwrite(fd, (void *) plname, PL_NSIZ);
#endif
		    ustuck_id = (u.ustuck ? u.ustuck->m_id : 0);
		    usteed_id = (u.usteed ? u.usteed->m_id : 0);
		    savegamestate(fd, WRITE_SAVE);
		}
		bclose(fd);
	}
	havestate = flags.ins_chkpt;
}
#endif

void
savelev(int fd, int lev, int mode)
{

	/* if we're tearing down the current level without saving anything
	   (which happens upon entrance to the endgame or after an aborted
	   restore attempt) then we don't want to do any actual I/O */
	if (mode == FREE_SAVE) goto skip_lots;
	if (iflags.purge_monsters) {
		/* purge any dead monsters (necessary if we're starting
		 * a panic save rather than a normal one, or sometimes
		 * when changing levels without taking time -- e.g.
		 * create statue trap then immediately level teleport) */
		dmonsfree();
	}

	if(fd < 0) panic("Save on bad file!");	/* impossible */
	if (lev >= 0 && lev <= maxledgerno())
	    level_info[lev].flags |= VISITED;
	bwrite(fd,(void *) &hackpid,sizeof(hackpid));
	bwrite(fd,(void *) &lev,sizeof(lev));
#ifdef RLECOMP
	{
	    /* perform run-length encoding of rm structs */
	    struct rm *prm, *rgrm;
	    int x, y;
	    uchar match;

	    rgrm = &levl[0][0];		/* start matching at first rm */
	    match = 0;

	    for (y = 0; y < ROWNO; y++) {
		for (x = 0; x < COLNO; x++) {
		    prm = &levl[x][y];
		    if (prm->glyph == rgrm->glyph
			&& prm->typ == rgrm->typ
			&& prm->seenv == rgrm->seenv
			&& prm->horizontal == rgrm->horizontal
			&& prm->flags == rgrm->flags
			&& prm->lit == rgrm->lit
			&& prm->waslit == rgrm->waslit
			&& prm->roomno == rgrm->roomno
			&& prm->edge == rgrm->edge) {
			match++;
			if (match > 254) {
			    match = 254;	/* undo this match */
			    goto writeout;
			}
		    } else {
			/* the run has been broken,
			 * write out run-length encoding */
		    writeout:
			bwrite(fd, (void *)&match, sizeof(uchar));
			bwrite(fd, (void *)rgrm, sizeof(struct rm));
			/* start encoding again. we have at least 1 rm
			 * in the next run, viz. this one. */
			match = 1;
			rgrm = prm;
		    }
		}
	    }
	    if (match > 0) {
		bwrite(fd, (void *)&match, sizeof(uchar));
		bwrite(fd, (void *)rgrm, sizeof(struct rm));
	    }
	}
#else
	bwrite(fd,(void *) levl,sizeof(levl));
#endif /* RLECOMP */

	bwrite(fd,(void *) &monstermoves,sizeof(monstermoves));
	bwrite(fd,(void *) &upstair,sizeof(stairway));
	bwrite(fd,(void *) &dnstair,sizeof(stairway));
	bwrite(fd,(void *) &upladder,sizeof(stairway));
	bwrite(fd,(void *) &dnladder,sizeof(stairway));
	bwrite(fd,(void *) &sstairs,sizeof(stairway));
	bwrite(fd,(void *) &updest,sizeof(dest_area));
	bwrite(fd,(void *) &dndest,sizeof(dest_area));
	bwrite(fd,(void *) &level.flags,sizeof(level.flags));
	bwrite(fd,(void *) &level.lastmove,sizeof(level.lastmove));
	bwrite(fd, (void *) doors, sizeof(doors));
	bwrite(fd,(void *) &altarindex, sizeof(int));
	bwrite(fd, (void *) altars, sizeof(altars));
	save_rooms(fd);	/* no dynamic memory to reclaim */

	/* from here on out, saving also involves allocated memory cleanup */
 skip_lots:
	savemonchn(fd, fmon, mode);
	save_worm(fd, mode);	/* save worm information */
	savetrapchn(fd, ftrap, mode);
	saveobjchn(fd, fobj, mode);
	saveobjchn(fd, level.buriedobjlist, mode);
	saveobjchn(fd, billobjs, mode);
	if (release_data(mode)) {
	    fmon = 0;
	    ftrap = 0;
	    fobj = 0;
	    level.buriedobjlist = 0;
	    billobjs = 0;
	}
	save_engravings(fd, mode);
	savedamage(fd, mode);
	save_regions(fd, mode);
	if (mode != FREE_SAVE) bflush(fd);
}

#ifdef ZEROCOMP
/* The runs of zero-run compression are flushed after the game state or a
 * level is written out.  This adds a couple bytes to a save file, where
 * the runs could be mashed together, but it allows gluing together game
 * state and level files to form a save file, and it means the flushing
 * does not need to be specifically called for every other time a level
 * file is written out.
 */

#define RLESC '\0'    /* Leading character for run of LRESC's */
#define flushoutrun(ln) (bputc(RLESC), bputc(ln), ln = -1)

#ifndef ZEROCOMP_BUFSIZ
# define ZEROCOMP_BUFSIZ BUFSZ
#endif
static unsigned char outbuf[ZEROCOMP_BUFSIZ];
static unsigned short outbufp = 0;
static short outrunlength = -1;
static int bwritefd;
static boolean compressing = FALSE;

/*dbg()
{
    HUP printf("outbufp %d outrunlength %d\n", outbufp,outrunlength);
}*/

static void
bputc(int c)
{
    if (outbufp >= sizeof outbuf) {
	(void) write(bwritefd, outbuf, sizeof outbuf);
	outbufp = 0;
    }
    outbuf[outbufp++] = (unsigned char)c;
}

/*ARGSUSED*/
void
bufon(int fd)
{
    compressing = TRUE;
    return;
}

/*ARGSUSED*/
void
bufoff(int fd)
{
    if (outbufp) {
	outbufp = 0;
	panic("closing file with buffered data still unwritten");
    }
    outrunlength = -1;
    compressing = FALSE;
    return;
}

void
bflush(  /* flush run and buffer */
	register int fd)
{
    bwritefd = fd;
    if (outrunlength >= 0) {	/* flush run */
	flushoutrun(outrunlength);
    }

    if (outbufp) {
	if (write(fd, outbuf, outbufp) != outbufp) {
#if defined(UNIX)
	    if (program_state.done_hup)
		terminate(EXIT_FAILURE);
	    else
#endif
		bclose(fd);	/* panic (outbufp != 0) */
	}
	outbufp = 0;
    }
}

void
bwrite(int fd, void * loc, register unsigned num)
{
    register unsigned char *bp = (unsigned char *)loc;

    if (!compressing) {
	if ((unsigned) write(fd, loc, num) != num) {
#if defined(UNIX)
	    if (program_state.done_hup)
		terminate(EXIT_FAILURE);
	    else
#endif
		panic("cannot write %u bytes to file #%d", num, fd);
	}
    } else {
	bwritefd = fd;
	for (; num; num--, bp++) {
	    if (*bp == RLESC) {	/* One more char in run */
		if (++outrunlength == 0xFF) {
		    flushoutrun(outrunlength);
		}
	    } else {		/* end of run */
		if (outrunlength >= 0) {	/* flush run */
		    flushoutrun(outrunlength);
		}
		bputc(*bp);
	    }
	}
    }
}

void
bclose(int fd)
{
    bufoff(fd);
    (void) close(fd);
    return;
}

#else /* ZEROCOMP */

static int bw_fd = -1;
static FILE *bw_FILE = 0;
static boolean buffering = FALSE;

void
bufon(int fd)
{
#ifdef UNIX
    if(bw_fd >= 0)
	panic("double buffering unexpected");
    bw_fd = fd;
    if((bw_FILE = fdopen(fd, "w")) == 0)
	panic("buffering of file %d failed", fd);
#endif
    buffering = TRUE;
}

void
bufoff(int fd)
{
    bflush(fd);
    buffering = FALSE;
}

void
bflush(int fd)
{
#ifdef UNIX
    if(fd == bw_fd) {
	if(fflush(bw_FILE) == EOF)
	    panic("flush of savefile failed!");
    }
#endif
    return;
}

void
bwrite(register int fd, register void * loc, register unsigned num)
{
	boolean failed;


#ifdef UNIX
	if (buffering) {
	    if(fd != bw_fd)
		panic("unbuffered write to fd %d (!= %d)", fd, bw_fd);

	    failed = (fwrite(loc, (int)num, 1, bw_FILE) != 1);
	} else
#endif /* UNIX */
	{
/* lint wants the 3rd arg of write to be an int; lint -p an unsigned */
	    failed = (write(fd, loc, num) != num);
	}

	if (failed) {
#if defined(UNIX)
	    if (program_state.done_hup)
		terminate(EXIT_FAILURE);
	    else
#endif
		panic("cannot write %u bytes to file #%d", num, fd);
	}
}

void
bclose(int fd)
{
    bufoff(fd);
#ifdef UNIX
    if (fd == bw_fd) {
	(void) fclose(bw_FILE);
	bw_fd = -1;
	bw_FILE = 0;
    } else
#endif
	(void) close(fd);
    return;
}
#endif /* ZEROCOMP */

static void
savelevchn(register int fd, register int mode)
{
	s_level	*tmplev, *tmplev2;
	int cnt = 0;

	for (tmplev = sp_levchn; tmplev; tmplev = tmplev->next) cnt++;
	if (perform_bwrite(mode))
	    bwrite(fd, (void *) &cnt, sizeof(int));

	for (tmplev = sp_levchn; tmplev; tmplev = tmplev2) {
	    tmplev2 = tmplev->next;
	    if (perform_bwrite(mode))
		bwrite(fd, (void *) tmplev, sizeof(s_level));
	    if (release_data(mode))
		free((void *) tmplev);
	}
	if (release_data(mode))
	    sp_levchn = 0;
}

static void
savedamage(register int fd, register int mode)
{
	register struct damage *damageptr, *tmp_dam;
	unsigned int xl = 0;

	damageptr = level.damagelist;
	for (tmp_dam = damageptr; tmp_dam; tmp_dam = tmp_dam->next)
	    xl++;
	if (perform_bwrite(mode))
	    bwrite(fd, (void *) &xl, sizeof(xl));

	while (xl--) {
	    if (perform_bwrite(mode))
		bwrite(fd, (void *) damageptr, sizeof(*damageptr));
	    tmp_dam = damageptr;
	    damageptr = damageptr->next;
	    if (release_data(mode))
		free((void *)tmp_dam);
	}
	if (release_data(mode))
	    level.damagelist = 0;
}

static void
saveobjchn(register int fd, register struct obj *otmp, register int mode)
{
	register struct obj *otmp2;
	unsigned int xl;
	int zero = 0;
	int minusone = -1;

	while(otmp) {
	    otmp2 = otmp->nobj;
	    if (perform_bwrite(mode)) {
			bwrite(fd, (void *) &zero, sizeof(int));
			bwrite(fd, (void *) otmp, sizeof(struct obj));
			if(otmp->mp){
				bwrite(fd, (void *) otmp->mp, (unsigned) sizeof(struct mask_properties));
//				bwrite(fd, (void *) otmp->mp->mskacurr, sizeof(struct attribs));
//				bwrite(fd, (void *) otmp->mp->mskaexe, sizeof(struct attribs));
//				bwrite(fd, (void *) otmp->mp->mskamask, sizeof(struct attribs));
			}
	    }
		if (otmp->oextra_p)
			save_oextra(otmp, fd, mode);
		if (otmp->light)
			save_lightsource(otmp->light, fd, mode);
		if (otmp->timed)
			save_timers(otmp->timed, fd, mode);
	    if (Has_contents(otmp))
		saveobjchn(fd,otmp->cobj,mode);
	    if (release_data(mode)) {
		if (otmp->oclass == FOOD_CLASS) food_disappears(otmp);
		if (otmp->oclass == SPBOOK_CLASS) book_disappears(otmp);
		otmp->where = OBJ_FREE;	/* set to free so dealloc will work */
		otmp->lamplit = 0;	/* caller handled lights */
		dealloc_obj(otmp);
	    }
	    otmp = otmp2;
	}
	if (perform_bwrite(mode))
	    bwrite(fd, (void *) &minusone, sizeof(int));
}

static void
savemonchn(register int fd, register struct monst *mtmp, register int mode)
{
	register struct monst *mtmp2;
	int zero = 0;
	int minusone = -1;
	struct permonst *monbegin = &mons[0];

	if (perform_bwrite(mode))
	    bwrite(fd, (void *) &monbegin, sizeof(monbegin));

	while (mtmp) {
	    mtmp2 = mtmp->nmon;
	    if (perform_bwrite(mode)) {
		bwrite(fd, (void *) &zero, sizeof(int));
		bwrite(fd, (void *) mtmp, sizeof(struct monst));
	    }
		if(mtmp->mextra_p)
			save_mextra(mtmp, fd, mode);
		if (mtmp->light)
			save_lightsource(mtmp->light, fd, mode);
		if (mtmp->timed)
			save_timers(mtmp->timed, fd, mode);
	    if (mtmp->minvent)
		saveobjchn(fd,mtmp->minvent,mode);
	    if (release_data(mode))
		dealloc_monst(mtmp);
	    mtmp = mtmp2;
	}
	if (perform_bwrite(mode))
	    bwrite(fd, (void *) &minusone, sizeof(int));
}

static void
savetrapchn(register int fd, register struct trap *trap, register int mode)
{
	register struct trap *trap2;
	static struct trap zerotrap;

	while (trap) {
	    trap2 = trap->ntrap;
	    if (perform_bwrite(mode))
		bwrite(fd, (void *) trap, sizeof(struct trap));
		if (trap->ammo)
			saveobjchn(fd, trap->ammo, mode);
	    if (release_data(mode))
		dealloc_trap(trap);
	    trap = trap2;
	}
	if (perform_bwrite(mode))
	    bwrite(fd, (void *) &zerotrap, sizeof(struct trap));
}

/* save all the fruit names and ID's; this is used only in saving whole games
 * (not levels) and in saving bones levels.  When saving a bones level,
 * we only want to save the fruits which exist on the bones level; the bones
 * level routine marks nonexistent fruits by making the fid negative.
 */
void
savefruitchn(register int fd, register int mode)
{
	register struct fruit *f2, *f1;
	static struct fruit zerofruit;

	f1 = ffruit;
	while (f1) {
	    f2 = f1->nextf;
	    if (f1->fid >= 0 && perform_bwrite(mode))
		bwrite(fd, (void *) f1, sizeof(struct fruit));
	    if (release_data(mode))
		dealloc_fruit(f1);
	    f1 = f2;
	}
	if (perform_bwrite(mode))
	    bwrite(fd, (void *) &zerofruit, sizeof(struct fruit));
	if (release_data(mode))
	    ffruit = 0;
}


void
free_percent_color_options(const struct percent_color_option *list_head)
{
    if (list_head == NULL) return;
    free_percent_color_options(list_head->next);
    free((void *)list_head);
}

void
free_text_color_options(const struct text_color_option *list_head)
{
    if (list_head == NULL) return;
    free_text_color_options(list_head->next);
    free((void *)list_head->text);
    free((void *)list_head);
}

void
free_status_colors(void)
{
    free_percent_color_options(hp_colors); hp_colors = NULL;
    free_percent_color_options(pw_colors); pw_colors = NULL;
    free_text_color_options(text_colors); text_colors = NULL;
}


/* also called by prscore(); this probably belongs in dungeon.c... */
void
free_dungeons(void)
{
#ifdef FREE_ALL_MEMORY
	savelevchn(0, FREE_SAVE);
	save_dungeon(0, FALSE, TRUE);
#endif
	return;
}

void
free_menu_coloring(void)
{
    struct menucoloring *tmp = menu_colorings;

    while (tmp) {
	struct menucoloring *tmp2 = tmp->next;
	if (tmp->is_regexp)
	    (void) regfree(&tmp->match);
	else
	    free(tmp->pattern);
	free(tmp);
	tmp = tmp2;
    }
}

void
freedynamicdata(void)
{
    free_status_colors();
	unload_qtlist();
	free_invbuf();	/* let_to_name (invent.c) */
	free_youbuf();	/* You_buf,&c (pline.c) */
	msgpline_free();
	querytype_free();
	free_menu_coloring();
	tmp_at(DISP_FREEMEM, 0);	/* temporary display effects */
#ifdef FREE_ALL_MEMORY
# define freeobjchn(X)	(saveobjchn(0, X, FREE_SAVE),  X = 0)
# define freemonchn(X)	(savemonchn(0, X, FREE_SAVE),  X = 0)
# define freetrapchn(X)	(savetrapchn(0, X, FREE_SAVE), X = 0)
# define freefruitchn()	 savefruitchn(0, FREE_SAVE)
# define freenames()	 savenames(0, FREE_SAVE)
# define free_oracles()	save_oracles(0, FREE_SAVE)
# define free_waterlevel() save_waterlevel(0, FREE_SAVE)
# define free_worm()	 save_worm(0, FREE_SAVE)
# define free_engravings() save_engravings(0, FREE_SAVE)
# define freedamage()	 savedamage(0, FREE_SAVE)
# define free_animals()	 mon_animal_list(FALSE)

	/* move-specific data */
	dmonsfree();		/* release dead monsters */

	/* level-specific data */
	freemonchn(fmon);
	free_worm();		/* release worm segment information */
	freetrapchn(ftrap);
	freeobjchn(fobj);
	freeobjchn(level.buriedobjlist);
	freeobjchn(billobjs);
	free_engravings();
	freedamage();

	/* game-state data */
	freeobjchn(invent);
	for(i=0;i<10;i++) freeobjchn(magic_chest_objs[i]);
	freeobjchn(migrating_objs);
	freemonchn(migrating_mons);
	freemonchn(mydogs);		/* ascension or dungeon escape */
     /* freelevchn();	[folded into free_dungeons()] */
	free_animals();
	free_oracles();
	freefruitchn();
	freenames();
	free_waterlevel();
	free_dungeons();

	/* some pointers in iflags */
	if (iflags.wc_font_map) free(iflags.wc_font_map);
	if (iflags.wc_font_message) free(iflags.wc_font_message);
	if (iflags.wc_font_text) free(iflags.wc_font_text);
	if (iflags.wc_font_menu) free(iflags.wc_font_menu);
	if (iflags.wc_font_status) free(iflags.wc_font_status);
	if (iflags.wc_tile_file) free(iflags.wc_tile_file);
	free_autopickup_exceptions();

#endif	/* FREE_ALL_MEMORY */
	return;
}


/*save.c*/
