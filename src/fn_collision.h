/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Collision functions
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

#ifndef FN_COLLISION_H
#define FN_COLLISION_H

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

/**
 * Check if two rectangles overlap.
 *
 * @param  r1  The first rectangle.
 * @param  r2  The second rectangle.
 *
 * @return 1 if the rectangles overlap, otherwise 0.
 */
int fn_collision_overlap_rect_rect(SDL_Rect * r1, SDL_Rect * r2);

/* --------------------------------------------------------------- */

/**
 * Check if two areas overlap.
 *
 * @param  x1  The x coordinate of the first area.
 * @param  y1  The y coordinate of the first area.
 * @param  w1  The width of the first area.
 * @param  h1  The height of the first area.
 * @param  x2  The x coordinate of the second area.
 * @param  y2  The y coordinate of the second area.
 * @param  w2  The width of the second area.
 * @param  h2  The height of the second area.
 *
 * @return 1 if the areas overalp, otherwise 0.
 */
int fn_collision_overlap_area_area(
    Uint32 x1, Uint32 y1, Uint32 w1, Uint32 h1,
    Uint32 x2, Uint32 y2, Uint32 w2, Uint32 h2);

/* --------------------------------------------------------------- */

/**
 * Check if a rectangle overlaps an area.
 *
 * @param  rect  The rectangle.
 * @param  x     The x coordinate of the area.
 * @param  y     The y coordinate of the area.
 * @param  w     The width of the area.
 * @param  h     The height of the area.
 *
 * @return 1 if the rectangle overalps the area, otherwise 0.
 */
int fn_collision_overlap_rect_area(SDL_Rect * rect,
    Uint32 x, Uint32 y, Uint32 w, Uint32 h);

/* --------------------------------------------------------------- */

/**
 * Check if two areas touch each other.
 *
 * @param  x1    The x coordinate of the first area.
 * @param  y1    The y coordinate of the first area.
 * @param  w1    The width of the first area.
 * @param  h1    The height of the first area.
 * @param  x2    The x coordinate of the second area.
 * @param  y2    The y coordinate of the second area.
 * @param  w2    The width of the second area.
 * @param  h2    The height of the second area.
 *
 * @return 1 if the rectangles touch, otherwise 0.
 */
int fn_collision_touch_area_area(
    Uint32 x1, Uint32 y1, Uint32 w1, Uint32 h1,
    Uint32 x2, Uint32 y2, Uint32 w2, Uint32 h2);

/* --------------------------------------------------------------- */

/**
 * Check if an area and a rectangle touch each other.
 *
 * @param  rect    The rectangle.
 * @param  x     The x coordinate of the area.
 * @param  y     The y coordinate of the area.
 * @param  w     The width of the area.
 * @param  h     The height of the area.
 *
 * @return 1 if the rectangle and the area touch, otherwise 0.
 */
int fn_collision_touch_rect_area(SDL_Rect * rect,
    Uint32 x, Uint32 y, Uint32 w, Uint32 h);

/* --------------------------------------------------------------- */

/**
 * Debug drawing function for a collision area.
 *
 * @param  destination  The surface on which to draw.
 * @param  pixelsize    The pixelsize with which to draw.
 * @param  x     The x coordinate of the area.
 * @param  y     The y coordinate of the area.
 * @param  w     The width of the area.
 * @param  h     The height of the area.
 */
void fn_collision_area_draw(SDL_Surface * destination,
    Uint8 pixelsize,
    Uint32 x, Uint32 y, Uint32 w, Uint32 h);

/* --------------------------------------------------------------- */

/**
 * Debug drawing function for a collision rectangle.
 *
 * @param  destination  The surface on which to draw.
 * @param  pixelsize    The pixelsize with which to draw.
 * @param  rect  The rectangle.
 */
void fn_collision_rect_draw(SDL_Surface * destination,
    Uint8 pixelsize,
    SDL_Rect * rect);

/* --------------------------------------------------------------- */

#endif /* FN_COLLISION_H */
