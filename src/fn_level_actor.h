/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Actor functions
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

#ifndef FN_LEVEL_ACTOR_H
#define FN_LEVEL_ACTOR_H

/* --------------------------------------------------------------- */

typedef struct fn_level_actor_t fn_level_actor_t;
typedef enum fn_level_actor_type_e fn_level_actor_type_e;

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_level.h"

/* --------------------------------------------------------------- */

/**
 * The actor types.
 */
enum fn_level_actor_type_e {
  FN_LEVEL_ACTOR_FIREWHEELBOT,
  FN_LEVEL_ACTOR_FLAMEGNOMEBOT,
  FN_LEVEL_ACTOR_FLYINGBOT,
  FN_LEVEL_ACTOR_FOOTBOT,
  FN_LEVEL_ACTOR_HELICOPTERBOT,
  FN_LEVEL_ACTOR_RABBITOIDBOT,
  FN_LEVEL_ACTOR_REDBALL_JUMPING,
  FN_LEVEL_ACTOR_REDBALL_LYING,
  FN_LEVEL_ACTOR_ROBOT,
  FN_LEVEL_ACTOR_ROBOT_DISAPPEARING,
  FN_LEVEL_ACTOR_SNAKEBOT,
  FN_LEVEL_ACTOR_TANKBOT,
  FN_LEVEL_ACTOR_WALLCRAWLERBOT_LEFT,
  FN_LEVEL_ACTOR_WALLCRAWLERBOT_RIGHT,
  FN_LEVEL_ACTOR_DRPROTON,
  FN_LEVEL_ACTOR_CAMERA,
  FN_LEVEL_ACTOR_EXPLOSION,
  FN_LEVEL_ACTOR_FIRE,
  FN_LEVEL_ACTOR_DUSTCLOUD,
  FN_LEVEL_ACTOR_STEAM,
  FN_LEVEL_ACTOR_PARTICLE_PINK,
  FN_LEVEL_ACTOR_PARTICLE_BLUE,
  FN_LEVEL_ACTOR_PARTICLE_WHITE,
  FN_LEVEL_ACTOR_PARTICLE_GREEN,
  FN_LEVEL_ACTOR_ROCKET,
  FN_LEVEL_ACTOR_BOMB,
  FN_LEVEL_ACTOR_BOMBFIRE,
  FN_LEVEL_ACTOR_WATER,
  FN_LEVEL_ACTOR_EXITDOOR,
  FN_LEVEL_ACTOR_NOTEBOOK,
  FN_LEVEL_ACTOR_SURVEILLANCESCREEN,
  FN_LEVEL_ACTOR_HOSTILESHOT_LEFT,
  FN_LEVEL_ACTOR_HOSTILESHOT_RIGHT,
  FN_LEVEL_ACTOR_SODA,
  FN_LEVEL_ACTOR_SODA_FLYING,
  FN_LEVEL_ACTOR_UNSTABLEFLOOR,
  FN_LEVEL_ACTOR_EXPANDINGFLOOR,
  FN_LEVEL_ACTOR_CONVEYOR_LEFTMOVING_RIGHTEND,
  FN_LEVEL_ACTOR_CONVEYOR_RIGHTMOVING_RIGHTEND,
  FN_LEVEL_ACTOR_FAN_LEFT,
  FN_LEVEL_ACTOR_FAN_RIGHT,
  FN_LEVEL_ACTOR_BROKENWALL_BACKGROUND,
  FN_LEVEL_ACTOR_STONE_BACKGROUND,
  FN_LEVEL_ACTOR_TELEPORTER1,
  FN_LEVEL_ACTOR_TELEPORTER2,
  FN_LEVEL_ACTOR_FENCE_BACKGROUND,
  FN_LEVEL_ACTOR_STONEWINDOW_BACKGROUND,
  FN_LEVEL_ACTOR_WINDOWLEFT_BACKGROUND,
  FN_LEVEL_ACTOR_WINDOWRIGHT_BACKGROUND,
  FN_LEVEL_ACTOR_SCREEN,
  FN_LEVEL_ACTOR_BOX_GREY_EMPTY,
  FN_LEVEL_ACTOR_BOX_GREY_BOOTS,
  FN_LEVEL_ACTOR_BOOTS,
  FN_LEVEL_ACTOR_BOX_GREY_CLAMPS,
  FN_LEVEL_ACTOR_CLAMPS,
  FN_LEVEL_ACTOR_BOX_GREY_GUN,
  FN_LEVEL_ACTOR_GUN,
  FN_LEVEL_ACTOR_BOX_GREY_BOMB,
  FN_LEVEL_ACTOR_BOX_RED_SODA,
  FN_LEVEL_ACTOR_BOX_RED_CHICKEN,
  FN_LEVEL_ACTOR_CHICKEN_SINGLE,
  FN_LEVEL_ACTOR_CHICKEN_DOUBLE,
  FN_LEVEL_ACTOR_BOX_BLUE_FOOTBALL,
  FN_LEVEL_ACTOR_FOOTBALL,
  FN_LEVEL_ACTOR_FLAG,
  FN_LEVEL_ACTOR_BOX_BLUE_JOYSTICK,
  FN_LEVEL_ACTOR_JOYSTICK,
  FN_LEVEL_ACTOR_BOX_BLUE_DISK,
  FN_LEVEL_ACTOR_DISK,
  FN_LEVEL_ACTOR_BOX_BLUE_BALLOON,
  FN_LEVEL_ACTOR_BALLOON,
  FN_LEVEL_ACTOR_BOX_GREY_GLOVE,
  FN_LEVEL_ACTOR_GLOVE,
  FN_LEVEL_ACTOR_BOX_GREY_FULL_LIFE,
  FN_LEVEL_ACTOR_FULL_LIFE,
  FN_LEVEL_ACTOR_BOX_BLUE_FLAG,
  FN_LEVEL_ACTOR_BLUE_FLAG,
  FN_LEVEL_ACTOR_BOX_BLUE_RADIO,
  FN_LEVEL_ACTOR_RADIO,
  FN_LEVEL_ACTOR_BOX_GREY_ACCESS_CARD,
  FN_LEVEL_ACTOR_ACCESS_CARD,
  FN_LEVEL_ACTOR_BOX_GREY_LETTER_D,
  FN_LEVEL_ACTOR_LETTER_D,
  FN_LEVEL_ACTOR_BOX_GREY_LETTER_U,
  FN_LEVEL_ACTOR_LETTER_U,
  FN_LEVEL_ACTOR_BOX_GREY_LETTER_K,
  FN_LEVEL_ACTOR_LETTER_K,
  FN_LEVEL_ACTOR_BOX_GREY_LETTER_E,
  FN_LEVEL_ACTOR_LETTER_E,
  FN_LEVEL_ACTOR_ACCESS_CARD_SLOT,
  FN_LEVEL_ACTOR_GLOVE_SLOT,
  FN_LEVEL_ACTOR_KEY_RED,
  FN_LEVEL_ACTOR_KEYHOLE_RED,
  FN_LEVEL_ACTOR_DOOR_RED,
  FN_LEVEL_ACTOR_KEY_BLUE,
  FN_LEVEL_ACTOR_KEYHOLE_BLUE,
  FN_LEVEL_ACTOR_DOOR_BLUE,
  FN_LEVEL_ACTOR_KEY_PINK,
  FN_LEVEL_ACTOR_KEYHOLE_PINK,
  FN_LEVEL_ACTOR_DOOR_PINK,
  FN_LEVEL_ACTOR_KEY_GREEN,
  FN_LEVEL_ACTOR_KEYHOLE_GREEN,
  FN_LEVEL_ACTOR_DOOR_GREEN,
  FN_LEVEL_ACTOR_SHOOTABLE_WALL,
  FN_LEVEL_ACTOR_LIFT,
  FN_LEVEL_ACTOR_ACME,
  FN_LEVEL_ACTOR_FIRE_RIGHT,
  FN_LEVEL_ACTOR_FIRE_LEFT,
  FN_LEVEL_ACTOR_MILL,
  FN_LEVEL_ACTOR_LASERBEAM,
  FN_LEVEL_ACTOR_ACCESS_CARD_DOOR,
  FN_LEVEL_ACTOR_SPIKES_UP,
  FN_LEVEL_ACTOR_SPIKES_DOWN,
  FN_LEVEL_ACTOR_SPIKE,
  FN_LEVEL_ACTOR_SCORE_100,
  FN_LEVEL_ACTOR_SCORE_200,
  FN_LEVEL_ACTOR_SCORE_500,
  FN_LEVEL_ACTOR_SCORE_1000,
  FN_LEVEL_ACTOR_SCORE_2000,
  FN_LEVEL_ACTOR_SCORE_5000,
  FN_LEVEL_ACTOR_SCORE_10000,
  FN_LEVEL_ACTOR_SCORE_BONUS_1_LEFT,
  FN_LEVEL_ACTOR_SCORE_BONUS_1_RIGHT,
  FN_LEVEL_ACTOR_SCORE_BONUS_2_LEFT,
  FN_LEVEL_ACTOR_SCORE_BONUS_2_RIGHT,
  FN_LEVEL_ACTOR_SCORE_BONUS_3_LEFT,
  FN_LEVEL_ACTOR_SCORE_BONUS_3_RIGHT,
  FN_LEVEL_ACTOR_SCORE_BONUS_4_LEFT,
  FN_LEVEL_ACTOR_SCORE_BONUS_4_RIGHT,
  FN_LEVEL_ACTOR_SCORE_BONUS_5_LEFT,
  FN_LEVEL_ACTOR_SCORE_BONUS_5_RIGHT,
  FN_LEVEL_ACTOR_SCORE_BONUS_6_LEFT,
  FN_LEVEL_ACTOR_SCORE_BONUS_6_RIGHT,
  FN_LEVEL_ACTOR_SCORE_BONUS_7_LEFT,
  FN_LEVEL_ACTOR_SCORE_BONUS_7_RIGHT,
  FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND1,
  FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND2,
  FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND3,
  FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND4,
  FN_LEVEL_ACTOR_TEXT_ON_SCREEN_BACKGROUND,
  FN_LEVEL_ACTOR_HIGH_VOLTAGE_FLASH_BACKGROUND,
  FN_LEVEL_ACTOR_RED_FLASHLIGHT_BACKGROUND,
  FN_LEVEL_ACTOR_BLUE_FLASHLIGHT_BACKGROUND,
  FN_LEVEL_ACTOR_KEYPANEL_BACKGROUND,
  FN_LEVEL_ACTOR_RED_ROTATIONLIGHT_BACKGROUND,
  FN_LEVEL_ACTOR_UPARROW_BACKGROUND,
  FN_LEVEL_ACTOR_GREEN_POISON_BACKGROUND,
  FN_LEVEL_ACTOR_LAVA_BACKGROUND,
  FN_LEVEL_ACTOR_NUM_TYPES,
};

/* --------------------------------------------------------------- */


/**
 * The actor struct.
 */
struct fn_level_actor_t {
  /**
   * The level inside which the actor is located.
   */
  fn_level_t * level;

  /**
   * The type of the actor.
   */
  fn_level_actor_type_e type;

  /**
   * The current position of the actor.
   */
  SDL_Rect position;

  /**
   * Private data - depends on type.
   */
  void * data;

  /**
   * Flag that indicates if the actor is (still) alive.
   */
  int is_alive;

  /**
   * Flag that indicates if the actor is being touched by the hero
   */
  int touches_hero;

  /**
   * Flag that indicates if the actor is in foreground (means in front
   * of hero).
   */
  Uint8 is_in_foreground;

  /**
   * Is the actor visible in the currently shown area?
   */
  Uint8 is_visible;

  /**
   * Does the actor act even if outside the visible area?
   */
  Uint8 acts_while_invisible;
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
fn_level_actor_t * fn_level_actor_create(fn_level_t * level,
    fn_level_actor_type_e type,
    Uint16 x,
    Uint16 y);

/* --------------------------------------------------------------- */

/**
 * Delete an actor and free its memory.
 *
 * @param  actor  The actor to delete.
 */
void fn_level_actor_free(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Check if the hero does touch the actor.
 *
 * @param  actor  The actor.
 *
 * @return Non-zero if the hero touches, otherwise zero.
 */
int fn_level_actor_touches_hero(fn_level_actor_t * actor);


/* --------------------------------------------------------------- */

/**
 * Check if the hero does touch the actor and accordingly
 * set the flags.
 *
 * @param  actor  The actor.
 */
void fn_level_actor_check_hero_touch(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * The hero starts touching the actor.
 *
 * @param  actor  The actor which got touched.
 */
void fn_level_actor_hero_touch_start(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * The hero stops touching the actor.
 *
 * @param  actor  The actor which got touched.
 */
void fn_level_actor_hero_touch_end(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Tells if the hero can interact with an actor.
 *
 * @param  actor  The actor.
 *
 * @return 1 if the hero can interact with the actor, otherwise 0.
 */
Uint8 fn_level_actor_hero_can_interact(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * The hero starts to interact with the actor
 * (player pressed up arrow)
 *
 * @param  actor  The actor with whom the player interacts.
 */
void fn_level_actor_hero_interact_start(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * The hero stops to interact with the actor
 * (player released up arrow)
 *
 * @param  actor  The actor with whom the player interacts.
 */
void fn_level_actor_hero_interact_stop(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */


/**
 * The actor acts.
 *
 * @param  actor  The actor.
 *
 * @return  Zero if the actor died, otherwise a non-zero value.
 */
int fn_level_actor_act(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Blit the actor to the level.
 *
 * @param  actor  The actor.
 */
void fn_level_actor_blit(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * The actor gets hit by a shot.
 *
 * @param  actor  The actor.
 *
 * @return 1 if the actor absorbs the shot, otherwise 0.
 */
Uint8 fn_level_actor_shot(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Get the x coordinate (in pixels) of the actor.
 *
 * @param  actor  The actor.
 *
 * @return  The x coordinate.
 */
Uint16 fn_level_actor_get_x(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Get the y coordinate (in pixels) of the actor.
 *
 * @param  actor  The actor.
 *
 * @return  The y coordinate.
 */
Uint16 fn_level_actor_get_y(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Get the width (in pixels) of the actor.
 *
 * @param  actor  The actor.
 *
 * @return  The width.
 */
Uint16 fn_level_actor_get_w(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Get the height (in pixels) of the actor.
 *
 * @param  actor  The actor.
 *
 * @return  The height.
 */
Uint16 fn_level_actor_get_h(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Tells if an actor can get shot.
 *
 * @param  actor  The actor.
 *
 * @return 1 if the actor can get shot, otherwise 0.
 */
Uint8 fn_level_actor_can_get_shot(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Tells if an actor is in the foreground.
 *
 * @param  actor  The actor.
 *
 * @return 1 if the actor is in foreground, otherwise 0.
 */
Uint8 fn_level_actor_in_foreground(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Get the current position of the actor.
 *
 * @param  actor  The actor.
 *
 * @return A rectangle containing the current position of the actor.
 */
SDL_Rect * fn_level_actor_get_position(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

/**
 * Set the visibility of the actor.
 *
 * @param  actor       The actor.
 * @param  visibility  If 1 set the actor visible,
 *                     if 0 set it invisible.
 */
void fn_level_actor_set_visible(fn_level_actor_t * actor, Uint8 visibility);

/* --------------------------------------------------------------- */

/**
 * Get the visibility of the actor.
 *
 * @param  actor  The actor.
 *
 * @return 1 if the actor is visible, 0 if invisible.
 */
Uint8 fn_level_actor_is_visible(fn_level_actor_t * actor);

/* --------------------------------------------------------------- */

#endif /* FN_LEVEL_ACTOR_H */
