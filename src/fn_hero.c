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

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_hero.h"
#include "fn_object.h"
#include "fn.h"
#include "fn_level.h"

/* --------------------------------------------------------------- */

void fn_hero_init(
    fn_hero_t * hero,
    Uint16 x,
    Uint16 y)
{
  hero->x = x;
  hero->y = y;

  hero->direction = fn_horizontal_direction_right;
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

  hero->score = 0;

  hero->hidden = 0;
}

/* --------------------------------------------------------------- */

void fn_hero_blit(fn_hero_t * hero,
    SDL_Surface * target,
    fn_tilecache_t * tilecache,
    Uint8 pixelsize)
{
  SDL_Rect dstrect;
  int tilenr;
  SDL_Surface * tile;

  if (hero->hidden) {
    return;
  }

  dstrect.x = FN_HALFTILE_WIDTH * pixelsize * (hero->x - 1);
  dstrect.y = (FN_HALFTILE_HEIGHT * hero->y - FN_TILE_HEIGHT) *
    pixelsize;
  dstrect.w = pixelsize * FN_TILE_WIDTH;
  dstrect.h = pixelsize * FN_TILE_HEIGHT;

  tilenr = hero->tilenr;

  tile = fn_tilecache_get_tile(tilecache, tilenr);
  SDL_BlitSurface(tile, NULL, target, &dstrect);

  dstrect.x += dstrect.w;
  tile = fn_tilecache_get_tile(tilecache, tilenr+1);
  SDL_BlitSurface(tile, NULL, target, &dstrect);

  dstrect.x -= dstrect.w;
  dstrect.y += dstrect.h;
  tile = fn_tilecache_get_tile(tilecache, tilenr+2);
  SDL_BlitSurface(tile, NULL, target, &dstrect);

  dstrect.x += dstrect.w;
  tile = fn_tilecache_get_tile(tilecache, tilenr+3);
  SDL_BlitSurface(tile, NULL, target, &dstrect);
}

/* --------------------------------------------------------------- */

int fn_hero_act(
    fn_hero_t * hero,
    void * data)
{
  fn_level_t * lv = (fn_level_t *)data;
  int heromoved = 0;

  if (lv == NULL) {
    return hero->health;
  }
  /* TODO */
  if (hero->motion == FN_HERO_MOTION_WALKING) {
    /* our hero is moving */
    switch(hero->direction) {
      case fn_horizontal_direction_left:
        if (!fn_hero_would_collide(hero, lv, hero->x-1, hero->y)) {
          hero->x--;
          heromoved = 1;
        }
        break;
      case fn_horizontal_direction_right:
        if (!fn_hero_would_collide(hero, lv, hero->x+1, hero->y)) {
          /* there is no solid block left of our hero */
          hero->x++;
          heromoved = 1;
        }
        break;
      default:
        /* do nothing else */
        break;
    }
  }

  if (hero->flying == FN_HERO_FLYING_FALSE) {
    /* our hero is standing or walking */
  } else {
    /* our hero is jumping or falling */
    if (hero->counter > 0) {
      /* jumping */
      hero->counter--;
      if (!fn_hero_would_collide(hero, lv, hero->x, hero->y-1)) {
        hero->y--;
        heromoved = 1;
      } else {
        /* we bumped against the ceiling */
        hero->counter = 0;
      }
    } else {
      /* falling */
      if (!fn_hero_would_collide(hero, lv, hero->x, hero->y+1)) {
        hero->y++;
        heromoved = 1;
      }
    }
  }

  if (fn_hero_would_collide(hero, lv, hero->x, hero->y+1)) {
    /* we are standing on solid ground */
    fn_hero_set_flying(hero, FN_HERO_FLYING_FALSE);
    hero->counter = 0;
  } else {
    /* we fall down */
    if (hero->counter == 0) {
      fn_hero_set_flying(hero, FN_HERO_FLYING_TRUE);
      hero->counter = 0;
    }
  }

  if (heromoved) {
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = fn_event_heromoved;
    event.user.data1 = hero;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
  }

  return hero->health;
}

/* --------------------------------------------------------------- */

void fn_hero_next_animationframe(
    fn_hero_t * hero)
{
  hero->animationframe++;
  hero->animationframe %= hero->num_animationframes;
  /*
  if (hero->counter > 0) {
    hero->counter--;
  }
  */
}

/* --------------------------------------------------------------- */

void fn_hero_update_animation(
    fn_hero_t * hero)
{
  if (hero->flying == FN_HERO_FLYING_FALSE) {

    /* hero is standing or walking on ground */
    if (hero->motion == FN_HERO_MOTION_NONE) {

      /* hero is standing */
      if (hero->direction == fn_horizontal_direction_left) {
        if (hero->shooting == FN_HERO_SHOOTING_TRUE) {
          hero->tilenr = HERO_WALKING_LEFT + 12;
        } else {
          hero->tilenr = HERO_STANDING_LEFT;
        }
      } else {
        if (hero->shooting == FN_HERO_SHOOTING_TRUE) {
          hero->tilenr = HERO_WALKING_RIGHT + 12;
        } else {
          hero->tilenr = HERO_STANDING_RIGHT;
        }
      }
      hero->num_animationframes = HERO_NUM_ANIM_STANDING;

    } else {

      /* hero is walking */
      if (hero->direction == fn_horizontal_direction_left) {
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
      if (hero->direction == fn_horizontal_direction_left) {
        hero->tilenr = HERO_JUMPING_LEFT;
      } else {
        hero->tilenr = HERO_JUMPING_RIGHT;
      }
      hero->num_animationframes = HERO_NUM_ANIM_JUMPING;

    } else {

      /* hero is falling */
      if (hero->direction == fn_horizontal_direction_left) {
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
    fn_horizontal_direction_e direction)
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
  if (flying == FN_HERO_FLYING_TRUE) {
    if (hero->flying != flying) {
      hero->counter = 6;
    }
  }
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
    Uint8 inventory)
{
  SDL_Event event;
  hero->inventory = inventory;
  event.type = SDL_USEREVENT;
  event.user.code = fn_event_hero_inventory_changed;
  event.user.data1 = hero;
  event.user.data2 = 0;
  SDL_PushEvent(&event);
}

/* --------------------------------------------------------------- */

Uint8 fn_hero_get_inventory(fn_hero_t * hero)
{
  return hero->inventory;
}

/* --------------------------------------------------------------- */
void fn_hero_improve_health(fn_hero_t * hero, Uint8 improvement)
{
  fn_hero_set_health(hero, hero->health + improvement);
}

/* --------------------------------------------------------------- */

Uint8 fn_hero_get_health(fn_hero_t * hero)
{
  return hero->health;
}

/* --------------------------------------------------------------- */

void fn_hero_set_health(fn_hero_t * hero, Uint8 health)
{
  SDL_Event event;
  hero->health = health;
  if (hero->health > 8) {
    hero->health = 8;
  }
  event.type = SDL_USEREVENT;
  event.user.code = fn_event_hero_health_changed;
  event.user.data1 = hero;
  event.user.data2 = 0;
  SDL_PushEvent(&event);
}

/* --------------------------------------------------------------- */

void fn_hero_jump(
    fn_hero_t * hero)
{
  fn_hero_set_counter(hero, 6);
  fn_hero_set_flying(hero, FN_HERO_FLYING_TRUE);
}

/* --------------------------------------------------------------- */

Uint16 fn_hero_get_x(
    fn_hero_t * hero)
{
  return hero->x;
}

/* --------------------------------------------------------------- */

Uint16 fn_hero_get_y(
    fn_hero_t * hero)
{
  return hero->y;
}

/* --------------------------------------------------------------- */

int fn_hero_would_collide(fn_hero_t * hero, void * level,
    int halftile_x, int halftile_y)
{
  fn_level_t * lv = (fn_level_t *)level;
  if (lv == NULL) {
    return 1;
  }
  if (halftile_x < 0 || halftile_x > FN_LEVEL_WIDTH * 2 ||
      halftile_y < 0 || halftile_y > FN_LEVEL_HEIGHT * 2) {
    return 1;
  }
  int i = 0;
  int j = 0;

  for (i = halftile_x; i < halftile_x + 2; i++) {
    for (j = halftile_y-2; j < halftile_y+2; j++) {
      if (fn_level_is_solid(lv, i/2, j/2)) {
        return 1;
      }
    }
  }

  return 0;
}

/* --------------------------------------------------------------- */

void fn_hero_add_score(fn_hero_t * hero, Uint64 score)
{
  SDL_Event event;

  hero->score += score;

  event.type = SDL_USEREVENT;
  event.user.code = fn_event_heroscored;
  event.user.data1 = hero;
  event.user.data2 = 0;
  SDL_PushEvent(&event);
}

/* --------------------------------------------------------------- */

Uint64 fn_hero_get_score(fn_hero_t * hero)
{
  return hero->score;
}

/* --------------------------------------------------------------- */

void fn_hero_increase_hurting_objects(fn_hero_t * hero)
{
  fn_hero_set_health(hero, hero->health - 1);
}

/* --------------------------------------------------------------- */

void fn_hero_decrease_hurting_objects(fn_hero_t * hero)
{
}

/* --------------------------------------------------------------- */

void fn_hero_fire_start(fn_hero_t * hero)
{
  printf("Starting fire.\n");
  fn_hero_set_shooting(hero, FN_HERO_SHOOTING_TRUE);
}

/* --------------------------------------------------------------- */

void fn_hero_fire_stop(fn_hero_t * hero)
{
  printf("Stopping fire.\n");
  fn_hero_set_shooting(hero, FN_HERO_SHOOTING_FALSE);
}

/* --------------------------------------------------------------- */

Uint8 fn_hero_get_firepower(fn_hero_t * hero)
{
  return hero->firepower;
}

/* --------------------------------------------------------------- */
