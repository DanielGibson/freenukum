/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tile Cache
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

#include <SDL.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

fn_tilecache_t * fn_tilecache_create()
{
  fn_tilecache_t * tc = malloc(sizeof(fn_tilecache_t));
  size_t i;
  for(i = 0; i != FN_TILECACHE_SIZE; i++)
  {
    tc->tiles[i] = NULL;
  }
  tc->size = 0;
  return tc;
}

/* --------------------------------------------------------------- */

int fn_tilecache_loadtiles(fn_tilecache_t * tc,
    fn_environment_t * env)
{
    int fd;
    size_t i = 0;
    char * path;
    int res;
    fn_tileheader_t header;
    char * directory = fn_environment_get_datapath(env);

    Uint8 transparent[] = {
      1,
      0,
      0,
      0,
      1,
      0,
      0,
      0,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1
    };

    char * files[] = {
        "BACK0.DN1",
        "BACK1.DN1",
        "BACK2.DN1",
        "BACK3.DN1",
        "SOLID0.DN1",
        "SOLID1.DN1",
        "SOLID2.DN1",
        "SOLID3.DN1",
        "ANIM0.DN1",
        "ANIM1.DN1",
        "ANIM2.DN1",
        "ANIM3.DN1",
        "ANIM4.DN1",
        "ANIM5.DN1",
        "OBJECT0.DN1",
        "OBJECT1.DN1",
        "OBJECT2.DN1",
        "MAN0.DN1",
        "MAN1.DN1",
        "MAN2.DN1",
        "MAN3.DN1",
        "MAN4.DN1",
        "FONT1.DN1",
        "FONT2.DN1",
        "BORDER.DN1",
        "NUMBERS.DN1",
        0
    };

    Uint8 size[] = {
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        48,
        50,
        50,
        50,
        48,
        48,
        48,
        48,
        48,
        50,
        50,
        48,
        48,
        0
    };

    path = malloc(strlen(directory) + 15);

    if (path == NULL)
    {
        return -1;
    }

    while (files[i] != 0)
    {
        snprintf(path, strlen(directory) + 15, "%s/%s",
            directory, files[i]);
        fd = open(path, O_RDONLY);
        if (fd == -1)
        {
          printf("Failed to open file %s\n", path);
        } else {

          fn_tile_loadheader(fd, &header);
          res =
            fn_tilecache_loadfile(tc,
                env,
                fd,
                size[i],
                &header,
                transparent[i]);
          close(fd);

          if (res != 0)
          {
            printf("Failed loading file %s\n", path);
          }
        }
        i++;
    }

    free(path);
    return 0;
}

/* --------------------------------------------------------------- */

int fn_tilecache_loadfile(
        fn_tilecache_t * tc,
        fn_environment_t * env,
        int fd,
        size_t num_tiles,
        fn_tileheader_t * header,
        Uint8 transparent)
{
    while(num_tiles > 0)
    {
        tc->tiles[tc->size] =
          fn_tile_load(fd,
              env,
              header,
              transparent);
        if (tc->tiles[tc->size] == NULL)
        {
            return -1;
        }
        tc->size++;
        num_tiles--;
    }
    return 0;
}

/* --------------------------------------------------------------- */

void fn_tilecache_destroy(fn_tilecache_t * tc)
{
    while (tc->size > 0)
    {
        tc->size--;
        g_object_unref(tc->tiles[tc->size]);
    }
}

/* --------------------------------------------------------------- */

FnTexture * fn_tilecache_get_tile(fn_tilecache_t * tc, size_t pos)
{
    return tc->tiles[pos];
}

/* --------------------------------------------------------------- */

