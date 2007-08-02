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
 * Freenukum is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *******************************************************************/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* --------------------------------------------------------------- */

#include "fn_error.h"

/* --------------------------------------------------------------- */

static fn_error_handler_f fn_error_handler = NULL;
static char * fn_error_string = NULL;

/* --------------------------------------------------------------- */

void fn_error_print(char * error)
{
  fn_error_string = realloc(fn_error_string, strlen(error) + 1);
  strcpy(fn_error_string, error);
  if (fn_error_handler != NULL)
    fn_error_handler(fn_error_string);
}

/* --------------------------------------------------------------- */

void fn_error_printf(size_t len, char * format, ...)
{
    va_list ap;

    fn_error_string = realloc(fn_error_string, len + 1);

    va_start(ap, format);
    vsnprintf(fn_error_string, len, format, ap);
    va_end(ap);

    if (fn_error_handler != NULL)
      fn_error_handler(fn_error_string);
}

/* --------------------------------------------------------------- */

void fn_error_set_handler(fn_error_handler_f h)
{
  fn_error_handler = h;
}
