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

#include <SDL.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

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
    fn_level_t * lv = NULL;
    int fd;
    fn_tilecache_t tc;
    Uint8 pixelsize = 1;
    int quit = 0;
    int res;
    SDL_Surface * screen;
    SDL_Surface * level;
    SDL_Event event;
    char * homedir;
    char tilespath[1024];
    char levelfile[1024];

    int argok = 0;
    char levelnumber;

    if (argc == 2) {
      if (strlen(argv[1]) == 1) {
        levelnumber = argv[1][0];
        if ((levelnumber >= '1' && levelnumber <= '9') ||
            (levelnumber >= 'A' && levelnumber <= 'C'))
        {
          argok = 1;
        }
      }
    }

    if (!argok)
    {
        fprintf(stderr, "\nShows a Duke Nukem original level.\n");
        fprintf(stderr, "Usage: %s <LEVELNUMBER>\n", argv[0]);
        fprintf(stderr,
                "LEVELNUMBER is the number of the level.\n"
                "          This is usually a number between 1 and 9\n"
                "          or one of A, B, C.\n\n");

        return -1;
    }

    homedir = getenv("HOME");

    if (homedir == NULL) {
      printf("%s\n", "HOME directory path not set.");
      exit(1);
    }

    snprintf(tilespath, 1024, "%s%s", homedir, "/.freenukum/data/");

    snprintf(levelfile, 1024, "%s/.freenukum/data/WORLDAL%c.DN1",
        homedir, levelnumber);

    printf("Use the arrow keys to navigate through the level\n");

    fn_tilecache_init(&tc, pixelsize);

    res = fn_tilecache_loadtiles(&tc, tilespath);
    if (res == -1)
    {
        printf("Could not load tiles.\n");
        printf("Copy the original game files to %s.\n", tilespath);
        exit(1);
    }

    fd = open(levelfile, O_RDONLY);

    if (fd == -1)
    {
        perror("Can't open file");
        return -1;
    }

    lv = fn_level_load(fd, pixelsize, &tc);
    if (lv == NULL)
    {
        close(fd);
        fprintf(stderr, "Could not load level from file %s\n", levelfile);
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
    r.w = FN_PART_WIDTH * pixelsize * FN_LEVEL_WIDTH;
    r.h = FN_PART_HEIGHT * pixelsize * FN_LEVEL_HEIGHT;

    fn_level_blit_to_surface(lv,
        level,
        &r,
        &r);

    SDL_BlitSurface(level, NULL, screen, NULL);

    SDL_UpdateRect(screen, 0, 0, 0, 0);

    r.x = 0;
    r.y = 0;
    r.w = screen->w;
    r.h = screen->h;

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
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                      Uint16 click_x = 0;
                      Uint16 click_y = 0;
                      Uint16 global_x = 0;
                      Uint16 global_y = 0;
                      Uint16 tile_x = 0;
                      Uint16 tile_y = 0;
                      int tilenr = 0;
                      Uint8 is_solid = 0;
                      click_x = event.button.x;
                      click_y = event.button.y;

                      global_x = (r.x) + (click_x);
                      global_y = (r.y) + (click_y);
                      tile_x = global_x / FN_PART_WIDTH / pixelsize;
                      tile_y = global_y / FN_PART_HEIGHT / pixelsize;

                      tilenr = fn_level_get_raw(lv, tile_x, tile_y);
                      is_solid = fn_level_is_solid(lv, tile_x, tile_y);
                      printf("Tile number: 0x%04x; Solid: %s\n",
                          tilenr, (is_solid? "yes" : "no"));
                    }
                    break;
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
