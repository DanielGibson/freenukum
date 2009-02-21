/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Infobox drawing function
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

#include "fn_infobox.h"
#include "fn_msgbox.h"

/* --------------------------------------------------------------- */

void fn_infobox_show(
    fn_environment_t * env,
    char * msg)
{
  FnTexture * msgbox;
  SDL_Surface * temp;
  SDL_Rect dstrect;

  int res;

  SDL_Event event;

  msgbox = fn_msgbox(
      env,
      msg);

  Uint8 pixelsize = fn_environment_get_pixelsize(env);

  SDL_Surface * screen = fn_environment_get_screen_sdl(env);
  dstrect.x =
    ((screen->w) - (fn_texture_get_width(msgbox) * pixelsize))/2;
  dstrect.y =
    ((screen->h) - (fn_texture_get_height(msgbox) * pixelsize))/2;
  dstrect.w = fn_texture_get_width(msgbox) * pixelsize;
  dstrect.h = fn_texture_get_height(msgbox) * pixelsize;

  /* backup the background */
  temp = fn_environment_create_surface(env,
      fn_texture_get_width(msgbox), fn_texture_get_height(msgbox));
  SDL_BlitSurface(screen, &dstrect, temp, NULL);

  fn_texture_blit_to_sdl_surface(msgbox, NULL, screen, &dstrect);
  g_object_unref(msgbox);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  while (1) {
    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_KEYDOWN:
          SDL_BlitSurface(temp, NULL, screen, &dstrect);
          SDL_FreeSurface(temp);
          return;
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT) {
            SDL_BlitSurface(temp, NULL, screen, &dstrect);
            SDL_FreeSurface(temp);
            return;
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
}

