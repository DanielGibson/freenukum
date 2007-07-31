/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Error printing routine for command-line
 *******************************************************************/

#include <stdio.h>

/* --------------------------------------------------------------- */

void fn_error_print_commandline(char * message)
{
  fprintf(stderr, "%s\n", message);
}
