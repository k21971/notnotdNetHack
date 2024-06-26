/*	SCCS Id: @(#)write.c	3.4	2001/11/29	*/
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"

static int cost(struct obj *);

/*
 * returns basecost of a scroll or a spellbook
 */
static int
cost(register struct obj *otmp)
{

	if (otmp->oclass == SPBOOK_CLASS)
		return(10 * objects[otmp->otyp].oc_level);

	switch (otmp->otyp) {
# ifdef MAIL
	case SCR_MAIL:
		return(2);
/*		break; */
# endif
	case SCR_LIGHT:
	case SCR_GOLD_DETECTION:
	case SCR_FOOD_DETECTION:
	case SCR_MAGIC_MAPPING:
	case SCR_AMNESIA:
	case SCR_FIRE:
	case SCR_EARTH:
	case SCR_WARD:
		return(8);
/*		break; */
	case SCR_DESTROY_ARMOR:
	case SCR_CREATE_MONSTER:
	case SCR_PUNISHMENT:
		return(10);
/*		break; */
	case SCR_CONFUSE_MONSTER:
		return(12);
/*		break; */
	case SCR_IDENTIFY:
		return(14);
/*		break; */
	case SCR_ENCHANT_ARMOR:
	case SCR_REMOVE_CURSE:
	case SCR_ENCHANT_WEAPON:
	case SCR_CHARGING:
		return(16);
/*		break; */
	case SCR_RESISTANCE:
	case SCR_ANTIMAGIC:
		return(18);
/*		break; */
	case SCR_SCARE_MONSTER:
	case SCR_STINKING_CLOUD:
	case SCR_TAMING:
	case SCR_TELEPORTATION:
	case SCR_WARDING:
		return(20);
/*		break; */
	case SCR_GENOCIDE:
		return(30);
/*		break; */
	case SCR_BLANK_PAPER:
	default:
		impossible("You can't write such a weird scroll!");
	}
	return(1000);
}

static const char write_on[] = { SCROLL_CLASS, SPBOOK_CLASS, 0 };

int
dowrite(register struct obj *pen)
{
	register struct obj *paper;
	char namebuf[BUFSZ], *nm, *bp;
	register struct obj *new_obj;
	int basecost, actualcost;
	int curseval;
	char qbuf[QBUFSZ];
	int first, last, i;
	boolean by_descr = FALSE;
	const char *typeword;
	int theward;
	
	if (nohands(youracedata)) {
	    You("need hands to be able to write!");
	    return 0;
	} else if (!freehand()) {
	    You("need a free %s to be able to write!", body_part(HAND));
	    return 0;
	} else if (Glib) {
	    pline("%s from your %s.",
		  Tobjnam(pen, "slip"), makeplural(body_part(FINGER)));
	    dropx(pen);
	    return 1;
	}

	/* get paper to write on */
	paper = getobj(write_on,"write on");
	if(!paper)
		return(0);
	typeword = (paper->oclass == SPBOOK_CLASS) ? "spellbook" : "scroll";
	if(Blind && !paper->dknown) {
		You("don't know if that %s is blank or not!", typeword);
		return(1);
	}
	paper->dknown = 1;
	if(paper->otyp != SCR_BLANK_PAPER && paper->otyp != SPE_BLANK_PAPER) {
		pline("That %s is not blank!", typeword);
		exercise(A_WIS, FALSE);
		return(1);
	}

	/* what to write */
	Sprintf(qbuf, "What type of %s do you want to write?", typeword);
	getlin(qbuf, namebuf);
	(void)mungspaces(namebuf);	/* remove any excess whitespace */
	if(namebuf[0] == '\033' || !namebuf[0])
		return(1);
	nm = namebuf;
	if (!strncmpi(nm, "scroll ", 7)) nm += 7;
	else if (!strncmpi(nm, "spellbook ", 10)) nm += 10;
	if (!strncmpi(nm, "of ", 3)) nm += 3;

	if ((bp = strstri(nm, " armour")) != 0) {
		(void)strcpy(bp, " armor ");
		eos(bp)[0] = ' ';	/* overwrite the '\0', we want the rest of the string */
		(void)mungspaces(bp + 1);	/* remove the extra space */
	}
	if(!strcmpi(nm, "heptagram")){
		if( !(u.wardsknown & WARD_HEPTAGRAM)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		theward = HEPTAGRAM;
		i = SCR_WARD;
		goto found_ward;
	} else if(!strcmpi(nm, "gorgoneion")){
		if( !(u.wardsknown & WARD_GORGONEION)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		theward = GORGONEION;
		i = SCR_WARD;
		goto found_ward;
	} else if(!strcmpi(nm, "circle of acheron") || 
				!strcmpi(nm, "circle") || 
				!strcmpi(nm, "acheron")){
		if( !(u.wardsknown & WARD_ACHERON)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		theward = CIRCLE_OF_ACHERON;
		i = SCR_WARD;
		goto found_ward;
	} else if(!strcmpi(nm, "pentagram")){
		if( !(u.wardsknown & WARD_PENTAGRAM)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		theward = PENTAGRAM;
		i = SCR_WARD;
		goto found_ward;
	} else if(!strcmpi(nm, "hexagram")){
		if( !(u.wardsknown & WARD_HEXAGRAM)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		theward = HEXAGRAM;
		i = SCR_WARD;
		goto found_ward;
	} else if(!strcmpi(nm, "hamsa") ||
				!strcmpi(nm, "hamsa mark")){
		if( !(u.wardsknown & WARD_HAMSA)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		theward = HAMSA;
		i = SCR_WARD;
		goto found_ward;
	} else if(!strcmpi(nm, "elder sign") || 
				!strcmpi(nm, "the elder sign")){
		if( !(u.wardsknown & WARD_ELDER_SIGN)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		theward = ELDER_SIGN;
		i = SCR_WARD;
		goto found_ward;
	} else if(!strcmpi(nm, "elder elemental eye") ||
				!strcmpi(nm, "elder eye") ||
				!strcmpi(nm, "elemental eye")){
		if( !(u.wardsknown & WARD_EYE)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		theward = ELDER_ELEMENTAL_EYE;
		i = SCR_WARD;
		goto found_ward;
	} else if(!strcmpi(nm, "sign of the scion queen mother") ||
				!strcmpi(nm, "sign of the scion queen mother") ||
				!strcmpi(nm, "scion queen mother") ||
				!strcmpi(nm, "queen mother") ||
				!strcmpi(nm, "mother") ||
				!strcmpi(nm, "sign")){
		if( !(u.wardsknown & WARD_QUEEN)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		theward = SIGN_OF_THE_SCION_QUEEN;
		i = SCR_WARD;
		goto found_ward;
	} else if(!strcmpi(nm, "cartouche of the cat lord") ||
				!strcmpi(nm, "cat lord") ||
				!strcmpi(nm, "cartouche")){
		if( !(u.wardsknown & WARD_CAT_LORD)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		i = CARTOUCHE_OF_THE_CAT_LORD;
		theward = TRUE;
		goto found_ward;
	} else if(!strcmpi(nm, "wings of garuda") ||
				!strcmpi(nm, "garuda") ||
				!strcmpi(nm, "wings")){
		if( !(u.wardsknown & WARD_GARUDA)){
			You_cant("scribe a ward you don't know!");
			return 1;
		}
		theward = WINGS_OF_GARUDA;
		i = SCR_WARD;
		goto found_ward;
	} else{
		first = bases[(int)paper->oclass];
		last = bases[(int)paper->oclass + 1] - 1;
		for (i = first; i <= last; i++) {
			/* extra shufflable descr not representing a real object */
			if (!OBJ_NAME(objects[i])) continue;

			if (!strcmpi(OBJ_NAME(objects[i]), nm))
				goto found;
			if (!strcmpi(OBJ_DESCR(objects[i]), nm)) {
				by_descr = TRUE;
				goto found;
			}
		}
		There("is no such %s!", typeword);
		return 1;
	}
found:
	if(i == SCR_WARD){
		You("must specify the ward to scribe!");
		return 1;
	}
found_ward:
	if (i == SCR_BLANK_PAPER || i == SPE_BLANK_PAPER) {
		You_cant("write that!");
		pline("It's obscene!");
		return 1;
	} else if (i == SPE_BOOK_OF_THE_DEAD || i == SPE_SECRETS || i == SCR_CONSECRATION) {
		pline("No mere dungeon adventurer could write that.");
		return 1;
	} else if (by_descr && paper->oclass == SPBOOK_CLASS &&
		    !objects[i].oc_name_known) {
		/* can't write unknown spellbooks by description */
		pline(
		  "Unfortunately you don't have enough information to go on.");
		return 1;
	}

	/* KMH, conduct */
	u.uconduct.literate++;

	new_obj = mksobj(i, MKOBJ_NOINIT);
	new_obj->bknown = (paper->bknown && pen->bknown);
	if(i==SCR_WARD){
		new_obj->oward = theward;
	}

	/* shk imposes a flat rate per use, not based on actual charges used */
	check_unpaid(pen);

	/* see if there's enough ink */
	basecost = cost(new_obj);
	
	if(Role_if(PM_WIZARD))
		basecost = basecost * 4 / 5;

	if(pen->spe < basecost/2)  {
		Your("marker is too dry to write that!");
		obfree(new_obj, (struct obj *) 0);
		return(1);
	}

	/* we're really going to write now, so calculate cost
	 */
	actualcost = rn1(basecost/2,basecost/2);
	curseval = bcsign(pen) + bcsign(paper);
	exercise(A_WIS, TRUE);
	/* dry out marker */
	if (pen->spe < actualcost) {
		pen->spe = 0;
		Your("marker dries out!");
		/* scrolls disappear, spellbooks don't */
		if (paper->oclass == SPBOOK_CLASS) {
			pline_The(
		       "spellbook is left unfinished and your writing fades.");
			update_inventory();	/* pen charges */
		} else {
			pline_The("scroll is now useless and disappears!");
			useup(paper);
		}
		obfree(new_obj, (struct obj *) 0);
		return(1);
	}
	pen->spe -= actualcost;
	
	struct objclass *oc = &objects[new_obj->otyp];
	int school_skill = 0;
	int skl;
	int spell_schools[] = {P_ATTACK_SPELL, P_HEALING_SPELL, P_DIVINATION_SPELL, P_ENCHANTMENT_SPELL, P_CLERIC_SPELL, P_ESCAPE_SPELL, P_MATTER_SPELL};
	int generalism_bonus = 0;
	for(skl=0; skl < SIZE(spell_schools); skl++)
		generalism_bonus += max(0, P_SKILL(spell_schools[skl])-1);
	if(oc->oc_skill && new_obj->oclass == SPBOOK_CLASS){
		//-1 (restricted) to +3 (expert)
		school_skill = P_SKILL(oc->oc_skill) - 1;
		if(school_skill*2 >= oc->oc_level){
			//Note: double-counts school_skill by design
			school_skill = school_skill*5 + generalism_bonus*5;
		}
		else {
			school_skill = school_skill*5 - oc->oc_level*5;
		}
	}
	else {
			school_skill = generalism_bonus*5;
	}
	//			(15*3)		16				14/2			2*10 (skilled)		4 >= 4 (skilled vs. fireball)
	//			45			16				7				20					-0
	//			45			61				68				88%

	//			(20*3)		23				23/2			1*5 (basic)		2 < 5 (basic vs. charm)
	//			60			23				11				5					-30
	//			60			83				94				99					69%

	//			(20*3)		23				23/2			3*5 (expert)		6 < 7 (expert vs. finger of death)
	//			60			23				11				15					-35
	//			60			83				94				109					74%
	int target = u.ulevel*3 + ACURR(A_INT) + ACURR(A_WIS)/2 + school_skill;
	
	if(!Role_if(PM_WIZARD) && target > 0)
		target /= 5;
	
	/* can't write if we don't know it - unless we're lucky */
	if(objects[new_obj->otyp].oc_nowish ||
	  (!(objects[new_obj->otyp].oc_name_known) &&
	   !(by_descr && objects[new_obj->otyp].oc_uname) &&
	   (rnl(100) >= target))
	){
		if(new_obj->otyp != SPE_SECRETS) You("%s to write that!", by_descr ? "fail" : "don't know how");
		/* scrolls disappear, spellbooks don't */
		if (paper->oclass == SPBOOK_CLASS) {
			You(
       "write in your best handwriting:  \"My Diary\", but it quickly fades.");
			update_inventory();	/* pen charges */
		} else {
			if (by_descr) {
			    Strcpy(namebuf, OBJ_DESCR(objects[new_obj->otyp]));
			    wipeout_text(namebuf, (6+MAXULEV - u.ulevel)/6, 0);
			} else
			    Sprintf(namebuf, "%s was here!", plname);
			You("write \"%s\" and the scroll disappears.", namebuf);
			useup(paper);
		}
		obfree(new_obj, (struct obj *) 0);
		return(1);
	}

	/* useup old scroll / spellbook */
	useup(paper);

	/* success */
	if (new_obj->oclass == SPBOOK_CLASS) {
		/* acknowledge the change in the object's description... */
		pline_The("spellbook warps strangely, then turns %s.",
		      OBJ_DESCR(objects[new_obj->otyp]));
	}
	new_obj->blessed = (curseval > 0);
	new_obj->cursed = (curseval < 0);
#ifdef MAIL
	if (new_obj->otyp == SCR_MAIL) new_obj->spe = 1;
#endif
	new_obj = hold_another_object(new_obj, "Oops!  %s out of your grasp!",
					       The(aobjnam(new_obj, "slip")),
					       (const char *)0);
	return(1);
}

/*write.c*/
