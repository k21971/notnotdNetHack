/*	SCCS Id: @(#)global.h	3.4	2003/08/31	*/
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>


/* #define BETA	*/	/* if a beta-test copy	[MRS] */

/*
 * Files expected to exist in the playground directory.
 */

#define RECORD	      "record"	/* file containing list of topscorers */
#define HELP	      "help"	/* file containing command descriptions */
#define SHELP	      "hh"	/* abbreviated form of the same */
#define DEBUGHELP     "wizhelp" /* file containing debug mode cmds */
#define RUMORFILE     "rumors"	/* file with fortune cookies */
#define ORACLEFILE    "oracles" /* file with oracular information */
#define DATAFILE      "data"	/* file giving the meaning of symbols used */
#define CMDHELPFILE   "cmdhelp" /* file telling what commands do */
#define HISTORY       "history" /* file giving nethack's history */
#define LICENSE       "license" /* file with license information */
#define OPTIONFILE    "opthelp" /* file explaining runtime options */
#define OPTIONS_USED  "options" /* compile-time options, for #version */

#define LEV_EXT ".lev"		/* extension for special level files */


/* Assorted definitions that may depend on selections in config.h. */

/*
 * for DUMB preprocessor and compiler, e.g., cpp and pcc supplied
 * with Microport SysV/AT, which have small symbol tables;
 * DUMB if needed is defined in CFLAGS
 */

/*
 * type xchar: small integers in the range 0 - 127, usually coordinates
 * although they are nonnegative they must not be declared unsigned
 * since otherwise comparisons with signed quantities are done incorrectly
 */
typedef schar	xchar;
#ifndef SKIP_BOOLEAN
typedef xchar	boolean;		/* 0 or 1 */
#endif

#ifndef TRUE		/* defined in some systems' native include files */
#define TRUE	((boolean)1)
#define FALSE	((boolean)0)
#endif

#ifndef STRNCMPI
# define strcmpi(a,b) strncmpi((a),(b),-1)
#endif

/* comment out to test effects of each #define -- these will probably
 * disappear eventually
 */
#ifdef INTERNAL_COMP
# define RLECOMP	/* run-length compression of levl array - JLee */
# define ZEROCOMP	/* zero-run compression of everything - Olaf Seibert */
#endif

/* #define SPECIALIZATION */	/* do "specialized" version of new topology */

#ifdef BITFIELDS
#define Bitfield(x,n)	unsigned x:n
#else
#define Bitfield(x,n)	uchar x
#endif

#define SIZE(x) (int)(sizeof(x) / sizeof(x[0]))


/* A limit for some NetHack int variables.  It need not, and for comparable
 * scoring should not, depend on the actual limit on integers for a
 * particular machine, although it is set to the minimum required maximum
 * signed integer for C (2^15 -1).
 */
#define LARGEST_INT	32767


#define Getchar pgetchar


#include "coord.h"
/*
 * Automatic inclusions for the subsidiary files.
 * Please don't change the order.  It does matter.
 */

#ifdef UNIX
#include "unixconf.h"
#endif

/* Displayable name of this port; don't redefine if defined in *conf.h */
#ifndef PORT_ID
# ifdef UNIX
#  define PORT_ID	"Unix"
# endif
#endif

#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
# define EXIT_FAILURE 1
#endif

#define Sprintf  (void) sprintf
#define Strcat   (void) strcat
#define Strcpy   (void) strcpy
#define Snprintf (void) snprintf
#define Strncat  (void) strncat
#define Strncpy  (void) strncpy
#ifdef NEED_VARARGS
#define Vprintf  (void) vprintf
#define Vfprintf (void) vfprintf
#define Vsprintf (void) vsprintf
#endif


/* primitive memory leak debugging; see alloc.c */
#ifdef MONITOR_HEAP
extern long *nhalloc(unsigned int,const char *,int);
extern void nhfree(void *,const char *,int);
# ifndef __FILE__
#  define __FILE__ ""
# endif
# ifndef __LINE__
#  define __LINE__ 0
# endif
# define alloc(a) nhalloc(a,__FILE__,(int)__LINE__)
# define free(a) nhfree(a,__FILE__,(int)__LINE__)
#else	/* !MONITOR_HEAP */
extern long *alloc(unsigned int);		/* alloc.c */
#endif

/* Used for consistency checks of various data files; declare it here so
   that utility programs which include config.h but not hack.h can see it. */
struct version_info {
	unsigned long long	incarnation;	/* actual version number */
	unsigned long long	feature_set;	/* bitmask of config settings */
	unsigned long long	entity_count;	/* # of monsters and objects */
	unsigned long long	struct_sizes;	/* size of key structs */
};


/*
 * Configurable internal parameters.
 *
 * Please be very careful if you are going to change one of these.  Any
 * changes in these parameters, unless properly done, can render the
 * executable inoperative.
 */

/* size of terminal screen is (at least) (ROWNO+3) by COLNO */
#define COLNO	80
#define ROWNO	21

/* MAXCO must hold longest uncompressed status line, and must be larger
 * than COLNO
 *
 * longest practical second status line at the moment is
 *	Astral Plane $:123456 HP:1234(1234) Pw:1234(1234) Br:8 AC:-127
 *	DR:127 Xp:30/123456789 T:123456 Stone Slime Sufct FoodPois Ill
 *	Satiated Overloaded Blind Stun Conf Hallu Babble Scream Fly
 *	Ride
 * -- or about 190 characters
 */
#if COLNO <= 160
#define MAXCO 200
#else
#define MAXCO (COLNO+40)
#endif

#define MAXNROFROOMS	40	/* max number of rooms per level */
#define MAX_SUBROOMS	24	/* max # of subrooms in a given room */
#define DOORMAX		120	/* max number of doors per level */
#define ALTARMAX	20	/* max number of altars per level */

#define BUFSZ		1024	/* for getlin buffers */
#define LONGBUFSZ	4096	/* because we overflowed BUFSZ in one place */
#define QBUFSZ		 512	/* for building question text */
#define TBUFSZ		1024	/* toplines[] buffer max msg: 3 81char names */
				/* plus longest prefix plus a few extra words */
				/* tmptext keeps overflowing.  Maybe this is too small? Doubling the size (300-600). -CM */

#define PL_NSIZ		32	/* name of player, ghost, shopkeeper */
#define PL_CSIZ		32	/* sizeof pl_character */
#define PL_FSIZ		32	/* fruit name */
#define PL_PSIZ		63	/* player-given names for pets, other
				 * monsters, objects */

#define MAXDUNGEON	32	/* current maximum number of dungeons */ //where the hell did these come from?
#define MAXLEVEL	64	/* max number of levels in one dungeon */ // NOTE:flagged as DANGEROUS!  was 16 dungeons and 32 levels
#define MAXSTAIRS	1	/* max # of special stairways in a dungeon */
#define ALIGNWEIGHT	4	/* generation weight of alignment */

#define MAXULEV		30	/* max character experience level */

#define MAXMONNO	120	/* extinct monst after this number created */
#define MHPMAX		500	/* maximum monster hp */

#endif /* GLOBAL_H */
