/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Text Drawing functions
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
#include <string.h>

/* --------------------------------------------------------------- */

#include "fn_text.h"
#include "fn_tilecache.h"
#include "fn_object.h"

/* --------------------------------------------------------------- */

void fn_text_printletter(
    SDL_Surface * target,
    SDL_Rect * r,
    fn_environment_t * env,
    char c)
{
  int tilenr;

  if (c >= ' ' && c <= 'Z')
    tilenr = c - ' ' + FONT_ASCII_UPPERCASE;
  else
    tilenr = c - 'a' + FONT_ASCII_LOWERCASE;
  SDL_BlitSurface(
      fn_environment_get_tile(env, tilenr),
      NULL,
      target,
      r);
}

/* --------------------------------------------------------------- */

void fn_text_print(
    SDL_Surface * target,
    SDL_Rect * r,
    fn_environment_t * env,
    char * text)
{
  SDL_Rect dstrect;

  char * walker;
  char * end;

  if (r != NULL)
    memcpy(&dstrect, r, sizeof(SDL_Rect));
  else {
    dstrect.x = 0;
    dstrect.y = 0;
  }
  Uint8 pixelsize = fn_environment_get_pixelsize(env);
  dstrect.w = pixelsize * FN_FONT_WIDTH;
  dstrect.h = pixelsize * FN_FONT_HEIGHT;

  end = text + strlen(text);

  for (walker = text; walker < end; walker++) {
    if (*walker == '\n') {
      dstrect.x = r->x;
      dstrect.y += pixelsize * FN_FONT_HEIGHT;
    } else {
      fn_text_printletter(target,
          &dstrect,
          env,
          *walker);
      dstrect.x += pixelsize * FN_FONT_WIDTH;
    }
  }
}

/* --------------------------------------------------------------- */
