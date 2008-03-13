/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Bot struct
 *
 * *****************************************************************
 *
 * Copyright 2008 Wolfgang Silbermayr
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

#ifndef FN_BOT_H
#define FN_BOT_H

#include <SDL.h>

#include "fn_hero.h"

/* --------------------------------------------------------------- */

typedef enum fn_bot_type_e fn_bot_type_e;

/* --------------------------------------------------------------- */

typedef struct fn_bot_t fn_bot_t;

/* --------------------------------------------------------------- */

typedef union fn_bot_data_u fn_bot_data_u;

/* --------------------------------------------------------------- */

enum fn_bot_type_e {
  FN_BOT_TYPE_FIREWHEEL,
  FN_BOT_TYPE_FLAMEGNOME,
  FN_BOT_TYPE_FLYINGBOT,
  FN_BOT_TYPE_FOOTBOT,
  FN_BOT_TYPE_HELICOPTER,
  FN_BOT_TYPE_RABBITOID,
  FN_BOT_TYPE_REDBALL_JUMPING,
  FN_BOT_TYPE_REDBALL_LYING,
  FN_BOT_TYPE_ROBOT,
  FN_BOT_TYPE_SNAKEBOT,
  FN_BOT_TYPE_TANKBOT,
  FN_BOT_TYPE_WALLCRAWLER_LEFT,
  FN_BOT_TYPE_WALLCRAWLER_RIGHT,
  FN_BOT_TYPE_DRPROTON,
  FN_BOT_TYPE_CAMERA
};

/* --------------------------------------------------------------- */

/**
 * The data needed for a firewheel bot.
 */
typedef struct fn_bot_firewheel_data_t {
} fn_bot_firewheel_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a flamegnome bot.
 */
typedef struct fn_bot_flamegnome_data_t {
} fn_bot_flamegnome_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a flying bot.
 */
typedef struct fn_bot_flyingbot_data_t {
} fn_bot_flyingbot_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a helicopter bot.
 */
typedef struct fn_bot_helicopter_data_t {
} fn_bot_helicopter_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a rabbitoid bot.
 */
typedef struct fn_bot_rabbitoid_data_t {
} fn_bot_rabbitoid_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a jumping red ball bot.
 */
typedef struct fn_bot_redball_jumping_data_t {
} fn_bot_redball_jumping_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a lying red ball bot.
 */
typedef struct fn_bot_redball_lying_data_t {
} fn_bot_redball_lying_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a robot.
 */
typedef struct fn_bot_robot_data_t {
} fn_bot_robot_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a snake bot.
 */
typedef struct fn_bot_snakebot_data_t {
} fn_bot_snakebot_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a tank bot.
 */
typedef struct fn_bot_tankbot_data_t {
} fn_bot_tankbot_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a left-sided wallcrawler bot.
 */
typedef struct fn_bot_wallcrawler_left_data_t {
} fn_bot_wallcrawler_left_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a right-sided wallcrawler bot.
 */
typedef struct fn_bot_wallcrawler_right_data_t {
} fn_bot_wallcrawler_right_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for dr proton.
 */
typedef struct fn_bot_drproton_data_t {
} fn_bot_drproton_data_t;

/* --------------------------------------------------------------- */

/**
 * The data needed for a camera.
 */
typedef struct fn_bot_camera_data_t {
} fn_bot_camera_data_t;

/* --------------------------------------------------------------- */

union fn_bot_data_u {
  fn_bot_firewheel_data_t firewheel;
  fn_bot_flamegnome_data_t flamegnome;
  fn_bot_flyingbot_data_t flyingbot;
  fn_bot_helicopter_data_t helicopter;
  fn_bot_rabbitoid_data_t rabbitoid;
  fn_bot_redball_jumping_data_t redball_jumping;
  fn_bot_redball_lying_data_t redball_lying;
  fn_bot_robot_data_t robot;
  fn_bot_snakebot_data_t snakebot;
  fn_bot_tankbot_data_t tankbot;
  fn_bot_wallcrawler_left_data_t wallcrawler_left;
  fn_bot_wallcrawler_right_data_t wallcrawler_right;
  fn_bot_drproton_data_t drproton;
  fn_bot_camera_data_t camera;
};

/* --------------------------------------------------------------- */

struct fn_bot_t {
  /**
   * The bot type.
   */
  fn_bot_type_e type;

  /**
   * The level inside which the bot is located.
   */
  fn_hero_t * hero;

  /**
   * The tilecache from which to blit the bot.
   */
  fn_tilecache_t * tilecache;

  /**
   * The size of one pixel.
   */
  size_t pixelsize;

  /**
   * The x position in the level.
   */
  Uint16 x;

  /**
   * The y position in the level.
   */
  Uint16 y;

  /**
   * The data of the different bot types.
   */
  fn_bot_data_u data;
};

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Create a bot.
 *
 * @param  type       The type of the bot.
 * @param  level      The level inside which the bot is located.
 * @param  tilecache  The tilecache to use for blitting.
 * @param  x          The x position of the bot (in half-tiles)
 * @param  y          The y position of the bot (in half-tiles)
 *
 * @return  The newly created bot.
 */
fn_bot_t * fn_bot_create(
    fn_bot_type_e type,
    fn_hero_t * hero,
    fn_tilecache_t * tilecache,
    Uint8 pixelsize,
    size_t x,
    size_t y);

/* --------------------------------------------------------------- */

/**
 * Delete a created bot.
 *
 * @param  bot  The bot to delete.
 */
void fn_bot_delete(fn_bot_t * bot);

/* --------------------------------------------------------------- */

/**
 * Blit the bot into the level.
 *
 * @param  bot     The bot to blit.
 * @param  target  The target surface.
 */
void fn_bot_blit(fn_bot_t * bot, SDL_Surface * target);

/* --------------------------------------------------------------- */

/**
 * Get the x position of the bot.
 *
 * @param  bot  The bot.
 *
 * @return The x position (in half-tiles) of the bot.
 */
size_t fn_bot_get_x(fn_bot_t * bot);

/* --------------------------------------------------------------- */

/**
 * Get the y position of the bot.
 *
 * @param  bot  The bot.
 *
 * @return The y position (in half-tiles) of the bot.
 */
size_t fn_bot_get_y(fn_bot_t * bot);

/* --------------------------------------------------------------- */

/**
 * Hit the bot with a shot from our hero.
 *
 * @param  bot  The bot which gets hit.
 *
 * @return non-zero if the bot gets hit, otherwise 0.
 */
int fn_bot_get_shot(fn_bot_t * bot);

/* --------------------------------------------------------------- */

/**
 * Animate another animation frame of our bot.
 *
 * @param bot  The bot which should be animated.
 */
void fn_bot_next_animation_frame(fn_bot_t * bot);

/* --------------------------------------------------------------- */

/**
 * Progress in the bot's actions (bot behaviour).
 *
 * @param bot  The bot which acts.
 *
 * @return zero if the bot was killed, otherwise non-zero.
 *         If zero was returned, the creator of the bot should delete it.
 */
int fn_bot_action_progress(fn_bot_t * bot);

/* --------------------------------------------------------------- */

#endif // FN_BOT_H

