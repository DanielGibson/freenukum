/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Level functions
 *
 * *****************************************************************
 *
 * Copyright 2007 Wolfgang Silbermayr
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

#ifndef FN_LEVEL_H
#define FN_LEVEL_H

/* --------------------------------------------------------------- */

#include "fn_hero.h"

/* --------------------------------------------------------------- */

/**
 * A struct representing a level.
 */
typedef struct fn_level_t {
  fn_hero_t hero;
  Uint8 solid[FN_LEVEL_HEIGHT][FN_LEVEL_WIDTH];
  Uint16 tiles[FN_LEVEL_HEIGHT][FN_LEVEL_WIDTH];
} fn_level_t;

/* --------------------------------------------------------------- */

/**
 * Load a level from a file.
 *
 * @param  fd  An already opened file descriptor to the level file.
 *
 * @return  The fully loaded level. If it was not possible to load
 *          the level, NULL is returned. Examine errno in order
 *          to find out what error occured.
 */
fn_level_t * fn_level_load(int fd);

/* --------------------------------------------------------------- */

/**
 * Destroy a level.
 *
 * @param  level  The level to destroy.
 */
void fn_level_destroy(fn_level_t * level);

/* --------------------------------------------------------------- */

/**
 * Get a tile from a certain position inside the level.
 */
Uint16 fn_level_gettile(fn_level_t * lv, size_t x, size_t y);

/* --------------------------------------------------------------- */

#endif /* FN_LEVEL_H */
