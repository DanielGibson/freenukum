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

#include <glib.h>

/* --------------------------------------------------------------- */

#include "fn_hero.h"
#include "fn_animation.h"
#include "fn_bot.h"

/* --------------------------------------------------------------- */

typedef struct fn_level_t fn_level_t;

/* --------------------------------------------------------------- */

#include "fn_item.h"

/* --------------------------------------------------------------- */

/**
 * A struct representing a level.
 */
struct fn_level_t {
  /**
   * Stores our hero.
   */
  fn_hero_t hero;

  /**
   * Stores the raw data loaded from the level.
   */
  Uint16 raw[FN_LEVEL_HEIGHT][FN_LEVEL_WIDTH];

  /**
   * Stores if tiles are solid or not.
   */
  Uint8 solid[FN_LEVEL_HEIGHT][FN_LEVEL_WIDTH];
  
  /**
   * The solid and background tiles.
   */
  Uint16 tiles[FN_LEVEL_HEIGHT][FN_LEVEL_WIDTH];

  /**
   * The surface for blitting the level.
   */
  SDL_Surface * surface;

  /**
   * The pixel size.
   */
  size_t pixelsize;
  
  /**
   * The tile cache.
   */
  fn_tilecache_t * tilecache;

  /**
   * The bots
   */
  GList * bots;

  /**
   * The items
   */
  GList * items;

  /**
   * The animations
   */
  GList * animations;

  /**
   * As long as this is non-zero, we keep on playing.
   */
  int do_play;

  /**
   * The number of animated frames since last action.
   */
  size_t animated_frames;

};

/* --------------------------------------------------------------- */

/**
 * Load a level from a file.
 *
 * @param  fd  An already opened file descriptor to the level file.
 * @param  pixelsize  The size of a single pixel.
 * @param  tilecache  The tilecache from which to show the tiles.
 *
 * @return  The fully loaded level. If it was not possible to load
 *          the level, NULL is returned. Examine errno in order
 *          to find out what error occured.
 */
fn_level_t * fn_level_load(int fd,
    size_t pixelsize,
    fn_tilecache_t * tilecache);

/* --------------------------------------------------------------- */

/**
 * Destroy a level.
 *
 * @param  level  The level to destroy.
 */
void fn_level_free(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Get a tile from a certain position inside the level.
 *
 * @param  lv  The level.
 * @param  x   The x coordinate.
 * @param  y   The y coordinate.
 *
 * @return  The tile of the position.
 */
Uint16 fn_level_get_tile(fn_level_t * lv, size_t x, size_t y);

/* --------------------------------------------------------------- */

/**
 * Get the raw value of a certain position inside the level.
 *
 * @param  lv  The level.
 * @param  x   The x coordinate.
 * @param  y   The y coordinate.
 *
 * @return  The raw tile number of the position.
 */
Uint16 fn_level_get_raw(fn_level_t * lv, size_t x, size_t y);

/* --------------------------------------------------------------- */

/**
 * Get the information wether a tile is solid or not.
 *
 * @param  lv  The level.
 * @param  x   The x coordinate.
 * @param  y   The y coordinate.
 *
 * @return 1 if solid, else 0.
 */
Uint8 fn_level_is_solid(fn_level_t * lv, int x, int y);

/* --------------------------------------------------------------- */

/**
 * Blit the current state of the level to an SDL Surface.
 *
 * @param  lv         The level to blit.
 * @param  target     The target SDL Surface.
 * @param  targetrect The target area to which to blit.
 * @param  sourcerect The source rectangle.
 */
void fn_level_blit_to_surface(fn_level_t * lv,
    SDL_Surface * target,
    SDL_Rect * targetrect,
    SDL_Rect * sourcerect);

/* --------------------------------------------------------------- */

/**
 * Indicate if we are still playing this level.
 * 
 * @param  lv    The level we want to play.
 * 
 * @return  non-zero if we are still playing, otherwise zero.
 */
int fn_level_keep_on_playing(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Get the hero of the level.
 *
 * @param  lv    The level from which to get the hero.
 *
 * @return The hero.
 */
fn_hero_t * fn_level_get_hero(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Call this function make the game act one step further.
 *
 * @param  lv  The level which should step.
 *
 * @return zero if the level is finished, otherwise non-zero.
 */
int fn_level_act(fn_level_t * lv);

/* --------------------------------------------------------------- */

#endif /* FN_LEVEL_H */
