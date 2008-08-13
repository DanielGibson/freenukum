/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Level functions
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

#ifndef FN_LEVEL_H
#define FN_LEVEL_H

/* --------------------------------------------------------------- */

typedef struct fn_level_t fn_level_t;

/* --------------------------------------------------------------- */

/*
 * includes below use fn_level_t this is why they are not
 * at the beginning of this file because fn_level_t is
 * not yet defined there.
 */
#include "fn_hero.h"
#include "fn_actor.h"
#include "fn_shot.h"
#include "fn_bot.h"
#include "fn_list.h"

/* --------------------------------------------------------------- */

/**
 * A struct representing a level.
 */
struct fn_level_t {
  /**
   * Stores our hero.
   */
  fn_hero_t * hero;

  /**
   * Stores the raw data loaded from the level.
   */
  Uint16 raw[FN_LEVEL_HEIGHT][FN_LEVEL_WIDTH];

  /**
   * Stores if tiles are solid or not.
   */
  Uint8 solid[FN_LEVEL_HEIGHT][FN_LEVEL_WIDTH];
  
  /**
   * The solid and background tiles.
   */
  Uint16 tiles[FN_LEVEL_HEIGHT][FN_LEVEL_WIDTH];

  /**
   * The surface for blitting the level.
   */
  SDL_Surface * surface;

  /**
   * The screen surface.
   */
  SDL_Surface * screen;

  /**
   * The pixel size.
   */
  Uint8 pixelsize;
  
  /**
   * The tile cache.
   */
  fn_tilecache_t * tilecache;

  /**
   * The actors inside the level.
   */
  fn_list_t * actors;

  /**
   * The shots inside the level.
   */
  fn_list_t * shots;

  /**
   * The number of shots currently in level.
   */
  Uint8 num_shots;

  /**
   * The bots
   * @TODO remove this (replaced by actors).
   */
  fn_list_t * bots;

  /**
   * As long as this is non-zero, we keep on playing.
   */
  int do_play;

  /**
   * The number of animated frames since last action.
   */
  size_t animated_frames;

  /**
   * Non-zero if the hero passed the level, otherwise zero.
   */
  int levelpassed;

  /**
   * The actor with which the hero interacts.
   */
  fn_actor_t * interactor;

  /**
   * Draw collision bounds for debugging.
   */
  Uint8 draw_collision_bounds;
};

/* --------------------------------------------------------------- */

/**
 * Load a level from a file.
 *
 * @param  fd  An already opened file descriptor to the level file.
 * @param  pixelsize  The size of a single pixel.
 * @param  tilecache  The tilecache from which to show the tiles.
 * @param  screen     The screen on which the level will be displayed.
 *
 * @return  The fully loaded level. If it was not possible to load
 *          the level, NULL is returned. Examine errno in order
 *          to find out what error occured.
 */
fn_level_t * fn_level_load(int fd,
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    SDL_Surface * screen,
    fn_hero_t * hero);

/* --------------------------------------------------------------- */

/**
 * Destroy a level.
 *
 * @param  level  The level to destroy.
 */
void fn_level_free(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Set a tile on a certain position inside the level.
 *
 * @param  lv    The level.
 * @param  x     The x coordinate.
 * @param  y     The y coordinate.
 * @param  tile  The tile number.
 */
void fn_level_set_tile(
    fn_level_t * lv,
    size_t x,
    size_t y,
    Uint16 tile);

/* --------------------------------------------------------------- */

/**
 * Get a tile from a certain position inside the level.
 *
 * @param  lv  The level.
 * @param  x   The x coordinate.
 * @param  y   The y coordinate.
 *
 * @return  The tile of the position.
 */
Uint16 fn_level_get_tile(fn_level_t * lv, size_t x, size_t y);

/* --------------------------------------------------------------- */

/**
 * Get the raw value of a certain position inside the level.
 *
 * @param  lv  The level.
 * @param  x   The x coordinate.
 * @param  y   The y coordinate.
 *
 * @return  The raw tile number of the position.
 */
Uint16 fn_level_get_raw(fn_level_t * lv, size_t x, size_t y);

/* --------------------------------------------------------------- */

/**
 * Get the information wether a tile is solid or not.
 *
 * @param  lv  The level.
 * @param  x   The x coordinate.
 * @param  y   The y coordinate.
 *
 * @return 1 if solid, else 0.
 */
Uint8 fn_level_is_solid(fn_level_t * lv, int x, int y);

/* --------------------------------------------------------------- */

/**
 * Set the information wether a tile is solid or not.
 *
 * @param  lv     The level.
 * @param  x      The x coordinate.
 * @param  y      The y coordinate.
 * @param  solid  1 if solid, else 0;
 */
void fn_level_set_solid(fn_level_t * lv, int x, int y, Uint8 solid);

/* --------------------------------------------------------------- */

/**
 * Blit the current state of the level to an SDL Surface.
 *
 * @param  lv         The level to blit.
 * @param  target     The target SDL Surface.
 * @param  targetrect The target area to which to blit.
 * @param  sourcerect The source rectangle.
 * @param  backdrop1  The first backdrop type.
 * @param  backdrop2  The second backdrop type.
 */
void fn_level_blit_to_surface(fn_level_t * lv,
    SDL_Surface * target,
    SDL_Rect * targetrect,
    SDL_Rect * sourcerect,
    SDL_Surface * backdrop1,
    SDL_Surface * backdrop2);

/* --------------------------------------------------------------- */

/**
 * Get the SDL surface to which the level is blitted.
 *
 * @param  lv   The level.
 *
 * @return The surface to which the level is blitted.
 */
SDL_Surface * fn_level_get_surface(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Get the tilecache for the level.
 *
 * @param  lv  The level.
 *
 * @return The tilecache.
 */
fn_tilecache_t * fn_level_get_tilecache(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Get the pixel size of the level.
 *
 * @param  lv  The level.
 *
 * @return The pixel size.
 */
Uint8 fn_level_get_pixelsize(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Indicate if we are still playing this level.
 * 
 * @param  lv    The level we want to play.
 * 
 * @return  non-zero if we are still playing, otherwise zero.
 */
int fn_level_keep_on_playing(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Get the hero of the level.
 *
 * @param  lv    The level from which to get the hero.
 *
 * @return The hero.
 */
fn_hero_t * fn_level_get_hero(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Call this function make the game act one step further.
 *
 * @param  lv  The level which should step.
 *
 * @return zero if the level is finished, otherwise non-zero.
 */
int fn_level_act(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Call this function to make the hero interact with items around.
 *
 * @param  lv  The level whose hero should interact.
 */
void fn_level_hero_interact_start(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Call this function to make the hero stop interacting with an item.
 *
 * @param  lv  The level whose hero should interact.
 */
void fn_level_hero_interact_stop(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Add an actor to the level.
 *
 * @param  lv    The level to which the actor gets added.
 * @param  type  The type of actor.
 * @param  x     The x coordinate of the top left corner.
 * @param  y     The y coordinate of the top left corner.
 *
 * @return  The newly created actor.
 */
fn_actor_t * fn_level_add_actor(fn_level_t * lv,
    fn_actor_type_e type,
    Uint16 x,
    Uint16 y);

/* --------------------------------------------------------------- */

/**
 * Add an actor to the level on a multiple coordinate of
 * tile-width and tile-height.
 *
 * @param  lv     The level to which the actor gets added.
 * @param  type   The type of the actor.
 * @param  x      The x coordinate which will be interally multiplied
 *                by FN_TILE_WIDTH.
 * @param  y      The y coordinate which will be interally multiplied
 *                by FN_TILE_HEIGHT.
 *
 * @return  The newly created actor.
 */
fn_actor_t * fn_level_add_initial_actor(fn_level_t * lv,
    fn_actor_type_e type,
    Uint16 x,
    Uint16 y);

/* --------------------------------------------------------------- */

/**
 * Add a particle firework to a level.
 *
 * @param  lv             The level to which the firework gets added.
 * @param  x              The x coordinate of the firework.
 * @param  y              The y coordinate of the firework.
 * @param  num_particles  The number of particles to create.
 */
void fn_level_add_particle_firework(fn_level_t * lv,
    Uint16 x, Uint16 y, Uint8 num_particles);

/* --------------------------------------------------------------- */

/**
 * Let the hero fire a shot.
 *
 * If there are already the maximum of shots in the level,
 * no shot is created and this function returns.
 * 
 * @param  lv  The level.
 */
void fn_level_fire_shot(fn_level_t * lv);

/* --------------------------------------------------------------- */

/**
 * Get a list containing all items in the level of a type.
 *
 * @param  lv    The level.
 * @param  type  The type of which to get the items.
 *
 * @return The list. The user who called this function has to
 *         call fn_list_free on it in order to free the memory.
 */
fn_list_t * fn_level_get_items_of_type(fn_level_t * lv,
    fn_actor_type_e type);

/* --------------------------------------------------------------- */

/**
 * Enable or disable the debug drawing of collision bounds
 * for a level.
 *
 * @param  lv      The level.
 * @param  enable  If 1, enable drawing. If 0, disable drawing.
 */
void fn_level_set_draw_collision_bounds(fn_level_t * lv,
    Uint8 enable);

/* --------------------------------------------------------------- */

/**
 * Check if a rectangle would collide with solids in a level.
 *
 * @param  lv     The level.
 * @param  rect   The rectangle.
 *
 * @return 1 if the rectangle would collide, otherwise 0.
 */
Uint8 fn_level_solid_collides(fn_level_t * lv,
    SDL_Rect * rect);

/* --------------------------------------------------------------- */

/**
 * Check if a rectangle stands completely on solid ground in a level.
 * Completely means that the whole width of the rectangle has solid
 * ground directly below.
 *
 * @param  lv     The level.
 * @param  rect   The rectangle.
 * 
 * @return 1 if the rectangle stands on solid ground, otherwise 0.
 */
Uint8 fn_level_stands_on_solid_ground_completely(fn_level_t * lv,
    SDL_Rect * rect);

/* --------------------------------------------------------------- */

/**
 * Check if a rectangle stands partially on solid ground in a level.
 * Partially means that not the whole width of the rectangle must
 * stand on ground, but only part of it.
 *
 * @param  lv     The level.
 * @param  rect   The rectangle.
 * 
 * @return 1 if the rectangle stands on solid ground, otherwise 0.
 */
Uint8 fn_level_stands_on_solid_ground_partially(fn_level_t * lv,
    SDL_Rect * rect);

/* --------------------------------------------------------------- */

/**
 * Push a rectangle which is standing on solid ground.
 * If the rectangle would no longer stand on solid ground,
 * this is shown in the return value.
 *
 * @param  level    The level inside which the rectangle is.
 * @param  rect     The rectangle.
 * @param  offset   The horizontal offset by which to push.
 * @param  gravity  The vertical speed by which the rect falls down.
 *
 * @return 1 if the push was successful, otherwise 0.
 */
Uint8 fn_level_push_rect_standing_on_solid_ground(
    fn_level_t * level, SDL_Rect * rect, Sint8 offset, Uint8 gravity);

/* --------------------------------------------------------------- */

/**
 * Let a rectangle fall down within a level.
 * This is possible, if it overlaps with no solid parts and if
 * it does not stand on any ground at all.
 *
 * @param  level     The level inside which the rectangle is.
 * @param  rect      The rectangle.
 * @param  dist      The distance for which to check.
 *
 * @return The number of pixels by which the rect can fall down
 *         (maximally the same value as dist).
 */
Uint8 fn_level_rect_fall_down(
    fn_level_t * level, SDL_Rect * rect, Uint8 dist);

/* --------------------------------------------------------------- */

#endif /* FN_LEVEL_H */
