/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Border drawing functions
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

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_borders.h"
#include "fn_object.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  SDL_Surface * screen;
  fn_tilecache_t tc;
  
  int pixelsize = 3;

  SDL_Event event;

  char * homedir;
  char datapath[1024];

  int res;

  fn_error_set_handler(fn_error_print_commandline);

  homedir = getenv("HOME");
  if (homedir == NULL) {
    fn_error_print("$HOME environment variable is not set.");
    exit(1);
  }

  snprintf(datapath, 1024, "%s%s", homedir, "/.freenukum/data/");

  fn_tilecache_init(&tc, (Uint8)pixelsize);
  res = fn_tilecache_loadtiles(&tc, datapath);
  if (res == -1) {
    fn_error_printf(1024, "Could not load tiles.\n"
        "Copy the original game files to %s", datapath);
    exit(1);
  }

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fn_error_printf(1024, "Could not initialize SDL: %s", SDL_GetError());
    exit(1);
  }

  screen = SDL_SetVideoMode(
      FN_WINDOW_WIDTH * pixelsize,
      FN_WINDOW_HEIGHT * pixelsize,
      FN_COLOR_DEPTH,
      SDL_SWSURFACE);
  if (screen == NULL) {
    fn_error_printf(1024, "Can't set video mode: %s", SDL_GetError());
    exit(1);
  }

  fn_borders_blit(screen,
      &tc,
      pixelsize);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  while (1)
  {
    res = SDL_PollEvent(&event);
    if (res == 1)
    {
      switch(event.type) {
        case SDL_QUIT:
          exit(0);
          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym)
          {
            case SDLK_q:
            case SDLK_ESCAPE:
              exit(0);
              break;
            default:
              /* ignore other keys */
              break;
          }
          break;
        case SDL_VIDEOEXPOSE:
          SDL_UpdateRect(screen, 0, 0, 0, 0);
          break;
        default:
          /* ignore other events */
          break;
      }
    }
  }

  return 0;
}
