/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Level functions
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

#include "fn_level.h"

/* --------------------------------------------------------------- */

fn_level_t * fn_level_load(int fd)
{
  size_t i = 0;
  fn_level_t * lv = malloc(sizeof(fn_level_t));
  Uint16 tilenr;
  Uint8 uppertile;
  Uint8 lowertile;
  while (i != FN_LEVEL_HEIGHT * FN_LEVEL_WIDTH)
  {
    read(fd, &lowertile, 1);
    read(fd, &uppertile, 1);
    tilenr = uppertile;
    tilenr <<= 8;
    tilenr |= lowertile;
    lv->tiles[i/FN_LEVEL_WIDTH][i%FN_LEVEL_WIDTH] = tilenr;
    i++;
  }
  return lv;
}

/* --------------------------------------------------------------- */

void fn_level_destroy(fn_level_t * level)
{
  free(level);
}

/* --------------------------------------------------------------- */

Uint16 fn_level_gettile(fn_level_t * lv, size_t x, size_t y)
{
  return lv->tiles[y][x];
}
