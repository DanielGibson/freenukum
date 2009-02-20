/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for Picture Drawing functions
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
#include <stdio.h>

/* --------------------------------------------------------------- */

#include "fn_picture.h"
#include "fn.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    g_type_init();

    int fd;
    int res;
    int quit = 0;
    SDL_Event event;
    fn_environment_t * env = fn_environment_create();
    fn_environment_load_tilecache(env);

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
    FnTexture * picture;

    screen = fn_environment_get_screen(env);

    picture = fn_picture_load(
        fd, env);

    fn_texture_blit_to_sdl_surface(picture, NULL, screen, NULL);
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    g_object_unref(picture);

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

