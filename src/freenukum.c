/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Main game starting file
 *******************************************************************/

#include <SDL/SDL.h>
#include <stdlib.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_msgbox.h"
#include "fn_tilecache.h"
#include "fn_error_cmdline.h"
#include "fn_error.h"
#include "fn_picture_splash.h"
#include "fn_mainmenu.h"
#include "fn_infobox.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  SDL_Surface * screen; /* the main screen surface */
  SDL_Surface * wallpaper; /* the background image for title screen */

  Uint8 pixelsize = 2; /* double pixel size */

  fn_tilecache_t tilecache; /* the main tilecache */

  int res; /* results are stored here */

  int choice = 0; /* choice of the main menu */

  char * homedir; /* home directory of the user */
  char tilespath[1024]; /* path to the original game data */

  fn_error_set_handler(fn_error_print_commandline);

  homedir = getenv("HOME");
  if (homedir == NULL) {
    fn_error_print("$HOME environment variable is not set.");
    exit(1);
  }

  snprintf(tilespath, 1024, "%s%s", homedir, "/.freenukum/duke/");

  fn_tilecache_init(&tilecache, pixelsize);

  res = fn_tilecache_loadtiles(&tilecache, tilespath);
  if (res == -1) {
    fn_error_printf(1024, "Could not load tiles.\n"
        "Copy the original game files to %s." , tilespath);
    exit(1);
  }

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
      &wallpaper,
      screen);
  if (!res) {
    exit(1);
  }

  while (choice != FN_MENUCHOICE_QUIT) {
    choice = fn_mainmenu(&tilecache, pixelsize, screen);
    switch(choice) {
      case FN_MENUCHOICE_START:
        fn_infobox_show(pixelsize, &tilecache, screen,
            "Gameplay not implemented yet.");
        break;
      case FN_MENUCHOICE_RESTORE:
        fn_infobox_show(pixelsize, &tilecache, screen,
            "Restore not implemented yet.");
        break;
      case FN_MENUCHOICE_INSTRUCTIONS:
        fn_infobox_show(pixelsize, &tilecache, screen,
            "Instructions not implemented yet.");
        break;
      case FN_MENUCHOICE_ORDERINGINFO:
        fn_infobox_show(pixelsize, &tilecache, screen,
            "Orderinginfo not implemented yet.");
        break;
      case FN_MENUCHOICE_SETUP:
        fn_infobox_show(pixelsize, &tilecache, screen,
            "Setup not implemented yet.");
        break;
      case FN_MENUCHOICE_HIGHSCORES:
        fn_infobox_show(pixelsize, &tilecache, screen,
            "Highscores not implemented yet.");
        break;
      case FN_MENUCHOICE_PREVIEWS:
        fn_infobox_show(pixelsize, &tilecache, screen,
            "Previews not implemented yet.");
        break;
      case FN_MENUCHOICE_VIEWUSERDEMO:
        fn_infobox_show(pixelsize, &tilecache, screen,
            "Userdemo not implemented yet.");
        break;
      case FN_MENUCHOICE_TITLESCREEN:
        res = fn_picture_splash_show(tilespath,
            "DN.DN1",
            &wallpaper,
            screen);
        break;
      case FN_MENUCHOICE_CREDITS:
        fn_infobox_show(pixelsize, &tilecache, screen,
            "Credits not implemented yet.");
        break;
      default:
        break;
    }
  }

  SDL_FreeSurface(wallpaper);
  return 0;
}
