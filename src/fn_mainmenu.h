/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Main menu
 *******************************************************************/

#ifndef FN_MAINMENU_H
#define FN_MAINMENU_H

/* --------------------------------------------------------------- */

#include "fn_msgbox.h"

/* --------------------------------------------------------------- */

#define FN_MENUCHOICE_START         1
#define FN_MENUCHOICE_RESTORE       2
#define FN_MENUCHOICE_INSTRUCTIONS  3
#define FN_MENUCHOICE_ORDERINGINFO  4
#define FN_MENUCHOICE_SETUP         5
#define FN_MENUCHOICE_HIGHSCORES    6
#define FN_MENUCHOICE_PREVIEWS      7
#define FN_MENUCHOICE_VIEWUSERDEMO  8
#define FN_MENUCHOICE_TITLESCREEN   9
#define FN_MENUCHOICE_CREDITS      10
#define FN_MENUCHOICE_QUIT         11

/* --------------------------------------------------------------- */

/**
 * Show the main menu and return the choice the user made.
 *
 * @param  tilecache   The tilecache from which the tiles are loaded.
 * @param  pixelsize   The pixel size on the screen.
 * @param  screen      The screen on which the menu is shown.
 *
 * @return The choice that the user made. This is one of the
 *         FN_MENUCHOICE_* defined values.
 */
int fn_mainmenu(
    fn_tilecache_t * tilecache,
    Uint8 pixelsize,
    SDL_Surface * screen);

/* --------------------------------------------------------------- */

#endif /* FN_MAINMENU_H */
