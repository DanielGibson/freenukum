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
#include <assert.h>

/* --------------------------------------------------------------- */

#include "fn_hero.h"
#include "fn_object.h"
#include "fn.h"
#include "fn_level.h"
#include "fn_collision.h"

/* --------------------------------------------------------------- */

fn_hero_t * fn_hero_create(fn_environment_t * env)
{
  fn_hero_t * hero = malloc(sizeof(fn_hero_t));

  assert(env != NULL);
  hero->env = env;
  fn_hero_reset(hero);

  return hero;
}

/* --------------------------------------------------------------- */

void fn_hero_delete(fn_hero_t * hero)
{
  free(hero); hero = NULL;
}

/* --------------------------------------------------------------- */

void fn_hero_reset(fn_hero_t * hero)
{
  fn_hero_set_x(hero, 0);
  fn_hero_set_y(hero, 0);

  hero->position.w = FN_TILE_WIDTH;
  hero->position.h = FN_TILE_HEIGHT * 2;

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

  hero->turned_around = 0;

  hero->is_moving_horizontally = 0;
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

  Uint8 inventory = fn_hero_get_inventory(hero);
  inventory &= (
      ~FN_INVENTORY_KEY_RED &
      ~FN_INVENTORY_KEY_GREEN &
      ~FN_INVENTORY_KEY_BLUE &
      ~FN_INVENTORY_KEY_PINK
      );
  fn_hero_set_inventory(hero, inventory);
  hero->hidden = 0;
  hero->fetchedletter = 0;
}

/* --------------------------------------------------------------- */

void fn_hero_blit(fn_hero_t * hero,
    SDL_Surface * target,
    fn_level_t * level)
{
  SDL_Rect dstrect;
  int tilenr;
  FnTexture * tile;

  if (hero->hidden) {
    return;
  }
  if (hero->immunitycountdown % 2 != 0) {
    return;
  }

  fn_environment_t * env = hero->env;
  Uint8 pixelsize = fn_environment_get_pixelsize(env);

  dstrect.x = pixelsize * (fn_hero_get_x(hero) - FN_HALFTILE_WIDTH);
  dstrect.y = pixelsize * fn_hero_get_y(hero);
  dstrect.w = pixelsize * fn_hero_get_w(hero);
  dstrect.h = pixelsize * fn_hero_get_h(hero);

  tilenr = hero->tilenr;
  if (hero->immunitycountdown > hero->immunityduration - 1) {
    if (hero->direction == fn_horizontal_direction_left) {
      tilenr = HERO_SKELETON_LEFT;
    } else {
      tilenr = HERO_SKELETON_RIGHT;
    }
  }

  tile = fn_environment_get_tile(env, tilenr);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &dstrect);

  dstrect.x += dstrect.w;
  tile = fn_environment_get_tile(env, tilenr+1);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &dstrect);

  dstrect.x -= dstrect.w;
  dstrect.y += dstrect.h;
  tile = fn_environment_get_tile(env, tilenr+2);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &dstrect);

  dstrect.x += dstrect.w;
  tile = fn_environment_get_tile(env, tilenr+3);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &dstrect);

  if (fn_environment_get_draw_collision_bounds(env)) {
    fn_collision_rect_draw(target, pixelsize, &(hero->position));

    Uint16 i = 0;
    Uint16 j = 0;

    for (i = hero->position.x - FN_TILE_WIDTH;
        i < hero->position.x + FN_TILE_WIDTH * 2;
        i += FN_TILE_WIDTH) {
      for (j = hero->position.y - FN_TILE_HEIGHT;
          j < hero->position.y + FN_TILE_HEIGHT * 3;
          j += FN_TILE_HEIGHT) {
        Uint16 tile_x = i / FN_TILE_WIDTH;
        Uint16 tile_y = j / FN_TILE_HEIGHT;
        if (level != NULL) {
          if (fn_level_is_solid(level, tile_x, tile_y))
          {
            SDL_Rect obstacle;
            obstacle.x = tile_x * FN_TILE_WIDTH;
            obstacle.y = tile_y * FN_TILE_HEIGHT;
            obstacle.w = FN_TILE_WIDTH;
            obstacle.h = FN_TILE_HEIGHT;

            fn_collision_rect_draw(target, pixelsize, &obstacle);
          }
        }
      }
    }
  }
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
    if (hero->turned_around) {
      hero->turned_around = 0;
    } else {
      switch(hero->direction) {
        case fn_horizontal_direction_left:
          if (!fn_hero_would_collide(hero, lv,
                fn_hero_get_x(hero) - FN_HALFTILE_WIDTH,
                fn_hero_get_y(hero)
                )) {
            fn_hero_set_x(hero, fn_hero_get_x(hero) - FN_HALFTILE_WIDTH);
            heromoved = 1;
            hero->is_moving_horizontally = 1;
          } else {
            hero->is_moving_horizontally = 0;
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
            hero->is_moving_horizontally = 1;
          } else {
            hero->is_moving_horizontally = 0;
          }
          break;
        default:
          /* do nothing else */
          break;
      }
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
  if (hero->direction != direction) {
    hero->turned_around = 1;
    hero->direction = direction;
  }
}

/* --------------------------------------------------------------- */

void fn_hero_set_motion(
    fn_hero_t * hero,
    Uint8 motion)
{
  hero->motion = motion;
}

/* --------------------------------------------------------------- */

Uint8 fn_hero_is_moving_horizontally(
    fn_hero_t * hero)
{
  return hero->is_moving_horizontally;
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
    hero->position.x = x;
  }
}

/* --------------------------------------------------------------- */

Uint32 fn_hero_get_x(
    fn_hero_t * hero)
{
  return hero->position.x;
}

/* --------------------------------------------------------------- */

void fn_hero_set_y(
    fn_hero_t * hero, Uint32 y)
{
  if (y < FN_LEVEL_HEIGHT * FN_TILE_HEIGHT)
  {
    hero->position.y = y;
  }
}

/* --------------------------------------------------------------- */

Uint32 fn_hero_get_y(
    fn_hero_t * hero)
{
  return hero->position.y;
}

/* --------------------------------------------------------------- */

Uint16 fn_hero_get_w(
    fn_hero_t * hero)
{
  return hero->position.w;
}

/* --------------------------------------------------------------- */

Uint16 fn_hero_get_h(
    fn_hero_t * hero)
{
  return hero->position.h;
}

/* --------------------------------------------------------------- */

int fn_hero_would_collide(fn_hero_t * hero, void * level,
    Uint32 x, Uint32 y)
{
  fn_level_t * lv = (fn_level_t *)level;
  if (lv == NULL) {
    return 1;
  }

  SDL_Rect herorect;
  herorect.x = x;
  herorect.y = y;
  herorect.w = hero->position.w;
  herorect.h = hero->position.h;

  Uint16 i = 0;
  Uint16 j = 0;

  for (i = x - FN_TILE_WIDTH;
      i < x + FN_TILE_WIDTH * 2;
      i += FN_TILE_WIDTH) {
    for (j = y - FN_TILE_HEIGHT;
        j < y + FN_TILE_HEIGHT * 3;
        j += FN_TILE_HEIGHT) {
      Uint16 tile_x = i / FN_TILE_WIDTH;
      Uint16 tile_y = j / FN_TILE_HEIGHT;
      if (fn_level_is_solid(lv, tile_x, tile_y))
      {
        SDL_Rect obstacle;
        obstacle.x = tile_x * FN_TILE_WIDTH;
        obstacle.y = tile_y * FN_TILE_HEIGHT;
        obstacle.w = FN_TILE_WIDTH;
        obstacle.h = FN_TILE_HEIGHT;

        if (fn_collision_overlap_rect_rect(&herorect, &obstacle)) {
          return 1;
        }
      }
    }
  }
  return 0;

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
    fn_level_actor_t * actor)
{
  hero->hurtingactors = fn_list_append(hero->hurtingactors,
      actor);
}

/* --------------------------------------------------------------- */

void fn_hero_decrease_hurting_actors(fn_hero_t * hero,
    fn_level_actor_t * actor)
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

SDL_Rect * fn_hero_get_position(fn_hero_t * hero)
{
  return &(hero->position);
}

/* --------------------------------------------------------------- */

Sint8 fn_hero_push_horizontally(
    fn_hero_t * hero, fn_level_t * level, Sint8 offset)
{
  if (offset == 0) {
    return 0;
  }
  hero->position.x += offset;

  if (!fn_hero_collides_with_solid(hero, level)) {
    /* no solids in the way */
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = fn_event_heromoved;
    event.user.data1 = hero;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
    return offset;
  }

  /* there was a solid in the way */
  Uint8 offset_abs = (offset < 0 ? -offset : offset);
  Sint8 direction = offset / offset_abs;

  Uint8 i = 0;
  for (i = 0; i < offset_abs; i++) {
    hero->position.x -= direction;
    if (!fn_hero_collides_with_solid(hero, level)) {
      SDL_Event event;
      event.type = SDL_USEREVENT;
      event.user.code = fn_event_heromoved;
      event.user.data1 = hero;
      event.user.data2 = 0;
      SDL_PushEvent(&event);
      return i * direction;
    }
  }
  return 0;
}

/* --------------------------------------------------------------- */

Sint8 fn_hero_push_vertically(
    fn_hero_t * hero, fn_level_t * level, Sint8 offset)
{
  if (offset == 0) {
    return 0;
  }
  hero->position.y += offset;

  if (!fn_hero_collides_with_solid(hero, level)) {
    /* no solids in the way */
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = fn_event_heromoved;
    event.user.data1 = hero;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
    return offset;
  }

  /* there was a solid in the way */
  Uint8 offset_abs = (offset < 0 ? -offset : offset);
  Sint8 direction = offset / offset_abs;

  Uint8 i = 0;
  for (i = 0; i < offset_abs; i++) {
    hero->position.y -= direction;
    if (!fn_hero_collides_with_solid(hero, level)) {
      SDL_Event event;
      event.type = SDL_USEREVENT;
      event.user.code = fn_event_heromoved;
      event.user.data1 = hero;
      event.user.data2 = 0;
      SDL_PushEvent(&event);
      return i * direction;
    }
  }
  return 0;
}

/* --------------------------------------------------------------- */

int fn_hero_collides_with_solid(fn_hero_t * hero, fn_level_t * level)
{
  SDL_Rect * pos = fn_hero_get_position(hero);
  Uint16 i = 0;
  Uint16 j = 0;
  for (i = pos->x - FN_TILE_WIDTH;
      i < pos->x + FN_TILE_WIDTH * 2;
      i += FN_TILE_WIDTH) {
    for (j = pos->y - FN_TILE_HEIGHT;
        j < pos->y + FN_TILE_HEIGHT * 3;
        j += FN_TILE_HEIGHT) {
      Uint16 tile_x = i / FN_TILE_WIDTH;
      Uint16 tile_y = j / FN_TILE_HEIGHT;
      if (fn_level_is_solid(level, tile_x, tile_y))
      {
        SDL_Rect obstacle;
        obstacle.x = tile_x * FN_TILE_WIDTH;
        obstacle.y = tile_y * FN_TILE_HEIGHT;
        obstacle.w = FN_TILE_WIDTH;
        obstacle.h = FN_TILE_HEIGHT;

        if (fn_collision_overlap_rect_rect(
              pos, &obstacle)) {
          return 1;
        }
      }
    }
  }
  return 0;
}

/* --------------------------------------------------------------- */

