/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for tile cache
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

#include <SDL/SDL.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_tile.h"
#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

int sumuntil(Uint8 * ar, size_t s)
{
    int ret = 0;
    while (s > 0)
    {
        s--;
        ret += ar[s];
    }
    return ret;
}

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    SDL_Surface * screen;
    fn_tilecache_t tc;
    size_t i = 0;
    size_t j = 0;
    int pixelsize = 2;
    int res;
    int quit = 0;
    SDL_Event event;

    if (argc != 2)
    {
        fprintf(stderr, "\nShows all the tiles that can be found "
                "in an original Duke Nukem game.\n");
        fprintf(stderr, "Usage: %s <DIRECTORY>\n", argv[0]);
        fprintf(stderr, "DIRECTORY is the directory where the original "
                "game data can be found.\n\n");
        return -1;
    }

    char * directory = argv[1];

    fn_tilecache_init(&tc, pixelsize);

    res = fn_tilecache_loadtiles(&tc, directory);
    if (res == -1)
    {
        printf("Could not load tiles.\n");
        return -1;
    }

    Uint8 size[] = {
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        50,
        50,
        50,
        48,
        48,
        48,
        48,
        48,
        50,
        50,
        48,
        48,
        0
    };

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
        return -1;
    }

    screen = SDL_SetVideoMode(
            FN_PART_WIDTH * pixelsize * 50,
            FN_PART_HEIGHT * pixelsize * 26,
            FN_COLOR_DEPTH,
            SDL_SWSURFACE);

    if (screen == NULL)
    {
        fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = FN_PART_WIDTH * pixelsize;
    r.h = FN_PART_HEIGHT * pixelsize;
    
    for (j = 0; j != 26; j++)
    {
        for(i = 0; i != size[j]; i++)
        {
            r.x = i * FN_PART_WIDTH * pixelsize;
            r.y = j * FN_PART_HEIGHT * pixelsize;
            SDL_BlitSurface(fn_tilecache_gettile(&tc, sumuntil(size, j)+i), NULL, 
                    screen, &r);
        }
    }
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    fn_tilecache_destroy(&tc);

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

