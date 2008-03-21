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
 *
 * @param  tile           The tile number for the tilecache.
 * @param  current_frame  The number of the current frame.
 * @param  num_frames     The complete number of frames for the animation.
 */
typedef struct fn_actor_simpleanimation_data_t {
  Uint16 tile;
  Uint8 current_frame;
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
    case FN_ACTOR_BLUE_LIGHT_BACKGROUND1:
      data->tile = 0x20;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_BLUE_LIGHT_BACKGROUND2:
      data->tile = 0x21;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_BLUE_LIGHT_BACKGROUND3:
      data->tile = 0x22;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_BLUE_LIGHT_BACKGROUND4:
      data->tile = 0x23;
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
  destrect.h = actor->w * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_BOOTS] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_RED_SODA] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_RED_CHICKEN] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_FOOTBALL] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_BLUE_JOYSTICK] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_JOYSTICK] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_BLUE_DISK] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_DISK] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_BLUE_BALLOON] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_RADIO] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BOX_GREY_ACCESS_CARD] = {
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
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

void fn_actor_check_hero_touch(fn_actor_t * actor)
{
  /*
   * TODO pseudocode:
   * check if actor touches hero
   * if actor did not touch before, but does now then
   *   call fn_actor_hero_touch_start
   * else if actor did touch before, but does no longer now
   *   call fn_actor_hero_touch_end
   */
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

