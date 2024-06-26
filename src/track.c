/*	SCCS Id: @(#)track.c	3.4	87/08/08	*/
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NetHack may be freely redistributed.  See license for details. */
/* track.c - version 1.0.2 */

#include "hack.h"

#define UTSZ	200

static int utcnt, utpnt;
static coord utrack[UTSZ];


void
initrack(void)
{
	utcnt = utpnt = 0;
}


/* add to track */
void
settrack(void)
{
	if(utcnt < UTSZ) utcnt++;
	if(utpnt == UTSZ) utpnt = 0;
	utrack[utpnt].x = u.ux;
	utrack[utpnt].y = u.uy;
	utpnt++;
}


coord *
gettrack(register int x, register int y, register int maxtrack)
{
    int cnt, ndist;
    coord *tc;
    cnt = !maxtrack ? utcnt : min(maxtrack, utcnt);
    for(tc = &utrack[utpnt]; cnt--; ){
		if(tc == utrack) tc = &utrack[UTSZ-1];
	
	
		else tc--;
		ndist = distmin(x,y,tc->x,tc->y);
	
		if(ndist <= 1)
		    return ndist ? tc : 0 ;
    }
    return (coord *)0;
}


/*track.c*/
