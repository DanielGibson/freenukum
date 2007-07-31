/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Error printing routine for command-line
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
