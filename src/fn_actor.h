/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Actor functions
 *
 * *****************************************************************
 *
 * Copyright 2007 Wolfgang Silbermayr
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

#ifndef FN_ACTOR_H
#define FN_ACTOR_H

/* --------------------------------------------------------------- */

typedef struct fn_actor_t fn_actor_t;
typedef enum fn_actor_type_e fn_actor_type_e;

/* --------------------------------------------------------------- */

#include "fn_level.h"

/* --------------------------------------------------------------- */

/**
 * The actor types.
 */
enum fn_actor_type_e {
  FN_ACTOR_FIREWHEELBOT,
  FN_ACTOR_FLAMEGNOMEBOT,
  FN_ACTOR_FLYINGBOT,
  FN_ACTOR_FOOTBOT,
  FN_ACTOR_HELICOPTERBOT,
  FN_ACTOR_RABBITOIDBOT,
  FN_ACTOR_REDBALL_JUMPING,
  FN_ACTOR_REDBALL_LYING,
  FN_ACTOR_ROBOT,
  FN_ACTOR_SNAKEBOT,
  FN_ACTOR_TANKBOT,
  FN_ACTOR_WALLCRAWLERBOT_LEFT,
  FN_ACTOR_WALLCRAWLERBOT_RIGHT,
  FN_ACTOR_DRPROTON,
  FN_ACTOR_CAMERA,
  FN_ACTOR_BOMB,
  FN_ACTOR_EXITDOOR,
  FN_ACTOR_SODA,
  FN_ACTOR_UNSTABLEFLOOR,
  FN_ACTOR_FAN_LEFT,
  FN_ACTOR_FAN_RIGHT,
  FN_ACTOR_BROKENWALL_BACKGROUND,
  FN_ACTOR_STONE_BACKGROUND,
  FN_ACTOR_TELEPORTER1,
  FN_ACTOR_TELEPORTER2,
  FN_ACTOR_FENCE_BACKGROUND,
  FN_ACTOR_WINDOW_BACKGROUND,
  FN_ACTOR_SCREEN,
  FN_ACTOR_BOX_GREY_EMPTY,
  FN_ACTOR_BOX_GREY_BOOTS,
  FN_ACTOR_BOOTS,
  FN_ACTOR_BOX_GREY_CLAMPS,
  FN_ACTOR_CLAMPS,
  FN_ACTOR_BOX_GREY_GUN,
  FN_ACTOR_GUN,
  FN_ACTOR_BOX_GREY_BOMB,
  FN_ACTOR_BOX_RED_SODA,
  FN_ACTOR_BOX_RED_CHICKEN,
  FN_ACTOR_CHICKEN_SINGLE,
  FN_ACTOR_CHICKEN_DOUBLE,
  FN_ACTOR_BOX_BLUE_FOOTBALL,
  FN_ACTOR_FOOTBALL,
  FN_ACTOR_BOX_BLUE_JOYSTICK,
  FN_ACTOR_JOYSTICK,
  FN_ACTOR_BOX_BLUE_DISK,
  FN_ACTOR_DISK,
  FN_ACTOR_BOX_BLUE_BALLOON,
  FN_ACTOR_BALLOON,
  FN_ACTOR_BOX_GREY_GLOVE,
  FN_ACTOR_GLOVE,
  FN_ACTOR_BOX_GREY_FULL_LIFE,
  FN_ACTOR_FULL_LIFE,
  FN_ACTOR_BOX_BLUE_FLAG,
  FN_ACTOR_BLUE_FLAG,
  FN_ACTOR_BOX_BLUE_RADIO,
  FN_ACTOR_RADIO,
  FN_ACTOR_BOX_GREY_ACCESS_CARD,
  FN_ACTOR_ACCESS_CARD,
  FN_ACTOR_BOX_GREY_LETTER_D,
  FN_ACTOR_LETTER_D,
  FN_ACTOR_BOX_GREY_LETTER_U,
  FN_ACTOR_LETTER_U,
  FN_ACTOR_BOX_GREY_LETTER_K,
  FN_ACTOR_LETTER_K,
  FN_ACTOR_BOX_GREY_LETTER_E,
  FN_ACTOR_LETTER_E,
  FN_ACTOR_KEY_RED,
  FN_ACTOR_KEYHOLE_RED,
  FN_ACTOR_DOOR_RED,
  FN_ACTOR_KEY_BLUE,
  FN_ACTOR_KEYHOLE_BLUE,
  FN_ACTOR_DOOR_BLUE,
  FN_ACTOR_KEY_PINK,
  FN_ACTOR_KEYHOLE_PINK,
  FN_ACTOR_DOOR_PINK,
  FN_ACTOR_KEY_GREEN,
  FN_ACTOR_KEYHOLE_GREEN,
  FN_ACTOR_DOOR_GREEN,
  FN_ACTOR_MILL,
  FN_ACTOR_ACCESS_CARD_DOOR,
  FN_ACTOR_BLUE_LIGHT_BACKGROUND1,
  FN_ACTOR_BLUE_LIGHT_BACKGROUND2,
  FN_ACTOR_BLUE_LIGHT_BACKGROUND3,
  FN_ACTOR_BLUE_LIGHT_BACKGROUND4,
  FN_ACTOR_NUM_TYPES,
};

/* --------------------------------------------------------------- */


/**
 * The actor struct.
 */
struct fn_actor_t {
  /**
   * The level inside which the actor is located.
   */
  fn_level_t * level;

  /**
   * The type of the actor.
   */
  fn_actor_type_e type;

  /**
   * The current x position (in pixels).
   */
  Uint16 x;

  /**
   * The current y position (in pixels).
   */
  Uint16 y;

  /**
   * The width of the actor (in pixels).
   */
  Uint16 w;

  /**
   * The height of the actor (in pixels).
   */
  Uint16 h;

  /**
   * Private data - depends on type.
   */
  void * data;

  /**
   * Flag that indicates if the actor is (still) alive.
   */
  int is_alive;
};

/* --------------------------------------------------------------- */

/**
 * Create a new actor inside a level.
 *
 * @param  level  The level inside which the actor is located.
 * @param  type   The type of the actor.
 * @param  x      The x coordinate of the top left corner.
 * @param  y      The y coordinate of the top left corner.
 *
 * @return  The newly created actor.
 */
fn_actor_t * fn_actor_create(fn_level_t * level,
    fn_actor_type_e type,
    Uint16 x,
    Uint16 y);

/* --------------------------------------------------------------- */

/**
 * Delete an actor and free its memory.
 *
 * @param  actor  The actor to delete.
 */
void fn_actor_free(fn_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Check if the hero does touch the actor and accordingly
 * set the flags.
 *
 * @param  actor  The actor.
 */
void fn_actor_check_hero_touch(fn_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * The hero starts touching the actor.
 *
 * @param  actor  The actor which got touched.
 */
void fn_actor_hero_touch_start(fn_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * The hero stops touching the actor.
 *
 * @param  actor  The actor which got touched.
 */
void fn_actor_hero_touch_end(fn_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * The hero starts to interact with the actor
 * (player pressed up arrow)
 *
 * @param  actor  The actor with whom the player interacts.
 */
void fn_actor_hero_interact_start(fn_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * The hero stops to interact with the actor
 * (player released up arrow)
 *
 * @param  actor  The actor with whom the player interacts.
 */
void fn_actor_hero_interact_stop(fn_actor_t * actor);

/* --------------------------------------------------------------- */


/**
 * The actor acts.
 *
 * @param  actor  The actor.
 *
 * @return  Zero if the actor died, otherwise a non-zero value.
 */
int fn_actor_act(fn_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Blit the actor to the level.
 *
 * @param  actor  The actor.
 */
void fn_actor_blit(fn_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Get the x coordinate (in pixels) of the actor.
 *
 * @return  The x coordinate.
 */
Uint16 fn_actor_get_x(fn_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Get the y coordinate (in pixels) of the actor.
 *
 * @return  The y coordinate.
 */
Uint16 fn_actor_get_y(fn_actor_t * actor);

/* --------------------------------------------------------------- */

#endif /* FN_ACTOR_H */
