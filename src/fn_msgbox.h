/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Messagebox Drawing functions
 *******************************************************************/

#ifndef FN_MSGBOX_H
#define FN_MSGBOX_H

/* --------------------------------------------------------------- */

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn_object.h"
#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

typedef struct {
    SDL_Surface * msgbox;
    Uint8 w;
    Uint8 h;
    Uint8 pixelsize;
    char ** text;
} fn_msgbox_t;

/* --------------------------------------------------------------- */

int fn_msgbox_init(
        fn_msgbox_t * mb,
        Uint8 pixelsize,
        Uint8 w,
        Uint8 h);

/* --------------------------------------------------------------- */

int fn_msgbox_settext(
        fn_msgbox_t * mb,
        char ** msg
        );

/* --------------------------------------------------------------- */

SDL_Surface * fn_msgbox_getsurface(
        fn_msgbox_t * mb,
        fn_tilecache_t * tc);

/* --------------------------------------------------------------- */

#endif // FN_MSGBOX_H
