/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Drop (Level Background) loader
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

#include <stdlib.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn_draw.h"
#include "fn_tile.h"
#include "fn_drop.h"
#include "fntexture.h"
#include "fngeometry.h"

/* --------------------------------------------------------------- */

FnTexture * fn_drop_load(int fd, fn_environment_t * env)
{
    FnTexture * drop;
    FnGeometry * geometry;
    size_t num_read = 0;
    fn_tileheader_t h;

    FnTexture * tile;

    Uint8 pixelsize = fn_environment_get_pixelsize(env);

    drop = fn_texture_new_with_environment(
        FN_DROP_WIDTH * FN_TILE_WIDTH,
        FN_DROP_HEIGHT * FN_TILE_HEIGHT,
        env);

    size_t num_loads = FN_DROP_WIDTH *  FN_DROP_HEIGHT;

    gint  x      = 0;
    gint  y      = 0;
    guint width  = FN_TILE_WIDTH  * pixelsize;
    guint height = FN_TILE_HEIGHT * pixelsize;

    h.width = 2;
    h.height = 16;

    geometry = fn_geometry_new(x, y, width, height);

    while(num_read != num_loads)
    {
        tile = fn_tile_load(fd,
            env,
            &h,
            FALSE);
        fn_texture_clone_to_texture(tile, NULL, drop, geometry);
        g_object_unref(tile);
        x += 16 * pixelsize;
        if (x == 16 * FN_DROP_WIDTH * pixelsize)
        {
            x = 0;
            y += 16 * pixelsize;
        }
        fn_geometry_set_x(geometry, x);
        fn_geometry_set_y(geometry, y);
        num_read++;
    }

    return drop;
}

/* --------------------------------------------------------------- */

