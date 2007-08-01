/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Gameplay functions
 *******************************************************************/

#ifndef FN_GAME_H
#define FN_GAME_H

/* --------------------------------------------------------------- */

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

void fn_game_start(
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    SDL_Surface * screen,
    char * datapath);

/* --------------------------------------------------------------- */

#endif /* FN_GAME_H */