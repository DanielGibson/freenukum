/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for Level loading functions
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

#include <SDL/SDL.h>
#include <unistd.h>
#include <string.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_level.h"
#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

void scroll(
        int xdist,
        int ydist,
        SDL_Rect * r,
        SDL_Surface * level,
        SDL_Surface * screen)
{
    r->x += xdist;
    r->y += ydist;

    if (r->x < 0)
        r->x = 0;
    if (r->y < 0)
        r->y = 0;
    if (r->x + r->w > level->w)
        r->x = level->w - r->w;
    if (r->y + r->h > level->h)
        r->y = level->h - r->h;

    SDL_BlitSurface(level, r, screen, NULL);
    SDL_UpdateRect(screen, 0, 0, 0, 0);
}

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    fn_level_t lv;
    int fd;
    fn_tilecache_t tc;
    Uint8 pixelsize = 1;
    size_t i = 0;
    size_t j = 0;
    int quit = 0;
    int res;
    SDL_Surface * screen;
    SDL_Surface * tile;
    SDL_Surface * level;
    SDL_Event event;

    if (argc != 3)
    {
        fprintf(stderr, "\nShows a Duke Nukem original level.\n");
        fprintf(stderr, "Usage: %s <GRAPHICSDIR> <LEVELFILE>\n", argv[0]);
        fprintf(stderr, "GRAPHICSDIR is the directory where the data is "
                "stored.\n"
                "LEVELFILE is the file containing the level itself.\n"
                "          This is usually something like WORLDAL1.DN1\n\n");

        return -1;
    }

    printf("Use the arrow keys to navigate through the level\n");

    char * directory = argv[1];
    char * file = argv[2];

    fn_tilecache_init(&tc, pixelsize);

    res = fn_tilecache_loadtiles(&tc, directory);
    if (res == -1)
    {
        printf("Could not load tiles.\n");
        return -1;
    }

    fd = open(file, O_RDONLY);

    if (fd == -1)
    {
        perror("Can't open file");
        return -1;
    }

    if (fn_level_load(&lv, fd) != 0)
    {
        close(fd);
        fprintf(stderr, "Could not load level from file %s\n", file);
        return -1;
    }

    close(fd);

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
        return -1;
    }

    screen = SDL_SetVideoMode(
            1000,
            700,
            FN_COLOR_DEPTH,
            SDL_SWSURFACE);

    if (screen == NULL)
    {
        fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
        return -1;
    }

    level = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            FN_PART_WIDTH * pixelsize * FN_LEVEL_WIDTH,
            FN_PART_HEIGHT * pixelsize * FN_LEVEL_HEIGHT,
            FN_COLOR_DEPTH,
            0,
            0,
            0,
            0);


    SDL_WM_SetCaption("FreeNukum Level Tester", "");

    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = FN_PART_WIDTH * pixelsize;
    r.h = FN_PART_HEIGHT * pixelsize;

    for (i = 0; i != FN_LEVEL_WIDTH; i++)
    {
        for (j = 0; j != FN_LEVEL_HEIGHT; j++)
        {
            r.x = i * FN_PART_WIDTH * pixelsize;
            r.y = j * FN_PART_HEIGHT * pixelsize;
            if (r.x < FN_PART_WIDTH * pixelsize * FN_LEVEL_WIDTH
                    && r.y < FN_PART_HEIGHT * pixelsize * FN_LEVEL_HEIGHT)
            {
                tile = fn_tilecache_gettile(
                        &tc,
                        (fn_level_gettile(&lv, i, j) / 0x20) % 1300
                        );
                SDL_BlitSurface(tile, NULL, level, &r);
            }
        }
    }

    SDL_BlitSurface(level, NULL, screen, NULL);

    SDL_UpdateRect(screen, 0, 0, 0, 0);

    r.x = 0;
    r.y = 0;
    r.w = screen->w;
    r.h = screen->h;

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
                        case SDLK_DOWN:
                            scroll(0, multiplier, &r, level, screen);
                            break;
                        case SDLK_UP:
                            scroll(0, -1 * multiplier, &r, level, screen);
                            break;
                        case SDLK_LEFT:
                            scroll(-1 * multiplier, 0, &r, level, screen);
                            break;
                        case SDLK_RIGHT:
                            scroll(multiplier, 0, &r, level, screen);
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
