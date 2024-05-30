/*	SCCS Id: @(#)extern.h	3.4	2003/03/10	*/
/* Copyright (c) Steve Creps, 1988.				  */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef EXTERN_H
#define EXTERN_H

/* ### alloc.c ### */

#if 0
extern long *alloc(unsigned int);
#endif
extern char *fmt_ptr(const void *,char *);

/* This next pre-processor directive covers almost the entire file,
 * interrupted only occasionally to pick up specific functions as needed. */
#if !defined(MAKEDEFS_C) && !defined(LEV_LEX_C)

/* ### allmain.c ### */

extern int you_action_cost(int, boolean);
extern void moveloop(void);
extern void stop_occupation(void);
extern void display_gamewindows(void);
extern void newgame(void);
extern void welcome(boolean);
extern time_t get_realtime(void);
extern void dogoat(void);
extern void dogoat_mon(struct monst *);
extern boolean doyog(struct monst *);
extern void dotwin_cast(struct monst *);
extern void dochaos_mon(struct monst *);
extern void dohost_mon(struct monst *);
extern void dosnake(struct monst *);
extern void dokraken_mon(struct monst *);
extern void dotailslap(struct monst *);
extern void dovines(struct monst *);
extern void dostarblades(struct monst *);
extern void dostorm(struct monst *);
extern void donachash(struct monst *);

/* ### apply.c ### */

extern int doapply(void);
extern int dorub(void);
extern int dojump(void);
extern int jump(int);
extern int number_leashed(void);
extern void o_unleash(struct obj *);
extern void m_unleash(struct monst *,boolean);
extern void unleash_all(void);
extern boolean next_to_u(void);
extern struct obj *get_mleash(struct monst *);
extern void check_leash(xchar,xchar);
extern boolean um_dist(xchar,xchar,xchar);
extern boolean snuff_candle(struct obj *);
extern boolean snuff_lit(struct obj *);
extern boolean catch_lit(struct obj *);
extern void use_unicorn_horn(struct obj *);
extern void use_bell(struct obj **, int);
extern boolean tinnable(struct obj *);
extern void reset_trapset(void);
extern void fig_transform(void *, long);
extern int use_whip(struct obj *);
extern int use_nunchucks(struct obj *);
extern int use_force_sword(struct obj *);
extern int do_bloodletter(struct obj *);
extern void pyramid_effects(struct obj *, int, int);
extern boolean use_ring_of_wishes(struct obj *);
extern boolean use_candle_of_invocation(struct obj *);
extern void use_magic_whistle(struct obj *);
extern void x_uses_crystal_skull(struct obj **, struct monst *, coord *);
extern int unfixable_trouble_count(boolean);
extern int dotrephination_menu(void);
extern int partial_action(void);
extern int check_partial_action(void);
extern int check_res_engine(struct monst *, int);
extern void add_class(char *, char);
extern boolean set_obj_shape(struct obj *, long);
extern void salve_effect(struct obj *);

/* ### artifact.c ### */

extern boolean CountsAgainstGifts(int);
extern boolean offerable_artifact(struct obj *);
extern void init_artifacts(void);
extern void make_singing_sword_nameable(void);
extern void hack_artifacts(void);
extern void save_artifacts(int);
extern void restore_artifacts(int);
extern int n_artifacts(void);
extern struct artifact * add_artifact(void);
extern const char *artiname(int);
extern int arti_value(struct obj *);
extern void toggle_socketed(struct obj *, struct obj *, boolean);
extern struct obj *mk_randart(struct obj *);
extern struct obj *mk_artifact(struct obj *,aligntyp);
extern struct obj *mk_special(struct obj *);
extern struct obj *mk_vault_special(struct obj *, int);
extern struct obj *mk_lolth_vault_special(struct obj *);
extern struct obj *mk_minor_special(struct obj *);
extern void add_oprop(struct obj *, int);
extern void remove_oprop(struct obj *, int);
extern void add_oprop_list(unsigned long int *, int);
extern boolean check_oprop(struct obj *, int);
extern boolean oprops_match(struct obj *, struct obj *);
extern void copy_oprop_list(struct obj *, unsigned long int *);
extern const char *artifact_name(const char *,short *, int *);
extern boolean art_already_exists(int);
extern boolean art_already_exists_byname(int,const char *);
extern void flag_existance(int, int);
extern void artifact_exists(struct obj *,const char *,boolean);
extern struct obj * mksartifact(int);
extern void get_art_property_list(int *, int, boolean);
extern int nartifact_exist(void);
extern boolean arti_gen_prop(struct obj *, unsigned long);
extern boolean arti_worn_prop(struct obj *, unsigned long);
extern boolean arti_carry_prop(struct obj *, unsigned long);
extern boolean arti_attack_prop(struct obj *, unsigned long);
extern boolean arti_is_prop(struct obj *, unsigned long);
extern boolean confers_luck(struct obj *);
extern boolean arti_digs(struct obj *);
extern boolean arti_poisoned(struct obj *);
extern boolean arti_bright(struct obj *);
extern boolean arti_shattering(struct obj *);
extern boolean arti_disarm(struct obj *);
extern boolean arti_steal(struct obj *);
extern boolean arti_tentRod(struct obj *);
extern boolean arti_threeHead(struct obj *);
extern boolean arti_dluck(struct obj *);
extern boolean arti_dexpl(struct obj *);
extern boolean arti_phasing(struct obj *);
extern boolean arti_mandala(struct obj *);
extern boolean arti_lighten(struct obj *, boolean);
extern boolean arti_chawis(struct obj *, boolean);
extern boolean arti_blindres(struct obj *, boolean);
extern boolean arti_plussev(struct obj *);
extern boolean arti_plusten(struct obj *);
extern boolean arti_socketed(struct obj *);
extern boolean arti_silvered(struct obj *);
extern boolean arti_returning(struct obj *);
extern boolean arti_reflects(struct obj *);
extern int artifact_weight(struct obj *);
extern boolean arti_light(struct obj *);
extern boolean restrict_name(struct obj *,const char *);
extern void set_spear_intrinsic(struct obj *,boolean,long long);
extern void set_artifact_intrinsic(struct obj *,boolean,long long);
extern int touch_artifact(struct obj *,struct monst *, int);
extern int spec_abon(struct obj *,struct monst *, boolean);
extern boolean spec_dbon(struct obj *,struct monst *,int,int*,int*);
extern boolean oproperty_dbon(struct obj *, struct monst *, struct monst *, int, int*, int*);
extern boolean material_dbon(struct obj *, struct monst *, struct monst *, int, int*, int*, int);
extern void mercy_blade_conflict(struct monst *, struct monst *, int, boolean);
extern void mindstealer_conflict(struct monst *, struct monst *);
extern int spec_applies(struct obj *,struct monst *, boolean);
extern void discover_artifact(int);
extern void undiscover_artifact(int);
extern boolean undiscovered_artifact(int);
extern int disp_artifact_discoveries(winid);
extern void otyp_hit(struct monst *,struct monst *,
		     struct obj *,int, int *,int*, int, boolean *, boolean);
extern int special_weapon_hit(struct monst *,struct monst *,
			      struct obj *,struct obj*,int,int*,int*,int,boolean*,boolean);
extern int doinvoke(void);
extern int doparticularinvoke(struct obj *);
extern void arti_speak(struct obj *);
extern boolean artifact_light(struct obj *);
extern int artifact_wet(struct obj *, boolean);
extern long spec_mm(int);
extern long spec_mt(int);
extern long spec_mf(int);
extern long spec_mb(int);
extern long spec_mg(int);
extern long spec_ma(int);
extern long spec_mv(int);
extern long spec_s (int);
extern boolean artifact_has_invprop(struct obj *,uchar);
extern long arti_cost(struct obj *);
extern void arti_poly_contents(struct obj *);
extern struct obj * minor_artifact(struct obj *, char *);
extern void dosymbiotic_equip(void);
extern void do_passive_attacks(void);
extern void living_items(void);
extern int oresist_disintegration(struct obj *);
extern int wrath_target(struct obj *, struct monst *);
extern int goat_weapon_damage_turn(struct obj *);
extern int soth_weapon_damage_turn(struct obj *);
extern int merc_weapon_damage_slice(struct obj *, struct monst *, int);
extern int infinity_s_mirrored_arc_litness(struct obj *);
extern int merge_skies(struct obj **);
extern void do_your_auras(void);

/* ### astar.c ### */
extern boolean path_exists(int, int, int, int, long, int);
/* ### attrib.c ### */

extern boolean adjattrib(int,int,int);
extern void change_luck(schar);
extern int stone_luck(boolean);
extern boolean has_luckitem(void);
extern void set_moreluck(void);
extern int stone_health(void);
extern int stone_energy(void);
extern void gainstr(struct obj *,int);
extern void losestr(int);
extern void restore_attrib(void);
extern void exercise(int,boolean);
extern void exerchk(void);
extern void reset_attribute_clock(void);
extern void init_attr(int);
extern void redist_attr(void);
extern void adjabil(int,int);
extern int newhp(void);
extern int newen(void);
extern int maxhp(int);
extern int maxen(void);
extern double conplus(int);
extern void change_usanity(int, boolean);
extern void change_uinsight(int);
extern boolean check_insight(void);
extern int roll_generic_madness(int);
extern int roll_generic_flat_madness(int);
extern int count_madnesses(void);
extern int roll_madness(long int);
extern int mad_turn(long int);
extern int flat_mad_turn(long int);
extern int mad_monster_turn(struct monst *, long int);
extern void roll_av_frigophobia(void);
extern void roll_frigophobia(void);
extern void give_madness(struct monst *);
extern void you_inflict_madness(struct monst *);
extern void calc_total_maxhp(void);
extern void calc_total_maxen(void);
extern schar acurr(int, struct monst *);
extern schar acurr_player(int);
extern schar acurrstr(int);
extern void adjalign(int);
extern void unSetFightingForm(int);
extern void setFightingForm(int);
extern boolean activeFightingForm(int);
extern boolean activeMentalEdge(int);
extern boolean selectedFightingForm(int);
extern int getFightingFormSkill(int);
extern const char * nameOfMentalEdge(int);
extern const char * nameOfFightingForm(int);
extern void validateLightsaberForm(void);
extern boolean blockedFightingForm(int);
extern boolean blockedMentalEdge(int);
extern int uhp(void);
extern int uhpmax(void);
extern void check_brainlessness(const char *);
extern boolean change_hod(int);
extern boolean change_chokhmah(int);
extern boolean change_gevurah(int);
extern boolean change_keter(int);

/* ### ball.c ### */

extern void ballrelease(boolean);
extern void ballfall(void);
extern void placebc(void);
extern void unplacebc(void);
extern void set_bc(int);
extern void move_bc(int,int,xchar,xchar,xchar,xchar);
extern boolean drag_ball(xchar,xchar,
			 int *,xchar *,xchar *,xchar *,xchar *, boolean *,boolean);
extern void drop_ball(xchar,xchar);
extern void drag_down(void);
extern void bc_sanity_check(void);

/* ### bones.c ### */

extern boolean can_make_bones(void);
extern void savebones(struct obj *);
extern int getbones(void);

/* ### botl.c ### */

extern int force_bot(void);
extern int xlev_to_rank(int);
extern int title_to_mon(const char *,int *,int *);
extern void max_rank_sz(void);
extern long botl_score(void);
extern int describe_level(char *);
extern const char *code_of(short);
extern const char *rank_of(int,short,boolean);
extern void bot(void);
#ifdef DUMP_LOG
extern void bot1str(char *);
extern void bot2str(char *, boolean, int, boolean);
extern void bot3str(char *, boolean, int);
#endif
extern void do_statuseffects(char *, boolean, int, int);
extern long get_status_duration(long long);
extern long long get_status_mask(void);

/* ### cmd.c ### */


extern char randomkey(void);
extern int doGithForm(void);
extern int psionic_pulse(void);
extern int wiz_makemap(void);
extern void reset_occupations(void);
extern void set_occupation(int (*)(void),const char *,int);
extern char pgetchar(void);
extern void pushch(char);
extern void savech(char);
#ifdef WIZARD
extern void add_debug_extended_commands(void);
#endif /* WIZARD */
extern void rhack(char *);
extern void dokeylist(void);
extern char * find_command_key(const char *, char *);
extern int doextlist(void);
extern int extcmd_via_menu(void);
extern int xytod(schar,schar);
extern void dtoxy(coord *,int);
extern int movecmd(char);
extern int getdir(const char *);
extern void confdir(void);
extern int isok(int,int);
extern int get_adjacent_loc(const char *, const char *, xchar, xchar, coord *);
extern const char *click_to_cmd(int,int,int);
extern char readchar(void);
#ifdef WIZARD
extern void sanity_check(void);
#endif
extern void commands_init(void);
extern char* stripspace(char*);
extern void parsebindings(char*);
extern void parseautocomplete(char*,boolean);
extern char txt2key(char*);
extern char* key2txt(char, char*);
extern char* str2txt(char*, char*);
extern char yn_function(const char *, const char *, char);
extern void querytype_add(xchar, char *);
extern void querytype_free(void);
extern char yesno(const char *, boolean);
extern int dotravel(void);

/* ### crown.c ### */

extern const char * crowning_title(void);
extern int gcrownu(void);

/* ### dbridge.c ### */

extern boolean is_pool(int,int, boolean);
extern boolean is_3dwater(int,int);
extern boolean is_lava(int,int);
extern boolean is_ice(int,int);
extern int is_drawbridge_wall(int,int);
extern boolean is_db_wall(int,int);
extern boolean find_drawbridge(int *,int*);
extern boolean create_drawbridge(int,int,int,boolean);
extern void open_drawbridge(int,int);
extern void close_drawbridge(int,int);
extern void destroy_drawbridge(int,int);

/* ### decl.c ### */

extern void decl_init(void);

/* ### detect.c ### */

extern struct obj *o_in(struct obj*,char);
extern struct obj *o_material(struct obj*,unsigned);
extern struct obj *o_artifact(struct obj*);
extern int gold_detect(struct obj *);
extern int food_detect(struct obj *);
extern int object_detect(struct obj *,int);
extern int artifact_detect(struct obj *);
extern int book_detect(boolean);
extern int monster_detect(struct obj *,int);
extern int pet_detect_and_tame(struct obj *);
extern int pet_detect_and_heal(struct obj *);
extern int trap_detect(struct obj *);
extern const char *level_distance(d_level *);
extern int use_crystal_ball(struct obj *);
extern void do_mapping(void);
extern void do_vicinity_map(int,int);
extern void cvt_sdoor_to_door(struct rm *);
extern int findit(void);
extern int openit(void);
extern void find_trap(struct trap *);
extern int dosearch0(int);
extern int dosearch(void);
extern void sokoban_detect(void);
extern int doterrain(void);

/* ### dig.c ### */

extern schar fillholetyp(int, int);
extern boolean is_digging(void);
extern int holetime(void);
extern boolean dig_check(struct monst *, boolean, int, int);
extern void openactualrocktrap(int,int,struct monst *);
extern void openactualdoor(int,int,struct monst *,int);
extern void digactualhole(int,int,struct monst *,int,boolean,boolean);
extern boolean openrocktrap(void);
extern boolean opennewdoor(int,int);
extern boolean opentrapdoor(boolean);
extern boolean dighole(boolean);
extern boolean digfarhole(boolean,int,int,boolean);
extern int use_pick_axe(struct obj *);
extern int use_pick_axe2(struct obj *);
extern boolean mdig_tunnel(struct monst *);
extern void mworldshape(struct monst *, int, int);
extern void watch_dig(struct monst *,xchar,xchar,boolean);
extern void zap_dig(int,int,int);
extern struct obj *bury_an_obj(struct obj *);
extern void bury_objs(int,int);
extern void unearth_objs(int,int);
extern void rot_organic(void *, long);
extern void rot_corpse(void *, long);
extern void dig_up_grave(int, int);
extern void hell_vault_items(int, int, int);
extern void levi_spawn_items(int, int, struct monst *);
extern void break_seal(int, int);
#if 0
extern void bury_monst(struct monst *);
extern void bury_you(void);
extern void unearth_you(void);
extern void escape_tomb(void);
extern void bury_obj(struct obj *);
#endif

/* ### display.c ### */

#ifdef INVISIBLE_OBJECTS
extern struct obj * vobj_at(xchar,xchar);
#endif /* INVISIBLE_OBJECTS */
extern void magic_map_background(xchar,xchar,int);
extern void map_background(xchar,xchar,int);
extern void map_trap(struct trap *,int);
extern int obj_to_glyph(struct obj *);
extern void map_object(struct obj *,int);
extern void map_invisible(xchar,xchar);
extern void unmap_object(int,int);
extern void map_location(int,int,int);
extern void feel_location(xchar,xchar);
extern void echo_location(xchar,xchar);
extern void newsym(int,int);
extern boolean sense_by_scent(struct monst *);
extern void shieldeff(xchar,xchar);
extern void tmp_at(int,int);
extern void swallowed(int);
extern void under_ground(int);
extern void under_water(int);
extern void see_monsters(void);
extern void set_mimic_blocking(void);
extern void see_objects(void);
extern void see_traps(void);
extern void see_altars(void);
extern void curs_on_u(void);
extern int doredraw(void);
extern void docrt(void);
extern void show_glyph(int,int,int);
extern void clear_glyph_buffer(void);
extern void row_refresh(int,int,int);
extern void cls(void);
extern void flush_screen(int);
#ifdef DUMP_LOG
extern void dump_screen(int);
#endif
extern int back_to_glyph(xchar,xchar);
extern int zapdir_to_glyph(int,int,int);
extern int glyph_at(xchar,xchar);
extern void set_wall_state(void);

/* ### do.c ### */

extern int dodrop(void);
extern boolean boulder_hits_pool(struct obj *,int,int,boolean);
extern boolean flooreffects(struct obj *,int,int,const char *);
extern void doaltarobj(struct obj *);
extern boolean canletgo(struct obj *,const char *);
extern void dropx(struct obj *);
extern void dropy(struct obj *);
extern void obj_no_longer_held(struct obj *);
extern boolean obj_summon_out(struct obj *);
extern int doddrop(void);
extern int dodown(void);
extern int doup(void);
extern int acu_asc_items_check(void);
extern void acu_asc_items_warning(int);
#ifdef INSURANCE
extern void save_currentstate(void);
#endif
extern void goto_level(d_level *,boolean,boolean,int);
extern void schedule_goto(d_level *,boolean,boolean,int,
			  const char *,const char *,int,int);
extern void deferred_goto(void);
extern boolean revive_corpse(struct obj *, int);
extern void revive_mon(void *, long);
extern void revive_mon_pickup(void *, long);
extern void moldy_corpse(void *, long);
extern void slimy_corpse(void *, long);
extern void shady_corpse(void *, long);
extern void zombie_corpse(void *, long);
extern void yellow_corpse(void *, long);
extern int donull(void);
extern int dowipe(void);
extern void set_wounded_legs(long,int);
extern void heal_legs(void);
extern int dowait(void);
extern int docome(void);
extern int doattack(void);
extern int dopassive(void);
extern int dodownboy(void);
extern int dosickem(void);
extern int dodropall(void);
extern int drop(struct obj *);

/* ### do_name.c ### */

extern void do_oname(struct obj *);
extern void do_floorname(void);
extern int getpos(coord *,boolean,const char *);
extern struct monst *christen_monst(struct monst *,const char *);
extern int do_mname(void);
extern struct obj *oname(struct obj *,const char *);
extern int ddocall(void);
extern void docall(struct obj *);
extern const char *rndghostname(void);
extern void append_template_desc(struct monst *, char *, boolean, boolean);
extern void adjust_permonst_template_desc(struct permonst *, char *, int);
extern const char *injury_desc_word(struct monst *);
extern char *x_monnam(struct monst *,int,const char *,int,boolean);
extern char *l_monnam(struct monst *);
extern char *mon_nam(struct monst *);
extern const char *sheheit(struct monst *);
extern const char *SheHeIt(struct monst *);
extern const char *hisherits(struct monst *);
extern const char *HisHerIts(struct monst *);
extern const char *himherit(struct monst *);
extern char *noit_mon_nam(struct monst *);
extern char *noit_nohalu_mon_nam(struct monst *);
extern char *Monnam(struct monst *);
extern char *noit_Monnam(struct monst *);
extern char *m_monnam(struct monst *);
extern char *y_monnam(struct monst *);
extern char *Adjmonnam(struct monst *,const char *);
extern char *Amonnam(struct monst *);
extern char *Aptrnam(struct permonst *);
extern char *a_monnam(struct monst *);
extern char *a_ptrnam(struct permonst *);
extern char *mon_nam_too(struct monst *, struct monst *);
extern const char *get_ent_species(int);
extern char *getDrowHouse(long);
extern char *distant_monnam(struct monst *,int,char *);
extern const char *rndmonnam(void);
extern const char *hcolor(const char *);
extern const char *rndcolor(void);
#ifdef REINCARNATION
extern const char *roguename(void);
#endif
extern const char *hliquid(const char *);
extern char *coyotename(struct monst *,char *);

/* ### do_wear.c ### */

extern void off_msg(struct obj *);
extern void set_wear(void);
extern boolean donning(struct obj *);
extern void cancel_don(void);
extern int Armor_on(void);
extern int Armor_off(void);
extern int Armor_gone(void);
extern int Helmet_on(void);
extern int Helmet_off(void);
extern int Gloves_off(void);
extern int Boots_on(void);
extern int Boots_off(void);
extern int Cloak_off(void);
extern int Shield_off(void);
extern int Shirt_on(void);
extern int Shirt_off(void);
extern void Amulet_off(void);
extern void Amulet_on(void);
extern void Ring_on(struct obj *);
extern void Ring_off(struct obj *);
extern void Ring_gone(struct obj *);
extern void Blindf_on(struct obj *);
extern void Blindf_off(struct obj *);
extern int dotakeoff(void);
extern int doremring(void);
extern int cursed(struct obj *);
extern int armoroff(struct obj *);
extern int canwearobj(struct obj *, long long *, boolean);
extern int dowear(void);
extern int doputon(void);
extern int arm_total_bonus(struct obj *);
extern int greatest_erosion(struct obj *);
extern int arm_ac_bonus(struct obj *);
extern int arm_dr_bonus(struct obj *);
extern int base_uac(void);
extern void find_ac(void);
extern int base_udr(void);
extern int base_nat_udr(void);
extern void find_dr(void);
extern int slot_udr(int, struct monst *, int, int);
extern int roll_udr(struct monst *, int);
extern int roll_udr_detail(struct monst *, int, int, int);
extern void glibr(void);
extern void bumbler(void);
extern struct obj *some_armor(struct monst *);
extern void erode_armor(struct monst *,boolean);
extern struct obj *stuck_ring(struct obj *,int);
extern struct obj *cursed_unchanger(void);
extern void reset_remarm(void);
extern int doddoremarm(void);
extern int destroy_arm(struct obj *);
extern int destroy_marm(struct monst *, struct obj *);
extern int claws_destroy_arm(struct obj *);
extern int claws_destroy_marm(struct monst *, struct obj *);
extern int teleport_arm(struct obj *, struct monst *);
extern int teleport_steal_arm(struct monst *, struct obj *);
extern int tent_destroy_arm(struct obj *);
extern void adj_abon(struct obj *,schar);
extern int properties_dr(struct obj *,int,int);
extern void dosymbiotic(struct monst *, struct obj *);
extern void doscorpion(struct monst *, struct obj *);
extern void doliving(struct monst *, struct obj *);
extern void doliving_dragonhead(struct monst *, struct obj *, boolean);
extern void doliving_mad_king(struct monst *, struct obj *, boolean);
extern void doliving_ringed_spear(struct monst *, struct obj *, boolean);
extern void doliving_ringed_armor(struct monst *, struct obj *, boolean);
extern void doliving_ibite_arm(struct monst *, struct obj *, boolean);
extern void doibite_ghosts(struct monst *, struct obj *);
extern void doliving_fallingstar(struct monst *, struct obj *, boolean);
extern void doliving_healing_armor(struct monst *, struct obj *, boolean);
extern void doliving_armor_salve(struct monst *, struct obj *);
extern void dotsmi_theft(struct monst *, struct monst *, struct obj *, struct obj *);

/* ### dog.c ### */

extern void initedog(struct monst *);
extern struct monst *make_familiar(struct obj *,xchar,xchar,boolean);
extern struct monst *makedog(void);
extern void update_mlstmv(void);
extern void losedogs(void);
extern void mon_extract_from_list(struct monst *, struct monst **);
extern void mon_arrive_on_level(struct monst *);
extern void mon_arrive(struct monst *,boolean);
extern void mon_catchup_elapsed_time(struct monst *,long);
extern void keepdogs(boolean, d_level *, boolean);
extern void migrate_to_level(struct monst *,int,xchar,coord *);
extern int dogfood(struct monst *,struct obj *);
extern boolean is_edible_mon(struct monst *,struct obj *);
extern struct monst *tamedog(struct monst *,struct obj *);
extern struct monst *tamedog_core(struct monst *,struct obj *, int);
extern void untame(struct monst *, boolean);
extern struct monst *make_pet_minion(int,int, boolean);
extern void abuse_dog(struct monst *);
extern void wary_dog(struct monst *, boolean);
extern void enough_dogs(int);
extern void vanish_dogs(void);
extern int dog_limit(void);
extern void average_dogs(void);

/* ### dogmove.c ### */

extern boolean could_use_item(struct monst *, struct obj *,boolean);
extern boolean acceptable_pet_target(struct monst *,struct monst *,boolean);
extern boolean betrayed(struct monst *);
extern int dog_nutrition(struct monst *,struct obj *);
extern int dog_eat(struct monst *,struct obj *,int,int,boolean);
extern void give_mon_corpse_intrinsic(struct monst *,int);
extern int monster_eat(struct monst *,struct obj *,int,int,boolean);
extern int dog_move(struct monst *,int);
extern struct obj *DROPPABLES(struct monst *);
extern struct obj *drop_envy(struct monst *);

/* ### dokick.c ### */

extern void kickdmg(struct monst *, boolean);
extern void dive_kick_monster(struct monst *);
extern void bird_kick_monsters(void);
extern void wing_storm_monsters(void);
extern boolean ghitm(struct monst *,struct obj *);
extern void container_impact_dmg(struct obj *);
extern int dotailkick(int, int);
extern int dokick(void);
extern int dokick_core(int, int);
extern boolean ship_object(struct obj *,xchar,xchar,boolean);
extern void obj_delivery(void);
extern schar down_gate(xchar,xchar);
extern void impact_drop(struct obj *,xchar,xchar,xchar,boolean);

/* ### dothrow.c ### */

extern int zap_raygun(struct obj *,int, int);
extern int zap_flamethrower(struct obj *,int, int);
extern void hurtle(int,int,int,boolean,boolean);
extern void mhurtle(struct monst *,int,int,int,boolean);
extern int hero_breaks(struct obj *,xchar,xchar,boolean);
extern int breaks(struct obj *,xchar,xchar);
extern boolean breaktest(struct obj *);
extern boolean walk_path(coord *, coord *, boolean (*)(void *,int,int), void *);
extern boolean hurtle_step(void *, int, int);

/* ### drawing.c ### */
#endif /* !MAKEDEFS_C && !LEV_LEX_C */
extern int def_char_to_objclass(char);
extern int def_char_to_monclass(char);
#if !defined(MAKEDEFS_C) && !defined(LEV_LEX_C)
extern void assign_graphics(glyph_t *,int,int,int);
extern void switch_graphics(int);
#ifdef REINCARNATION
extern void assign_rogue_graphics(boolean);
#endif
extern void assign_utf8graphics_symbol(int, glyph_t);
#ifdef USER_DUNGEONCOLOR
extern void assign_colors(uchar *,int,int,int);
#endif

/* ### dungeon.c ### */

extern void save_dungeon(int,boolean,boolean);
extern void restore_dungeon(int);
extern void insert_branch(branch *,boolean);
extern void init_dungeons(void);
extern s_level *find_level(const char *);
extern s_level *Is_special(d_level *);
extern branch *Is_branchlev(d_level *);
extern d_level *branchlev_other_end(branch *, d_level *);
extern int ledger_no(d_level *);
extern int maxledgerno(void);
extern schar depth(d_level *);
extern int dunlev(d_level *);
extern int dunlevs_in_dungeon(d_level *);
extern int ledger_to_dnum(int);
extern int ledger_to_dlev(int);
extern int deepest_lev_reached(boolean);
extern boolean on_level(d_level *,d_level *);
extern void next_level(boolean);
extern void prev_level(boolean);
extern void u_on_newpos(int,int);
extern void u_on_sstairs(void);
extern void u_on_upstairs(void);
extern void u_on_dnstairs(void);
extern boolean On_stairs(xchar,xchar);
extern void get_level(d_level *,int);
extern boolean Is_botlevel(d_level *);
extern boolean Can_fall_thru(d_level *);
extern boolean Can_dig_down(d_level *);
extern boolean Can_rise_up(int,int,d_level *);
extern boolean In_quest(d_level *);
extern boolean In_outdoors(d_level *);
extern boolean In_cave(d_level *);
extern boolean In_mines(d_level *);
extern boolean In_mines_quest(d_level *);
extern boolean In_neu(d_level *);
extern boolean In_outlands(d_level *);
extern boolean In_lost_cities(d_level *);
extern boolean In_cha(d_level *);
extern boolean In_mithardir_desert(d_level *);
extern boolean In_mithardir_catacombs(d_level *);
extern boolean In_mithardir_terminus(d_level *);
extern boolean In_mithardir_quest(d_level *);
extern boolean In_FF_quest(d_level *);
extern boolean In_mordor_quest(d_level *);
extern boolean In_mordor_forest(d_level *);
extern boolean In_mordor_fields(d_level *);
extern boolean In_mordor_buildings(d_level *);
extern boolean In_mordor_depths(d_level *);
extern boolean In_mordor_borehole(d_level *);
extern boolean In_law(d_level *);
extern branch *dungeon_branch(const char *);
extern boolean at_dgn_entrance(const char *);
extern boolean In_hell(d_level *);
extern boolean In_V_tower(d_level *);
extern boolean On_W_tower_level(d_level *);
extern boolean In_W_tower(int,int,d_level *);
extern void find_hell(d_level *);
extern void goto_hell(boolean,boolean);
extern void assign_level(d_level *,d_level *);
extern void assign_rnd_level(d_level *,d_level *,int);
extern int induced_align(int);
extern boolean Invocation_lev(d_level *);
extern int level_difficulty(void);
extern schar lev_by_name(const char *);
#ifdef WIZARD
extern boolean print_dungeon(boolean,boolean,schar *,int *);
#endif
extern int donamelevel(void);
extern int dooverview(void);
extern void forget_mapseen(int);
extern void rm_mapseen(int);
extern void init_mapseen(d_level *);
extern void recalc_mapseen(void);
extern void recbranch_mapseen(d_level *, d_level *);
extern void remdun_mapseen(int);
extern void dust_storm(void);

/* ### eat.c ### */

extern int unfaint(void);
extern void cprefx(int, boolean, boolean);
extern void cpostfx(int, boolean, boolean, boolean);
extern boolean incantifier_edible(struct obj *);
extern boolean is_edible(struct obj *);
extern void init_uhunger(void);
extern void reset_uhunger(void);
extern boolean satiate_uhunger(void);
extern double get_uhungersizemod(void);
extern int get_uhungermax(void);
extern int get_satiationlimit(void);
extern int Hear_again(void);
extern void reset_eat(void);
extern int doeat(void);
extern void gethungry(void);
extern void morehungry(int);
extern void lesshungry(int);
extern boolean is_fainted(void);
extern void reset_faint(void);
extern void violated_vegetarian(void);
#if 0
extern void sync_hunger(void);
#endif
extern void newuhs(boolean);
extern struct obj *floorfood(const char *,int);
extern void vomit(void);
extern int eaten_stat(int,struct obj *);
extern void food_disappears(struct obj *);
extern void food_substitution(struct obj *,struct obj *);
extern boolean bite_monster(struct monst *);
extern void give_intrinsic(int, long);
extern void fix_petrification(void);
extern int intrinsic_possible(int,struct permonst *);
extern void consume_oeaten(struct obj *,int);
extern int obj_nutrition(struct obj *);
extern boolean maybe_finished_meal(boolean);
extern int ask_turns(struct monst *, int, int);
extern int ask_cp(struct monst *, int);
extern int start_clockwinding(struct obj *,struct monst *, int);

/* ### end.c ### */

extern void mk_mapdump(char *);
extern void mk_dgl_extrainfo(void);
extern char *dump_format_str(char *);
extern void done1(int);
extern int done2(void);
extern void done_in_by(struct monst *);
#endif /* !MAKEDEFS_C && !LEV_LEX_C */
extern void panic(const char *,...) PRINTF_F(1,2);
#if !defined(MAKEDEFS_C) && !defined(LEV_LEX_C)
extern const char* get_alignment_code(void);
extern const char* get_alignment_adj(void);
extern boolean Check_crystal_lifesaving(void);
extern boolean Check_iaso_lifesaving(void);
extern boolean Check_twin_lifesaving(void);
extern boolean Check_ring_lifesaving(void);
extern void done(int);
extern void container_contents(struct obj *,boolean,boolean);
#ifdef DUMP_LOG
extern void dump(char *, char *);
extern void do_containerconts(struct obj *,boolean,boolean,boolean,boolean);
#endif
extern void terminate(int);
extern int num_genocides(void);
extern int num_extinct(void);
extern void list_genocided(int,boolean,boolean);

/* ### engrave.c ### */

extern void bindspirit(int);
extern void blank_all_wards(void);
extern void randomize_all_wards(void);
extern int pick_seal(const char *);
extern int pick_ward(int);
extern void describe_ward(int);
extern int randHaluWard(void);
extern int random_unknown_ward(void);
extern int get_num_wards_added(int, int);
extern char *random_engraving(char *);
extern int random_haluIndex(void);
extern const char *fetchHaluWard(int);
extern void wipeout_text(char *,int,unsigned);
extern boolean can_reach_floor(void);
extern struct engr *get_head_engr(void);
extern const char *surface(int,int);
extern const char *ceiling(int,int);
extern struct engr *engr_at(xchar,xchar);
extern void move_gliders(void);
extern int sengr_at(const char *,xchar,xchar);
extern int ward_at(xchar,xchar);
extern int num_wards_at(xchar,xchar);
extern void u_wipe_engr(int);
extern int decode_wardID(int);
extern int get_wardID(int);
extern int decode_sealID(long);
extern long get_sealID(int);
extern void wipe_engr_at(xchar,xchar,xchar);
extern void read_engr_at(int,int);
extern void make_engr_at(int,int,const char *,long,xchar);
extern void del_engr_at(int,int);
extern void del_ward_at(int,int);
extern void del_engr_ward_at(int,int);
extern int freehand(void);
extern int doengrave(void);
extern int doward(void);
extern int doseal(void);
extern int doengward(void);
extern void save_engravings(int,int);
extern void rest_engravings(int);
extern void del_engr(struct engr *);
extern void del_ward(struct engr *);
extern void del_engr_ward(struct engr *);
extern void rloc_engr(struct engr *);
extern void make_grave(int,int,const char *);
extern boolean allied_faction(int,int);

/* ### enlighten.c ### */

extern int doattributes(void);
extern int doconduct(void);
extern int doenlightenment(void);
extern void udr_enlightenment(void);
extern void signs_mirror(void);
extern void show_enlightenment(int, boolean);
extern void show_conduct(int, boolean);

/* ### exper.c ### */

extern long newuexp(int);
extern int experience(struct monst *,int);
extern int ptrexperience(struct permonst *);
extern void more_experienced(int,int);
extern void lose_experience(int);
extern void losexp(const char *,boolean,boolean,boolean);
extern void newexplevel(void);
extern void binderup(void);
extern void pluslvl(boolean);
extern long rndexp(boolean);

/* ### explode.c ### */

extern void explode(int,int,int,int,int,int,int);
extern void explode_sound(int,int,int,int,int,int,int,int);
extern void explode_pa(int,int,int,int,int,int,int,struct permonst *);
extern void explode_yours(int,int,int,int,int,int,int,boolean);
extern void explode_full(int,int,int,int,int,int,int,int, boolean, struct permonst *);
extern void splash(int,int,int,int,int,int,int,int);
extern long scatter(int, int, int, unsigned int, struct obj *, long *, struct monst *);
extern void splatter_burning_oil(int, int);
extern int adtyp_expl_color(int);
extern void grenade_explode(struct obj *, int, int, boolean, int);
extern void arm_bomb(struct obj *, boolean);

/* ### extralev.c ### */

#ifdef REINCARNATION
extern void makeroguerooms(void);
extern void corr(int,int);
extern void makerogueghost(void);
#endif

/* ### files.c ### */
extern int chmod(const char *path, mode_t mode);
extern char *fname_encode(const char *, char, char *, char *, int);
extern char *fname_decode(char, char *, char *, int);
extern const char *fqname(const char *, int, int);
extern FILE *fopen_datafile(const char *,const char *,int);
extern boolean uptodate(int,const char *);
extern void store_version(int);
extern void set_levelfile_name(char *,int);
extern int create_levelfile(int,char *);
extern int open_levelfile(int,char *);
extern void delete_levelfile(int);
extern void clearlocks(void);
extern int create_bonesfile(d_level*,char **, char *);
extern void commit_bonesfile(d_level *);
extern int open_bonesfile(d_level*,char **);
extern int delete_bonesfile(d_level*);
extern void compress_bonesfile(void);
extern void set_savefile_name(void);
#ifdef INSURANCE
extern void save_savefile_name(int);
#endif
#if defined(WIZARD)
extern void set_error_savefile(void);
#endif
extern int create_savefile(void);
extern int open_savefile(void);
extern int delete_savefile(void);
extern int restore_saved_game(void);
extern void compress(const char *);
extern void uncompress(const char *);
extern boolean lock_file(const char *,int,int);
extern void unlock_file(const char *);
#ifdef USER_SOUNDS
extern boolean can_read_file(const char *);
#endif
extern void read_config_file(const char *);
extern void check_recordfile(const char *);
#if defined(WIZARD)
extern void read_wizkit(void);
#endif
extern void paniclog(const char *, const char *);
extern int validate_prefix_locations(char *);
extern char** get_saved_games(void);
extern void free_saved_games(char**);
#ifdef SELF_RECOVER
extern boolean recover_savefile(void);
#endif
#ifdef HOLD_LOCKFILE_OPEN
extern void really_close(void);
#endif
#ifdef WHEREIS_FILE
extern void touch_whereis(void);
extern void delete_whereis(void);
#endif
extern void livelog_write_string(char *);

/* ### fountain.c ### */

extern void floating_above(const char *);
extern void dogushforth(int);
extern void dryup(xchar,xchar, boolean);
extern void drinkfountain(void);
extern void dipfountain(struct obj *);
extern void breakforge(int, int);
extern void drinkforge(void);
extern void dipforge(struct obj *);
extern void breaksink(int,int);
extern void drinksink(void);

/* ### thoughtglyph.c ### */

extern int count_glyphs(void);
extern long int otyp_to_thought(int);
extern long int mtyp_to_thought(int);
extern boolean maybe_give_thought(long int);
extern void give_thought(long int);
extern void remove_thought(long int);
extern int glyph_sanity(long int);
extern int glyph_insight(long int);
extern boolean active_glyph(long int);
extern boolean was_active_glyph(long int, int, int);
extern void change_glyph_active(long int, boolean);
extern boolean dofreethought(void);

extern void doguidance(struct monst *, int);

/* ### hack.c ### */

extern int max_ints(int,int);
extern int min_ints(int,int);
extern boolean revive_nasty(int,int,const char*);
extern void movobj(struct obj *,xchar,xchar);
extern boolean may_dig(xchar,xchar);
extern boolean may_passwall(xchar,xchar);
extern boolean bad_rock(struct monst *,xchar,xchar);
extern boolean invocation_pos(xchar,xchar);
extern boolean test_move(int, int, int, int, int);
extern boolean adjacent_mon(void);
extern void domove(void);
extern void invocation_message(void);
extern void spoteffects(boolean);
extern char *in_rooms(xchar,xchar,int);
extern boolean in_town(int,int);
extern void check_special_room(boolean);
extern int dopickup(void);
extern void lookaround(void);
extern int monster_nearby(void);
extern void nomul(int, const char *);
extern void maybe_wail(void);
extern void unmul(const char *);
extern void showdmg(int, boolean);
extern void losehp(int,const char *,boolean);
extern void losepw(int);
extern void mdamageu(struct monst *, int);
extern int weight_cap(void);
extern int inv_weight(void);
extern int near_capacity(void);
extern int calc_capacity(int);
extern int max_capacity(void);
extern boolean check_capacity(const char *);
extern int inv_cnt(void);
#ifdef GOLDOBJ
extern long money_cnt(struct obj *);
#endif
extern struct obj * start_all_items(int * );
extern struct obj * next_all_items(int *);
extern void end_all_items(void);

/* ### hacklib.c ### */

extern boolean digit(char);
extern boolean letter(char);
extern char highc(char);
extern char lowc(char);
extern char *lcase(char *);
extern char *upstart(char *);
extern char *mungspaces(char *);
extern char *eos(char *);
extern void sanitizestr(char *);
extern char *strkitten(char *,char);
extern char *s_suffix(const char *);
extern char *ing_suffix(const char *);
extern char *xcrypt(const char *,char *);
extern boolean onlyspace(const char *);
extern char *tabexpand(char *);
extern char *visctrl(char);
extern const char *ordin(int);
extern char *sitoa(int);
extern int sgn(int);
extern int rounddiv(long,int);
extern int dist2(int,int,int,int);
extern int distmin(int,int,int,int);
extern boolean online2(int,int,int,int);
extern boolean pmatch(const char *,const char *);
#ifndef STRNCMPI
extern int strncmpi(const char *,const char *,int);
#endif
#ifndef STRSTRI
extern char *strstri(const char *,const char *);
#endif
extern char *strsubst(char *bp, const char *orig, const char *replacement);
extern boolean fuzzymatch(const char *,const char *,const char *,boolean);
extern void setrandom(void);
extern int getyear(void);
#if 0
extern char *yymmdd(time_t);
#endif
extern long yyyymmdd(time_t);
extern int phase_of_the_moon(void);
extern boolean friday_13th(void);
extern boolean is_june(void);
extern int night(void);
extern int midnight(void);
extern unsigned long int hash(unsigned long int);

/* ### invent.c ### */

extern boolean mergable_traits(struct obj *,struct obj *);
extern void assigninvlet(struct obj *);
extern struct obj *merge_choice(struct obj *,struct obj *);
extern int merged(struct obj **,struct obj **);
extern void addinv_core1(struct obj *);
extern void addinv_core2(struct obj *);
extern struct obj *addinv(struct obj *);
extern struct obj *hold_another_object(struct obj *,const char *,const char *,const char *);
extern void useupall(struct obj *);
extern void useup(struct obj *);
extern void consume_obj_charge(struct obj *,boolean);
extern void freeinv_core(struct obj *);
extern void freeinv(struct obj *);
extern void m_freeinv(struct obj *);
extern void delallobj(int,int);
extern void delobj(struct obj *);
extern struct obj *sobj_at(int,int,int);
extern struct obj *boulder_at(int,int);
extern struct obj *toustefna_at(int,int);
extern struct obj *dreprun_at(int,int);
extern struct obj *veioistafur_at(int,int);
extern struct obj *thjofastafur_at(int,int);
extern struct obj *fear_arti_at(int, int);
extern struct obj *carrying(int);
extern char carrying_applyable_ring(void);
extern char carrying_applyable_amulet(void);
extern char carrying_applyable_gem(void);
extern char carrying_readable_weapon(void);
extern char carrying_readable_tool(void);
extern char carrying_readable_armor(void);
extern struct obj *carrying_art(int);
extern boolean have_lizard(void);
extern struct obj *o_on(unsigned int,struct obj *);
extern boolean obj_here(struct obj *,int,int);
extern boolean wearing_armor(void);
extern boolean is_worn(struct obj *);
extern struct obj *g_at(int,int);
extern struct obj *mkgoldobj(long);
extern struct obj *getobj(const char *,const char *);
extern int ggetobj(const char *,int (*)(struct obj *),int,boolean,unsigned *);
extern void fully_identify_obj(struct obj *);
extern int identify(struct obj *);
extern void identify_pack(int);
extern int askchain(struct obj **,const char *,int,int (*)(struct obj *),
		    int (*)(struct obj *),int,const char *);
extern void prinv(const char *,struct obj *,long);
extern char *xprname(struct obj *,const char *,char,boolean,long,long);
extern int ddoinv(void);
extern void describe_item(struct obj *, int, int, winid *);
extern char display_inventory(const char *,boolean);
#ifdef DUMP_LOG
extern char dump_inventory(const char *,boolean,boolean);
#endif
extern int display_binventory(int,int,boolean);
extern struct obj *display_cinventory(struct obj *);
extern struct obj *display_minventory(struct monst *,int,char *);
extern int dotypeinv(void);
extern const char *dfeature_at(int,int,char *);
extern int look_here(int,boolean);
extern int dolook(void);
extern boolean will_feel_cockatrice(struct obj *,boolean);
extern void feel_cockatrice(struct obj *,boolean);
extern void stackobj(struct obj *);
extern int doprgold(void);
extern int doprwep(void);
extern int doprarm(void);
extern int doprring(void);
extern int dopramulet(void);
extern int doprtool(void);
extern int doprinuse(void);
extern void useupf(struct obj *,long);
extern char *let_to_name(char,boolean,boolean);
extern char *rand_class_name(void);
extern void free_invbuf(void);
extern void reassign(void);
extern int doorganize(void);
extern int count_unpaid(struct obj *);
extern boolean has_object_type(struct obj *, int);
extern int count_buc(struct obj *,int);
extern void carry_obj_effects(struct obj *);
extern const char *currency(long);
extern void silly_thing(const char *,struct obj *);
extern struct obj *getnextgetobj(void);
extern int sortloot_cmp(struct obj *, struct obj *);
extern int mon_healing_penalty(struct monst *);
extern int u_healing_penalty(void);
extern int u_clothing_discomfort(void);
extern struct obj * outermost_armor(struct monst *);
extern struct obj * get_most_complete_puzzle(void);

/* ### ioctl.c ### */

#if defined(UNIX)
extern void getwindowsz(void);
extern void getioctls(void);
extern void setioctls(void);
# ifdef SUSPEND
extern int dosuspend(void);
# endif /* SUSPEND */
#endif /* UNIX */

/* ### light.c ### */

extern void new_light_source(int, void *, int);
extern void del_light_source(struct ls_t *);
extern void do_light_sources(char **);
extern boolean uswallow_indark(void);
extern struct monst *find_mid(unsigned, unsigned);
extern void save_lightsource(struct ls_t *, int, int);
extern void rest_lightsource(int, void *, struct ls_t *, int, boolean);
extern boolean any_light_source(void);
extern void snuff_light_source(int, int);
extern boolean obj_sheds_light(struct obj *);
extern boolean obj_eternal_light(struct obj *);
extern boolean obj_is_burning(struct obj *);
extern boolean litsaber(struct obj *);
extern void obj_split_light_source(struct obj *, struct obj *);
extern void obj_merge_light_sources(struct obj *,struct obj *);
extern int candle_light_range(struct obj *);
#ifdef WIZARD
extern int wiz_light_sources(void);
#endif

/* ### lock.c ### */

extern boolean is_box_picking_context(void);
extern boolean picking_lock(int *,int *);
extern boolean picking_at(int,int);
extern boolean forcing_door(int *, int*);
extern void reset_pick(void);
extern int pick_lock(struct obj **);
extern int doforce(void);
extern boolean boxlock(struct obj *,struct obj *);
extern boolean doorlock(struct obj *,int,int);
extern int doopen(void);
extern int doopen_indir(int,int);
extern int doclose(void);
extern int artifact_door(int,int);


/* ### mail.c ### */

extern void server_admin_msg(void);
#ifdef MAIL
# ifdef UNIX
extern void getmailstatus(void);
# endif
extern void ckmailstatus(void);
extern void readmail(struct obj *);
#endif /* MAIL */
extern void ck_server_admin_msg(void);

/* ### makemon.c ### */

extern void m_initgrp(struct monst *,int,int,int);
extern boolean is_home_elemental(struct permonst *);
extern struct monst *clone_mon(struct monst *,xchar,xchar);
extern struct monst *cloneu(void);
extern struct monst *makemon(struct permonst *,int,int,int);
extern struct monst *makemon_full(struct permonst *,int,int,int,int,int);
extern struct monst *makemon_core(struct permonst *,int,int,int,int,int);
extern boolean create_critters(int,struct permonst *);
extern struct permonst *rndmonst(void);
extern int rndshape(boolean(*)(int));
extern void reset_rndmonst(int);
extern struct permonst *mkclass(char,int);
extern struct permonst *mkzombie(void);
extern int adj_lev(struct permonst *);
extern void m_level_up_intrinsic(struct monst *);
extern struct permonst *grow_up(struct monst *,struct monst *);
extern struct obj * mongets(struct monst *,int,int);
extern void m_initthrow(struct monst *, int, int, int);
extern int golemhp(int);
extern boolean peace_minded(struct permonst *);
extern void set_malign(struct monst *);
extern void set_mimic_sym(struct monst *);
extern void set_curhouse(int);
extern int mbirth_limit(int);
extern void mimic_hit_msg(struct monst *, short);
#ifdef GOLDOBJ
extern void mkmonmoney(struct monst *, long);
#endif
extern int bagotricks(struct obj *, boolean, int *);
extern long init_doll_sales(void);
extern boolean propagate(int, boolean,boolean);
extern boolean mon_can_see_you(struct monst *);
extern boolean mon_can_see_mon(struct monst *, struct monst *);
extern int permonst_max_lev(struct permonst *);
extern int mon_max_lev(struct monst *);

/* ### mapglyph.c ### */

extern void mapglyph(int, glyph_t *, int *, unsigned *, int, int);

/* ### mcastu.c ### */

extern void cursetxt(struct monst *, struct monst *, boolean);
extern int xcasty(struct monst *, struct monst *, struct attack *, int, int);
extern int cast_spell(struct monst *, struct monst *, struct attack *, int, int, int);
extern int needs_familiar(struct monst *);
extern int pick_tannin(struct monst *);

/* ### mextra.c ### */
extern void add_mx(struct monst *, int);
extern void add_mx_l(struct monst *, int, long);
extern void rem_mx(struct monst *, int);
extern void rem_all_mx(struct monst *);
extern void cpy_mx(struct monst *, struct monst *, int);
extern void mov_mx(struct monst *, struct monst *, int);
extern void mov_all_mx(struct monst *, struct monst *);
extern void * get_mx(struct monst *, int);
extern long siz_mx(struct monst *, int);
extern void * bundle_mextra(struct monst *, long *);
extern void unbundle_mextra(struct monst *, void *);
extern void save_mextra(struct monst *, int, int);
extern void rest_mextra(struct monst *, int, boolean);
extern void relink_mx(struct monst *);

/* out of order, but it makes sense to directly follow mextra */
/* ### oextra.c ### */
extern void add_ox(struct obj *, int);
extern void add_ox_l(struct obj *, int, long);
extern void rem_ox(struct obj *, int);
extern void rem_all_ox(struct obj *);
extern void cpy_ox(struct obj *, struct obj *, int);
extern void mov_ox(struct obj *, struct obj *, int);
extern void mov_all_ox(struct obj *, struct obj *);
extern void * get_ox(struct obj *, int);
extern long siz_ox(struct obj *, int);
extern void * bundle_oextra(struct obj *, long *);
extern void unbundle_oextra(struct obj *, void *);
extern void save_oextra(struct obj *, int, int);
extern void rest_oextra(struct obj *, int, boolean);
extern void relink_ox(struct obj *);

/* ### minion.c ### */

extern void msummon(struct monst *, struct permonst *);
extern struct monst * summon_god_minion(int,boolean);
extern struct monst * summon_minion(aligntyp,boolean,boolean,boolean);
extern int demon_talk(struct monst *);
extern long bribe(struct monst *);
extern int dprince(struct permonst *, aligntyp);
extern int dlord(struct permonst *, aligntyp);
extern int llord(void);
extern int nlord(void);
extern int clord(void);
extern int ndemon(aligntyp);
extern int lminion(void);
extern int nminion(void);
extern int cminion(void);

/* ### mklev.c ### */

extern void sort_rooms(void);
extern void add_room(int,int,int,int,boolean,schar,boolean);
extern void add_subroom(struct mkroom *,int,int,int,int,
			boolean,schar,boolean);
extern void makecorridors(void);
extern int add_door(int,int,struct mkroom *);
extern void add_altar(int, int, aligntyp, boolean, int);
extern int random_special_room(void);
extern void mkpoolroom(void);
extern void mkslabroom(void);
extern void mkhellvaultroom(void);
extern void mklev(void);
#ifdef SPECIALIZATION
extern void topologize(struct mkroom *,boolean);
#else
extern void topologize(struct mkroom *);
#endif
extern void place_branch(branch *,xchar,xchar);
extern boolean occupied(xchar,xchar);
extern int okdoor(xchar,xchar);
extern void dodoor(int,int,struct mkroom *);
extern void mktrap(int,int,struct mkroom *,coord*);
extern struct mkroom *room_at(xchar, xchar);
extern void mkstairs(xchar,xchar,char,struct mkroom *);
extern boolean mkfeature(int, int, struct mkroom *);
extern void mkinvokearea(void);
extern void mkHVstatue(int, int, int);

/* ### mkmap.c ### */

void flood_fill_rm(int,int,int,boolean,boolean);
void remove_rooms(int,int,int,int,schar);
void remove_room(unsigned);

/* ### mkmaze.c ### */

extern void wallification(int,int,int,int);
extern void walkfrom(int,int,int);
extern void makemaz(const char *);
extern void mazexy(coord *);
extern void bound_digging(void);
extern struct trap *mkportal(xchar,xchar,int,int);
extern boolean bad_location(xchar,xchar,xchar,xchar,xchar,xchar);
extern void place_lregion(xchar,xchar,xchar,xchar,
			  xchar,xchar,xchar,xchar,
			  xchar,d_level *);
extern void maze_add_rooms(int, int);
extern void maze_add_openings(int);
extern void maze_remove_deadends(int, int);
extern void maze_damage_rooms(int);
extern void maze_touchup_rooms(int);
extern void maze_remove_room(int);
extern void movebubbles(void);
extern void water_friction(void);
extern void save_waterlevel(int,int);
extern void restore_waterlevel(int);
extern const char *waterbody_name(xchar,xchar);

/* ### mkobj.c ### */

extern struct obj *mkobj_at(char,int,int,int);
extern struct obj *mksobj_at(int,int,int,int);
extern struct obj *mkobj(char,int);
extern int rndmonnum(void);
extern struct obj *splitobj(struct obj *,long);
extern struct obj *duplicate_obj(struct obj *);
extern void replace_object(struct obj *,struct obj *);
extern void bill_dummy_object(struct obj *);
extern struct obj *mksobj(int,int);
extern int bcsign(struct obj *);
extern void set_obj_size(struct obj *, int);
extern void set_obj_quan(struct obj *, int);
extern void maybe_set_material(struct obj *, int);
extern void rand_interesting_obj_material(struct obj *);
extern void set_material(struct obj *, int);
extern void set_material_gm(struct obj *, int);
extern int weight(struct obj *);
extern struct obj *mkgold(long,int,int);
extern struct obj *mkgold_core(long,int,int,boolean);
extern struct obj *mkcorpstat(int,struct monst *,struct permonst *,int,int,boolean);
extern struct obj *obj_attach_mid(struct obj *, unsigned);
extern struct obj *save_mtraits(struct obj *, struct monst *);
extern struct monst *get_mtraits(struct obj *, boolean);
extern struct obj *mk_tt_object(int,int,int);
extern struct obj *mk_named_object(int,struct permonst *,int,int,const char *);
extern struct obj *rnd_treefruit_at(int, int);
extern void start_corpse_timeout(struct obj *);
extern void bless(struct obj *);
extern void unbless(struct obj *);
extern void curse(struct obj *);
extern void uncurse(struct obj *);
extern void blessorcurse(struct obj *,int);
extern boolean is_flammable(struct obj *);
extern boolean is_rottable(struct obj *);
extern void place_object(struct obj *,int,int);
extern void remove_object(struct obj *);
extern void uncontain(struct obj *);
extern void discard_minvent(struct monst *);
extern void obj_extract_self(struct obj *);
extern void obj_extract_and_unequip_self(struct obj *);
extern void extract_magic_chest_nobj(struct obj *);
extern void extract_nobj(struct obj *, struct obj **);
extern void extract_nexthere(struct obj *, struct obj **);
extern int add_to_minv(struct monst *, struct obj *);
extern struct obj *add_to_magic_chest(struct obj *, int);
extern struct obj *add_to_container(struct obj *, struct obj *);
extern void add_to_migration(struct obj *);
extern void add_to_buried(struct obj *);
extern void container_weight(struct obj *);
extern void dealloc_obj(struct obj *);
extern int hornoplenty(struct obj *, boolean);
extern void obj_ice_effects(int, int, boolean);
extern long peek_at_iced_corpse_age(struct obj *);
extern void size_and_shape_to_fit(struct obj *, struct monst *);
extern void doMaskStats(struct obj *);
#ifdef WIZARD
extern void obj_sanity_check(void);
#endif

/* ### mkroom.c ### */

extern boolean isspacious(struct mkroom *);
extern void mksepulcher(void);
extern void mkmivault(void);
extern void mkmivaultitem(struct obj *);
extern struct obj * mkjewel(void);
extern struct obj * mklolthvaultitem(void);
extern struct obj * mkhellvaultitem(int);
extern void mkhellvaultitem_cnt(struct obj *, int, boolean);
extern void place_lolth_vaults(void);
extern void place_chaos_forest_features(void);
extern void place_elfquest_forest_features(void);
extern void place_drow_healer_features(void);
extern void place_law_features(void);
extern void place_neutral_features(void);
extern void place_sum_all_features(void);
extern void place_swamp_features(void);
extern struct mkroom * pick_room(boolean, boolean);
extern boolean special_room_requires_full_walls(int);
extern void mkroom(int);
extern void fill_zoo(struct mkroom *);
extern boolean nexttodoor(int,int);
extern boolean has_dnstairs(struct mkroom *);
extern boolean has_upstairs(struct mkroom *);
extern int somex(struct mkroom *);
extern int somey(struct mkroom *);
extern boolean inside_room(struct mkroom *,xchar,xchar);
extern boolean somexy(struct mkroom *,coord *);
extern void mkundead(coord *,boolean,int,long);
extern void mk_yellow_undead(coord *,boolean,int,long);
extern struct permonst *courtmon(int);
extern struct permonst *mivaultmon(void);
extern void save_rooms(int);
extern void rest_rooms(int);
extern struct mkroom *search_special(schar);
extern struct monst *prisoner(int, int, int);

/* ### mon.c ### */

extern int undead_to_corpse(int);
extern int genus(int,int);
extern int pm_to_cham(int);
extern int minliquid(struct monst *);
extern int movemon(void);
extern int meatmetal(struct monst *);
extern int meatgluttony(struct monst *);
extern int meatobj(struct monst *);
extern void mvanishobj(struct monst *, int, int);
extern void mpickgold(struct monst *);
extern boolean mpickstuff(struct monst *,const char *);
extern int curr_mon_load(struct monst *);
extern int max_mon_load(struct monst *);
extern boolean can_carry(struct monst *,struct obj *);
extern int mfndpos(struct monst *,coord *,long *,long);
extern long mm_aggression(struct monst *,struct monst *);
extern long mm_grudge(struct monst *,struct monst *, boolean);
extern boolean monnear(struct monst *,int,int);
extern void dmonsfree(void);
extern int mcalcmove(struct monst*);
extern void mcalcdistress(void);
extern void replmon(struct monst *,struct monst *);
extern void relmon(struct monst *);
extern struct obj *mlifesaver(struct monst *);
extern boolean corpse_chance(struct monst *,struct monst *,boolean);
extern void mondead(struct monst *);
extern void spore_dies(struct monst *);
extern void mondied(struct monst *);
extern void monvanished(struct monst *);
extern void mongone(struct monst *);
extern void monslime(struct monst *);
extern void monstone(struct monst *);
extern void mongolded(struct monst *);
extern void monglassed(struct monst *);
extern void monkilled(struct monst *,const char *,int);
extern void unstuck(struct monst *);
extern boolean m_losehp(struct monst *, int, boolean, char*);
extern void killed(struct monst *);
extern void xkilled(struct monst *,int);
extern void mon_to_stone(struct monst*);
extern void mon_to_gold(struct monst*);
extern void mnexto(struct monst *);
extern void monline(struct monst *);
extern void mofflin(struct monst *);
extern void mofflin_close(struct monst *);
extern boolean mnearto(struct monst *,xchar,xchar,boolean);
extern void poisontell(int);
extern void poisoned(const char *,int,const char *,int, boolean);
extern void m_respond(struct monst *);
extern void m_widegaze(struct monst *);
extern void setmangry(struct monst *);
extern void wakeup(struct monst *, int);
extern void wake_nearby(void);
extern void wake_nearby_noisy(void);
extern void wake_nearto(int,int,int);
extern void wake_nearto_noisy(int,int,int);
extern void seemimic_ambush(struct monst *);
extern void seemimic(struct monst *);
extern void see_passive_mimic(struct monst *);
extern void rescham(void);
extern void restartcham(void);
extern void restore_cham(struct monst *);
extern void mon_animal_list(boolean);
extern int newcham(struct monst *,int,boolean,boolean);
extern boolean pick_animal(int);
extern int select_newcham_form(struct monst *);
extern int can_be_hatched(int);
extern int egg_type_from_parent(int,boolean);
extern boolean dead_species(int,boolean);
extern void kill_genocided_monsters(void);
extern void golemeffects(struct monst *,int,int);
extern void bud_metroid(struct monst *);
extern boolean angry_guards(boolean);
extern void pacify_guards(void);
extern void removeMonster(int,int);
extern int u_sanity_loss(struct monst *);
extern int u_sanity_loss_minor(struct monst *);
extern int u_sanity_loss_nyar(void);
extern int u_sanity_gain(struct monst *);
extern int u_insight_gain(struct monst *);
extern int u_visible_insight(struct monst *);
extern void repair(struct monst *, struct monst *, boolean);
extern void nurse_heal(struct monst *, struct monst *, boolean);
extern void itiner_heal(struct monst *, struct monst *, boolean);
extern void insight_vanish(struct monst *);
extern long timer_duration_remaining(timer_element *);
extern void adjust_timer_duration(timer_element *, long);
extern timer_element * get_timer(timer_element *, short);
extern void abjure_summon(struct monst *, int);
extern void mark_mon_as_summoned(struct monst *, struct monst *, int, int);
extern struct monst * mtyp_on_level(int);
extern struct monst * mtyp_on_migrating(int);

/* ### mondata.c ### */

extern void id_permonst(void);
extern void set_mcan(struct monst *,boolean);
extern void set_mon_data(struct monst *,int);
extern void set_mon_data_core(struct monst *, struct permonst *);
extern void make_horror(struct permonst *, int, int);
extern void give_mintrinsic(struct monst *, long);
extern void remove_mintrinsic(struct monst *, long);
extern void set_faction(struct monst *, int);
extern void set_template(struct monst *, int);
extern boolean mtemplate_accepts_mtyp(int, int);
extern struct permonst * permonst_of(int, int);
extern struct attack *permonst_dmgtype(struct permonst *,int);
extern struct attack *attacktype_fordmg(struct permonst *,int,int);
extern boolean at_least_one_attack(struct monst *);
extern boolean attacktype(struct permonst *,int);
extern boolean mon_attacktype(struct monst *,int);
extern boolean mon_offhand_attack(struct monst *);
extern boolean cantwield(struct monst *);
extern boolean you_cantwield(struct permonst *);
extern int mon_count_attacktype(struct monst *,int);
extern struct attack *mon_get_attacktype(struct monst *,int, struct attack *);
extern boolean noattacks(struct permonst *);
extern int attackindex(struct permonst *,int,int);
extern boolean poly_when_stoned(struct permonst *);
extern boolean poly_when_golded(struct permonst *);
extern boolean resists_drli(struct monst *);
extern boolean resists_oona(struct monst *);
extern boolean resists_fire(struct monst *);
extern boolean resists_cold(struct monst *);
extern boolean resists_sleep(struct monst *);
extern boolean resists_disint(struct monst *);
extern boolean resists_elec(struct monst *);
extern boolean resists_poison(struct monst *);
extern boolean resists_acid(struct monst *);
extern boolean Slime_res(struct monst *);
extern boolean resists_ston(struct monst *);
extern boolean resists_drain(struct monst *);
extern boolean resists_sickness(struct monst *);
extern boolean resists_magm(struct monst *);
extern boolean resists_death(struct monst *);
extern boolean resists_blnd(struct monst *);
extern boolean can_blnd(struct monst *,struct monst *,int,struct obj *);
extern int m_martial_skill(struct permonst *);
extern boolean ranged_attk(struct permonst *);
extern boolean passes_bars(struct monst *);
extern boolean can_track(struct permonst *);
extern boolean sticks(struct monst *);
extern int num_horns(struct permonst *);
extern struct attack *dmgtype_fromattack(struct permonst *,int,int);
extern boolean dmgtype(struct permonst *,int);
extern int max_passive_dmg(struct monst *,struct monst *);
extern int monsndx(struct permonst *);
extern int name_to_mon(const char *);
extern int gender(struct monst *);
extern int pronoun_gender(struct monst *);
extern boolean levl_follower(struct monst *);
extern int little_to_big(int,int);
extern int big_to_little(int);
extern const char *locomotion(struct monst *,const char *);
extern const char *stagger(struct monst *,const char *);
extern const char *on_fire(struct permonst *,struct attack *);
extern const struct permonst *raceptr(struct monst *);
extern int mstrength(struct permonst *);
extern long mon_str(struct monst *);
extern long mon_con(struct monst *);
extern boolean hiddenwidegaze(struct monst *);
extern int hd_size(struct permonst *);
extern void do_ancient_breaths(struct monst *);
extern void do_auras(struct monst *);

/* ### monmove.c ### */

extern boolean scaryElb(struct monst *);
extern boolean scaryLol(struct monst *);
extern boolean scaryItem(struct monst *);
extern boolean scaryYellow(int, struct monst *);
extern boolean scaryHept(int, struct monst *);
extern boolean scaryGorg(int, struct monst *);
extern boolean scaryCircle(int, struct monst *);
extern boolean scaryPent(int, struct monst *);
extern boolean scaryHex(int, struct monst *);
extern boolean scaryHam(int, struct monst *);
extern boolean scarySign(int, struct monst *);
extern boolean scaryEye(int, struct monst *);
extern boolean scaryQueen(int, struct monst *);
extern boolean scaryCat(int, struct monst *);
extern boolean scaryWings(int, struct monst *);
extern boolean scaryTou(struct monst *);
extern boolean scaryDre(struct monst *);
extern boolean scaryVei(struct monst *);
extern boolean scaryThj(struct monst *);
extern boolean itsstuck(struct monst *);
extern boolean mb_trapped(struct monst *);
extern void mon_regen(struct monst *,boolean);
extern void timeout_problems(struct monst *);
extern int dochugw(struct monst *);
extern boolean onscary(int,int,struct monst *);
extern void monflee(struct monst *, int, boolean, boolean);
extern void dracae_eladrin_spawn_equip(struct monst *, int);
extern int dochug(struct monst *);
extern int m_move(struct monst *,int);
extern void break_iron_bars(int, int, boolean);
extern void dissolve_bars(int,int);
extern boolean closed_door(int,int);
extern boolean accessible(int,int);
extern void set_apparxy(struct monst *);
extern boolean can_ooze(struct monst *);
extern void remove_monster(int, int);
extern void held_item_bites(struct monst *, struct obj *);
extern void add_byakhee_to_obj(struct obj *);
extern boolean likes_obj(struct monst *, struct obj *);
extern boolean can_equip(struct monst *, struct obj *);
extern void phantom_scorpions_sting(struct monst *);

/* ### monst.c ### */

extern void monst_init(void);

/* ### monstr.c ### */

extern void monstr_init(void);

/* ### mplayer.c ### */

extern struct monst *mk_mplayer(struct permonst *,xchar, xchar,long);
extern void create_mplayers(int,boolean);
extern void mplayer_talk(struct monst *);


/* ### mthrowu.c ### */

extern int set_bypassDR(int);
extern int set_destroy_thrown(int);
extern boolean mtarget_adjacent(struct monst *);
extern struct monst *mfind_target(struct monst *, boolean, boolean);
extern boolean linedup(xchar,xchar,xchar,xchar);
extern boolean lined_up(struct monst *);
extern int m_pole_range(struct monst *);
extern struct obj *m_carrying(struct monst *,int);
extern struct obj *m_carrying_charged(struct monst *,int);
extern void m_useup(struct monst *,struct obj *);
extern void m_throw(struct monst *,int,int,int,int,int,struct obj *,boolean);
extern boolean hits_bars(struct obj **,int,int,int,int);

/* ### muse.c ### */

extern boolean find_defensive(struct monst *);
extern int use_defensive(struct monst *);
extern int rnd_defensive_item(struct monst *);
extern boolean find_offensive(struct monst *);
extern struct permonst * find_mask(struct monst *);
extern int use_offensive(struct monst *);
extern int rnd_offensive_item(struct monst *);
extern boolean is_attack_wand(int);
extern int rnd_attack_wand(struct monst *);
extern int rnd_attack_potion(struct monst *);
extern int rnd_utility_wand(struct monst *);
extern int rnd_utility_potion(struct monst *);
extern int rnd_good_amulet(void);
extern boolean find_misc(struct monst *);
extern int use_misc(struct monst *);
extern int rnd_misc_item(struct monst *);
extern boolean searches_for_item(struct monst *,struct obj *);
extern boolean mon_reflects(struct monst *,const char *);
extern boolean ureflects(const char *,const char *);
extern boolean munstone(struct monst *,boolean);
extern int mbreak_entanglement(struct monst *);
extern int mescape_entanglement(struct monst *);
extern int entangle_material(struct monst *, int);
extern int entangle_beatitude(struct monst *, int);

/* ### music.c ### */

extern void song_noise(int);
extern void awaken_soldiers(void);
extern void do_earthquake(int, int, int, int,boolean,struct monst *);
extern int do_play_instrument(struct obj *);
extern int pet_can_sing(struct monst *,boolean);
extern int mon_can_counter_sing(struct monst *,boolean);
extern int resist_song(struct monst *, int, struct obj *);

/* ### mutations.c ### */

extern void confer_mutation(int);
extern boolean any_mutation(void);

/* ### nhlan.c ### */
#ifdef LAN_FEATURES
extern void init_lan_features(void);
extern char *lan_username(void);
# ifdef LAN_MAIL
extern boolean lan_mail_check(void);
extern void lan_mail_read(struct obj *);
extern void lan_mail_init(void);
extern void lan_mail_finish(void);
extern void lan_mail_terminate(void);
# endif
#endif

/* ### o_init.c ### */

extern void init_objects(void);
extern void hack_objects(void);
extern int find_sawant(void);
extern int find_gawant(void);
extern int find_pawant(void);
extern int find_riwant(void);
extern int find_gcirclet(void);
extern int find_sring(void);
extern int find_iring(void);
extern int find_good_iring(void);
extern int find_good_dring(void);
extern int find_good_fring(void);
extern int find_good_wring(void);
extern int find_good_aring(void);
extern int find_vhelm(void);
extern int find_skates(void);
extern int find_cboots(void);
extern int find_mboots(void);
extern int find_hboots(void);
extern int find_bboots(void);
extern int find_jboots(void);
extern int find_rboots(void);
extern int find_cope(void);
extern int find_opera_cloak(void);
extern int find_pcloth(void);
extern int find_signet_ring(void);
extern int find_engagement_ring(void);
extern int find_gold_ring(void);
extern int find_silver_ring(void);
extern int find_opal_ring(void);
extern int find_clay_ring(void);
extern int find_coral_ring(void);
extern int find_onyx_ring(void);
extern int find_moonstone_ring(void);
extern int find_jade_ring(void);
extern int find_agate_ring(void);
extern int find_topaz_ring(void);
extern int find_sapphire_ring(void);
extern int find_ruby_ring(void);
extern int find_pearl_ring(void);
extern int find_ivory_ring(void);
extern int find_emerald_ring(void);
extern int find_droven_ring(void);
extern boolean isEngrRing(int);
extern boolean isSignetRing(int);
extern int find_golden_potion(void);
extern int find_cloth_book(void);
extern int find_leather_book(void);
extern int find_bronze_book(void);
extern int find_silver_book(void);
extern int find_gold_book(void);
extern int matWand(int, int);
extern int find_ogloves(void);
extern int find_tgloves(void);
extern int find_pgloves(void);
extern int find_fgloves(void);
extern int find_rgloves(void);
extern void oinit(void);
extern void savenames(int,int);
extern void restnames(int);
extern void discover_object(int,boolean,boolean);
extern void undiscover_object(int);
extern int dodiscovered(void);
extern void set_isamusei_color(struct obj *);
extern void set_object_color(struct obj *);
extern int object_color(struct obj *);
extern void set_submat(struct obj *, int);
extern void fix_object(struct obj *);

/* ### objects.c ### */

extern void objects_init(void);

/* ### objnam.c ### */

extern int nth_ring_text(int, char *, size_t);
extern const char *lightsaber_colorText(struct obj *);
extern int lightsaber_colorCLR(struct obj *);
extern char *lightsaber_hiltText(struct obj *);
extern char *beamsword_hiltText(struct obj *);
extern int random_saber_hilt(void);
extern int random_beam_hilt(void);
extern char *obj_typename(int);
extern char *obj_descname(struct obj *);
extern char *simple_typename(int);
extern char *artiadjusted_objnam(char *, int);
extern boolean obj_is_pname(struct obj *);
extern char *distant_name(struct obj *,char *(*)(struct obj *));
extern char *fruitname(boolean);
extern char *xname(struct obj *);
extern const char *material_name(struct obj *, boolean);
extern const char *default_material_name(int, boolean);
extern char *mshot_xname(struct obj *);
extern boolean the_unique_obj(struct obj *obj);
extern char *doname(struct obj *);
extern char *doname_with_price(struct obj *);
extern boolean not_fully_identified(struct obj *);
extern char *corpse_xname(struct obj *,boolean);
extern char *cxname(struct obj *);
extern char *xname_bland(struct obj *);
extern char *cxname2(struct obj *);
extern char *killer_xname(struct obj *);
extern const char *singular(struct obj *,char *(*)(struct obj *));
extern char *an(const char *);
extern char *An(const char *);
extern char *The(const char *);
extern char *the(const char *);
extern char *aobjnam(struct obj *,const char *);
extern char *Tobjnam(struct obj *,const char *);
extern char *otense(struct obj *,const char *);
extern char *vtense(const char *,const char *);
extern char *Doname2(struct obj *);
extern char *yname(struct obj *);
extern char *Yname2(struct obj *);
extern char *ysimple_name(struct obj *);
extern char *Ysimple_name2(struct obj *);
extern char *makeplural(const char *);
extern char *makesingular(const char *);
extern struct obj *readobjnam(char *,int *,int);
extern int rnd_class(int,int);
extern const char *cloak_simple_name(struct obj *);
extern const char *mimic_obj_name(struct monst *);

/* ### options.c ### */

extern boolean match_optname(const char *,const char *,int,boolean);
extern void initoptions(void);
extern void parseoptions(char *,boolean,boolean);
extern int doset(void);
extern int dotogglepickup(void);
extern void option_help(void);
extern void next_opt(winid,const char *);
extern int fruitadd(char *);
extern int choose_classes_menu(const char *,int,boolean,char *,char *);
extern void add_menu_cmd_alias(char, char);
extern char map_menu_cmd(char);
extern void assign_warnings(uchar *);
extern char *nh_getenv(const char *);
extern void set_duplicate_opt_detection(int);
extern void set_wc_option_mod_status(unsigned long, int);
extern void set_wc2_option_mod_status(unsigned long, int);
extern void set_option_mod_status(const char *,int);
extern int add_autopickup_exception(const char *);
extern void free_autopickup_exceptions(void);
extern boolean add_menu_coloring(char *);
extern boolean parse_monster_color(char *);
extern boolean parse_monster_template(char *);
extern int parse_codepoint(char *);
extern boolean parse_monster_symbol(const char *);
extern boolean parse_object_symbol(const char *);
extern boolean parse_symbol(const char *);

/* ### pager.c ### */

extern char *flag_to_word(unsigned long, int);
extern int dowhatis(void);
extern int doquickwhatis(void);
extern int doidtrap(void);
extern int dowhatdoes(void);
extern boolean object_from_map(int,int,int,struct obj **);
extern const char *rndobjnam(void);
extern char *dowhatdoes_core(char, char *);
extern char *get_description_of_attack_type(int);
extern char *get_description_of_damage_type(int);
extern int dohelp(void);
extern int dohistory(void);
extern boolean checkfile(char *,struct permonst *,boolean,boolean, winid*);
extern char *do_look_letter(glyph_t, boolean, boolean, boolean, coord, char *, const char *);

/* ### pickup.c ### */

extern void observe_quantum_cat(struct obj *, boolean);
extern void open_coffin(struct obj *, boolean);
extern int swap_point(struct obj *);
extern void open_sarcophagus(struct obj *, boolean);
extern void open_crazy_box(struct obj *, boolean);
extern boolean open_madstuff_box(struct obj *, boolean);
extern void open_giants_sack(struct obj *, boolean);
extern void kill_giants_sack(struct obj *);
#ifdef GOLDOBJ
extern int collect_obj_classes(char *,struct obj *,boolean,boolean (*)(struct obj *), int *);
#else
extern int collect_obj_classes(char *,struct obj *,boolean,boolean,boolean (*)(struct obj *), int *);
#endif
extern void add_valid_menu_class(int);
extern boolean allow_all(struct obj *);
extern boolean allow_category(struct obj *);
extern boolean is_worn_by_type(struct obj *);
extern int pickup(int);
extern int pickup_object(struct obj *, long, boolean);
extern int query_category(const char *, struct obj *, int, menu_item **, int);
extern int query_objlist(const char *, struct obj *, int, menu_item **, int, boolean (*)(struct obj *));
extern struct obj *pick_obj(struct obj *);
extern int encumber_msg(void);
extern int doloot(void);
extern int dotip(void);
extern int dopetequip(void);
extern int use_container(struct obj *,int);
extern int use_massblaster(struct obj *);
extern int loot_mon(struct monst *,int *,boolean *);
extern const char *safe_qbuf(const char *,unsigned, const char *,const char *,const char *);
extern boolean is_autopickup_exception(struct obj *, boolean);

/* ### pline.c ### */

extern void msgpline_add(xchar, char *);
extern void msgpline_free(void);
extern void pline(const char *,...) PRINTF_F(1,2);
extern void Norep(const char *,...) PRINTF_F(1,2);
extern void free_youbuf(void);
extern void You(const char *,...) PRINTF_F(1,2);
extern void Your(const char *,...) PRINTF_F(1,2);
extern void You_feel(const char *,...) PRINTF_F(1,2);
extern void You_cant(const char *,...) PRINTF_F(1,2);
extern void You_hear(const char *,...) PRINTF_F(1,2);
extern void pline_The(const char *,...) PRINTF_F(1,2);
extern void There(const char *,...) PRINTF_F(1,2);
extern void verbalize(const char *,...) PRINTF_F(1,2);
extern void raw_printf(const char *,...) PRINTF_F(1,2);
extern void impossible(const char *,...) PRINTF_F(1,2);
extern const char *align_str(aligntyp);
extern const char *align_str_proper(aligntyp);
extern void mdrslotline(struct monst *);
extern void mstatusline(struct monst *);
extern void ustatusline(void);
extern void self_invis_message(void);
extern const char *piratesay(const char *);

/* ### polyself.c ### */

extern void init_uasmon(void);
extern void set_uasmon(void);
extern void change_sex(void);
extern void polyself(boolean);
extern int polymon(int);
extern void rehumanize(void);
extern int dobreathe(struct permonst *);
extern int domakewhisperer(void);
extern int dokiai(void);
extern int doelementalbreath(void);
extern int dospit(void);
extern int doremove(void);
extern int dospinweb(void);
extern int dosummon(void);
extern int dodemonpet(void);
extern int dovampminion(void);
extern int dotinker(void);
extern int dogaze(void);
extern int dohide(void);
extern int domindblast(void);
extern int dodarken(void);
extern int doandroid(void);
extern int doclockspeed(void);
extern void break_armor(void);
extern void drop_weapon(int);
extern int dowords(int);
extern void skinback(boolean);
extern const char *mbodypart(struct monst *,int);
extern const char *body_part(int);
extern int poly_gender(void);
extern void ugolemeffects(int,int);

/* ### potion.c ### */

extern void set_itimeout(long long *,long);
extern void incr_itimeout(long long *,long);
extern long itimeout_incr(long,long);
extern void make_confused(long,boolean);
extern void make_stunned(long,boolean);
extern void make_doubtful(long,boolean);
extern void make_invulnerable(long,boolean);
extern void make_blinded(long,boolean);
extern void make_sick(long, const char *, boolean,int);
extern void make_vomiting(long,boolean);
extern boolean make_hallucinated(long,boolean,long long);
extern int dodrink(void);
extern int dopotion(struct obj *, boolean);
extern int peffects(struct obj *, boolean);
extern void healup(int,int,boolean,boolean);
extern void strange_feeling(struct obj *,const char *);
extern void potionhit(struct monst *,struct obj *,boolean);
extern void potionbreathe(struct obj *);
extern boolean get_wet(struct obj *, boolean);
extern int dodip(void);
extern void djinni_from_bottle(struct obj *);
extern struct monst *split_mon(struct monst *,struct monst *);
extern const char *bottlename(void);

/* ### pray.c ### */
extern void godvoice(int,const char*);
extern void gods_angry(int);
extern void gods_upset(int);
extern void angrygods(int);
extern boolean maybe_god_gives_gift(void);
extern void pacify_goat_faction(void);
extern int dosacrifice(void);
extern void at_your_feet(const char *);
extern boolean can_pray(boolean);
extern int dopray(void);
extern const char *u_gname(void);
extern int doturn(void);
extern int mon_doturn(struct monst *);
extern const char *a_gname(void);
extern const char *a_gname_at(xchar x,xchar y);
extern const char *align_gname(aligntyp);
extern const char *gtitle(int);
extern void altar_wrath(int,int);
extern int candle_on_altar(struct obj *);
extern void goat_eat(struct obj *, int);
extern void flame_consume(struct monst *, struct obj *, boolean);
extern void yog_credit(int);
extern void bokrug_offer(struct obj *);
extern boolean goat_mouth_at(int, int);
extern boolean bokrug_idol_at(int, int);
extern int commune_with_goat(void);
extern int commune_with_silver_flame(void);
extern int commune_with_yog(void);
extern void init_gods(void);
extern void save_gods(int);
extern void restore_gods(int);
extern aligntyp galign(int);
extern int gholiness(int);
extern int align_to_god(aligntyp);
extern const char * godname_full(int);
extern const char * godname(int);
extern int god_faction(int);
extern int altaralign_to_godnum(int);
extern const int * god_minions(int);
extern struct monst * god_priest(int, int, int, int);
extern int god_at_altar(int, int);
extern boolean gods_are_friendly(int, int);
extern boolean god_accepts_you(int);

/* ### priest.c ### */

extern coord * shrine_pos(int);
extern aligntyp temple_alignment(int);
extern int move_special(struct monst *,boolean,schar,boolean,boolean,
			xchar,xchar,xchar,xchar);
extern char temple_occupied(char *);
extern int pri_move(struct monst *);
extern void priestini(d_level *,struct mkroom *,int,int,int);
extern char *priestname(struct monst *,char *);
extern boolean p_coaligned(struct monst *);
extern struct monst *findpriest(char);
extern void intemple(int);
extern void priest_talk(struct monst *);
extern struct monst *mk_roamer(struct permonst *,aligntyp,
			       xchar,xchar,boolean);
extern void reset_hostility(struct monst *);
extern boolean in_your_sanctuary(struct monst *,xchar,xchar);
extern void ghod_hitsu(struct monst *);
extern void angry_priest(void);
extern void clearpriests(void);

/* ### projectile.c ### */

extern void interrupt_multishot(struct obj *, struct obj *);
extern int projectile(struct monst *, struct obj *, void *, int, int, int, int, int, int, int, boolean, boolean, boolean);
extern void do_digging_impact(struct monst *, struct obj *, int, int);
extern void hitfloor2(struct monst *, struct obj **, struct obj *, boolean, boolean);
extern boolean xbreathey(struct monst *, struct attack *, int, int);
extern boolean xspity(struct monst *, struct attack *, int, int);
extern boolean xfirey(struct monst *, struct attack *, int, int, int);
extern boolean m_online(struct monst *, struct monst *, int, int, boolean, boolean);
extern boolean m_insplash(struct monst *, struct monst *, int, int, boolean);
extern boolean mdofire(struct monst *, struct monst *, int, int);
extern boolean umetgaze(struct monst *);
extern int dothrow(void);
extern int dofire(void);
extern int mthrow(struct monst *, struct obj *, struct obj *, int, int, boolean);
extern void return_ammo(void *, long);

/* ### quest.c ### */

extern void onquest(void);
extern void nemdead(void);
extern void artitouch(void);
extern boolean ok_to_quest(void);
extern void leader_speaks(struct monst *);
extern void nemesis_speaks(void);
extern void quest_chat(struct monst *);
extern void quest_talk(struct monst *);
extern void quest_stat_check(struct monst *);
extern void finish_quest(struct obj *);
extern void turn_stag(void);

/* ### questpgr.c ### */

extern void load_qtlist(void);
extern void unload_qtlist(void);
extern short quest_info(int);
extern const char *ldrname(void);
extern boolean is_quest_artifact(struct obj*);
extern boolean is_primary_quest_artifact(struct obj*);
extern void com_pager(int);
extern void qt_pager(int);
extern struct permonst *qt_montype(void);
extern struct permonst *icecaves_montype(void);
extern struct permonst *blackforest_montype(void);
extern struct permonst *dismalswamp_montype(void);
extern struct permonst *archipelago_montype(void);
extern struct permonst *chaos_montype(void);
extern struct permonst *chaos2_montype(void);
extern struct permonst *chaos3_montype(void);
extern struct permonst *ford_montype(int);
extern struct permonst *neutral_montype(void);
extern struct permonst *law_montype(void);

/* ### random.c ### */

#if defined(RANDOM)
extern void srandom(unsigned);
extern char *initstate(unsigned,char *,int);
extern char *setstate(char *);
extern long random(void);
#endif /* RANDOM */

/* ### read.c ### */

extern int doread(void);
extern boolean is_chargeable(struct obj *);
extern int recharge(struct obj *,int);
extern void forget(int);
extern void forget_objects(int);
extern void forget_levels(int);
extern void forget_traps(void);
extern void forget_map(int);
extern int seffects(struct obj *);
extern void litroom(boolean,struct obj *);
extern void set_lit(int,int,void *);
extern void do_genocide(int);
extern void punish(struct obj *);
extern void unpunish(void);
extern boolean cant_create(int *, boolean);
#ifdef WIZARD
extern int wiz_kill_all(void);
extern struct monst * create_particular(int, int, unsigned long, int, int, unsigned long, unsigned long, int, char *);
#endif

/* ### rect.c ### */

extern void init_rect(void);
extern NhRect *get_rect(NhRect *);
extern NhRect *rnd_rect(void);
extern void remove_rect(NhRect *);
extern void add_rect(NhRect *);
extern void split_rects(NhRect *,NhRect *);

/* ## region.c ### */
extern void clear_regions(void);
extern void run_regions(void);
extern boolean In_fog_cloud(struct monst *);
extern boolean check_region(xchar, xchar, int);
extern boolean in_out_region(xchar,xchar);
extern boolean m_in_out_region(struct monst *,xchar,xchar);
extern void update_player_regions(void);
extern void update_monster_region(struct monst *);
extern NhRegion *visible_region_at(xchar,xchar);
extern void show_region(NhRegion*, xchar, xchar);
extern void save_regions(int,int);
extern void rest_regions(int,boolean);
extern NhRegion* create_generic_cloud(xchar, xchar, int, struct region_arg *, boolean);
extern NhRegion* create_gas_cloud(xchar, xchar, int, int, boolean);
extern NhRegion* create_fog_cloud(xchar, xchar, int, int, boolean);
extern NhRegion* create_dust_cloud(xchar, xchar, int, int);

/* ### restore.c ### */

extern void inven_inuse(boolean);
extern int dorecover(int);
extern void trickery(char *);
extern void getlev(int,int,int,boolean);
extern void minit(void);
extern boolean lookup_id_mapping(unsigned, unsigned *);
#ifdef ZEROCOMP
extern int mread(int,void *,unsigned int);
#else
extern void mread(int,void *,unsigned int);
#endif

/* ### rip.c ### */

extern void genl_outrip(winid,int);

/* ### rnd.c ### */

extern void check_reseed(void);
extern int rn2(int);
extern int rnl(int);
extern int rnd(int);
extern int d(int,int);
extern int exploding_d(int,int,int);
extern int lucky_exploding_d(int,int,int);
extern int unlucky_exploding_d(int,int,int);
extern int rne(int);
extern int rnz(int);

/* ### role.c ### */

extern boolean validrole(int);
extern boolean validrace(int, int);
extern boolean validgend(int, int, int);
extern boolean validalign(int, int, int);
extern boolean validspecies(int, int, int, int);
extern boolean validdescendant(int);
extern int randrole(int);
extern int randrace(int);
extern int randgend(int, int);
extern int randalign(int, int);
extern int randspecies(int, int, int);
extern int str2role(char *);
extern struct Role *pm2role(int);
extern int str2race(char *);
extern int str2gend(char *);
extern int str2align(char *);
extern int str2species(char *);
extern boolean ok_role(int, int, int, int);
extern int pick_role(int, int, int, int);
extern boolean ok_race(int, int, int, int);
extern int pick_race(int, int, int, int);
extern boolean ok_gend(int, int, int, int);
extern int pick_gend(int, int, int, int);
extern boolean ok_align(int, int, int, int);
extern int pick_align(int, int, int, int);
extern int pick_species(int, int, int, int);
extern void role_init(int);
extern void rigid_role_checks(void);
extern void plnamesuffix(void);
extern const char *Hello(struct monst *);
extern const char *Goodbye(void);
extern char *build_plselection_prompt(char *, int, int, int, int, int, int);
extern char *root_plselection_prompt(char *, int, int, int, int, int, int);
extern void add_imp_record(long);
extern void give_quest_trophy(void);
extern void give_ascension_trophy(void);
extern void give_lamashtu_trophy(void);
extern void give_baalphegor_trophy(void);
extern void give_castle_trophy(void);
extern void give_ugwish_trophy(void);
extern void give_law_trophy(void);
extern void give_angel_vault_trophy(void);
extern void give_ancient_vault_trophy(void);
extern void give_tannin_vault_trophy(void);
extern void give_devil_vault_trophy(void);
extern void give_demon_vault_trophy(void);
extern void give_hell_vault_trophy(int);
extern void give_neutral_trophy(void);
extern void give_chaos_temple_trophy(void);
extern void check_mithardir_trophy(void);
extern void give_mordor_trophy(void);
extern void check_illumian_trophy(void);
extern void give_rescue_trophy(void);
extern void check_loadout_trophy(void);
extern void give_nightmare_hunter_trophy(void);
extern void check_madman_trophy(void);
extern void check_drunkard_trophy(void);
extern void give_bokrug_trophy(void);

/* ### rumors.c ### */

extern char *getrumor(int,char *, boolean);
extern void outrumor(int,int);
extern void outgmaster(void);
extern void outoracle(boolean, boolean);
extern void save_oracles(int,int);
extern void restore_oracles(int);
extern int doconsult(struct monst *);

/* ### save.c ### */

extern int dosave(void);
#if defined(UNIX)
extern void hangup(int);
#endif
extern int dosave0(void);
#ifdef INSURANCE
extern void savestateinlock(void);
#endif
extern void savelev(int,int,int);
extern void bufon(int);
extern void bufoff(int);
extern void bflush(int);
extern void bwrite(int,void *,unsigned int);
extern void bclose(int);
extern void savefruitchn(int,int);
extern void free_dungeons(void);
extern void freedynamicdata(void);
extern boolean dahlverNarVis(void);

/* ### seduce.c ### */

extern int could_seduce(struct monst *, struct monst *, struct attack *);
#ifdef SEDUCE
extern int doseduce(struct monst *);
extern int dosflseduce(struct monst *);
extern int dopaleseduce(struct monst *);
extern int dotent(struct monst *, int);
extern boolean msteal_m(struct monst *, struct monst *, struct attack *, int *);
#endif

/* ### shk.c ### */

#ifdef GOLDOBJ
extern long money2mon(struct monst *, long);
extern long money2none(long);
extern void money2u(struct monst *, long);
#endif
extern char *shkname(struct monst *);
extern void shkgone(struct monst *);
extern void set_residency(struct monst *,boolean);
extern void replshk(struct monst *);
extern void restshk(struct monst *,boolean);
extern char inside_shop(xchar,xchar);
extern void u_left_shop(char *,boolean);
extern void remote_burglary(struct obj *);
extern void u_entered_shop(char *);
extern boolean same_price(struct obj *,struct obj *);
extern void shopper_financial_report(void);
extern int inhishop(struct monst *);
extern struct monst *shop_keeper(char);
extern boolean tended_shop(struct mkroom *);
extern void delete_contents(struct obj *);
extern void obfree(struct obj *,struct obj *);
extern void home_shk(struct monst *,boolean);
extern void pacify_shk(struct monst *);
extern void make_happy_shk(struct monst *,boolean);
extern void hot_pursuit(struct monst *);
extern void make_angry_shk(struct monst *,xchar,xchar);
extern long get_cost_of_shop_item(struct obj *);
extern int dopay(void);
extern boolean paybill(int);
extern void finish_paybill(void);
extern struct obj *find_oid(unsigned);
extern long contained_cost(struct obj *,struct monst *,long,boolean, boolean);
extern long contained_gold(struct obj *);
extern void picked_container(struct obj *);
extern long unpaid_cost(struct obj *);
extern void addtobill(struct obj *,boolean,boolean,boolean);
extern void splitbill(struct obj *,struct obj *);
extern void subfrombill(struct obj *,struct monst *);
extern long stolen_value(struct obj *,xchar,xchar,boolean,boolean);
extern void sellobj_state(int);
extern void sellobj(struct obj *,xchar,xchar);
extern void setpaid(struct monst *);
extern int doinvbill(int);
extern long getprice(struct obj *, boolean, boolean);
extern struct monst *shkcatch(struct obj *,xchar,xchar);
extern void add_damage(xchar,xchar,long);
extern int repair_damage(struct monst *,struct damage *,boolean);
extern int shk_move(struct monst *);
extern void after_shk_move(struct monst *);
extern boolean is_fshk(struct monst *);
extern void shopdig(int);
extern void pay_for_damage(const char *,boolean);
extern boolean costly_spot(xchar,xchar);
extern struct obj *shop_object(xchar,xchar);
extern void price_quote(struct obj *);
extern void shk_chat(struct monst *);
extern void check_unpaid_usage(struct obj *,boolean);
extern void check_unpaid(struct obj *);
extern void costly_gold(xchar,xchar,long);
extern boolean block_door(xchar,xchar);
extern boolean block_entry(xchar,xchar);
extern char *shk_mons(char *,struct obj *, struct monst *);
extern char *Shk_Mons(char *,struct obj *, struct monst *);
extern char *shk_your(char *,struct obj *);
extern char *Shk_Your(char *,struct obj *);
extern void makeketer(coord *);
extern int countFarSigns(struct monst *);
extern int countCloseSigns(struct monst *);
extern void smithy_services(struct monst *);
extern void initialize_smith_stocks(struct monst *);

/* ### shknam.c ### */

extern void stock_room(int,struct mkroom *);
extern boolean saleable(struct monst *,struct obj *);
extern int get_special_shop_item(int);
extern int get_shop_item(int);

/* ### sit.c ### */

extern void take_gold(void);
extern int dosit(void);
extern int sit_bergonic(struct obj *);
extern boolean rndcurse(void);
extern boolean mrndcurse(struct monst *);
extern void attrcurse(void);

/* ### sounds.c ### */

extern void dosounds(void);
extern const char *growl_sound(struct monst *);
extern const char *tat_to_name(int);
extern void growl(struct monst *);
extern void yelp(struct monst *);
extern void whimper(struct monst *);
extern void beg(struct monst *);
extern void m_command(struct monst *);
extern int dotalk(void);
extern int dochat(boolean, int, int, int);
extern int binder_nearvoid_slots(void);
extern int * spirit_props(int);
extern void councilspirit(int);
extern void gnosisspirit(int);
extern void scatter_seals(void);
extern int P_MAX_SKILL(int);
extern int P_MAX_SKILL_CORE(int, boolean);
extern int P_SKILL(int);
extern int P_SKILL_CORE(int, boolean);
extern int P_RESTRICTED(int);
extern boolean spiritSkill(int);
extern boolean roleSkill(int);
extern int domonnoise(struct monst *, boolean);
#ifdef USER_SOUNDS
extern int add_sound_mapping(const char *);
extern void play_sound_for_message(const char *);
#endif
extern boolean doreinforce_binding(void);

/* ### sys/msdos/sound.c ### */


/* ### sp_lev.c ### */

extern boolean check_room(xchar *,xchar *,xchar *,xchar *,boolean);
extern boolean create_room(xchar,xchar,xchar,xchar,
			   xchar,xchar,xchar,xchar);
extern void create_secret_door(struct mkroom *,xchar);
extern boolean dig_corridor(coord *,coord *,boolean,schar,schar);
extern void fill_room(struct mkroom *,boolean);
extern boolean load_special(const char *);

/* ### spell.c ### */

extern int study_book(struct obj *);
extern int further_study(int);
extern int spellid_to_spellno(int);
extern boolean spell_maintained(int);
extern void spell_maintain(int);
extern void spell_unmaintain(int);
extern void run_maintained_spells(void);
extern void book_disappears(struct obj *);
extern void book_substitution(struct obj *,struct obj *);
extern void age_spells(void);
extern void damage_spells(int);
extern int docast(void);
extern boolean tt_findadjacent(coord *, struct monst *);
extern int spiritDsize(void);
extern int dospirit(void);
extern int spell_skill_from_adtype(int);
extern int spell_adtype(int);
extern const char *spelltypemnemonic(int);
extern int spell_skilltype(int);
extern int spiriteffects(int,boolean);
extern int nudzirath_hit_pile(struct obj *, struct obj *);
extern int nudzirath_hit_mon(struct monst *, struct obj *);
extern void nudzirath_shatter(struct obj *, int, int);
extern int spellenergy(int);
extern int spelleffects(int,boolean,int);
extern int wordeffects(int);
extern void losespells(int);
extern int throwgaze(void);
extern int dovspell(void);
extern int base_casting_stat(void);
extern int percent_success(int);
extern void initialspell(struct obj *);
extern void initialforgotwizardspells(int);
extern void initialforgotpriestspells(int);
extern void initialforgotspell(int);
extern void initialward(struct obj *);
extern void set_spirit_powers(long);
extern int reorder_spirit_powers(void);
extern void dopseudonatural(void);
extern void dodestruction(void);
extern void domindblast_strong(void);
extern boolean doreinforce_spell(void);
extern void update_externally_granted_spells(void);
extern void expel_summons(void);

/* ### steal.c ### */

#ifdef GOLDOBJ
extern long somegold(long);
#else
extern long somegold(void);
#endif
extern void stealgold(struct monst *);
extern void remove_worn_item(struct obj *,boolean);
extern int steal(struct monst *, char *,int,int);
extern int mpickobj(struct monst *,struct obj *);
extern void stealamulet(struct monst *);
extern void stealquestart(struct monst *);
extern void mdrop_special_objs(struct monst *);
extern void relobj(struct monst *,int,boolean);
extern void relobj_envy(struct monst *,int);
extern void mdrop_obj(struct monst *,struct obj *,boolean);
#ifdef GOLDOBJ
extern struct obj *findgold(struct obj *);
#endif

/* ### steed.c ### */

extern void rider_cant_reach(void);
extern boolean can_saddle(struct monst *, struct obj *);
extern int use_saddle(struct obj *);
extern boolean can_ride(struct monst *);
extern int doride(void);
extern boolean mount_steed(struct monst *, boolean);
extern void exercise_steed(void);
extern void kick_steed(void);
extern void dismount_steed(int);
extern void place_monster(struct monst *,int,int);

/* ### teleport.c ### */

extern boolean teleok(int,int,boolean);
extern boolean goodpos(int,int,struct monst *,unsigned);
extern boolean eonline(coord *,xchar,xchar,struct permonst *);
extern boolean eofflin(coord *,xchar,xchar,struct permonst *);
extern boolean eofflin_close(coord *,xchar,xchar,struct permonst *);
extern boolean enexto(coord *,xchar,xchar,struct permonst *);
extern boolean enexto_core(coord *,xchar,xchar,struct permonst *,unsigned);
extern void xpathto(int,xchar,xchar,int (*)(void *,int,int),void *);
extern void teleds(int,int,boolean);
extern boolean safe_teleds(boolean);
extern boolean teleport_pet(struct monst *,boolean);
extern boolean tele(void);
extern int dotele(void);
extern boolean level_tele(void);
extern boolean branch_tele(void);
extern void domagicportal(struct trap *);
extern void tele_trap(struct trap *);
extern void level_tele_trap(struct trap *);
extern void rloc_to(struct monst *,int,int);
extern boolean rloc(struct monst *, boolean);
extern boolean tele_restrict(struct monst *);
extern void mtele_trap(struct monst *, struct trap *,int);
extern int mlevel_tele_trap(struct monst *, struct trap *,boolean,int);
extern void rlocos_at(int, int);
extern void rloco(struct obj *);
extern void randomly_place_obj(struct obj *);
extern int random_teleport_level(void);
extern boolean u_teleport_mon(struct monst *,boolean);

/* ### testing.c ### */
extern int wiz_testmenu(void);

/* ### tile.c ### */
#ifdef USE_TILES
extern void substitute_tiles(d_level *);
#endif

/* ### timeout.c ### */

extern void burn_away_slime(void);
extern void melt_frozen_air(void);
extern void unbind_lifesaving(long);
extern void unbind(long, boolean);
extern void unbind_core(long, boolean, boolean);
extern void nh_timeout(void);
extern void fall_asleep(int, boolean);
extern void attach_bomb_blow_timeout(struct obj *,int,boolean);
extern void attach_egg_hatch_timeout(struct obj *);
extern void attach_fig_transform_timeout(struct obj *);
extern void kill_egg(struct obj *);
extern void hatch_egg(void *, long);
extern void learn_egg_type(int);
extern void burn_object(void *, long);
extern int lightsource_radius(struct obj *);
extern long lightsource_turns(struct obj *);
extern boolean lightsource_timed(struct obj *);
extern void begin_burn(struct obj *);
extern void end_burn(struct obj *, boolean);
extern void lightsaber_deactivate(struct obj *, boolean);
extern void do_storms(void);
extern struct obj * update_skull_mon(struct monst *, struct obj *);
extern void desummon_mon(void *, long);
extern void cleanup_msummon(void *, long);
extern void desummon_obj(void *, long);
extern void summoner_gone(struct monst *, boolean);
extern void stop_corpse_timers(struct obj *);
extern timer_element * start_timer(long, short, short, void *);
extern void pause_timer(timer_element *);
extern void resume_timer(timer_element *);
extern void pause_timers(timer_element *);
extern void resume_timers(timer_element *);
extern void migrate_timers(timer_element *);
extern void receive_timers(timer_element *);
extern long stop_timer(short, timer_element *);
extern void stop_all_timers(timer_element *);
extern void run_timers(void);
extern void save_timers(timer_element *,int,int);
extern void rest_timers(int,void *,timer_element *,int,boolean,long);
extern void copy_timer(struct timer *, int, void *);
extern void copy_timers(struct timer *, int, void *);
#ifdef WIZARD
extern int wiz_timeout_queue(void);
extern void timer_sanity_check(void);
#endif

/* ### topten.c ### */

extern long encodeconduct(void);
extern void topten(int);
extern void prscore(int,char **);
extern struct obj *tt_oname(struct obj *);
extern void write_HUP_file(void);

/* ### track.c ### */

extern void initrack(void);
extern void settrack(void);
extern coord *gettrack(int,int,int);

/* ### trap.c ### */

extern boolean burnarmor(struct monst *, boolean);
extern boolean rust_dmg(struct obj *,const char *,int,boolean,struct monst *,boolean);
extern void grease_protect(struct obj *,const char *,struct monst *);
extern struct trap *maketrap(int,int,int);
extern void set_trap_ammo(struct trap *, struct obj *);
extern void fall_through(boolean);
extern struct monst *animate_statue(struct obj *,xchar,xchar,int,int *);
extern struct monst *activate_statue_trap(struct trap *,xchar,xchar,boolean);
extern void dotrap(struct trap *, unsigned);
extern void seetrap(struct trap *);
extern boolean spire_fall_mon(struct monst *);
extern int mintrap(struct monst *);
extern void reward_untrap(struct trap *, struct monst *);
extern void rloc_trap(struct trap *);
extern void instapetrify(const char *);
extern void minstapetrify(struct monst *,boolean);
extern void minstaglass(struct monst *,boolean);
extern void minstagoldify(struct monst *,int);
extern void selftouch(const char *);
extern void mselftouch(struct monst *,const char *,boolean);
extern void float_up(void);
extern void m_float_up(struct monst *, boolean);
extern void fill_pit(int,int);
extern int float_down(long long, long long);
extern void m_float_down(struct monst *, boolean);
extern int fire_damage_chain(struct obj *,boolean,boolean,xchar,xchar);
extern int fire_damage(struct obj *,boolean,xchar,xchar);
extern boolean lava_damage(struct obj *,xchar,xchar);
extern boolean water_damage(struct obj *, boolean, boolean, uchar, struct monst *);
extern boolean drown(void);
extern int dodeepswim(void);
extern void drain_en(int);
extern int dountrap(void);
extern void remove_trap_ammo(struct trap *);
extern int you_remove_jrt_fang(struct monst *, struct obj *);
extern int untrap(struct obj *);
extern boolean chest_trap(struct obj *,int,boolean);
extern void deltrap(struct trap *);
extern boolean delfloortrap(struct trap *);
extern struct trap *t_at(int,int);
extern void b_trapped(const char *,int);
extern boolean unconscious(void);
extern boolean lava_effects(boolean);
extern void blow_up_landmine(struct trap *);
extern int launch_obj(short, struct trap *, int);
extern void unshackle_mon(struct monst *);
extern void dowebgush(int,int,int);
extern void webgush(int,int,void *);
extern int ubreak_entanglement(void);
extern void entangle_effects(struct monst *);
extern int uescape_entanglement(void);

/* ### u_init.c ### */

extern void u_init(void);
extern void knows_object(int) ;
extern void know_random_obj(int);
extern void scatter_weapons(void);

/* ### unixmain.c ### */

#ifdef UNIX
# ifdef PORT_HELP
extern void port_help(void);
# endif
#endif /* UNIX */


/* ### unixtty.c ### */

#if defined(UNIX)
extern void gettty(void);
extern void settty(const char *);
extern void setftty(void);
extern void intron(void);
extern void introff(void);
extern void error(const char *,...) PRINTF_F(1,2);
#endif /* UNIX */

/* ### unixunix.c ### */

#ifdef UNIX
extern void getlock(void);
extern void regularize(char *);
# if defined(TIMED_DELAY) && !defined(msleep)
extern void msleep(unsigned);
# endif
# ifdef SHELL
extern int dosh(void);
# endif /* SHELL */
# if defined(SHELL) || defined(DEF_PAGER) || defined(DEF_MAILREADER)
extern int child(int);
# endif
#endif /* UNIX */

/* ### unixres.c ### */

#ifdef UNIX
#endif /* UNIX */

/* ### vault.c ### */

extern boolean grddead(struct monst *);
extern char vault_occupied(char *);
extern void invault(void);
extern int gd_move(struct monst *);
extern void paygd(void);
extern long hidden_gold(void);
extern boolean gd_sound(void);

/* ### version.c ### */

extern char *version_string(char *);
extern char *getversionstring(char *);
extern int doversion(void);
extern int doextversion(void);
extern boolean check_version(struct version_info *, const char *,boolean);
extern unsigned long get_feature_notice_ver(char *);
extern unsigned long get_current_feature_ver(void);
#ifdef RUNTIME_PORT_ID
extern void append_port_id(char *);
#endif

/* ### vision.c ### */

extern void vision_init(void);
extern int does_block(int,int,struct rm*);
extern void vision_reset(void);
extern void vision_recalc(int);
extern void block_point(int,int);
extern void unblock_point(int,int);
extern boolean clear_path(int,int,int,int);
extern void do_clear_area(int,int,int, void (*)(int,int,void *),void *);

/* ### weapon.c ### */

extern int hitval(struct obj *,struct monst *,struct monst *);
extern int attack_mask(struct obj *, int, int, struct monst *);
extern int dmgval_core(struct weapon_dice *, boolean, struct obj *, int, struct monst *);
extern int weapon_dmg_roll(struct weapon_dice *, boolean);
extern int weapon_die_roll(int, int, struct weapon_dice *, boolean);
extern int dmgval(struct obj *,struct monst *, int, struct monst *);
extern struct obj *select_rwep(struct monst *);
extern struct obj *select_hwep(struct monst *);
extern struct obj *select_pick(struct monst *);
extern struct obj *select_axe(struct monst *);
extern void possibly_unwield(struct monst *,boolean);
extern int mon_wield_item(struct monst *);
extern void setmwielded(struct monst *, struct obj *, long long);
extern void setmnotwielded(struct monst *, struct obj *);
extern void init_mon_wield_item(struct monst *);
extern int str_abon(void);
extern int abon(void);
extern float atr_dbon(struct obj *, struct monst *, int);
extern int str_dbon(struct monst *);
extern int dbon(struct obj *, struct monst *);
extern void reset_skills(void);
extern boolean fake_skill(int);
extern int enhance_weapon_skill(void);
extern int skill_dam_bonus(int);
extern void gm_weapon_skill(int);
extern void free_skill_up(int);
#ifdef DUMP_LOG
extern void dump_weapon_skill(void);
#endif
extern void unrestrict_weapon_skill(int);
extern void restrict_weapon_skill(int);
extern void expert_weapon_skill(int);
extern void skilled_weapon_skill(int);
extern void use_skill(int,int);
extern void lose_skill(int,int);
extern void add_weapon_skill(int);
extern void lose_weapon_skill(int);
extern int weapon_type(struct obj *);
extern int uwep_skill_type(void);
extern int get_your_size(void);
extern int get_your_shield_size(void);
extern int weapon_hit_bonus(struct obj *, int);
extern int mon_weapon_dam_bonus(struct permonst *, struct obj *, int);
extern int weapon_dam_bonus(struct obj *, int);
extern int shield_skill(struct obj *);
extern void skill_init(const struct def_skill *);
extern void skill_add(const struct def_skill *);
extern void skill_up(const struct def_skill *);
extern const char * P_NAME(int);
extern int aeshbon(void);
extern boolean ok_mariwep(struct obj *, struct monst *, struct permonst *, boolean);
extern struct obj * get_mariwep(struct monst *, struct permonst *, int);

/* ### were.c ### */

extern void were_change(struct monst *);
extern int counter_were(int);
extern int transmitted_were(int);
extern void were_transform(struct monst *, int);
extern void new_were(struct monst *);
extern int were_summon(struct monst *,int *,char *);
extern void you_were(void);
extern void you_unwere(boolean);

/* ### wield.c ### */

extern void setuwep(struct obj *);
extern void setuqwep(struct obj *);
extern void setuswapwep(struct obj *);
extern int dowield(void);
extern int doswapweapon(void);
extern int dowieldquiver(void);
extern void rewield(struct obj *, long long);
extern boolean wield_tool(struct obj *,const char *);
extern int test_twoweapon(void);
extern int starting_twoweapon(void);
extern void drop_uswapwep(void);
extern int dotwoweapon(void);
extern void uwepgone(void);
extern void uswapwepgone(void);
extern void uqwepgone(void);
extern void untwoweapon(void);
extern void erode_obj(struct obj *,boolean,boolean);
extern int chwepon(struct obj *,int);
extern int welded(struct obj *);
extern void weldmsg(struct obj *);
extern int wielder_size_bonus(struct permonst *);
extern double bimanual_mod(struct obj *, struct monst *);
extern boolean bimanual(struct obj *, struct permonst *);

/* ### windows.c ### */

extern void choose_windows(const char *);
extern char genl_message_menu(char,int,const char *);
extern void genl_preference_update(const char *);

/* ### wizard.c ### */

extern void amulet(void);
extern int mon_has_amulet(struct monst *);
extern int mon_has_special(struct monst *);
extern boolean mon_has_arti(struct monst *,short);
extern int tactics(struct monst *);
extern void aggravate(void);
extern void clonewiz(void);
extern int pick_nasty(void);
extern int nasty(struct monst*);
extern void yellow_nasty(void);
extern void yellow_dead(void);
extern boolean yellow_smite(void);
extern void resurrect(void);
extern void illur_resurrect(void);
extern void coa_arrive(void);
extern void intervene(void);
extern void illur_intervene(void);
extern boolean yello_intervene(void);
extern void wizdead(void);
extern void cuss(struct monst *);

/* ### worm.c ### */

extern int get_wormno(void);
extern void initworm(struct monst *,int);
extern void worm_move(struct monst *);
extern void worm_nomove(struct monst *);
extern void wormgone(struct monst *);
extern void wormhitu(struct monst *);
extern boolean wormline(struct monst *, int, int);
extern void cutworm(struct monst *,xchar,xchar,struct obj *);
extern void see_wsegs(struct monst *);
extern void detect_wsegs(struct monst *,boolean);
extern void save_worm(int,int);
extern void rest_worm(int);
extern void place_wsegs(struct monst *);
extern void remove_worm(struct monst *);
extern void place_worm_tail_randomly(struct monst *,xchar,xchar);
extern int count_wsegs(struct monst *);
extern boolean worm_known(struct monst *);

/* ### worn.c ### */
extern struct obj *wornmask_to_ring(long long);
extern int count_worn_rings(boolean);
extern int uring_otyp_index(int);
extern int uring_art_index(int);
extern struct obj *uring_otyp(int);
extern struct obj *uring_art(int);
extern boolean item_has_property(struct obj *, int);
extern void get_item_property_list(int *, struct obj*, int);
extern void setworn(struct obj *,long long);
extern void m_lose_armor(struct monst *,struct obj *);
extern void setnotworn(struct obj *);
extern void mon_set_minvis(struct monst *);
extern void mon_adjust_speed(struct monst *,int,struct obj *, boolean);
extern void update_mon_intrinsics(struct monst *,struct obj *,boolean,boolean);
extern int base_mac(struct monst *);
extern int find_mac(struct monst *);
extern int full_mac(struct monst *);
extern int full_marmorac(struct monst *);
extern int base_nat_mdr(struct monst *);
extern int base_mdr(struct monst *);
extern int avg_spell_mdr(struct monst *);
extern int roll_mdr(struct monst *, struct monst *, int);
extern int roll_mdr_detail(struct monst *, struct monst *, int, int, int);
extern void mon_slot_dr(struct monst *, struct monst *, int, int *, int *, int *, int);
extern int avg_mdr(struct monst *); 
extern int mdat_avg_mdr(struct monst *);
extern void m_dowear(struct monst *,boolean);
extern boolean mon_throw_armor(struct monst *);
extern boolean mon_strip_armor(struct monst *);
extern struct obj *mon_remove_armor(struct monst *,long);
extern struct obj *which_armor(struct monst *,long);
extern void mon_break_armor(struct monst *,boolean);
extern int extra_pref(struct monst *, struct obj *);
extern void bypass_obj(struct obj *);
extern void clear_bypasses(void);
extern int magic_negation(struct monst *);
extern void light_damage(void *, long);
extern int heal_mlevel_bonus(void);
extern int heal_vilya(void);
extern int lev_lomya(void);
extern int en_nenya(void);

/* ### write.c ### */

extern int dowrite(struct obj *);

/* ### xhity.c ### */

extern int check_subout(int *, int);
extern void add_subout(int *, int);
extern void zero_subout(int *);
extern int getvis(struct monst *, struct monst *, int, int);
extern boolean attack2(struct monst *);
extern int xattacky(struct monst *, struct monst *, int, int);
extern int xmeleehity(struct monst *, struct monst *, struct attack *, struct obj **, int, int, boolean);
extern struct attack * getattk(struct monst *, struct monst *, int *, int *, struct attack *, boolean, int *, int *);
extern boolean slips_free(struct monst *, struct monst *, struct attack *, int);
extern void heal(struct monst *, int);
extern int xdamagey(struct monst *, struct monst *, struct attack *, int);
extern int xstoney(struct monst *, struct monst *);
extern int xmeleehurty(struct monst *, struct monst *, struct attack *, struct attack *, struct obj **, boolean, int, int, int, boolean);
extern void getgazeinfo(int, int, struct permonst *, struct monst *, struct monst *, boolean *, boolean *, boolean *);
extern int xgazey(struct monst *, struct monst *, struct attack *, int);
extern int xengulfhity(struct monst *, struct monst *, struct attack *, int);
extern int xengulfhurty(struct monst *, struct monst *, struct attack *, int);
extern void passive_obj2(struct monst *, struct monst *, struct obj *, struct attack *, struct attack *);
extern void breakobj(struct obj *, xchar, xchar, boolean, boolean);
extern int hmon_with_unowned_obj(struct monst *, struct obj **, int);
extern int hmon_with_trap(struct monst *, struct obj **, struct trap *, int, int);
extern int hmon_general(struct monst *, struct monst *, struct attack *, struct attack *, struct obj **, void *, int, int, int, boolean, int, boolean, int);
extern void wakeup2(struct monst *, boolean);
extern int xpassivey(struct monst *, struct monst *, struct attack *, struct obj *, int, int, struct permonst *, boolean);
extern int tohitval(struct monst *, struct monst *, struct attack *, struct obj *, void *, int, int, int *);
extern void weave_black_web(struct monst *);
extern int android_combo(void);
extern void movement_combos(void);
extern boolean perform_monk_move(int);
extern int check_monk_move(void);
extern int u_pole_pound(struct monst *);
extern boolean Curse_res(struct monst *, boolean);
extern int mummy_curses_x(struct monst *, struct monst *);
extern int reduce_dmg(struct monst *, int, boolean, boolean);

/* ### xhityhelpers.c ### */

extern boolean magr_can_attack_mdef(struct monst *, struct monst *, int, int, boolean);
extern int attack_checks(struct monst *, struct obj *);
extern boolean madness_cant_attack(struct monst *);
extern void stumble_onto_mimic(struct monst *);
extern void check_caitiff(struct monst *);
extern void steal_it(struct monst *, struct attack *);
extern int mattacku(struct monst *);
extern int mattackm(struct monst *, struct monst *);
extern int fightm(struct monst *);
extern void expels(struct monst *, struct permonst *, boolean);
extern boolean diseasemu(struct permonst *);
extern void u_slow_down(void);
extern const char *mpoisons_subj(struct monst *, struct attack *);
extern int sleep_monst(struct monst *, int, int);
extern void slept_monst(struct monst *);
extern void hurtarmor(int, boolean);
extern void hurtmarmor(struct monst *, int, boolean);
extern long long attk_protection(int);
extern long long attk_equip_slot(struct monst *, int);
extern boolean badtouch(struct monst *, struct monst *, struct attack *, struct obj *);
extern boolean safe_attack(struct monst *, struct monst *, struct attack *, struct obj *, struct permonst *, struct permonst *);
extern int beastmastery(void);
extern int narya(void);
extern int mountedCombat(void);
extern boolean obj_silver_searing(struct obj *);
extern boolean obj_jade_searing(struct obj *);
extern int hatesobjdmg(struct monst *, struct obj *, struct monst *);
extern int hits_insubstantial(struct monst *, struct monst *, struct attack *, struct obj *);
extern boolean miss_via_insubstantial(struct monst *, struct monst *, struct attack *, struct obj *, int);
extern int destroy_item(struct monst *, int, int);
extern boolean wearing_dragon_armor(struct monst *, int);
extern int hit_with_cclaw(struct monst *,struct obj *, int, int, int, struct attack *);
extern int hit_with_iwarp(struct monst *,struct obj *, int, int, int, struct attack *);
extern int hit_with_rblood(struct monst *,struct obj *, int, int, int, struct attack *);
extern int hit_with_dance(struct monst *,struct obj *, int, int, int, struct attack *);
extern int hit_with_streaming(struct monst *,struct obj *, int, int, int, struct attack *);

/* ### zap.c ### */

extern char * flash_type(int,int);
extern int zap_glyph_color(int);
extern int wand_adtype(int);
extern int zap_hit(struct monst *,int, boolean);
extern int bhitm(struct monst *,struct obj *);
extern void probe_monster(struct monst *);
extern boolean get_obj_location(struct obj *,xchar *,xchar *,int);
extern boolean get_mon_location(struct monst *,xchar *,xchar *,int);
extern struct monst *get_container_location(struct obj *obj, int *, int *);
extern struct monst *montraits(struct obj *,coord *);
extern struct monst *revive(struct obj *, boolean);
extern int unturn_dead(struct monst *);
extern void cancel_item(struct obj *);
extern boolean drain_item(struct obj *);
extern boolean damage_item(struct obj *);
extern struct obj *randpoly_obj(struct obj *);
extern struct obj *poly_obj(struct obj *, int);
extern boolean obj_resists(struct obj *,int,int);
extern boolean obj_shudders(struct obj *);
extern void do_osshock(struct obj *);
extern int bhito(struct obj *,struct obj *);
extern int bhitpile(struct obj *,int (*)(struct obj *,struct obj *),int,int);
extern int zapcostchance(struct obj *, struct monst *);
extern int zappable(struct obj *);
extern void zapnodir(struct obj *);
extern int dozap(void);
extern struct zapdata * basiczap(struct zapdata *, int, int, int);
extern void zap(struct monst *, int, int, int, int, int, struct zapdata *);
extern int zapyourself(struct obj *,boolean);
extern boolean cancel_monst(struct monst *,struct obj *,
			    boolean,boolean,boolean,int);
extern void weffects(struct obj *);
extern int spell_damage_bonus(void);
extern int kraubon(void);
extern const char *exclam(int force);
extern void hit(const char *,struct monst *,const char *);
extern void miss(const char *,struct monst *);
extern struct monst *bhit(int,int,int,int,int (*)(struct monst *,struct obj *),
			  int (*)(struct obj *,struct obj *),struct obj *, boolean *);
extern int flash_hits_mon(struct monst *, struct obj *);
extern int burn_floor_paper(int,int,boolean,boolean);
extern void buzz(int,int,int,int,xchar,xchar,int,int,int,int);
extern void lightning_blind(struct monst *, int);
extern struct monst * delouse(struct monst *,int);
extern struct monst * delouse_tame(struct monst *);
extern void melt_ice(xchar,xchar);
extern int zap_over_floor(xchar,xchar,int,int,int,boolean *);
extern void break_boulder(struct obj *);
extern void fracture_rock(struct obj *);
extern boolean break_statue(struct obj *);
extern void break_crate(struct obj *);
extern void separate_mass_of_stuff(struct obj *, boolean);
extern int resist(struct monst *,char,int,int);
extern boolean makewish(int);
extern void costly_cancel(struct obj *);
extern void revive_egg(struct obj *);
extern int allow_artwish(void);
extern boolean dowand_refresh(void);
extern int android_braindamage(int, struct monst *, struct monst *, boolean);
extern boolean nearby_targets(struct monst *);
extern boolean adjacent_targets(struct monst *);

#endif /* !MAKEDEFS_C && !LEV_LEX_C */

/* ### unicode.c ### */
extern glyph_t get_unicode_codepoint(int);
extern int pututf8char(glyph_t);

#endif /* EXTERN_H */
