/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Pixel Drawing functions
 *
 * *****************************************************************
 *
 * Copyright 2007-2008 Wolfgang Silbermayr
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

