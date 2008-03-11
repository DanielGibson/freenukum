/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Hero behavior functions
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

#ifndef FN_HERO_H
#define FN_HERO_H

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

#define FN_HERO_DIRECTION_RIGHT    0
#define FN_HERO_DIRECTION_LEFT     1

#define FN_HERO_MOTION_NONE        0
#define FN_HERO_MOTION_WALKING     1

#define FN_HERO_FLYING_FALSE       0
#define FN_HERO_FLYING_TRUE        1

#define FN_HERO_SHOOTING_FALSE     0
#define FN_HERO_SHOOTING_TRUE      1

/* --------------------------------------------------------------- */

/**
 * Our hero.
 */
typedef struct fn_hero_t {
  /**
   * The direction to which the hero moves.
   */
  Uint8 direction;

  /**
   * The motion state (none or walking).
   */
  Uint8 motion;

  /**
   * Is the hero going up (flying) or resting (falling/standing)?
   */
  Uint8 flying;

  /**
   * Is the hero currently shooting?
   */
  Uint8 shooting;

  /**
   * How much firepower does the hero have?
   */
  Uint8 firepower;

  /**
   * The counter for actions that take longer than one animation frame.
   */
  Uint8 counter;

  /**
   * The tile number that currently represents the hero.
   */
  int tilenr;

  /**
   * The current representation of the hero within the tile cache.
   */
  Uint8 animationframe;
  /**
   * The number of frames inside the current animation.
   */
  Uint8 num_animationframes;

  /**
   * The inventory (one bit for each key/item)
   */
  Uint8 inventory;
  /**
   * The health of our hero (0 = still alive, 8 = full life).
   */
  Uint8 health;

  /**
   * The x position of our hero (in half-tiles).
   */
  Uint16 x;
  /**
   * The y position of our hero (in half-tiles).
   */
  Uint16 y;
} fn_hero_t;

/* --------------------------------------------------------------- */

typedef void (*fn_hero_changed_f)(fn_hero_t *);

/* --------------------------------------------------------------- */

void fn_hero_blit(
    fn_hero_t * hero,
    SDL_Surface * target,
    fn_tilecache_t * tilecache,
    Uint8 pixelsize);

/* --------------------------------------------------------------- */

void fn_hero_next_animationframe(
    fn_hero_t * hero);

/* --------------------------------------------------------------- */

void fn_hero_update_animation(
    fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Initialize a hero.
 *
 * @param  hero  The hero that is to be initialized.
 * @param  x     The initial x position of our hero (in half-tiles)
 * @param  y     The initial x position of our hero (in half-tiles)
 */
void fn_hero_init(
    fn_hero_t * hero,
    Uint16 x,
    Uint16 y);

/* --------------------------------------------------------------- */

void fn_hero_set_direction(
    fn_hero_t * hero,
    Uint8 direction);

/* --------------------------------------------------------------- */

void fn_hero_set_motion(
    fn_hero_t * hero,
    Uint8 motion);

/* --------------------------------------------------------------- */

void fn_hero_set_flying(
    fn_hero_t * hero,
    Uint8 flying);

/* --------------------------------------------------------------- */

void fn_hero_set_shooting(
    fn_hero_t * hero,
    Uint8 shooting);

/* --------------------------------------------------------------- */

void fn_hero_set_firepower(
    fn_hero_t * hero,
    Uint8 firepower);

/* --------------------------------------------------------------- */

void fn_hero_set_counter(
    fn_hero_t * hero,
    Uint8 counter);

/* --------------------------------------------------------------- */

void fn_hero_set_inventory(
    fn_hero_t * hero,
    Uint8 inventory);

/* --------------------------------------------------------------- */

void fn_hero_set_health(
    fn_hero_t * hero,
    Uint8 health);

/* --------------------------------------------------------------- */

void fn_hero_jump(
    fn_hero_t * hero);

/* --------------------------------------------------------------- */

#endif /* FN_HERO_H */
