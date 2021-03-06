/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Messagebox Drawing functions
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

#include "fn.h"
#include "fn_msgbox.h"
#include "fn_text.h"
#include "fntexture.h"

/* --------------------------------------------------------------- */

#define MAXVAL(X,Y) ((X) > (Y) ? (X) : (Y))

/* --------------------------------------------------------------- */

Uint8 fn_msgbox_get_line_length(
    char * line)
{
  Uint8 length = 0;
  char * walker = line;
  while (*walker != '\n' && *walker != '\0') {
    walker++;
    length++;
  }
  return length;
}

/* --------------------------------------------------------------- */

void fn_msgbox_get_text_information(
    char * text,
    Uint16 * columns,
    Uint16 * rows
    )
{
  *columns = 0;
  *rows = 0;
  char * walker = text;

  while (*walker != '\0') {
    Uint8 current_line_len = fn_msgbox_get_line_length(walker);
    *columns = MAXVAL(*columns, current_line_len);
    (*rows)++;

    walker += current_line_len;
    if (*walker == '\n') {
      walker++;
    }
  }
}

/* --------------------------------------------------------------- */

FnTexture * fn_msgbox(
    fn_environment_t * env,
    char * text
    )
{
  Uint16 columns = 0;
  Uint16 rows = 0;
  FnTexture * msgbox;
  Uint8 i, j;
  int tilenr;
  FnGeometry * r = fn_geometry_new(0, 0, 0, 0);

  fn_msgbox_get_text_information(
      text,
      &columns,
      &rows);

  FnGraphicOptions * graphic_options =
    fn_environment_get_graphic_options(env);

  Uint8 pixelsize = fn_environment_get_pixelsize(env);
  msgbox = fn_texture_new_with_options(
      FN_FONT_WIDTH * (columns + 2),
      FN_FONT_HEIGHT * (rows + 2),
      graphic_options
      );

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

      fn_geometry_set_data(r,
          j * pixelsize * FN_FONT_WIDTH,
          i * pixelsize * FN_FONT_HEIGHT,
          pixelsize * FN_FONT_WIDTH,
          pixelsize * FN_FONT_HEIGHT);
      fn_texture_clone_to_texture(
          fn_environment_get_tile(env, tilenr),
          NULL,
          msgbox,
          r);
    }
  }

  fn_geometry_set_data(r,
      pixelsize * FN_FONT_WIDTH,
      pixelsize * FN_FONT_HEIGHT,
      pixelsize * FN_FONT_WIDTH,
      pixelsize * FN_FONT_HEIGHT);

  fn_text_print(msgbox,
      r,
      env,
      text);
  
  return msgbox;
}

/* --------------------------------------------------------------- */
