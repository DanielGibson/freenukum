/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Blending effect functions
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

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_effect.h"
#include "fn_error.h"

/* --------------------------------------------------------------- */

void fn_effect_blend_step(
    SDL_Surface * s,
    Uint32 blendcolor,
    Uint32 removecolor,
    Uint8 pixelsize)
{
  SDL_Rect r;
  Uint32 * pixels;

  r.w = pixelsize;
  r.h = pixelsize;
  fn_error_printf(1024, "s->w = %d, s->h = %d", s->w, s->h);

  pixels = (Uint32 *)s->pixels;
  for (r.y = 0; r.y < pixelsize * s->h; r.y += pixelsize) {
    for (r.x = 0; r.x < pixelsize * s->w; r.x += pixelsize) {
      if (pixels[r.x + r.y * s->w] == removecolor) {
        SDL_FillRect(s, &r, blendcolor);
      }
    }
  }
}

/* --------------------------------------------------------------- */

void fn_effect_blend(
    SDL_Surface * s,
    Uint8 step,
    Uint32 blendcolor,
    Uint8 pixelsize)
{
  SDL_PixelFormat * format = s->format;
  static Uint32 colors[16] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  if (colors[1] == 0) {
    colors[0] = SDL_MapRGB(format, 0x00, 0x00, 0x00); /* dark black */
    colors[1] = SDL_MapRGB(format, 0x00, 0x00, 0xA8); /* dark blue */
    colors[2] = SDL_MapRGB(format, 0x00, 0xA8, 0x00); /* dark green */
    colors[3] = SDL_MapRGB(format, 0xA8, 0x00, 0x00); /* dark red */
    colors[4] = SDL_MapRGB(format, 0xA8, 0x00, 0xA8); /* dark violet */
    colors[5] = SDL_MapRGB(format, 0xA8, 0x00, 0x00); /* dark yellow */
    colors[6] = SDL_MapRGB(format, 0xA8, 0xA8, 0xA8); /* dark white */
    colors[7] = SDL_MapRGB(format, 0x54, 0x54, 0x54); /* bright black */
    colors[8] = SDL_MapRGB(format, 0x54, 0x54, 0xFC); /* bright blue */
    colors[9] = SDL_MapRGB(format, 0x00, 0xA8, 0xA8); /* dark cyan */
    colors[10] = SDL_MapRGB(format, 0x54, 0xFC, 0xFC); /* bright cyan */
    colors[11] = SDL_MapRGB(format, 0xFC, 0x54, 0x54); /* bright red */
    colors[12] = SDL_MapRGB(format, 0xFC, 0x54, 0xFC); /* bright violet */
    colors[13] = SDL_MapRGB(format, 0xFC, 0xFC, 0x54); /* bright yellow */
    colors[14] = SDL_MapRGB(format, 0xFC, 0xFC, 0xFC); /* bright white */
    colors[15] = SDL_MapRGB(format, 0x00, 0x00, 0x00);
  };

  fn_effect_blend_step(s,
      blendcolor,
      colors[step],
      pixelsize);
}

/* --------------------------------------------------------------- */

