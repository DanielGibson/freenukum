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

#include <SDL/SDL.h>

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

typedef struct fn_hero_t {
  Uint8 direction;
  Uint8 motion;
  Uint8 flying;
  Uint8 shooting;
  Uint8 firepower;
  Uint8 counter;

  Uint8 animationframe;
  Uint8 num_animationframes;

  Uint8 inventory;
  Uint8 health;
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

void fn_hero_init(
    fn_hero_t * hero);

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

#endif /* FN_HERO_H */