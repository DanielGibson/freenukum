/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Hero behavior functions
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

#ifndef FN_HERO_H
#define FN_HERO_H

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

typedef struct fn_hero_t fn_hero_t;

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"
#include "fn_actor.h"

/* --------------------------------------------------------------- */

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
struct fn_hero_t {
  /**
   * The direction to which the hero moves.
   */
  fn_horizontal_direction_e direction;

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

  /**
   * The score of the hero.
   */
  Uint64 score;

  /**
   * Blit the hero only if this is zero.
   */
  Uint8 hidden;

  /**
   * The letter which was last fetched by the hero.
   * This is zero if none was fetched yet.
   */
  Uint8 fetchedletter;

  /**
   * The speed with which our hero falls or jumps.
   * Either 0, 1 or 2.
   */
  Uint8 verticalspeed;
};

/* --------------------------------------------------------------- */

typedef void (*fn_hero_changed_f)(fn_hero_t *);

/* --------------------------------------------------------------- */

void fn_hero_blit(
    fn_hero_t * hero,
    SDL_Surface * target,
    fn_tilecache_t * tilecache,
    Uint8 pixelsize);

/* --------------------------------------------------------------- */

/**
 * Let the hero act execute his next timed action.
 *
 * @param  hero  The hero that has to act.
 * @param  data  A pointer to the level inside which the hero
 *               is placed. Maybe I will find a better way to
 *               use a direct fn_level_t pointer instead of a
 *               void* one day, but currently this is the
 *               simplest solution because we have a chicken-egg
 *               problem if we include fn_hero.h inside fn_level.h
 *               and other way round too.
 * 
 * @return Zero if the hero has died, otherwise non-zero.
 */
int fn_hero_act(fn_hero_t * hero,
    void * data);

/* --------------------------------------------------------------- */

/**
 * Put the hero to a new position.
 *
 * @param  hero  The hero.
 * @param  x     The new x position of our hero (in half-tiles).
 * @param  y     The new y position of our hero (in half-tiles).
 */
void fn_hero_replace(fn_hero_t * hero,
    Uint16 x, Uint16 y);

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

/**
 * Update a hero for a new level.
 *
 * @param  hero  The hero that is to be updated.
 * @param  x     The initial x position of our hero (in half-tiles)
 * @param  y     The initial x position of our hero (in half-tiles)
 */
void fn_hero_enterlevel(
    fn_hero_t * hero,
    Uint16 x,
    Uint16 y);

/* --------------------------------------------------------------- */

void fn_hero_set_direction(
    fn_hero_t * hero,
    fn_horizontal_direction_e direction);

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

Uint8 fn_hero_get_inventory(
    fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Improve the life of our hero by a certain amount of units.
 *
 * @param  hero         The hero whose life should be improved.
 * @param  improvement  The number of units by which to improve.
 */
void fn_hero_improve_health(fn_hero_t * hero, Uint8 improvement);

/* --------------------------------------------------------------- */

/**
 * Get the health of our hero.
 *
 * @param  hero  The hero.
 *
 * @return  The health of the hero.
 */
Uint8 fn_hero_get_health(fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Set the health of the hero.
 *
 * @param  hero    The hero.
 * @param  health  The health to set for the hero.
 */
void fn_hero_set_health(
    fn_hero_t * hero,
    Uint8 health);

/* --------------------------------------------------------------- */

void fn_hero_jump(
    fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Get the x position of the hero.
 *
 * @param  hero  The hero.
 *
 * @return  The x position.
 */
Uint16 fn_hero_get_x(
    fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Get the y position of the hero.
 *
 * @param  hero  The hero.
 *
 * @return  The y position.
 */
Uint16 fn_hero_get_y(
    fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Calculate if our hero would  collide with a solid tile in the level.
 *
 * @param  hero        The hero.
 * @param  level       The level.
 * @param  halftile_x  The x halftile coordinate.
 * @param  halftile_y  The y halftile coordinate.
 *
 * @return 1 if hero collides, 0 if not.
 */
int fn_hero_would_collide(fn_hero_t * hero, void * level,
    int halftile_x, int halftile_y);

/* --------------------------------------------------------------- */

/**
 * Add score to our hero.
 *
 * @param  hero   The hero.
 * @param  score  The score to add.
 */
void fn_hero_add_score(fn_hero_t * hero, Uint64 score);

/* --------------------------------------------------------------- */

/**
 * Get the current score of the hero.
 *
 * @param  hero  The hero.
 *
 * @return The current score of the hero.
 */
Uint64 fn_hero_get_score(fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Increase the number of objects which can currently hurt the hero
 * because he touches them.
 *
 * @param  hero  The hero.
 */
void fn_hero_increase_hurting_objects(fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Decrease the number of objects which can currently hurt the hero
 * because he touches them.
 *
 * @param  hero  The hero.
 */
void fn_hero_decrease_hurting_objects(fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Fire a shot.
 *
 * @param  hero  The hero.
 */
void fn_hero_fire_start(fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Stop firing a shot.
 *
 * @param  hero  The hero.
 */
void fn_hero_fire_stop(fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Get the firepower that our hero currently has.
 *
 * @param  hero  The hero.
 */
Uint8 fn_hero_get_firepower(fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Get the last fetched letter.
 */
Uint8 fn_hero_get_fetched_letter(fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Set the last fetched letter.
 */
void fn_hero_set_fetched_letter(fn_hero_t * hero, Uint8 letter);

/* --------------------------------------------------------------- */

#endif /* FN_HERO_H */
