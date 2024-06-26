/*	SCCS Id: @(#)fountain.c	3.4	2003/03/23	*/
/*	Copyright Scott R. Turner, srt@ucla, 10/27/86 */
/* NetHack may be freely redistributed.  See license for details. */

/* Code for drinking from fountains. */

#include "hack.h"

static void dowatersnakes(void);
static void dowaterdemon(void);
static void dowaternymph(void);
static void dolavademon(void);
static void gush(int,int,void *);
static void dofindgem(void);
static void blowupforge(int, int);

void
floating_above(const char *what)
{
    You("are floating high above the %s.", what);
}

static void
dowatersnakes(void) /* Fountain of snakes! */
{
    register int num = rn1(5,2);
    struct monst *mtmp;

    if (!(mvitals[PM_WATER_MOCCASIN].mvflags & G_GONE && !In_quest(&u.uz))) {
	if (!Blind)
	    pline("An endless stream of %s pours forth!",
		  Hallucination ? makeplural(rndmonnam()) : "snakes");
	else
	    You_hear("%s hissing!", something);
	while(num-- > 0)
	    if((mtmp = makemon(&mons[PM_WATER_MOCCASIN],
			u.ux, u.uy, NO_MM_FLAGS)) && t_at(mtmp->mx, mtmp->my))
		(void) mintrap(mtmp);
    } else
	pline_The("fountain bubbles furiously for a moment, then calms.");
}

static void
dowaterdemon(void) /* Water demon */
{
    register struct monst *mtmp;

    if(!(mvitals[PM_MARID].mvflags & G_GONE && !In_quest(&u.uz))) {
	if((mtmp = makemon(&mons[PM_MARID],u.ux,u.uy, NO_MM_FLAGS))) {
	    if (!Blind)
		You("unleash %s!", a_monnam(mtmp));
	    else
		You_feel("the presence of evil.");

	/* Give those on low levels a (slightly) better chance of survival */
	    if (rnd(100) > (80 + level_difficulty())) {
		pline("Grateful for %s release, %s grants you a wish!",
		      mhis(mtmp), mhe(mtmp));
		makewish(allow_artwish() | WISH_VERBOSE);
		mongone(mtmp);
	    } else if (t_at(mtmp->mx, mtmp->my))
		(void) mintrap(mtmp);
	}
    } else
	pline_The("fountain bubbles furiously for a moment, then calms.");
}

/* Lava Demon */
static void
dolavademon(void)
{
    struct monst *mtmp;

    if (!(mvitals[PM_LAVA_DEMON].mvflags & G_GONE)) {
        if ((mtmp = makemon(&mons[PM_LAVA_DEMON], u.ux, u.uy,
                            MM_ADJACENTOK)) != 0) {
            if (!Blind)
                You("summon %s!", a_monnam(mtmp));
            else
                You_feel("the temperature rise significantly.");

            /* Give those on low levels a (slightly) better chance of survival
             */
            if (rnd(100) > (80 + level_difficulty())) {
                pline("Freed from the depths of Gehennom, %s offers to aid you in your quest!",
                      mhe(mtmp));
                (void) tamedog_core(mtmp, (struct obj *) 0, TRUE);
            } else if (t_at(mtmp->mx, mtmp->my))
                (void) mintrap(mtmp);
        }
    } else
        pline_The("forge violently spews lava for a moment, then settles.");
}

static void
dowaternymph(void) /* Water Nymph */
{
	register struct monst *mtmp;

	if(!(mvitals[PM_NAIAD].mvflags & G_GONE && !In_quest(&u.uz)) &&
	   (mtmp = makemon(&mons[PM_NAIAD],u.ux,u.uy, NO_MM_FLAGS))) {
		if (!Blind)
		   You("attract %s!", a_monnam(mtmp));
		else
		   You_hear("a seductive voice.");
		mtmp->msleeping = 0;
		if (t_at(mtmp->mx, mtmp->my))
		    (void) mintrap(mtmp);
	} else
		if (!Blind)
		   pline("A large bubble rises to the surface and pops.");
		else
		   You_hear("a loud pop.");
}

void
dogushforth( /* Gushing forth along LOS from (u.ux, u.uy) */
	int drinking)
{
	int madepool = 0;

	do_clear_area(u.ux, u.uy, 7, gush, (void *)&madepool);
	if (!madepool) {
	    if (drinking)
		Your("thirst is quenched.");
	    else
		pline("Water sprays all over you.");
	}
}

static void
gush(int x, int y, void * poolcnt)
{
	register struct monst *mtmp;
	register struct trap *ttmp;

	if (((x+y)%2) || (x == u.ux && y == u.uy) ||
	    (rn2(1 + distmin(u.ux, u.uy, x, y)))  ||
	    (levl[x][y].typ != ROOM) ||
	    (boulder_at(x, y)) || nexttodoor(x, y))
		return;

	if ((ttmp = t_at(x, y)) != 0 && !delfloortrap(ttmp))
		return;

	if (!((*(int *)poolcnt)++))
	    pline("Water gushes forth from the overflowing fountain!");

	/* Put a puddle at x, y */
	levl[x][y].typ = PUDDLE;
	del_engr_ward_at(x, y);
	water_damage(level.objects[x][y], FALSE, TRUE, FALSE, (struct monst *) 0);

	if ((mtmp = m_at(x, y)) != 0)
		(void) minliquid(mtmp);
	else
		newsym(x,y);
}

static void
dofindgem(void) /* Find a gem in the sparkling waters. */
{
	if (!Blind) You("spot a gem in the sparkling waters!");
	else You_feel("a gem here!");
	(void) mksobj_at(rnd_class(DILITHIUM_CRYSTAL, LUCKSTONE-1),
			 u.ux, u.uy, MKOBJ_NOINIT);
	SET_FOUNTAIN_LOOTED(u.ux,u.uy);
	newsym(u.ux, u.uy);
	exercise(A_WIS, TRUE);			/* a discovery! */
}

void
dryup(xchar x, xchar y, boolean isyou)
{
	if (IS_FOUNTAIN(levl[x][y].typ) &&
	    (!rn2(3) || FOUNTAIN_IS_WARNED(x,y))) {
		if(isyou && in_town(x, y) && !FOUNTAIN_IS_WARNED(x,y)) {
			struct monst *mtmp;
			SET_FOUNTAIN_WARNED(x,y);
			/* Warn about future fountain use. */
			for(mtmp = fmon; mtmp; mtmp = mtmp->nmon) {
			    if (DEADMONSTER(mtmp)) continue;
			    if ((mtmp->mtyp == PM_WATCHMAN ||
				mtmp->mtyp == PM_WATCH_CAPTAIN) &&
			       couldsee(mtmp->mx, mtmp->my) &&
			       mtmp->mpeaceful) {
				pline("%s yells:", Amonnam(mtmp));
				verbalize("Hey, stop using that fountain!");
				break;
			    }
			}
			/* You can see or hear this effect */
			if(!mtmp) pline_The("flow reduces to a trickle.");
			return;
		}
#ifdef WIZARD
		if (isyou && wizard) {
			if (yn("Dry up fountain?") == 'n')
				return;
		}
#endif
		/* replace the fountain with ordinary floor */
		levl[x][y].typ = ROOM;
		levl[x][y].looted = 0;
		levl[x][y].blessedftn = 0;
		if (cansee(x,y)) pline_The("fountain dries up!");
		/* The location is seen if the hero/monster is invisible */
		/* or felt if the hero is blind.			 */
		newsym(x, y);
		level.flags.nfountains--;
		if(isyou && in_town(x, y))
		    (void) angry_guards(FALSE);
		
		if(isyou && u.sealsActive&SEAL_EDEN) unbind(SEAL_EDEN,TRUE);
	}
}

void
dipforge(register struct obj *obj)
{
	if (Levitation) {
		floating_above("forge");
		return;
	}

	burn_away_slime();
	melt_frozen_air();

	/* Dipping something you're still wearing into a forge filled with
	 * lava, probably not the smartest thing to do. This is gonna hurt.
	 * Non-metallic objects are handled by lava_damage().
	 */
	if (is_metallic(obj) && (obj->owornmask & (W_ARMOR | W_ACCESSORY))) {
		if (!Fire_resistance) {
			You("dip your worn %s into the forge.  You burn yourself!",
				xname(obj));
			if (!rn2(3))
				You("may want to remove your %s first...",
					xname(obj));
			losehp(d(2, 8),
				   "dipping a worn object into a forge", KILLED_BY);
		}
		else {
			You("dip your worn %s into the forge.  This is fine.",
				xname(obj));
			if (!rn2(3))
				You("may want to remove your %s first...",
					xname(obj));
		}
		return;
	}

	/* If punished and wielding a hammer, there's a good chance
	 * you can use a forge to free yourself */
	if (Punished && obj->otyp == HEAVY_IRON_BALL) {
		if ((uwep && !is_hammer(uwep)) || !uwep) { /* sometimes drop a hint */
			if (!rn2(4))
				pline("You'll need a hammer to be able to break the chain.");
			goto result;
		} else if (uwep && is_hammer(uwep)) {
			You("place the ball and chain inside the forge.");
			pline("Raising your %s, you strike the chain...",
				  xname(uwep));
			if (!rn2((P_SKILL(P_HAMMER) < P_SKILLED) ? 8 : 2)
				&& Luck >= 0) { /* training up hammer skill pays off */
				pline("The chain breaks free!");
				unpunish();
			} else {
				pline("Clang!");
			}
		}
		return;
	}

result:
	switch (rnd(30)) {
	case 6:
	case 7:
	case 8:
	case 9: /* Strange feeling */
		pline("A weird sensation runs up your %s.", body_part(ARM));
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
		if (!is_metallic(obj))
			goto lava;
		Your("%s glows briefly from the heat.", xname(obj));

		// /* TODO: perhaps our hero needs to wield some sort of tool to
		   // successfully reforge an object? */
		// if (is_metallic(obj) && Luck >= 0) {
			// if (greatest_erosion(obj) > 0) {
				// if (!Blind)
					// You("successfully reforge your %s, repairing some of the damage.",
						// xname(obj));
				// if (obj->oeroded > 0)
					// obj->oeroded--;
				// if (obj->oeroded2 > 0)
					// obj->oeroded2--;
			// } else {
				// if (!Blind) {
					// Your("%s glows briefly from the heat, but looks reforged and as new as ever.",
						 // xname(obj));
				// }
			// }
		// }
		break;
	case 19:
	case 20:
		if (!is_metallic(obj))
			goto lava;
		You_feel("a sudden wave of heat.");

		// if (!obj->blessed && is_metallic(obj) && Luck > 5) {
			// bless(obj);
			// if (!Blind) {
				// Your("%s glows blue for a moment.",
					 // xname(obj));
			// }
		// } else {
			// You_feel("a sudden wave of heat.");
		// }
		break;
	case 21: /* Lava Demon */
		if (!rn2(8))
			dolavademon();
		else
			pline_The("forge violently spews lava for a moment, then settles.");
		break;
	case 22:
		if (Luck < 0) {
			blowupforge(u.ux, u.uy);
			/* Avoid destroying the same item twice (lava_damage) */
			return;
		} else {
			pline("Molten lava surges up and splashes all over you!");
			if(!Fire_resistance)
				losehp(d(6, 6), "dipping into a forge", KILLED_BY);
		}
		break;
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30: /* Strange feeling */
		You_feel("a sudden flare of heat.");
		break;
	}
lava:
	lava_damage(obj, u.ux, u.uy);
	update_inventory();
}

void
drinkfountain(void)
{
	/* What happens when you drink from a fountain? */
	register boolean mgkftn = (levl[u.ux][u.uy].blessedftn == 1);
	register int fate = rnd(30);

	if (Levitation) {
		floating_above("fountain");
		return;
	}

	if (mgkftn && u.uluck >= 0 && fate >= 10) {
		int i, ii, littleluck = (u.uluck < 4);

		pline("Wow!  This makes you feel great!");
		/* blessed restore ability */
		for (ii = 0; ii < A_MAX; ii++)
		    if (ABASE(ii) < AMAX(ii)) {
			ABASE(ii) = AMAX(ii);
			flags.botl = 1;
		    }
		/* gain ability, blessed if "natural" luck is high */
		i = rn2(A_MAX);		/* start at a random attribute */
		for (ii = 0; ii < A_MAX; ii++) {
		    if (adjattrib(i, 1, littleluck ? -1 : 0) && littleluck)
			break;
		    if (++i >= A_MAX) i = 0;
		}
		display_nhwindow(WIN_MESSAGE, FALSE);
		pline("A wisp of vapor escapes the fountain...");
		exercise(A_WIS, TRUE);
		levl[u.ux][u.uy].blessedftn = 0;
		return;
	}

	if (fate < 10) {
		pline_The("cool draught refreshes you.");
		if(Race_if(PM_INCANTIFIER)) u.uen += rnd(10); /* don't choke on water */
		else u.uhunger += rnd(10); /* don't choke on water */
		newuhs(FALSE);
		if(mgkftn) return;
	} else {
	    switch (fate) {

		case 19: /* Self-knowledge */

			You_feel("self-knowledgeable...");
			display_nhwindow(WIN_MESSAGE, FALSE);
			doenlightenment();
			exercise(A_WIS, TRUE);
			pline_The("feeling subsides.");
			break;

		case 20: /* Foul water */

			if (!umechanoid){
				pline_The("water is foul!  You gag and vomit.");
				morehungry(rn1(20, 11));
				vomit();
	    		} 
			else {
				pline_The("water is foul! It offends your olfactory receptors.");
			}
			
			break;

		case 21: /* Poisonous */

			pline_The("water is contaminated!");
			if (Poison_resistance) {
			   pline(
			      "Perhaps it is runoff from the nearby %s farm.",
				 fruitname(FALSE));
			   losehp(rnd(4),"unrefrigerated sip of juice",
				KILLED_BY_AN);
			   break;
			}
			losestr(rn1(4,3));
			losehp(rnd(10),"contaminated water", KILLED_BY);
			exercise(A_CON, FALSE);
			break;

		case 22: /* Fountain of snakes! */

			dowatersnakes();
			break;

		case 23: /* Water demon */
			dowaterdemon();
			break;

		case 24: /* Curse an item */ {
			register struct obj *obj;

			pline("This water's no good!");
			morehungry(rn1(20, 11));
			exercise(A_CON, FALSE);
			rndcurse();
			break;
			}

		case 25: /* See invisible */

			if (Blind) {
			    if (Invisible) {
				You("feel transparent.");
			    } else {
			    	You("feel very self-conscious.");
			    	pline("Then it passes.");
			    }
			} else {
			   You("see an image of someone stalking you.");
			   pline("But it disappears.");
			}
			HSee_invisible |= TIMEOUT_INF;
			newsym(u.ux,u.uy);
			exercise(A_WIS, TRUE);
			break;

		case 26: /* See Monsters */

			(void) monster_detect((struct obj *)0, 0);
			exercise(A_WIS, TRUE);
			break;

		case 27: /* Find a gem in the sparkling waters. */

			if (!FOUNTAIN_IS_LOOTED(u.ux,u.uy)) {
				dofindgem();
				break;
			}

		case 28: /* Water Nymph */

			dowaternymph();
			break;

		case 29: /* Scare */ {
			register struct monst *mtmp;

			pline("This water gives you bad breath!");
			for(mtmp = fmon; mtmp; mtmp = mtmp->nmon)
			    if(!DEADMONSTER(mtmp))
				monflee(mtmp, 0, FALSE, FALSE);
			}
			break;

		case 30: /* Gushing forth in this room */

			dogushforth(TRUE);
			break;

		default:

			pline("This tepid water is tasteless.");
			break;
	    }
	}
	dryup(u.ux, u.uy, TRUE);
}

void
dipfountain(register struct obj *obj)
{
	if (Levitation) {
		floating_above("fountain");
		return;
	}

	/* Don't grant Excalibur when there's more than one object.  */
	/* (quantity could be > 1 if merged daggers got polymorphed) */
	if (obj->otyp == LONG_SWORD && obj->quan == 1L
	    && u.ulevel >= 5 && !rn2(6)
	    && !obj->oartifact
	    && !art_already_exists(ART_EXCALIBUR)) {

		if (u.ualign.type != A_LAWFUL) {
			/* Ha!  Trying to cheat her. */
			pline("A freezing mist rises from the water and envelops the sword.");
			pline_The("fountain disappears!");
			curse(obj);
			if (obj->spe > -6 && !rn2(3)) obj->spe--;
			obj->oerodeproof = FALSE;
			exercise(A_WIS, FALSE);
		} else {
			/* The lady of the lake acts! - Eric Backus */
			/* Be *REAL* nice */
			pline("From the murky depths, a hand reaches up to bless the sword.");
			pline("As the hand retreats, the fountain disappears!");
			obj = oname(obj, artiname(ART_EXCALIBUR));
			discover_artifact(ART_EXCALIBUR);
			bless(obj);
			obj->oeroded = obj->oeroded2 = 0;
			obj->oerodeproof = TRUE;
			exercise(A_WIS, TRUE);
		}
		update_inventory();
		levl[u.ux][u.uy].typ = ROOM;
		levl[u.ux][u.uy].looted = 0;
		newsym(u.ux, u.uy);
		level.flags.nfountains--;
		if(in_town(u.ux, u.uy))
		    (void) angry_guards(FALSE);
		return;
	} else if (get_wet(obj,FALSE) && !rn2(2))
		return;

	/* Acid and water don't mix */
	if (obj->otyp == POT_ACID) {
	    useup(obj);
	    return;
	}

	switch (rnd(30)) {
		case 16: /* Curse the item */
			curse(obj);
			break;
		case 17:
		case 18:
		case 19:
		case 20: /* Uncurse the item */
			if(obj->cursed) {
			    if (!Blind)
				pline_The("water glows for a moment.");
			    uncurse(obj);
			} else {
			    pline("A feeling of loss comes over you.");
			}
			break;
		case 21: /* Water Demon */
			dowaterdemon();
			break;
		case 22: /* Water Nymph */
			dowaternymph();
			break;
		case 23: /* an Endless Stream of Snakes */
			dowatersnakes();
			break;
		case 24: /* Find a gem */
			if (!FOUNTAIN_IS_LOOTED(u.ux,u.uy)) {
				dofindgem();
				break;
			}
		case 25: /* Water gushes forth */
			dogushforth(FALSE);
			break;
		case 26: /* Strange feeling */
			pline("A strange tingling runs up your %s.",
							body_part(ARM));
			break;
		case 27: /* Strange feeling */
			You_feel("a sudden chill.");
			break;
		case 28: /* Strange feeling */
			pline("An urge to take a bath overwhelms you.");
#ifndef GOLDOBJ
			if (u.ugold > 10) {
			    u.ugold -= somegold() / 10;
			    You("lost some of your gold in the fountain!");
			    CLEAR_FOUNTAIN_LOOTED(u.ux,u.uy);
			    exercise(A_WIS, FALSE);
			}
#else
			{
			    long money = money_cnt(invent);
			    struct obj *otmp;
                            if (money > 10) {
				/* Amount to loose.  Might get rounded up as fountains don't pay change... */
			        money = somegold(money) / 10; 
			        for (otmp = invent; otmp && money > 0; otmp = otmp->nobj) if (otmp->oclass == COIN_CLASS) {
				    int denomination = objects[otmp->otyp].oc_cost;
				    long coin_loss = (money + denomination - 1) / denomination;
                                    coin_loss = min(coin_loss, otmp->quan);
				    otmp->quan -= coin_loss;
				    money -= coin_loss * denomination;				  
				    if (!otmp->quan) delobj(otmp);
				}
			        You("lost some of your money in the fountain!");
				CLEAR_FOUNTAIN_LOOTED(u.ux,u.uy);
			        exercise(A_WIS, FALSE);
                            }
			}
#endif
			break;
		case 29: /* You see coins */

		/* We make fountains have more coins the closer you are to the
		 * surface.  After all, there will have been more people going
		 * by.	Just like a shopping mall!  Chris Woodbury  */

		    if (FOUNTAIN_IS_LOOTED(u.ux,u.uy)) break;
		    SET_FOUNTAIN_LOOTED(u.ux,u.uy);
		    (void) mkgold((long)
			(rnd((dunlevs_in_dungeon(&u.uz)-dunlev(&u.uz)+1)*2)+5),
			u.ux, u.uy);
		    if (!Blind)
		pline("Far below you, you see coins glistening in the water.");
		    exercise(A_WIS, TRUE);
		    newsym(u.ux,u.uy);
		    break;
	}
	update_inventory();
	dryup(u.ux, u.uy, TRUE);
}

void
breakforge(int x, int y)
{
    if (cansee(x, y) || (x == u.ux && y == u.uy))
        pline_The("forge splits in two as molten lava rushes forth!");
    levl[x][y].doormask = 0;
    levl[x][y].typ = LAVAPOOL;
    newsym(x, y);
    level.flags.nforges--;
}

void
blowupforge(int x, int y)
{
    if (cansee(x, y) || (x == u.ux && y == u.uy))
        pline_The("forge rumbles, then explodes!  Molten lava splashes everywhere!");
    levl[x][y].typ = ROOM, levl[x][y].flags = 0;
    levl[x][y].doormask = 0;
    newsym(x, y);
    level.flags.nforges--;
    explode(u.ux, u.uy, AD_FIRE, FORGE_EXPLODE, d(6,6), EXPL_FIERY, 1);
}

//Note: used in EvilHack if a forge is used up by forging magic or artifacts

void
coolforge(int x, int y)
{
    if (cansee(x, y) || (x == u.ux && y == u.uy))
        pline_The("lava in the forge cools and solidifies.");
    levl[x][y].typ = ROOM, levl[x][y].flags = 0;
    levl[x][y].doormask = 0;
    newsym(x, y);
    level.flags.nforges--;
}

void
drinkforge(void)
{
    if (Levitation) {
        floating_above("forge");
        return;
    }

    if (!likes_fire(youmonst.data)) {
        pline("Molten lava incinerates its way down your gullet...");
        losehp(Upolyd ? u.mh : u.uhp, "trying to drink molten lava", KILLED_BY);
        return;
    }
    burn_away_slime();
	melt_frozen_air();
    switch(rn2(20)) {
    case 0:
        pline("You drink some molten lava.  Mmmmm mmm!");
		if(!Race_if(PM_INCANTIFIER))
			lesshungry(rnd(50));
        break;
    case 1:
        breakforge(u.ux, u.uy);
        break;
    case 2:
    case 3:
        pline_The("%s moves as though of its own will!", hliquid("lava"));
        if ((mvitals[PM_FIRE_ELEMENTAL].mvflags & G_GONE)
            || !makemon(&mons[PM_FIRE_ELEMENTAL], u.ux, u.uy, MM_ADJACENTOK)
		)
            pline("But it settles down.");
        break;
    default:
        pline("You take a sip of molten lava.");
		if(!Race_if(PM_INCANTIFIER))
			lesshungry(rnd(5));
    }
}

void
breaksink(int x, int y)
{
    if(cansee(x,y) || (x == u.ux && y == u.uy))
	pline_The("pipes break!  Water spurts out!");
    level.flags.nsinks--;
    levl[x][y].doormask = 0;
    levl[x][y].typ = FOUNTAIN;
    level.flags.nfountains++;
    newsym(x,y);
}

void
drinksink(void)
{
	struct obj *otmp;
	struct monst *mtmp;

	if (Levitation) {
		floating_above("sink");
		return;
	}
	switch(rn2(20)) {
		case 0: You("take a sip of very cold water.");
			break;
		case 1: You("take a sip of very warm water.");
			break;
		case 2: You("take a sip of scalding hot water.");
			if (Fire_resistance)
				pline("It seems quite tasty.");
			else losehp(rnd(6), "sipping boiling water", KILLED_BY);
			break;
		case 3: if (mvitals[PM_SEWER_RAT].mvflags & G_GONE && !In_quest(&u.uz))
				pline_The("sink seems quite dirty.");
			else {
				mtmp = makemon(&mons[PM_SEWER_RAT],
						u.ux, u.uy, NO_MM_FLAGS);
				if (mtmp) pline("Eek!  There's %s in the sink!",
					(Blind || !canspotmon(mtmp)) ?
					"something squirmy" :
					a_monnam(mtmp));
			}
			break;
		case 4: do {
				/* use Luck here instead of u.uluck */
				if (!rn2(13) && ((Luck >= 0 && is_vampire(youracedata)) ||
				    (Luck <= 0 && !is_vampire(youracedata)))) {
					otmp = mksobj(POT_BLOOD, MKOBJ_NOINIT);
					if(Luck){
						/*Good luck: vampire, which wants cursed human blood, bad luck: sucks to be a human PC!*/
						otmp->corpsenm = PM_HUMAN;
						curse(otmp);
					}
					else {
						otmp->corpsenm = (mvitals[PM_SEWER_RAT].mvflags & G_GENOD && !In_quest(&u.uz)) ? PM_WERERAT : PM_SEWER_RAT;
					}
				} else {
					otmp = mkobj(POTION_CLASS, NO_MKOBJ_FLAGS);
					if (otmp->otyp == POT_WATER) {
						obfree(otmp, (struct obj *)0);
						otmp = (struct obj *) 0;
					}
				}
			} while(!otmp);
			otmp->cursed = otmp->blessed = 0;
			pline("Some %s liquid flows from the faucet.",
			      Blind ? "odd" :
			      hcolor(OBJ_DESCR(objects[otmp->otyp])));
			otmp->dknown = !(Blind || Hallucination);
			otmp->quan++; /* Avoid panic upon useup() */
			otmp->fromsink = 1; /* kludge for docall() */
			(void) dopotion(otmp, TRUE);
			obfree(otmp, (struct obj *)0);
			break;
		case 5: if (!(levl[u.ux][u.uy].looted & S_LRING)) {
			    You("find a ring in the sink!");
			    (void) mkobj_at(RING_CLASS, u.ux, u.uy, MKOBJ_ARTIF);
			    levl[u.ux][u.uy].looted |= S_LRING;
			    exercise(A_WIS, TRUE);
			    newsym(u.ux,u.uy);
			} else pline("Some dirty water backs up in the drain.");
			break;
		case 6: breaksink(u.ux,u.uy);
			break;
		case 7: pline_The("water moves as though of its own will!");
			if ((mvitals[PM_WATER_ELEMENTAL].mvflags & G_GONE && !In_quest(&u.uz))
			    || !makemon(&mons[PM_WATER_ELEMENTAL],
					u.ux, u.uy, NO_MM_FLAGS))
				pline("But it quiets down.");
			break;
		case 8: pline("Yuk, this water tastes awful.");
			more_experienced(1,0);
			newexplevel();
			break;
		case 9: if (!uclockwork) {
				pline("Gaggg... this tastes like sewage!  You vomit.");
				morehungry(max_ints(1, rn1(30-ACURR(A_CON), 11) * get_uhungersizemod()));
				vomit();
			}
			else {
				pline("Ugh, this tastes like sewage. Your gustatory receptors are offended.");
			}
			
			break;
		case 10: pline("This water contains toxic wastes!");
			if (!Unchanging) {
				You("undergo a freakish metamorphosis!");
				polyself(FALSE);
			}
			break;
		/* more odd messages --JJB */
		case 11: You_hear("clanking from the pipes...");
			break;
		case 12: You_hear("snatches of song from among the sewers...");
			break;
		case 19: if (Hallucination) {
		   pline("From the murky drain, a hand reaches up... --oops--");
				break;
			}
		default: You("take a sip of %s water.",
			rn2(3) ? (rn2(2) ? "cold" : "warm") : "hot");
	}
}

/*fountain.c*/
