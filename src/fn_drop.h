/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Drop (Level Background) loader
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

#ifndef FN_DROP_H
#define FN_DROP_H

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_environment.h"

/* --------------------------------------------------------------- */

/**
 * Loads a backdrop from a file.
 * @param  fd            The file descriptor of the already opened file.
 * @param  env           The environment.
 *
 * @return The loaded backrdop.
 */
SDL_Surface * fn_drop_load(int fd, fn_environment_t * env);

/* --------------------------------------------------------------- */

#endif /* FN_DROP_H */
