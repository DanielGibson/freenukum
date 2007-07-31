/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tile Cache
 * $Id: fn_tilecache.h 11 2006-06-10 12:20:52Z sttereo3 $
 *******************************************************************/

#ifndef FN_TILECACHE_H
#define FN_TILECACHE_H

/* --------------------------------------------------------------- */

#include <SDL/SDL.h>
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
        char * directory
        );

/* --------------------------------------------------------------- */

int fn_tilecache_loadfile(
        fn_tilecache_t * tc,
        int fd,
        size_t num_tiles,
        fn_tileheader_t * header);

/* --------------------------------------------------------------- */

void fn_tilecache_destroy(
        fn_tilecache_t * tc);

/* --------------------------------------------------------------- */

SDL_Surface * fn_tilecache_gettile(fn_tilecache_t * tc, size_t pos);

/* --------------------------------------------------------------- */

#endif // FN_TILECACHE_H

