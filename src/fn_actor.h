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
  FN_ACTOR_FIREWHEELBOT,             /* TODO */
  FN_ACTOR_FLAMEGNOMEBOT,            /* TODO */
  FN_ACTOR_FLYINGBOT,                /* TODO */
  FN_ACTOR_FOOTBOT,                  /* TODO */
  FN_ACTOR_HELICOPTERBOT,            /* TODO */
  FN_ACTOR_RABBITOIDBOT,             /* TODO */
  FN_ACTOR_REDBALL_JUMPING,          /* TODO */
  FN_ACTOR_REDBALL_LYING,            /* TODO */
  FN_ACTOR_ROBOT,                    /* TODO */
  FN_ACTOR_SNAKEBOT,                 /* TODO */
  FN_ACTOR_TANKBOT,                  /* TODO */
  FN_ACTOR_WALLCRAWLERBOT_LEFT,      /* TODO */
  FN_ACTOR_WALLCRAWLERBOT_RIGHT,     /* TODO */
  FN_ACTOR_DRPROTON,                 /* TODO */
  FN_ACTOR_CAMERA,                   /* TODO */
  FN_ACTOR_BOMB,                     /* TODO */
  FN_ACTOR_EXITDOOR,                 /* TODO */
  FN_ACTOR_SODA,                     /* TODO */
  FN_ACTOR_UNSTABLEFLOOR,            /* TODO */
  FN_ACTOR_FAN_LEFT,                 /* TODO */
  FN_ACTOR_FAN_RIGHT,                /* TODO */
  FN_ACTOR_BROKENWALL_BACKGROUND,    /* TODO */
  FN_ACTOR_STONE_BACKGROUND,         /* TODO */
  FN_ACTOR_TELEPORTER1,              /* TODO */
  FN_ACTOR_TELEPORTER2,              /* TODO */
  FN_ACTOR_FENCE_BACKGROUND   ,      /* TODO */
  FN_ACTOR_WINDOW_BACKGROUND,        /* TODO */
  FN_ACTOR_SCREEN,                   /* TODO */
  FN_ACTOR_BOX_GREY_EMPTY,           /* TODO */
  FN_ACTOR_BOX_GREY_BOOTS,           /* TODO */
  FN_ACTOR_BOOTS,                    /* TODO */
  FN_ACTOR_BOX_GREY_CLAMPS,          /* TODO */
  FN_ACTOR_CLAMPS,                   /* TODO */
  FN_ACTOR_BOX_GREY_GUN,             /* TODO */
  FN_ACTOR_GUN,                      /* TODO */
  FN_ACTOR_BOX_GREY_BOMB,            /* TODO */
  FN_ACTOR_BOX_RED_SODA,             /* TODO */
  FN_ACTOR_BOX_RED_CHICKEN,          /* TODO */
  FN_ACTOR_CHICKEN_SINGLE,           /* TODO */
  FN_ACTOR_CHICKEN_DOUBLE,           /* TODO */
  FN_ACTOR_BOX_BLUE_FOOTBALL,        /* TODO */
  FN_ACTOR_FOOTBALL,                 /* TODO */
  FN_ACTOR_FLAG,                     /* TODO */
  FN_ACTOR_BOX_BLUE_JOYSTICK,        /* TODO */
  FN_ACTOR_JOYSTICK,                 /* TODO */
  FN_ACTOR_BOX_BLUE_DISK,            /* TODO */
  FN_ACTOR_DISK,                     /* TODO */
  FN_ACTOR_BOX_BLUE_BALLOON,         /* TODO */
  FN_ACTOR_BALLOON,                  /* TODO */
  FN_ACTOR_BOX_GREY_GLOVE,           /* TODO */
  FN_ACTOR_GLOVE,                    /* TODO */
  FN_ACTOR_BOX_GREY_FULL_LIFE,       /* TODO */
  FN_ACTOR_FULL_LIFE,                /* TODO */
  FN_ACTOR_BOX_BLUE_FLAG,            /* TODO */
  FN_ACTOR_BLUE_FLAG,                /* TODO */
  FN_ACTOR_BOX_BLUE_RADIO,           /* TODO */
  FN_ACTOR_RADIO,                    /* TODO */
  FN_ACTOR_BOX_GREY_ACCESS_CARD,     /* TODO */
  FN_ACTOR_ACCESS_CARD,              /* TODO */
  FN_ACTOR_BOX_GREY_LETTER_D,        /* TODO */
  FN_ACTOR_LETTER_D,                 /* TODO */
  FN_ACTOR_BOX_GREY_LETTER_U,        /* TODO */
  FN_ACTOR_LETTER_U,                 /* TODO */
  FN_ACTOR_BOX_GREY_LETTER_K,        /* TODO */
  FN_ACTOR_LETTER_K,                 /* TODO */
  FN_ACTOR_BOX_GREY_LETTER_E,        /* TODO */
  FN_ACTOR_LETTER_E,                 /* TODO */
  FN_ACTOR_KEY_RED,                  /* TODO */
  FN_ACTOR_KEYHOLE_RED,              /* TODO */
  FN_ACTOR_DOOR_RED,                 /* TODO */
  FN_ACTOR_KEY_BLUE,                 /* TODO */
  FN_ACTOR_KEYHOLE_BLUE,             /* TODO */
  FN_ACTOR_DOOR_BLUE,                /* TODO */
  FN_ACTOR_KEY_PINK,                 /* TODO */
  FN_ACTOR_KEYHOLE_PINK,             /* TODO */
  FN_ACTOR_DOOR_PINK,                /* TODO */
  FN_ACTOR_KEY_GREEN,                /* TODO */
  FN_ACTOR_KEYHOLE_GREEN,            /* TODO */
  FN_ACTOR_DOOR_GREEN,               /* TODO */
  FN_ACTOR_MILL,                     /* TODO */
  FN_ACTOR_ACCESS_CARD_DOOR,         /* TODO */
  FN_ACTOR_SCORE_100,                /* TODO */
  FN_ACTOR_SCORE_200,                /* TODO */
  FN_ACTOR_SCORE_500,                /* TODO */
  FN_ACTOR_SCORE_1000,               /* TODO */
  FN_ACTOR_SCORE_2000,               /* TODO */
  FN_ACTOR_SCORE_5000,               /* TODO */
  FN_ACTOR_SCORE_10000,              /* TODO */
  FN_ACTOR_SCORE_BONUS_1_LEFT,       /* TODO */
  FN_ACTOR_SCORE_BONUS_1_RIGHT,      /* TODO */
  FN_ACTOR_SCORE_BONUS_2_LEFT,       /* TODO */
  FN_ACTOR_SCORE_BONUS_2_RIGHT,      /* TODO */
  FN_ACTOR_SCORE_BONUS_3_LEFT,       /* TODO */
  FN_ACTOR_SCORE_BONUS_3_RIGHT,      /* TODO */
  FN_ACTOR_SCORE_BONUS_4_LEFT,       /* TODO */
  FN_ACTOR_SCORE_BONUS_4_RIGHT,      /* TODO */
  FN_ACTOR_SCORE_BONUS_5_LEFT,       /* TODO */
  FN_ACTOR_SCORE_BONUS_5_RIGHT,      /* TODO */
  FN_ACTOR_SCORE_BONUS_6_LEFT,       /* TODO */
  FN_ACTOR_SCORE_BONUS_6_RIGHT,      /* TODO */
  FN_ACTOR_SCORE_BONUS_7_LEFT,       /* TODO */
  FN_ACTOR_SCORE_BONUS_7_RIGHT,      /* TODO */
  FN_ACTOR_BLUE_LIGHT_BACKGROUND1,
  FN_ACTOR_BLUE_LIGHT_BACKGROUND2,
  FN_ACTOR_BLUE_LIGHT_BACKGROUND3,
  FN_ACTOR_BLUE_LIGHT_BACKGROUND4,
  FN_ACTOR_TEXT_ON_SCREEN_BACKGROUND,
  FN_ACTOR_HIGH_VOLTAGE_FLASH_BACKGROUND,
  FN_ACTOR_RED_FLASHLIGHT_BACKGROUND,
  FN_ACTOR_BLUE_FLASHLIGHT_BACKGROUND,
  FN_ACTOR_KEYPANEL_BACKGROUND,
  FN_ACTOR_RED_ROTATIONLIGHT_BACKGROUND,
  FN_ACTOR_UPARROW_BACKGROUND,
  FN_ACTOR_GREEN_POISON_BACKGROUND,
  FN_ACTOR_LAVA_BACKGROUND,
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

  /**
   * Flag that indicates if the actor is being touched by the hero
   */
  int touches_hero;
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
 * Check if the hero does touch the actor.
 *
 * @param  actor  The actor.
 *
 * @return Non-zero if the hero touches, otherwise zero.
 */
int fn_actor_touches_hero(fn_actor_t * actor);


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