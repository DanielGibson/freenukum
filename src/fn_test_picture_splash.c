/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tests for picture splash functions
 *******************************************************************/

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"
#include "fn_picture_splash.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  Uint8 pixelsize = 2;
  int res;
  char * homedir;
  char tilespath[1024];
  SDL_Surface * screen;

  fn_error_set_handler(fn_error_print_commandline);

  homedir = getenv("HOME");
  if (homedir == NULL) {
    fn_error_print("$HOME environment variable is not set.");
    exit(1);
  }

  snprintf(tilespath, 1024, "%s%s", homedir, "/.freenukum/data/");

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fn_error_printf(1024, "Could not initialize SDL: %s", SDL_GetError());
    exit(1);
  }

  screen = SDL_SetVideoMode(
      FN_WINDOW_WIDTH * pixelsize,
      FN_WINDOW_HEIGHT * pixelsize,
      FN_COLOR_DEPTH,
      SDL_SWSURFACE);

  if (screen == NULL) {
    fn_error_printf(1024, "Can't set video mode: %s", SDL_GetError());
    exit(1);
  }

  res = fn_picture_splash_show(tilespath,
      "DN.DN1",
      (Uint8) pixelsize,
      screen);
  
  return 0;
}
