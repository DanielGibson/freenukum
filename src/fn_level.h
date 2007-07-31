/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Level loading functions
 * $Id: fn_level.h 11 2006-06-10 12:20:52Z sttereo3 $
 *******************************************************************/

#ifndef FN_LEVEL_H
#define FN_LEVEL_H

/* --------------------------------------------------------------- */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn.h"

/* --------------------------------------------------------------- */

typedef struct {
    Uint16 level[FN_LEVEL_HEIGHT * FN_LEVEL_WIDTH];
} fn_level_t;

/* --------------------------------------------------------------- */

int fn_level_load(fn_level_t * lv, int fd);

/* --------------------------------------------------------------- */

Uint16 fn_level_gettile(fn_level_t * lv, size_t x, size_t y);

/* --------------------------------------------------------------- */

#endif // FN_LEVEL_H
