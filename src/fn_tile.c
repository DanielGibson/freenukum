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

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn_object.h"
#include "fn_tile.h"
#include "fn_draw.h"
#include "fn.h"

/* --------------------------------------------------------------- */

int fn_tile_loadheader(int fd, fn_tileheader_t * h)
{
    return read(fd, h, sizeof(*h)) == sizeof(*h);
}

/* --------------------------------------------------------------- */

SDL_Surface * fn_tile_load(
        int fd,
        Uint8 pixelsize,
        fn_tileheader_t * h)
{
    SDL_Surface * tile;
    SDL_Rect r;
    size_t num_read = 0;
    fn_byterow_t br;
    char readbuf[5];

    tile = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            h->width * 8 * pixelsize,
            h->height * pixelsize,
            FN_COLOR_DEPTH,
            0,
            0,
            0,
            0
            );

    Uint32 transparent = SDL_MapRGB(tile->format, 100, 1, 1);

    size_t num_loads = h->width * h->height;
    
    r.x = 0;
    r.y = 0;
    r.w = 8 * pixelsize;
    r.h = 1 * pixelsize;

    while (num_read < num_loads)
    {
        read(fd, readbuf, 5);
        br.trans  = readbuf[0];
        br.blue   = readbuf[1];
        br.green  = readbuf[2];
        br.red    = readbuf[3];
        br.brighten = readbuf[4];
        fn_draw_byterow(
                tile,
                r,
                &br,
                transparent,
                pixelsize);
        r.x += 8 * pixelsize;
        r.x %= (8 * h->width * pixelsize);


        if (r.x == 0)
            r.y += pixelsize;
        num_read++;
    }

    if (SDL_SetColorKey(tile, SDL_SRCCOLORKEY, transparent) != 0)
    {
        return NULL;
    }

    return tile;
}

/* --------------------------------------------------------------- */

int fn_tile_is_solid(
    Uint16 tile)
{
  return tile >= SOLID_START && tile < ANIM_START;
}

/* --------------------------------------------------------------- */

