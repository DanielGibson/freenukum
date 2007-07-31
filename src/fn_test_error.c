/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for Error handling
 * $Id: fn_test_error.c 15 2006-07-02 11:49:56Z sttereo3 $
 *******************************************************************/

#include <stdio.h>

/* --------------------------------------------------------------- */

#include "fn_error.h"

/* --------------------------------------------------------------- */

void print_error(char * error)
{
  printf("%s\n", error);
}
/* --------------------------------------------------------------- */

int main()
{

  fn_error_set_handler(&print_error);
  fn_error_print("hello.");

  fn_error_printf(100, "Hello %d, Test %s %s %s!\n",
      103,
      "Testtesttesttesttesttest testtesttest",
      "aanwerserlaerasdfsdfqwer",
      "aanselisnekrkasd;lfknase;rlkasnd;rlkanwerlkwenrs"
      );

  return 0;
}
