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

#ifndef FN_ENVIRONMENT_H
#define FN_ENVIRONMENT_H

/* --------------------------------------------------------------- */

#include <unistd.h>
#include <SDL.h>

/* --------------------------------------------------------------- */

typedef struct fn_environment_t fn_environment_t;

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_settings.h"
#include "fn_tilecache.h"
#include "fn_hero.h"

/* --------------------------------------------------------------- */

struct fn_environment_t {
  /**
   * Was the initialization successful?
   */
  Uint8 initialized;

  /**
   * The pixelsize.
   */
  Uint8 pixelsize;

  /**
   * The video flags.
   */
  Uint32 videoflags;

  /**
   * The transparent color.
   */
  Uint32 transparent;

  /**
   * Are we playing fullscreen?
   */
  Uint8 fullscreen;

  /**
   * Draw collision bounds for debugging?
   */
  Uint8 draw_collision_bounds;

  /**
   * The path where the config file is stored.
   */
  char * configfilepath;

  /**
   * The path where the data can be found.
   */
  char * datapath;

  /**
   * The game settings.
   */
  fn_settings_t * settings;

  /**
   * SDL screen
   */
  SDL_Surface * screen;

  /**
   * The tilecache.
   */
  fn_tilecache_t * tilecache;

  /**
   * The episode number.
   */
  Uint8 episode;

  /**
   * The number of episodes available.
   */
  Uint8 num_episodes;

  /**
   * The hero.
   */
  fn_hero_t * hero;
};

/* --------------------------------------------------------------- */

/**
 * Create an environment using the default settings.
 *
 * @return  The completely setup environment. If something goes
 *          wrong, NULL is returned.
 */
fn_environment_t * fn_environment_create();

/* --------------------------------------------------------------- */

/**
 * Delete an allocated environment.
 *
 * @param  env  The environment.
 */
void fn_environment_delete(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Check if there are any episodes available for this environment.
 *
 * @param  env  The environment.
 *
 * @return The number of available episodes.
 */
Uint8 fn_environment_check_for_episodes(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Load the tilecache into an environment.
 *
 * @param  env  The environment.
 *
 * @return  1 on success, 0 on failure.
 */
Uint8 fn_environment_load_tilecache(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Get the pixel size of the environment.
 *
 * @param  env  The environment.
 *
 * @return The pixelsize.
 */
Uint8 fn_environment_get_pixelsize(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Set the pixelsize for the environment.
 *
 * @param  env        The environment.
 * @param  pixelsize  The pixelsize. It must be a number from
 *                    1 to 10. If an invalid number is passed,
 *                    the pixelsize is reset to 1.
 */
void fn_environment_set_pixelsize(fn_environment_t * env,
    Uint8 pixelsize);

/* --------------------------------------------------------------- */

/**
 * Get the information if the environment is in fullscreen mode.
 *
 * @param  env  The environment.
 *
 * @return  1 if the game is in fullscreen mode, 0 if windowed.
 */
Uint8 fn_environment_get_fullscreen(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Toggle fullscreen in an environment.
 *
 * @param  env  The environment.
 */
void fn_environment_toggle_fullscreen(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Get the transparent color of an environment.
 *
 * @param  env  The environment.
 *
 * @return The transparent color.
 */
Uint32 fn_environment_get_transparent(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Create a new SDL Surface with the environment's settings.
 * The user is responsible for freeing that surface on his own by
 * calling SDL_Free on it.
 *
 * @param  env     The environment.
 * @param  width   The width of the surface in original-game pixels.
 *                 The returned width will be multiplied by the
 *                 pixelsize of the environment.
 * @param  height  The height of the surface in orginal-game pixels.
 *                 The returned height will be multiplied by the
 *                 pixelsize of the environment.
 *
 * @return The newly created surface.
 */
SDL_Surface * fn_environment_create_surface(fn_environment_t * env,
    int width,
    int height);

/* --------------------------------------------------------------- */

/**
 * Create a new SDL Surface with the environment's settings.
 * The user is responsible for freeing that surface on his own by
 * calling SDL_Free on it.
 *
 * @param  env     The environment.
 * @param  width   The width of the surface in real pixels.
 * @param  height  The height of the surface in real pixels.
 *
 * @return The newly created surface.
 */
SDL_Surface * fn_environment_create_surface_with_aboslute_size(
    fn_environment_t * env,
    int width,
    int height);

/* --------------------------------------------------------------- */

/**
 * Get the screen to which the environment displays the game.
 *
 * @param  env    The environment.
 *
 * @return  The screen.
 */
SDL_Surface * fn_environment_get_screen(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Get the number of the current episode.
 *
 * @param  env  The environment.
 *
 * @return  The number of the episode.
 */
Uint8 fn_environment_get_episode(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Switch the environment to an episode.
 *
 * @param  env      The environment.
 * @param  episode  The episode number.
 */
void fn_environment_set_episode(fn_environment_t * env,
    Uint8 episode);

/* --------------------------------------------------------------- */

/**
 * Get a tile from the environment's tilecache.
 *
 * @param  env  The environment.
 * @param  pos  The number of the tile.
 *
 * @return  The tile. If no tile exists at pos, or no tilecache is
 *          loaded, NULL is returned.
 */
SDL_Surface * fn_environment_get_tile(fn_environment_t * env,
    size_t pos);

/* --------------------------------------------------------------- */

/**
 * Get the health of the hero in the environment.
 *
 * @param  env  The environment.
 *
 * @return The health.
 */
Uint8 fn_environment_get_health(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Get the firepower of the hero in the environment.
 *
 * @param  env  The environment.
 *
 * @return The firepower.
 */
Uint8 fn_environment_get_firepower(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Get the inventory of the hero in the environment.
 *
 * @param  env  The environment.
 *
 * @return The inventory.
 */
Uint8 fn_environment_get_inventory(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Get the score of the player in the environment.
 *
 * @param  env  The environment.
 *
 * @return The score.
 */
Uint32 fn_environment_get_score(fn_environment_t * env);

/* --------------------------------------------------------------- */

/**
 * Get the information if collision bounds should be draws.
 */
Uint8 fn_environment_get_draw_collision_bounds(
    fn_environment_t * env);

/* --------------------------------------------------------------- */

char * fn_environment_get_datapath(fn_environment_t * env);

/* --------------------------------------------------------------- */

fn_tilecache_t * fn_environment_get_tilecache(fn_environment_t * env);

/* --------------------------------------------------------------- */

Uint8 fn_environment_tilecache_loaded(fn_environment_t * env);

/* --------------------------------------------------------------- */

Uint8 fn_environment_store_settings(fn_environment_t * env);

/* --------------------------------------------------------------- */

fn_hero_t * fn_environment_get_hero(fn_environment_t * env);

/* --------------------------------------------------------------- */

#endif /* FN_ENVIRONMENT_H */
