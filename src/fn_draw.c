/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Pixel Drawing functions
 *******************************************************************/

#include "fn_draw.h"

/* --------------------------------------------------------------- */

int fn_draw_byterow(
        SDL_Surface * target,
        SDL_Rect r,
        fn_byterow_t * br,
        Uint32 transcolor,
        Uint8 pixelsize)
{
    SDL_PixelFormat * fmt = target->format;
    Uint32 color;
    size_t i;
    r.h = pixelsize;
    r.w = pixelsize;

    for (i = 0; i != 8; i++)
    {
        if (((br->trans >> (7-i)) & 1) == 0)
        {
            color = transcolor;
        }
        else
        {
            color = SDL_MapRGB(
                    fmt,
                    ((br->red >> (7-i)) & 1) * 0x54 * 2
                    + ((br->brighten >> (7-i)) & 1) * 0x54,
                    ((br->green >> (7-i)) & 1) * 0x54 * 2
                    + ((br->brighten >> (7-i)) & 1) * 0x54,
                    ((br->blue >> (7-i)) & 1) * 0x54 * 2
                    + ((br->brighten >> (7-i)) & 1) * 0x54
                    );
        }
        SDL_FillRect(target, &r, color);

        r.x+= pixelsize;
    }
    return 0;
}

/* --------------------------------------------------------------- */

