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

#include "fn_shot.h"
#include "fn_object.h"
#include "fn_collision.h"

/* --------------------------------------------------------------- */

fn_shot_t * fn_shot_create(fn_level_t * level,
    Uint16 x, Uint16 y, fn_horizontal_direction_e direction)
{
  fn_shot_t * shot = malloc(sizeof(fn_shot_t));
  shot->level = level;
  shot->position.x = x;
  shot->position.y = y;
  shot->position.w = FN_TILE_WIDTH;
  shot->position.h = FN_HALFTILE_HEIGHT / 2;
  shot->is_alive = 1;
  shot->direction = direction;
  shot->counter = 0;
  shot->countdown = 2;

  if ((shot->position.x + FN_HALFTILE_WIDTH) % FN_TILE_WIDTH) {
    shot->position.x = shot->position.x -
      ((shot->position.x + FN_HALFTILE_WIDTH) % FN_TILE_WIDTH);
  }
  if (shot->direction == fn_horizontal_direction_right) {
    shot->position.x -= FN_TILE_WIDTH;
  } else {
    shot->position.x += FN_TILE_WIDTH;
  }

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
      shot->position.x += FN_TILE_WIDTH;
    } else {
      shot->position.x -= FN_TILE_WIDTH;
    }

    fn_list_t * iter = NULL;
    fn_level_t * lv = fn_shot_get_level(shot);

    for (iter = fn_list_first(lv->actors);
        iter != NULL && shot->countdown != 1;
        iter = fn_list_next(iter)) {
      fn_actor_t * actor = (fn_actor_t *)iter->data;

      if (fn_actor_can_get_shot(actor) &&
          fn_shot_overlaps_actor(shot, actor) &&
          fn_actor_shot(actor)) {
        shot->countdown = 1;
      }
    }
  }
  if (shot->countdown == 2) {
    Uint8 subtraction =
      (shot->direction == fn_horizontal_direction_right ? 1 : 0);
    if (fn_level_is_solid(shot->level,
          (shot->position.x / FN_TILE_WIDTH) + subtraction,
          (shot->position.y + FN_HALFTILE_HEIGHT) / FN_TILE_HEIGHT))
    {
      shot->countdown = 1;
      fn_level_add_actor(shot->level,
          FN_ACTOR_EXPLOSION,
          shot->position.x, shot->position.y);
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
    SDL_Surface * tile = fn_tilecache_get_tile(tc,
        OBJ_SHOT+shot->counter);
    Uint8 pixelsize = fn_level_get_pixelsize(shot->level);
    destrect.x = shot->position.x * pixelsize;
    destrect.y = shot->position.y * pixelsize;
    destrect.w = shot->position.w * pixelsize;
    destrect.h = shot->position.h * pixelsize;
    SDL_BlitSurface(tile, NULL, target, &destrect);
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
  SDL_Rect * actorpos = fn_actor_get_pos(actor);
  return fn_collision_overlap_rect_rect(actorpos, &(shot->position));
}

/* --------------------------------------------------------------- */
