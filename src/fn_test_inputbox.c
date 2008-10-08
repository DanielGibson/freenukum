/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Infobox drawing function test
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

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"
#include "fn_inputbox.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv) {
  SDL_Surface * screen;
  fn_tilecache_t tilecache;
  Uint8 pixelsize = 2;

  char * homedir;
  char tilespath[1024];
  
  int res;

  homedir = getenv("HOME");
  if (homedir == NULL) {
    printf("%s\n", "HOME directory path not set.");
    exit(1);
  }
  snprintf(tilespath, 1024, "%s%s", homedir, "/.freenukum/data/");

  fn_tilecache_init(&tilecache, pixelsize);

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
    return -1;
  }

  screen = SDL_SetVideoMode(
      FN_WINDOW_WIDTH * pixelsize,
      FN_WINDOW_HEIGHT * pixelsize,
      FN_COLOR_DEPTH,
      FN_SURFACE_FLAGS);
  if (screen == NULL) {
    fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
    return -1;
  }

  res = fn_tilecache_loadtiles(
      &tilecache, screen->flags, screen->format, tilespath);
  if (res == -1) {
    printf("Could not load tiles.\n");
    printf("Copy the original game files to %s.\n", tilespath);
    exit(1);
  }

  char answer[30] = "";
  fn_inputbox_answer_t entered =
    fn_inputbox_show(pixelsize, &tilecache, screen,
        "Please enter your name:",
        answer,
        30);

  if (entered == fn_inputbox_answer_ok) {
    printf("Okay.\n");
    printf("You entered %s.\n", answer);
  } else {
    printf("Aborted.\n");
  }
        
  return 0;
}


