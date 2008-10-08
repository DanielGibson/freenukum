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

#ifndef FN_INPUTFIELD_H
#define FN_INPUTFIELD_H

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

typedef struct fn_inputfield_t {
  char * data;
  Uint8 data_len;
  Uint8 cursor;
  Uint8 fillstate;
} fn_inputfield_t;

/* --------------------------------------------------------------- */

fn_inputfield_t * fn_inputfield_new(
    char * data, Uint8 data_len);

/* --------------------------------------------------------------- */

void fn_inputfield_free(fn_inputfield_t * field);

/* --------------------------------------------------------------- */

void fn_inputfield_pressed_backspace(fn_inputfield_t * field);

void fn_inputfield_pressed_delete(fn_inputfield_t * field);

/* --------------------------------------------------------------- */

void fn_inputfield_pressed_left(fn_inputfield_t * field);

/* --------------------------------------------------------------- */

void fn_inputfield_pressed_right(fn_inputfield_t * field);

/* --------------------------------------------------------------- */

void fn_inputfield_pressed_symbol(fn_inputfield_t * field,
    char symbol
    );

/* --------------------------------------------------------------- */

void fn_inputfield_blit(fn_inputfield_t * field,
    SDL_Surface * target,
    fn_tilecache_t * tc,
    Uint8 pixelsize);

/* --------------------------------------------------------------- */

#endif /* FN_INPUTFIELD_H */

/* --------------------------------------------------------------- */
