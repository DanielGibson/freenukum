/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Main menu
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

#include "fn_mainmenu.h"
#include "fn_msgbox.h"

/* --------------------------------------------------------------- */

int fn_mainmenu(fn_tilecache_t * tilecache,
    Uint8 pixelsize,
    SDL_Surface * screen)
{
  SDL_Surface * msgbox;
  SDL_Surface * temp;
  SDL_Rect dstrect;

  int res = 0;
  int choice = 0;
  char * msg =
    "\n"
    "  FREENUKUM MAIN MENU \n"
    "  ------------------- \n"
    "\n"
    " S)tart a new game \n"
    " R)estore an old game \n"
    " I)nstructions \n"
    " O)rdering information \n"
    " G)ame setup \n"
    " H)igh scores \n"
    " P)reviews/Main Demo! \n"
    " V)iew user demo \n"
    " T)itle screen \n"
    " C)redits \n"
    " Q)uit to DOS \n"
    "\n";

  SDL_Event event;

  msgbox = fn_msgbox(pixelsize, tilecache, msg);

  dstrect.x = ((screen->w)-(msgbox->w))/2;
  dstrect.y = ((screen->h)-(msgbox->h))/2;
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

  while (!choice) {
    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_s:
            case SDLK_RETURN:
              choice = FN_MENUCHOICE_START;
              break;
            case SDLK_r:
              choice = FN_MENUCHOICE_RESTORE;
              break;
            case SDLK_i:
              choice = FN_MENUCHOICE_INSTRUCTIONS;
              break;
            case SDLK_o:
              choice = FN_MENUCHOICE_ORDERINGINFO;
              break;
            case SDLK_g:
              choice = FN_MENUCHOICE_SETUP;
              break;
            case SDLK_h:
              choice = FN_MENUCHOICE_HIGHSCORES;
              break;
            case SDLK_p:
              choice = FN_MENUCHOICE_PREVIEWS;
              break;
            case SDLK_v:
              choice = FN_MENUCHOICE_VIEWUSERDEMO;
              break;
            case SDLK_t:
              choice = FN_MENUCHOICE_TITLESCREEN;
              break;
            case SDLK_c:
              choice = FN_MENUCHOICE_CREDITS;
              break;
            case SDLK_q:
            case SDLK_ESCAPE:
              choice = FN_MENUCHOICE_QUIT;
              break;
            default:
              /* ignore other input */
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
  SDL_BlitSurface(temp, NULL, screen, &dstrect);
  SDL_FreeSurface(temp);
  return choice;
}
