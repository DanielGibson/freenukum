/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Bot struct
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

#ifndef FN_BOT_H
#define FN_BOT_H

#include <SDL/SDL.h>

#include "fn_level.h"

/* --------------------------------------------------------------- */

typedef struct fn_bot_t {
  /**
   * A pointer to any data needed in private.
   */
  void * data;

  /**
   * The level inside which the bot is.
   */
  fn_level_t level;

  /**
   * The x position in the level.
   */
  Uint16 pos_x;

  /**
   * The y position in the level.
   */
  Uint16 pos_y;

  /**
   * Function to call when bot gets hit.
   */
  void (* get_hit)(void);

  /**
   * Function that is called to calculate progress of one frame.
   * @return  Zero if the bot was killed, otherwise non-zero.
   */
  int (* do_step)(void);

  /**
   * Function that blits the bot in its current state to the level.
   * @param  bot_layer  The SDL Surface to which the bots are blitted.
   */
  void (* blit_to_level)(SDL_Surface * bot_layer);
} fn_bot_t;

/* --------------------------------------------------------------- */

#endif // FN_BOT_H

