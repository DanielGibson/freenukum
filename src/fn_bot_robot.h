/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Robot functions for small single robot
 *
 * *****************************************************************
 *
 * Copyright 2008 Wolfgang Silbermayr
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

#ifndef FN_BOT_ROBOT_H
#define FN_BOT_ROBOT_H

#include <SDL/SDL.h>

#include "fn_bot.h"

/* --------------------------------------------------------------- */

/**
 * Create a new robot.
 *
 * @return  The newly created bot.
 */
fn_bot_t * fn_bot_robot_create(void);

/**
 * Function that is called when the bot gets hit.
 */
void fn_bot_robot_get_hit(void);

/**
 * Function that is called for simulation.
 *
 * @return  Zero if the bot was killed, otherwise non-zero.
 */
int fn_bot_robot_do_step(void);

/**
 * Function that blits the robot in its current state to the level.
 * @param  bot_layer  The SDL Surface to which the bots are blitted.
 */
void fn_bot_robot_blit_to_level(SDL_Surface * bot_layer);

#endif // FN_BOT_ROBOT_H
