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
#include "fn_collision.h"

/* --------------------------------------------------------------- */

void fn_hero_init(
    fn_hero_t * hero,
    Uint32 x,
    Uint32 y)
{
  fn_hero_set_x(hero, x);
  fn_hero_set_y(hero, y);

  hero->direction = fn_horizontal_direction_right;
  hero->motion = FN_HERO_MOTION_NONE;
  hero->flying = FN_HERO_FLYING_FALSE;
  hero->shooting = FN_HERO_SHOOTING_FALSE;
  hero->firepower = 1;
  hero->counter = 0;
  hero->tilenr = HERO_STANDING_RIGHT;
  hero->verticalspeed = 0;

  hero->animationframe = 0;
  hero->num_animationframes = 1;

  hero->inventory = 0x00;
  hero->health = 8;

  hero->score = 0;

  hero->hidden = 0;

  hero->immunitycountdown = 0;
  hero->immunityduration = 16;
  hero->hurtingactors = NULL;
}

/* --------------------------------------------------------------- */

void fn_hero_enterlevel(
    fn_hero_t * hero,
    Uint32 x,
    Uint32 y)
{
  fn_hero_set_x(hero, x);
  fn_hero_set_y(hero, y);
  hero->direction = fn_horizontal_direction_right;
  hero->motion = FN_HERO_MOTION_NONE;
  hero->flying = FN_HERO_FLYING_FALSE;
  hero->shooting = FN_HERO_SHOOTING_FALSE;
  hero->verticalspeed = 0;

  hero->counter = 0;
  hero->tilenr = HERO_STANDING_RIGHT;

  hero->animationframe = 0;
  hero->num_animationframes = 1;

  hero->inventory &= (
      ~FN_INVENTORY_KEY_RED &
      ~FN_INVENTORY_KEY_GREEN &
      ~FN_INVENTORY_KEY_BLUE &
      ~FN_INVENTORY_KEY_PINK
      );
  hero->hidden = 0;
  hero->fetchedletter = 0;
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
  if (hero->immunitycountdown % 2 != 0) {
    return;
  }

  dstrect.x = pixelsize *
    (fn_hero_get_x(hero) - FN_HALFTILE_WIDTH);
  dstrect.y = (fn_hero_get_y(hero) - FN_TILE_HEIGHT) * pixelsize;
  dstrect.w = pixelsize * FN_TILE_WIDTH;
  dstrect.h = pixelsize * FN_TILE_HEIGHT;

  tilenr = hero->tilenr;
  if (hero->immunitycountdown > hero->immunityduration - 1) {
    if (hero->direction == fn_horizontal_direction_left) {
      tilenr = HERO_SKELETON_LEFT;
    } else {
      tilenr = HERO_SKELETON_RIGHT;
    }
  }

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

  if (hero->immunitycountdown > 0) {
    hero->immunitycountdown--;
  }
  if (hero->immunitycountdown == 0 && hero->hurtingactors != NULL) {
    hero->immunitycountdown = hero->immunityduration;
    fn_hero_set_health(hero, hero->health - 1);
  }

  if (lv == NULL) {
    return hero->health;
  }

  if (hero->motion == FN_HERO_MOTION_WALKING) {
    /* our hero is moving */
    switch(hero->direction) {
      case fn_horizontal_direction_left:
        if (!fn_hero_would_collide(hero, lv,
              fn_hero_get_x(hero) - FN_HALFTILE_WIDTH,
              fn_hero_get_y(hero)
              )) {
          fn_hero_set_x(hero, fn_hero_get_x(hero) - FN_HALFTILE_WIDTH);
          heromoved = 1;
        }
        break;
      case fn_horizontal_direction_right:
        if (!fn_hero_would_collide(hero, lv,
              fn_hero_get_x(hero) + FN_HALFTILE_WIDTH,
              fn_hero_get_y(hero)
              )) {
          /* there is no solid block left of our hero */
          fn_hero_set_x(hero, fn_hero_get_x(hero) + FN_HALFTILE_WIDTH);
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
    hero->verticalspeed = 0;
  } else {
    /* our hero is jumping or falling */
    if (hero->counter > 0) {
      /* jumping */
      hero->counter--;
      switch(hero->counter) {
        case 3:
        case 2:
          hero->verticalspeed = 1;
          break;
        case 1:
        case 0:
          hero->verticalspeed = 0;
          break;
        default:
          hero->verticalspeed = 2;
          break;

      }
      int i = 0;
      for (i = 0; i < hero->verticalspeed; i++) {
        if (!fn_hero_would_collide(hero, lv,
              fn_hero_get_x(hero),
              fn_hero_get_y(hero) - FN_HALFTILE_HEIGHT
              )) {
          fn_hero_set_y(hero, fn_hero_get_y(hero) - FN_HALFTILE_HEIGHT);
          heromoved = 1;
        } else {
          /* we bumped against the ceiling */
          hero->counter = 0;
        }
      }
    } else {
      /* falling */
      if (hero->verticalspeed != 6) {
        hero->verticalspeed++;
      }

      int i = 0;
      for (i = 0; i < hero->verticalspeed/2; i++) {
        if (!fn_hero_would_collide(hero, lv,
              fn_hero_get_x(hero),
              fn_hero_get_y(hero) + FN_HALFTILE_HEIGHT
              )) {
          fn_hero_set_y(hero, fn_hero_get_y(hero) + FN_HALFTILE_HEIGHT);
          heromoved = 1;
        }
      }
    }
  }

  if (fn_hero_would_collide(hero, lv,
        fn_hero_get_x(hero),
        fn_hero_get_y(hero) + FN_HALFTILE_HEIGHT
        )) {
    if (hero->flying == FN_HERO_FLYING_TRUE) {
      SDL_Event event;
      event.type = SDL_USEREVENT;
      event.user.code = fn_event_herolanded;
      event.user.data1 = hero;
      event.user.data2 = 0;
      SDL_PushEvent(&event);
    }
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

void fn_hero_replace(fn_hero_t * hero,
    Uint32 x, Uint32 y)
{
  fn_hero_set_x(hero, x);
  fn_hero_set_y(hero, y);
  SDL_Event event;
  event.type = SDL_USEREVENT;
  event.user.code = fn_event_heromoved;
  event.user.data1 = hero;
  event.user.data2 = 0;
  SDL_PushEvent(&event);
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
      if (hero->inventory & FN_INVENTORY_BOOT) {
        hero->counter = 7;
        hero->verticalspeed = 2;
      } else {
        hero->counter = 6;
        hero->verticalspeed = 2;
      }
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
  SDL_Event event;

  if (firepower > 4) {
    firepower = 4;
  }
  hero->firepower = firepower;

  event.type = SDL_USEREVENT;
  event.user.code = fn_event_hero_firepower_changed;
  event.user.data1 = hero;
  event.user.data2 = 0;
  SDL_PushEvent(&event);
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

void fn_hero_set_x(
    fn_hero_t * hero, Uint32 x)
{
  if (x < FN_LEVEL_WIDTH * FN_TILE_WIDTH)
  {
    hero->x = x;
  }
}

/* --------------------------------------------------------------- */

Uint32 fn_hero_get_x(
    fn_hero_t * hero)
{
  return hero->x;
}

/* --------------------------------------------------------------- */

void fn_hero_set_y(
    fn_hero_t * hero, Uint32 y)
{
  if (y < FN_LEVEL_HEIGHT * FN_TILE_HEIGHT)
  {
    hero->y = y;
  }
}

/* --------------------------------------------------------------- */

Uint32 fn_hero_get_y(
    fn_hero_t * hero)
{
  return hero->y;
}

/* --------------------------------------------------------------- */

int fn_hero_would_collide(fn_hero_t * hero, void * level,
    Uint32 x, Uint32 y)
{
  fn_level_t * lv = (fn_level_t *)level;
  if (lv == NULL) {
    return 1;
  }

  /* FIXME Trying new collision detection...
  SDL_Rect herorect;
  herorect.x = x - FN_HALFTILE_WIDTH;
  herorect.y = y - FN_HALFTILE_HEIGHT;
  herorect.w = FN_TILE_WIDTH;
  herorect.h = FN_TILE_HEIGHT * 2;

  Uint32 x_start = herorect.x / FN_TILE_WIDTH - 1;
  Uint32 y_start = herorect.y / FN_TILE_HEIGHT - 2;

  SDL_Rect solidrect;
  solidrect.w = FN_TILE_WIDTH;
  solidrect.h = FN_TILE_HEIGHT;

  int i = 0;
  int j = 0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
      if (fn_level_is_solid(lv,
            x_start + i,
            y_start + j)) {
        solidrect.x = (x_start + i) * FN_TILE_WIDTH;
        solidrect.y = (y_start + i) * FN_TILE_HEIGHT;

        if (fn_collision_rect(&herorect, &solidrect)) {
          return 1;
        }
      }
    }
  }
  return 0;
  */

  if (x < 0 || x > FN_LEVEL_WIDTH * FN_TILE_WIDTH ||
      y < 0 || y > FN_LEVEL_HEIGHT * FN_TILE_HEIGHT) {
    return 1;
  }
  Uint32 i = 0;
  Uint32 j = 0;

  for (i = x; i < x + FN_TILE_WIDTH; i += FN_HALFTILE_WIDTH) {
    for (j = y-FN_TILE_HEIGHT; j < y+FN_TILE_HEIGHT; j++) {
      if (fn_level_is_solid(lv, i/FN_TILE_WIDTH, j/FN_TILE_HEIGHT)) {
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

void fn_hero_increase_hurting_actors(fn_hero_t * hero,
    fn_actor_t * actor)
{
  hero->hurtingactors = fn_list_append(hero->hurtingactors,
      actor);
}

/* --------------------------------------------------------------- */

void fn_hero_decrease_hurting_actors(fn_hero_t * hero,
    fn_actor_t * actor)
{
  hero->hurtingactors = fn_list_remove_all(hero->hurtingactors,
      actor);
}

/* --------------------------------------------------------------- */

void fn_hero_fire_start(fn_hero_t * hero)
{
  fn_hero_set_shooting(hero, FN_HERO_SHOOTING_TRUE);
}

/* --------------------------------------------------------------- */

void fn_hero_fire_stop(fn_hero_t * hero)
{
  fn_hero_set_shooting(hero, FN_HERO_SHOOTING_FALSE);
}

/* --------------------------------------------------------------- */

Uint8 fn_hero_get_firepower(fn_hero_t * hero)
{
  return hero->firepower;
}

/* --------------------------------------------------------------- */

Uint8 fn_hero_get_fetched_letter(fn_hero_t * hero)
{
  return hero->fetchedletter;
}

/* --------------------------------------------------------------- */

void fn_hero_set_fetched_letter(fn_hero_t * hero, Uint8 letter)
{
  hero->fetchedletter = letter;
}

/* --------------------------------------------------------------- */
