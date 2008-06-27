/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for Pixel Drawing functions
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

#include <SDL.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_draw.h"

/* --------------------------------------------------------------- */

int main()
{
    SDL_Surface * screen;
    SDL_Surface * object;
    SDL_Rect r;
    Uint32 color;
    Uint8 pixelsize = 5;
    int res;
    int quit = 0;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError() );
        return -1;
    }

    screen = SDL_SetVideoMode(
            FN_DROP_WIDTH * FN_TILE_WIDTH * pixelsize,
            FN_DROP_HEIGHT * FN_TILE_HEIGHT * pixelsize,
            FN_COLOR_DEPTH,
            FN_SURFACE_FLAGS
    );
    if(screen == NULL)
    {
        fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
        return -1;
    }

    object = SDL_CreateRGBSurface(screen->flags,
            FN_DROP_WIDTH * FN_TILE_WIDTH * pixelsize,
            FN_DROP_HEIGHT * FN_TILE_HEIGHT * pixelsize,
            screen->format->BitsPerPixel,
            0,
            0,
            0,
            SDL_ALPHA_TRANSPARENT);
    if (object == NULL)
    {
        fprintf(stderr, "Can't crate object: %s\n", SDL_GetError());
        return -1;
    }

    SDL_FillRect(screen, NULL, 0x00FFCCCC);

    SDL_SetAlpha(object, SDL_SRCCOLORKEY, SDL_ALPHA_TRANSPARENT);
    color = SDL_MapRGB(object->format, 1,1,1);
    SDL_SetColorKey(object, SDL_SRCCOLORKEY, color);

    r.x = 0;
    r.y = 0;
    r.w = 8 * pixelsize;
    r.h = 1 * pixelsize;

    Uint8 xpos = 0;
    Uint8 ypos = 0;

    fn_byterow_t br[] =
        {
            //red  green blue  brigh trans
            {0x00, 0x00, 0x00, 0x00, 0x0F},
            {0x00, 0x00, 0x00, 0xFF, 0xF0},
            {0x00, 0x00, 0xFF, 0x00, 0x0F},
            {0x00, 0x00, 0xFF, 0xFF, 0xF0},
            {0x00, 0xFF, 0x00, 0x00, 0x0F},
            {0x00, 0xFF, 0x00, 0xFF, 0xF0},
            {0x00, 0xFF, 0xFF, 0x00, 0x0F},
            {0x00, 0xFF, 0xFF, 0xFF, 0xF0},

            //red  green blue  brigh trans
            {0xFF, 0x00, 0x00, 0x00, 0x0F},
            {0xFF, 0x00, 0x00, 0xFF, 0xF0},
            {0xFF, 0x00, 0xFF, 0x00, 0x0F},
            {0xFF, 0x00, 0xFF, 0xFF, 0xF0},
            {0xFF, 0xFF, 0x00, 0x00, 0x0F},
            {0xFF, 0xFF, 0x00, 0xFF, 0xF0},
            {0xFF, 0xFF, 0xFF, 0x00, 0x0F},
            {0xFF, 0xFF, 0xFF, 0xFF, 0xF0}
        };


    while (ypos != FN_DROP_HEIGHT * FN_TILE_HEIGHT)
    {
        fn_draw_byterow(
                object,
                r,
                br + ((ypos / (8)) % (16)),
                color,
                pixelsize);
        if (xpos == FN_DROP_WIDTH * FN_TILE_WIDTH)
        {
            xpos = 0;
            ypos ++;
        }
        else
        {
            xpos += 8;
        }
        r.x = xpos * pixelsize;
        r.y = ypos * pixelsize;
    }

    SDL_BlitSurface(object, NULL, screen, NULL);
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    while (quit == 0)
    {
        res = SDL_WaitEvent(&event);
        if (res == 1)
        {
            int multiplier = 1;
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.mod & KMOD_CTRL)
                    {
                        multiplier = 160;
                    }
                    else
                    {
                        multiplier = 16;
                    }
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_q:
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;
                        default:
                            /* do nothing, ignoring other keys. */
                            break;
                    }
                case SDL_VIDEOEXPOSE:
                    SDL_UpdateRect(screen, 0, 0, 0, 0);
                    break;
                default:
                    /* do nothing */
                    break;
            }
        }
    }


    return 0;
}

/* --------------------------------------------------------------- */

