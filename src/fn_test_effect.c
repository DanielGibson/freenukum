/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for blending effects
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
#include <errno.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_effect.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"
#include "fn_picture.h"
#include "fn_environment.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  FnTexture * picture;

  fn_environment_t * env = fn_environment_create();

  SDL_Event event;

  int res;

  int fd;

  int quit = 0;
  Uint8 step = 0;

  Uint8 pixelsize = 2;

  fn_error_set_handler(fn_error_print_commandline);

  picture = fn_picture_load(
      fd,
      env);
  close(fd);

  SDL_Surface * screen = fn_environment_get_screen(env);
  fn_texture_blit_to_sdl_surface(picture, NULL, screen, NULL);
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
