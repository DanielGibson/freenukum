/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Level loading functions
 *******************************************************************/

#include <sys/stat.h>
#include <fcntl.h>

/* --------------------------------------------------------------- */

#include "fn_level.h"

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

