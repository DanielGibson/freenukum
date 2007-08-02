/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Drop (Level Background) loader
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

#include <stdlib.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn_draw.h"
#include "fn_tile.h"
#include "fn_drop.h"

/* --------------------------------------------------------------- */

SDL_Surface * fn_drop_load(int fd, Uint8 pixelsize)
{
    SDL_Surface * drop;
    SDL_Rect r;
    size_t num_read = 0;
    fn_tileheader_t h;
    SDL_Surface * tile;

    drop = SDL_CreateRGBSurface(
            SDL_SWSURFACE,  /* flags */
            FN_DROP_WIDTH * FN_PART_WIDTH * pixelsize,  /* width */
            FN_DROP_HEIGHT * FN_PART_WIDTH * pixelsize, /* height */
            FN_COLOR_DEPTH, /* depth */
            0,              /* Rmask */
            0,              /* Gmask */
            0,              /* Bmask */
            0               /* Amask */
            );

    size_t num_loads = FN_DROP_WIDTH *  FN_DROP_HEIGHT;

    r.x=0;
    r.y=0;
    r.w=FN_PART_WIDTH * pixelsize;
    r.h=FN_PART_HEIGHT * pixelsize;

    h.width = 2;
    h.height = 16;

    while(num_read != num_loads)
    {
        tile = fn_tile_load(fd, pixelsize, &h);
        SDL_BlitSurface(tile, NULL, drop, &r);
        SDL_FreeSurface(tile);
        r.x += 16 * pixelsize;
        if (r.x == 16 * FN_DROP_WIDTH * pixelsize)
        {
            r.x = 0;
            r.y += 16 * pixelsize;
        }
        num_read++;
    }

    return drop;
}

/* --------------------------------------------------------------- */

