/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Error handling
 * $Id: fn_error.c 15 2006-07-02 11:49:56Z sttereo3 $
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
