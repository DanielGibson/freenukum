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

#include "fn_tilecache.h"
#include "fn_actor.h"
#include "fn_object.h"
#include "fn_infobox.h"
#include "fn_error_cmdline.h"

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
   * The actor gets hit by a shot.
   */
  FN_ACTOR_FUNCTION_SHOT,
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

  actor->is_in_foreground = 0;
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
    case FN_ACTOR_WINDOWLEFT_BACKGROUND:
      data->tile = ANIM_WINDOWBG;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_WINDOWRIGHT_BACKGROUND:
      data->tile = ANIM_WINDOWBG + 1;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_STONEWINDOW_BACKGROUND:
      data->tile = ANIM_STONEWINDOWBG;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_BROKENWALL_BACKGROUND:
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
/* --------------------------------------------------------------- */

/**
 * The jumping red ball.
 */
typedef struct fn_actor_redball_jumping_data_t {
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
} fn_actor_redball_jumping_data_t;

/* --------------------------------------------------------------- */

void fn_actor_function_redball_jumping_create(fn_actor_t * actor)
{
  fn_actor_redball_jumping_data_t * data = malloc(
      sizeof(fn_actor_redball_jumping_data_t));
  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  data->counter = 0;
  data->tile = ANIM_MINE;
  data->base_y = actor->y;
}

/* --------------------------------------------------------------- */

void fn_actor_function_redball_jumping_free(fn_actor_t * actor)
{
  fn_actor_redball_jumping_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_actor_function_redball_jumping_hero_touch_start(
    fn_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_increase_hurting_objects(hero);
}

/* --------------------------------------------------------------- */

void fn_actor_function_redball_jumping_hero_touch_end(
    fn_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_objects(hero);
}

/* --------------------------------------------------------------- */

void fn_actor_function_redball_jumping_act(fn_actor_t * actor)
{
  fn_actor_redball_jumping_data_t * data = actor->data;

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
  actor->y = data->base_y - distance;

  data->counter++;
  data->counter %= 12;
}

/* --------------------------------------------------------------- */

void fn_actor_function_redball_jumping_blit(fn_actor_t * actor)
{
  fn_actor_redball_jumping_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * tile = fn_tilecache_get_tile(tc,
      data->tile);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_actor_function_redball_jumping_shot(fn_actor_t * actor)
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
typedef struct fn_actor_redball_lying_data_t {
  /**
   * The tile number which is to be blitted in the level.
   */
  Uint16 tile;
  /**
   * Flag that stores if the redball is touching the hero.
   */
  Uint8 touching_hero;
} fn_actor_redball_lying_data_t;

/* --------------------------------------------------------------- */

void fn_actor_function_redball_lying_create(fn_actor_t * actor)
{
  fn_actor_redball_lying_data_t * data = malloc(
      sizeof(fn_actor_redball_lying_data_t));
  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  data->tile = ANIM_MINE;
  data->touching_hero = 0;
}


/* --------------------------------------------------------------- */

void fn_actor_function_redball_lying_free(fn_actor_t * actor)
{
  fn_actor_redball_lying_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_actor_function_redball_lying_hero_touch_start(
    fn_actor_t * actor)
{
  fn_actor_redball_lying_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (!data->touching_hero) {
    data->touching_hero = 1;
    fn_hero_increase_hurting_objects(hero);
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_redball_lying_act(
    fn_actor_t * actor)
{
  fn_actor_redball_lying_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (data->touching_hero == 1) {
    data->touching_hero++;
  } else if (data->touching_hero > 1) {
    fn_hero_decrease_hurting_objects(hero);
    actor->is_alive = 0;
    fn_level_add_actor(actor->level,
        FN_ACTOR_FIRE, actor->x, actor->y);
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_redball_lying_blit(fn_actor_t * actor)
{
  fn_actor_redball_lying_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * tile = fn_tilecache_get_tile(tc,
      data->tile);
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
 * The robot.
 */
typedef struct fn_actor_robot_data_t {
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
   * A flag indicating if the robot was shot.
   */
  Uint8 was_shot;
  /**
   * A flag indicating if the robot is currently touching the hero.
   */
  Uint8 touching_hero;
} fn_actor_robot_data_t;

/* --------------------------------------------------------------- */

void fn_actor_function_robot_create(fn_actor_t * actor)
{
  fn_actor_robot_data_t * data = malloc(
      sizeof(fn_actor_robot_data_t));
  actor->data = data;
  actor->is_in_foreground = 1;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  data->direction = fn_horizontal_direction_left;
  data->tile = ANIM_ROBOT;
  data->current_frame = 0;
  data->num_frames = 3;
  data->was_shot = 0;
  data->touching_hero = 0;
}

/* --------------------------------------------------------------- */

void fn_actor_function_robot_free(fn_actor_t * actor)
{
  fn_actor_robot_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_actor_function_robot_touch_start(fn_actor_t * actor)
{
  fn_actor_robot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (!data->was_shot) {
    fn_hero_increase_hurting_objects(hero);
    data->touching_hero = 1;
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_robot_touch_end(fn_actor_t * actor)
{
  fn_actor_robot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (!data->was_shot) {
    fn_hero_decrease_hurting_objects(hero);
    data->touching_hero = 0;
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_robot_act(fn_actor_t * actor)
{
  fn_actor_robot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  data->current_frame++;
  if (data->was_shot) {
    if (data->current_frame == data->num_frames) {
      /* create explosion */
      actor->is_alive = 0;
      fn_level_add_actor(actor->level,
          FN_ACTOR_EXPLOSION, actor->x, actor->y);
      fn_hero_add_score(hero, 100);
    }
  } else {
    data->current_frame %= data->num_frames;
    if (!fn_level_is_solid(actor->level,
          (actor->x) / FN_TILE_WIDTH,
          (actor->y) / FN_TILE_HEIGHT + 1)) {
      /* still in the air, so let the robot fall down. */
      actor->y += FN_HALFTILE_HEIGHT;
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
              (actor->x + direction * FN_HALFTILE_WIDTH)/FN_TILE_WIDTH,
              (actor->y) / FN_TILE_HEIGHT) &&
            /* Check if it is solid below this place */
            fn_level_is_solid(actor->level,
              (actor->x + direction * FN_HALFTILE_WIDTH)/FN_TILE_WIDTH,
              (actor->y+FN_TILE_HEIGHT) / FN_TILE_HEIGHT)
           )
        {
          if (direction == 2) direction = 1;
          actor->x += direction * FN_HALFTILE_WIDTH;
        } else {
          data->direction = (
              data->direction == fn_horizontal_direction_left ?
              fn_horizontal_direction_right :
              fn_horizontal_direction_left);

          if (direction == 2) direction = 1;
          direction *= (-1);
          actor->x += direction * FN_HALFTILE_WIDTH;
        }
      }
    }
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_robot_blit(fn_actor_t * actor)
{
  fn_actor_robot_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
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

void fn_actor_function_robot_shot(fn_actor_t * actor)
{
  fn_actor_robot_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  if (!data->was_shot && data->touching_hero) {
    fn_hero_decrease_hurting_objects(hero);
    data->touching_hero = 0;
  }
  if (!data->was_shot) {
    data->current_frame = 0;
    data->was_shot = 1;
    data->tile = ANIM_ROBOT + 3;
    data->num_frames = 7;
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The wallcrawler bot.
 */
typedef struct fn_actor_wallcrawler_data_t {
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
} fn_actor_wallcrawler_data_t;

/* --------------------------------------------------------------- */

void fn_actor_function_wallcrawler_create(fn_actor_t * actor)
{

  fn_actor_wallcrawler_data_t * data = malloc(
      sizeof(fn_actor_wallcrawler_data_t));
  actor->data = data;
  actor->is_in_foreground = 1;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  data->direction = fn_vertical_direction_up;
  if (actor->type == FN_ACTOR_WALLCRAWLERBOT_LEFT) {
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

void fn_actor_function_wallcrawler_free(fn_actor_t * actor)
{
  fn_actor_wallcrawler_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_actor_function_wallcrawler_touch_start(fn_actor_t * actor)
{
  fn_actor_wallcrawler_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (!data->was_shot) {
    fn_hero_increase_hurting_objects(hero);
    data->touching_hero = 1;
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_wallcrawler_touch_end(fn_actor_t * actor)
{
  fn_actor_wallcrawler_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (!data->was_shot) {
    fn_hero_decrease_hurting_objects(hero);
    data->touching_hero = 0;
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_wallcrawler_act(fn_actor_t * actor)
{
  fn_actor_wallcrawler_data_t * data = actor->data;
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
          (actor->x) / FN_TILE_WIDTH,
          (actor->y - 1) / FN_TILE_HEIGHT) ||
        /* bot has no more wall to stick upon */
        !fn_level_is_solid(level,
          (actor->x + orientation * FN_TILE_WIDTH) / FN_TILE_WIDTH,
          (actor->y - 1) / FN_TILE_HEIGHT)
       ) {
      actor->y++;
      data->direction = fn_vertical_direction_down;
    } else {
      actor->y--;
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
          (actor->x) / FN_TILE_WIDTH,
          (actor->y + FN_TILE_HEIGHT) / FN_TILE_HEIGHT) ||
        /* bot has no more wall to stick upon */
        !fn_level_is_solid(level,
          (actor->x + orientation * FN_TILE_WIDTH) / FN_TILE_WIDTH,
          (actor->y + FN_TILE_HEIGHT) / FN_TILE_HEIGHT)
       ) {
      actor->y--;
      data->direction = fn_vertical_direction_up;
    } else {
      actor->y++;
    }
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_wallcrawler_blit(fn_actor_t * actor)
{
  fn_actor_wallcrawler_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
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

void fn_actor_function_wallcrawler_shot(fn_actor_t * actor)
{
  fn_actor_wallcrawler_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  if (!data->was_shot && data->touching_hero) {
    fn_hero_decrease_hurting_objects(hero);
    data->touching_hero = 0;
    data->current_frame = 0;
  }
  actor->is_alive = 0;
  fn_level_add_actor(actor->level,
      FN_ACTOR_EXPLOSION, actor->x, actor->y);
  fn_hero_add_score(hero, 100);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef enum fn_actor_lift_state_e {
  fn_actor_lift_state_idle,
  fn_actor_lift_state_ascending,
  fn_actor_lift_state_descending,
} fn_actor_lift_state_e;

/* --------------------------------------------------------------- */

/**
 * The lift.
 */
typedef struct fn_actor_lift_data_t {
  /**
   * The current height of the lift.
   */
  Uint16 height;
  /**
   * The state of the lift.
   */
  fn_actor_lift_state_e state;
} fn_actor_lift_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a lift.
 *
 * @param  actor  The lift actor.
 */
void fn_actor_function_lift_create(fn_actor_t * actor)
{
  fn_actor_lift_data_t * data = malloc(
      sizeof(fn_actor_lift_data_t));
  data->height = 0;
  data->state = fn_actor_lift_state_idle;
  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 0;
}

/* --------------------------------------------------------------- */

/**
 * Delete the lift.
 *
 * @param  actor  The lift actor.
 */
void fn_actor_function_lift_free(fn_actor_t * actor)
{
  fn_actor_lift_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Hero starts to interact with lift.
 *
 * @param  actor  The lift actor.
 */
void fn_actor_function_lift_interact_start(fn_actor_t * actor)
{
  fn_actor_lift_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  if (fn_hero_get_x(hero) * FN_HALFTILE_WIDTH == actor->x &&
      fn_hero_get_y(hero) * FN_HALFTILE_HEIGHT ==
      actor->y - FN_TILE_HEIGHT) {
    data->state = fn_actor_lift_state_ascending;
  }
}

/* --------------------------------------------------------------- */

/**
 * Hero stops to interact with lift.
 *
 * @param  actor  The lift actor.
 */
void fn_actor_function_lift_interact_end(fn_actor_t * actor)
{
  fn_actor_lift_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  if (fn_hero_get_x(hero) * FN_HALFTILE_WIDTH == actor->x &&
      fn_hero_get_y(hero) * FN_HALFTILE_HEIGHT ==
      actor->y - FN_TILE_HEIGHT) {
    data->state = fn_actor_lift_state_idle;
  } else {
    data->state = fn_actor_lift_state_descending;
  }
}

/* --------------------------------------------------------------- */

/**
 * Lift acts.
 *
 * @param  actor  The lift actor.
 */
void fn_actor_function_lift_act(fn_actor_t * actor)
{
  fn_actor_lift_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_level_t * level = actor->level;

  if (data->state == fn_actor_lift_state_ascending ||
      (data->state == fn_actor_lift_state_idle && data->height > 0))
  {
    if (fn_hero_get_x(hero) * FN_HALFTILE_WIDTH == actor->x &&
        fn_hero_get_y(hero) * FN_HALFTILE_HEIGHT ==
        actor->y - FN_TILE_HEIGHT) {
    } else {
      data->state = fn_actor_lift_state_descending;
    }
  }

  switch(data->state)
  {
    case fn_actor_lift_state_ascending:
      if (fn_level_is_solid(level,
            actor->x/FN_TILE_WIDTH,
            actor->y/FN_TILE_HEIGHT-3)) {
        data->state = fn_actor_lift_state_idle;
      } else {
        data->height++;
        actor->y -= FN_TILE_HEIGHT;
        fn_hero_replace(hero,
            actor->x/FN_HALFTILE_WIDTH,
            actor->y/FN_HALFTILE_HEIGHT - 2);
        fn_level_set_solid(level,
            actor->x/FN_TILE_WIDTH,
            actor->y/FN_TILE_HEIGHT,
            1);
      }
      break;
    case fn_actor_lift_state_descending:
      {
        int i = 0;
        for (i = 0; i < 2; i++) {
          if (data->height != 0) {
            fn_level_set_solid(level,
                actor->x/FN_TILE_WIDTH,
                actor->y/FN_TILE_HEIGHT,
                0);
            actor->y += FN_TILE_HEIGHT;
            data->height--;
          } else {
            data->state = fn_actor_lift_state_idle;
          }
        }
      }
      break;
    case fn_actor_lift_state_idle:
      /* nothing to do, we stay where we are. */
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
void fn_actor_function_lift_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_actor_lift_data_t * data = actor->data;
  SDL_Surface * tile = NULL;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;

  int i = 0;
  tile = fn_tilecache_get_tile(tc, SOLID_START + 23);
  for (i = 0; i < data->height * 2; i++) {
    destrect.y += FN_HALFTILE_HEIGHT * pixelsize;
    SDL_BlitSurface(tile, NULL, target, &destrect);
  }

  tile = fn_tilecache_get_tile(tc,
      OBJ_ELEVATOR);
  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);

}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The acme stone.
 */
typedef struct fn_actor_acme_data_t {
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
} fn_actor_acme_data_t;

/* --------------------------------------------------------------- */

void fn_actor_function_acme_create(fn_actor_t * actor)
{
  fn_actor_acme_data_t * data = malloc(
      sizeof(fn_actor_acme_data_t));
  actor->data = data;
  data->tile = OBJ_FALLINGBLOCK;
  data->counter = 0;
  data->touching_hero = 0;
  actor->w = FN_TILE_WIDTH * 2;
  actor->h = FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

void fn_actor_function_acme_free(fn_actor_t * actor)
{
  fn_actor_acme_data_t * data = actor->data;

  if (data->touching_hero) {
    fn_hero_t * hero = fn_level_get_hero(actor->level);
    data->touching_hero = 0;
    fn_hero_decrease_hurting_objects(hero);
  }

  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

void fn_actor_function_acme_act(fn_actor_t * actor)
{
  fn_actor_acme_data_t * data = actor->data;

  fn_hero_t * hero = fn_level_get_hero(actor->level);

  switch(data->counter) {
    case 0:
      if (fn_hero_get_x(hero) >= actor->x / FN_HALFTILE_WIDTH &&
        fn_hero_get_x(hero) <= (actor->x / FN_HALFTILE_WIDTH)+2 &&
        fn_hero_get_y(hero) >= actor->y / FN_HALFTILE_HEIGHT)
      {
        data->counter++;
      }
      break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
      actor->y++;
      data->counter++;
      break;
    case 2:
    case 4:
    case 6:
    case 8:
    case 10:
      actor->y--;
      data->counter++;
      break;
    default:
      if (fn_level_is_solid(actor->level,
            actor->x / FN_TILE_WIDTH,
            (actor->y / FN_TILE_HEIGHT) + 1))
      {
        fn_level_add_actor(actor->level,
            FN_ACTOR_STEAM, actor->x + FN_HALFTILE_WIDTH, actor->y);
        /* TODO make particles */
        actor->is_alive = 0;
      } else {
        actor->y += FN_TILE_HEIGHT;
      }
      break;
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_acme_blit(fn_actor_t * actor)
{
  fn_actor_acme_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * tile = fn_tilecache_get_tile(tc,
      data->tile);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);

  tile = fn_tilecache_get_tile(tc, data->tile+1);
  destrect.x += FN_TILE_WIDTH * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_actor_function_acme_shot(fn_actor_t * actor)
{
  fn_actor_acme_data_t * data = actor->data;

  if (data->counter > 0) {
    fn_hero_t * hero = fn_level_get_hero(actor->level);

    fn_hero_add_score(hero, 500);
    fn_level_add_actor(actor->level,
        FN_ACTOR_SCORE_500, actor->x, actor->y);
    actor->is_alive = 0;
    /* TODO add particles */
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_acme_hero_touch_start(fn_actor_t * actor)
{
  fn_actor_acme_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  if (data->counter > 10 && !data->touching_hero) {
    data->touching_hero = 1;
    fn_hero_increase_hurting_objects(hero);
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef enum fn_actor_fire_state_e {
  fn_actor_fire_state_off,
  fn_actor_fire_state_ignition,
  fn_actor_fire_state_burning
} fn_actor_fire_state_e;

/* --------------------------------------------------------------- */

/**
 * The burning fire.
 */
typedef struct fn_actor_fire_data_t {
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
  fn_actor_fire_state_e state;
  /**
   * Counter for animation.
   */
  Uint8 counter;
  /**
   * Flag indicating if the hero is currently being touched.
   */
  Uint8 touching_hero;
} fn_actor_fire_data_t;

/* --------------------------------------------------------------- */

void fn_actor_function_fire_create(fn_actor_t * actor)
{
  fn_actor_fire_data_t * data = malloc(
      sizeof(fn_actor_fire_data_t));
  actor->data = data;

  actor->w = FN_TILE_WIDTH * 3;
  actor->h = FN_TILE_HEIGHT;

  if (actor->type == FN_ACTOR_FIRE_RIGHT) {
    data->tile = OBJ_FIRERIGHT;
    data->direction = fn_horizontal_direction_right;
  } else {
    data->tile = OBJ_FIRELEFT;
    data->direction = fn_horizontal_direction_left;
    actor->x -= 2 * FN_TILE_WIDTH;
  }
  data->counter = 0;
  data->state = fn_actor_fire_state_off;
  data->touching_hero = 0;
  actor->is_in_foreground = 1;
}

/* --------------------------------------------------------------- */

void fn_actor_function_fire_free(fn_actor_t * actor)
{
  fn_actor_fire_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_actor_function_fire_hero_touch_start(fn_actor_t * actor)
{
  fn_actor_fire_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  data->touching_hero = 1;

  if (data->state == fn_actor_fire_state_burning) {
    fn_hero_increase_hurting_objects(hero);
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_fire_hero_touch_end(fn_actor_t * actor)
{
  fn_actor_fire_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  data->touching_hero = 0;

  if (data->state == fn_actor_fire_state_burning) {
    fn_hero_decrease_hurting_objects(hero);
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_fire_act(fn_actor_t * actor)
{
  fn_actor_fire_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  switch(data->state)
  {
    case fn_actor_fire_state_off:
      if (data->counter == 40) {
        data->counter = 0;
        data->state = fn_actor_fire_state_ignition;
      }
      break;
    case fn_actor_fire_state_ignition:
      if (data->counter == 20) {
        data->counter = 0;
        data->state = fn_actor_fire_state_burning;
        if (data->touching_hero) {
          fn_hero_increase_hurting_objects(hero);
        }
      }
      break;
    case fn_actor_fire_state_burning:
      if (data->counter == 20) {
        data->counter = 0;
        data->state = fn_actor_fire_state_off;
        if (data->touching_hero) {
          fn_hero_decrease_hurting_objects(hero);
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

void fn_actor_function_fire_blit(fn_actor_t * actor)
{
  fn_actor_fire_data_t * data = actor->data;
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * tile0 = NULL;
  SDL_Surface * tile1 = NULL;
  SDL_Surface * tile2 = NULL;

  switch(data->state)
  {
    case fn_actor_fire_state_off:
      break;
    case fn_actor_fire_state_ignition:
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
    case fn_actor_fire_state_burning:
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
  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;
  SDL_BlitSurface(tile0, NULL, target, &destrect);
  destrect.x += FN_TILE_WIDTH * pixelsize;
  SDL_BlitSurface(tile1, NULL, target, &destrect);
  destrect.x += FN_TILE_WIDTH * pixelsize;
  SDL_BlitSurface(tile2, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The accesscard slot.
 */
typedef struct fn_actor_acces_card_slot_data_t {
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
} fn_actor_access_card_slot_data_t;

/* --------------------------------------------------------------- */

/**
 * Create an accesscard slot.
 *
 * @param  actor  The accesscard slot actor.
 */
void fn_actor_function_accesscard_slot_create(fn_actor_t * actor)
{
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  fn_actor_access_card_slot_data_t * data = malloc(
      sizeof(fn_actor_access_card_slot_data_t));
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
void fn_actor_function_accesscard_slot_free(fn_actor_t * actor)
{
  fn_actor_access_card_slot_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Interact with an accesscard slot.
 *
 * @param  actor  The accesscard slot actor.
 */
void fn_actor_function_accesscard_slot_interact_start(fn_actor_t * actor)
{
  fn_actor_access_card_slot_data_t * data = actor->data;
  fn_level_t * level = actor->level;
  fn_hero_t * hero = fn_level_get_hero(level);
  Uint8 inventory = fn_hero_get_inventory(hero);

  if (inventory & FN_INVENTORY_ACCESS_CARD) {
    GList * iter = NULL;
    for (iter = g_list_first(actor->level->actors);
        iter != NULL;
        iter = g_list_next(iter)) {
      fn_actor_t * dooractor = (fn_actor_t *)iter->data;

      if (dooractor->type == FN_ACTOR_ACCESS_CARD_DOOR) {
        dooractor->is_alive = 0;
        int x = dooractor->x / FN_TILE_WIDTH;
        int y = dooractor->y / FN_TILE_HEIGHT;
        fn_level_set_solid(level, x, y, 0);
      }
    }
    data->current_frame = 0;
    data->num_frames = 1;
    data->tile = OBJ_ACCESS_CARD_SLOT + 8;
    inventory &= ~FN_INVENTORY_ACCESS_CARD;
    fn_hero_set_inventory(hero, inventory);
  } else {
    Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
    fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
    SDL_Surface * screen = actor->level->screen;

    fn_infobox_show(pixelsize, tc, screen,
        "You don't have the access card\n");
  }
}

/* --------------------------------------------------------------- */

/**
 * Let the accesscard slot act.
 *
 * @param  actor  The accesscard slot actor.
 */
void fn_actor_function_accesscard_slot_act(fn_actor_t * actor)
{
  fn_actor_access_card_slot_data_t * data = actor->data;
  data->current_frame++;
  data->current_frame %= data->num_frames;
}

/* --------------------------------------------------------------- */

/**
 * Blit the accesscard slot.
 *
 * @param  actor  The accesscard slot actor.
 */
void fn_actor_function_accesscard_slot_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_actor_access_card_slot_data_t * data = actor->data;
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
  actor->is_in_foreground = 0;
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
    case FN_ACTOR_SODA:
      data->tile = ANIM_SODA;
      data->current_frame = 0;
      data->num_frames = 4;
      break;
    case FN_ACTOR_BOOTS:
      data->tile = OBJ_BOOT;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_GUN:
      data->tile = OBJ_GUN;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_FULL_LIFE:
      data->tile = OBJ_NUCLEARMOLECULE;
      data->current_frame = 0;
      data->num_frames = 8;
      break;
    case FN_ACTOR_CHICKEN_SINGLE:
      data->tile = OBJ_CHICKEN_SINGLE;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_CHICKEN_DOUBLE:
      data->tile = OBJ_CHICKEN_DOUBLE;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_LETTER_D:
      data->tile = OBJ_LETTER_D;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_LETTER_U:
      data->tile = OBJ_LETTER_U;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_LETTER_K:
      data->tile = OBJ_LETTER_K;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_LETTER_E:
      data->tile = OBJ_LETTER_E;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_ACCESS_CARD:
      data->tile = OBJ_ACCESS_CARD;
      data->current_frame = 0;
      data->num_frames = 1;
      break;
    case FN_ACTOR_GLOVE:
      data->tile = OBJ_ROBOHAND;
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
  Uint8 inventory = fn_hero_get_inventory(hero);
  Uint8 health = fn_hero_get_health(hero);
  Uint8 firepower = fn_hero_get_firepower(hero);
  switch(actor->type) {
    case FN_ACTOR_LETTER_D:
      fn_hero_set_fetched_letter(hero, 'D');
      actor->is_alive = 0;
      fn_hero_add_score(hero, 500);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_500, actor->x, actor->y);
      break;
    case FN_ACTOR_LETTER_U:
      if (fn_hero_get_fetched_letter(hero) == 'D') {
        fn_hero_set_fetched_letter(hero, 'U');
      } else {
        fn_hero_set_fetched_letter(hero, 0);
      }
      actor->is_alive = 0;
      fn_hero_add_score(hero, 500);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_500, actor->x, actor->y);
      break;
    case FN_ACTOR_LETTER_K:
      if (fn_hero_get_fetched_letter(hero) == 'U') {
        fn_hero_set_fetched_letter(hero, 'K');
      } else {
        fn_hero_set_fetched_letter(hero, 0);
      }
      actor->is_alive = 0;
      fn_hero_add_score(hero, 500);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_500, actor->x, actor->y);
      break;
    case FN_ACTOR_LETTER_E:
      if (fn_hero_get_fetched_letter(hero) == 'K') {
      fn_hero_add_score(hero, 10000);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_10000, actor->x, actor->y);
      } else {
      fn_hero_add_score(hero, 500);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_500, actor->x, actor->y);
      }
      actor->is_alive = 0;
      break;
    case FN_ACTOR_FULL_LIFE:
      health = 8;
      fn_hero_set_health(hero, health);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_1000, actor->x, actor->y);
      break;
    case FN_ACTOR_GUN:
      firepower++;
      fn_hero_set_firepower(hero, firepower);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_1000, actor->x, actor->y);
      break;
    case FN_ACTOR_ACCESS_CARD:
      inventory |= FN_INVENTORY_ACCESS_CARD;
      fn_hero_set_inventory(hero, inventory);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_1000, actor->x, actor->y);
      break;
    case FN_ACTOR_GLOVE:
      inventory |= FN_INVENTORY_ROBOHAND;
      fn_hero_set_inventory(hero, inventory);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_1000, actor->x, actor->y);
      break;
    case FN_ACTOR_BOOTS:
      inventory |= FN_INVENTORY_BOOT;
      fn_hero_set_inventory(hero, inventory);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_1000, actor->x, actor->y);
      break;
    case FN_ACTOR_CLAMPS:
      inventory |= FN_INVENTORY_CLAMP;
      fn_hero_set_inventory(hero, inventory);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 1000);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_1000, actor->x, actor->y);
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
    case FN_ACTOR_SODA:
      fn_hero_improve_health(hero, 1);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 200);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_200, actor->x, actor->y);
      break;
    case FN_ACTOR_CHICKEN_SINGLE:
      fn_hero_improve_health(hero, 1);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 100);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_100, actor->x, actor->y);
      break;
    case FN_ACTOR_CHICKEN_DOUBLE:
      fn_hero_improve_health(hero, 2);
      actor->is_alive = 0;
      fn_hero_add_score(hero, 200);
      fn_level_add_actor(actor->level,
          FN_ACTOR_SCORE_200, actor->x, actor->y);
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
 * @param  actor  The item actor.
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

/**
 * An item gets shot.
 *
 * @param  actor  The item actor.
 */
void fn_actor_function_item_shot(fn_actor_t * actor)
{
  fn_level_t * lv = actor->level;
  switch(actor->type) {
    case FN_ACTOR_BOX_BLUE_FOOTBALL:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_FOOTBALL, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_BLUE_JOYSTICK:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_JOYSTICK, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_BLUE_DISK:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_DISK, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_BLUE_BALLOON:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_BALLOON,
            actor->x, actor->y - FN_TILE_HEIGHT));
      break;
    case FN_ACTOR_BOX_BLUE_FLAG:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_FLAG, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_BLUE_RADIO:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_RADIO, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_RED_SODA:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_SODA, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_RED_CHICKEN:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_CHICKEN_SINGLE, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_EMPTY:
      actor->is_alive = 0;
      break;
    case FN_ACTOR_BOX_GREY_BOOTS:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_BOOTS, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_CLAMPS:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_CLAMPS, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_GUN:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_GUN, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_BOMB:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_BOMB, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_GLOVE:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_GLOVE, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_FULL_LIFE:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_FULL_LIFE, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_ACCESS_CARD:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_ACCESS_CARD, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_LETTER_D:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_LETTER_D, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_LETTER_U:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_LETTER_U, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_LETTER_K:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_LETTER_K, actor->x, actor->y));
      break;
    case FN_ACTOR_BOX_GREY_LETTER_E:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_LETTER_E, actor->x, actor->y));
      break;
    case FN_ACTOR_CHICKEN_SINGLE:
      actor->is_alive = 0;
      lv->actors = g_list_append(lv->actors,
          fn_actor_create(lv,
            FN_ACTOR_CHICKEN_DOUBLE, actor->x, actor->y));
      break;
    default:
      break;
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The balloon struct.
 */
typedef struct fn_actor_balloon_data_t {
  /**
   * A flag indicating if the balloon was destroyed.
   */
  Uint8 destroyed;
  /**
   * The current frame number for the cord animation.
   */
  Uint8 current_frame;
} fn_actor_balloon_data_t;

/* --------------------------------------------------------------- */

void fn_actor_function_balloon_create(fn_actor_t * actor)
{
  fn_actor_balloon_data_t * data =
    malloc(sizeof(fn_actor_balloon_data_t));
  actor->data = data;
  data->destroyed = 0;
  data->current_frame = 0;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT * 2;
}

/* --------------------------------------------------------------- */

void fn_actor_function_balloon_free(fn_actor_t * actor)
{
  fn_actor_balloon_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

void fn_actor_function_balloon_touch_start(fn_actor_t * actor)
{
  fn_actor_balloon_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (!data->destroyed) {
    actor->is_alive = 0;
    fn_hero_add_score(hero, 10000);
    fn_level_add_actor(actor->level,
        FN_ACTOR_SCORE_10000, actor->x, actor->y);
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_balloon_act(fn_actor_t * actor)
{
  fn_actor_balloon_data_t * data = actor->data;
  fn_level_t * level = actor->level;

  data->current_frame++;
  data->current_frame %= 9;
  if (data->destroyed) {
    actor->is_alive = 0;
  } else {
    actor->y--;
    if (
        /* balloon bumps against wall */
        fn_level_is_solid(level,
          (actor->x) / FN_TILE_WIDTH,
          (actor->y -1) / FN_TILE_HEIGHT)
       )
    {
      data->destroyed = 1;
      fn_level_add_actor(level,
          FN_ACTOR_STEAM, actor->x, actor->y);
    }
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_balloon_blit(fn_actor_t * actor)
{
  fn_actor_balloon_data_t * data = actor->data;

  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * tile;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;

  if (data->destroyed) {
    tile = fn_tilecache_get_tile(tc, OBJ_BALLOON + 4);
  } else {
    tile = fn_tilecache_get_tile(tc, OBJ_BALLOON);
  }
  SDL_BlitSurface(tile, NULL, target, &destrect);

  destrect.y += FN_TILE_HEIGHT * pixelsize;

  tile = fn_tilecache_get_tile(tc,
      OBJ_BALLOON + 1 + data->current_frame / 3);
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

void fn_actor_function_balloon_shot(fn_actor_t * actor)
{
  fn_actor_balloon_data_t * data = actor->data;
  fn_level_t * level = actor->level;
  data->destroyed = 1;
  fn_level_add_actor(level,
      FN_ACTOR_STEAM, actor->x, actor->y);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Create a teleporter.
 *
 * @param  actor  The teleporter actor.
 */
void fn_actor_function_teleporter_create(fn_actor_t * actor)
{
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 1;
}

/* --------------------------------------------------------------- */

/**
 * Interact with a teleporter.
 *
 * @param  actor  The teleporter actor.
 */
void fn_actor_function_teleporter_interact_start(fn_actor_t * actor)
{
  fn_actor_type_e othertype;
  if (actor->type == FN_ACTOR_TELEPORTER1) {
    othertype = FN_ACTOR_TELEPORTER2;
  } else {
    othertype = FN_ACTOR_TELEPORTER1;
  }
  fn_level_t * level = actor->level;

  GList * iter = NULL;
  for (iter = g_list_first(level->actors);
      iter != NULL;
      iter = g_list_next(iter)) {
    fn_actor_t * otheractor = (fn_actor_t *)iter->data;
    if (otheractor->type == othertype) {
      fn_hero_t * hero = fn_level_get_hero(actor->level);
      fn_hero_replace(hero,
          otheractor->x / FN_HALFTILE_WIDTH,
          otheractor->y / FN_HALFTILE_HEIGHT);
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
void fn_actor_function_teleporter_act(fn_actor_t * actor)
{
}

/* --------------------------------------------------------------- */

/**
 * Blit a teleporter.
 *
 * @param  actor  The teleporter actor.
 */
void fn_actor_function_teleporter_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * tile;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;

  int i = 0;
  for (i = 0; i < 3; i++) {
    int j = 0;
    for (j = 0; j < 3; j++) {
      destrect.x = (actor->x - (1 - j) * FN_TILE_WIDTH) * pixelsize;
      destrect.y = (actor->y - (2 - i) * FN_TILE_HEIGHT) * pixelsize;
      tile = fn_tilecache_get_tile(tc,
          ANIM_TELEPORTER1 + i * 3 + j
          );
      SDL_BlitSurface(tile, NULL, target, &destrect);
    }
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Singleanimation data struct.
 */
typedef struct fn_actor_singleanimation_data_t {
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
} fn_actor_singleanimation_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a singleanimation.
 *
 * @param  actor  The singleanimation actor.
 */
void fn_actor_function_singleanimation_create(fn_actor_t * actor)
{
  fn_actor_singleanimation_data_t * data = malloc(
      sizeof(fn_actor_singleanimation_data_t));

  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 1;

  switch(actor->type) {
    case FN_ACTOR_FIRE:
      data->tile = ANIM_BOMBFIRE;
      data->current_frame = 0;
      data->num_frames = 6;
      break;
    case FN_ACTOR_DUSTCLOUD:
      data->tile = OBJ_DUST;
      data->current_frame = 0;
      data->num_frames = 5;
      break;
    case FN_ACTOR_STEAM:
      data->tile = OBJ_STEAM;
      data->current_frame = 0;
      data->num_frames = 5;
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
void fn_actor_function_singleanimation_free(fn_actor_t * actor)
{
  fn_actor_singleanimation_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Act a singleanimation.
 *
 * @param  actor  The singleanimation actor.
 */
void fn_actor_function_singleanimation_act(fn_actor_t * actor)
{
  fn_actor_singleanimation_data_t * data = actor->data;

  data->current_frame++;
  if (data->current_frame == data->num_frames) {
    actor->is_alive = 0;
  }
}

/* --------------------------------------------------------------- */

/**
 * Blit an singleanimation.
 *
 * @param  actor  The singleanimation actor.
 */
void fn_actor_function_singleanimation_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_actor_singleanimation_data_t * data = actor->data;
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
 * Explosion data struct.
 */
typedef struct fn_actor_explosion_data_t {
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
} fn_actor_explosion_data_t;

/* --------------------------------------------------------------- */

/**
 * Create an explosion.
 *
 * @param  actor  The explosion actor.
 */
void fn_actor_function_explosion_create(fn_actor_t * actor)
{
  fn_actor_explosion_data_t * data = malloc(
      sizeof(fn_actor_explosion_data_t));

  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
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
void fn_actor_function_explosion_free(fn_actor_t * actor)
{
  fn_actor_explosion_data_t * data = actor->data;
  free(data); actor->data = NULL; data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Act an explosion.
 *
 * @param  actor  The explosion actor.
 */
void fn_actor_function_explosion_act(fn_actor_t * actor)
{
  fn_actor_explosion_data_t * data = actor->data;

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
void fn_actor_function_explosion_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_actor_explosion_data_t * data = actor->data;
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
 * Create a camera.
 *
 * @param  actor  The camera actor.
 */
void fn_actor_function_camera_create(fn_actor_t * actor)
{
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 0;
}

/**
 * Blit the camera.
 *
 * @param  actor  The camera actor.
 */
void fn_actor_function_camera_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * tile;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  size_t x = fn_hero_get_x(hero) * FN_HALFTILE_WIDTH;
  if (x-1 > actor->x) {
    tile = fn_tilecache_get_tile(tc,
        ANIM_CAMERA_RIGHT);
  } else if (x+1 < actor->x) {
    tile = fn_tilecache_get_tile(tc,
        ANIM_CAMERA_LEFT);
  } else {
    tile = fn_tilecache_get_tile(tc,
        ANIM_CAMERA_CENTER);
  }
  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

/**
 * A camera gets shot.
 *
 * @param  actor  The camera actor.
 */
void fn_actor_function_camera_shot(fn_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  actor->is_alive = 0;
  fn_hero_add_score(hero, 100);
  fn_level_add_actor(actor->level,
      FN_ACTOR_SCORE_100, actor->x, actor->y);
  fn_level_add_actor(actor->level,
      FN_ACTOR_EXPLOSION, actor->x, actor->y);
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
  actor->is_in_foreground = 1;
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

typedef struct fn_actor_unstablefloor_data_t {
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
} fn_actor_unstablefloor_data_t;

/* --------------------------------------------------------------- */

void fn_actor_function_unstablefloor_create(fn_actor_t * actor)
{
  fn_actor_unstablefloor_data_t * data = malloc(
      sizeof(fn_actor_unstablefloor_data_t));
  actor->data = data;
  data->tile = SOLID_START + 77;
  data->touched = 0;
  data->touching = 0;
  actor->w = 0;
  actor->h = 0;
}

/* --------------------------------------------------------------- */

void fn_actor_function_unstablefloor_free(fn_actor_t * actor)
{
  fn_actor_unstablefloor_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

void fn_actor_function_unstablefloor_touch_start(fn_actor_t * actor)
{
  fn_actor_unstablefloor_data_t * data = actor->data;
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  if (fn_hero_get_x(hero) * FN_HALFTILE_WIDTH >=
      actor->x &&
      fn_hero_get_x(hero) * FN_HALFTILE_WIDTH <
      actor->x + actor->w) {

    if (!data->touched) {
      data->touching = 1;
    } else {
      /* TODO let the floor crash away. */
      actor->is_alive = 0;
      /* TODO set the floor unsolid */
    }
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_unstablefloor_touch_end(fn_actor_t * actor)
{
  fn_actor_unstablefloor_data_t * data = actor->data;
  if (data->touching) {
    data->touching = 0;
    data->touched = 1;
  }
}

/* --------------------------------------------------------------- */

void fn_actor_function_unstablefloor_act(fn_actor_t * actor)
{
  fn_actor_unstablefloor_data_t * data = actor->data;
  fn_level_t * level = actor->level;
  fn_hero_t * hero = fn_level_get_hero(actor->level);

  Uint8 floorlength = 0;

  /*
   * postponed initialization because when floor is created,
   * the necessary information is not yet loaded from the level.
   */
  if (actor->w == 0) {
    while (!fn_level_is_solid(level,
          actor->x / FN_TILE_WIDTH + floorlength,
          actor->y / FN_TILE_HEIGHT))
    {
      fn_level_set_solid(level,
          actor->x / FN_TILE_WIDTH + floorlength,
          actor->y / FN_TILE_HEIGHT,
          1);
      floorlength++;
    }
    actor->w = floorlength * FN_TILE_WIDTH;
    actor->h = FN_TILE_HEIGHT;
  }

  if (
      /* hero is right of leftend */
      fn_hero_get_x(hero) * FN_HALFTILE_WIDTH >=
      actor->x &&
      /* hero is left of rightend */
      fn_hero_get_x(hero) * FN_HALFTILE_WIDTH <
      actor->x + actor->w &&
      /* hero is directly above floor */
      (fn_hero_get_y(hero) + 2) * FN_HALFTILE_HEIGHT ==
      actor->y)
  {
    if (data->touched) {
      /* TODO make particles fly. */
      floorlength = 0;
      while (floorlength < actor->w / FN_TILE_WIDTH) {
        fn_level_set_solid(level,
            actor->x / FN_TILE_WIDTH + floorlength,
            actor->y / FN_TILE_HEIGHT,
            0);
        if (floorlength % 2 == 1) {
          
        }
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

void fn_actor_function_unstablefloor_blit(fn_actor_t * actor)
{
  fn_actor_unstablefloor_data_t * data = actor->data;
  
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * tile = NULL;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;

  int i = 0;
  for (i = 0; i < (actor->w / FN_TILE_WIDTH); i++) {
    tile = fn_tilecache_get_tile(tc,
        data->tile + i % 2);
    SDL_BlitSurface(tile, NULL, target, &destrect);
    destrect.x += FN_TILE_WIDTH * pixelsize;
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

void fn_actor_function_surveillancescreen_create(fn_actor_t * actor)
{
  actor->w = FN_TILE_WIDTH * 2;
  actor->h = FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

void fn_actor_function_surveillancescreen_free(fn_actor_t * actor)
{
}

/* --------------------------------------------------------------- */

void fn_actor_function_surveillancescreen_interact_start(
    fn_actor_t * actor)
{
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * screen = actor->level->screen;

  /* TODO show real note instead of this dummy */
  fn_infobox_show(pixelsize, tc, screen, "Not implemented yet.\n");
}

/* --------------------------------------------------------------- */

void fn_actor_function_surveillancescreen_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  SDL_Surface * tile = NULL;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;

  tile = fn_tilecache_get_tile(tc, ANIM_BADGUYSCREEN);
  SDL_BlitSurface(tile, NULL, target, &destrect);

  destrect.x += FN_TILE_WIDTH * pixelsize;
  tile = fn_tilecache_get_tile(tc, ANIM_BADGUYSCREEN + 1);
  SDL_BlitSurface(tile, NULL, target, &destrect);
}


/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

void fn_actor_function_notebook_create(fn_actor_t * actor)
{
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
}

/* --------------------------------------------------------------- */

void fn_actor_function_notebook_free(fn_actor_t * actor)
{
}

/* --------------------------------------------------------------- */

void fn_actor_function_notebook_interact_start(fn_actor_t * actor)
{
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * screen = actor->level->screen;

  /* TODO show real note instead of this dummy */
  fn_infobox_show(pixelsize, tc, screen, "Not implemented yet.\n");
}

/* --------------------------------------------------------------- */

void fn_actor_function_notebook_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  SDL_Surface * tile = NULL;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;

  tile = fn_tilecache_get_tile(tc, OBJ_NOTE);
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The exitdoor struct.
 */
typedef struct fn_actor_exitdoor_data_t {
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
} fn_actor_exitdoor_data_t;

/* --------------------------------------------------------------- */

/**
 * Create an exit door.
 *
 * @param  actor  The door actor.
 */
void fn_actor_function_exitdoor_create(fn_actor_t * actor)
{
  fn_actor_exitdoor_data_t * data = malloc(
      sizeof(fn_actor_exitdoor_data_t));
  actor->data = data;
  actor->w = FN_TILE_WIDTH * 2;
  actor->h = FN_TILE_HEIGHT * 2;
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
void fn_actor_function_exitdoor_free(fn_actor_t * actor)
{
  fn_actor_exitdoor_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Interaction of hero with exit door.
 *
 * @param  actor  The exitdoor actor.
 */
void fn_actor_function_exitdoor_interact_start(fn_actor_t * actor)
{
  fn_actor_exitdoor_data_t * data = actor->data;
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
void fn_actor_function_exitdoor_act(fn_actor_t * actor)
{
  fn_actor_exitdoor_data_t * data = actor->data;
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
void fn_actor_function_exitdoor_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_actor_exitdoor_data_t * data = actor->data;
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = 0;
  destrect.y = 0;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;

  SDL_Surface * tile = SDL_CreateRGBSurface(
      FN_SURFACE_FLAGS,
      actor->w * pixelsize,
      actor->h * pixelsize,
      FN_COLOR_DEPTH,
      0,
      0,
      0,
      0);
  SDL_Surface * part = fn_tilecache_get_tile(tc,
      data->tile + data->counter * 4);
  SDL_BlitSurface(part, NULL, tile, &destrect);

  destrect.x += pixelsize * FN_TILE_WIDTH;
  part = fn_tilecache_get_tile(tc,
    data->tile + data->counter * 4 + 1);
  SDL_BlitSurface(part, NULL, tile, &destrect);

  destrect.x = 0;
  destrect.y += pixelsize * FN_TILE_HEIGHT;
  part = fn_tilecache_get_tile(tc,
    data->tile + data->counter * 4 + 2);
  SDL_BlitSurface(part, NULL, tile, &destrect);

  destrect.x += pixelsize * FN_TILE_WIDTH;
  part = fn_tilecache_get_tile(tc,
    data->tile + data->counter * 4 + 3);
  SDL_BlitSurface(part, NULL, tile, &destrect);


  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;
  SDL_BlitSurface(tile, NULL, target, &destrect);

  SDL_FreeSurface(tile); tile = NULL;
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * The door struct.
 */
typedef struct fn_actor_door_data_t {
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
} fn_actor_door_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a door.
 *
 * @param  actor  The door actor.
 */
void fn_actor_function_door_create(fn_actor_t * actor)
{
  fn_actor_door_data_t * data = malloc(
      sizeof(fn_actor_door_data_t));
  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
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
void fn_actor_function_door_free(fn_actor_t * actor)
{
  fn_actor_door_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Action for door.
 * 
 * @param  actor  The door actor.
 */
void fn_actor_function_door_act(fn_actor_t * actor)
{
  fn_level_t * level = actor->level;
  fn_actor_door_data_t * data = actor->data;

  switch(data->state) {
    case 0: /* idle */
      break;
    case 1: /* door opening */
      if (data->counter == 0) {
        fn_level_set_solid(level,
            actor->x / FN_TILE_WIDTH,
            actor->y / FN_TILE_HEIGHT,
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
void fn_actor_function_door_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_actor_door_data_t * data = actor->data;
  SDL_Surface * tile = fn_tilecache_get_tile(tc,
      data->tile + data->counter);
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
 * The keyhole struct.
 */
typedef struct fn_actor_keyhole_data_t {
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
} fn_actor_keyhole_data_t;

/* --------------------------------------------------------------- */

/**
 * Create a keyhole.
 *
 * @param  actor  The keyhole actor.
 */
void fn_actor_function_keyhole_create(fn_actor_t * actor)
{
  fn_actor_keyhole_data_t * data = malloc(
      sizeof(fn_actor_keyhole_data_t));
  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
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
void fn_actor_function_keyhole_free(fn_actor_t * actor)
{
  fn_actor_keyhole_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Action for keyhole.
 * 
 * @param  actor  The keyhole actor.
 */
void fn_actor_function_keyhole_act(fn_actor_t * actor)
{
  fn_actor_keyhole_data_t * data = actor->data;

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
void fn_actor_function_keyhole_blit(fn_actor_t * actor)
{
  fn_actor_keyhole_data_t * data = actor->data;
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  SDL_Surface * tile = fn_tilecache_get_tile(tc,
      data->tile);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  if (data->counter > 1) {
    switch(actor->type) {
      case FN_ACTOR_KEYHOLE_RED:
        tile = fn_tilecache_get_tile(tc, OBJ_KEYHOLE_RED);
        break;
      case FN_ACTOR_KEYHOLE_BLUE:
        tile = fn_tilecache_get_tile(tc, OBJ_KEYHOLE_BLUE);
        break;
      case FN_ACTOR_KEYHOLE_PINK:
        tile = fn_tilecache_get_tile(tc, OBJ_KEYHOLE_PINK);
        break;
      case FN_ACTOR_KEYHOLE_GREEN:
        tile = fn_tilecache_get_tile(tc, OBJ_KEYHOLE_GREEN);
        break;
      default:
        fn_error_print_commandline("Invalid keyhole actor");
    }
  }

  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;

  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

/**
 * Hero interacts with keyhole.
 *
 * @param  actor  The keyhole actor.
 */
void fn_actor_function_keyhole_interact_start(fn_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_actor_keyhole_data_t * data = actor->data;
  Uint8 inventory = fn_hero_get_inventory(hero);

  char msg[40];

  Uint8 haskey = 0;
  Uint8 needed_key = 0;
  fn_actor_type_e door_to_open;

  switch(actor->type) {
    case FN_ACTOR_KEYHOLE_RED:
      needed_key = FN_INVENTORY_KEY_RED;
      door_to_open = FN_ACTOR_DOOR_RED;
      snprintf(msg, 40, "You don't have the red key.\n");
      break;
    case FN_ACTOR_KEYHOLE_BLUE:
      needed_key = FN_INVENTORY_KEY_BLUE;
      door_to_open = FN_ACTOR_DOOR_BLUE;
      snprintf(msg, 40, "You don't have the blue key.\n");
      break;
    case FN_ACTOR_KEYHOLE_PINK:
      needed_key = FN_INVENTORY_KEY_PINK;
      door_to_open = FN_ACTOR_DOOR_PINK;
      snprintf(msg, 40, "You don't have the pink key.\n");
      break;
    case FN_ACTOR_KEYHOLE_GREEN:
      needed_key = FN_INVENTORY_KEY_GREEN;
      door_to_open = FN_ACTOR_DOOR_GREEN;
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
    GList * iter = NULL;
    for (iter = g_list_first(actor->level->actors);
        iter != NULL;
        iter = g_list_next(iter)) {
      fn_actor_t * dooractor = (fn_actor_t *)iter->data;

      if (dooractor->type == door_to_open) {
        fn_actor_door_data_t * doordata = dooractor->data;
        doordata->state = 1;
      }
    }
  } else if (data->counter != 5) {
    Uint8 pixelsize = fn_level_get_pixelsize(actor->level);
    fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
    SDL_Surface * screen = actor->level->screen;

    fn_infobox_show(pixelsize, tc, screen, msg);
  }
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Key actor creation function.
 *
 * @param  actor  The key actor.
 */
void fn_actor_function_key_create(fn_actor_t * actor)
{
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_WIDTH;
  actor->is_in_foreground = 0;
}


/* --------------------------------------------------------------- */

/**
 * The hero touches a key actor.
 *
 * @param  actor  The key actor.
 */
void fn_actor_function_key_touch_start(fn_actor_t * actor)
{
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
  fn_hero_add_score(hero, 1000);
  fn_level_add_actor(actor->level,
      FN_ACTOR_SCORE_1000, actor->x, actor->y);
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

/**
 * Create the shootable wall.
 *
 * @param  actor  The wall actor.
 */
void fn_actor_function_shootable_wall_create(fn_actor_t * actor)
{
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;
  actor->is_in_foreground = 0;
}

/* --------------------------------------------------------------- */

/**
 * Blit the shootable wall.
 *
 * @param  actor  The wall actor.
 */
void fn_actor_function_shootable_wall_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  SDL_Surface * tile = NULL;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  Uint8 pixelsize = fn_level_get_pixelsize(actor->level);

  destrect.x = actor->x * pixelsize;
  destrect.y = actor->y * pixelsize;
  destrect.w = actor->w * pixelsize;
  destrect.h = actor->h * pixelsize;

  tile = fn_tilecache_get_tile(tc, 0x8C0/0x20);
  SDL_BlitSurface(tile, NULL, target, &destrect);
  tile = fn_tilecache_get_tile(tc, 0x1800/0x20);
  SDL_BlitSurface(tile, NULL, target, &destrect);
}

/* --------------------------------------------------------------- */

/**
 * Shoot the shootable wall.
 *
 * @param  actor  The wall actor.
 */
void fn_actor_function_shootable_wall_shot(fn_actor_t * actor)
{
  fn_level_t * level = actor->level;
  fn_hero_t * hero = fn_level_get_hero(level);
  actor->is_alive = 0;
  fn_hero_add_score(hero, 10);
  fn_level_set_solid(level,
      actor->x / FN_TILE_WIDTH,
      actor->y / FN_TILE_HEIGHT,
      0);
  fn_level_add_actor(actor->level,
      FN_ACTOR_EXPLOSION, actor->x, actor->y);
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

typedef struct fn_actor_accesscard_door_data_t
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
} fn_actor_accesscard_door_data_t;

/**
 * Create an accesscard door.
 *
 * @param  actor  The accesscard door actor.
 */
void fn_actor_function_access_card_door_create(fn_actor_t * actor)
{
  fn_actor_accesscard_door_data_t * data = malloc(
      sizeof(fn_actor_accesscard_door_data_t));
  actor->data = data;
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_HEIGHT;

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
void fn_actor_function_access_card_door_free(fn_actor_t * actor)
{
  fn_actor_accesscard_door_data_t * data = actor->data;
  free(data); data = NULL; actor->data = NULL;
}

/* --------------------------------------------------------------- */

/**
 * Blit an accesscard door.
 *
 * @param  actor  The accesscard door actor.
 */
void fn_actor_function_access_card_door_blit(fn_actor_t * actor)
{
  SDL_Surface * target = fn_level_get_surface(actor->level);
  SDL_Rect destrect;
  fn_tilecache_t * tc = fn_level_get_tilecache(actor->level);
  fn_actor_accesscard_door_data_t * data = actor->data;
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
 * Act an accesscard door.
 *
 * @param  actor  The accesscard door actor.
 */
void fn_actor_function_access_card_door_act(fn_actor_t * actor)
{
  fn_actor_accesscard_door_data_t * data = actor->data;
  data->current_frame++;
  data->current_frame %= data->num_frames;
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/**
 * Spikes actor creation function.
 *
 * @param  actor  The spikes actor.
 */
void fn_actor_function_spikes_create(fn_actor_t * actor)
{
  actor->w = FN_TILE_WIDTH;
  actor->h = FN_TILE_WIDTH;
  actor->is_in_foreground = 1;
}

/* --------------------------------------------------------------- */

/**
 * Hero touches spikes actor.
 *
 * @param  actor  The spikes actor.
 */
void fn_actor_function_spikes_touch_start(fn_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_increase_hurting_objects(hero);
}

/* --------------------------------------------------------------- */

/**
 * Hero stops to touch spikes actor.
 *
 * @param  actor  The spikes actor.
 */
void fn_actor_function_spikes_touch_end(fn_actor_t * actor)
{
  fn_hero_t * hero = fn_level_get_hero(actor->level);
  fn_hero_decrease_hurting_objects(hero);
}

/* --------------------------------------------------------------- */

/**
 * Blit the spikes.
 *
 * @param  actor  The spikes actor.
 */
void fn_actor_function_spikes_blit(fn_actor_t * actor)
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
    case FN_ACTOR_SPIKES_UP:
      tile = fn_tilecache_get_tile(tc, OBJ_SPIKES_UP);
      break;
    case FN_ACTOR_SPIKES_DOWN:
      tile = fn_tilecache_get_tile(tc, OBJ_SPIKES_DOWN);
      break;
    case FN_ACTOR_SPIKE:
      tile = fn_tilecache_get_tile(tc, OBJ_SPIKE);
      /* TODO check if hero touches spike and print heavy spike */
      break;
    default:
      printf(__FILE__ ":%d: warning: spike #%d"
          " tried to blit which is not a spike\n",
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_ACTOR_REDBALL_JUMPING] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_redball_jumping_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_redball_jumping_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_redball_jumping_hero_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_redball_jumping_hero_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_redball_jumping_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_redball_jumping_blit,
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_redball_jumping_shot,
  },
  [FN_ACTOR_REDBALL_LYING] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_redball_lying_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_redball_lying_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_redball_lying_hero_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_redball_lying_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_redball_lying_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_ROBOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_robot_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_robot_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_robot_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_robot_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_robot_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_robot_blit,
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_robot_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_ACTOR_WALLCRAWLERBOT_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_wallcrawler_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_wallcrawler_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_wallcrawler_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_wallcrawler_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_wallcrawler_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_wallcrawler_blit,
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_wallcrawler_shot,
  },
  [FN_ACTOR_WALLCRAWLERBOT_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_wallcrawler_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_wallcrawler_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_wallcrawler_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_wallcrawler_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_wallcrawler_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_wallcrawler_blit,
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_wallcrawler_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_ACTOR_CAMERA] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_camera_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_camera_blit,
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_camera_shot,
  },
  [FN_ACTOR_EXPLOSION] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_explosion_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_explosion_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_explosion_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_explosion_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_FIRE] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_singleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_singleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_singleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_singleanimation_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_DUSTCLOUD] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_singleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_singleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_singleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_singleanimation_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_STEAM] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_singleanimation_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_singleanimation_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_singleanimation_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_singleanimation_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_ACTOR_EXITDOOR] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_exitdoor_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_exitdoor_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_exitdoor_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_exitdoor_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_exitdoor_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_NOTEBOOK] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_notebook_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_notebook_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_notebook_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_notebook_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_SURVEILLANCESCREEN] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_surveillancescreen_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_surveillancescreen_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_surveillancescreen_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_surveillancescreen_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_SODA] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_ACTOR_UNSTABLEFLOOR] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_unstablefloor_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_unstablefloor_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_unstablefloor_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_unstablefloor_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_ACTOR_BROKENWALL_BACKGROUND] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_ACTOR_TELEPORTER1] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_teleporter_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_teleporter_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_teleporter_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_teleporter_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_TELEPORTER2] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_teleporter_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_teleporter_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_teleporter_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_teleporter_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_ACTOR_STONEWINDOW_BACKGROUND] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_WINDOWLEFT_BACKGROUND] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_WINDOWRIGHT_BACKGROUND] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_BOOTS] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_CLAMPS] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_GUN] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_CHICKEN_SINGLE] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_CHICKEN_DOUBLE] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_BALLOON] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_balloon_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_balloon_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_balloon_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_balloon_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_balloon_blit,
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_balloon_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_GLOVE] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_FULL_LIFE] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_ACCESS_CARD] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_LETTER_D] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_LETTER_U] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_LETTER_K] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_item_shot,
  },
  [FN_ACTOR_LETTER_E] = {
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_ACCESS_CARD_SLOT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_accesscard_slot_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_accesscard_slot_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_accesscard_slot_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_accesscard_slot_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_accesscard_slot_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_KEY_RED] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_key_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_key_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_key_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_KEYHOLE_RED] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_keyhole_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_keyhole_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_keyhole_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_keyhole_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_keyhole_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_DOOR_RED] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_door_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_door_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_door_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_door_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_KEY_BLUE] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_key_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_key_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_key_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_KEYHOLE_BLUE] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_keyhole_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_keyhole_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_keyhole_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_keyhole_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_keyhole_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_DOOR_BLUE] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_door_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_door_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_door_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_door_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_KEY_PINK] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_key_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_key_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_key_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_KEYHOLE_PINK] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_keyhole_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_keyhole_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_keyhole_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_keyhole_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_keyhole_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_DOOR_PINK] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_door_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_door_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_door_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_door_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_KEY_GREEN] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_key_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_key_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_key_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_KEYHOLE_GREEN] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_keyhole_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_keyhole_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_keyhole_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_keyhole_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_keyhole_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_DOOR_GREEN] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_door_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_door_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_door_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_door_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_SHOOTABLE_WALL] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_shootable_wall_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_shootable_wall_blit,
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_shootable_wall_shot,
  },
  [FN_ACTOR_LIFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_lift_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_lift_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] =
      fn_actor_function_lift_interact_start,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   =
      fn_actor_function_lift_interact_end,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_lift_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_lift_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_ACME] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_acme_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_acme_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_acme_hero_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_acme_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_acme_blit,
    [FN_ACTOR_FUNCTION_SHOT]                =
      fn_actor_function_acme_shot,
  },
  [FN_ACTOR_FIRE_RIGHT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_fire_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_fire_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_fire_hero_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_fire_hero_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_fire_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_fire_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_FIRE_LEFT] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_fire_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_fire_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_fire_hero_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_fire_hero_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_fire_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_fire_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL, /* TODO */
  },
  [FN_ACTOR_ACCESS_CARD_DOOR] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_access_card_door_create,
    [FN_ACTOR_FUNCTION_FREE]                =
      fn_actor_function_access_card_door_free,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 =
      fn_actor_function_access_card_door_act,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_access_card_door_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_SPIKES_UP] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_spikes_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_spikes_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_spikes_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_spikes_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_SPIKES_DOWN] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_spikes_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_spikes_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_spikes_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_spikes_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
  },
  [FN_ACTOR_SPIKE] = {
    [FN_ACTOR_FUNCTION_CREATE]              =
      fn_actor_function_spikes_create,
    [FN_ACTOR_FUNCTION_FREE]                = NULL,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_START]    =
      fn_actor_function_spikes_touch_start,
    [FN_ACTOR_FUNCTION_HERO_TOUCH_END]      =
      fn_actor_function_spikes_touch_end,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_START] = NULL,
    [FN_ACTOR_FUNCTION_HERO_INTERACT_END]   = NULL,
    [FN_ACTOR_FUNCTION_ACT]                 = NULL,
    [FN_ACTOR_FUNCTION_BLIT]                =
      fn_actor_function_spikes_blit,
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
    [FN_ACTOR_FUNCTION_SHOT]                = NULL,
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
  actor->is_in_foreground = 0;
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
    (fn_hero_get_x(fn_level_get_hero(actor->level))) * FN_HALFTILE_WIDTH;
  Uint16 hero_y =
    (fn_hero_get_y(fn_level_get_hero(actor->level))-2)* FN_HALFTILE_HEIGHT;
  Uint16 hero_w = FN_TILE_WIDTH;
  Uint16 hero_h = FN_TILE_HEIGHT * 2;

  if ((hero_x + hero_w) <= (actor->x)) {
    /* hero is left of actor */
    return 0;
  }
  if ((hero_x) >= (actor->x + actor->w)) {
    /* hero is right of actor */
    return 0;
  }
  if ((hero_y + hero_h) <= (actor->y)) {
    /* hero is above actor */
    return 0;
  }
  if ((hero_y) >= (actor->y + actor->h)) {
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

Uint8 fn_actor_hero_can_interact(fn_actor_t * actor)
{
  if (actor->type == FN_ACTOR_LIFT) {
    /* This check needs to be done for lift only because
     * if there are two lifts next to each other, the mostleft
     * lift would be chosen for interaction instead of the one on
     * which the hero stands.
     */
    fn_hero_t * hero = fn_level_get_hero(actor->level);
    return (fn_hero_get_x(hero) * FN_HALFTILE_WIDTH == actor->x &&
        fn_hero_get_y(hero) * FN_HALFTILE_HEIGHT ==
        actor->y - FN_TILE_HEIGHT);
  }
  fn_actor_function_t func =
    fn_actor_functions[
    actor->type][FN_ACTOR_FUNCTION_HERO_INTERACT_START];
  return (func != NULL);
}

/* --------------------------------------------------------------- */

void fn_actor_hero_interact_start(fn_actor_t * actor)
{
  fn_actor_function_t func =
    fn_actor_functions[
    actor->type][FN_ACTOR_FUNCTION_HERO_INTERACT_START];
  if (func != NULL) {
    func(actor);
  }
}

/* --------------------------------------------------------------- */

void fn_actor_hero_interact_stop(fn_actor_t * actor)
{
  fn_actor_function_t func =
    fn_actor_functions[
    actor->type][FN_ACTOR_FUNCTION_HERO_INTERACT_END];
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

Uint8 fn_actor_shot(fn_actor_t * actor)
{
  fn_actor_function_t func =
    fn_actor_functions[actor->type][FN_ACTOR_FUNCTION_SHOT];
  if (func != NULL) {
    func(actor);
    return 1;
  }
  return 0;
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

Uint16 fn_actor_get_w(fn_actor_t * actor)
{
  return actor->w;
}

/* --------------------------------------------------------------- */

Uint16 fn_actor_get_h(fn_actor_t * actor)
{
  return actor->h;
}

/* --------------------------------------------------------------- */

Uint8 fn_actor_can_get_shot(fn_actor_t * actor)
{
  fn_actor_function_t func =
    fn_actor_functions[actor->type][FN_ACTOR_FUNCTION_SHOT];
  return (func != NULL);
}

/* --------------------------------------------------------------- */

Uint8 fn_actor_in_foreground(fn_actor_t * actor)
{
  return actor->is_in_foreground;
}
