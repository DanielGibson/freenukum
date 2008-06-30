/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    A simple linked list - test functions
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

#include <stdlib.h>
#include <stdio.h>

/* --------------------------------------------------------------- */

#include "fn_list.h"

/* --------------------------------------------------------------- */

void printlist(fn_list_t * list)
{
  fn_list_t * iter;

  printf("List:\n");
  for (iter = fn_list_first(list);
      iter != fn_list_last(list);
      iter = fn_list_next(iter))
  {
    printf("element: %d\n", (int)(iter->data));
  }
}

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  fn_list_t * list = NULL;

  list = fn_list_append(list, (void *)1);

  printlist(list);

  list = fn_list_append(list, (void *)2);
  list = fn_list_append(list, (void *)3);
  list = fn_list_append(list, (void *)2);

  printlist(list);

  list = fn_list_remove_all(list, (void *)2);

  printlist(list);

  return 0;
}

