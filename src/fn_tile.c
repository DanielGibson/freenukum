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
#include "fn_draw.h"
#include "fn.h"
#include "fntile.h"

/* --------------------------------------------------------------- */

int fn_tile_loadheader(int fd, fn_tileheader_t * h)
{
    return read(fd, h, sizeof(*h)) == sizeof(*h);
}

/* --------------------------------------------------------------- */

FnTile * fn_tile_load(
    int fd,
    fn_environment_t * env,
    fn_tileheader_t * h)
{
  FnTile * tile = fn_tile_new_with_environment(
      h->width,
      h->height,
      env);
  guchar * data = g_new(guchar, h->width * h->height * 4);

  guchar readbuf[5];

  guint num_loads = h->width * h->height / 8;
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
      guchar opaque_pixel = ((opaque_row >> (7-i)) & 1);
      guchar ugly_yellow  = (
          red_pixel == 1 &&
          green_pixel == 1 &&
          blue_pixel == 0 &&
          bright_pixel == 1) ? 1 : 0;

      guchar * red    = iter;
      guchar * green  = iter + 1;
      guchar * blue   = iter + 2;
      guchar * opaque = iter + 3;

      *red =    red_pixel    * 0x54 * (2 + bright_pixel);
      *green =  green_pixel  * 0x54 * (2 + bright_pixel - ugly_yellow);
      *blue  =  blue_pixel   * 0x54 * (2 + bright_pixel);
      *opaque = opaque_pixel * 0xFF;
      iter += 4;
    }

    num_read++;
  }

  fn_tile_set_data(tile, data);

  g_free(data);
  return tile;
}

/* --------------------------------------------------------------- */

SDL_Surface * fn_tile_load_to_sdl(
        int fd,
        fn_environment_t * env,
        fn_tileheader_t * h,
        Uint8 transparent)
{
    SDL_Surface * tile;
    SDL_Rect r;
    size_t num_read = 0;
    fn_byterow_t br = {0, 0, 0, 0, 0};
    char readbuf[5];

    Uint8 pixelsize = fn_environment_get_pixelsize(env);

    tile = fn_environment_create_surface(
        env,
        h->width * 8,
        h->height);

    size_t num_loads = h->width * h->height;
    
    r.x = 0;
    r.y = 0;
    r.w = 8 * pixelsize;
    r.h = 1 * pixelsize;

    Uint32 transparent_color = (
        transparent ?
        fn_environment_get_transparent(env) :
        0);


    while (num_read < num_loads)
    {
        read(fd, readbuf, 5);
        br.trans  = readbuf[0];
        br.blue   = readbuf[1];
        br.green  = readbuf[2];
        br.red    = readbuf[3];
        br.brighten = readbuf[4];
        fn_draw_byterow(
                tile,
                r,
                &br,
                transparent_color,
                pixelsize);
        r.x += 8 * pixelsize;
        r.x %= (8 * h->width * pixelsize);


        if (r.x == 0)
            r.y += pixelsize;
        num_read++;
    }

    return tile;
}

/* --------------------------------------------------------------- */

int fn_tile_is_solid(
    Uint16 tile)
{
  return tile >= SOLID_START && tile < ANIM_START;
}

/* --------------------------------------------------------------- */

