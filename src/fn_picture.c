/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Picture Drawing functions
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

#include "fn.h"
#include "fn_picture.h"

/* --------------------------------------------------------------- */

FnTexture * fn_picture_load(int fd, 
    fn_environment_t * env)
{
    FnTexture * picture;
    guint i = 0;
    guint j = 0;

    picture = fn_texture_new_with_environment(
        FN_WINDOW_WIDTH,
        FN_WINDOW_HEIGHT,
        env
        );

    guint num_loads = FN_PICTURE_WIDTH * FN_PICTURE_HEIGHT;

    guchar * data = g_new0(guchar,
        FN_PICTURE_WIDTH * FN_PICTURE_HEIGHT * 4 * 8);
    guchar * data_pos = data;
    guchar readbuf[num_loads];

    /* read blue */
    read(fd, readbuf, num_loads);
    data_pos = data + 2;
    for(i = 0; i < num_loads; i++) {
      for (j = 0; j < 8; j++) {
        guchar blue_pixel = ((readbuf[i] >> (7 -j)) & 1);
        *data_pos += blue_pixel * 0x54 * 2;
        data_pos += 4;
      }
    }

    /* read green */
    read(fd, readbuf, num_loads);
    data_pos = data + 1;
    for(i = 0; i < num_loads; i++) {
      for (j = 0; j < 8; j++) {
        guchar green_pixel = ((readbuf[i] >> (7 -j)) & 1);
        *data_pos += green_pixel * 0x54 * 2;
        data_pos += 4;
      }
    }

    /* read red */
    read(fd, readbuf, num_loads);
    data_pos = data;
    for(i = 0; i < num_loads; i++) {
      for (j = 0; j < 8; j++) {
        guchar red_pixel = ((readbuf[i] >> (7 -j)) & 1);
        *data_pos += red_pixel * 0x54 * 2;
        data_pos += 4;
      }
    }

    /* read brighten, and set pixels opaque */
    read(fd, readbuf, num_loads);
    data_pos = data;
    for(i = 0; i < num_loads; i++) {
      for (j = 0; j < 8; j++) {
        guchar bright_pixel = ((readbuf[i] >> (7 -j)) & 1);

        /* brighten red */
        *data_pos += bright_pixel * 0x54;
        data_pos++;

        /* brighten blue */
        *data_pos += bright_pixel * 0x54;
        data_pos++;

        /* brighten green */
        *data_pos += bright_pixel * 0x54;
        data_pos++;

        /* set opaque */
        *data_pos = 0xFF;
        data_pos++;
      }
    }

    fn_texture_set_data(picture, data);

    return picture;
}

/* --------------------------------------------------------------- */

