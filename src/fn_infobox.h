/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Infobox drawing function
 *******************************************************************/

#ifndef FN_INFOBOX_H
#define FN_INFOBOX_H

/* --------------------------------------------------------------- */

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

void fn_infobox_show(
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    SDL_Surface * screen,
    char * text);

/* --------------------------------------------------------------- */

#endif /* FN_INFOBOX_H */
