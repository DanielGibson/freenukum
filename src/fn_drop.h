/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Drop (Level Background) loader
 * $Id: fn_drop.h 8 2006-06-04 11:26:48Z sttereo3 $
 *******************************************************************/

#ifndef FN_DROP_H
#define FN_DROP_H

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn.h"

/* --------------------------------------------------------------- */

/**
 * Loads a backdrop from a file.
 * @param  fd  The file descriptor of the already opened file.
 */
SDL_Surface * fn_drop_load(int fd, Uint8 pixelsize);

/* --------------------------------------------------------------- */

#endif // FN_DROP_H
