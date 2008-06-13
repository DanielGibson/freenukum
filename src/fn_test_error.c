/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for Error handling
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
