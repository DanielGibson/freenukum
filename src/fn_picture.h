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

#ifndef FN_PICTURE_H
#define FN_PICTURE_H

/* --------------------------------------------------------------- */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_environment.h"
#include "fntexture.h"

/* --------------------------------------------------------------- */

/**
 * Load a picture from a picture file.
 *
 * @param  fd            The opened file descriptor to the file.
 * @param  env           The game environment.
 */
FnTexture * fn_picture_load(int fd, fn_environment_t * env);

/* --------------------------------------------------------------- */

#endif /* FN_PICTURE_H */
