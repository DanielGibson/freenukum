/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Gameplay functions
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
    "Hello Proton!",
    0
  };
  char * msg2[] = {
    "Hi Duke.",
    0
  };

  res = fn_picture_splash_show_with_message(
      datapath,
      "DUKE.DN1",
      (Uint8)pixelsize,
      screen,
      tilecache,
      msg1,
      100,
      100);

  res = fn_picture_splash_show_with_message(
      datapath,
      "BADGUY.DN1",
      (Uint8)pixelsize,
      screen,
      tilecache,
      msg2,
      100,
      100);

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
