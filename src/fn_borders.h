/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Border drawing functions
 *******************************************************************/

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

void fn_borders_blit(
    SDL_Surface * screen,
    fn_tilecache_t * tc,
    Uint8 pixelsize);
