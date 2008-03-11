/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Global defines for FreeNukum
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

#ifndef FN_H
#define FN_H

/* --------------------------------------------------------------- */

#define FN_DROP_WIDTH       13
#define FN_DROP_HEIGHT      10

#define FN_HALFTILE_WIDTH    8
#define FN_HALFTILE_HEIGHT   8

#define FN_FONT_WIDTH        8
#define FN_FONT_HEIGHT       8

#define FN_PART_WIDTH       16
#define FN_PART_HEIGHT      16

#define FN_COLOR_DEPTH      24

#define FN_WINDOW_WIDTH    320
#define FN_WINDOW_HEIGHT   200

#define FN_PICTURE_WIDTH    40
#define FN_PICTURE_HEIGHT  200

/**
 * The number of tiles how wide the level output screen is.
 */
#define FN_LEVELWINDOW_WIDTH  13

/**
 * The number of tiles how high the level output screen is.
 */
#define FN_LEVELWINDOW_HEIGHT  10

#define FN_TILECACHE_SIZE 1300

/**
 * The height of a level (in full tiles)
 */
#define FN_LEVEL_HEIGHT     90
/**
 * The width of a level (in full tiles)
 */
#define FN_LEVEL_WIDTH     128

/**
 * The maximum number of items in a level
 */
#define FN_MAX_ITEMS       128

/**
 * The maximum number of animations in a level
 */
#define FN_MAX_ANIMATIONS  128

/**
 * The maximum number of bots in a level
 */
#define FN_MAX_BOTS        128

/* --------------------------------------------------------------- */

#define FN_DEFAULT_PIXELSIZE     2

/* --------------------------------------------------------------- */

#define FN_NUM_MAXLIFE       8
#define FN_SCORE_DIGITS      8
#define FN_NUM_MAXFIREPOWER  4
#define FN_SIZE_INVENTORY    8

/* --------------------------------------------------------------- */

#define FN_INVENTORY_KEY_RED     (0x01 << 7)
#define FN_INVENTORY_KEY_GREEN   (0x01 << 6)
#define FN_INVENTORY_KEY_BLUE    (0x01 << 5)
#define FN_INVENTORY_KEY_PINK    (0x01 << 4)
#define FN_INVENTORY_BOOT        (0x01 << 3)
#define FN_INVENTORY_ROBOHAND    (0x01 << 2)
#define FN_INVENTORY_CLAMP       (0x01 << 1)
#define FN_INVENTORY_ACCESS_CARD (0x01 << 0)

/* --------------------------------------------------------------- */

typedef enum fn_horizontal_direction_e {
  fn_horizontal_direction_none,
  fn_horizontal_direction_left,
  fn_horizontal_direction_right,
  fn_horizontal_direction_size
} fn_horizontal_direction_e;

/* --------------------------------------------------------------- */

#endif // FN_H
