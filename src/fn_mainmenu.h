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

#define FN_MENUCHOICE_START              's'
#define FN_MENUCHOICE_RESTORE            'r'
#define FN_MENUCHOICE_INSTRUCTIONS       'i'
#define FN_MENUCHOICE_ORDERINGINFO       'o'
#define FN_MENUCHOICE_SETUP              's'
#define FN_MENUCHOICE_FULLSCREENTOGGLE   'f'
#define FN_MENUCHOICE_EPISODECHANGE      'e'
#define FN_MENUCHOICE_HIGHSCORES         'h'
#define FN_MENUCHOICE_PREVIEWS           'p'
#define FN_MENUCHOICE_VIEWUSERDEMO       'v'
#define FN_MENUCHOICE_TITLESCREEN        't'
#define FN_MENUCHOICE_CREDITS            'c'
#define FN_MENUCHOICE_QUIT               'q'

/* --------------------------------------------------------------- */

/**
 * Show the main menu and return the choice the user made.
 *
 * @param  env   The game environment.
 *
 * @return The choice that the user made. This is one of the
 *         FN_MENUCHOICE_* defined values.
 */
int fn_mainmenu(
    fn_environment_t * env);

/* --------------------------------------------------------------- */

#endif /* FN_MAINMENU_H */
