/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Main menu
 *
 * *****************************************************************
 *
 * Copyright 2007-2008 Wolfgang Silbermayr
 *
 * *****************************************************************
 *
 * This file is part of Freenukum.
 * 
 * Freenukum is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Freenukum is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
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
