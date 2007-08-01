/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Gameplay functions
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

#include "fn_game.h"
#include "fn_borders.h"
#include "fn_picture_splash.h"

/* --------------------------------------------------------------- */

void fn_game_start(
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    SDL_Surface * screen,
    char * datapath)
{
  SDL_Event event;
  int res;

  char * msg1[] = {
    "So you're the pitiful",
    "hero they sent to stop",
    "me.  I, Dr. Proton, will",
    "soon rule the world!",
    0
  };
  char * msg2[] = {
    "You're wrong, Proton",
    "breath.  I'll be done",
    "with you and still have",
    "time to watch Oprah!",
    0
  };

  res = fn_picture_splash_show_with_message(
      datapath,
      "BADGUY.DN1",
      (Uint8)pixelsize,
      screen,
      tilecache,
      msg1,
      0,
      120);

  res = fn_picture_splash_show_with_message(
      datapath,
      "DUKE.DN1",
      (Uint8)pixelsize,
      screen,
      tilecache,
      msg2,
      100,
      120);

  SDL_FillRect(screen, NULL, 0);
  fn_borders_blit(
      screen,
      tilecache,
      pixelsize);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  while(1) {
    res = SDL_PollEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
              return;
              break;
            default:
              /* ignore other keys */
              break;
          }
        case SDL_VIDEOEXPOSE:
          SDL_UpdateRect(screen, 0, 0, 0, 0);
          break;
        default:
          /* ignore other events */
          break;
      }
    }
  }
}
