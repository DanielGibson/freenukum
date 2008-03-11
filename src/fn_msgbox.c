/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Messagebox Drawing functions
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

#include "fn.h"
#include "fn_msgbox.h"
#include "fn_text.h"

/* --------------------------------------------------------------- */

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

/* --------------------------------------------------------------- */

SDL_Surface * fn_msgbox(
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    char * text
    )
{
  char * walker;
  Uint8 columns = 0;
  Uint8 rows = 0;
  char * mytext;
  char * linemarker;
  SDL_Surface * msgbox;
  Uint8 i, j;
  int tilenr;
  SDL_Rect r;

  mytext = malloc(strlen(text)+1);
  strcpy(mytext, text);
  walker = mytext;

  linemarker = walker;

  while (*walker != '\0') {
    if (*walker == '\n') {
      *walker = '\0';
      columns = MAX(strlen(linemarker), columns);
      *walker = '\n';
      linemarker = walker + 1;
      rows++;
    }
    walker++;
  }

  msgbox = SDL_CreateRGBSurface(
      SDL_SWSURFACE,
      FN_FONT_WIDTH * pixelsize * (columns + 2),
      FN_FONT_HEIGHT * pixelsize * (rows + 2),
      FN_COLOR_DEPTH,
      0,
      0,
      0,
      0
      );
  r.w = pixelsize * FN_PART_WIDTH;
  r.h = pixelsize * FN_PART_HEIGHT;

  for (i = 0; i <= rows; i++) {
    for (j = 0; j <= columns; j++) {

      if      (i == 0      && j == 0)       tilenr = BORD_BLUE_TOPLEFT;
      else if (i == 0      && j == columns) tilenr = BORD_BLUE_TOPRIGHT;
      else if (i == rows   && j == 0)       tilenr = BORD_BLUE_BOTTOMLEFT;
      else if (i == rows   && j == columns) tilenr = BORD_BLUE_BOTTOMRIGHT;
      else if (i == 0      && j % 2 == 0)   tilenr = BORD_BLUE_TOP;
      else if (i % 2 == 0  && j == 0)       tilenr = BORD_BLUE_LEFT;
      else if (i == rows   && j % 2 == 0)   tilenr = BORD_BLUE_BOTTOM;
      else if (i % 2 == 0  && j == columns) tilenr = BORD_BLUE_RIGHT;
      else if (i % 2 == 0  && j % 2 == 0)   tilenr = BORD_BLUE_MIDDLE;
      else continue;
      r.x = j * pixelsize * FN_FONT_WIDTH;
      r.y = i * pixelsize * FN_FONT_HEIGHT;
      SDL_BlitSurface(
          fn_tilecache_get_tile(tilecache, tilenr),
          NULL,
          msgbox,
          &r);
    }
  }

  r.w = pixelsize * FN_FONT_WIDTH;
  r.h = pixelsize * FN_FONT_HEIGHT;
  r.x = pixelsize * FN_FONT_WIDTH;
  r.y = pixelsize * FN_FONT_HEIGHT;

  fn_text_print(msgbox,
      &r,
      tilecache,
      mytext,
      pixelsize);
  
  free(mytext);

  return msgbox;
}

/* --------------------------------------------------------------- */
