/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Gameplay functions
 *******************************************************************/

#include "fn_game.h"
#include "fn_borders.h"

/* --------------------------------------------------------------- */

void fn_game_start(
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    SDL_Surface * screen)
{
  SDL_Event event;
  int res;

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
