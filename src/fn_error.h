/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Error handling
 * $Id: fn_error.h 15 2006-07-02 11:49:56Z sttereo3 $
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
