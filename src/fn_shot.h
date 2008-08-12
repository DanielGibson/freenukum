/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Shot functions
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

#ifndef FN_SHOT_H
#define FN_SHOT_H

/* --------------------------------------------------------------- */

typedef struct fn_shot_t fn_shot_t;

/* --------------------------------------------------------------- */

#include "fn_level.h"

/* --------------------------------------------------------------- */

/**
 * The shot struct.
 */
struct fn_shot_t {
  /**
   * The level inside which the shot is located.
   */
  fn_level_t * level;

  /**
   * The position of the shot.
   */
  SDL_Rect position;

  /**
   * Flag that indicates if the shot is (still) alive.
   */
  int is_alive;

  /**
   * The direction to which the shot was fired.
   */
  fn_horizontal_direction_e direction;

  /**
   * The counter for the animation.
   */
  Uint8 counter;

  /**
   * The down until the shot is to be removed.
   */
  Uint8 countdown;

  /**
   * Flag indicating if collision bounds are drawn.
   */
  Uint8 draw_collision_bounds;
};

/* --------------------------------------------------------------- */

/**
 * Create a shot.
 *
 * @param  level      The level inside which to create the shot.
 * @param  x          The initial x position (in pixels).
 * @param  y          The initial y position (in pixels).
 * @param  direction  The direction to which the shot goes.
 *
 * @return  The newly created shot.
 */
fn_shot_t * fn_shot_create(fn_level_t * level,
    Uint16 x, Uint16 y, fn_horizontal_direction_e direction);

/* --------------------------------------------------------------- */

/**
 * Delete a shot.
 *
 * @param  shot      The shot to delete.
 */
void fn_shot_free(fn_shot_t * shot);

/* --------------------------------------------------------------- */

/**
 * Make the shot act one game cycle.
 *
 * @param  shot      The shot.
 *
 * @return 0 if shot is obsolete, 1 if it is still alive.
 */
Uint8 fn_shot_act(fn_shot_t * shot);

/* --------------------------------------------------------------- */

/**
 * Blit a shot.
 *
 * @param  shot       The shot to delete.
 */
void fn_shot_blit(fn_shot_t * shot);

/* --------------------------------------------------------------- */

/**
 * Call this function when a shot gets out of sight.
 * It tells the shot that it is no longer alive.
 *
 * @param  shot      The shot.
 */
void fn_shot_gets_out_of_sight(fn_shot_t * shot);

/* --------------------------------------------------------------- */

/**
 * Get the x position of a shot (in pixels).
 *
 * @param  shot  The shot.
 */
Uint16 fn_shot_get_x(fn_shot_t * shot);

/* --------------------------------------------------------------- */

/**
 * Get the y position of a shot (in pixels).
 *
 * @param  shot  The shot.
 */
Uint16 fn_shot_get_y(fn_shot_t * shot);

/* --------------------------------------------------------------- */

/**
 * Get the width of a shot (in pixels).
 *
 * @param  shot  The shot.
 */
Uint16 fn_shot_get_w(fn_shot_t * shot);

/* --------------------------------------------------------------- */

/**
 * Get the height of a shot (in pixels).
 *
 * @param  shot  The shot.
 */
Uint16 fn_shot_get_h(fn_shot_t * shot);

/* --------------------------------------------------------------- */

/**
 * Get the level inside which a shot resides.
 * 
 * @param  shot  The shot.
 *
 * @return The level inside the shot resides.
 */
fn_level_t * fn_shot_get_level(fn_shot_t * shot);

/* --------------------------------------------------------------- */

/**
 * Check if a shot overlaps an actor.
 *
 * @param  shot   The shot.
 * @param  actor  The actor.
 *
 * @return 1 if they overlap, otherwise 0.
 */
Uint8 fn_shot_overlaps_actor(fn_shot_t * shot, fn_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Check if a shot touches an actor.
 *
 * @param  shot   The shot.
 * @param  actor  The actor.
 *
 * @return 1 if they touch, otherwise 0.
 */
Uint8 fn_shot_touches_actor(fn_shot_t * shot, fn_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Enable or disable the drawing of collision bounds for a shot.
 *
 * @param  shot    The shot.
 * @param  enable  If 0, disable drawing, else enable.
 */
void fn_shot_set_draw_collision_bounds(
    fn_shot_t * shot, Uint8 enable);

/* --------------------------------------------------------------- */

/**
 * Check if the shot hits a solid tile
 *
 * @param  shot   The shot.
 *
 * @return 1 if the shot hits solid tile, otherwise 0.
 */
Uint8 fn_shot_hits_solid(
    fn_shot_t * shot);

/* --------------------------------------------------------------- */

#endif /* FN_SHOT_H */
