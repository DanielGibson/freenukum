/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Main game starting file
 *******************************************************************/

#include <SDL/SDL.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_msgbox.h"
#include "fn_tilecache.h"
#include "fn_error_cmdline.h"
#include "fn_error.h"
#include "fn_picture_splash.h"
#include "fn_mainmenu.h"
#include "fn_infobox.h"
#include "fn_settings.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  SDL_Surface * screen; /* the main screen surface */

  long int pixelsize; /* pixel size */

  fn_tilecache_t tilecache; /* the main tilecache */

  int res; /* results are stored here */

  int choice = 0; /* choice of the main menu */

  char * homepath; /* home directory of the user */
  char configpath[1024]; /* path to the settings directory */
  char datapath[1024]; /* path to the original game data */
  char configfilepath[1024]; /* path to the config file */

  DIR * configdir; /* directory pointer to the config directory */
  DIR * datadir; /* directory pointer to the data directory */

  fn_settings_t * settings; /* the settings struct */

/* --------------------------------------------------------------- */

  fn_error_set_handler(fn_error_print_commandline);

  /* retrieve home directory path */
  homepath = getenv("HOME");
  if (homepath == NULL) {
    fn_error_print("$HOME environment variable is not set.");
    exit(1);
  }

  snprintf(configpath, 1024, "%s%s", homepath, "/.freenukum");
  snprintf(datapath, 1024, "%s%s", configpath, "/data/");
  snprintf(configfilepath, 1024, "%s%s", configpath, "/config");

  /* check if .freenukum directory exists and create it if
   * it does not exist yet */
  configdir = opendir(configpath);
  if (configdir == NULL) {
    res = mkdir(configpath, S_IRUSR | S_IWUSR | S_IXUSR
        | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    if (res) {
      fn_error_printf(1024, "Could not create the directory %s: %s",
          configpath, strerror(errno));
      exit(1);
    }
  }
  closedir(configdir);

  /* check if data directory exists and create it if
   * it does not exist yet */
  datadir = opendir(datapath);
  if (datadir == NULL) {
    res = mkdir(datapath, S_IRUSR | S_IWUSR | S_IXUSR
        | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    if (res) {
      fn_error_printf(1024, "Could not create the directory %s: %s",
          datapath, strerror(errno));
      exit(1);
    }
  }
  closedir(datadir);

  /* load the settings from the config file and
   * create the file if it does not exist */
  settings = fn_settings_new_from_file(configfilepath);
  if (settings == NULL) {
    settings = fn_settings_new();
    res = fn_settings_store(settings, configfilepath);
    if (!res) {
      fn_error_printf(1024, "Could not create the settings file %s: %s",
          configfilepath, strerror(errno));
      exit(1);
    }
  }

  /* load pixelsize from config */
  fn_settings_get_longint_with_default(settings, "pixelsize",
      &pixelsize, FN_DEFAULT_PIXELSIZE);

  /* initialize the tile cache */
  fn_tilecache_init(&tilecache, (Uint8)pixelsize);
  res = fn_tilecache_loadtiles(&tilecache, datapath);
  if (res == -1) {
    fn_error_printf(1024, "Could not load tiles.\n"
        "Copy the original game files to %s" , datapath);
    exit(1);
  }

  /* initialize SDL */
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fn_error_printf(1024, "Could not initialize SDL: %s", SDL_GetError());
    exit(1);
  }

  /* initialize SDL window */
  screen = SDL_SetVideoMode(
      FN_WINDOW_WIDTH * pixelsize,
      FN_WINDOW_HEIGHT * pixelsize,
      FN_COLOR_DEPTH,
      SDL_SWSURFACE);
  if (screen == NULL) {
    fn_error_printf(1024, "Can't set video mode: %s", SDL_GetError());
    exit(1);
  }

  /* show the splash screen */
  res = fn_picture_splash_show(
      datapath,
      "DN.DN1",
      (Uint8)pixelsize,
      screen);
  if (!res) {
    exit(1);
  }

  /* show the main menu */
  while (choice != FN_MENUCHOICE_QUIT) {
    choice = fn_mainmenu(&tilecache, (Uint8)pixelsize, screen);
    switch(choice) {
      case FN_MENUCHOICE_START:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Gameplay not implemented yet.");
        break;
      case FN_MENUCHOICE_RESTORE:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Restore not implemented yet.");
        break;
      case FN_MENUCHOICE_INSTRUCTIONS:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Instructions not implemented yet.");
        break;
      case FN_MENUCHOICE_ORDERINGINFO:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Orderinginfo not implemented yet.");
        break;
      case FN_MENUCHOICE_SETUP:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Setup not implemented yet.");
        break;
      case FN_MENUCHOICE_HIGHSCORES:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Highscores not implemented yet.");
        break;
      case FN_MENUCHOICE_PREVIEWS:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Previews not implemented yet.");
        break;
      case FN_MENUCHOICE_VIEWUSERDEMO:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Userdemo not implemented yet.");
        break;
      case FN_MENUCHOICE_TITLESCREEN:
        res = fn_picture_splash_show(datapath,
            "DN.DN1",
            (Uint8)pixelsize,
            screen);
        break;
      case FN_MENUCHOICE_CREDITS:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Credits not implemented yet.");
        break;
      default:
        break;
    }
  }

  res = fn_settings_store(settings, configfilepath);
  if (!res) {
    fn_error_printf(1024, "Could not store settings to %s: %s",
        configfilepath, strerror(errno));
  }
  return 0;
}
