/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for hero blitting
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

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_tile.h"
#include "fn_tilecache.h"
#include "fn_hero.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  SDL_Surface * screen;
  fn_tilecache_t tc;
  fn_hero_t hero;

  int pixelsize = 2;
  int res;
  SDL_Event event;

  char * homedir;
  char datapath[1024];

  int quit = 0;

  fn_error_set_handler(fn_error_print_commandline);

  homedir = getenv("HOME");
  if (homedir == NULL) {
    fn_error_print("$HOME environment variable is not set.");
    exit(1);
  }

  snprintf(datapath, 1024, "%s%s", homedir, "/.freenukum/data/");

  fn_tilecache_init(&tc, pixelsize);

  res = fn_tilecache_loadtiles(&tc, datapath);
  if (res == -1) {
    printf("Could not load tiles.\n");
    printf("Copy the original game files to %s.\n", datapath);
    exit(1);
  }

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  screen = SDL_SetVideoMode(
      FN_WINDOW_WIDTH * pixelsize,
      FN_WINDOW_HEIGHT * pixelsize,
      FN_COLOR_DEPTH,
      SDL_SWSURFACE);

  if (screen == NULL) {
    fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
    exit(1);
  }

  /* here comes the hero!!!!! */
  fn_hero_init(&hero);
  fn_hero_blit(&hero, screen, &tc, pixelsize);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  while (quit == 0) {
    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_QUIT:
          quit = 1;
          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_q:
            case SDLK_ESCAPE:
              quit = 1;
              break;
            case SDLK_RIGHT:
              SDL_FillRect(screen, NULL, 0);
              fn_hero_set_direction(&hero, FN_HERO_DIRECTION_RIGHT);
              fn_hero_blit(&hero, screen, &tc, pixelsize);
              SDL_UpdateRect(screen, 0, 0, 0, 0);
              break;
            case SDLK_LEFT:
              SDL_FillRect(screen, NULL, 0);
              fn_hero_set_direction(&hero, FN_HERO_DIRECTION_LEFT);
              fn_hero_blit(&hero, screen, &tc, pixelsize);
              SDL_UpdateRect(screen, 0, 0, 0, 0);
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
