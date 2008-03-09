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

#include "fn_bot_robot.h"

/* --------------------------------------------------------------- */

fn_bot_t * fn_bot_robot_create(void)
{
  fn_bot_t * bot = malloc(sizeof(fn_bot_t));
  memset(bot, 0, sizeof(fn_bot_t));
  bot->get_hit = fn_bot_robot_get_hit;
  bot->animate = fn_bot_robot_animate;
  bot->do_step = fn_bot_robot_do_step;
  bot->blit_to_level = fn_bot_robot_blit_to_level;
  bot->delete_bot_data = fn_bot_robot_delete_bot_data;
  bot->data = malloc(sizeof(fn_bot_robot_data_t));
  fn_bot_robot_data_t * data = bot->data;
  memset(data, 0, sizeof(fn_bot_robot_data_t));
  data->direction = fn_horizontal_direction_left;
  data->state = fn_bot_robot_state_walking;
  data->num_animation = 0;
  return bot;
}

/* --------------------------------------------------------------- */

void fn_bot_robot_get_hit(fn_bot_t * bot)
{
  /* TODO */
}

/* --------------------------------------------------------------- */

void fn_bot_robot_animate(fn_bot_t * bot)
{
  
}

/* --------------------------------------------------------------- */

int fn_bot_robot_do_step(fn_bot_t * bot)
{
  /* TODO */
  return 0;
}

/* --------------------------------------------------------------- */

void fn_bot_robot_blit_to_level(fn_bot_t * bot,
    SDL_Surface * bot_layer)
{
  /* TODO */
}

/* --------------------------------------------------------------- */

void fn_bot_robot_delete_bot_data(void * data)
{
  fn_bot_robot_data_t * botdata = data;
  free(botdata);
}
