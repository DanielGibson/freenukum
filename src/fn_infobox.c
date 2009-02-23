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
  FnGeometry * destrect;

  int res;

  SDL_Event event;

  msgbox = fn_msgbox(
      env,
      msg);

  FnScreen * screen = fn_environment_get_screen(env);

  destrect = fn_geometry_new(
      (fn_screen_get_width(screen) - fn_texture_get_width(msgbox)) /
      2,
      (fn_screen_get_height(screen) - fn_texture_get_height(msgbox)) /
      2,
      fn_texture_get_width(msgbox),
      fn_texture_get_height(msgbox));

  /* backup the background */
  fn_screen_snapshot_push(screen);

  fn_screen_clone_texture(screen, destrect,
      msgbox, NULL);
  g_object_unref(destrect);
  g_object_unref(msgbox);

  fn_screen_update(screen);

  while (1) {
    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_KEYDOWN:
          fn_screen_snapshot_pop(screen);
          return;
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT) {
            fn_screen_snapshot_pop(screen);
            return;
          }
          break;
        case SDL_VIDEOEXPOSE:
          fn_screen_update(screen);
          break;
        default:
          /* ignore other events */
          break;
      }
    }
  }
}

