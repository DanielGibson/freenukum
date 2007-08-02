/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for Messagebox Drawing functions
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
#include <stdlib.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_msgbox.h"
#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    SDL_Surface * screen;
    SDL_Surface * msgbox;
    Uint8 width = 13;
    Uint8 height = 9;
    Uint8 pixelsize = 2;
    fn_tilecache_t tc;
    int res;
    int quit = 0;
    SDL_Event event;
    char * homedir;
    char tilespath[1024];

    char * msg =
        " FREENUKUM MAIN MENU\n"
        " ------------------- \n"
        "\n"
        "S)tart a new game\n"
        "R)estore an old game\n"
        "I)nstructions\n"
        "O)rdering information\n"
        "G)ame setup\n"
        "H)igh scores\n"
        "P)reviews/Main Demo!\n"
        "V)iew user demo\n"
        "T)itle screen\n"
        "C)redits\n"
        "Q)it to DOS\n";

    homedir = getenv("HOME");

    if (homedir == NULL) {
      printf("%s\n", "HOME directory path not set.");
      exit(1);
    }

    snprintf(tilespath, 1024, "%s%s", homedir, "/.freenukum/data/");

    fn_tilecache_init(&tc, pixelsize);

    res = fn_tilecache_loadtiles(&tc, tilespath);
    if (res == -1)
    {
        printf("Could not load tiles.\n");
        printf("Copy the original game files to %s.\n", tilespath);
        exit(1);
    }

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
        return -1;
    }

    screen = SDL_SetVideoMode(
            FN_PART_WIDTH * pixelsize * width,
            FN_PART_HEIGHT * pixelsize * height,
            FN_COLOR_DEPTH,
            SDL_SWSURFACE);

    if (screen == NULL)
    {
        fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
        return -1;
    }

    msgbox = fn_msgbox(pixelsize,
        &tc,
        msg);

    SDL_BlitSurface(msgbox, NULL, screen, NULL);
    SDL_FreeSurface(msgbox);
    SDL_UpdateRect(screen, 0, 0, 0, 0);

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

