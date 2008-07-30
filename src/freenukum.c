/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Main game starting file
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_SDL_SDL_TTF_H
#ifdef HAVE_LIBCURL
#ifdef HAVE_LIBZIP
#define HAVE_AUTOMATIC_DOWNLOAD 1
#endif /* HAVE_LIBZIP */
#endif /* HAVE_LIBCURL */
#endif /* HAVE_SDL_SDL_TTF_H */

/* --------------------------------------------------------------- */

#include <SDL.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#ifdef HAVE_SDL_SDL_TTF_H
#include <SDL/SDL_ttf.h>
#endif /* HAVE_SDL_SDL_TTF_H */

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
#include "fn_game.h"
#include "fn_data.h"

/* --------------------------------------------------------------- */

#ifdef HAVE_SDL_SDL_TTF_H
TTF_Font * loadfont(fontsize)
{
  TTF_Font * font = NULL;
  /* TODO read from more paths */
  font = TTF_OpenFont("/usr/share/fonts/truetype/linux-libertine/"
      "LinLibertine_Re.ttf", fontsize);
  if (!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
  }
  return font;
}
#endif /* HAVE_SDL_SDL_TTF_H */

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  SDL_Surface * screen; /* the main screen surface */

  long int pixelsize; /* pixel size */
  Uint8 fullscreen; /* Play fullscreen? */

  fn_tilecache_t tilecache; /* the main tilecache */

  int res; /* results are stored here */

  int retval = 1; /* The return value from the program. */

  int choice = 0; /* choice of the main menu */

  char * homepath; /* home directory of the user */
  char configpath[1024]; /* path to the settings directory */
  char datapath[1024]; /* path to the original game data */
  char configfilepath[1024]; /* path to the config file */

  DIR * configdir; /* directory pointer to the config directory */
  DIR * datadir; /* directory pointer to the data directory */

  fn_settings_t * settings = NULL; /* the settings struct */

  Uint8 episode = 1; /* The episode currently being played. */

  char backgroundfile[10] = "DN.DN1";

  Uint32 videoflags = FN_SURFACE_FLAGS;

/* --------------------------------------------------------------- */

  fn_error_set_handler(fn_error_print_commandline);

  /* retrieve home directory path */
  homepath = getenv("HOME");
  if (homepath == NULL) {
    fn_error_print("$HOME environment variable is not set.");
    goto homepath_failed;
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
      goto configdir_failed;
    }
  }

  /* check if data directory exists and create it if
   * it does not exist yet */
  datadir = opendir(datapath);
  if (datadir == NULL) {
    res = mkdir(datapath, S_IRUSR | S_IWUSR | S_IXUSR
        | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    if (res) {
      fn_error_printf(1024, "Could not create the directory %s: %s",
          datapath, strerror(errno));
      goto datadir_failed;
    }
  }

  /* load the settings from the config file and
   * create the file if it does not exist */
  settings = fn_settings_new_from_file(configfilepath);
  if (settings == NULL) {
    settings = fn_settings_new();
    res = fn_settings_store(settings, configfilepath);
    if (!res) {
      fn_error_printf(1024, "Could not create the settings file %s: %s",
          configfilepath, strerror(errno));
      goto settings_failed;
    }
  }

  /* load pixelsize from config */
  fn_settings_get_longint_with_default(settings, "pixelsize",
      &pixelsize, FN_DEFAULT_PIXELSIZE);
  fn_settings_get_bool_with_default(settings, "fullscreen",
      &fullscreen, FN_DEFAULT_FULLSCREEN);

  if (fullscreen) {
    videoflags |= SDL_FULLSCREEN;
  }

  /* initialize SDL */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
    fn_error_printf(1024, "Could not initialize SDL: %s", SDL_GetError());
    goto sdl_init_failed;
  }

  /* initialize SDL window */
  screen = SDL_SetVideoMode(
      FN_WINDOW_WIDTH * pixelsize,
      FN_WINDOW_HEIGHT * pixelsize,
      FN_COLOR_DEPTH,
      videoflags);
  if (screen == NULL) {
    fn_error_printf(1024, "Can't set video mode: %s", SDL_GetError());
    goto sdl_videomode_failed;
  }

  /* set window caption */
  SDL_WM_SetCaption("Freenukum " VERSION, "Freenukum " VERSION);

  /* check if all data is present */
  int episodes = 0;
  while (res != -1) {
    res = fn_data_check(datapath, episodes + 1);
    if (res == -1 && episodes == 0) {
      /* we found no episodes */
      int succeeded = 0;
      int can_download = fn_data_download_possible();
      char downloadinfo[1024] = "";
      if (can_download) {
        snprintf(downloadinfo, 1024,
            "\n"
            "I can try to download the files automatically.\n"
            "\n"
            "Press ENTER for automatic download\n"
            "Press ESCAPE to abort.");
      } else {
        snprintf(downloadinfo, 1024,
            "\n"
            "Press any key to close this window.");
      }
      char message_cmdline[1024];
      char message_screen[1024];
      snprintf(message_cmdline, 1024,
          "Could not load data level and graphics files.\n"
          "You can download the shareware episode for free from\n"
          "http://www.3drealms.com/duke1/\n"
          "Copy the data files to\n"
          "%s\n", datapath);
      snprintf(message_screen, 1024,
          "%s\n"
          "%s\n",
          message_cmdline,
          downloadinfo);
      printf("%s\n", message_cmdline);
#ifdef HAVE_SDL_SDL_TTF_H
      TTF_Font * font = NULL;
      int fontsize = 10 * pixelsize;
      if (TTF_Init() != -1) {
        font = loadfont(fontsize);
      }
      if (font) {
        fn_data_display_text(screen, 0, 0, font, message_screen);
        SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);

        SDL_Event event;

        char input = 0;
        while (input == 0) {
          res = SDL_WaitEvent(&event);
          if (res == 1) {
            switch(event.type) {
              case SDL_QUIT:
                input = 'q';
                break;
              case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                  case SDLK_RETURN:
                    input = 'd';
                    break;
                  case SDLK_ESCAPE:
                    input = 'q';
                    break;
                  default:
                    /* do nothing */
                    break;
                }
              default:
                /* do nothing on other events */
                break;
            }
          }
        }
#ifdef HAVE_AUTOMATIC_DOWNLOAD
        if (input == 'd') {
          succeeded =
            fn_data_download(screen, font, fontsize, datapath);

          if (!succeeded) {
            input = 0;
            Uint32 black = SDL_MapRGB(screen->format, 0, 0, 0);
            SDL_FillRect(screen, NULL, black);
            fn_data_display_text(screen, 0, 0, font,
                "Download failed. Press ESCAPE to quit.");
            SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
            
            while (input == 0) {
              res = SDL_WaitEvent(&event);
              if (res == 1) {
                switch(event.type) {
                  case SDL_QUIT:
                    input = 'q';
                    break;
                  case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                      case SDLK_ESCAPE:
                        input = 'q';
                        break;
                      default:
                        /* do nothing */
                        break;
                    }
                  default:
                    /* do nothing on other events */
                    break;
                }
              }
            }
          }

          res = 0;
        }
#endif /* HAVE_AUTOMATIC_DOWNLOAD */
        TTF_CloseFont(font);
        font = NULL;
      }
#endif
      if (!succeeded) {
        goto data_check_failed;
      }
    } else if (res != -1) {
      /* we found the currently requested episode */
      episodes++;
    }
  }
  printf("Found %d episodes.\n", episodes);

  /* initialize the tile cache */
  fn_tilecache_init(&tilecache, (Uint8)pixelsize);
  res = fn_tilecache_loadtiles(
      &tilecache,
      screen->flags,
      screen->format,
      datapath);
  if (res == -1) {
    fn_error_printf(1024, "Could not load tiles.\n"
        "Copy the original game files to %s.\n"
        "They can be downloaded free of charge from\n"
        "http://www.3drealms.com/duke1/", datapath);
    /* TODO show text in screen maybe? */
    goto tilecache_failed;
  }


  /* show the splash screen */
  res = fn_picture_splash_show(
      datapath,
      backgroundfile,
      (Uint8)pixelsize,
      screen);
  if (!res) {
    fn_error_printf(1024, "Could not show splash screen.\n");
    goto splashscreen_failed;
  }

  /* show the main menu */
  while (choice != FN_MENUCHOICE_QUIT) {
    choice = fn_mainmenu(&tilecache, (Uint8)pixelsize, screen);
    switch(choice) {
      case FN_MENUCHOICE_START:
        fn_game_start(
            (Uint8)pixelsize, &tilecache, screen, datapath, episode,
            settings);
        res = fn_picture_splash_show(datapath,
            backgroundfile,
            (Uint8)pixelsize,
            screen);
        break;
      case FN_MENUCHOICE_RESTORE:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Restore not implemented yet.\n");
        break;
      case FN_MENUCHOICE_INSTRUCTIONS:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Instructions not implemented yet.\n");
        break;
      case FN_MENUCHOICE_ORDERINGINFO:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Orderinginfo not implemented yet.\n");
        break;
      case FN_MENUCHOICE_SETUP:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Setup not implemented yet.\n");
        break;
      case FN_MENUCHOICE_FULLSCREENTOGGLE:
        {
          int res = SDL_WM_ToggleFullScreen(screen);
          if (res) {
            fullscreen = (fullscreen + 1) % 2;
            fn_settings_set_bool(settings, "fullscreen", fullscreen);
          }
        }
        break;
      case FN_MENUCHOICE_EPISODECHANGE:
        {
          episode++;
          if (episode > 3) {
            episode = 1;
          }
          snprintf(backgroundfile,
              7, "DN.DN%d", episode);
          res = fn_picture_splash_show(datapath,
              backgroundfile, (Uint8)pixelsize, screen);
          if (res == 0) {
            fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
                "You don't have this episode installed.\n"
                "We stay in episode 1\n");
            episode = 1;
            snprintf(backgroundfile,
                7, "DN.DN%d", episode);
            res = fn_picture_splash_show(datapath,
                backgroundfile, (Uint8)pixelsize, screen);
          }
        }
        break;
      case FN_MENUCHOICE_HIGHSCORES:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Highscores not implemented yet.\n");
        break;
      case FN_MENUCHOICE_PREVIEWS:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Previews not implemented yet.\n");
        break;
      case FN_MENUCHOICE_VIEWUSERDEMO:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Userdemo not implemented yet.\n");
        break;
      case FN_MENUCHOICE_TITLESCREEN:
        res = fn_picture_splash_show(datapath,
            backgroundfile,
            (Uint8)pixelsize,
            screen);
        break;
      case FN_MENUCHOICE_CREDITS:
        fn_infobox_show((Uint8)pixelsize, &tilecache, screen,
            "Credits not implemented yet.\n");
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

  retval = 0;

splashscreen_failed:
  fn_tilecache_destroy(&tilecache);
tilecache_failed:
data_check_failed:
sdl_videomode_failed:
  SDL_Quit();
sdl_init_failed:
  fn_settings_free(settings);
settings_failed:
  closedir(datadir);
datadir_failed:
  closedir(configdir);
configdir_failed:
homepath_failed:
  return retval;
}
