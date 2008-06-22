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

/* --------------------------------------------------------------- */

fn_shot_t * fn_shot_create(fn_level_t * level,
    Uint16 x, Uint16 y, fn_horizontal_direction_e direction)
{
  fn_shot_t * shot = malloc(sizeof(fn_shot_t));
  shot->level = level;
  shot->x = x;
  shot->y = y;
  shot->is_alive = 1;
  shot->direction = direction;
  shot->counter = 0;
  shot->countdown = 2;

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
      shot->x += FN_TILE_WIDTH;
    } else {
      shot->x -= FN_TILE_WIDTH;
    }

    GList * iter = NULL;
    fn_level_t * lv = fn_shot_get_level(shot);

    for (iter = g_list_first(lv->actors);
        iter != NULL && shot->countdown != 1;
        iter = g_list_next(iter)) {
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
          (shot->x / FN_TILE_WIDTH) + subtraction,
          (shot->y + FN_HALFTILE_HEIGHT) / FN_TILE_HEIGHT))
    {
      shot->countdown = 1;
      fn_level_add_actor(shot->level,
          FN_ACTOR_EXPLOSION,
          shot->x, shot->y);
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
    destrect.x = shot->x * pixelsize;
    destrect.y = shot->y * pixelsize;
    destrect.w = FN_TILE_WIDTH * pixelsize;
    destrect.h = FN_TILE_HEIGHT * pixelsize;
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
  return shot->x;
}

/* --------------------------------------------------------------- */

Uint16 fn_shot_get_y(fn_shot_t * shot)
{
  return shot->y;
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
  Uint16 shot_x_start = fn_shot_get_x(shot);
  Uint16 shot_y_start = fn_shot_get_y(shot);
  Uint16 shot_x_end = shot_x_start + fn_shot_get_w(shot);
  Uint16 shot_y_end = shot_y_start + fn_shot_get_h(shot);
  Uint16 actor_x_start = fn_actor_get_x(actor);
  Uint16 actor_y_start = fn_actor_get_y(actor);
  Uint16 actor_x_end = actor_x_start + fn_actor_get_w(actor);
  Uint16 actor_y_end = actor_y_start + fn_actor_get_h(actor);

  if (shot_x_end < actor_x_start) {
    /* shot is further left than actor. */
    return 0;
  }

  if (actor_x_end < shot_x_start) {
    /* shot is further right than actor */
    return 0;
  }

  if (shot_y_end < actor_y_start) {
    /* shot is above actor. */
    return 0;
  }

  if (actor_y_end < shot_y_start) {
    /* shot is below actor. */
    return 0;
  }

  return 1;
}

/* --------------------------------------------------------------- */
