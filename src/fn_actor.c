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

#include "fn_tilecache.h"
#include "fn_actor.h"
#include "fn_object.h"

/* --------------------------------------------------------------- */

/**
 * The different types of functions which can be executed on the actor.
 */
typedef enum fn_actor_function_type_e {
  /**
   * The create function. Allocates memory and sets properties.
   */
  FN_ACTOR_FUNCTION_CREATE,
  /**
   * The free function. Frees the used memory.
   */
  FN_ACTOR_FUNCTION_FREE,
  /**
   * The touch_start function. Is called when the hero starts touching
   * the actor.
   */
  FN_ACTOR_FUNCTION_HERO_TOUCH_START,
  /**
   * The touch_end function. Is called when the hero stops touching
   * the actor.
   */
  FN_ACTOR_FUNCTION_HERO_TOUCH_END,
  /**
   * The interact_start function. Is called when the hero starts to
   * interact with the actor.
   */
  FN_ACTOR_FUNCTION_HERO_INTERACT_START,
  /**
   * The interact_end function. Is called when the hero stops to
   * interact with the actor.
   */
  FN_ACTOR_FUNCTION_HERO_INTERACT_END,
  /**
   * The act function. Is called on fixed time slices. This is
   * where the actual action takes place.
   */
  FN_ACTOR_FUNCTION_ACT,
  /**
   * The blit function. Blits the actor into the level in which
   * it is placed.
   */
  FN_ACTOR_FUNCTION_BLIT,
  /**
   * The number of functions. Only used for getting the enum bounds.
   */
  FN_ACTOR_NUM_FUNCTIONS
} fn_actor_function_type_e;

/* --------------------------------------------------------------- */

/**
 * The simple animation struct.
 * A simple animation is an animation which is one part high,
 * one part wide and has a fixed number of frames that occur
 * one after each other and are lined up in a row inside
 * the tilecache.
 */
typedef struct fn_actor_simpleanimation_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The number of the current frame.
   */
  Uint8 current_frame;
  /**
   * The number of frames for the animation.
   */
  Uint8 num_frames;
} fn_actor_simpleanimation_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a simple animation.
 *
 * @param  actor The animation actor.
 */
void fn_actor_function_simpleanimation_create(fn_actor_t * actor)
{
  fn_actor_simpleanimation_data_t * data = malloc(
      sizeof(fn_actor_simpleanimation_data_t));

  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  switch(actor->type) {
    case FN_ACTOR_TEXT_ON_SCREEN_BACKGROUND:
      data->tile = 0x0004;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_HIGH_VOLTAGE_FLASH_BACKGROUND:
      data->tile = 0x0008;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_RED_FLASHLIGHT_BACKGROUND:
      data->tile = 0x000C;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_BLUE_FLASHLIGHT_BACKGROUND:
      data->tile = 0x0010;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_KEYPANEL_BACKGROUND:
      data->tile = 0x0014;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_RED_ROTATIONLIGHT_BACKGROUND:
      data->tile = 0x0018;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_UPARROW_BACKGROUND:
      data->tile = 0x001C;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_BLUE_LIGHT_BACKGROUND1:
      data->tile = 0x0020;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_BLUE_LIGHT_BACKGROUND2:
      data->tile = 0x0021;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_BLUE_LIGHT_BACKGROUND3:
      data->tile = 0x0022;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_BLUE_LIGHT_BACKGROUND4:
      data->tile = 0x0023;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_GREEN_POISON_BACKGROUND:
      data->tile = 0x0028;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_LAVA_BACKGROUND:
      data->tile = 0x002C;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    default:
      /* we got a type which should not be an animation. */
      printf(__FILE__ ":%d: warning: animation #%d"
          " added which is not an animation\n",
          __LINE__, actor->type);
      break;
  }
}

/* --------------------------------------------------------------- */

/**
 * Delete a simple animation.
 *
 * @param  actor  The animation actor.
 */
void fn_actor_function_simpleanimation_free(fn_actor_t * actor)
{
  fn_actor_simpleanimation_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}


/* --------------------------------------------------------------- */

/**
 * Action for simple animation.
 *
 * @param  actor  The animation actor.
 */
void fn_actor_function_simpleanimation_act(fn_actor_t * actor)
{
  fn_actor_simpleanimation_data_t * data = actor->data;
  data->current_frame++;
  data->current_frame %= data->num_frames;
}

/* --------------------------------------------------------------- */

/**
 * Blit the simple animation.
 *
 * @param  actor  The animation actor.
 */
void fn_actor_function_simpleanimation_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_actor_simpleanimation_data_t * data = actor->data;
  SDL_Surface * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

/**
 * The item struct.
 * Items are elements in the game which fall to the floor.
 * They are one part high, one part wide and
 * have either a single frame or a fixed number
 * of frames that appear in order and are lined up in a row
 * inside the tilecache.
 */
typedef struct fn_actor_item_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The number of the current frame.
   */
  Uint8 current_frame;
  /**
   * The number of frames for the animation.
   */
  Uint8 num_frames;
  /**
   * Are we standing on the ground? If no, this is zero, otherwise 1.
   */
  Uint8 standing_on_ground;
} fn_actor_item_data_t;

/* --------------------------------------------------------------- */

/**
 * Create an item.
 *
 * @param  actor The item actor.
 */
void fn_actor_function_item_create(fn_actor_t * actor)
{
  fn_actor_item_data_t * data = malloc(
      sizeof(fn_actor_item_data_t));

  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  switch(actor->type) {
    case FN_ACTOR_BOX_RED_SODA:
    case FN_ACTOR_BOX_RED_CHICKEN:
      data->tile = OBJ_BOX_RED;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_BOX_BLUE_FOOTBALL:
    case FN_ACTOR_BOX_BLUE_JOYSTICK:
    case FN_ACTOR_BOX_BLUE_DISK:
    case FN_ACTOR_BOX_BLUE_BALLOON:
    case FN_ACTOR_BOX_BLUE_FLAG:
    case FN_ACTOR_BOX_BLUE_RADIO:
      data->tile = OBJ_BOX_BLUE;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_BOX_GREY_EMPTY:
    case FN_ACTOR_BOX_GREY_BOOTS:
    case FN_ACTOR_BOX_GREY_CLAMPS:
    case FN_ACTOR_BOX_GREY_GUN:
    case FN_ACTOR_BOX_GREY_BOMB:
    case FN_ACTOR_BOX_GREY_GLOVE:
    case FN_ACTOR_BOX_GREY_FULL_LIFE:
    case FN_ACTOR_BOX_GREY_ACCESS_CARD:
    case FN_ACTOR_BOX_GREY_LETTER_D:
    case FN_ACTOR_BOX_GREY_LETTER_U:
    case FN_ACTOR_BOX_GREY_LETTER_K:
    case FN_ACTOR_BOX_GREY_LETTER_E:
      data->tile = OBJ_BOX_GREY;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_JOYSTICK:
      data->tile = OBJ_JOYSTICK;
      data->current_frame = 0;
      data->num_frames  = 1;
      break;
    case FN_ACTOR_FOOTBALL:
      data->tile = OBJ_FOOTBALL;
      data->current_frame = 0;
      data->num_frames  = 1;
      break;
    case FN_ACTOR_FLAG:
      data->tile = OBJ_FLAG;
      data->current_frame = 0;
      data->num_frames  = 3;
      break;
    case FN_ACTOR_DISK:
      data->tile = OBJ_DISK;
      data->current_frame = 0;
      data->num_frames  = 1;
      break;
    case FN_ACTOR_RADIO:
      data->tile = OBJ_RADIO;
      data->current_frame = 0;
      data->num_frames = 3;
      break;
    default:
      /* we got a type which should not be an item. */
      printf(__FILE__ ":%d: warning: item #%d"
          " added which is not an item\n",
          __LINE__, actor->type);
      break;
  }
}

/* --------------------------------------------------------------- */

/**
 * Delete an item.
 *
 * @param  actor  The item actor.
 */
void fn_actor_function_item_free(fn_actor_t * actor)
{
  fn_actor_item_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Hero starts to touch item.
 *
 * @param  actor  The item actor.
 */
void fn_actor_function_item_touch_start(fn_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_actor_item_data_t * data = (fn_actor_item_data_t *)actor->data;
  switch(actor->type) {
    case FN_ACTOR_LETTER_D:
      /* TODO */
      printf(__FILE__ ":%d: warning: the letter d"
          " cannot be fetched by the hero yet\n",
          __LINE__);
      break;
    case FN_ACTOR_LETTER_U:
      /* TODO */
      printf(__FILE__ ":%d: warning: the letter u"
          " cannot be fetched by the hero yet\n",
          __LINE__);
      break;
    case FN_ACTOR_LETTER_K:
      /* TODO */
      printf(__FILE__ ":%d: warning: the letter k"
          " cannot be fetched by the hero yet\n",
          __LINE__);
      break;
    case FN_ACTOR_LETTER_E:
      /* TODO */
      printf(__FILE__ ":%d: warning: the letter e"
          " cannot be fetched by the hero yet\n",
          __LINE__);
      break;
    case FN_ACTOR_FULL_LIFE:
      /* TODO */
      printf(__FILE__ ":%d: warning: the full life"
          " cannot be fetched by the hero yet\n",
          __LINE__);
      break;
    case FN_ACTOR_GUN:
      /* TODO */
      printf(__FILE__ ":%d: warning: the gun"
          " cannot be fetched by the hero yet\n",
          __LINE__);
      break;
    case FN_ACTOR_ACCESS_CARD:
      /* TODO */
      printf(__FILE__ ":%d: warning: the access card"
          " cannot be fetched by the hero yet\n",
          __LINE__);
      break;
    case FN_ACTOR_GLOVE:
      /* TODO */
      printf(__FILE__ ":%d: warning: the glove"
          " cannot be fetched by the hero yet\n",
          __LINE__);
      break;
    case FN_ACTOR_BOOTS:
      /* TODO */
      printf(__FILE__ ":%d: warning: the boots"
          " cannot be fetched by the hero yet\n",
          __LINE__);
      break;
    case FN_ACTOR_CLAMPS:
      /* TODO */
      printf(__FILE__ ":%d: warning: the clamps"
          " cannot be fetched by the hero yet\n",
          __LINE__);
      break;
    case FN_ACTOR_FOOTBALL:
      fn_hero_add_score(hero, 100);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_100, actor->x, actor->y);
      actor->is_alive = 0;
      break;
    case FN_ACTOR_DISK:
      fn_hero_add_score(hero, 5000);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_5000, actor->x, actor->y);
      actor->is_alive = 0;
      break;
    case FN_ACTOR_JOYSTICK:
      fn_hero_add_score(hero, 2000);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_2000, actor->x, actor->y);
      actor->is_alive = 0;
      break;
    case FN_ACTOR_RADIO:
    case FN_ACTOR_FLAG:
      switch(data->current_frame) {
        case 0:
          fn_hero_add_score(hero, 100);
          fn_level_add_actor(actor->level,
              FN_ACTOR_SCORE_100, actor->x, actor->y);
          break;
        case 1:
          fn_hero_add_score(hero, 2000);
          fn_level_add_actor(actor->level,
              FN_ACTOR_SCORE_2000, actor->x, actor->y);
          break;
        case 2:
          fn_hero_add_score(hero, 5000);
          fn_level_add_actor(actor->level,
              FN_ACTOR_SCORE_5000, actor->x, actor->y);
          break;
      }
      actor->is_alive = 0;
      break;
    default:
      /* do nothing about other items */
      break;
  }
}

/* --------------------------------------------------------------- */

/**
 * Hero stops to touch item.
 *
 * @param  actor  The item actor.
 */
void fn_actor_function_item_touch_end(fn_actor_t * actor) {
  /* Nothing to do here */
}

/* --------------------------------------------------------------- */

/**
 * Action for item.
 *
 * @param  actor  The item actor.
 */
void fn_actor_function_item_act(fn_actor_t * actor)
{
  fn_actor_item_data_t * data = actor->data;
  data->current_frame++;
  data->current_frame %= data->num_frames;
  if (!fn_level_is_solid(actor->level,
        (actor->x) / FN_TILE_WIDTH,
        (actor->y) / FN_TILE_HEIGHT + 1)) {
    actor->y += FN_HALFTILE_HEIGHT;
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit the item.
 *
 * @param  actor  The animation actor.
 */
void fn_actor_function_item_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_actor_item_data_t * data = actor->data;
  SDL_Surface * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The score struct.
 * Scores are elements which get shown when the hero has fetched
 * an item for which he gets points. The score element slowly
 * flys up until it disappears by itself. Scores are animated by
 * two frames which appear alternating.
 */
typedef struct fn_actor_score_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The counter which defines for how many steps the score
   * will fly up until it disappears. Gets reduced every
   * time the act function is called.
   */
  Uint8 countdown;
} fn_actor_score_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a score.
 *
 * @param  actor  The score actor.
 */
void fn_actor_function_score_create(fn_actor_t * actor)
{
  fn_actor_score_data_t * data = malloc(
      sizeof(fn_actor_score_data_t));
  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  data->countdown = 40;

  switch(actor->type) {
    case FN_ACTOR_SCORE_100:
      data->tile = NUMB_100;
      break;
    case FN_ACTOR_SCORE_200:
      data->tile = NUMB_200;
      break;
    case FN_ACTOR_SCORE_500:
      data->tile = NUMB_500;
      break;
    case FN_ACTOR_SCORE_1000:
      data->tile = NUMB_1000;
      break;
    case FN_ACTOR_SCORE_2000:
      data->tile = NUMB_2000;
      break;
    case FN_ACTOR_SCORE_5000:
      data->tile = NUMB_5000;
      break;
    case FN_ACTOR_SCORE_10000:
      data->tile = NUMB_10000;
      break;
    case FN_ACTOR_SCORE_BONUS_1_LEFT:
      data->tile = NUMB_BONUS_1_LEFT;
      break;
    case FN_ACTOR_SCORE_BONUS_1_RIGHT:
      data->tile = NUMB_BONUS_1_RIGHT;
      break;
    case FN_ACTOR_SCORE_BONUS_2_LEFT:
      data->tile = NUMB_BONUS_2_LEFT;
      break;
    case FN_ACTOR_SCORE_BONUS_2_RIGHT:
      data->tile = NUMB_BONUS_2_RIGHT;
      break;
    case FN_ACTOR_SCORE_BONUS_3_LEFT:
      data->tile = NUMB_BONUS_3_LEFT;
      break;
    case FN_ACTOR_SCORE_BONUS_3_RIGHT:
      data->tile = NUMB_BONUS_3_RIGHT;
      break;
    case FN_ACTOR_SCORE_BONUS_4_LEFT:
      data->tile = NUMB_BONUS_4_LEFT;
      break;
    case FN_ACTOR_SCORE_BONUS_4_RIGHT:
      data->tile = NUMB_BONUS_4_RIGHT;
      break;
    case FN_ACTOR_SCORE_BONUS_5_LEFT:
      data->tile = NUMB_BONUS_5_LEFT;
      break;
    case FN_ACTOR_SCORE_BONUS_5_RIGHT:
      data->tile = NUMB_BONUS_5_RIGHT;
      break;
    case FN_ACTOR_SCORE_BONUS_6_LEFT:
      data->tile = NUMB_BONUS_6_LEFT;
      break;
    case FN_ACTOR_SCORE_BONUS_6_RIGHT:
      data->tile = NUMB_BONUS_6_RIGHT;
      break;
    case FN_ACTOR_SCORE_BONUS_7_LEFT:
      data->tile = NUMB_BONUS_7_LEFT;
      break;
    case FN_ACTOR_SCORE_BONUS_7_RIGHT:
      data->tile = NUMB_BONUS_7_RIGHT;
      break;
    default:
      break;
  }
}

/* --------------------------------------------------------------- */

/**
 * Delete a score.
 *
 * @param  actor  The score actor.
 */
void fn_actor_function_score_free(fn_actor_t * actor)
{
  fn_actor_score_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Action for score.
 * 
 * @param  actor  The score actor.
 */
void fn_actor_function_score_act(fn_actor_t * actor)
{
  fn_actor_score_data_t * data = actor->data;
  data->countdown--;
  actor->y--;
  if (data->countdown == 0 || actor->y == 0) {
    actor->is_alive = 0;
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit the score.
 *
 * @param  actor  The score actor.
 */
void fn_actor_function_score_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_actor_score_data_t * data = actor->data;
  SDL_Surface * tile = fn_tilecache_get_tile(tc,
      data->tile + (data->countdown % 2));
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The hero touches a key actor.
 *
 * @param  actor  The key actor.
 */
void fn_actor_function_key_touch_start(fn_actor_t * actor)
{
  printf("******** hero touches key.\n");
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  Uint8 inventory = fn_hero_get_inventory(hero);
  switch(actor->type) {
    case FN_ACTOR_KEY_RED:
      inventory |= FN_INVENTORY_KEY_RED;
      break;
    case FN_ACTOR_KEY_BLUE:
      inventory |= FN_INVENTORY_KEY_BLUE;
      break;
    case FN_ACTOR_KEY_GREEN:
      inventory |= FN_INVENTORY_KEY_GREEN;
      break;
    case FN_ACTOR_KEY_PINK:
      inventory |= FN_INVENTORY_KEY_PINK;
      break;
    default:
      printf(__FILE__ ":%d: warning: key #%d"
          " added which is not a key\n",
          __LINE__, actor->type);
      break;
  }
  actor->is_alive = 0;
  fn_hero_set_inventory(hero, inventory);
}

/* --------------------------------------------------------------- */

/**
 * Blit the key.
 *
 * @param  actor  The key actor.
 */
void fn_actor_function_key_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * tile = NULL;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;
  switch(actor->type) {
    case FN_ACTOR_KEY_RED:
      tile = fn_tilecache_get_tile(tc, OBJ_KEY_RED);
      break;
    case FN_ACTOR_KEY_BLUE:
      tile = fn_tilecache_get_tile(tc, OBJ_KEY_BLUE);
      break;
    case FN_ACTOR_KEY_GREEN:
      tile = fn_tilecache_get_tile(tc, OBJ_KEY_GREEN);
      break;
    case FN_ACTOR_KEY_PINK:
      tile = fn_tilecache_get_tile(tc, OBJ_KEY_PINK);
      break;
    default:
      printf(__FILE__ ":%d: warning: key #%d"
          " tried to blit which is not a key\n",
          __LINE__, actor->type);
      return;
      break;
  }
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef void (* fn_actor_function_t)(fn_actor_t *);

/**
 * An array of functions to call for different actions on different
 * actors.
 */
void
  (* fn_actor_functions[FN_ACTOR_NUM_TYPES][FN_ACTOR_NUM_FUNCTIONS])
  (fn_actor_t *) =
{
  [FN_ACTOR_FIREWHEELBOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_FLAMEGNOMEBOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_FLYINGBOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_FOOTBOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_HELICOPTERBOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_RABBITOIDBOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_REDBALL_JUMPING] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_REDBALL_LYING] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_ROBOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_SNAKEBOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_TANKBOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_WALLCRAWLERBOT_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_WALLCRAWLERBOT_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_DRPROTON] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_CAMERA] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOMB] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_EXITDOOR] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_SODA] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_UNSTABLEFLOOR] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_FAN_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_FAN_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BROKENWALL_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_STONE_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_TELEPORTER1] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_TELEPORTER2] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_FENCE_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_WINDOW_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_SCREEN] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_EMPTY] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_BOX_GREY_BOOTS] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_BOOTS] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_CLAMPS] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = 
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_CLAMPS] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_GUN] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_GUN] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_BOMB] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_BOX_RED_SODA] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_BOX_RED_CHICKEN] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_CHICKEN_SINGLE] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_CHICKEN_DOUBLE] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_BLUE_FOOTBALL] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_FOOTBALL] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_FLAG] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_BOX_BLUE_JOYSTICK] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_JOYSTICK] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_BOX_BLUE_DISK] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_DISK] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_BOX_BLUE_BALLOON] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_BALLOON] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_GLOVE] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_GLOVE] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_FULL_LIFE] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_FULL_LIFE] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_BLUE_FLAG] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_BLUE_FLAG] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_BLUE_RADIO] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_RADIO] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_BOX_GREY_ACCESS_CARD] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_ACCESS_CARD] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_LETTER_D] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_LETTER_D] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_LETTER_U] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_LETTER_U] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_LETTER_K] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_LETTER_K] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_LETTER_E] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_item_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_item_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_item_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_item_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_item_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_item_blit,
  },
  [FN_ACTOR_LETTER_E] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_KEY_RED] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_key_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_key_blit,
  },
  [FN_ACTOR_KEYHOLE_RED] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_DOOR_RED] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_KEY_BLUE] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_key_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_key_blit,
  },
  [FN_ACTOR_KEYHOLE_BLUE] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_DOOR_BLUE] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_KEY_PINK] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_key_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_key_blit,
  },
  [FN_ACTOR_KEYHOLE_PINK] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_DOOR_PINK] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_KEY_GREEN] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_key_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_key_blit,
  },
  [FN_ACTOR_KEYHOLE_GREEN] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_DOOR_GREEN] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_MILL] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_ACCESS_CARD_DOOR] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_SCORE_100] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_200] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_500] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_1000] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_2000] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_5000] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_10000] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_1_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_1_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_2_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_2_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_3_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_3_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_4_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_4_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_5_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_5_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_6_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_6_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_7_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_SCORE_BONUS_7_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_score_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_score_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_score_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_score_blit,
  },
  [FN_ACTOR_BLUE_LIGHT_BACKGROUND1] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_BLUE_LIGHT_BACKGROUND2] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_BLUE_LIGHT_BACKGROUND3] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_BLUE_LIGHT_BACKGROUND4] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_TEXT_ON_SCREEN_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_HIGH_VOLTAGE_FLASH_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_RED_FLASHLIGHT_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_BLUE_FLASHLIGHT_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_KEYPANEL_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_RED_ROTATIONLIGHT_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_UPARROW_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_GREEN_POISON_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
  [FN_ACTOR_LAVA_BACKGROUND] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_simpleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                = 
      fn_actor_function_simpleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = 
      fn_actor_function_simpleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_simpleanimation_blit,
  },
};

/* --------------------------------------------------------------- */

fn_actor_t * fn_actor_create(fn_level_t * level,
    fn_actor_type_e type,
    Uint16 x,
    Uint16 y)
{
  fn_actor_function_t func = NULL;
  fn_actor_t * actor = malloc(sizeof(fn_actor_t));
  actor->level = level;
  actor->type = type;
  actor->x = x;
  actor->y = y;
  actor->w = 0; /* should be changed by func */
  actor->h = 0; /* should be changed by func */
  actor->is_alive = 1;
  actor->touches_hero = 0;
  func = fn_actor_functions[actor->type][FN_ACTOR_FUNCTION_CREATE];
  if (func != NULL) {
    func(actor);
  }
  return actor;
}

/* --------------------------------------------------------------- */

void fn_actor_free(fn_actor_t * actor)
{
  fn_actor_function_t func =
    fn_actor_functions[actor->type][FN_ACTOR_FUNCTION_FREE];
  if (func != NULL) {
    func(actor);
  }
  free(actor);
}

/* --------------------------------------------------------------- */

int fn_actor_touches_hero(fn_actor_t * actor)
{
  Uint16 hero_x =
    fn_hero_get_x(fn_level_get_hero(actor->level)) * FN_HALFTILE_WIDTH;
  Uint16 hero_y =
    fn_hero_get_y(fn_level_get_hero(actor->level)) * FN_HALFTILE_HEIGHT;
  Uint16 hero_w = FN_TILE_WIDTH;
  Uint16 hero_h = FN_TILE_WIDTH;

  if (hero_x + hero_w <= (actor->x)) {
    /* hero is left of actor */
    return 0;
  }
  if (hero_x >= (actor->x + actor->w)) {
    /* hero is right of actor */
    return 0;
  }
  if (hero_y + hero_h <= (actor->y)) {
    /* hero is above actor */
    return 0;
  }
  if (hero_y >= (actor->y + actor->h)) {
    /* hero is below actor */
    return 0;
  }

  /* in any other case, the hero touches the actor. */
  return 1;
}

/* --------------------------------------------------------------- */

void fn_actor_check_hero_touch(fn_actor_t * actor)
{
  if (fn_actor_touches_hero(actor)) {
    if (!actor->touches_hero) {
      actor->touches_hero = 1;
      fn_actor_hero_touch_start(actor);
    }
  } else {
    if (actor->touches_hero) {
      fn_actor_hero_touch_end(actor);
      actor->touches_hero = 0;
    }
  }
}

/* --------------------------------------------------------------- */

void fn_actor_hero_touch_start(fn_actor_t * actor)
{
  fn_actor_function_t func =
    fn_actor_functions[actor->type][FN_ACTOR_FUNCTION_HERO_TOUCH_START];
  if (func != NULL) {
    func(actor);
  }
}

/* --------------------------------------------------------------- */

void fn_actor_hero_touch_end(fn_actor_t * actor)
{
  fn_actor_function_t func =
    fn_actor_functions[actor->type][FN_ACTOR_FUNCTION_HERO_TOUCH_END];
  if (func != NULL) {
    func(actor);
  }
}

/* --------------------------------------------------------------- */

void fn_actor_hero_interact_start(fn_actor_t * actor)
{
  fn_actor_function_t func =
    fn_actor_functions[actor->type][FN_ACTOR_FUNCTION_HERO_INTERACT_START];
  if (func != NULL) {
    func(actor);
  }
}

/* --------------------------------------------------------------- */

void fn_actor_hero_interact_stop(fn_actor_t * actor)
{
  fn_actor_function_t func =
    fn_actor_functions[actor->type][FN_ACTOR_FUNCTION_HERO_INTERACT_END];
  if (func != NULL) {
    func(actor);
  }
}

/* --------------------------------------------------------------- */

int fn_actor_act(fn_actor_t * actor)
{
  fn_actor_check_hero_touch(actor);
  fn_actor_function_t func =
    fn_actor_functions[actor->type][FN_ACTOR_FUNCTION_ACT];
  if (func != NULL) {
    func(actor);
  }
  return actor->is_alive;
}

/* --------------------------------------------------------------- */

void fn_actor_blit(fn_actor_t * actor)
{
  fn_actor_function_t func =
    fn_actor_functions[actor->type][FN_ACTOR_FUNCTION_BLIT];
  if (func != NULL) {
    func(actor);
  }
}

/* --------------------------------------------------------------- */

Uint16 fn_actor_get_x(fn_actor_t * actor)
{
  return actor->x;
}

/* --------------------------------------------------------------- */

Uint16 fn_actor_get_y(fn_actor_t * actor)
{
  return actor->y;
}

/* --------------------------------------------------------------- */

