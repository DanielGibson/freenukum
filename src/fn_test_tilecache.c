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
#include <sys/stat.h>
#include <fcntl.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_tile.h"
#include "fn_tilecache.h"
#include "fn_object.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"

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

void blithex(SDL_Surface * target,
    SDL_Rect * r,
    fn_tilecache_t * tc,
    int x,
    Uint8 pixelsize)
{
  int tilenr;
  char dst[3];
  snprintf(dst, 3, "%02X", x);
  int i;

  for (i = 0; i < strlen(dst); i++) {
    if(dst[i] >= ' ' && dst[i] <= 'Z')
      tilenr = dst[i] - ' ' + FONT_ASCII_UPPERCASE;
    else
      tilenr = dst[i] - 'a' + FONT_ASCII_LOWERCASE;
    SDL_BlitSurface(
        fn_tilecache_gettile(tc, tilenr),
        NULL,
        target,
        r);
    r->x += (pixelsize * FN_FONT_WIDTH);
  }
}

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    SDL_Surface * screen;
    fn_tilecache_t tc;
    size_t i = 0;
    size_t j = 0;
    int pixelsize = 1;
    int res;
    int quit = 0;
    SDL_Event event;

    char * homedir;
    char datapath[1024];

    fn_error_set_handler(fn_error_print_commandline);

    homedir = getenv("HOME");
    if (homedir == NULL) {
      fn_error_print("$HOME environment variable is not set.");
      exit(1);
    }

    snprintf(datapath, 1024, "%s%s", homedir, "/.freenukum/data/");

    fn_tilecache_init(&tc, pixelsize);

    res = fn_tilecache_loadtiles(&tc, datapath);
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
            FN_PART_WIDTH * pixelsize * (50+1),
            FN_PART_HEIGHT * pixelsize * (26+1),
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

    for (i = 0; i != 26; i++) {
      r.x = 0;
      r.y = (i+1) * FN_PART_HEIGHT * pixelsize;
      blithex(screen,
          &r,
          &tc,
          i,
          pixelsize);
    }

    for (i = 0; i != 50; i++) {
      r.x = (i+1) * FN_PART_WIDTH * pixelsize;
      r.y = 0;
      blithex(screen,
          &r,
          &tc,
          i,
          pixelsize);
    }
    
    for (j = 0; j != 26; j++)
    {
        for(i = 0; i != size[j]; i++)
        {
            r.x = (i+1) * FN_PART_WIDTH * pixelsize;
            r.y = (j+1) * FN_PART_HEIGHT * pixelsize;
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

