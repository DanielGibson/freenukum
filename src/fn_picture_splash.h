/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Splash a picture to the screen
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

#ifndef FN_PICTURE_SPLASH
#define FN_PICTURE_SPLASH

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"
#include "fn_environment.h"

/* --------------------------------------------------------------- */

/**
 * Show a splash picture on the screen.
 * This function waits for input of the Escape or Return key, then
 * it returns.
 * 
 * @param  env        The environment.
 * @param  filename   The filename of the picture to show.
 *                    Usually one of: BADGUY.DN1, CREDITS.DN1, DN.DN1, DUKE.DN1
 *
 * @return 1 on success, otherwise 0 (if for example the file could not be
 *         read. In that case, it also calls the fn_error_printf function).
 */
int fn_picture_splash_show(
    fn_environment_t * env,
    char * filename);

/* --------------------------------------------------------------- */

/**
 * Show a splash picture on the screen and display a message.
 * This function waits for input of the Escape or Return key, then
 * it returns.
 * 
 * @param  env        The environment.
 * @param  filename   The filename of the picture to show.
 *                    Usually one of: BADGUY.DN1, CREDITS.DN1, DN.DN1, DUKE.DN1
 * @param  message    A string containing the message. Must have a
 *                    trailing \n otherwise the last line will be omitted.
 *                    If this is NULL, no message will be displayed.
 * @param  x          The x offset of the message (in pixels).
 * @param  y          The y offset of the message (in pixels).
 *
 * @return 1 on success, otherwise 0 (if for example the file could not be
 *         read. In that case, it also calls the fn_error_printf function).
 */
int fn_picture_splash_show_with_message(
    fn_environment_t * env,
    char * filename,
    char * message,
    Uint8 x,
    Uint8 y);

/* --------------------------------------------------------------- */

#endif /* FN_PICTURE_SPLASH */
