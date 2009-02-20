/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tile loader tester
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

#include "fn_tile.h"
#include "fntexture.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    g_type_init();
    int fd;
    fn_environment_t * env = fn_environment_create();
    fn_environment_load_tilecache(env);
    SDL_Event event;
    int res = 0;
    int quit = 0;
    
    if (argc != 2)
    {
        fprintf(stderr, "\nShows the tiles that can be found inside "
                "an original Duke Nukem file.\n");
        fprintf(stderr, "Usage: %s <FILENAME>\n", argv[0]);
        fprintf(stderr, "FILENAME is usually one of the following:\n"
                "ANIM0.DN1 to ANIM5.DN1, BORDER.DN1, FONT1.DN1, FONT2.DN1,\n"
                "NUMBERS.DN1, OBJECT0.DN1 to OBJECT2.DN1, SOLID0.DN1"
                " to SOLID3.DN1\n\n");
        return -1;
    }

    fd = open(argv[1], O_RDONLY);

    SDL_Surface * screen;
    FnTexture * tile;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
        return -1;
    }

    fn_tileheader_t h;
    fn_tile_loadheader(fd, &h);
 
    screen = fn_environment_get_screen(env);
    Uint8 pixelsize = fn_environment_get_pixelsize(env);

    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = h.width * 8 * pixelsize;
    r.h = h.height * pixelsize;
    size_t i = 0;
    while (i != h.tiles)
    {
        tile = fn_tile_load(
            fd, env, &h, 0);
        fn_texture_blit_to_sdl_surface(tile, NULL, screen, &r);
        g_object_unref(tile);
        i++;
        r.x += 8 * h.width * pixelsize;
        r.y = 0;
    }
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

