/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Animation struct
 *
 * *****************************************************************
 *
 * Copyright 2008 Wolfgang Silbermayr
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

#include "fn.h"
#include "fn_animation.h"

/* --------------------------------------------------------------- */

fn_animation_t * fn_animation_create(
    size_t num_frames,
    SDL_Surface ** frames,
    size_t startframe,
    Uint16 x,
    Uint16 y,
    size_t pixelsize)
{
  fn_animation_t * anim = malloc(sizeof(fn_animation_t));
  anim->num_frames = num_frames;
  anim->frames = malloc(sizeof(SDL_Surface *) * num_frames);
  memcpy(anim->frames, frames, sizeof(SDL_Surface *) * num_frames);
  anim->current_frame = startframe;
  anim->x = x;
  anim->y = y;
  anim->pixelsize = pixelsize;
  return anim;
}

/* --------------------------------------------------------------- */

void fn_animation_free(fn_animation_t * anim)
{
  free(anim->frames);
  free(anim);
}

/* --------------------------------------------------------------- */

void fn_animation_blit(
    fn_animation_t * anim,
    SDL_Surface * target
    )
{
  SDL_Rect r;
  r.x = anim->pixelsize * anim->x * FN_PART_WIDTH;
  r.y = anim->pixelsize * anim->y * FN_PART_HEIGHT;
  SDL_BlitSurface(anim->frames[anim->current_frame], NULL,
      target, &r);
}

/* --------------------------------------------------------------- */

Uint16 fn_animation_get_x(fn_animation_t * anim)
{
  return anim->x;
}

/* --------------------------------------------------------------- */

Uint16 fn_animation_get_y(fn_animation_t * anim)
{
  return anim->y;
}

/* --------------------------------------------------------------- */

void fn_animation_act(fn_animation_t * anim)
{
  anim->current_frame++;
  anim->current_frame %= anim->num_frames;
}

/* --------------------------------------------------------------- */
