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

void fn_level_set_tile(fn_level_t * level,
    Uint16 tilenr,
    Uint16 x,
    Uint16 y)
{
  if (tilenr < BACKGROUND_END) {
    /* we have a background tile */
  } else if (tilenr < SOLID_END) {
    /* we have a solid tile */
  } else {
    /* we don't know yet what we have. */
  }
}

/* --------------------------------------------------------------- */

