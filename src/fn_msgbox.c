/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Messagebox Drawing functions
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
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *******************************************************************/

#include "fn.h"
#include "fn_msgbox.h"

/* --------------------------------------------------------------- */

int fn_msgbox_init(
        fn_msgbox_t * mb,
        Uint8 pixelsize,
        Uint8 w,
        Uint8 h)
{
    mb->pixelsize = pixelsize;
    mb->w = w;
    mb->h = h;
    mb->text = 0;
    return 0;
}

/* --------------------------------------------------------------- */

int fn_msgbox_settext(
        fn_msgbox_t * mb,
        char ** msg
        )
{
    mb->text = msg;
    return 0;
}

/* --------------------------------------------------------------- */

void fn_msgbox_printletter(SDL_Surface * msgbox,
        SDL_Rect * r,
        fn_tilecache_t * tc,
        char c)
{
    int tilenr;

    if (c >= ' ' && c <= 'Z')
    {
        tilenr = c - ' ' + FONT_ASCII_UPPERCASE;
    }
    else
    {
        tilenr = c - 'a' + FONT_ASCII_LOWERCASE;
    }
    SDL_BlitSurface(
            fn_tilecache_gettile(tc, tilenr),
            NULL,
            msgbox,
            r);
}

/* --------------------------------------------------------------- */

SDL_Surface * fn_msgbox_getsurface(
        fn_msgbox_t * mb,
        fn_tilecache_t * tc)
{
    SDL_Surface * msgbox;
    SDL_Rect r;
    size_t i = 0;
    size_t j = 0;
    int tilenr;

    msgbox = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            FN_PART_WIDTH * mb->pixelsize * mb->w,
            FN_PART_HEIGHT * mb->pixelsize * mb->h,
            FN_COLOR_DEPTH,
            0,
            0,
            0,
            0
            );

    r.x = 0;
    r.y = 0;
    r.w = FN_PART_WIDTH * mb->pixelsize;
    r.h = FN_PART_HEIGHT * mb->pixelsize;

    for (i = 0; i != mb->w; i++)
    {
        for (j = 0; j != mb->h; j++)
        {
            r.x = i * mb->pixelsize * FN_PART_WIDTH;
            r.y = j * mb->pixelsize * FN_PART_HEIGHT;
            if (i == 0 && j == 0)
            {
                /* top left corner */
                tilenr = BORD_BLUE_TOPLEFT;
            }
            else if (i == 0 && j == mb->h-1)
            {
                /* bottom left corner */
                tilenr = BORD_BLUE_BOTTOMLEFT;
            }
            else if (i == mb->w - 1 && j == 0)
            {
                /* top right corner */
                tilenr = BORD_BLUE_TOPRIGHT;
            }
            else if (i == mb->w - 1 && j == mb->h - 1)
            {
                /* bottom right corner */
                tilenr = BORD_BLUE_BOTTOMRIGHT;
            }
            else if (i == 0)
            {
                /* left border */
                tilenr = BORD_BLUE_LEFT;
            }
            else if (i == mb->w - 1)
            {
                /* right border */
                tilenr = BORD_BLUE_RIGHT;
            }
            else if (j == 0)
            {
                /* top border */
                tilenr = BORD_BLUE_TOP;
            }
            else if (j == mb->h - 1)
            {
                /* bottom border */
                tilenr = BORD_BLUE_BOTTOM;
            }
            else
            {
                /* central piece */
                tilenr = BORD_BLUE_MIDDLE;
            }
            SDL_BlitSurface(
                    fn_tilecache_gettile(tc, tilenr),
                    NULL,
                    msgbox,
                    &r
                    );

        }
    }

    i = 0;
    j = 0;

    r.w = FN_PART_WIDTH / 2 * mb->pixelsize;
    r.h = FN_PART_HEIGHT / 2 * mb->pixelsize;
    r.y = FN_PART_HEIGHT * mb->pixelsize;
    while (mb->text[i] != 0)
    {
        r.x = FN_PART_WIDTH * mb->pixelsize;
        while (mb->text[i][j] != 0)
        {
            fn_msgbox_printletter(msgbox, &r, tc, mb->text[i][j]);
            r.x += FN_PART_WIDTH / 2 * mb->pixelsize;
            j++;
        }
        r.y += FN_PART_HEIGHT / 2 * mb->pixelsize;
        j = 0;
        i++;
    }


    return msgbox;
}

/* --------------------------------------------------------------- */
