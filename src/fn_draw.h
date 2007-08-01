/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Pixel Drawing functions
 *******************************************************************/

#ifndef FN_DRAW
#define FN_DRAW

/* --------------------------------------------------------------- */

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

typedef struct {
    Uint8 brighten;
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 trans;
} fn_byterow_t;

/* --------------------------------------------------------------- */

int fn_draw_byterow(
        SDL_Surface * target,
        SDL_Rect r,
        fn_byterow_t * br,
        Uint32 transcolor,
        Uint8 pixelsize);

/* --------------------------------------------------------------- */

#endif // FN_DRAW
