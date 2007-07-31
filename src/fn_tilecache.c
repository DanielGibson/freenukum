/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tile Cache
 * $Id: fn_tilecache.c 11 2006-06-10 12:20:52Z sttereo3 $
 *******************************************************************/

#include <SDL/SDL.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

void fn_tilecache_init(
        fn_tilecache_t * tc,
        Uint8 pixelsize)
{
    size_t i;
    for(i = 0; i != FN_TILECACHE_SIZE; i++)
    {
        tc->tiles[i] = NULL;
    }
    tc->pixelsize = pixelsize;
    tc->size = 0;
}

/* --------------------------------------------------------------- */

int fn_tilecache_loadtiles(
        fn_tilecache_t * tc,
        char * directory
        )
{
    int fd;
    size_t i = 0;
    char * path;
    int res;
    fn_tileheader_t header;

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

    path = malloc(strlen(directory) + 12);

    if (path == NULL)
    {
        return -1;
    }

    while (files[i] != 0)
    {
        strcpy(path, directory);
        fd = open(strcat(path, files[i]), O_RDONLY);
        if (fd == -1)
        {
            return -1;
        }

        fn_tile_loadheader(fd, &header);
        res = fn_tilecache_loadfile(tc, fd, size[i], &header);
        close(fd);

        if (res != 0)
        {
            return -1;
        }
        i++;
    }

    free(path);
    return 0;
}

/* --------------------------------------------------------------- */

int fn_tilecache_loadfile(
        fn_tilecache_t * tc,
        int fd,
        size_t num_tiles,
        fn_tileheader_t * header)
{
    while(num_tiles > 0)
    {
        tc->tiles[tc->size] = fn_tile_load(fd, tc->pixelsize, header);
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
        SDL_FreeSurface(tc->tiles[tc->size]);
    }
}

/* --------------------------------------------------------------- */

SDL_Surface * fn_tilecache_gettile(fn_tilecache_t * tc, size_t pos)
{
    return tc->tiles[pos];
}

/* --------------------------------------------------------------- */

