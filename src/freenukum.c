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
#include "fn_environment.h"
#include "fntexture.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  g_type_init();

  int res = 0; /* results are stored here */

  int retval = 1; /* The return value from the program. */

  int choice = 0; /* choice of the main menu */

  /* TODO move this into fn_environment. */
  char backgroundfile[10] = "DN.DN1";
/* --------------------------------------------------------------- */

  fn_error_set_handler(fn_error_print_commandline);

  fn_environment_t * env = fn_environment_create();

/* --------------------------------------------------------------- */

  /* check if all data is present */
  int episodes = fn_environment_check_for_episodes(env);
  if (episodes == 0) {
    exit(retval);
  }

  /* load the tilecache */
  res = fn_environment_load_tilecache(env);

  /* show the splash screen */
  res = fn_picture_splash_show(
      env,
      backgroundfile);
  if (!res) {
    fn_error_printf(1024, "Could not show splash screen.\n");
    exit(retval);
  }

  /* show the main menu */
  while (choice != FN_MENUCHOICE_QUIT) {
    choice = fn_mainmenu(env);
    switch(choice) {
      case FN_MENUCHOICE_START:
        fn_game_start(
            env);
        res = fn_picture_splash_show(
            env,
            backgroundfile);
        break;
      case FN_MENUCHOICE_RESTORE:
        fn_infobox_show(env,
            "Restore not implemented yet.\n");
        break;
      case FN_MENUCHOICE_INSTRUCTIONS:
        fn_infobox_show(env,
            "Instructions not implemented yet.\n");
        break;
      case FN_MENUCHOICE_ORDERINGINFO:
        fn_infobox_show(env,
            "Orderinginfo not implemented yet.\n");
        break;
      case FN_MENUCHOICE_FULLSCREENTOGGLE:
        {
          fn_environment_toggle_fullscreen(env);
        }
        break;
      case FN_MENUCHOICE_EPISODECHANGE:
        {
          Uint8 episode = fn_environment_get_episode(env);
          episode++;
          if (episode > 3) {
            episode = 1;
          }
          snprintf(backgroundfile,
              7, "DN.DN%d", episode);
          res = fn_picture_splash_show(env, backgroundfile);
          if (res == 0) {
            fn_infobox_show(env,
                "You don't have this episode installed.\n"
                "We stay in episode 1\n");
            episode = 1;
            snprintf(backgroundfile,
                7, "DN.DN%d", episode);
            res = fn_picture_splash_show(env,
                backgroundfile);
          } else {
            fn_environment_set_episode(env, episode);
          }
        }
        break;
      case FN_MENUCHOICE_HIGHSCORES:
        fn_infobox_show(env,
            "Highscores not implemented yet.\n");
        break;
      case FN_MENUCHOICE_PREVIEWS:
        fn_infobox_show(env,
            "Previews not implemented yet.\n");
        break;
      case FN_MENUCHOICE_VIEWUSERDEMO:
        fn_infobox_show(env,
            "Userdemo not implemented yet.\n");
        break;
      case FN_MENUCHOICE_TITLESCREEN:
        res = fn_picture_splash_show(env,
            backgroundfile);
        break;
      case FN_MENUCHOICE_CREDITS:
        fn_infobox_show(env,
            "Credits not implemented yet.\n");
        break;
      default:
        break;
    }
  }

  fn_environment_store_settings(env);

  retval = 0;

  fn_environment_delete(env);

  return retval;
}
