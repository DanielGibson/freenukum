/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Level loading functions
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

#include <sys/stat.h>
#include <fcntl.h>

/* --------------------------------------------------------------- */

#include "fn_level_loader.h"

/* --------------------------------------------------------------- */

int fn_level_load(fn_level_t * lv, int fd)
{
    size_t i = 0;
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
        lv->level[i] = tilenr;
        i++;
    }
    return 0;
}

/* --------------------------------------------------------------- */

Uint16 fn_level_gettile(fn_level_t * lv, size_t x, size_t y)
{
    return lv->level[y * FN_LEVEL_WIDTH + x];
}

/* --------------------------------------------------------------- */
