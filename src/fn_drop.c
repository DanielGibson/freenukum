/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Drop (Level Background) loader
 * $Id: fn_drop.c 8 2006-06-04 11:26:48Z sttereo3 $
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

