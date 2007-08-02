/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tile loader
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

#ifndef FN_TILE_H
#define FN_TILE_H

/* --------------------------------------------------------------- */

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn.h"

/* --------------------------------------------------------------- */

typedef struct {
    Uint8 tiles;
    Uint8 width;
    Uint8 height;
} fn_tileheader_t;

/* --------------------------------------------------------------- */

int fn_tile_loadheader(int fd, fn_tileheader_t * h);

/* --------------------------------------------------------------- */

SDL_Surface * fn_tile_load(
        int fd,
        Uint8 pixelsize, fn_tileheader_t * h
        );

/* --------------------------------------------------------------- */

#endif // FN_TILE_H
