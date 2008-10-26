/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Border drawing functions
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

#include "fn.h"
#include "fn_borders.h"
#include "fn_object.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  SDL_Event event;

  int res;

  fn_error_set_handler(fn_error_print_commandline);

  fn_environment_t * env = fn_environment_create();
  fn_environment_check_for_episodes(env);
  fn_environment_load_tilecache(env);

  SDL_Surface * screen = fn_environment_get_screen(env);

  fn_borders_blit(env);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  while (1)
  {
    res = SDL_WaitEvent(&event);
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
