/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Error handling
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

#include <string.h>

/* --------------------------------------------------------------- */

typedef void (*fn_error_handler_f)(char *);

/* --------------------------------------------------------------- */

/**
 * Show an error. This function does not show the error itself,
 * but instead calls the handler function that was set by
 * the fn_error_set_handler function.
 *
 * @param  error  The description to set.
 */
void fn_error_print(char * error);

/* --------------------------------------------------------------- */

/**
 * Show an error using the printf function.
 * This function does not show the error by itself,
 * but instead calls the handler function that was set by
 * the fn_error_set_handler function.
 *
 * @param  len         The maximum length that the error message can have.
 *                     This is used for internal memory allocation.
 * @param  format      The format that shall be used.
 *                     This is in the same format as the printf() function.
 * @param  ...         The additional parameters.
 *                     Also see printf functionality for this.
 */
void fn_error_printf(size_t len, char * format, ...);

/* --------------------------------------------------------------- */

/**
 * Set an error handler.
 *
 * @param  h  The handler function.
 */
void fn_error_set_handler(fn_error_handler_f h);
/* --------------------------------------------------------------- */
