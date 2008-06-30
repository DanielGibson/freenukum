/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    A simple linked list
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

/* --------------------------------------------------------------- */

#include "fn_list.h"

/* --------------------------------------------------------------- */

fn_list_t * fn_list_append(fn_list_t * list,
    void * data)
{
  fn_list_t * newitem = malloc(sizeof(fn_list_t));
  newitem->data = data;
  newitem->next = NULL;

  fn_list_t * iter = NULL;
  fn_list_t * enditem = NULL;
  /* find the last item */
  for (iter = fn_list_first(list);
      iter != fn_list_last(list);
      iter = fn_list_next(iter))
  {
    enditem = iter;
  }

  if (enditem != NULL) {
    enditem->next = newitem;
  } else {
    list = newitem;
  }
  return list;
}

/* --------------------------------------------------------------- */

fn_list_t * fn_list_first(fn_list_t * list)
{
  return list;
}

/* --------------------------------------------------------------- */

fn_list_t * fn_list_last(fn_list_t * list)
{
  return NULL;
}

/* --------------------------------------------------------------- */

fn_list_t * fn_list_next(fn_list_t * list)
{
  if (list != NULL) {
    return list->next;
  }
  return NULL;
}

/* --------------------------------------------------------------- */

void fn_list_free(fn_list_t * list)
{
  fn_list_t * todelete = list;
  while (list != NULL) {
    todelete = list;
    list = list->next;
    free(todelete); todelete = NULL;
  }
}

/* --------------------------------------------------------------- */

fn_list_t * fn_list_remove_all(fn_list_t * list, void * data)
{
  fn_list_t * prev = NULL;
  fn_list_t * current = list;

  while (current != fn_list_last(list)) {
    if (current->data == data) {
      /* found an occurrence - remove it */
      fn_list_t * todelete = current;
      if (prev != NULL) {
        prev->next = current->next;
      } else {
        list = current->next;
      }
      current = prev;
      free(todelete); todelete = NULL;
    }

    prev = current;
    if (prev != NULL) {
      current = prev->next;
    } else {
      current = NULL;
    }
  }

  return list;
}

/* --------------------------------------------------------------- */

