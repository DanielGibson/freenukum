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

void fn_hero_init(
    fn_hero_t * hero,
    Uint16 x,
    Uint16 y)
{
  hero->x = x;
  hero->y = y;

  hero->direction = FN_HERO_DIRECTION_RIGHT;
  hero->motion = FN_HERO_MOTION_NONE;
  hero->flying = FN_HERO_FLYING_FALSE;
  hero->shooting = FN_HERO_SHOOTING_FALSE;
  hero->firepower = 1;
  hero->counter = 0;
  hero->tilenr = HERO_STANDING_RIGHT;

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
  SDL_Rect dstrect;
  int i;
  int tilenr;

  dstrect.x = FN_HALFTILE_WIDTH * pixelsize * hero->x;
  dstrect.y = FN_HALFTILE_HEIGHT * pixelsize * hero->y;
  dstrect.w = pixelsize * FN_PART_WIDTH;
  dstrect.h = pixelsize * FN_PART_HEIGHT;

  tilenr = hero->tilenr;

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
  if (hero->counter > 0) {
    hero->counter--;
  }
}

/* --------------------------------------------------------------- */

void fn_hero_update_animation(
    fn_hero_t * hero)
{
  if (hero->flying == FN_HERO_FLYING_FALSE) {

    /* hero is standing or walking on ground */
    if (hero->motion == FN_HERO_MOTION_NONE) {

      /* hero is standing */
      if (hero->direction == FN_HERO_DIRECTION_LEFT) {
        hero->tilenr = HERO_STANDING_LEFT;
      } else {
        hero->tilenr = HERO_STANDING_RIGHT;
      }
      hero->num_animationframes = HERO_NUM_ANIM_STANDING;

    } else {

      /* hero is walking */
      if (hero->direction == FN_HERO_DIRECTION_LEFT) {
        hero->tilenr = HERO_WALKING_LEFT + 4 * hero->animationframe;
      } else {
        hero->tilenr = HERO_WALKING_RIGHT + 4 * hero->animationframe;
      }
      hero->num_animationframes = HERO_NUM_ANIM_WALKING;
    }

  } else {

    /* hero is jumping or falling */
    if (hero->counter > 0) {

      /* hero is jumping */
      if (hero->direction == FN_HERO_DIRECTION_LEFT) {
        hero->tilenr = HERO_JUMPING_LEFT;
      } else {
        hero->tilenr = HERO_JUMPING_RIGHT;
      }
      hero->num_animationframes = HERO_NUM_ANIM_JUMPING;

    } else {

      /* hero is falling */
      if (hero->direction == FN_HERO_DIRECTION_LEFT) {
        hero->tilenr = HERO_FALLING_LEFT;
      } else {
        hero->tilenr = HERO_FALLING_RIGHT;
      }
      hero->num_animationframes = HERO_NUM_ANIM_FALLING;

    }
  }

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

void fn_hero_jump(
    fn_hero_t * hero)
{
  fn_hero_set_counter(hero, 6);
  fn_hero_set_flying(hero, FN_HERO_FLYING_TRUE);
}

/* --------------------------------------------------------------- */
