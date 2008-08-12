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

#include "fn.h"
#include "fn_collision.h"

/* --------------------------------------------------------------- */

int fn_collision_overlap_rect_rect(SDL_Rect * r1, SDL_Rect * r2)
{
  return fn_collision_overlap_area_area(
      r1->x, r1->y, r1->w, r1->h,
      r2->x, r2->y, r2->w, r2->h);
}

/* --------------------------------------------------------------- */

int fn_collision_overlap_area_area(
    Uint32 x1, Uint32 y1, Uint32 w1, Uint32 h1,
    Uint32 x2, Uint32 y2, Uint32 w2, Uint32 h2)
{
  if (x1 + w1 <= x2)
  {
    return 0;
  }
  if (x2 + w2 <= x1)
  {
    return 0;
  }
  if (y1 + h1 <= y2)
  {
    return 0;
  }
  if (y2 + h2 <= y1)
  {
    return 0;
  }
  return 1;
}

/* --------------------------------------------------------------- */

int fn_collision_overlap_rect_area(SDL_Rect * rect,
    Uint32 x, Uint32 y, Uint32 w, Uint32 h)
{
  return fn_collision_overlap_area_area(
      rect->x, rect->y, rect->w, rect->h,
      x, y, w, h);
}

/* --------------------------------------------------------------- */

void fn_collision_area_draw(SDL_Surface * destination,
    Uint8 pixelsize,
    Uint32 x, Uint32 y, Uint32 w, Uint32 h)
{
  Uint32 color = FN_COLLISION_DEBUG_COLOR(destination->format);
  SDL_Rect destrect;

  destrect.x = pixelsize * x;
  destrect.y = pixelsize * y;
  destrect.w = pixelsize;
  destrect.h = pixelsize * h;

  SDL_FillRect(destination, &destrect, color);
  destrect.x += (w - 1) * pixelsize;
  SDL_FillRect(destination, &destrect, color);
  destrect.x = x * pixelsize;
  destrect.y = y * pixelsize;
  destrect.h = pixelsize;
  destrect.w = w * pixelsize;
  SDL_FillRect(destination, &destrect, color);
  destrect.y = (y + h - 1) * pixelsize;
  SDL_FillRect(destination, &destrect, color);
}

/* --------------------------------------------------------------- */

void fn_collision_rect_draw(SDL_Surface * destination,
    Uint8 pixelsize,
    SDL_Rect * rect)
{
  fn_collision_area_draw(destination, pixelsize,
      rect->x, rect->y, rect->w, rect->h);
}

/* --------------------------------------------------------------- */

int fn_collision_distance_horizontal_area_area(
    Uint32 x1, Uint32 w1, Uint32 x2, Uint32 w2)
{
  if (x1 + w1 < x2) {
    return x2 - w1 - x1;
  }
  if (x2 + w2 < x1) {
    return - (x1 - w2 - x2);
  }
  return 0;
}

/* --------------------------------------------------------------- */

int fn_collision_distance_horizontal_rect_area(
    SDL_Rect * rect, Uint32 x, Uint32 w)
{
  return fn_collision_distance_horizontal_area_area(
      rect->x, rect->w, x, w);
}

/* --------------------------------------------------------------- */

int fn_collision_overlap_vertical_area_area(
    Uint32 y1, Uint32 h1, Uint32 y2, Uint32 h2)
{
  if (y1 + h1 <= y2) {
    return 0;
  }
  if (y2 + h2 <= y1) {
    return 0;
  }
  return 1;
}

/* --------------------------------------------------------------- */

int fn_collision_overlap_vertical_rect_area(
    SDL_Rect * rect, Uint32 y, Uint32 h)
{
  return fn_collision_overlap_vertical_area_area(
      rect->y, rect->h, y, h);
}

/* --------------------------------------------------------------- */

int fn_collision_distance_vertical_area_area(
    Uint32 y1, Uint32 h1, Uint32 y2, Uint32 h2)
{
  if (y1 + h1 < y2) {
    return y2 - h1 - y1;
  }
  if (y2 + h2 < y1) {
    return -(y1 - h2 - y2);
  }
  return 0;
}

/* --------------------------------------------------------------- */

int fn_collision_distance_vertical_rect_area(
    SDL_Rect * rect, Uint32 y, Uint32 h)
{
  return fn_collision_distance_vertical_area_area(
      rect->y, rect->h, y, h);
}

/* --------------------------------------------------------------- */

int fn_collision_touch_area_area(
    Uint32 x1, Uint32 y1, Uint32 w1, Uint32 h1,
    Uint32 x2, Uint32 y2, Uint32 w2, Uint32 h2)
{
  int ret = fn_collision_overlap_area_area(x1, y1, w1 + 1, h1 + 1,
      x2, y2, w2 + 1, h2 + 1);
  return ret;
}

/* --------------------------------------------------------------- */

int fn_collision_touch_rect_area(SDL_Rect * rect,
    Uint32 x, Uint32 y, Uint32 w, Uint32 h)
{
  return fn_collision_touch_area_area(
      x, y, w, h,
      rect->x, rect->y, rect->w, rect->h);
}

/* --------------------------------------------------------------- */

int fn_collision_touch_rect_rect(SDL_Rect * rect1,
    SDL_Rect * rect2)
{
  return fn_collision_touch_area_area(
      rect1->x, rect1->y, rect1->w, rect1->h,
      rect2->x, rect2->y, rect2->w, rect2->h);
}

/* --------------------------------------------------------------- */
