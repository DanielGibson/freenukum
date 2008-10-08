/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Infobox drawing function
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

#include "fn_inputfield.h"
#include "fn_text.h"

/* --------------------------------------------------------------- */

fn_inputfield_t * fn_inputfield_new(
    char * data, Uint8 data_len)
{
  fn_inputfield_t * field = malloc(sizeof(fn_inputfield_t));
  field->data = data;
  field->data_len = data_len;
  field->data[data_len] = '\0';
  field->cursor = 0;
  field->fillstate = strlen(data);
  return field;
}

/* --------------------------------------------------------------- */

void fn_inputfield_free(fn_inputfield_t * field)
{
  free(field);
}

/* --------------------------------------------------------------- */

void fn_inputfield_print(fn_inputfield_t * field)
{
  printf("content: \"%s\"\n", field->data);
  printf("          ");
  int i = 0;
  while (i < field->cursor) {
    printf(" ");
    i++;
  }
  printf("^ (%d)\n", field->cursor);
}

/* --------------------------------------------------------------- */

void fn_inputfield_pressed_backspace(fn_inputfield_t * field)
{
  if (field->cursor > 0) {
    int i = 0;
    for (i = field->cursor; i <= field->fillstate; i++) {
      field->data[i-1] = field->data[i];
    }
    field->cursor--;
    field->fillstate--;
  }
  fn_inputfield_print(field);
}

/* --------------------------------------------------------------- */

void fn_inputfield_pressed_delete(fn_inputfield_t * field)
{
  int i = 0;
  for (i = field->cursor; i <= field->fillstate; i++) {
    field->data[i] = field->data[i+1];
  }
  field->fillstate--;
  fn_inputfield_print(field);
}

/* --------------------------------------------------------------- */

void fn_inputfield_pressed_left(fn_inputfield_t * field)
{
  if (field->cursor > 0) {
    field->cursor--;
  }
  fn_inputfield_print(field);
}

/* --------------------------------------------------------------- */

void fn_inputfield_pressed_right(fn_inputfield_t * field)
{
  if (field->cursor < field->fillstate) {
    field->cursor++;
  }
  fn_inputfield_print(field);
}

/* --------------------------------------------------------------- */

void fn_inputfield_pressed_symbol(fn_inputfield_t * field,
    char symbol)
{
  if (field->fillstate < field->data_len) {
    int i = 0;
    for (i = field->fillstate; i > field->cursor; i--) {
      field->data[i] = field->data[i-1];
    }
    field->data[field->cursor] = symbol;
    field->cursor++;
    field->fillstate++;
  }
  fn_inputfield_print(field);
}

/* --------------------------------------------------------------- */

void fn_inputfield_blit(fn_inputfield_t * field,
    SDL_Surface * target,
    fn_tilecache_t * tc,
    Uint8 pixelsize
    )
{
  Uint32 cursorcolor = SDL_MapRGB(target->format,
      0x88, 0x88, 0x88);
  SDL_FillRect(target, NULL, 0);
  fn_text_print(target, NULL, tc,
      field->data, pixelsize);
  SDL_Rect cursorrect;
  cursorrect.x = field->cursor * FN_FONT_WIDTH * pixelsize -
    pixelsize / 2;
  cursorrect.y = pixelsize;
  cursorrect.w = pixelsize;
  cursorrect.h = (FN_FONT_HEIGHT - 2) * pixelsize;
  SDL_FillRect(target, &cursorrect, cursorcolor);
}

/* --------------------------------------------------------------- */

