/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Infobox drawing function
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

#include "fn_infobox.h"
#include "fn_msgbox.h"

/* --------------------------------------------------------------- */

#define MAX(X,Y) ((X)>(Y) ? (X) : (Y))

/* --------------------------------------------------------------- */

void fn_infobox_show(
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    SDL_Surface * screen,
    char * text)
{
  SDL_Surface * msgbox;
  SDL_Surface * temp;
  fn_msgbox_t mb;

  int width = 0;
  int height = 0;

  SDL_Rect dstrect;

  char * localtext;

  int lines = 1;

  char * start, * end, * walker;
  char ** msg;

  int res;

  SDL_Event event;

  /* make a local copy of the text that we can change. */
  localtext = malloc(strlen(text)+1);
  strcpy(localtext, text);

  /* set the start and end pointers */
  start = localtext;
  end = localtext + strlen(text);

  /* count the newlines */
  for (walker = start; walker < end; walker++) {
    if ((*walker) == '\n') {
      lines++;
      *walker = '\0';
    }
  }

  height = ((lines) / 2)+2;

  /* alloc index for msgbox lines */
  msg = malloc((lines+1) * sizeof(char *));
  msg[lines] = 0;

  lines = 0;
  walker = start;

  /* fill the index with the line beginnings */
  do {
    if (walker == start || *(walker-1) == '\0')
    {
      msg[lines++] = walker;
      width = (MAX(strlen(walker)/2+2,width));
    }
    walker++;
  } while (walker < end);

  fn_msgbox_init(&mb, pixelsize, width, height);
  fn_msgbox_settext(&mb, msg);

  msgbox = fn_msgbox_getsurface(&mb, tilecache);

  dstrect.x = ((screen->w) - (msgbox->w))/2;
  dstrect.y = ((screen->h) - (msgbox->h))/2;
  dstrect.w = msgbox->w;
  dstrect.h = msgbox->h;

  temp = SDL_CreateRGBSurface(SDL_SWSURFACE,
      dstrect.w, dstrect.h,
      FN_COLOR_DEPTH,
      0, 0, 0, 0);
  SDL_BlitSurface(screen, &dstrect, temp, NULL);

  SDL_BlitSurface(msgbox, NULL, screen, &dstrect);
  SDL_FreeSurface(msgbox);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  while (1) {
    res = SDL_PollEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_KEYDOWN:
          SDL_BlitSurface(temp, NULL, screen, &dstrect);
          SDL_FreeSurface(temp);
          return;
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

