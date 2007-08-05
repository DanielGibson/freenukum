/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Gameplay functions
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

#ifndef FN_GAME_H
#define FN_GAME_H

/* --------------------------------------------------------------- */

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

#define FN_INVENTORY_KEY_RED     (0x01 << 7);
#define FN_INVENTORY_KEY_GREEN   (0x01 << 6);
#define FN_INVENTORY_KEY_BLUE    (0x01 << 5);
#define FN_INVENTORY_KEY_PINK    (0x01 << 4);
#define FN_INVENTORY_BOOT        (0x01 << 3);
#define FN_INVENTORY_ROBOHAND    (0x01 << 2);
#define FN_INVENTORY_CLAMPS      (0x01 << 1);
#define FN_INVENTORY_ACCESS_CARD (0x01 << 0);

/* --------------------------------------------------------------- */

void fn_game_start(
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    SDL_Surface * screen,
    char * datapath);

/* --------------------------------------------------------------- */

#endif /* FN_GAME_H */
