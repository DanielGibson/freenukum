/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Splash a picture to the screen
 *
 * *****************************************************************
 *
 * Copyright 2007 Wolfgang Silbermayr
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
 * Foobar is distributed in the hope that it will be useful,
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

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

/**
 * Show a splash picture on the screen.
 * This function waits for input of the Escape or Return key, then
 * it returns.
 * 
 * @param  datapath   The directory where the data files are stored.
 * @param  filename   The filename of the picture to show.
 *                    Usually one of: BADGUY.DN1, CREDITS.DN1, DN.DN1, DUKE.DN1
 * @param  pixelsize  The pixel size.
 * @param  screen     The surface to which the image is finally blitted.
 *
 * @return 1 on success, otherwise 0 (if for example the file could not be
 *         read. In that case, it also calls the fn_error_printf function).
 */
int fn_picture_splash_show(char * datapath,
    char * filename,
    Uint8 pixelsize,
    SDL_Surface * screen);

/* --------------------------------------------------------------- */

/**
 * Show a splash picture on the screen and display a message.
 * This function waits for input of the Escape or Return key, then
 * it returns.
 * 
 * @param  datapath   The directory where the data files are stored.
 * @param  filename   The filename of the picture to show.
 *                    Usually one of: BADGUY.DN1, CREDITS.DN1, DN.DN1, DUKE.DN1
 * @param  pixelsize  The pixel size.
 * @param  screen     The surface to which the image is finally blitted.
 * @param  tilecache  The tilecache from which the fonts are loaded.
 *                    If this is NULL, no message will be displayed.
 * @param  message    A string containing the message. Must have a
 *                    trailing \n otherwise the last line will be omitted.
 *                    If this is NULL, no message will be displayed.
 * @param  x          The x offset of the message (in pixels).
 * @param  y          The y offset of the message (in pixels).
 *
 * @return 1 on success, otherwise 0 (if for example the file could not be
 *         read. In that case, it also calls the fn_error_printf function).
 */
int fn_picture_splash_show_with_message(char * datapath,
    char * filename,
    Uint8 pixelsize,
    SDL_Surface * screen,
    fn_tilecache_t * tilecache,
    char * message,
    Uint8 x,
    Uint8 y);

/* --------------------------------------------------------------- */

#endif /* FN_PICTURE_SPLASH */
