/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Splash a picture to the screen
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

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_draw.h"
#include "fn_picture.h"
#include "fn_picture_splash.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"
#include "fn.h"
#include "fn_msgbox.h"

/* --------------------------------------------------------------- */

#define MAX(X,Y) ((X)>(Y) ? (X) : (Y))

/* --------------------------------------------------------------- */

int fn_picture_splash_show(char * datapath,
    char * filename,
    Uint8 pixelsize,
    SDL_Surface * screen)
{
  return fn_picture_splash_show_with_message(datapath,
      filename,
      pixelsize,
      screen,
      NULL,
      NULL,
      0,0);
}

/* --------------------------------------------------------------- */

int fn_picture_splash_show_with_message(char * datapath,
    char * filename,
    Uint8 pixelsize,
    SDL_Surface * screen,
    fn_tilecache_t * tilecache,
    char * msg,
    Uint8 x,
    Uint8 y)
{
  char * path;
  int fd;
  int res;
  SDL_Event event;
  SDL_Surface * picture;

  path = malloc(strlen(datapath) + strlen(filename) + 1);
  sprintf(path, "%s%s", datapath, filename);
  fd = open(path, O_RDONLY);

  if (fd == -1) {
    fn_error_printf(1024, "Could not open file %s for reading: %s",
        path,strerror(errno));
    free(path);
    return 0;
  }
  free(path);

  Uint32 flags = screen->flags;

  picture = fn_picture_load(fd, pixelsize, flags, screen->format);

  SDL_BlitSurface(picture, NULL, screen, NULL);


  if (tilecache != NULL && msg != NULL) {
    SDL_Surface * msgbox;
    SDL_Rect dstrect;

    msgbox = fn_msgbox(pixelsize,
        screen->flags,
        screen->format,
        tilecache,
        msg);

    dstrect.x = x * pixelsize;
    dstrect.y = y * pixelsize;

    SDL_BlitSurface(msgbox, NULL, screen, &dstrect);
    SDL_FreeSurface(msgbox);
  }

  SDL_UpdateRect(screen, 0, 0, 0, 0);
  SDL_FreeSurface(picture);

  while (1) {
    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_QUIT:
          return 1;
          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
            case SDLK_RETURN:
              return 1;
            default:
              /* ignore other keys */
              break;
          }
        case SDL_VIDEOEXPOSE:
          SDL_UpdateRect(screen, 0, 0, 0, 0);
          break;
        default:
          /* ignore unknown events */
          break;
      }
    }
  }
  return 0;
}
