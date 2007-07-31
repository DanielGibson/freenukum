/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Main menu
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

  Uint8 width = 13; /* the width of the menu (two letters is one unit) */
  Uint8 height = 9; /* the height of the menu (two letters is one unit) */

  fn_msgbox_t mb;
  int res = 0;
  int choice = 0;
  char * msg[] = {
    " FREENUKUM MAIN MENU",
    " ------------------- ",
    "",
    "S)tart a new game",
    "R)estore an old game",
    "I)nstructions",
    "O)rdering information",
    "G)ame setup",
    "H)igh scores",
    "P)reviews/Main Demo!",
    "V)iew user demo",
    "T)itle screen",
    "C)redits",
    "Q)it to DOS",
    0
  };

  SDL_Event event;

  fn_msgbox_init(&mb, pixelsize, width, height);
  fn_msgbox_settext(&mb, msg);

  msgbox = fn_msgbox_getsurface(&mb, tilecache);

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
    res = SDL_PollEvent(&event);
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
