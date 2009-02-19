/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for Drop (Level Background) loader
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

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn_drop.h"
#include "fn.h"
#include "fn_tile.h"
#include "fn_environment.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    g_type_init();
    int fd;
    fn_tileheader_t h;
    Uint8 pixelsize = 3;
    int quit = 0;
    int res;
    SDL_Event event;
    
    if (argc != 2)
    {
        fprintf(stderr, "\nShow an original Duke Nukem backdrop.\n");
        fprintf(stderr, "Usage: %s <FILENAME>\n", argv[0]);
        fprintf(stderr, "FILENAME is usually something like DROP1.DN1\n\n");
        fprintf(stderr, "filename is usually something like DROP1.DN1\n");
        return -1;
    }

    fn_environment_t * env = fn_environment_create();

    fd = open(argv[1], O_RDONLY);

    SDL_Surface * screen;
    SDL_Surface * drop;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
        return -1;
    }

    screen = SDL_SetVideoMode(
            FN_DROP_WIDTH * FN_TILE_WIDTH * pixelsize,
            FN_DROP_HEIGHT * FN_TILE_HEIGHT * pixelsize,
            FN_COLOR_DEPTH,
            FN_SURFACE_FLAGS);

    if (screen == NULL)
    {
        fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
        return -1;
    }

    fn_tile_loadheader(fd, &h);

    drop = fn_drop_load(fd, env);

    SDL_BlitSurface(drop, NULL, screen, NULL);
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    
    SDL_FreeSurface(drop);

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

