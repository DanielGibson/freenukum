/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Gameplay functions
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

#ifndef FN_GAME_H
#define FN_GAME_H

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_hero.h"
#include "fn_tilecache.h"
#include "fn_settings.h"
#include "fn_environment.h"

/* --------------------------------------------------------------- */

/**
 * Start the game from the beginning including the intro sequence.
 *
 * @param  env        The environent.
 */
void fn_game_start(
    fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Start the game from a certain level.
 *
 * @param  levelnumber  The level number (must be between 1 and 12).
 * @param  env          The environment.
 * @param  hero         The hero to use.
 *
 * @return Non-zero if the level was completed successfully, else zero.
 */
int fn_game_start_in_level(
    int levelnumber,
    fn_environment_t * env);

/* --------------------------------------------------------------- */

#endif /* FN_GAME_H */
