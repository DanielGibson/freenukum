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

typedef enum fn_bot_robot_state_e {
  fn_bot_robot_state_walking,
  fn_bot_robot_state_disappearing,
  fn_bot_robot_state_blowup,
  fn_bot_robot_state_size
} fn_bot_robot_state_e;

/* --------------------------------------------------------------- */

const size_t
fn_bot_num_animations[fn_bot_robot_state_size] = {3, 7, 5};

/* --------------------------------------------------------------- */

/**
 * The struct holding the data for the robot.
 */
typedef struct fn_bot_robot_data_t {
  fn_horizontal_direction_e direction;
  fn_bot_robot_state_e state;
  size_t num_animation;
} fn_bot_robot_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a new robot.
 *
 * @return  The newly created bot.
 */
fn_bot_t * fn_bot_robot_create(void);

/* --------------------------------------------------------------- */

/**
 * Function that is called when the bot gets hit.
 *
 * @param  bot  The bot that got hit.
 */
void fn_bot_robot_get_hit(fn_bot_t * bot);

/* --------------------------------------------------------------- */

/**
 * Function that is called for animation.
 *
 * @param  bot  The bot which is to be animated.
 */
void fn_bot_robot_animate(fn_bot_t * bot);

/* --------------------------------------------------------------- */

/**
 * Function that is called for simulation.
 *
 * @param  bot  The bot which has to be simulated.
 *
 * @return  Zero if the bot was killed, otherwise non-zero.
 */
int fn_bot_robot_do_step(fn_bot_t * bot);

/* --------------------------------------------------------------- */

/**
 * Function that blits the robot in its current state to the level.
 * @param  bot        The bot which is to be blitted.
 * @param  bot_layer  The SDL Surface to which the bots are blitted.
 */
void fn_bot_robot_blit_to_level(fn_bot_t * bot,
    SDL_Surface * bot_layer);

/* --------------------------------------------------------------- */

/**
 * Function that deletes the data stored for the bot.
 * @param  bot  The bot whose data has to be deleted.
 */
void fn_bot_robot_delete_bot_data(void * data);

/* --------------------------------------------------------------- */

#endif // FN_BOT_ROBOT_H
