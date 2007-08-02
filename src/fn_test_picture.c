/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for Picture Drawing functions
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
 * Freenukum is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *******************************************************************/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* --------------------------------------------------------------- */

#include "fn_draw.h"
#include "fn_picture.h"
#include "fn.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    int fd;
    Uint8 pixelsize = 3;
    int res;
    int quit = 0;
    SDL_Event event;

    if (argc != 2)
    {
        fprintf(stderr, "\nShows a Duke Nukem picture of the original Duke Nukem game.\n");
        fprintf(stderr, "Usage: %s <FILENAME>\n", argv[0]);
        fprintf(stderr, "FILENAME is usually one of the following file names:\n"
                "BADGUY.DN1, CREDITS.DN1, DN.DN1, DUKE.DN1, END.DN1\n\n");
        return -1;
    }

    fd = open(argv[1], O_RDONLY);

    SDL_Surface * screen;
    SDL_Surface * picture;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
        return -1;
    }

    screen = SDL_SetVideoMode(
            FN_WINDOW_WIDTH * pixelsize,
            FN_WINDOW_HEIGHT * pixelsize,
            FN_COLOR_DEPTH,
            SDL_SWSURFACE);

    if (screen == NULL)
    {
        fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
        return -1;
    }

    picture = fn_picture_load(fd, pixelsize);

    SDL_BlitSurface(picture, NULL, screen, NULL);
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    SDL_FreeSurface(picture);

    while (quit == 0)
    {
        res = SDL_PollEvent(&event);
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

