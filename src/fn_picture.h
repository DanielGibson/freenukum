/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Picture Drawing functions
 * $Id: fn_picture.h 8 2006-06-04 11:26:48Z sttereo3 $
 *******************************************************************/

#ifndef FN_PICTURE_H
#define FN_PICTURE_H

/* --------------------------------------------------------------- */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

SDL_Surface * fn_picture_load(int fd, Uint8 pixelsize);

/* --------------------------------------------------------------- */

#endif // FN_PICTURE_H
