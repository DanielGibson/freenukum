/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Setting up the freenukum environment
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

/* --------------------------------------------------------------- */

#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

#ifdef HAVE_SDL_SDL_TTF_H
#include <SDL/SDL_ttf.h>
#endif /* HAVE_SDL_SDL_TTF_H */

/* --------------------------------------------------------------- */

#include "fn_environment.h"
#include "fn_error.h"
#include "fn_data.h"

/* --------------------------------------------------------------- */

char * font_base_directories[] = {
  "/usr/share/fonts",
  "/usr/share/fonts/truetype",
  "/usr/local/share/fonts",
  "/usr/local/share/fonts/truetype",
  "/usr/share/fonts/TTF",
  0
};

char * fonts[] = {
  "/DejaVuSans.ttf",
  "/DejavuSerif.ttf",
  "/linux-libertine/LinLibertine.ttf",
  "/linux-libertine/LinLibertine_Re.ttf",
  "/freefont/FreeMono.ttf",
  "/freefont/FreeSans.ttf",
  "/freefont/FreeSerif.ttf",
  "/dustin/Balker.ttf",
  "/dustin/Dustismo.ttf",
  "/kochi/kochi-gothic.ttf",
  "/kochi/kochi-mincho.ttf",
  "/msttcorefonts/arial.ttf",
  "/msttcorefonts/Arial.ttf",
  "/msttcorefonts/Arial_Black.ttf",
  "/msttcorefonts/times.ttf",
  "/msttcorefonts/verdana.ttf",
  "/ttf-bitstream-vera/Vera.ttf",
  "/ttf-dejavu/DejaVuSans.ttf",
  "/ttf-dejavu/DejaVuSansMono.ttf",
  "/unfonts/UnBatang.ttf",
  "/unfonts/UnDotum.ttf",
  0
};

/* --------------------------------------------------------------- */

#ifdef HAVE_SDL_SDL_TTF_H
TTF_Font * fn_environment_loadfont(fontsize)
{
  TTF_Font * font = NULL;
  char path[256] = "";

  int i = 0;
  int j = 0;
  while (fonts[i] != 0) {
    while (font_base_directories[j] != 0) {
      snprintf(path, 256, "%s%s",
          font_base_directories[j], fonts[i]);
      font = TTF_OpenFont(path, fontsize);
      if (font) {
        return font;
      }
      j++;
    }
    i++;
    j=0;
  }

  printf("Could not find any font.");
  return font;
}
#endif /* HAVE_SDL_SDL_TTF_H */

/* --------------------------------------------------------------- */

char const * const subpath_config = "/.freenukum";
char const * const subpath_data = "/data";
char const * const subpath_configfile = "/config";

/* --------------------------------------------------------------- */

fn_environment_t * fn_environment_create()
{
  /* create the environment */
  fn_environment_t * env = malloc(sizeof(fn_environment_t));

  /* fill with default values */
  env->pixelsize = 2;
  env->videoflags = FN_SURFACE_FLAGS;
  env->transparent = 0;
  env->fullscreen = 0;
  env->draw_collision_bounds = 0;
  env->configfilepath = NULL;
  env->datapath = NULL;
  env->settings = NULL;
  env->screen = NULL;
  env->tilecache = NULL;
  env->episode = 1;
  env->num_episodes = 0;
  env->health = FN_NUM_MAXLIFE;
  env->firepower = 1;
  env->inventory = 0x00;
  env->score = 0;

  /* create all the path variables */
  char * homepath = getenv("HOME");

  if (homepath == NULL) {
    homepath = ".";
  }

  size_t configpath_size =
    strlen(subpath_config) +
    strlen(homepath) +
    2;
  char * configpath = malloc(configpath_size);
  snprintf(configpath, configpath_size, "%s%s",
      homepath, subpath_config);

  size_t configfilepath_size =
    strlen(configpath) +
    strlen(subpath_configfile) +
    2;
  env->configfilepath = malloc(configfilepath_size);
  snprintf(env->configfilepath, configfilepath_size, "%s%s",
      configpath, subpath_configfile);

  size_t datapath_size =
    strlen(configpath) +
    strlen(subpath_data) +
    2;
  env->datapath = malloc(datapath_size);
  snprintf(env->datapath, datapath_size, "%s%s",
      configpath, subpath_data);

  /* check if the paths exist and create them if necessary */
  DIR * configdir = opendir(configpath);
  if (configdir == NULL) {
    int res = mkdir(configpath, S_IRUSR | S_IWUSR | S_IXUSR
        | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    if (res) {
      fn_error_printf(1024, "Could not create the directory %s: %s",
          configpath, strerror(errno));
      return env;
    }
  }
  closedir(configdir);
  free(configpath); configpath = NULL;

  DIR * datadir = opendir(env->datapath);
  if (datadir == NULL) {
    int res = mkdir(env->datapath, S_IRUSR | S_IWUSR | S_IXUSR
        | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    if (res) {
      fn_error_printf(1024, "Could not create the directory %s: %s",
          env->datapath, strerror(errno));
      return env;
    }
  }

  /* load the settings from the config file and
   * create the file if it does not exist. */
  env->settings = fn_settings_new_from_file(env->configfilepath);
  if (env->settings == NULL) {
    env->settings = fn_settings_new();
    int res = fn_settings_store(env->settings, env->configfilepath);
    if (!res) {
      fn_error_printf(1024, "Could not create the settings file %s: %s",
          env->configfilepath, strerror(errno));
      return env;
    }
  }

  /* TODO rewrite this once we can load uint8 from the settings */
  long int pixelsize = 0;
  fn_settings_get_longint_with_default(env->settings,
      "pixelsize",
      &pixelsize, FN_DEFAULT_PIXELSIZE);
  env->pixelsize = (Uint8)pixelsize;

  fn_settings_get_bool_with_default(env->settings,
      "fullscreen",
      &(env->fullscreen), FN_DEFAULT_FULLSCREEN);

  fn_settings_get_bool_with_default(env->settings,
      "draw_collision_bounds",
      &(env->draw_collision_bounds), FN_DEFAULT_DRAWCOLLISIONBOUNDS);

  if (env->fullscreen) {
    env->videoflags |= SDL_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
    fn_error_printf(1024,
        "Could not initialize SDL: %s", SDL_GetError());
    return env;
  }

  env->screen = SDL_SetVideoMode(
      FN_WINDOW_WIDTH * env->pixelsize,
      FN_WINDOW_HEIGHT * env->pixelsize,
      FN_COLOR_DEPTH,
      env->videoflags);
  if (env->screen == NULL) {
    fn_error_printf(1024, "Can't set video mode: %s", SDL_GetError());
    return env;
  }

  env->transparent = SDL_MapRGB(env->screen->format, 100, 1, 1);

  SDL_WM_SetCaption("Freenukum " VERSION, "Freenukum " VERSION);

  env->initialized = 1;
  return env;
}

/* --------------------------------------------------------------- */

void fn_environment_delete(fn_environment_t * env)
{
  if (env->settings != NULL) {
    fn_settings_free(env->settings); env->settings = NULL;
  }
  if (env->configfilepath != NULL) {
    free(env->configfilepath); env->configfilepath = NULL;
  }
  if (env->datapath != NULL) {
    free(env->datapath); env->datapath = NULL;
  }
  if (env->tilecache != NULL) {
    fn_tilecache_destroy(env->tilecache); env->tilecache = NULL;
  }
  if (env->screen != NULL) {
    SDL_FreeSurface(env->screen); env->screen = NULL;
  }
  free(env);

  SDL_Quit();
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_check_for_episodes(fn_environment_t * env)
{
  env->num_episodes = 0;

  int res = 0;

  while (res != -1) {
    res = fn_data_check(env->datapath, env->num_episodes + 1);
    if (res == -1 && env->num_episodes == 0) {
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
          "%s\n", env->datapath);
      snprintf(message_screen, 1024,
          "%s\n"
          "%s\n",
          message_cmdline,
          downloadinfo);
      printf("%s\n", message_cmdline);
#ifdef HAVE_SDL_SDL_TTF_H
      TTF_Font * font = NULL;
      int fontsize = 10 * env->pixelsize;
      if (TTF_Init() != -1) {
        font = fn_environment_loadfont(fontsize);
      }
      if (font) {
        fn_data_display_text(env->screen, 0, 0, font, message_screen);
        SDL_UpdateRect(
            env->screen, 0, 0, env->screen->w, env->screen->h);

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
        if (can_download && input == 'd') {
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
        return 0;
      }
    } else if (res != -1) {
      /* we found the currently requested episode */
      env->num_episodes++;
    }
  }

  return env->num_episodes;
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_load_tilecache(fn_environment_t * env)
{
  env->tilecache = fn_tilecache_create();
  return fn_tilecache_loadtiles(env->tilecache, env);
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_get_pixelsize(fn_environment_t * env)
{
  return env->pixelsize;
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_get_fullscreen(fn_environment_t * env)
{
  return env->fullscreen;
}

/* --------------------------------------------------------------- */

void fn_environment_toggle_fullscreen(fn_environment_t * env)
{
  int res = SDL_WM_ToggleFullScreen(env->screen);
  if (res) {
    env->fullscreen = (env->fullscreen + 1) % 2;
    fn_settings_set_bool(env->settings, "fullscreen", env->fullscreen);
  }
}

/* --------------------------------------------------------------- */

Uint32 fn_environment_get_transparent(fn_environment_t * env)
{
  return env->transparent;
}

/* --------------------------------------------------------------- */

SDL_Surface * fn_environment_create_surface(fn_environment_t * env,
   int width, int height)
{
  return fn_environment_create_surface_with_aboslute_size(
      env, width * env->pixelsize, height * env->pixelsize);
}

/* --------------------------------------------------------------- */

SDL_Surface * fn_environment_create_surface_with_aboslute_size(
    fn_environment_t * env,
    int width, int height)
{
  SDL_Surface * surface = SDL_CreateRGBSurface(
      env->screen->flags,
      width,
      height,
      env->screen->format->BitsPerPixel,
      0,
      0,
      0,
      0);

  SDL_SetColorKey(surface, SDL_SRCCOLORKEY, env->transparent);

  return surface;
}

/* --------------------------------------------------------------- */

SDL_Surface * fn_environment_get_screen(fn_environment_t * env)
{
  return env->screen;
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_get_episode(fn_environment_t * env)
{
  return env->episode;
}

/* --------------------------------------------------------------- */

void fn_environment_set_episode(fn_environment_t * env,
    Uint8 episode)
{
  env->episode = episode;
}

/* --------------------------------------------------------------- */

SDL_Surface * fn_environment_get_tile(fn_environment_t * env,
    size_t pos)
{
  if (env->tilecache == NULL) {
    return NULL;
  }
  return fn_tilecache_get_tile(env->tilecache, pos);
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_get_health(fn_environment_t * env)
{
  return env->health;
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_get_firepower(fn_environment_t * env)
{
  return env->firepower;
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_get_inventory(fn_environment_t * env)
{
  return env->inventory;
}

/* --------------------------------------------------------------- */

Uint32 fn_environment_get_score(fn_environment_t * env)
{
  return env->score;
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_get_draw_collision_bounds(
    fn_environment_t * env)
{
  return env->draw_collision_bounds;
}

/* --------------------------------------------------------------- */

char * fn_environment_get_datapath(fn_environment_t * env)
{
  return env->datapath;
}

/* --------------------------------------------------------------- */

fn_tilecache_t * fn_environment_get_tilecache(fn_environment_t * env)
{
  return env->tilecache;
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_tilecache_loaded(fn_environment_t * env)
{
  return (env->tilecache != NULL);
}

/* --------------------------------------------------------------- */

Uint8 fn_environment_store_settings(fn_environment_t * env)
{
  int res = 0;
  res = fn_settings_store(env->settings, env->configfilepath);
  if (!res) {
    fn_error_printf(1024, "Could not store settings to %s: %s",
        env->configfilepath, strerror(errno));
  }
  return res;
}

/* --------------------------------------------------------------- */

