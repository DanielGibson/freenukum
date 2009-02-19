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

#include <stdlib.h>

/* --------------------------------------------------------------- */

#include "fn_shot.h"
#include "fn_object.h"
#include "fn_collision.h"

/* --------------------------------------------------------------- */

fn_shot_t * fn_shot_create(fn_level_t * level,
    Uint16 x, Uint16 y, fn_horizontal_direction_e direction)
{
  fn_shot_t * shot = malloc(sizeof(fn_shot_t));
  shot->level = level;
  shot->position.w = 4;
  shot->position.h = FN_TILE_HEIGHT - 4;

  shot->position.x = x + FN_HALFTILE_WIDTH - shot->position.w / 2;
  shot->position.y = y + FN_TILE_HEIGHT - shot->position.h;
  shot->is_alive = 1;
  shot->direction = direction;
  shot->counter = 0;
  shot->countdown = 2;
  shot->draw_collision_bounds = 0;

  return shot;
}

/* --------------------------------------------------------------- */

void fn_shot_free(fn_shot_t * shot)
{
  free(shot);
}

/* --------------------------------------------------------------- */

Uint8 fn_shot_act(fn_shot_t * shot)
{
  shot->counter++;
  shot->counter %= 4;

  if (shot->countdown == 1) {
    shot->countdown--;
    shot->is_alive = 0;
  }

  if (shot->countdown == 2) {
    if (shot->direction == fn_horizontal_direction_right) {
      /* push twice so that every position gets covered. */
      fn_shot_push(shot, FN_HALFTILE_WIDTH);
      fn_shot_push(shot, FN_HALFTILE_WIDTH);
    } else {
      /* push twice so that every position gets covered. */
      fn_shot_push(shot, -FN_HALFTILE_WIDTH);
      fn_shot_push(shot, -FN_HALFTILE_WIDTH);
    }
  }
  return shot->is_alive;
}

/* --------------------------------------------------------------- */

void fn_shot_blit(fn_shot_t * shot)
{
  if (shot->is_alive) {
    SDL_Surface * target = fn_level_get_surface(shot->level);
    SDL_Rect destrect;
    fn_tilecache_t * tc = fn_level_get_tilecache(shot->level);
    FnTile * tile = fn_tilecache_get_tile(tc,
        OBJ_SHOT+shot->counter);
    Uint8 pixelsize = fn_level_get_pixelsize(shot->level);
    destrect.x =
      (shot->position.x + shot->position.w / 2 - FN_HALFTILE_WIDTH) *
      pixelsize;
    destrect.y = shot->position.y * pixelsize;
    destrect.w = FN_TILE_WIDTH * pixelsize;
    destrect.h = shot->position.h * pixelsize;
    fn_tile_blit_to_sdl_surface(tile, NULL, target, &destrect);

    if (shot->draw_collision_bounds) {
      fn_collision_rect_draw(target, pixelsize, &(shot->position));
    }
  }
}

/* --------------------------------------------------------------- */

void fn_shot_gets_out_of_sight(fn_shot_t * shot)
{
  shot->is_alive = 0;
}

/* --------------------------------------------------------------- */

Uint16 fn_shot_get_x(fn_shot_t * shot)
{
  return shot->position.x;
}

/* --------------------------------------------------------------- */

Uint16 fn_shot_get_y(fn_shot_t * shot)
{
  return shot->position.y;
}

/* --------------------------------------------------------------- */

Uint16 fn_shot_get_w(fn_shot_t * shot)
{
  return FN_TILE_WIDTH;
}

/* --------------------------------------------------------------- */

Uint16 fn_shot_get_h(fn_shot_t * shot)
{
  return FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

fn_level_t * fn_shot_get_level(fn_shot_t * shot)
{
  return shot->level;
}

/* --------------------------------------------------------------- */

Uint8 fn_shot_overlaps_actor(fn_shot_t * shot, fn_actor_t * actor)
{
  SDL_Rect * actorpos = fn_actor_get_position(actor);
  return fn_collision_overlap_rect_rect(actorpos, &(shot->position));
}

/* --------------------------------------------------------------- */

Uint8 fn_shot_touches_actor(fn_shot_t * shot, fn_actor_t * actor)
{
  SDL_Rect * actorpos = fn_actor_get_position(actor);
  return fn_collision_touch_rect_rect(actorpos, &(shot->position));
}

/* --------------------------------------------------------------- */

void fn_shot_set_draw_collision_bounds(
    fn_shot_t * shot, Uint8 enable)
{
  shot->draw_collision_bounds = enable;
}

/* --------------------------------------------------------------- */

Uint8 fn_shot_hits_solid(
    fn_shot_t * shot)
{
  return fn_level_solid_collides(shot->level, &(shot->position));
}

/* --------------------------------------------------------------- */

void fn_shot_push(fn_shot_t * shot, Sint16 offset)
{
  if (shot->countdown == 2) {
    shot->position.x += offset;
    fn_list_t * iter = NULL;
    for (iter = fn_list_first(shot->level->actors);
        iter != NULL && shot->countdown != 1;
        iter = fn_list_next(iter)) {
      fn_actor_t * actor = (fn_actor_t *)iter->data;

      if (fn_actor_can_get_shot(actor) &&
          fn_shot_touches_actor(shot, actor) &&
          fn_actor_shot(actor)) {
        shot->countdown = 1;
      }
    }
  }
  if (shot->countdown == 2) {
    if (fn_shot_hits_solid(shot)) {
      shot->countdown = 1;

      fn_level_add_actor(shot->level,
          FN_ACTOR_EXPLOSION,
          shot->position.x + shot->position.w / 2 - FN_HALFTILE_WIDTH,
          shot->position.y);
    }
  }
}

/* --------------------------------------------------------------- */

Uint8 fn_shot_is_alive(fn_shot_t * shot)
{
  return shot->countdown == 2;
}

/* --------------------------------------------------------------- */

SDL_Rect * fn_shot_get_position(fn_shot_t * shot)
{
  return &(shot->position);
}

/* --------------------------------------------------------------- */

