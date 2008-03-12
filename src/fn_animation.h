/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Animation struct
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

#ifndef FN_ANIMATION_H
#define FN_ANIMATION_H

#include <SDL.h>

/* --------------------------------------------------------------- */

typedef struct fn_animation_t fn_animation_t;

struct fn_animation_t {
  /**
   * The number of frames
   */
  size_t num_frames;

  /**
   * The animation frames
   */
  SDL_Surface ** frames;

  /**
   * The current frame
   */
  size_t current_frame;

  /**
   * The x position
   */
  Uint16 x;

  /**
   * The y position
   */
  Uint16 y;

  /**
   * The size of one pixel
   */
  size_t pixelsize;
};

/* --------------------------------------------------------------- */

/**
 * Initialize an animation.
 *
 * @param  num_frames  The number of frames.
 * @param  frames      The frames.
 * @param  startframe  The number of the start frame.
 * @param  x           The x position.
 * @param  y           The y position.
 * @param  pixelsize   The size of one pixel.
 */
void fn_animation_init(fn_animation_t * anim,
    size_t num_frames,
    SDL_Surface ** frames,
    size_t startframe,
    Uint16 x,
    Uint16 y,
    size_t pixelsize);

/* --------------------------------------------------------------- */

/**
 * Blit the animation to the animation layer.
 *
 * @param  anim     The animation to blit.
 * @param  target   The target layer.
 */
void fn_animation_blit(
    fn_animation_t * anim,
    SDL_Surface * target
    );

/* --------------------------------------------------------------- */

/**
 * Get the x coordinate of the animation.
 *
 * @return  The x coordinate.
 */
Uint16 fn_animation_get_x(fn_animation_t * anim);

/* --------------------------------------------------------------- */

/**
 * Get the y coordinate of the animation.
 *
 * @return  The y coordinate.
 */
Uint16 fn_animation_get_y(fn_animation_t * anim);

/* --------------------------------------------------------------- */

#endif // FN_ANIMATION_H
