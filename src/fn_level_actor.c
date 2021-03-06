/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Level actor functions
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

#include <stdlib.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"
#include "fn_level_actor.h"
#include "fn_object.h"
#include "fn_infobox.h"
#include "fn_error_cmdline.h"
#include "fn_collision.h"

/* --------------------------------------------------------------- */

/**
 * The different types of functions which can be executed on the actor.
 */
typedef enum fn_level_actor_function_type_e {
  /**
   * The create function. Allocates memory and sets properties.
   */
  FN_LEVEL_ACTOR_FUNCTION_CREATE,
  /**
   * The free function. Frees the used memory.
   */
  FN_LEVEL_ACTOR_FUNCTION_FREE,
  /**
   * The touch_start function. Is called when the hero starts touching
   * the actor.
   */
  FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START,
  /**
   * The touch_end function. Is called when the hero stops touching
   * the actor.
   */
  FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END,
  /**
   * The interact_start function. Is called when the hero starts to
   * interact with the actor.
   */
  FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START,
  /**
   * The interact_end function. Is called when the hero stops to
   * interact with the actor.
   */
  FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END,
  /**
   * The act function. Is called on fixed time slices. This is
   * where the actual action takes place.
   */
  FN_LEVEL_ACTOR_FUNCTION_ACT,
  /**
   * The blit function. Blits the actor into the level in which
   * it is placed.
   */
  FN_LEVEL_ACTOR_FUNCTION_BLIT,
  /**
   * The actor gets hit by a shot.
   */
  FN_LEVEL_ACTOR_FUNCTION_SHOT,
  /**
   * The number of functions. Only used for getting the enum bounds.
   */
  FN_LEVEL_ACTOR_NUM_FUNCTIONS
} fn_level_actor_function_type_e;

/* --------------------------------------------------------------- */

/**
 * The simple animation struct.
 * A simple animation is an animation which is one part high,
 * one part wide and has a fixed number of frames that occur
 * one after each other and are lined up in a row inside
 * the tilecache.
 */
typedef struct fn_level_actor_simpleanimation_data_t {
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
} fn_level_actor_simpleanimation_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a simple animation.
 *
 * @param  actor The animation actor.
 */
void fn_level_actor_function_simpleanimation_create(fn_level_actor_t * actor)
{
  fn_level_actor_simpleanimation_data_t * data = malloc(
      sizeof(fn_level_actor_simpleanimation_data_t));

  actor->is_in_foreground = 0;
  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  switch(actor->type) {
    case FN_LEVEL_ACTOR_TEXT_ON_SCREEN_BACKGROUND:
      data->tile = 0x0004;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_HIGH_VOLTAGE_FLASH_BACKGROUND:
      data->tile = 0x0008;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_RED_FLASHLIGHT_BACKGROUND:
      data->tile = 0x000C;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_BLUE_FLASHLIGHT_BACKGROUND:
      data->tile = 0x0010;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_KEYPANEL_BACKGROUND:
      data->tile = 0x0014;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_RED_ROTATIONLIGHT_BACKGROUND:
      data->tile = 0x0018;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_UPARROW_BACKGROUND:
      data->tile = 0x001C;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND1:
      data->tile = 0x0020;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND2:
      data->tile = 0x0021;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND3:
      data->tile = 0x0022;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND4:
      data->tile = 0x0023;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_GREEN_POISON_BACKGROUND:
      data->tile = 0x0028;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_LAVA_BACKGROUND:
      data->tile = 0x002C;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_WINDOWLEFT_BACKGROUND:
      data->tile = ANIM_WINDOWBG;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_WINDOWRIGHT_BACKGROUND:
      data->tile = ANIM_WINDOWBG + 1;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_STONEWINDOW_BACKGROUND:
      data->tile = ANIM_STONEWINDOWBG;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_BROKENWALL_BACKGROUND:
      data->tile = ANIM_BROKENWALLBG;
      data->current_frame = 0;
      data->num_frames = 1;
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
void fn_level_actor_function_simpleanimation_free(fn_level_actor_t * actor)
{
  fn_level_actor_simpleanimation_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}


/* --------------------------------------------------------------- */

/**
 * Action for simple animation.
 *
 * @param  actor  The animation actor.
 */
void fn_level_actor_function_simpleanimation_act(fn_level_actor_t * actor)
{
  fn_level_actor_simpleanimation_data_t * data = actor->data;
  data->current_frame++;
  data->current_frame %= data->num_frames;
}

/* --------------------------------------------------------------- */

/**
 * Blit the simple animation.
 *
 * @param  actor  The animation actor.
 */
void fn_level_actor_function_simpleanimation_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_level_actor_simpleanimation_data_t * data = actor->data;
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The jumping red ball.
 */
typedef struct fn_level_actor_redball_jumping_data_t {
  /**
   * The tile number which is to be blitted in the level.
   */
  Uint16 tile;
  /**
   * The counter for the position inside the loop.
   */
  Uint8 counter;
  /**
   * The base position of the ball.
   */
  Uint16 base_y;
} fn_level_actor_redball_jumping_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_jumping_create(fn_level_actor_t * actor)
{
  fn_level_actor_redball_jumping_data_t * data = malloc(
      sizeof(fn_level_actor_redball_jumping_data_t));
  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  data->counter = 0;
  data->tile = ANIM_MINE;
  data->base_y = actor->position.y;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_jumping_free(fn_level_actor_t * actor)
{
  fn_level_actor_redball_jumping_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_jumping_hero_touch_start(
    fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_increase_hurting_actors(hero, actor);
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_jumping_hero_touch_end(
    fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_jumping_act(fn_level_actor_t * actor)
{
  fn_level_actor_redball_jumping_data_t * data = actor->data;

  Uint8 distance = 0;
  switch(data->counter) {
    case 0:
      distance = 0;
      break;
    case 1:
    case 11:
      distance = 16;
      break;
    case 2:
    case 10:
      distance = 28;
      break;
    case 3:
    case 9:
      distance = 36;
      break;
    case 4:
    case 8:
      distance = 40;
      break;
    case 5:
    case 7:
      distance = 41;
      break;
    case 6:
      distance = 42;
      break;
    default:
      distance = 0;
      break;
  }
  actor->position.y = data->base_y - distance;

  data->counter++;
  data->counter %= 12;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_jumping_blit(fn_level_actor_t * actor)
{
  fn_level_actor_redball_jumping_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_jumping_shot(fn_level_actor_t * actor)
{
  /*
   * Do nothing. This function just exists so that the red
   * ball absorbs the bullet when it is shot.
   */
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The lying red ball.
 */
typedef struct fn_level_actor_redball_lying_data_t {
  /**
   * The tile number which is to be blitted in the level.
   */
  Uint16 tile;
  /**
   * Flag that stores if the redball is touching the hero.
   */
  Uint8 touching_hero;
} fn_level_actor_redball_lying_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_lying_create(fn_level_actor_t * actor)
{
  fn_level_actor_redball_lying_data_t * data = malloc(
      sizeof(fn_level_actor_redball_lying_data_t));
  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  data->tile = ANIM_MINE;
  data->touching_hero = 0;
}


/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_lying_free(fn_level_actor_t * actor)
{
  fn_level_actor_redball_lying_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_lying_hero_touch_start(
    fn_level_actor_t * actor)
{
  fn_level_actor_redball_lying_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (!data->touching_hero) {
    data->touching_hero = 1;
    fn_hero_increase_hurting_actors(hero, actor);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_lying_act(
    fn_level_actor_t * actor)
{
  fn_level_actor_redball_lying_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  if (!fn_level_is_solid(actor->level,
        (actor->position.x) / FN_TILE_WIDTH,
        (actor->position.y) / FN_TILE_HEIGHT + 1)) {
    actor->position.y += FN_HALFTILE_HEIGHT;
  }

  if (data->touching_hero == 1) {
    data->touching_hero++;
  } else if (data->touching_hero > 1) {
    fn_hero_decrease_hurting_actors(hero, actor);
    actor->is_alive = 0;
    fn_level_add_actor(actor->level,
        FN_LEVEL_ACTOR_FIRE, actor->position.x, actor->position.y);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_redball_lying_blit(fn_level_actor_t * actor)
{
  fn_level_actor_redball_lying_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The robot.
 */
typedef struct fn_level_actor_robot_data_t {
  /**
   * The direction to which the robot moves.
   */
  fn_horizontal_direction_e direction;
  /**
   * The tile number.
   */
  Uint16 tile;
  /**
   * The animation counter.
   */
  Uint8 current_frame;
  /**
   * The number of frames.
   */
  Uint8 num_frames;
  /**
   * A flag indicating if the robot is currently touching the hero.
   */
  Uint8 touching_hero;
} fn_level_actor_robot_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_robot_create(fn_level_actor_t * actor)
{
  fn_level_actor_robot_data_t * data = malloc(
      sizeof(fn_level_actor_robot_data_t));
  actor->data = data;
  actor->is_in_foreground = 1;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  data->direction = fn_horizontal_direction_left;
  data->tile = ANIM_ROBOT;
  data->current_frame = 0;
  data->num_frames = 3;
  data->touching_hero = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_robot_free(fn_level_actor_t * actor)
{
  fn_level_actor_robot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);

  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_robot_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_robot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_increase_hurting_actors(hero, actor);
  data->touching_hero = 1;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_robot_touch_end(fn_level_actor_t * actor)
{
  fn_level_actor_robot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
  data->touching_hero = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_robot_act(fn_level_actor_t * actor)
{
  fn_level_actor_robot_data_t * data = actor->data;
  data->current_frame++;

  data->current_frame %= data->num_frames;
  if (!fn_level_is_solid(actor->level,
        (actor->position.x) / FN_TILE_WIDTH,
        (actor->position.y) / FN_TILE_HEIGHT + 1)) {
    /* still in the air, so let the robot fall down. */
    actor->position.y += FN_HALFTILE_HEIGHT;
  } else {
    /* on the floor, so let's walk */
    if (data->current_frame == 0) {
      int direction = (
          data->direction == fn_horizontal_direction_left ?
          -1 :
          2);
      if (
          /* Check if the place next to the bot is free */
          !fn_level_is_solid(actor->level,
            (actor->position.x + direction * FN_HALFTILE_WIDTH) /
            FN_TILE_WIDTH,
            (actor->position.y) / FN_TILE_HEIGHT) &&
          /* Check if it is solid below this place */
          fn_level_is_solid(actor->level,
            (actor->position.x + direction * FN_HALFTILE_WIDTH) /
            FN_TILE_WIDTH,
            (actor->position.y+FN_TILE_HEIGHT) / FN_TILE_HEIGHT)
         )
      {
        if (direction == 2) direction = 1;
        actor->position.x += direction * FN_HALFTILE_WIDTH;
      } else {
        data->direction = (
            data->direction == fn_horizontal_direction_left ?
            fn_horizontal_direction_right :
            fn_horizontal_direction_left);

        if (direction == 2) direction = 1;
        direction *= (-1);
        actor->position.x += direction * FN_HALFTILE_WIDTH;
      }
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_robot_blit(fn_level_actor_t * actor)
{
  fn_level_actor_robot_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_robot_shot(fn_level_actor_t * actor)
{
  fn_level_actor_robot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  fn_hero_add_score(hero, 100);
  if (data->touching_hero) {
    fn_hero_decrease_hurting_actors(hero, actor);
    data->touching_hero = 0;
  }
  fn_level_add_actor(actor->level,
      FN_LEVEL_ACTOR_ROBOT_DISAPPEARING,
      actor->position.x,
      actor->position.y);
  actor->is_alive = 0;
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The tankbot.
 */
typedef struct fn_level_actor_tankbot_data_t {
  /**
   * The direction to which the robot moves.
   */
  fn_horizontal_direction_e direction;
  /**
   * The tile number.
   */
  Uint16 tile;
  /**
   * The animation counter.
   */
  Uint8 current_frame;
  /**
   * The number of frames.
   */
  Uint8 num_frames;
  /**
   * A counter counting how often the bot was hit by the hero.
   * If 0, the bot is healthy. If 1, the bot was hit once and is
   * damaged (pushes steam clouds out), if 2 the bot is killed.
   */
  Uint8 was_shot;
  /**
   * A flag indicating if the robot is currently touching the hero.
   */
  Uint8 touching_hero;
} fn_level_actor_tankbot_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_tankbot_create(fn_level_actor_t * actor)
{
  fn_level_actor_tankbot_data_t * data = malloc(
      sizeof(fn_level_actor_tankbot_data_t));
  actor->data = data;
  actor->is_in_foreground = 1;
  actor->position.w = FN_TILE_WIDTH * 2;
  actor->position.h = FN_TILE_HEIGHT;
  data->direction = fn_horizontal_direction_left;
  data->tile = ANIM_CARBOT;
  data->current_frame = 0;
  data->num_frames = 4;
  data->was_shot = 0;
  data->touching_hero = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_tankbot_free(fn_level_actor_t * actor)
{
  fn_level_actor_tankbot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);

  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_tankbot_hero_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_tankbot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (data->was_shot < 2) {
    fn_hero_increase_hurting_actors(hero, actor);
    data->touching_hero = 1;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_tankbot_hero_touch_end(fn_level_actor_t * actor)
{
  fn_level_actor_tankbot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (data->was_shot < 2) {
    fn_hero_decrease_hurting_actors(hero, actor);
    data->touching_hero = 0;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_tankbot_act(fn_level_actor_t * actor)
{
  fn_level_actor_tankbot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  data->current_frame++;
  if (data->was_shot == 2) {
    /* create explosion */
    actor->is_alive = 0;
    fn_level_add_actor(actor->level,
        FN_LEVEL_ACTOR_EXPLOSION,
        actor->position.x + FN_HALFTILE_WIDTH,
        actor->position.y);
    fn_hero_add_score(hero, 2500);
    fn_level_add_particle_firework(
        actor->level, actor->position.x, actor->position.y, 4);
  } else {
    data->current_frame %= data->num_frames;
    if (!fn_level_is_solid(actor->level,
          (actor->position.x) / FN_TILE_WIDTH,
          (actor->position.y) / FN_TILE_HEIGHT + 1) &&
        !fn_level_is_solid(actor->level,
          (actor->position.x) / FN_TILE_WIDTH + 1,
          (actor->position.y) / FN_TILE_HEIGHT + 1)) {
      /* still in the air, so let the robot fall down */
      actor->position.y += FN_HALFTILE_HEIGHT;
    } else {
      /* on the floor, so let's walk */
      int direction = (data->direction == fn_horizontal_direction_left ?
          -1 : 4);
      if (
          /* check if the place next to the bot is free */
          !fn_level_is_solid(actor->level,
            (actor->position.x +
             direction * FN_HALFTILE_WIDTH) / FN_TILE_WIDTH,
            (actor->position.y) / FN_TILE_HEIGHT) &&
          /* check if it is solid below this place */
          fn_level_is_solid(actor->level,
            (actor->position.x +
             direction * FN_HALFTILE_WIDTH) / FN_TILE_WIDTH,
            (actor->position.y + FN_TILE_HEIGHT) / FN_TILE_HEIGHT)
         )
      {
        if (direction > 0) {
          direction = 1;
        }
        actor->position.x += direction * FN_HALFTILE_WIDTH * 0.7;
      } else {
        /* Reached the end, so turn around */
        data->direction = (
            data->direction == fn_horizontal_direction_left ?
            fn_horizontal_direction_right :
            fn_horizontal_direction_left);
        if (direction > 0) direction = 1;
        direction *= -1;
        actor->position.x += direction * FN_HALFTILE_WIDTH;
        data->tile += 4 * direction;

        if (direction > 0) {
          fn_level_add_actor(actor->level,
             FN_LEVEL_ACTOR_HOSTILESHOT_RIGHT,
             actor->position.x, actor->position.y - 6);
        } else {
          fn_level_add_actor(actor->level,
             FN_LEVEL_ACTOR_HOSTILESHOT_LEFT,
             actor->position.x, actor->position.y - 6);
        }
      }
    }
  }
  if (data->was_shot == 1) {
    /* create steam clouds */
    if (data->current_frame == 0) {
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_STEAM, actor->position.x + FN_HALFTILE_WIDTH,
          actor->position.y - FN_TILE_HEIGHT);
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_tankbot_blit(fn_level_actor_t * actor)
{
  fn_level_actor_tankbot_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + (data->current_frame/2) * 2);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  tile = fn_tilecache_get_tile(tc,
      data->tile + (data->current_frame/2) * 2 + 1);
  destrect.x += pixelsize * FN_TILE_WIDTH;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_tankbot_shot(fn_level_actor_t * actor)
{
  fn_level_actor_tankbot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  if (data->was_shot == 1 && data->touching_hero) {
    fn_hero_decrease_hurting_actors(hero, actor);
    data->touching_hero = 0;
  }
  if (!(data->was_shot == 2)) {
    data->was_shot++;
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The firewheel bot.
 */
typedef struct fn_level_actor_firewheelbot_data_t {
  /**
   * The direction to which the robot moves.
   */
  fn_horizontal_direction_e direction;
  /**
   * The tile number.
   */
  Uint16 tile;
  /**
   * The animation counter.
   */
  Uint8 current_frame;
  /**
   * The number of frames.
   */
  Uint8 num_frames;
  /**
   * A counter counting how often the bot was hit by the hero.
   * If 0, the bot is healthy. If 1, the bot was hit once and is
   * damaged (pushes steam clouds out), if 2 the bot is killed.
   */
  Uint8 was_shot;
  /**
   * A flag indicating if the robot is currently touching the hero.
   */
  Uint8 touching_hero;
  /**
   * A flag indicating if the robot currently has fire on.
   */
  Uint8 fire_is_on;
  /**
   * A counter for the number of cycles how long the fire is on.
   */
  Uint8 counter;
} fn_level_actor_firewheelbot_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_firewheelbot_create(fn_level_actor_t * actor)
{
  fn_level_actor_firewheelbot_data_t * data = malloc(
      sizeof(fn_level_actor_firewheelbot_data_t));
  actor->data = data;
  data->direction = fn_horizontal_direction_left;
  data->tile = ANIM_FIREWHEEL_OFF;
  data->current_frame = 0;
  data->num_frames = 4;
  data->was_shot = 0;
  data->touching_hero = 0;
  data->fire_is_on = 0;
  data->counter = 0;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_firewheelbot_free(fn_level_actor_t * actor)
{
  fn_level_actor_firewheelbot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);

  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_firewheelbot_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_firewheelbot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (data->was_shot < 2) {
    fn_hero_increase_hurting_actors(hero, actor);
    data->touching_hero = 1;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_firewheelbot_touch_end(fn_level_actor_t * actor)
{
  fn_level_actor_firewheelbot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (data->was_shot < 2) {
    fn_hero_decrease_hurting_actors(hero, actor);
    data->touching_hero = 0;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_firewheelbot_act(fn_level_actor_t * actor)
{
  fn_level_actor_firewheelbot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (data->was_shot == 2) {
    /* create explosion */
    actor->is_alive = 0;
    fn_level_add_actor(actor->level,
        FN_LEVEL_ACTOR_EXPLOSION, actor->position.x + FN_HALFTILE_WIDTH,
        actor->position.y);
    fn_level_add_particle_firework(
        actor->level, actor->position.x, actor->position.y, 8);
    fn_hero_add_score(hero, 2500);
  } else {
    data->counter++;
    if (data->counter % 2) {
      data->current_frame++;
      data->current_frame %= data->num_frames;
    }

    if (data->counter == 50) {
      data->counter = 0;
      data->fire_is_on = !(data->fire_is_on);
      if (data->fire_is_on) {
        data->tile = ANIM_FIREWHEEL_ON;
      } else {
        data->tile = ANIM_FIREWHEEL_OFF;
      }
    }

    int direction = (data->direction == fn_horizontal_direction_left ?
          -1 : 1);
    if (!fn_level_push_rect_standing_on_solid_ground(
        actor->level,
        &(actor->position),
        direction * FN_HALFTILE_WIDTH / 2,
        FN_HALFTILE_HEIGHT))
    {
      /* push was not successful, so we reverse the direction */
      data->direction =
        (data->direction == fn_horizontal_direction_left ?
         fn_horizontal_direction_right :
         fn_horizontal_direction_left);
    }

    if (data->was_shot == 1) {
      /* create steam clouds */
      if (data->current_frame == 0) {
        fn_level_add_actor(actor->level,
            FN_LEVEL_ACTOR_STEAM, actor->position.x + FN_HALFTILE_WIDTH,
            actor->position.y - FN_TILE_HEIGHT);
      }
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_firewheelbot_blit(fn_level_actor_t * actor)
{
  fn_level_actor_firewheelbot_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = NULL;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  
  tile = fn_tilecache_get_tile(tc,
      data->tile + (data->current_frame) * 4);
  destrect.x = (actor->position.x +
      actor->position.w / 2
      - FN_TILE_WIDTH) * pixelsize;
  destrect.y = (actor->position.y - FN_TILE_HEIGHT) * pixelsize;
  destrect.w = FN_TILE_WIDTH * 2 * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  tile = fn_tilecache_get_tile(tc,
      data->tile + (data->current_frame) * 4 + 1);
  destrect.x += pixelsize * FN_TILE_WIDTH;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  destrect.x -= pixelsize * FN_TILE_WIDTH;
  destrect.y += pixelsize * FN_TILE_HEIGHT;
  tile = fn_tilecache_get_tile(tc,
      data->tile + (data->current_frame) * 4 + 2);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  destrect.x += pixelsize * FN_TILE_WIDTH;
  tile = fn_tilecache_get_tile(tc,
      data->tile + (data->current_frame) * 4 + 3);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_firewheelbot_shot(fn_level_actor_t * actor)
{
  fn_level_actor_firewheelbot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  if (!(data->fire_is_on)) {
    if (data->was_shot == 1 && data->touching_hero) {
      fn_hero_decrease_hurting_actors(hero, actor);
      data->touching_hero = 0;
    }
    if (!(data->was_shot == 2)) {
      data->was_shot++;
    }
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The wallcrawler bot.
 */
typedef struct fn_level_actor_wallcrawler_data_t {
  /**
   * The direction to which the wallcrawler is moving.
   */
  fn_vertical_direction_e direction;
  /**
   * The direction to which the wallcrawler is orientated.
   */
  fn_horizontal_direction_e orientation;
  /**
   * The tile number.
   */
  Uint16 tile;
  /**
   * The animation counter.
   */
  Uint8 current_frame;
  /**
   * The number of frames.
   */
  Uint8 num_frames;
  /**
   * A flag indicating if the robot was shot.
   */
  Uint8 was_shot;
  /**
   * A flag indicating if the robot is currently touching the hero.
   */
  Uint8 touching_hero;
} fn_level_actor_wallcrawler_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_wallcrawler_create(fn_level_actor_t * actor)
{

  fn_level_actor_wallcrawler_data_t * data = malloc(
      sizeof(fn_level_actor_wallcrawler_data_t));
  actor->data = data;
  actor->is_in_foreground = 1;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  data->direction = fn_vertical_direction_up;
  if (actor->type == FN_LEVEL_ACTOR_WALLCRAWLERBOT_LEFT) {
    data->tile = ANIM_WALLCRAWLERBOT_LEFT;
    data->orientation = fn_horizontal_direction_left;
  } else {
    data->tile = ANIM_WALLCRAWLERBOT_RIGHT;
    data->orientation = fn_horizontal_direction_right;
  }

  data->current_frame = 0;
  data->num_frames = 4;
  data->was_shot = 0;
  data->touching_hero = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_wallcrawler_free(fn_level_actor_t * actor)
{
  fn_level_actor_wallcrawler_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);

  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_wallcrawler_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_wallcrawler_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (!data->was_shot) {
    fn_hero_increase_hurting_actors(hero, actor);
    data->touching_hero = 1;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_wallcrawler_touch_end(fn_level_actor_t * actor)
{
  fn_level_actor_wallcrawler_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (!data->was_shot) {
    fn_hero_decrease_hurting_actors(hero, actor);
    data->touching_hero = 0;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_wallcrawler_act(fn_level_actor_t * actor)
{
  fn_level_actor_wallcrawler_data_t * data = actor->data;
  fn_level_t * level = actor->level;

  int direction = (data->direction == fn_vertical_direction_up ?
      1 :
      -1);
  int orientation = (data->orientation == fn_horizontal_direction_left ?
      -1 :
      1);
  if (direction > 0) {
    /* going up */
    data->current_frame++;
    data->current_frame %= data->num_frames;

    if (
        /* bot collides with solid tile */
        fn_level_is_solid(level,
          (actor->position.x) / FN_TILE_WIDTH,
          (actor->position.y - 1) / FN_TILE_HEIGHT) ||
        /* bot has no more wall to stick upon */
        !fn_level_is_solid(level,
          (actor->position.x + orientation * FN_TILE_WIDTH) /
          FN_TILE_WIDTH,
          (actor->position.y - 1) / FN_TILE_HEIGHT)
       ) {
      actor->position.y++;
      data->direction = fn_vertical_direction_down;
    } else {
      actor->position.y--;
    }

  } else {
    /* going down */
    if (data->current_frame == 0) {
      data->current_frame = data->num_frames;
    }
    data->current_frame--;

    if (
        /* bot collides with solid tile */
        fn_level_is_solid(level,
          (actor->position.x) / FN_TILE_WIDTH,
          (actor->position.y + FN_TILE_HEIGHT) / FN_TILE_HEIGHT) ||
        /* bot has no more wall to stick upon */
        !fn_level_is_solid(level,
          (actor->position.x + orientation * FN_TILE_WIDTH) /
          FN_TILE_WIDTH,
          (actor->position.y + FN_TILE_HEIGHT) / FN_TILE_HEIGHT)
       ) {
      actor->position.y--;
      data->direction = fn_vertical_direction_up;
    } else {
      actor->position.y++;
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_wallcrawler_blit(fn_level_actor_t * actor)
{
  fn_level_actor_wallcrawler_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_wallcrawler_shot(fn_level_actor_t * actor)
{
  fn_level_actor_wallcrawler_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  if (!data->was_shot) {
    if (data->touching_hero) {
      fn_hero_decrease_hurting_actors(hero, actor);
      data->touching_hero = 0;
      data->current_frame = 0;
    }
    actor->is_alive = 0;
    fn_level_add_actor(actor->level,
        FN_LEVEL_ACTOR_STEAM, actor->position.x, actor->position.y);
    fn_level_add_actor(actor->level,
        FN_LEVEL_ACTOR_EXPLOSION, actor->position.x, actor->position.y);
    fn_hero_add_score(hero, 100);
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef enum fn_level_actor_lift_state_e {
  fn_level_actor_lift_state_idle,
  fn_level_actor_lift_state_ascending,
  fn_level_actor_lift_state_descending,
} fn_level_actor_lift_state_e;

/* --------------------------------------------------------------- */

/**
 * The lift.
 */
typedef struct fn_level_actor_lift_data_t {
  /**
   * The state of the lift.
   */
  fn_level_actor_lift_state_e state;
} fn_level_actor_lift_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a lift.
 *
 * @param  actor  The lift actor.
 */
void fn_level_actor_function_lift_create(fn_level_actor_t * actor)
{
  fn_level_actor_lift_data_t * data = malloc(
      sizeof(fn_level_actor_lift_data_t));
  data->state = fn_level_actor_lift_state_idle;
  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 0;
}

/* --------------------------------------------------------------- */

/**
 * Delete the lift.
 *
 * @param  actor  The lift actor.
 */
void fn_level_actor_function_lift_free(fn_level_actor_t * actor)
{
  fn_level_actor_lift_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Hero starts to interact with lift.
 *
 * @param  actor  The lift actor.
 */
void fn_level_actor_function_lift_interact_start(fn_level_actor_t * actor)
{
  fn_level_actor_lift_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  SDL_Rect * heropos = fn_hero_get_position(hero);
  if (fn_collision_touch_rect_rect(
        heropos, &(actor->position)) &&
      heropos->y + heropos->h == actor->position.y) {
    data->state = fn_level_actor_lift_state_ascending;
  }
}

/* --------------------------------------------------------------- */

/**
 * Hero stops to interact with lift.
 *
 * @param  actor  The lift actor.
 */
void fn_level_actor_function_lift_interact_end(fn_level_actor_t * actor)
{
  fn_level_actor_lift_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  SDL_Rect * heropos = fn_hero_get_position(hero);
  if (fn_collision_touch_rect_rect(
        heropos, &(actor->position)) &&
      heropos->x == actor->position.x) {
    data->state = fn_level_actor_lift_state_idle;
  } else {
    data->state = fn_level_actor_lift_state_descending;
  }
}

/* --------------------------------------------------------------- */

/**
 * Lift acts.
 *
 * @param  actor  The lift actor.
 */
void fn_level_actor_function_lift_act(fn_level_actor_t * actor)
{
  fn_level_actor_lift_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_level_t * level = actor->level;

  if (data->state == fn_level_actor_lift_state_ascending ||
      (data->state == fn_level_actor_lift_state_idle &&
       actor->position.h > FN_TILE_HEIGHT))
  {
    /* check if hero leaves elevator. */
    SDL_Rect * heropos = fn_hero_get_position(hero);
    if (!fn_collision_touch_rect_rect(heropos,
          &(actor->position)) ||
        actor->position.x != heropos->x) {
      data->state = fn_level_actor_lift_state_descending;
    }
  }

  switch(data->state)
  {
    case fn_level_actor_lift_state_ascending:
      if (fn_level_is_solid(level,
            actor->position.x/FN_TILE_WIDTH,
            actor->position.y/FN_TILE_HEIGHT-3)) {
        data->state = fn_level_actor_lift_state_idle;
      } else {
        Sint8 offset = fn_hero_push_vertically(
            hero, level, -FN_TILE_HEIGHT);
        if (-offset < FN_TILE_HEIGHT) {
          offset = fn_hero_push_vertically(hero, level, -offset);
          data->state = fn_level_actor_lift_state_idle;
        } else {
          actor->position.h -= offset;
          actor->position.y += offset;

          fn_level_set_solid(level,
              actor->position.x/FN_TILE_WIDTH,
              actor->position.y/FN_TILE_HEIGHT,
              1);
        }

      }
      break;
    case fn_level_actor_lift_state_descending:
      {
        int i = 0;
        for (i = 0; i < 2; i++) {
          if (actor->position.h > FN_TILE_HEIGHT) {
            fn_level_set_solid(level,
                actor->position.x/FN_TILE_WIDTH,
                actor->position.y/FN_TILE_HEIGHT,
                0);
            actor->position.y += FN_TILE_HEIGHT;
            actor->position.h -= FN_TILE_HEIGHT;
          } else {
            data->state = fn_level_actor_lift_state_idle;
          }
        }
      }
      break;
    case fn_level_actor_lift_state_idle:
      /* nothing to do, we stay where we are */
      break;
    default:
      /* we are in an invalid state. */
      printf(__FILE__ ":%d: warning: lift "
          "is in invalid state.\n",
          __LINE__);
      break;
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit the lift.
 *
 * @param  actor  The lift actor.
 */
void fn_level_actor_function_lift_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = NULL;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  int i = 0;
  tile = fn_tilecache_get_tile(tc, SOLID_START + 23);
  for (i = 0;
      i < actor->position.h - FN_TILE_HEIGHT;
      i += FN_HALFTILE_HEIGHT) {
    destrect.y += FN_HALFTILE_HEIGHT * pixelsize;
    fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
  }

  tile = fn_tilecache_get_tile(tc,
      OBJ_ELEVATOR);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The acme stone.
 */
typedef struct fn_level_actor_acme_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The counter for the state.
   */
  Uint8 counter;
  /**
   * A flag indicating if the hero is being touched.
   */
  Uint8 touching_hero;
} fn_level_actor_acme_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_acme_create(fn_level_actor_t * actor)
{
  fn_level_actor_acme_data_t * data = malloc(
      sizeof(fn_level_actor_acme_data_t));
  actor->data = data;
  data->tile = OBJ_FALLINGBLOCK;
  data->counter = 0;
  data->touching_hero = 0;
  actor->position.w = FN_TILE_WIDTH * 2;
  actor->position.h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 1;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_acme_free(fn_level_actor_t * actor)
{
  fn_level_actor_acme_data_t * data = actor->data;

  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);

  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_acme_act(fn_level_actor_t * actor)
{
  fn_level_actor_acme_data_t * data = actor->data;

  fn_hero_t * hero = fn_level_get_hero(actor->level);

  switch(data->counter) {
    case 0:
      {
        Uint16 xl = actor->position.x;
        Uint16 xr = xl + actor->position.w;
        Uint16 y = actor->position.y;
        Uint32 hxl = fn_hero_get_x(hero);
        Uint32 hxr = hxl + FN_TILE_WIDTH;
        Uint32 hy = fn_hero_get_y(hero);

        if (y < hy && /* actor higher than hero */
            xl < hxr &&
            xr > hxl) {
          /* check if there are solid parts between hero and acme */
          Uint16 i = 0;
          Uint8 solidbetween = 0;
          for (i = y + FN_TILE_HEIGHT;
              i < hy && !solidbetween;
              i += FN_TILE_HEIGHT) {
            if (fn_level_is_solid(actor->level,
                  xl / FN_TILE_WIDTH, i / FN_TILE_WIDTH) ||
                fn_level_is_solid(actor->level,
                  xl / FN_TILE_WIDTH + 1, i / FN_TILE_WIDTH)) {
              solidbetween = 1;
            }
          }
          if (!solidbetween) {
            data->counter++;
          }
        }
      }
      break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
      actor->position.y++;
      data->counter++;
      break;
    case 2:
    case 4:
    case 6:
    case 8:
    case 10:
      actor->position.y--;
      data->counter++;
      break;
    default:
      if (fn_level_is_solid(actor->level,
            actor->position.x / FN_TILE_WIDTH,
            (actor->position.y / FN_TILE_HEIGHT) + 1))
      {
        fn_level_add_actor(actor->level,
            FN_LEVEL_ACTOR_STEAM,
            actor->position.x + FN_HALFTILE_WIDTH,
            actor->position.y);
        fn_level_add_particle_firework(
            actor->level, actor->position.x, actor->position.y, 4);
        actor->is_alive = 0;
      } else {
        actor->position.y += FN_TILE_HEIGHT;
      }
      break;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_acme_blit(fn_level_actor_t * actor)
{
  fn_level_actor_acme_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  tile = fn_tilecache_get_tile(tc, data->tile+1);
  destrect.x += FN_TILE_WIDTH * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_acme_shot(fn_level_actor_t * actor)
{
  fn_level_actor_acme_data_t * data = actor->data;

  if (data->counter > 0) {
    fn_hero_t * hero = fn_level_get_hero(actor->level);

    fn_hero_add_score(hero, 500);
    fn_level_add_actor(actor->level,
        FN_LEVEL_ACTOR_SCORE_500, actor->position.x, actor->position.y);
    actor->is_alive = 0;
    fn_level_add_particle_firework(
        actor->level, actor->position.x, actor->position.y, 4);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_acme_hero_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_acme_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  if (data->counter > 10 && !data->touching_hero) {
    data->touching_hero = 1;
    fn_hero_increase_hurting_actors(hero, actor);
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef enum fn_level_actor_fire_state_e {
  fn_level_actor_fire_state_off,
  fn_level_actor_fire_state_ignition,
  fn_level_actor_fire_state_burning
} fn_level_actor_fire_state_e;

/* --------------------------------------------------------------- */

/**
 * The burning fire.
 */
typedef struct fn_level_actor_fire_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The direction to which the fire burns.
   */
  fn_horizontal_direction_e direction;
  /**
   * The state of the fire.
   */
  fn_level_actor_fire_state_e state;
  /**
   * Counter for animation.
   */
  Uint8 counter;
  /**
   * Flag indicating if the hero is currently being touched.
   */
  Uint8 touching_hero;
} fn_level_actor_fire_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_fire_create(fn_level_actor_t * actor)
{
  fn_level_actor_fire_data_t * data = malloc(
      sizeof(fn_level_actor_fire_data_t));
  actor->data = data;

  actor->position.w = FN_TILE_WIDTH * 3;
  actor->position.h = FN_TILE_HEIGHT;

  if (actor->type == FN_LEVEL_ACTOR_FIRE_RIGHT) {
    data->tile = OBJ_FIRERIGHT;
    data->direction = fn_horizontal_direction_right;
  } else {
    data->tile = OBJ_FIRELEFT;
    data->direction = fn_horizontal_direction_left;
    actor->position.x -= 2 * FN_TILE_WIDTH;
  }
  data->counter = 0;
  data->state = fn_level_actor_fire_state_off;
  data->touching_hero = 0;
  actor->is_in_foreground = 1;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_fire_free(fn_level_actor_t * actor)
{
  fn_level_actor_fire_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_fire_hero_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_fire_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  data->touching_hero = 1;

  if (data->state == fn_level_actor_fire_state_burning) {
    fn_hero_increase_hurting_actors(hero, actor);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_fire_hero_touch_end(fn_level_actor_t * actor)
{
  fn_level_actor_fire_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  data->touching_hero = 0;

  if (data->state == fn_level_actor_fire_state_burning) {
    fn_hero_decrease_hurting_actors(hero, actor);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_fire_act(fn_level_actor_t * actor)
{
  fn_level_actor_fire_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  switch(data->state)
  {
    case fn_level_actor_fire_state_off:
      if (data->counter == 40) {
        data->counter = 0;
        data->state = fn_level_actor_fire_state_ignition;
      }
      break;
    case fn_level_actor_fire_state_ignition:
      if (data->counter == 20) {
        data->counter = 0;
        data->state = fn_level_actor_fire_state_burning;
        if (data->touching_hero) {
          fn_hero_increase_hurting_actors(hero, actor);
        }
      }
      break;
    case fn_level_actor_fire_state_burning:
      if (data->counter == 20) {
        data->counter = 0;
        data->state = fn_level_actor_fire_state_off;
        if (data->touching_hero) {
          fn_hero_decrease_hurting_actors(hero, actor);
        }
      }
      break;
    default:
      printf(__FILE__ ":%d: warning: fire "
          "is in invalid state.\n",
          __LINE__);
      break;
  }
  data->counter++;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_fire_blit(fn_level_actor_t * actor)
{
  fn_level_actor_fire_data_t * data = actor->data;
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile0 = NULL;
  FnTexture * tile1 = NULL;
  FnTexture * tile2 = NULL;

  switch(data->state)
  {
    case fn_level_actor_fire_state_off:
      break;
    case fn_level_actor_fire_state_ignition:
      if (data->counter % 2) {
        if (data->direction == fn_horizontal_direction_left) {
          tile2 = fn_tilecache_get_tile(tc,
              data->tile);
        } else {
          tile0 = fn_tilecache_get_tile(tc,
              data->tile);
        }
      }
      break;
    case fn_level_actor_fire_state_burning:
      tile1 = fn_tilecache_get_tile(tc,
          data->tile + 1 + (data->counter % 2));
      if (data->direction == fn_horizontal_direction_left) {
        tile2 = tile1;
        tile0 = fn_tilecache_get_tile(tc, data->tile + 3 +
            (data->counter % 2));
      } else {
        tile0 = tile1;
        tile2 = fn_tilecache_get_tile(tc, data->tile + 3 +
            (data->counter % 2));
      }
      break;
    default:
      printf(__FILE__ ":%d: warning: fire "
          "is in invalid state.\n",
          __LINE__);
      break;
  }
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  if (tile0 != NULL) {
    fn_texture_blit_to_sdl_surface(tile0, NULL, target, &destrect);
  }
  destrect.x += FN_TILE_WIDTH * pixelsize;
  if (tile1 != NULL) {
    fn_texture_blit_to_sdl_surface(tile1, NULL, target, &destrect);
  }
  destrect.x += FN_TILE_WIDTH * pixelsize;
  if (tile2 != NULL) {
    fn_texture_blit_to_sdl_surface(tile2, NULL, target, &destrect);
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The rotating mill.
 */
typedef struct fn_level_actor_mill_data_t {
  /**
   * The tile number which is to be blitted to the level.
   */
  Uint16 tile;
  /**
   * The animation counter.
   */
  Uint8 current_frame;
  /**
   * The number of frames.
   */
  Uint8 num_frames;
  /**
   * The number of lives that the mill still has.
   */
  Uint8 lives;
} fn_level_actor_mill_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_mill_create(fn_level_actor_t * actor)
{
  fn_level_actor_mill_data_t * data = malloc(
      sizeof(fn_level_actor_mill_data_t));
  actor->data = data;
  actor->is_in_foreground = 0;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  data->tile = OBJ_ROTATECYLINDER;
  data->current_frame = 0;
  data->num_frames = 5;
  data->lives = 10;

  while (!fn_level_is_solid(actor->level,
        actor->position.x / FN_TILE_WIDTH,
        actor->position.y / FN_TILE_HEIGHT - 1)) {
    actor->position.y -= FN_TILE_HEIGHT;
    actor->position.h += FN_TILE_HEIGHT;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_mill_free(fn_level_actor_t * actor)
{
  fn_level_actor_mill_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_mill_hero_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_mill_data_t * data = actor->data;
  if (data->lives > 0) {
    /* TODO check if this is okay or if we need to go beyond 0 */
    fn_hero_set_health(fn_level_get_hero(actor->level), 0);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_mill_act(fn_level_actor_t * actor)
{
  fn_level_actor_mill_data_t * data = actor->data;
  if (data->lives > 0) {
    fn_level_actor_mill_data_t * data = actor->data;
    data->current_frame++;
    data->current_frame %= data->num_frames;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_mill_blit(fn_level_actor_t * actor)
{
  fn_level_actor_mill_data_t * data = actor->data;

  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = FN_TILE_WIDTH * pixelsize;
  destrect.h = FN_TILE_HEIGHT * pixelsize;

  int i = 0;
  for (i = 0; i < (actor->position.h / FN_TILE_HEIGHT); i++) {
    fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
    destrect.y += FN_TILE_HEIGHT * pixelsize;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_mill_shot(fn_level_actor_t * actor)
{
  fn_level_actor_mill_data_t * data = actor->data;
  
  data->lives--;
  if (data->lives > 0) {
    fn_level_add_particle_firework(
        actor->level,
        actor->position.x + actor->position.w / 2,
        actor->position.y + actor->position.h / 2,
        4);
  } else {
    /* TODO add removal animation (destroyed body) */
    actor->is_alive = 0;
    fn_hero_add_score(fn_level_get_hero(actor->level), 20000);
    fn_level_add_particle_firework(
        actor->level,
        actor->position.x + actor->position.w / 2,
        actor->position.y + actor->position.h / 2,
        20);
    fn_level_add_actor(actor->level,
        FN_LEVEL_ACTOR_SCORE_10000,
        actor->position.x,
        actor->position.y + actor->position.h / 2 - FN_TILE_HEIGHT);
    fn_level_add_actor(actor->level,
        FN_LEVEL_ACTOR_SCORE_10000,
        actor->position.x,
        actor->position.y + actor->position.h / 2);
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The accesscard slot.
 */
typedef struct fn_level_actor_acces_card_slot_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The number of the current frame.
   */
  Uint8 current_frame;
  /**
   * The number of frames.
   */
  Uint8 num_frames;
} fn_level_actor_access_card_slot_data_t;

/* --------------------------------------------------------------- */

/**
 * Create an accesscard slot.
 *
 * @param  actor  The accesscard slot actor.
 */
void fn_level_actor_function_accesscard_slot_create(fn_level_actor_t * actor)
{
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  fn_level_actor_access_card_slot_data_t * data = malloc(
      sizeof(fn_level_actor_access_card_slot_data_t));
  data->tile = OBJ_ACCESS_CARD_SLOT;
  data->current_frame = 0;
  data->num_frames = 8;
  actor->data = data;
  actor->is_in_foreground = 0;
}

/* --------------------------------------------------------------- */

/**
 * Delete an accesscard slot.
 *
 * @param  actor  The accesscard slot actor.
 */
void fn_level_actor_function_accesscard_slot_free(fn_level_actor_t * actor)
{
  fn_level_actor_access_card_slot_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Interact with an accesscard slot.
 *
 * @param  actor  The accesscard slot actor.
 */
void fn_level_actor_function_accesscard_slot_interact_start(fn_level_actor_t * actor)
{
  fn_level_actor_access_card_slot_data_t * data = actor->data;
  fn_level_t * level = actor->level;
  fn_hero_t * hero = fn_level_get_hero(level);
  Uint8 inventory = fn_hero_get_inventory(hero);
  fn_environment_t * env = fn_level_get_environment(level);

  if (inventory & FN_INVENTORY_ACCESS_CARD) {
    fn_list_t * iter = NULL;
    for (iter = fn_list_first(actor->level->actors);
        iter != NULL;
        iter = fn_list_next(iter)) {
      fn_level_actor_t * dooractor = (fn_level_actor_t *)iter->data;

      if (dooractor->type == FN_LEVEL_ACTOR_ACCESS_CARD_DOOR) {
        dooractor->is_alive = 0;
        int x = dooractor->position.x / FN_TILE_WIDTH;
        int y = dooractor->position.y / FN_TILE_HEIGHT;
        fn_level_set_solid(level, x, y, 0);
      }
    }
    data->current_frame = 0;
    data->num_frames = 1;
    data->tile = OBJ_ACCESS_CARD_SLOT + 8;
    inventory &= ~FN_INVENTORY_ACCESS_CARD;
    fn_hero_set_inventory(hero, inventory);
  } else {
    fn_infobox_show(env,
        "You don't have the access card\n");
  }
}

/* --------------------------------------------------------------- */

/**
 * Let the accesscard slot act.
 *
 * @param  actor  The accesscard slot actor.
 */
void fn_level_actor_function_accesscard_slot_act(fn_level_actor_t * actor)
{
  fn_level_actor_access_card_slot_data_t * data = actor->data;
  data->current_frame++;
  data->current_frame %= data->num_frames;
}

/* --------------------------------------------------------------- */

/**
 * Blit the accesscard slot.
 *
 * @param  actor  The accesscard slot actor.
 */
void fn_level_actor_function_accesscard_slot_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_level_actor_access_card_slot_data_t * data = actor->data;
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The states in which the golve slot can be.
 */
typedef enum fn_level_actor_glove_slot_state_e {
  fn_level_actor_glove_slot_state_idle,
  fn_level_actor_glove_slot_state_expanding,
  fn_level_actor_glove_slot_state_shooting,
  fn_level_actor_glove_slot_state_expanded
} fn_level_actor_glove_slot_state_e;

/* --------------------------------------------------------------- */

/**
 * The glove slot.
 */
typedef struct fn_level_actor_glove_slot_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The number of the current frame.
   */
  Uint8 current_frame;
  /**
   * The number of frames.
   */
  Uint8 num_frames;
  /**
   * The state of the slot.
   */
  fn_level_actor_glove_slot_state_e state;
  /**
   * The countdown for state shooting.
   */
  Uint8 countdown;
} fn_level_actor_glove_slot_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_glove_slot_create(fn_level_actor_t * actor)
{
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  fn_level_actor_glove_slot_data_t * data = malloc(
      sizeof(fn_level_actor_glove_slot_data_t));
  data->tile = OBJ_GLOVE_SLOT;
  data->current_frame = 0;
  data->num_frames = 4;
  data->state = fn_level_actor_glove_slot_state_idle;
  data->countdown = 0;
  actor->data = data;
  actor->is_in_foreground = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_glove_slot_free(fn_level_actor_t * actor)
{
  fn_level_actor_glove_slot_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_glove_slot_interact_start(fn_level_actor_t * actor)
{
  fn_level_actor_glove_slot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  switch(data->state)
  {
    case fn_level_actor_glove_slot_state_idle:
      if (fn_hero_get_inventory(hero) & FN_INVENTORY_GLOVE) {
        data->state = fn_level_actor_glove_slot_state_expanding;
      } else {
        data->state = fn_level_actor_glove_slot_state_shooting;
        data->countdown = 20;
      }
      break;
    case fn_level_actor_glove_slot_state_expanding:
      /* nothing to do */
      break;
    case fn_level_actor_glove_slot_state_shooting:
      /* nothing to do */
      break;
    case fn_level_actor_glove_slot_state_expanded:
      /* nothing to do */
      break;
    default:
      /* we got an invalid state. */
      printf(__FILE__ ":%d: warning: glove slot"
          " is in state %d which is invalud.\n",
          __LINE__, data->state);
      break;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_glove_slot_act(fn_level_actor_t * actor)
{
  fn_level_actor_glove_slot_data_t * data = actor->data;


  switch(data->state)
  {
    case fn_level_actor_glove_slot_state_idle:
      data->current_frame++;
      data->current_frame %= data->num_frames;
      break;
    case fn_level_actor_glove_slot_state_expanding:
      data->current_frame++;
      data->current_frame %= data->num_frames;
      {
        fn_list_t * expandfloors =
          fn_level_get_items_of_type(actor->level,
              FN_LEVEL_ACTOR_EXPANDINGFLOOR);
        Uint8 action = 0;
        fn_list_t * iter = NULL;
        for (iter = fn_list_first(expandfloors);
            iter != fn_list_last(expandfloors);
            iter = fn_list_next(iter)) {
          fn_level_actor_t * floor = iter->data;
          if (!fn_level_is_solid(actor->level,
                (floor->position.x + floor->position.w) / FN_TILE_WIDTH,
                (floor->position.y) / FN_TILE_HEIGHT)) {
            fn_level_set_solid(actor->level,
                (floor->position.x + floor->position.w) / FN_TILE_WIDTH,
                (floor->position.y) / FN_TILE_HEIGHT, 1);
            action = 1;
            floor->position.w += FN_TILE_WIDTH;
          }
        }
        fn_list_free(expandfloors); expandfloors = NULL;

        if (!action) {
          data->state = fn_level_actor_glove_slot_state_expanded;
        }
      }
      break;
    case fn_level_actor_glove_slot_state_shooting:
      data->current_frame++;
      data->current_frame %= data->num_frames;

      data->countdown--;
      if (data->countdown % 4 == 0) {
        fn_level_add_actor(actor->level,
            FN_LEVEL_ACTOR_HOSTILESHOT_RIGHT,
            actor->position.x, actor->position.y);
      } else if (data->countdown % 4 == 2) {
        fn_level_add_actor(actor->level,
            FN_LEVEL_ACTOR_HOSTILESHOT_LEFT,
            actor->position.x, actor->position.y);
      }
      if (data->countdown == 0) {
        data->state = fn_level_actor_glove_slot_state_idle;
      }
      break;
    case fn_level_actor_glove_slot_state_expanded:
      /* nothing to do */
      break;
    default:
      /* we got an invalid state. */
      printf(__FILE__ ":%d: warning: glove slot"
          " is in state %d which is invalud.\n",
          __LINE__, data->state);
      break;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_glove_slot_blit(fn_level_actor_t * actor)
{
  fn_level_actor_glove_slot_data_t * data = actor->data;
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  Uint8 adder = (data->current_frame == 0 ? 0 : 1);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + adder);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  destrect.x -= FN_TILE_WIDTH * pixelsize;
  tile = fn_tilecache_get_tile(tc, data->tile + 2);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  destrect.x += 2 * FN_TILE_WIDTH * pixelsize;
  tile = fn_tilecache_get_tile(tc, data->tile + 3);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The item struct.
 * Items are elements in the game which fall to the floor.
 * They are one part high, one part wide and
 * have either a single frame or a fixed number
 * of frames that appear in order and are lined up in a row
 * inside the tilecache.
 */
typedef struct fn_level_actor_item_data_t {
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
} fn_level_actor_item_data_t;

/* --------------------------------------------------------------- */

/**
 * Create an item.
 *
 * @param  actor The item actor.
 */
void fn_level_actor_function_item_create(fn_level_actor_t * actor)
{
  fn_level_actor_item_data_t * data = malloc(
      sizeof(fn_level_actor_item_data_t));

  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 0;
  switch(actor->type) {
    case FN_LEVEL_ACTOR_BOX_RED_SODA:
    case FN_LEVEL_ACTOR_BOX_RED_CHICKEN:
      data->tile = OBJ_BOX_RED;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_BOX_BLUE_FOOTBALL:
    case FN_LEVEL_ACTOR_BOX_BLUE_JOYSTICK:
    case FN_LEVEL_ACTOR_BOX_BLUE_DISK:
    case FN_LEVEL_ACTOR_BOX_BLUE_BALLOON:
    case FN_LEVEL_ACTOR_BOX_BLUE_FLAG:
    case FN_LEVEL_ACTOR_BOX_BLUE_RADIO:
      data->tile = OBJ_BOX_BLUE;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_EMPTY:
    case FN_LEVEL_ACTOR_BOX_GREY_BOOTS:
    case FN_LEVEL_ACTOR_BOX_GREY_CLAMPS:
    case FN_LEVEL_ACTOR_BOX_GREY_GUN:
    case FN_LEVEL_ACTOR_BOX_GREY_BOMB:
    case FN_LEVEL_ACTOR_BOX_GREY_GLOVE:
    case FN_LEVEL_ACTOR_BOX_GREY_FULL_LIFE:
    case FN_LEVEL_ACTOR_BOX_GREY_ACCESS_CARD:
    case FN_LEVEL_ACTOR_BOX_GREY_LETTER_D:
    case FN_LEVEL_ACTOR_BOX_GREY_LETTER_U:
    case FN_LEVEL_ACTOR_BOX_GREY_LETTER_K:
    case FN_LEVEL_ACTOR_BOX_GREY_LETTER_E:
      data->tile = OBJ_BOX_GREY;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_JOYSTICK:
      data->tile = OBJ_JOYSTICK;
      data->current_frame = 0;
      data->num_frames  = 1;
      break;
    case FN_LEVEL_ACTOR_FOOTBALL:
      data->tile = OBJ_FOOTBALL;
      data->current_frame = 0;
      data->num_frames  = 1;
      break;
    case FN_LEVEL_ACTOR_FLAG:
      data->tile = OBJ_FLAG;
      data->current_frame = 0;
      data->num_frames  = 3;
      break;
    case FN_LEVEL_ACTOR_DISK:
      data->tile = OBJ_DISK;
      data->current_frame = 0;
      data->num_frames  = 1;
      break;
    case FN_LEVEL_ACTOR_RADIO:
      data->tile = OBJ_RADIO;
      data->current_frame = 0;
      data->num_frames = 3;
      break;
    case FN_LEVEL_ACTOR_SODA:
      data->tile = ANIM_SODA;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_LEVEL_ACTOR_BOOTS:
      data->tile = OBJ_BOOT;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_GUN:
      data->tile = OBJ_GUN;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_FULL_LIFE:
      data->tile = OBJ_NUCLEARMOLECULE;
      data->current_frame = 0;
      data->num_frames = 8;
      break;
    case FN_LEVEL_ACTOR_CHICKEN_SINGLE:
      data->tile = OBJ_CHICKEN_SINGLE;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_CHICKEN_DOUBLE:
      data->tile = OBJ_CHICKEN_DOUBLE;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_LETTER_D:
      data->tile = OBJ_LETTER_D;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_LETTER_U:
      data->tile = OBJ_LETTER_U;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_LETTER_K:
      data->tile = OBJ_LETTER_K;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_LETTER_E:
      data->tile = OBJ_LETTER_E;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_ACCESS_CARD:
      data->tile = OBJ_ACCESS_CARD;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_GLOVE:
      data->tile = OBJ_ROBOHAND;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_LEVEL_ACTOR_CLAMPS:
      data->tile = OBJ_CLAMP;
      data->current_frame = 0;
      data->num_frames = 1;
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
void fn_level_actor_function_item_free(fn_level_actor_t * actor)
{
  fn_level_actor_item_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Hero starts to touch item.
 *
 * @param  actor  The item actor.
 */
void fn_level_actor_function_item_touch_start(fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_level_actor_item_data_t * data = (fn_level_actor_item_data_t *)actor->data;
  Uint8 inventory = fn_hero_get_inventory(hero);
  Uint8 health = fn_hero_get_health(hero);
  Uint8 firepower = fn_hero_get_firepower(hero);
  switch(actor->type) {
    case FN_LEVEL_ACTOR_LETTER_D:
      fn_hero_set_fetched_letter(hero, 'D');
      actor->is_alive = 0;
      fn_hero_add_score(hero, 500);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_500, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_LETTER_U:
      if (fn_hero_get_fetched_letter(hero) == 'D') {
        fn_hero_set_fetched_letter(hero, 'U');
      } else {
        fn_hero_set_fetched_letter(hero, 0);
      }
      actor->is_alive = 0;
      fn_hero_add_score(hero, 500);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_500, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_LETTER_K:
      if (fn_hero_get_fetched_letter(hero) == 'U') {
        fn_hero_set_fetched_letter(hero, 'K');
      } else {
        fn_hero_set_fetched_letter(hero, 0);
      }
      actor->is_alive = 0;
      fn_hero_add_score(hero, 500);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_500, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_LETTER_E:
      if (fn_hero_get_fetched_letter(hero) == 'K') {
      fn_hero_add_score(hero, 10000);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_10000, actor->position.x, actor->position.y);
      } else {
      fn_hero_add_score(hero, 500);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_500, actor->position.x, actor->position.y);
      }
      actor->is_alive = 0;
      break;
    case FN_LEVEL_ACTOR_FULL_LIFE:
      health = 8;
      fn_hero_set_health(hero, health);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_1000, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_GUN:
      firepower++;
      fn_hero_set_firepower(hero, firepower);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_1000, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_ACCESS_CARD:
      inventory |= FN_INVENTORY_ACCESS_CARD;
      fn_hero_set_inventory(hero, inventory);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_1000, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_GLOVE:
      inventory |= FN_INVENTORY_GLOVE;
      fn_hero_set_inventory(hero, inventory);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_1000, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_BOOTS:
      inventory |= FN_INVENTORY_BOOT;
      fn_hero_set_inventory(hero, inventory);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_1000, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_CLAMPS:
      inventory |= FN_INVENTORY_CLAMP;
      fn_hero_set_inventory(hero, inventory);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_1000, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_FOOTBALL:
      fn_hero_add_score(hero, 100);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_100, actor->position.x, actor->position.y);
      actor->is_alive = 0;
      break;
    case FN_LEVEL_ACTOR_DISK:
      fn_hero_add_score(hero, 5000);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_5000, actor->position.x, actor->position.y);
      actor->is_alive = 0;
      break;
    case FN_LEVEL_ACTOR_JOYSTICK:
      fn_hero_add_score(hero, 2000);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_2000, actor->position.x, actor->position.y);
      actor->is_alive = 0;
      break;
    case FN_LEVEL_ACTOR_RADIO:
    case FN_LEVEL_ACTOR_FLAG:
      switch(data->current_frame) {
        case 0:
          fn_hero_add_score(hero, 100);
          fn_level_add_actor(actor->level,
              FN_LEVEL_ACTOR_SCORE_100, actor->position.x, actor->position.y);
          break;
        case 1:
          fn_hero_add_score(hero, 2000);
          fn_level_add_actor(actor->level,
              FN_LEVEL_ACTOR_SCORE_2000,
              actor->position.x, actor->position.y);
          break;
        case 2:
          fn_hero_add_score(hero, 5000);
          fn_level_add_actor(actor->level,
              FN_LEVEL_ACTOR_SCORE_5000, actor->position.x, actor->position.y);
          break;
      }
      actor->is_alive = 0;
      break;
    case FN_LEVEL_ACTOR_SODA:
      fn_hero_improve_health(hero, 1);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 200);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_200, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_CHICKEN_SINGLE:
      fn_hero_improve_health(hero, 1);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 100);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_100, actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_CHICKEN_DOUBLE:
      fn_hero_improve_health(hero, 2);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 200);
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_SCORE_200, actor->position.x, actor->position.y);
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
void fn_level_actor_function_item_touch_end(fn_level_actor_t * actor) {
  /* Nothing to do here */
}

/* --------------------------------------------------------------- */

/**
 * Action for item.
 *
 * @param  actor  The item actor.
 */
void fn_level_actor_function_item_act(fn_level_actor_t * actor)
{
  fn_level_actor_item_data_t * data = actor->data;
  data->current_frame++;
  data->current_frame %= data->num_frames;
  if (!fn_level_is_solid(actor->level,
        (actor->position.x) / FN_TILE_WIDTH,
        (actor->position.y) / FN_TILE_HEIGHT + 1)) {
    actor->position.y += FN_HALFTILE_HEIGHT;
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit the item.
 *
 * @param  actor  The item actor.
 */
void fn_level_actor_function_item_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_level_actor_item_data_t * data = actor->data;
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

/**
 * An item gets shot.
 *
 * @param  actor  The item actor.
 */
void fn_level_actor_function_item_shot(fn_level_actor_t * actor)
{
  fn_level_t * lv = actor->level;
  switch(actor->type) {
    case FN_LEVEL_ACTOR_BOX_BLUE_FOOTBALL:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_FOOTBALL,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_BLUE_JOYSTICK:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_JOYSTICK,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_BLUE_DISK:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_DISK,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_BLUE_BALLOON:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_BALLOON,
          actor->position.x, actor->position.y - FN_TILE_HEIGHT);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_BLUE_FLAG:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_FLAG,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_BLUE_RADIO:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_RADIO,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_RED_SODA:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_SODA,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_RED_CHICKEN:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_CHICKEN_SINGLE,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_EMPTY:
      actor->is_alive = 0;
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_BOOTS:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_BOOTS,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_CLAMPS:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_CLAMPS,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_GUN:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_GUN,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_BOMB:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_BOMB,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_GLOVE:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_GLOVE,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_FULL_LIFE:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_FULL_LIFE,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_ACCESS_CARD:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_ACCESS_CARD,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_LETTER_D:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_LETTER_D,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_LETTER_U:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_LETTER_U,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_LETTER_K:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_LETTER_K,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_BOX_GREY_LETTER_E:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_LETTER_E,
          actor->position.x, actor->position.y);
      fn_level_add_particle_firework(
          actor->level, actor->position.x, actor->position.y, 4);
      break;
    case FN_LEVEL_ACTOR_CHICKEN_SINGLE:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_CHICKEN_DOUBLE,
          actor->position.x, actor->position.y);
      break;
    case FN_LEVEL_ACTOR_SODA:
      actor->is_alive = 0;
      fn_level_add_actor(lv, FN_LEVEL_ACTOR_SODA_FLYING,
          actor->position.x, actor->position.y);
      break;
    default:
      break;
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

void fn_level_actor_function_soda_flying_create(fn_level_actor_t * actor)
{
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_soda_flying_free(fn_level_actor_t * actor)
{
  /* nothing to do here */
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_soda_flying_touch_start(fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_add_score(hero, 1000);
  fn_level_add_actor(actor->level,
      FN_LEVEL_ACTOR_SCORE_1000, actor->position.x, actor->position.y);
  actor->is_alive = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_soda_flying_act(fn_level_actor_t * actor)
{
  actor->position.y -= FN_HALFTILE_HEIGHT;
  if (fn_level_is_solid(actor->level,
        (actor->position.x) / FN_TILE_WIDTH,
        (actor->position.y) / FN_TILE_HEIGHT)) {
    fn_level_add_actor(actor->level,
        FN_LEVEL_ACTOR_EXPLOSION, actor->position.x, actor->position.y);
    actor->is_alive = 0;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_soda_flying_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc, ANIM_SODAFLY +
      (actor->position.y/FN_HALFTILE_HEIGHT) % 4);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}


/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The balloon struct.
 */
typedef struct fn_level_actor_balloon_data_t {
  /**
   * A flag indicating if the balloon was destroyed.
   */
  Uint8 destroyed;
  /**
   * The current frame number for the cord animation.
   */
  Uint8 current_frame;
} fn_level_actor_balloon_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_balloon_create(fn_level_actor_t * actor)
{
  fn_level_actor_balloon_data_t * data =
    malloc(sizeof(fn_level_actor_balloon_data_t));
  actor->data = data;
  data->destroyed = 0;
  data->current_frame = 0;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT * 2;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_balloon_free(fn_level_actor_t * actor)
{
  fn_level_actor_balloon_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_balloon_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_balloon_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (!data->destroyed) {
    actor->is_alive = 0;
    fn_hero_add_score(hero, 10000);
    fn_level_add_actor(actor->level,
        FN_LEVEL_ACTOR_SCORE_10000, actor->position.x, actor->position.y);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_balloon_act(fn_level_actor_t * actor)
{
  fn_level_actor_balloon_data_t * data = actor->data;
  fn_level_t * level = actor->level;

  data->current_frame++;
  data->current_frame %= 9;
  if (data->destroyed) {
    actor->is_alive = 0;
  } else {
    actor->position.y--;
    if (
        /* balloon bumps against wall */
        fn_level_is_solid(level,
          (actor->position.x) / FN_TILE_WIDTH,
          (actor->position.y -1) / FN_TILE_HEIGHT)
       )
    {
      data->destroyed = 1;
      fn_level_add_actor(level,
          FN_LEVEL_ACTOR_STEAM, actor->position.x, actor->position.y);
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_balloon_blit(fn_level_actor_t * actor)
{
  fn_level_actor_balloon_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  if (data->destroyed) {
    tile = fn_tilecache_get_tile(tc, OBJ_BALLOON + 4);
  } else {
    tile = fn_tilecache_get_tile(tc, OBJ_BALLOON);
  }
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  destrect.y += FN_TILE_HEIGHT * pixelsize;

  tile = fn_tilecache_get_tile(tc,
      OBJ_BALLOON + 1 + data->current_frame / 3);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_balloon_shot(fn_level_actor_t * actor)
{
  fn_level_actor_balloon_data_t * data = actor->data;
  fn_level_t * level = actor->level;
  data->destroyed = 1;
  fn_level_add_actor(level,
      FN_LEVEL_ACTOR_STEAM, actor->position.x, actor->position.y);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Create a teleporter.
 *
 * @param  actor  The teleporter actor.
 */
void fn_level_actor_function_teleporter_create(fn_level_actor_t * actor)
{
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 1;
}

/* --------------------------------------------------------------- */

/**
 * Interact with a teleporter.
 *
 * @param  actor  The teleporter actor.
 */
void fn_level_actor_function_teleporter_interact_start(fn_level_actor_t * actor)
{
  fn_level_actor_type_e othertype;
  if (actor->type == FN_LEVEL_ACTOR_TELEPORTER1) {
    othertype = FN_LEVEL_ACTOR_TELEPORTER2;
  } else {
    othertype = FN_LEVEL_ACTOR_TELEPORTER1;
  }
  fn_level_t * level = actor->level;

  fn_list_t * iter = NULL;
  for (iter = fn_list_first(level->actors);
      iter != NULL;
      iter = fn_list_next(iter)) {
    fn_level_actor_t * otheractor = (fn_level_actor_t *)iter->data;
    if (otheractor->type == othertype) {
      fn_hero_t * hero = fn_level_get_hero(actor->level);
      fn_hero_replace(hero,
          otheractor->position.x,
          otheractor->position.y - FN_TILE_HEIGHT);
      return;
    }
  }
  return;
}

/* --------------------------------------------------------------- */

/**
 * The teleporter acts.
 *
 * @param  actor  The teleporter actor.
 */
void fn_level_actor_function_teleporter_act(fn_level_actor_t * actor)
{
}

/* --------------------------------------------------------------- */

/**
 * Blit a teleporter.
 *
 * @param  actor  The teleporter actor.
 */
void fn_level_actor_function_teleporter_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  int i = 0;
  for (i = 0; i < 3; i++) {
    int j = 0;
    for (j = 0; j < 3; j++) {
      destrect.x = (actor->position.x - (1 - j) * FN_TILE_WIDTH) * pixelsize;
      destrect.y = (actor->position.y - (2 - i) * FN_TILE_HEIGHT) * pixelsize;
      tile = fn_tilecache_get_tile(tc,
          ANIM_TELEPORTER1 + i * 3 + j
          );
      fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
    }
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Singleanimation data struct.
 */
typedef struct fn_level_actor_singleanimation_data_t {
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
} fn_level_actor_singleanimation_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a singleanimation.
 *
 * @param  actor  The singleanimation actor.
 */
void fn_level_actor_function_singleanimation_create(fn_level_actor_t * actor)
{
  fn_level_actor_singleanimation_data_t * data = malloc(
      sizeof(fn_level_actor_singleanimation_data_t));

  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 1;

  switch(actor->type) {
    case FN_LEVEL_ACTOR_FIRE:
      data->tile = ANIM_BOMBFIRE;
      data->current_frame = 0;
      data->num_frames = 6;
      break;
    case FN_LEVEL_ACTOR_DUSTCLOUD:
      data->tile = OBJ_DUST;
      data->current_frame = 0;
      data->num_frames = 5;
      break;
    case FN_LEVEL_ACTOR_STEAM:
      data->tile = OBJ_STEAM;
      data->current_frame = 0;
      data->num_frames = 5;
      break;
    case FN_LEVEL_ACTOR_ROBOT_DISAPPEARING:
      data->tile = ANIM_ROBOT + 3;
      data->current_frame = 0;
      data->num_frames = 7;
      break;
    default:
      printf(__FILE__ ":%d: warning: singleanimation #%d"
          " added which is not a singleanimation\n",
          __LINE__, actor->type);
      break;
  }
}

/* --------------------------------------------------------------- */

/**
 * Delete a singleanimation.
 *
 * @param  actor  The singleanimation actor.
 */
void fn_level_actor_function_singleanimation_free(fn_level_actor_t * actor)
{
  fn_level_actor_singleanimation_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Act a singleanimation.
 *
 * @param  actor  The singleanimation actor.
 */
void fn_level_actor_function_singleanimation_act(fn_level_actor_t * actor)
{
  fn_level_actor_singleanimation_data_t * data = actor->data;

  data->current_frame++;
  if (data->current_frame == data->num_frames) {
    actor->is_alive = 0;
    if (actor->type == FN_LEVEL_ACTOR_ROBOT_DISAPPEARING) {
      fn_level_add_actor(actor->level,
          FN_LEVEL_ACTOR_EXPLOSION, actor->position.x, actor->position.y);
    }
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit an singleanimation.
 *
 * @param  actor  The singleanimation actor.
 */
void fn_level_actor_function_singleanimation_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_level_actor_singleanimation_data_t * data = actor->data;
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The particle information data.
 */
typedef struct fn_level_actor_particle_data_t {
  /**
   * A countdown for the living time of the particle.
   */
  Uint8 countdown;
  /**
   * The tile to blit.
   */
  Uint16 tile;
  /**
   * The horizontal speed of the particle.
   */
  int hspeed;
  /**
   * The vertical initial speed of the particle.
   */
  int vspeed;
} fn_level_actor_particle_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_particle_create(fn_level_actor_t * actor)
{
  fn_level_actor_particle_data_t * data = malloc(
      sizeof(fn_level_actor_particle_data_t));
  actor->data = data;
  data->countdown = 20;
  actor->is_in_foreground = 1;

  Uint16 hrand = rand();
  Uint16 vrand = rand();

  int const hrand_max = 15;
  int const vrand_max = 15;

  hrand %= hrand_max;
  vrand %= vrand_max;
  data->hspeed = hrand - hrand_max / 2;
  data->vspeed = vrand - vrand_max / 2;

  switch(actor->type) {
    case FN_LEVEL_ACTOR_PARTICLE_PINK:
      data->tile = OBJ_SPARK_PINK;
      break;
    case FN_LEVEL_ACTOR_PARTICLE_BLUE:
      data->tile = OBJ_SPARK_BLUE;
      break;
    case FN_LEVEL_ACTOR_PARTICLE_WHITE:
      data->tile = OBJ_SPARK_WHITE;
      break;
    case FN_LEVEL_ACTOR_PARTICLE_GREEN:
      data->tile = OBJ_SPARK_GREEN;
      break;
    default:
      printf(__FILE__ ":%d: warning: particle #%d"
          " added which is not a particle\n",
          __LINE__, actor->type);
      break;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_particle_free(fn_level_actor_t * actor)
{
  fn_level_actor_particle_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_particle_act(fn_level_actor_t * actor)
{
  fn_level_actor_particle_data_t * data = actor->data;
  if (data->countdown) {
    data->countdown--;
    actor->position.x += data->hspeed * 2;
    actor->position.y += data->vspeed * 2;
    data->vspeed++;
  } else {
    actor->is_alive = 0;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_particle_blit(fn_level_actor_t * actor)
{
  fn_level_actor_particle_data_t * data = actor->data;

  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc, data->tile);
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef enum fn_level_actor_rocket_state_e {
  fn_level_actor_rocket_state_idle,
  fn_level_actor_rocket_state_flying
} fn_level_actor_rocket_state_e;

/* --------------------------------------------------------------- */

/**
 * The rocket.
 */
typedef struct fn_level_actor_rocket_data_t {
  /**
   * The state.
   */
  fn_level_actor_rocket_state_e state;
} fn_level_actor_rocket_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a rocket.
 *
 * @param  actor  The rocket actor.
 */
void fn_level_actor_function_rocket_create(fn_level_actor_t * actor)
{
  fn_level_actor_rocket_data_t * data = malloc(
      sizeof(fn_level_actor_rocket_data_t));
  actor->data = data;
  data->state = fn_level_actor_rocket_state_idle;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_rocket_free(fn_level_actor_t * actor)
{
  fn_level_actor_rocket_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_rocket_act(fn_level_actor_t * actor)
{
  fn_level_actor_rocket_data_t * data = actor->data;
  if (data->state == fn_level_actor_rocket_state_idle) {
    /* idle, so do nothing */
    return;
  }
  if (data->state == fn_level_actor_rocket_state_flying) {
    actor->position.y -= FN_HALFTILE_HEIGHT;
    if (fn_level_solid_collides(actor->level, &(actor->position))) {
      Uint16 tile_x = actor->position.x / FN_TILE_WIDTH;
      Uint16 tile_y = actor->position.y / FN_TILE_HEIGHT;
      fn_level_set_solid(actor->level, tile_x, tile_y, 0);
      fn_level_set_tile(actor->level, tile_x, tile_y,
          fn_level_get_tile(actor->level, tile_x, tile_y - 1));
      actor->is_alive = 0;
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_rocket_blit(fn_level_actor_t * actor)
{
  fn_level_actor_rocket_data_t * data = actor->data;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc, OBJ_ROCKET);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = (actor->position.y - FN_TILE_HEIGHT * 3) * pixelsize;
  destrect.w = FN_TILE_WIDTH * pixelsize;
  destrect.h = FN_TILE_HEIGHT * pixelsize;

  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  tile = fn_tilecache_get_tile(tc, OBJ_ROCKET + 1);
  destrect.y += FN_TILE_HEIGHT * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
  destrect.y += FN_TILE_HEIGHT * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
  destrect.y += FN_TILE_HEIGHT * pixelsize;

  tile = fn_tilecache_get_tile(tc, OBJ_ROCKET + 2);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  tile = fn_tilecache_get_tile(tc, OBJ_ROCKET + 3);
  destrect.x -= FN_TILE_WIDTH * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
  destrect.x += FN_TILE_WIDTH * 2 * pixelsize;
  tile = fn_tilecache_get_tile(tc, OBJ_ROCKET + 4);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  if (data->state == fn_level_actor_rocket_state_flying) {
    destrect.x -= FN_TILE_WIDTH * pixelsize;
    destrect.y += FN_TILE_HEIGHT * pixelsize;
    tile = fn_tilecache_get_tile(tc, OBJ_ROCKET + 6);
    fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_rocket_shot(fn_level_actor_t * actor)
{
  fn_level_actor_rocket_data_t * data = actor->data;
  data->state = fn_level_actor_rocket_state_flying;
  /* TODO create animation */
  Uint16 tile_x = actor->position.x / FN_TILE_WIDTH;
  Uint16 tile_y = (actor->position.y + actor->position.h) /
    FN_TILE_HEIGHT;
  fn_level_set_solid(actor->level, tile_x, tile_y, 0);
  fn_level_set_tile(actor->level, tile_x, tile_y,
      fn_level_get_tile(actor->level, tile_x, tile_y + 1));
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef struct fn_level_actor_bomb_data_t {
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
   * The counter for the number of cycles.
   */
  Uint8 counter;
  /**
   * Flag showing if the bomb explodes to the left.
   */
  Uint8 explode_left;
  /**
   * Flag showing if the bomb explodes to the right.
   */
  Uint8 explode_right;
  /**
   * The threshold when the bomb should explode.
   */
  Uint8 explode_threshold;
  /**
   * The number of flames that should be produced by the bomb
   * to each direction.
   */
  Uint8 num_flames;
} fn_level_actor_bomb_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_bomb_create(fn_level_actor_t * actor)
{
  fn_level_actor_bomb_data_t * data = malloc(
      sizeof(fn_level_actor_bomb_data_t));
  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;

  data->tile = ANIM_BOMB;
  data->current_frame = 0;
  data->num_frames = 2;
  data->counter = 0;
  data->explode_left = 1;
  data->explode_right = 1;
  data->explode_threshold = 12;
  data->num_flames = 4;
}

/* --------------------------------------------------------------- */

void fn_level_actor_bomb_free(fn_level_actor_t * actor)
{
  fn_level_actor_bomb_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_bomb_act(fn_level_actor_t * actor)
{
  fn_level_actor_bomb_data_t * data = actor->data;
  data->current_frame++;
  data->current_frame %= data->num_frames;

  data->counter++;

  if (data->counter < data->explode_threshold) {
    /* do nothing here, the counter counts anyway. */
  }
  else if (data->counter < data->explode_threshold + data->num_flames)
  {
    Uint8 distance = data->counter - data->explode_threshold;
    if (data->explode_left) {
      /* explode to the left if possible */
      if (
          /* check if the place for the flame is free */
          !fn_level_is_solid(actor->level,
            (actor->position.x - distance * FN_TILE_WIDTH) / FN_TILE_WIDTH,
            actor->position.y / FN_TILE_HEIGHT) &&
          /* check if there is solid place below */
          fn_level_is_solid(actor->level,
            (actor->position.x - distance * FN_TILE_WIDTH) / FN_TILE_WIDTH,
            (actor->position.y / FN_TILE_HEIGHT) + 1))
      {
        fn_level_add_actor(actor->level,
            FN_LEVEL_ACTOR_BOMBFIRE, actor->position.x - distance * FN_TILE_WIDTH,
            actor->position.y);
      } else {
        data->explode_left = 0;
      }
    }

    if (data->explode_right) {
      /* explode to the right if possible */
      if (
          /* check if the place for the flame is free */
          !fn_level_is_solid(actor->level,
            (actor->position.x + distance * FN_TILE_WIDTH) / FN_TILE_WIDTH,
            actor->position.y / FN_TILE_HEIGHT) &&
          /* check if there is solid place below */
          fn_level_is_solid(actor->level,
            (actor->position.x + distance * FN_TILE_WIDTH) / FN_TILE_WIDTH,
            (actor->position.y / FN_TILE_HEIGHT) + 1))
      {
        fn_level_add_actor(actor->level,
            FN_LEVEL_ACTOR_BOMBFIRE, actor->position.x + distance * FN_TILE_WIDTH,
            actor->position.y);
      } else {
        data->explode_right = 0;
      }
    }

  } else {
    actor->is_alive = 0;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_bomb_blit(fn_level_actor_t * actor)
{
  fn_level_actor_bomb_data_t * data = actor->data;
  if (data->counter < data->explode_threshold) {
    SDL_Surface * target = fn_level_get_surface(actor->level);
    SDL_Rect destrect;
    fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
    FnTexture * tile = fn_tilecache_get_tile(tc,
        data->tile + data->current_frame);
    Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
    destrect.x = actor->position.x * pixelsize;
    destrect.y = actor->position.y * pixelsize;
    destrect.w = actor->position.w * pixelsize;
    destrect.h = actor->position.h * pixelsize;
    fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef struct fn_level_actor_bombfire_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The number of the current frame.
   */
  Uint8 current_frame;
  /**
   * The number of frames total.
   */
  Uint8 num_frames;
  /**
   * Flag indicating if the flame is touching the hero.
   */
  Uint8 touching_hero;
} fn_level_actor_bombfire_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_bombfire_create(fn_level_actor_t * actor)
{
  fn_level_actor_bombfire_data_t * data = malloc(
      sizeof(fn_level_actor_bombfire_data_t));
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  actor->data = data;
  data->tile = ANIM_BOMBFIRE;
  data->current_frame = 0;
  data->num_frames = 6;
  data->touching_hero = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_bombfire_free(fn_level_actor_t * actor)
{
  fn_level_actor_bombfire_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_bombfire_hero_touch_start(fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_level_actor_bombfire_data_t * data = actor->data;
  fn_hero_increase_hurting_actors(hero, actor);
  data->touching_hero = 1;
}

/* --------------------------------------------------------------- */

void fn_level_actor_bombfire_hero_touch_end(fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
  fn_level_actor_bombfire_data_t * data = actor->data;
  data->touching_hero = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_bombfire_act(fn_level_actor_t * actor)
{
  fn_level_actor_bomb_data_t * data = actor->data;
  data->current_frame++;
  if (data->current_frame == data->num_frames) {
    actor->is_alive = 0;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_bombfire_blit(fn_level_actor_t * actor)
{
  fn_level_actor_bombfire_data_t * data = actor->data;
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Explosion data struct.
 */
typedef struct fn_level_actor_explosion_data_t {
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
} fn_level_actor_explosion_data_t;

/* --------------------------------------------------------------- */

/**
 * Create an explosion.
 *
 * @param  actor  The explosion actor.
 */
void fn_level_actor_function_explosion_create(fn_level_actor_t * actor)
{
  fn_level_actor_explosion_data_t * data = malloc(
      sizeof(fn_level_actor_explosion_data_t));

  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 0;

  data->tile = ANIM_EXPLODE;
  data->current_frame = 0;
  data->num_frames = 6;
}

/* --------------------------------------------------------------- */

/**
 * Delete an explosion.
 *
 * @param  actor  The explosion actor.
 */
void fn_level_actor_function_explosion_free(fn_level_actor_t * actor)
{
  fn_level_actor_explosion_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Act an explosion.
 *
 * @param  actor  The explosion actor.
 */
void fn_level_actor_function_explosion_act(fn_level_actor_t * actor)
{
  fn_level_actor_explosion_data_t * data = actor->data;

  data->current_frame++;
  if (data->current_frame == data->num_frames) {
    actor->is_alive = 0;
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit an explosion.
 *
 * @param  actor  The explosion actor.
 */
void fn_level_actor_function_explosion_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_level_actor_explosion_data_t * data = actor->data;
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Create a camera.
 *
 * @param  actor  The camera actor.
 */
void fn_level_actor_function_camera_create(fn_level_actor_t * actor)
{
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 0;
}

/**
 * Blit the camera.
 *
 * @param  actor  The camera actor.
 */
void fn_level_actor_function_camera_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  size_t x = fn_hero_get_x(hero);
  if (x-1 > actor->position.x) {
    tile = fn_tilecache_get_tile(tc,
        ANIM_CAMERA_RIGHT);
  } else if (x+1 < actor->position.x) {
    tile = fn_tilecache_get_tile(tc,
        ANIM_CAMERA_LEFT);
  } else {
    tile = fn_tilecache_get_tile(tc,
        ANIM_CAMERA_CENTER);
  }
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

/**
 * A camera gets shot.
 *
 * @param  actor  The camera actor.
 */
void fn_level_actor_function_camera_shot(fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  actor->is_alive = 0;
  fn_hero_add_score(hero, 100);
  fn_level_add_actor(actor->level,
      FN_LEVEL_ACTOR_SCORE_100, actor->position.x, actor->position.y);
  fn_level_add_actor(actor->level,
      FN_LEVEL_ACTOR_EXPLOSION, actor->position.x, actor->position.y);
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
typedef struct fn_level_actor_score_data_t {
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
} fn_level_actor_score_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a score.
 *
 * @param  actor  The score actor.
 */
void fn_level_actor_function_score_create(fn_level_actor_t * actor)
{
  fn_level_actor_score_data_t * data = malloc(
      sizeof(fn_level_actor_score_data_t));
  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 1;
  data->countdown = 40;

  switch(actor->type) {
    case FN_LEVEL_ACTOR_SCORE_100:
      data->tile = NUMB_100;
      break;
    case FN_LEVEL_ACTOR_SCORE_200:
      data->tile = NUMB_200;
      break;
    case FN_LEVEL_ACTOR_SCORE_500:
      data->tile = NUMB_500;
      break;
    case FN_LEVEL_ACTOR_SCORE_1000:
      data->tile = NUMB_1000;
      break;
    case FN_LEVEL_ACTOR_SCORE_2000:
      data->tile = NUMB_2000;
      break;
    case FN_LEVEL_ACTOR_SCORE_5000:
      data->tile = NUMB_5000;
      break;
    case FN_LEVEL_ACTOR_SCORE_10000:
      data->tile = NUMB_10000;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_1_LEFT:
      data->tile = NUMB_BONUS_1_LEFT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_1_RIGHT:
      data->tile = NUMB_BONUS_1_RIGHT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_2_LEFT:
      data->tile = NUMB_BONUS_2_LEFT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_2_RIGHT:
      data->tile = NUMB_BONUS_2_RIGHT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_3_LEFT:
      data->tile = NUMB_BONUS_3_LEFT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_3_RIGHT:
      data->tile = NUMB_BONUS_3_RIGHT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_4_LEFT:
      data->tile = NUMB_BONUS_4_LEFT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_4_RIGHT:
      data->tile = NUMB_BONUS_4_RIGHT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_5_LEFT:
      data->tile = NUMB_BONUS_5_LEFT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_5_RIGHT:
      data->tile = NUMB_BONUS_5_RIGHT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_6_LEFT:
      data->tile = NUMB_BONUS_6_LEFT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_6_RIGHT:
      data->tile = NUMB_BONUS_6_RIGHT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_7_LEFT:
      data->tile = NUMB_BONUS_7_LEFT;
      break;
    case FN_LEVEL_ACTOR_SCORE_BONUS_7_RIGHT:
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
void fn_level_actor_function_score_free(fn_level_actor_t * actor)
{
  fn_level_actor_score_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Action for score.
 * 
 * @param  actor  The score actor.
 */
void fn_level_actor_function_score_act(fn_level_actor_t * actor)
{
  fn_level_actor_score_data_t * data = actor->data;
  data->countdown--;
  actor->position.y--;
  if (data->countdown == 0 || actor->position.y == 0) {
    actor->is_alive = 0;
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit the score.
 *
 * @param  actor  The score actor.
 */
void fn_level_actor_function_score_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_level_actor_score_data_t * data = actor->data;
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + (data->countdown % 2));
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef struct fn_level_actor_unstablefloor_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The flag showing if the hero has already been standing upon the
   * floor
   */
  Uint8 touched;
  /**
   * The flag showing if the hero is currently touching the floor.
   */
  Uint8 touching;
} fn_level_actor_unstablefloor_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_unstablefloor_create(fn_level_actor_t * actor)
{
  fn_level_actor_unstablefloor_data_t * data = malloc(
      sizeof(fn_level_actor_unstablefloor_data_t));
  actor->data = data;
  data->tile = SOLID_START + 77;
  data->touched = 0;
  data->touching = 0;
  actor->position.w = 0;
  actor->position.h = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_unstablefloor_free(fn_level_actor_t * actor)
{
  fn_level_actor_unstablefloor_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_unstablefloor_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_unstablefloor_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (fn_collision_touch_rect_area(
        fn_hero_get_position(hero),
        actor->position.x, actor->position.y, actor->position.w, actor->position.h))
  {
    if (!data->touched) {
      data->touching = 1;
    } else {
      actor->is_alive = 0;
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_unstablefloor_touch_end(fn_level_actor_t * actor)
{
  fn_level_actor_unstablefloor_data_t * data = actor->data;
  if (data->touching) {
    data->touching = 0;
    data->touched = 1;
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_unstablefloor_act(fn_level_actor_t * actor)
{
  fn_level_actor_unstablefloor_data_t * data = actor->data;
  fn_level_t * level = actor->level;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  Uint8 floorlength = 0;

  /*
   * postponed initialization because when floor is created,
   * the necessary information is not yet loaded from the level.
   */
  if (actor->position.w == 0) {
    while (!fn_level_is_solid(level,
          actor->position.x / FN_TILE_WIDTH + floorlength,
          actor->position.y / FN_TILE_HEIGHT))
    {
      fn_level_set_solid(level,
          actor->position.x / FN_TILE_WIDTH + floorlength,
          actor->position.y / FN_TILE_HEIGHT,
          1);
      floorlength++;
    }
    actor->position.w = floorlength * FN_TILE_WIDTH;
    actor->position.h = FN_TILE_HEIGHT;
  }

  if (fn_collision_touch_rect_area(
        fn_hero_get_position(hero),
        actor->position.x, actor->position.y, actor->position.w, actor->position.h))
  {
    if (data->touched) {
      floorlength = 0;
      while (floorlength < actor->position.w / FN_TILE_WIDTH) {
        fn_level_set_solid(level,
            actor->position.x / FN_TILE_WIDTH + floorlength,
            actor->position.y / FN_TILE_HEIGHT,
            0);
        fn_level_add_actor(actor->level,
            FN_LEVEL_ACTOR_EXPLOSION,
            actor->position.x + floorlength * FN_TILE_WIDTH,
            actor->position.y);
        fn_level_add_particle_firework(
            actor->level,
            actor->position.x + floorlength * FN_TILE_WIDTH,
            actor->position.y, 4);
        floorlength++;
      }
      actor->is_alive = 0;
    } else {
      data->touching = 1;
    }
  } else {
    if (data->touching) {
      data->touching = 0;
      data->touched = 1;
    }
  }
}
/* --------------------------------------------------------------- */

void fn_level_actor_function_unstablefloor_blit(fn_level_actor_t * actor)
{
  fn_level_actor_unstablefloor_data_t * data = actor->data;
  
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = NULL;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  int i = 0;
  for (i = 0; i < (actor->position.w / FN_TILE_WIDTH); i++) {
    tile = fn_tilecache_get_tile(tc,
        data->tile + i % 2);
    fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
    destrect.x += FN_TILE_WIDTH * pixelsize;
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

void fn_level_actor_function_expandingfloor_create(fn_level_actor_t * actor)
{
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_expandingfloor_free(fn_level_actor_t * actor)
{
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_expandingfloor_act(fn_level_actor_t * actor)
{
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_expandingfloor_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc, SOLID_EXPANDINGFLOOR);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  int i = 0;
  for (i = 0; i < (actor->position.w / FN_TILE_WIDTH); i++) {
    fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
    destrect.x += FN_TILE_WIDTH * pixelsize;
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The conveyor belt.
 */
typedef struct fn_level_actor_conveyor_data_t {
  /**
   * The animation counter.
   */
  Uint8 current_frame;
  /**
   * The number of animation frames.
   */
  Uint8 num_frames;
  /**
   * The direction to which the conveyor runs.
   */
  fn_horizontal_direction_e direction;
} fn_level_actor_conveyor_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_conveyor_create(fn_level_actor_t * actor)
{
  fn_level_actor_conveyor_data_t * data = malloc(
      sizeof(fn_level_actor_conveyor_data_t));
  actor->data = data;
  actor->is_in_foreground = 0;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  fn_level_t * level = actor->level;

  data->current_frame = 0;

  data->num_frames = 4;

  switch(actor->type) {
    case FN_LEVEL_ACTOR_CONVEYOR_LEFTMOVING_RIGHTEND:
      data->direction = fn_horizontal_direction_left;
      break;
    case FN_LEVEL_ACTOR_CONVEYOR_RIGHTMOVING_RIGHTEND:
      data->direction = fn_horizontal_direction_right;
      break;
    default: /* error */
      printf(__FILE__ ":%d: warning: conveyor #%d"
          " added which is no conveyor\n",
          __LINE__, actor->type);
      break;
  }

  /* find the beginning of the conveyor belt */
  Uint8 found_begin = 0;
  Uint16 tile = 0;
  while(!found_begin) {
    actor->position.x -= FN_TILE_WIDTH;
    actor->position.w += FN_TILE_WIDTH;
    tile = fn_level_get_tile(level,
        actor->position.x / FN_TILE_WIDTH, actor->position.y / FN_TILE_HEIGHT);
    if (tile == SOLID_CONVEYORBELT_LEFTEND ||
        actor->position.x == 0 ||
        tile == 0) {
      found_begin = 1;
      fn_level_set_tile(level,
          actor->position.x / FN_TILE_WIDTH,
          actor->position.y / FN_TILE_HEIGHT,
          SOLID_BLACK);
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_conveyor_free(fn_level_actor_t * actor)
{
  fn_level_actor_conveyor_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_conveyor_act(fn_level_actor_t * actor)
{
  fn_level_actor_conveyor_data_t * data = actor->data;
  if (data->direction == fn_horizontal_direction_left) {
    if (data->current_frame == 0) {
      data->current_frame = data->num_frames;
    }
    data->current_frame--;
  } else {
    data->current_frame++;
    data->current_frame %= data->num_frames;
  }

  fn_hero_t * hero = fn_level_get_hero(actor->level);
  SDL_Rect * heropos = fn_hero_get_position(hero);

  int direction = (
      data->direction == fn_horizontal_direction_right ?  1 : -1);
  if (
      heropos->x + heropos->w > actor->position.x &&
      heropos->x < actor->position.x + actor->position.w &&
      heropos->y + heropos->h == actor->position.y) {
    fn_hero_push_horizontally(
        hero, actor->level, direction * FN_HALFTILE_WIDTH);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_conveyor_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_level_actor_conveyor_data_t * data = actor->data;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  Uint16 i = 0;

  FnTexture * tile = fn_tilecache_get_tile(tc,
      SOLID_CONVEYORBELT_LEFTEND + data->current_frame);

  for (i = actor->position.x; i < actor->position.x + actor->position.w; i+= FN_TILE_WIDTH) {
    destrect.x = i * pixelsize;
    if (i + FN_TILE_WIDTH == actor->position.x + actor->position.w) {
      /* last element */
      tile = fn_tilecache_get_tile(tc,
          SOLID_CONVEYORBELT_RIGHTEND + data->current_frame);
    }

    fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

    tile = fn_tilecache_get_tile(tc,
        SOLID_CONVEYORBELT_CENTER + data->current_frame % 2);
  }

}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

void fn_level_actor_function_surveillancescreen_create(fn_level_actor_t * actor)
{
  actor->position.w = FN_TILE_WIDTH * 2;
  actor->position.h = FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_surveillancescreen_free(fn_level_actor_t * actor)
{
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_surveillancescreen_interact_start(
    fn_level_actor_t * actor)
{
  fn_environment_t * env = fn_level_get_environment(actor->level);

  /* TODO show real note instead of this dummy */
  fn_infobox_show(env, "Not implemented yet.\n");
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_surveillancescreen_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  FnTexture * tile = NULL;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  tile = fn_tilecache_get_tile(tc, ANIM_BADGUYSCREEN);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  destrect.x += FN_TILE_WIDTH * pixelsize;
  tile = fn_tilecache_get_tile(tc, ANIM_BADGUYSCREEN + 1);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef struct fn_level_actor_hostileshot_data_t {
  /**
   * The tile number which is to be blitted in the level.
   */
  Uint16 tile;
  /**
   * Flag indicating if the shot is touching the hero.
   */
  Uint8 touching_hero;
  /**
   * The current frame.
   */
  Uint8 current_frame;
  /**
   * The number of frames.
   */
  Uint8 num_frames;
} fn_level_actor_hostileshot_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_hostileshot_create(fn_level_actor_t * actor)
{
  fn_level_actor_hostileshot_data_t * data = malloc(
      sizeof(fn_level_actor_hostileshot_data_t));
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  actor->data = data;
  data->current_frame = 0;
  data->num_frames = 2;
  if (actor->type == FN_LEVEL_ACTOR_HOSTILESHOT_LEFT) {
    data->tile = OBJ_BADSHOT;
  } else {
    data->tile = OBJ_BADSHOT + 2;
  }
  data->touching_hero = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_hostileshot_free(fn_level_actor_t * actor)
{
  fn_level_actor_hostileshot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_hostileshot_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_hostileshot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_increase_hurting_actors(hero, actor);
  data->touching_hero = 1;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_hostileshot_touch_end(fn_level_actor_t * actor)
{
  fn_level_actor_hostileshot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
  data->touching_hero = 0;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_hostileshot_act(fn_level_actor_t * actor)
{
  fn_level_actor_hostileshot_data_t * data = actor->data;

  data->current_frame++;
  data->current_frame %= data->num_frames;

  if (actor->type == FN_LEVEL_ACTOR_HOSTILESHOT_LEFT) {
    actor->position.x -= FN_HALFTILE_WIDTH;
  } else {
    actor->position.x += FN_HALFTILE_WIDTH;
  }
  if (fn_level_is_solid(actor->level,
        actor->position.x / FN_TILE_WIDTH,
        actor->position.y / FN_TILE_HEIGHT)) {
    actor->is_alive = 0;
    if (data->touching_hero) {
      fn_hero_t * hero = fn_level_get_hero(actor->level);
      fn_hero_decrease_hurting_actors(hero, actor);
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_hostileshot_blit(fn_level_actor_t * actor)
{
  fn_level_actor_hostileshot_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

void fn_level_actor_function_notebook_create(fn_level_actor_t * actor)
{
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_notebook_free(fn_level_actor_t * actor)
{
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_notebook_interact_start(fn_level_actor_t * actor)
{
  fn_environment_t * env = fn_level_get_environment(actor->level);

  /* TODO show real note instead of this dummy */
  fn_infobox_show(env, "Not implemented yet.\n");
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_notebook_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  FnTexture * tile = NULL;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  tile = fn_tilecache_get_tile(tc, OBJ_NOTE);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The exitdoor struct.
 */
typedef struct fn_level_actor_exitdoor_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The counter which defines for how many steps the exitdoor
   * has to be animated until the hero disappears.
   * time the act function is called.
   */
  Uint8 counter;
  /**
   * Stores the state of the door. 0 is idle, 1 is opening,
   * 2 is closing.
   */
  Uint8 state;
} fn_level_actor_exitdoor_data_t;

/* --------------------------------------------------------------- */

/**
 * Create an exit door.
 *
 * @param  actor  The door actor.
 */
void fn_level_actor_function_exitdoor_create(fn_level_actor_t * actor)
{
  fn_level_actor_exitdoor_data_t * data = malloc(
      sizeof(fn_level_actor_exitdoor_data_t));
  actor->data = data;
  actor->position.w = FN_TILE_WIDTH * 2;
  actor->position.h = FN_TILE_HEIGHT * 2;
  data->counter = 0;
  data->state = 0;
  data->tile = ANIM_EXITDOOR;
  actor->is_in_foreground = 0;
}

/* --------------------------------------------------------------- */

/**
 * Delete an exit door.
 *
 * @param  actor  The door actor.
 */
void fn_level_actor_function_exitdoor_free(fn_level_actor_t * actor)
{
  fn_level_actor_exitdoor_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Interaction of hero with exit door.
 *
 * @param  actor  The exitdoor actor.
 */
void fn_level_actor_function_exitdoor_interact_start(fn_level_actor_t * actor)
{
  fn_level_actor_exitdoor_data_t * data = actor->data;
  data->state = 1;
  fn_level_t * level = actor->level;
  level->levelpassed = 1;
}

/* --------------------------------------------------------------- */

/**
 * Action for exit door.
 * 
 * @param  actor  The exitdoor actor.
 */
void fn_level_actor_function_exitdoor_act(fn_level_actor_t * actor)
{
  fn_level_actor_exitdoor_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  switch(data->state) {
    case 0: /* idle */
      break;
    case 1: /* door opening */
      data->counter++;
      if (data->counter == 4) {
        hero->hidden = 1;
        data->state = 2;
        data->counter--;
      }
      break;
    case 2: /* door closing */
      if (data->counter == 0) {
        actor->level->do_play = 0;
        hero->hidden = 0;
      }
      data->counter--;
      break;
    default: /* error */
      fn_error_print_commandline("Exitdoor in invalid state");
      break;
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit the exitdoor.
 *
 * @param  actor  The exitdoor actor.
 */
void fn_level_actor_function_exitdoor_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_level_actor_exitdoor_data_t * data = actor->data;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = 0;
  destrect.y = 0;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  SDL_Surface * tile = SDL_CreateRGBSurface(
      target->flags,
      actor->position.w * pixelsize,
      actor->position.h * pixelsize,
      target->format->BitsPerPixel,
      0,
      0,
      0,
      0);
  FnTexture * part = fn_tilecache_get_tile(tc,
      data->tile + data->counter * 4);
  fn_texture_blit_to_sdl_surface(part, NULL, tile, &destrect);

  destrect.x += pixelsize * FN_TILE_WIDTH;
  part = fn_tilecache_get_tile(tc,
    data->tile + data->counter * 4 + 1);
  fn_texture_blit_to_sdl_surface(part, NULL, tile, &destrect);

  destrect.x = 0;
  destrect.y += pixelsize * FN_TILE_HEIGHT;
  part = fn_tilecache_get_tile(tc,
    data->tile + data->counter * 4 + 2);
  fn_texture_blit_to_sdl_surface(part, NULL, tile, &destrect);

  destrect.x += pixelsize * FN_TILE_WIDTH;
  part = fn_tilecache_get_tile(tc,
    data->tile + data->counter * 4 + 3);
  fn_texture_blit_to_sdl_surface(part, NULL, tile, &destrect);


  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);

  SDL_FreeSurface(tile); tile = NULL;
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The door struct.
 */
typedef struct fn_level_actor_door_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The counter which defines for how many steps the exitdoor
   * has to be animated until the hero disappears.
   * time the act function is called.
   */
  Uint8 counter;
  /**
   * Stores the state of the door. 0 is idle, 1 is opening,
   * 2 is removed and invisible.
   */
  Uint8 state;
} fn_level_actor_door_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a door.
 *
 * @param  actor  The door actor.
 */
void fn_level_actor_function_door_create(fn_level_actor_t * actor)
{
  fn_level_actor_door_data_t * data = malloc(
      sizeof(fn_level_actor_door_data_t));
  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  data->counter = 0;
  data->state = 0;
  data->tile = OBJ_DOOR;
  actor->is_in_foreground = 0;
}

/* --------------------------------------------------------------- */

/**
 * Delete a door.
 *
 * @param  actor  The door actor.
 */
void fn_level_actor_function_door_free(fn_level_actor_t * actor)
{
  fn_level_actor_door_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Action for door.
 * 
 * @param  actor  The door actor.
 */
void fn_level_actor_function_door_act(fn_level_actor_t * actor)
{
  fn_level_t * level = actor->level;
  fn_level_actor_door_data_t * data = actor->data;

  switch(data->state) {
    case 0: /* idle */
      break;
    case 1: /* door opening */
      if (data->counter == 0) {
        fn_level_set_solid(level,
            actor->position.x / FN_TILE_WIDTH,
            actor->position.y / FN_TILE_HEIGHT,
            0);
      }
      data->counter++;
      if (data->counter == 8) {
        data->counter = 0;
        data->state = 2;
        actor->is_alive = 0;
      }
      break;
    case 2:
      /* do nothing, the door is already opened. */
      break;
    default: /* error */
      fn_error_print_commandline("Door in invalid state");
      break;
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit the door.
 *
 * @param  actor  The door actor.
 */
void fn_level_actor_function_door_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_level_actor_door_data_t * data = actor->data;
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->counter);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The keyhole struct.
 */
typedef struct fn_level_actor_keyhole_data_t {
  /**
   * The tile number for the tilecache.
   */
  Uint16 tile;
  /**
   * The counter which defines for how many steps the exitdoor
   * has to be animated until the hero disappears.
   * time the act function is called.
   */
  Uint8 counter;
} fn_level_actor_keyhole_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a keyhole.
 *
 * @param  actor  The keyhole actor.
 */
void fn_level_actor_function_keyhole_create(fn_level_actor_t * actor)
{
  fn_level_actor_keyhole_data_t * data = malloc(
      sizeof(fn_level_actor_keyhole_data_t));
  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  data->counter = 0;
  data->tile = OBJ_KEYHOLE_BLACK;
  actor->is_in_foreground = 0;
}

/* --------------------------------------------------------------- */

/**
 * Delete a keyhole.
 *
 * @param  actor  The keyhole actor.
 */
void fn_level_actor_function_keyhole_free(fn_level_actor_t * actor)
{
  fn_level_actor_keyhole_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Action for keyhole.
 * 
 * @param  actor  The keyhole actor.
 */
void fn_level_actor_function_keyhole_act(fn_level_actor_t * actor)
{
  fn_level_actor_keyhole_data_t * data = actor->data;

  if (data->counter != 5) {
    data->counter++;
    data->counter %= 4;
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit the keyhole.
 *
 * @param  actor  The keyhole actor.
 */
void fn_level_actor_function_keyhole_blit(fn_level_actor_t * actor)
{
  fn_level_actor_keyhole_data_t * data = actor->data;
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  if (data->counter > 1) {
    switch(actor->type) {
      case FN_LEVEL_ACTOR_KEYHOLE_RED:
        tile = fn_tilecache_get_tile(tc, OBJ_KEYHOLE_RED);
        break;
      case FN_LEVEL_ACTOR_KEYHOLE_BLUE:
        tile = fn_tilecache_get_tile(tc, OBJ_KEYHOLE_BLUE);
        break;
      case FN_LEVEL_ACTOR_KEYHOLE_PINK:
        tile = fn_tilecache_get_tile(tc, OBJ_KEYHOLE_PINK);
        break;
      case FN_LEVEL_ACTOR_KEYHOLE_GREEN:
        tile = fn_tilecache_get_tile(tc, OBJ_KEYHOLE_GREEN);
        break;
      default:
        fn_error_print_commandline("Invalid keyhole actor");
    }
  }

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

/**
 * Hero interacts with keyhole.
 *
 * @param  actor  The keyhole actor.
 */
void fn_level_actor_function_keyhole_interact_start(fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_level_actor_keyhole_data_t * data = actor->data;
  Uint8 inventory = fn_hero_get_inventory(hero);

  char msg[40];

  Uint8 haskey = 0;
  Uint8 needed_key = 0;
  fn_level_actor_type_e door_to_open;

  switch(actor->type) {
    case FN_LEVEL_ACTOR_KEYHOLE_RED:
      needed_key = FN_INVENTORY_KEY_RED;
      door_to_open = FN_LEVEL_ACTOR_DOOR_RED;
      snprintf(msg, 40, "You don't have the red key.\n");
      break;
    case FN_LEVEL_ACTOR_KEYHOLE_BLUE:
      needed_key = FN_INVENTORY_KEY_BLUE;
      door_to_open = FN_LEVEL_ACTOR_DOOR_BLUE;
      snprintf(msg, 40, "You don't have the blue key.\n");
      break;
    case FN_LEVEL_ACTOR_KEYHOLE_PINK:
      needed_key = FN_INVENTORY_KEY_PINK;
      door_to_open = FN_LEVEL_ACTOR_DOOR_PINK;
      snprintf(msg, 40, "You don't have the pink key.\n");
      break;
    case FN_LEVEL_ACTOR_KEYHOLE_GREEN:
      needed_key = FN_INVENTORY_KEY_GREEN;
      door_to_open = FN_LEVEL_ACTOR_DOOR_GREEN;
      snprintf(msg, 40, "You don't have the green key.\n");
      break;
    default:
      fn_error_print_commandline("Invalid keyhole actor");
  }

  haskey = inventory & needed_key;

  if (haskey) {
    inventory &= ~(needed_key);
    fn_hero_set_inventory(hero, inventory);
    data->counter = 5;

    /* open all doors with the real color */
    fn_list_t * iter = NULL;
    for (iter = fn_list_first(actor->level->actors);
        iter != NULL;
        iter = fn_list_next(iter)) {
      fn_level_actor_t * dooractor = (fn_level_actor_t *)iter->data;

      if (dooractor->type == door_to_open) {
        fn_level_actor_door_data_t * doordata = dooractor->data;
        doordata->state = 1;
      }
    }
  } else if (data->counter != 5) {
    fn_environment_t * env = fn_level_get_environment(actor->level);
    fn_infobox_show(env, msg);
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Key actor creation function.
 *
 * @param  actor  The key actor.
 */
void fn_level_actor_function_key_create(fn_level_actor_t * actor)
{
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_WIDTH;
  actor->is_in_foreground = 0;
}


/* --------------------------------------------------------------- */

/**
 * The hero touches a key actor.
 *
 * @param  actor  The key actor.
 */
void fn_level_actor_function_key_touch_start(fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  Uint8 inventory = fn_hero_get_inventory(hero);
  switch(actor->type) {
    case FN_LEVEL_ACTOR_KEY_RED:
      inventory |= FN_INVENTORY_KEY_RED;
      break;
    case FN_LEVEL_ACTOR_KEY_BLUE:
      inventory |= FN_INVENTORY_KEY_BLUE;
      break;
    case FN_LEVEL_ACTOR_KEY_GREEN:
      inventory |= FN_INVENTORY_KEY_GREEN;
      break;
    case FN_LEVEL_ACTOR_KEY_PINK:
      inventory |= FN_INVENTORY_KEY_PINK;
      break;
    default:
      printf(__FILE__ ":%d: warning: key #%d"
          " added which is not a key\n",
          __LINE__, actor->type);
      break;
  }
  fn_hero_add_score(hero, 1000);
  fn_level_add_actor(actor->level,
      FN_LEVEL_ACTOR_SCORE_1000, actor->position.x, actor->position.y);
  actor->is_alive = 0;
  fn_hero_set_inventory(hero, inventory);
}

/* --------------------------------------------------------------- */

/**
 * Blit the key.
 *
 * @param  actor  The key actor.
 */
void fn_level_actor_function_key_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = NULL;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  switch(actor->type) {
    case FN_LEVEL_ACTOR_KEY_RED:
      tile = fn_tilecache_get_tile(tc, OBJ_KEY_RED);
      break;
    case FN_LEVEL_ACTOR_KEY_BLUE:
      tile = fn_tilecache_get_tile(tc, OBJ_KEY_BLUE);
      break;
    case FN_LEVEL_ACTOR_KEY_GREEN:
      tile = fn_tilecache_get_tile(tc, OBJ_KEY_GREEN);
      break;
    case FN_LEVEL_ACTOR_KEY_PINK:
      tile = fn_tilecache_get_tile(tc, OBJ_KEY_PINK);
      break;
    default:
      printf(__FILE__ ":%d: warning: key #%d"
          " tried to blit which is not a key\n",
          __LINE__, actor->type);
      return;
      break;
  }
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Create the shootable wall.
 *
 * @param  actor  The wall actor.
 */
void fn_level_actor_function_shootable_wall_create(fn_level_actor_t * actor)
{
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 0;
}

/* --------------------------------------------------------------- */

/**
 * Blit the shootable wall.
 *
 * @param  actor  The wall actor.
 */
void fn_level_actor_function_shootable_wall_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  FnTexture * tile = NULL;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;

  tile = fn_tilecache_get_tile(tc, 0x8C0/0x20);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
  tile = fn_tilecache_get_tile(tc, 0x1800/0x20);
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

/**
 * Shoot the shootable wall.
 *
 * @param  actor  The wall actor.
 */
void fn_level_actor_function_shootable_wall_shot(fn_level_actor_t * actor)
{
  fn_level_t * level = actor->level;
  fn_hero_t * hero = fn_level_get_hero(level);
  actor->is_alive = 0;
  fn_hero_add_score(hero, 10);
  fn_level_set_solid(level,
      actor->position.x / FN_TILE_WIDTH,
      actor->position.y / FN_TILE_HEIGHT,
      0);
  fn_level_add_actor(actor->level,
      FN_LEVEL_ACTOR_EXPLOSION, actor->position.x, actor->position.y);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef struct fn_level_actor_accesscard_door_data_t
{
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
} fn_level_actor_accesscard_door_data_t;

/**
 * Create an accesscard door.
 *
 * @param  actor  The accesscard door actor.
 */
void fn_level_actor_function_access_card_door_create(fn_level_actor_t * actor)
{
  fn_level_actor_accesscard_door_data_t * data = malloc(
      sizeof(fn_level_actor_accesscard_door_data_t));
  actor->data = data;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_HEIGHT;

  data->tile = OBJ_LASERBEAM;
  data->current_frame = 0;
  data->num_frames = 4;
  actor->is_in_foreground = 0;
}

/* --------------------------------------------------------------- */

/**
 * Delete an accesscard door.
 *
 * @param  actor  The accesscard door actor.
 */
void fn_level_actor_function_access_card_door_free(fn_level_actor_t * actor)
{
  fn_level_actor_accesscard_door_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Blit an accesscard door.
 *
 * @param  actor  The accesscard door actor.
 */
void fn_level_actor_function_access_card_door_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_level_actor_accesscard_door_data_t * data = actor->data;
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

/**
 * Act an accesscard door.
 *
 * @param  actor  The accesscard door actor.
 */
void fn_level_actor_function_access_card_door_act(fn_level_actor_t * actor)
{
  fn_level_actor_accesscard_door_data_t * data = actor->data;
  data->current_frame++;
  data->current_frame %= data->num_frames;
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The spikes data structure.
 */
typedef struct fn_level_actor_spike_data_t {
  /**
   * A flag indicating if the hero is currently touching the spike.
   */
  Uint8 touching_hero;
} fn_level_actor_spike_data_t;

/* --------------------------------------------------------------- */

/**
 * Spikes actor creation function.
 *
 * @param  actor  The spikes actor.
 */
void fn_level_actor_function_spikes_create(fn_level_actor_t * actor)
{
  fn_level_actor_spike_data_t * data = malloc(
      sizeof(fn_level_actor_spike_data_t));
  actor->data = data;
  data->touching_hero = 0;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.h = FN_TILE_WIDTH;
  actor->is_in_foreground = 1;
}

/* --------------------------------------------------------------- */


/**
 * Spikes actor deletion function.
 *
 * @param  actor  The spikes actor.
 */
void fn_level_actor_function_spikes_free(fn_level_actor_t * actor)
{
  fn_level_actor_spike_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Hero touches spikes actor.
 *
 * @param  actor  The spikes actor.
 */
void fn_level_actor_function_spikes_touch_start(fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_level_actor_spike_data_t * data = actor->data;
  fn_hero_increase_hurting_actors(hero, actor);
  data->touching_hero = 1;
}

/* --------------------------------------------------------------- */

/**
 * Hero stops to touch spikes actor.
 *
 * @param  actor  The spikes actor.
 */
void fn_level_actor_function_spikes_touch_end(fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_actors(hero, actor);
  fn_level_actor_spike_data_t * data = actor->data;
  data->touching_hero = 0;
}

/* --------------------------------------------------------------- */

/**
 * Blit the spikes.
 *
 * @param  actor  The spikes actor.
 */
void fn_level_actor_function_spikes_blit(fn_level_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  FnTexture * tile = NULL;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  fn_level_actor_spike_data_t * data = actor->data;
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  switch(actor->type) {
    case FN_LEVEL_ACTOR_SPIKES_UP:
      tile = fn_tilecache_get_tile(tc, OBJ_SPIKES_UP);
      break;
    case FN_LEVEL_ACTOR_SPIKES_DOWN:
      tile = fn_tilecache_get_tile(tc, OBJ_SPIKES_DOWN);
      break;
    case FN_LEVEL_ACTOR_SPIKE:
      if (data->touching_hero) {
        tile = fn_tilecache_get_tile(tc, OBJ_SPIKE + 1);
      } else {
        tile = fn_tilecache_get_tile(tc, OBJ_SPIKE);
      }

      break;
    default:
      printf(__FILE__ ":%d: warning: spike #%d"
          " tried to blit which is not a spike\n",
          __LINE__, actor->type);
      return;
      break;
  }
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The fan wheel
 */
typedef struct fn_level_actor_fan_data_t {
  /**
   * The tile number which is blitted in the level.
   */
  Uint16 tile;
  /**
   * The animation counter.
   */
  Uint8 current_frame;
  /**
   * The number of frames.
   */
  Uint8 num_frames;
  /**
   * A flag showing if the wheel is running.
   */
  Uint8 running;
} fn_level_actor_fan_data_t;

/* --------------------------------------------------------------- */

void fn_level_actor_function_fan_create(fn_level_actor_t * actor)
{
  fn_level_actor_fan_data_t * data = malloc(
      sizeof(fn_level_actor_fan_data_t));
  actor->data = data;
  data->tile = ANIM_FAN;
  data->num_frames = 4;
  data->current_frame = 0;
  data->running = 10;
  actor->position.h = 2 * FN_TILE_HEIGHT;
  actor->position.w = FN_TILE_WIDTH;
  actor->position.y -= FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_fan_free(fn_level_actor_t * actor)
{
  fn_level_actor_fan_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_fan_act(fn_level_actor_t * actor)
{
  fn_level_actor_fan_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  switch(data->running) {
    case 0:
      /* Do nothing */
      break;
    case 1:
      data->current_frame++;
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      data->current_frame++;
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      data->current_frame++;
      break;
    case 9:
      break;
    case 10:
      data->current_frame++;
      break;
    default:
      /* do nothing */
      break;
  }

  data->current_frame %= data->num_frames;
  if (data->running < 10 && data->running > 0) {
    data->running--;
  } else if (data->running == 10) {
    SDL_Rect * heropos = fn_hero_get_position(hero);

    if (fn_collision_overlap_vertical_rect_area(heropos,
          actor->position.y, actor->position.h)) {
      int hdistance = fn_collision_distance_horizontal_rect_area(
          heropos, actor->position.x, actor->position.w);

      int fandirection = 0;
      if (actor->type == FN_LEVEL_ACTOR_FAN_LEFT) {
        fandirection = -1;
      } else {
        fandirection = 1;
      }

      if (fandirection < 0 && hdistance < 0) {
        return;
      }
      if (fandirection > 0 && hdistance > 0) {
        return;
      }

      if (hdistance == 0) {
        hdistance = FN_HALFTILE_WIDTH * fandirection;
      }

      Uint16 hdistance_abs =
        (hdistance > 0 ? hdistance : -hdistance);
      if (hdistance_abs < 8 * FN_HALFTILE_WIDTH) {
        fn_hero_push_horizontally(
            hero,
            actor->level,
            fandirection * FN_TILE_WIDTH);
      }
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_fan_blit(fn_level_actor_t * actor)
{
  fn_level_actor_fan_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);

  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  FnTexture * tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame * 2);
  destrect.x = actor->position.x * pixelsize;
  destrect.y = actor->position.y * pixelsize;
  destrect.w = actor->position.w * pixelsize;
  destrect.h = actor->position.h * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);

  tile = fn_tilecache_get_tile(tc,
      data->tile + data->current_frame * 2 + 1);
  destrect.y += FN_TILE_HEIGHT * pixelsize;
  fn_texture_blit_to_sdl_surface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_level_actor_function_fan_shot(fn_level_actor_t * actor)
{
  fn_level_actor_fan_data_t * data = actor->data;
  data->running = 9;
  fn_level_add_actor(actor->level,
      FN_LEVEL_ACTOR_STEAM, actor->position.x, actor->position.y);
}


/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef void (* fn_level_actor_function_t)(fn_level_actor_t *);

/**
 * An array of functions to call for different actions on different
 * actors.
 */
void
  (* fn_level_actor_functions[FN_LEVEL_ACTOR_NUM_TYPES][FN_LEVEL_ACTOR_NUM_FUNCTIONS])
  (fn_level_actor_t *) =
{
  [FN_LEVEL_ACTOR_FIREWHEELBOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_firewheelbot_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_firewheelbot_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_firewheelbot_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_firewheelbot_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_firewheelbot_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_firewheelbot_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_firewheelbot_shot,
  },
  [FN_LEVEL_ACTOR_FLAMEGNOMEBOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_FLYINGBOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_FOOTBOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_HELICOPTERBOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_RABBITOIDBOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_REDBALL_JUMPING] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_redball_jumping_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_redball_jumping_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_redball_jumping_hero_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_redball_jumping_hero_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_redball_jumping_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_redball_jumping_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_redball_jumping_shot,
  },
  [FN_LEVEL_ACTOR_REDBALL_LYING] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_redball_lying_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_redball_lying_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_redball_lying_hero_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_redball_lying_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_redball_lying_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_ROBOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_robot_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_robot_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_robot_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_robot_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_robot_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_robot_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_robot_shot,
  },
  [FN_LEVEL_ACTOR_ROBOT_DISAPPEARING] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_singleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_singleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_singleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_singleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SNAKEBOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_TANKBOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_tankbot_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_tankbot_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_tankbot_hero_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_tankbot_hero_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_tankbot_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_tankbot_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_tankbot_shot,
  },
  [FN_LEVEL_ACTOR_WALLCRAWLERBOT_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_wallcrawler_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_wallcrawler_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_wallcrawler_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_wallcrawler_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_wallcrawler_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_wallcrawler_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_wallcrawler_shot,
  },
  [FN_LEVEL_ACTOR_WALLCRAWLERBOT_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_wallcrawler_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_wallcrawler_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_wallcrawler_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_wallcrawler_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_wallcrawler_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_wallcrawler_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_wallcrawler_shot,
  },
  [FN_LEVEL_ACTOR_DRPROTON] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_CAMERA] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_camera_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_camera_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_camera_shot,
  },
  [FN_LEVEL_ACTOR_EXPLOSION] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_explosion_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_explosion_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_explosion_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_explosion_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_FIRE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_singleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_singleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_singleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_singleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_DUSTCLOUD] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_singleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_singleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_singleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_singleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_STEAM] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_singleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_singleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_singleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_singleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_PARTICLE_PINK] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_particle_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_particle_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_particle_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_particle_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_PARTICLE_BLUE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_particle_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_particle_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_particle_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_particle_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_PARTICLE_WHITE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_particle_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_particle_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_particle_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_particle_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_PARTICLE_GREEN] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_particle_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_particle_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_particle_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_particle_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_ROCKET] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_rocket_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_rocket_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_rocket_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_rocket_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_rocket_shot,
  },
  [FN_LEVEL_ACTOR_BOMB] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_bomb_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_bomb_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_bomb_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_bomb_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOMBFIRE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_bombfire_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_bombfire_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_bombfire_hero_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_bombfire_hero_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_bombfire_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_bombfire_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_WATER] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_EXITDOOR] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_exitdoor_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_exitdoor_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_exitdoor_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_exitdoor_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_exitdoor_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_NOTEBOOK] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_notebook_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_notebook_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_notebook_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_notebook_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SURVEILLANCESCREEN] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_surveillancescreen_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_surveillancescreen_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_surveillancescreen_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_surveillancescreen_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_HOSTILESHOT_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_hostileshot_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_hostileshot_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_hostileshot_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_hostileshot_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_hostileshot_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_hostileshot_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_HOSTILESHOT_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_hostileshot_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_hostileshot_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_hostileshot_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_hostileshot_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_hostileshot_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_hostileshot_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SODA] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_SODA_FLYING] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_soda_flying_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_soda_flying_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_soda_flying_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_soda_flying_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_soda_flying_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_UNSTABLEFLOOR] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_unstablefloor_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_unstablefloor_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_unstablefloor_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_unstablefloor_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_EXPANDINGFLOOR] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_expandingfloor_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_expandingfloor_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_expandingfloor_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_expandingfloor_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_CONVEYOR_LEFTMOVING_RIGHTEND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_conveyor_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_conveyor_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_conveyor_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_conveyor_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_CONVEYOR_RIGHTMOVING_RIGHTEND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_conveyor_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_conveyor_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_conveyor_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_conveyor_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_FAN_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_fan_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_fan_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_fan_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_fan_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_fan_shot,
  },
  [FN_LEVEL_ACTOR_FAN_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_fan_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_fan_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_fan_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_fan_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_fan_shot,
  },
  [FN_LEVEL_ACTOR_BROKENWALL_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_STONE_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_TELEPORTER1] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_teleporter_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_teleporter_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_teleporter_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_teleporter_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_TELEPORTER2] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_teleporter_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_teleporter_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_teleporter_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_teleporter_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_FENCE_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_STONEWINDOW_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_WINDOWLEFT_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_WINDOWRIGHT_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCREEN] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_BOX_GREY_EMPTY] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_BOOTS] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_BOOTS] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_CLAMPS] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = 
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_CLAMPS] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_GUN] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_GUN] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_BOMB] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_BOX_RED_SODA] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_BOX_RED_CHICKEN] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_CHICKEN_SINGLE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_CHICKEN_DOUBLE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_BLUE_FOOTBALL] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_FOOTBALL] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_FLAG] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_BLUE_JOYSTICK] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_JOYSTICK] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_BLUE_DISK] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_DISK] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_BLUE_BALLOON] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_BALLOON] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_balloon_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_balloon_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_balloon_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_balloon_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_balloon_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_balloon_shot,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_GLOVE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_GLOVE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_FULL_LIFE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_FULL_LIFE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
    fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_BLUE_FLAG] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_BLUE_FLAG] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_BOX_BLUE_RADIO] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_RADIO] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_ACCESS_CARD] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_ACCESS_CARD] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_LETTER_D] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_LETTER_D] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_LETTER_U] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_LETTER_U] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_LETTER_K] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_LETTER_K] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BOX_GREY_LETTER_E] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_item_shot,
  },
  [FN_LEVEL_ACTOR_LETTER_E] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_item_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_item_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_item_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_item_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_item_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_item_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_ACCESS_CARD_SLOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_accesscard_slot_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_accesscard_slot_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_accesscard_slot_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_accesscard_slot_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_accesscard_slot_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_GLOVE_SLOT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_glove_slot_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_glove_slot_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_glove_slot_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_glove_slot_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_glove_slot_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_KEY_RED] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_key_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_key_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_key_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_KEYHOLE_RED] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_keyhole_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_keyhole_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_keyhole_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_keyhole_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_keyhole_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_DOOR_RED] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_door_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_door_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_door_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_door_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_KEY_BLUE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_key_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_key_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_key_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_KEYHOLE_BLUE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_keyhole_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_keyhole_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_keyhole_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_keyhole_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_keyhole_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_DOOR_BLUE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_door_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_door_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_door_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_door_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_KEY_PINK] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_key_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_key_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_key_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_KEYHOLE_PINK] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_keyhole_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_keyhole_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_keyhole_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_keyhole_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_keyhole_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_DOOR_PINK] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_door_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_door_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_door_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_door_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_KEY_GREEN] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_key_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_key_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_key_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_KEYHOLE_GREEN] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_keyhole_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_keyhole_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_keyhole_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_keyhole_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_keyhole_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_DOOR_GREEN] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_door_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_door_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_door_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_door_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SHOOTABLE_WALL] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_shootable_wall_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_shootable_wall_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_shootable_wall_shot,
  },
  [FN_LEVEL_ACTOR_LIFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_lift_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_lift_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_level_actor_function_lift_interact_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   =
      fn_level_actor_function_lift_interact_end,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_lift_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_lift_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_ACME] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_acme_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_acme_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_acme_hero_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_acme_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_acme_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_acme_shot,
  },
  [FN_LEVEL_ACTOR_FIRE_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_fire_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_fire_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_fire_hero_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_fire_hero_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_fire_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_fire_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_FIRE_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_fire_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_fire_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_fire_hero_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_fire_hero_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_fire_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_fire_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_MILL] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_mill_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_mill_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_mill_hero_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_mill_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_mill_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                =
      fn_level_actor_function_mill_shot,
  },
  [FN_LEVEL_ACTOR_LASERBEAM] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                = NULL, /* TODO */
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_LEVEL_ACTOR_ACCESS_CARD_DOOR] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_access_card_door_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_access_card_door_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_access_card_door_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_access_card_door_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SPIKES_UP] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_spikes_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_spikes_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_spikes_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_spikes_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_spikes_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SPIKES_DOWN] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_spikes_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_spikes_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_spikes_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_spikes_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_spikes_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SPIKE] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_spikes_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_spikes_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_level_actor_function_spikes_touch_start,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_level_actor_function_spikes_touch_end,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_spikes_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_100] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_200] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_500] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_1000] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_2000] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_5000] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_10000] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_1_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_1_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_2_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_2_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_3_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_3_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_4_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_4_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_5_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_5_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_6_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_6_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_7_LEFT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_SCORE_BONUS_7_RIGHT] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_score_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                =
      fn_level_actor_function_score_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 =
      fn_level_actor_function_score_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_score_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND1] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND2] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND3] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BLUE_LIGHT_BACKGROUND4] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_TEXT_ON_SCREEN_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_HIGH_VOLTAGE_FLASH_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_RED_FLASHLIGHT_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_BLUE_FLASHLIGHT_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_KEYPANEL_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_RED_ROTATIONLIGHT_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_UPARROW_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_GREEN_POISON_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_LEVEL_ACTOR_LAVA_BACKGROUND] = {
    [FN_LEVEL_ACTOR_FUNCTION_CREATE]              =
      fn_level_actor_function_simpleanimation_create,
    [FN_LEVEL_ACTOR_FUNCTION_FREE]                = 
      fn_level_actor_function_simpleanimation_free,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_LEVEL_ACTOR_FUNCTION_ACT]                 = 
      fn_level_actor_function_simpleanimation_act,
    [FN_LEVEL_ACTOR_FUNCTION_BLIT]                =
      fn_level_actor_function_simpleanimation_blit,
    [FN_LEVEL_ACTOR_FUNCTION_SHOT]                = NULL,
  },
};

/* --------------------------------------------------------------- */

fn_level_actor_t * fn_level_actor_create(fn_level_t * level,
    fn_level_actor_type_e type,
    Uint16 x,
    Uint16 y)
{
  fn_level_actor_function_t func = NULL;
  fn_level_actor_t * actor = malloc(sizeof(fn_level_actor_t));
  actor->level = level;
  actor->type = type;
  actor->position.x = x;
  actor->position.y = y;
  actor->position.w = 0; /* should be changed by func */
  actor->position.h = 0; /* should be changed by func */
  actor->is_alive = 1;
  actor->touches_hero = 0;
  actor->is_in_foreground = 0;
  actor->is_visible = 0;
  actor->acts_while_invisible = 0;
  func = fn_level_actor_functions[actor->type][FN_LEVEL_ACTOR_FUNCTION_CREATE];
  if (func != NULL) {
    func(actor);
  }
  return actor;
}

/* --------------------------------------------------------------- */

void fn_level_actor_free(fn_level_actor_t * actor)
{
  fn_level_actor_function_t func =
    fn_level_actor_functions[actor->type][FN_LEVEL_ACTOR_FUNCTION_FREE];
  if (func != NULL) {
    func(actor);
  }
  free(actor);
}

/* --------------------------------------------------------------- */

int fn_level_actor_touches_hero(fn_level_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  return(
      fn_collision_overlap_rect_area(
        fn_hero_get_position(hero),
        actor->position.x, actor->position.y, actor->position.w, actor->position.h));
}

/* --------------------------------------------------------------- */

void fn_level_actor_check_hero_touch(fn_level_actor_t * actor)
{
  if (fn_level_actor_touches_hero(actor)) {
    if (!actor->touches_hero) {
      actor->touches_hero = 1;
      fn_level_actor_hero_touch_start(actor);
    }
  } else {
    if (actor->touches_hero) {
      fn_level_actor_hero_touch_end(actor);
      actor->touches_hero = 0;
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_hero_touch_start(fn_level_actor_t * actor)
{
  fn_level_actor_function_t func =
    fn_level_actor_functions[actor->type][FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_START];
  if (func != NULL) {
    func(actor);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_hero_touch_end(fn_level_actor_t * actor)
{
  fn_level_actor_function_t func =
    fn_level_actor_functions[actor->type][FN_LEVEL_ACTOR_FUNCTION_HERO_TOUCH_END];
  if (func != NULL) {
    func(actor);
  }
}

/* --------------------------------------------------------------- */

Uint8 fn_level_actor_hero_can_interact(fn_level_actor_t * actor)
{
  if (actor->type == FN_LEVEL_ACTOR_LIFT) {
    /* This check needs to be done for lift only because
     * if there are two lifts next to each other, the mostleft
     * lift would be chosen for interaction instead of the one on
     * which the hero stands.
     */
    fn_hero_t * hero = fn_level_get_hero(actor->level);
    SDL_Rect * heropos = fn_hero_get_position(hero);
    return (actor->position.x == heropos->x);
  }
  fn_level_actor_function_t func =
    fn_level_actor_functions[
    actor->type][FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START];
  return (func != NULL);
}

/* --------------------------------------------------------------- */

void fn_level_actor_hero_interact_start(fn_level_actor_t * actor)
{
  fn_level_actor_function_t func =
    fn_level_actor_functions[
    actor->type][FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_START];
  if (func != NULL) {
    func(actor);
  }
}

/* --------------------------------------------------------------- */

void fn_level_actor_hero_interact_stop(fn_level_actor_t * actor)
{
  fn_level_actor_function_t func =
    fn_level_actor_functions[
    actor->type][FN_LEVEL_ACTOR_FUNCTION_HERO_INTERACT_END];
  if (func != NULL) {
    func(actor);
  }
}

/* --------------------------------------------------------------- */

int fn_level_actor_act(fn_level_actor_t * actor)
{
  fn_level_actor_check_hero_touch(actor);
  fn_level_actor_function_t func =
    fn_level_actor_functions[actor->type][FN_LEVEL_ACTOR_FUNCTION_ACT];
  if (func != NULL)
  {
    func(actor);
  }
  return actor->is_alive;
}

/* --------------------------------------------------------------- */

void fn_level_actor_blit(fn_level_actor_t * actor)
{
  fn_level_actor_function_t func =
    fn_level_actor_functions[actor->type][FN_LEVEL_ACTOR_FUNCTION_BLIT];
  if (func != NULL) {
    func(actor);
    SDL_Surface * target = fn_level_get_surface(actor->level);
    Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
    Uint8 draw_collision_bounds =
      fn_environment_get_draw_collision_bounds(
          fn_level_get_environment(actor->level));
    if (draw_collision_bounds) {
      fn_collision_area_draw(target, pixelsize,
          actor->position.x, actor->position.y, actor->position.w, actor->position.h);
    }
  }
}

/* --------------------------------------------------------------- */

Uint8 fn_level_actor_shot(fn_level_actor_t * actor)
{
  fn_level_actor_function_t func =
    fn_level_actor_functions[actor->type][FN_LEVEL_ACTOR_FUNCTION_SHOT];
  if (func != NULL) {
    func(actor);
    return 1;
  }
  return 0;
}

/* --------------------------------------------------------------- */

Uint16 fn_level_actor_get_x(fn_level_actor_t * actor)
{
  return actor->position.x;
}

/* --------------------------------------------------------------- */

Uint16 fn_level_actor_get_y(fn_level_actor_t * actor)
{
  return actor->position.y;
}

/* --------------------------------------------------------------- */

Uint16 fn_level_actor_get_w(fn_level_actor_t * actor)
{
  return actor->position.w;
}

/* --------------------------------------------------------------- */

Uint16 fn_level_actor_get_h(fn_level_actor_t * actor)
{
  return actor->position.h;
}

/* --------------------------------------------------------------- */

Uint8 fn_level_actor_can_get_shot(fn_level_actor_t * actor)
{
  fn_level_actor_function_t func =
    fn_level_actor_functions[actor->type][FN_LEVEL_ACTOR_FUNCTION_SHOT];
  return (func != NULL);
}

/* --------------------------------------------------------------- */

Uint8 fn_level_actor_in_foreground(fn_level_actor_t * actor)
{
  return actor->is_in_foreground;
}

/* --------------------------------------------------------------- */

SDL_Rect * fn_level_actor_get_position(fn_level_actor_t * actor)
{
  return &(actor->position);
}

/* --------------------------------------------------------------- */

void fn_level_actor_set_visible(fn_level_actor_t * actor, Uint8 visibility)
{
  actor->is_visible = visibility;
}

/* --------------------------------------------------------------- */

Uint8 fn_level_actor_is_visible(fn_level_actor_t * actor)
{
  return actor->is_visible;
}
