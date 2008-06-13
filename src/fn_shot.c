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

  if (shot->direction == fn_horizontal_direction_right) {
    shot->x += FN_TILE_WIDTH;
  } else {
    shot->x -= FN_TILE_WIDTH;
  }
  /* TODO check if shot hits anything else */
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

