/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tile loader
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

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn_object.h"
#include "fn_tile.h"
#include "fn.h"
#include "fntexture.h"

/* --------------------------------------------------------------- */

int fn_tile_loadheader(int fd, fn_tileheader_t * h)
{
    return read(fd, h, sizeof(*h)) == sizeof(*h);
}

/* --------------------------------------------------------------- */

FnTexture * fn_tile_load(
    int fd,
    FnGraphicOptions * graphic_options,
    fn_tileheader_t * h,
    gboolean has_transparency)
{
  guint width = h->width * 8;
  guint height = h->height;

  FnTexture * tile = fn_texture_new_with_options(
      width,
      height,
      graphic_options);

  guchar * data = g_new(guchar, width * height * 4);

  guchar readbuf[5];

  guint num_loads = width * height / 8;
  guint num_read = 0;
  guchar * iter = data;

  while (num_read < num_loads)
  {
    read(fd, readbuf, 5);
    guchar opaque_row = readbuf[0];
    guchar blue_row   = readbuf[1];
    guchar green_row  = readbuf[2];
    guchar red_row    = readbuf[3];
    guchar bright_row = readbuf[4];

    guchar i = 0;

    for (i = 0; i < 8; i++) {
      guchar bright_pixel = ((bright_row >> (7-i)) & 1);
      guchar red_pixel    = ((red_row    >> (7-i)) & 1);
      guchar green_pixel  = ((green_row  >> (7-i)) & 1);
      guchar blue_pixel   = ((blue_row   >> (7-i)) & 1);
      guchar opaque_pixel = (
          has_transparency ?
          ((opaque_row >> (7-i)) & 1) :
          1);
      guchar ugly_yellow  = (
          red_pixel == 1 &&
          green_pixel == 1 &&
          blue_pixel == 0 &&
          bright_pixel == 0) ? 1 : 0;

      guchar * red    = iter;
      guchar * green  = iter + 1;
      guchar * blue   = iter + 2;
      guchar * opaque = iter + 3;

      *red =    0x54 * (red_pixel   * 2 + bright_pixel);
      *green =  0x54 * (green_pixel * 2 + bright_pixel - ugly_yellow);
      *blue  =  0x54 * (blue_pixel  * 2 + bright_pixel);
      *opaque = opaque_pixel * 0xFF;
      iter += 4;
    }

    num_read++;
  }

  fn_texture_set_data(tile, data);

  g_free(data);
  return tile;
}

/* --------------------------------------------------------------- */

int fn_tile_is_solid(
    Uint16 tile)
{
  return tile >= SOLID_START && tile < ANIM_START;
}

/* --------------------------------------------------------------- */

