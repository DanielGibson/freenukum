/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tile Cache
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

#ifndef FN_TILECACHE_H
#define FN_TILECACHE_H

/* --------------------------------------------------------------- */

#include <SDL.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_tile.h"

/* --------------------------------------------------------------- */

typedef struct {
    SDL_Surface * tiles[FN_TILECACHE_SIZE];
    Uint8 pixelsize;
    ssize_t size;
} fn_tilecache_t;

/* --------------------------------------------------------------- */

void fn_tilecache_init(
        fn_tilecache_t * tc,
        Uint8 pixelsize);

/* --------------------------------------------------------------- */

int fn_tilecache_loadtiles(
        fn_tilecache_t * tc,
        Uint32 flags,
        int bitsperpixel,
        char * directory
        );

/* --------------------------------------------------------------- */

int fn_tilecache_loadfile(
        fn_tilecache_t * tc,
        Uint32 flags,
        int bitsperpixel,
        int fd,
        size_t num_tiles,
        fn_tileheader_t * header);

/* --------------------------------------------------------------- */

void fn_tilecache_destroy(
        fn_tilecache_t * tc);

/* --------------------------------------------------------------- */

SDL_Surface * fn_tilecache_get_tile(fn_tilecache_t * tc, size_t pos);

/* --------------------------------------------------------------- */

#endif /* FN_TILECACHE_H */

