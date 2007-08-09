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

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn_hero.h"
#include "fn_object.h"
#include "fn.h"

/* --------------------------------------------------------------- */

//static fn_hero_changed_f handler_direction_changed = NULL;
//static fn_hero_changed_f handler_motion_changed = NULL;
//static fn_hero_changed_f handler_flying_changed = NULL;
//static fn_hero_changed_f handler_shooting_changed = NULL;
//static fn_hero_changed_f handler_firepower_changed = NULL;
//static fn_hero_changed_f handler_counter_changed = NULL;
//static fn_hero_changed_f handler_inventory_changed = NULL;

/* --------------------------------------------------------------- */

void fn_hero_init(
    fn_hero_t * hero)
{
  hero->direction = FN_HERO_DIRECTION_RIGHT;
  hero->motion = FN_HERO_MOTION_NONE;
  hero->flying = FN_HERO_FLYING_FALSE;
  hero->shooting = FN_HERO_SHOOTING_FALSE;
  hero->firepower = 1;
  hero->counter = 0;

  hero->animationframe = 0;
  hero->num_animationframes = 1;

  hero->inventory = 0x00;
  hero->health = 8;
}

/* --------------------------------------------------------------- */

void fn_hero_blit(fn_hero_t * hero,
    SDL_Surface * target,
    fn_tilecache_t * tilecache,
    Uint8 pixelsize)
{
  int tilenr;
  SDL_Rect dstrect;
  int i;

  if (hero->flying == FN_HERO_FLYING_FALSE) {

    /* hero is standing or walking on ground */
    if (hero->motion == FN_HERO_MOTION_NONE) {

      /* hero is standing */
      if (hero->direction == FN_HERO_DIRECTION_LEFT) {
        tilenr = HERO_STANDING_LEFT;
      } else {
        tilenr = HERO_STANDING_RIGHT;
      }

    } else {

      /* hero is walking */
      if (hero->direction == FN_HERO_DIRECTION_LEFT) {
        tilenr = HERO_WALKING_LEFT + 4 * hero->animationframe;
      } else {
        tilenr = HERO_WALKING_RIGHT + 4 * hero->animationframe;
      }
    }

  } else {

    /* hero is jumping or falling */
    if (hero->counter > 0) {

      /* hero is jumping */
      if (hero->direction == FN_HERO_DIRECTION_LEFT) {
        tilenr = HERO_JUMPING_LEFT;
      } else {
        tilenr = HERO_JUMPING_RIGHT;
      }

    } else {

      /* hero is falling */
      if (hero->direction == FN_HERO_DIRECTION_LEFT) {
        tilenr = HERO_FALLING_LEFT;
      } else {
        tilenr = HERO_FALLING_RIGHT;
      }

    }
  }

  dstrect.x = 0;
  dstrect.y = 0;
  dstrect.w = pixelsize * FN_PART_WIDTH;
  dstrect.h = pixelsize * FN_PART_HEIGHT;
  for (i = 0; i < 4; i++) {
    SDL_Surface * tile;
    tile = fn_tilecache_gettile(tilecache, tilenr+i);
    SDL_BlitSurface(tile, NULL, target, &dstrect);
    dstrect.x += dstrect.w;
    dstrect.x %= dstrect.w * 2;
    if (dstrect.x == 0)
      dstrect.y += dstrect.h;
  }
}

/* --------------------------------------------------------------- */

void fn_hero_next_animationframe(
    fn_hero_t * hero)
{
  hero->animationframe++;
  hero->animationframe %= hero->num_animationframes;
}

/* --------------------------------------------------------------- */

void fn_hero_set_direction(
    fn_hero_t * hero,
    Uint8 direction)
{
  hero->direction = direction;
}

/* --------------------------------------------------------------- */

void fn_hero_set_motion(
    fn_hero_t * hero,
    Uint8 motion)
{
  hero->motion = motion;
  if (hero->flying == FN_HERO_FLYING_TRUE) {
    hero->num_animationframes = HERO_NUM_ANIM_WALKING;
  } else {
    hero->num_animationframes = HERO_NUM_ANIM_STANDING;
  }
}

/* --------------------------------------------------------------- */

void fn_hero_set_flying(
    fn_hero_t * hero,
    Uint8 flying)
{
  hero->flying = flying;
}

/* --------------------------------------------------------------- */

void fn_hero_set_shooting(
    fn_hero_t * hero,
    Uint8 shooting)
{
  hero->shooting = shooting;
}

/* --------------------------------------------------------------- */

void fn_hero_set_firepower(
    fn_hero_t * hero,
    Uint8 firepower)
{
  hero->firepower = firepower;
}

/* --------------------------------------------------------------- */

void fn_hero_set_counter(
    fn_hero_t * hero,
    Uint8 counter)
{
  hero->counter = counter;
}

/* --------------------------------------------------------------- */

void fn_hero_set_inventory(
    fn_hero_t * hero,
    Uint8 health)
{
  hero->health = health;
}

/* --------------------------------------------------------------- */
