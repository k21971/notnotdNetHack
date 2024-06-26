/* vim:set cin ft=c sw=4 sts=4 ts=8 et ai cino=Ls\:0t0(0 : -*- mode:c;fill-column:80;tab-width:8;c-basic-offset:4;indent-tabs-mode:nil;c-file-style:"k&r" -*-*/

#ifndef CURSDIAL_H
# define CURSDIAL_H

# include <regex.h>

/* Global declarations */

void curses_line_input_dialog(const char *prompt, char *answer, int buffer);
int curses_character_input_dialog(const char *prompt, const char *choices,
                                  char def);
int curses_ext_cmd(void);
void curses_create_nhmenu(winid wid);
void curses_add_nhmenu_item(winid wid, int glyph, const anything * identifier,
                            char accelerator, char group_accel, int attr,
                            const char *str, boolean presel);
boolean get_menu_coloring(char *, int *, int *);
void curses_finalize_nhmenu(winid wid, const char *prompt);
int curses_display_nhmenu(winid wid, int how, menu_item ** _selected);
boolean curses_menu_exists(winid wid);
void curses_del_menu(winid wid);



#endif /* CURSDIAL_H */
