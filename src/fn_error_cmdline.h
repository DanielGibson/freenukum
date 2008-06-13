/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Error printing routine for command-line
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

#ifndef FN_ERROR_CMDLINE
#define FN_ERROR_CMDLINE

/* --------------------------------------------------------------- */

/**
 * Print an error to the commandline.
 * This function is intended to be used as a callback function
 * that handles the output of fn_error_print() and fn_error_printf()
 * functions. It can be passed to the fn_error_set_handler()
 * function as the handler function.
 *
 * @param  message  The character string that contains the message.
 */
void fn_error_print_commandline(char * message);

/* --------------------------------------------------------------- */

#endif /* FN_ERROR_CMDLINE */
