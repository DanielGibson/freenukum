/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for blending effects
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

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_effect.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"
#include "fn_picture.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  SDL_Surface * screen;
  SDL_Surface * picture;

  SDL_Event event;

  char * homedir;
  char datapath[1024];
  char picturepath[1024];

  int res;

  int fd;

  int quit = 0;
  Uint8 step = 0;

  Uint8 pixelsize = 2;

  fn_error_set_handler(fn_error_print_commandline);

  homedir = getenv("HOME");
  if (homedir == NULL) {
    fn_error_print("$HOME environment variable is not set.");
    exit(1);
  }

  snprintf(datapath, 1024, "%s%s", homedir, "/.freenukum/data/");

  snprintf(picturepath, 1024, "%s%s", datapath, "DN.DN1");

  fd = open(picturepath, O_RDONLY);
  if (fd == -1) {
    fn_error_printf(1024, "Error reading file %s: %s", picturepath, strerror(errno));
    fn_error_printf(1024, "Copy the original game files to %s.", datapath);
    exit(1);
  }

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fn_error_printf(1024, "Can't init SDL: %s", SDL_GetError());
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

  picture = fn_picture_load(fd, pixelsize);
  close(fd);

  SDL_BlitSurface(picture, NULL, screen, NULL);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  while (quit == 0) {
    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_QUIT:
          quit = 1;
          break;
        case SDL_KEYDOWN:
          fn_effect_blend(screen, step, 0x00, pixelsize);
          step++;
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
