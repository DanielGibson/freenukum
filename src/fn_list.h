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

typedef struct fn_list_t fn_list_t;

struct fn_list_t {
  /**
   * The next list item.
   */
  fn_list_t * next;
  /**
   * The data item.
   */
  void * data;
};

/* --------------------------------------------------------------- */

/**
 * Append an item to the list.
 *
 * @param  list  The list.
 * @param  data  The data object to append.
 *
 * @return The new list.
 */
fn_list_t * fn_list_append(fn_list_t * list,
    void * data);

/* --------------------------------------------------------------- */

/**
 * Get the first iterator.
 *
 * @param  list  The list.
 *
 * @return The first object.
 */
fn_list_t * fn_list_first(fn_list_t * list);

/* --------------------------------------------------------------- */

/**
 * Get the last iterator.
 *
 * @param  list  The list.
 *
 * @return The last object.
 */
fn_list_t * fn_list_last(fn_list_t * list);

/* --------------------------------------------------------------- */

/**
 * Set an iterator to the next list element.
 *
 * @param  list  The current list iterator.
 *
 * @return The new iterator.
 */
fn_list_t * fn_list_next(fn_list_t * list);

/* --------------------------------------------------------------- */

/**
 * Free a list.
 *
 * @param  list  The list.
 */
void fn_list_free(fn_list_t * list);

/* --------------------------------------------------------------- */

/**
 * Remove all occurrences of a list item.
 *
 * @param  list  The list.
 * @param  data  The data to remove.
 *
 * @return The changed list.
 */
fn_list_t * fn_list_remove_all(fn_list_t * list, void * data);

/* --------------------------------------------------------------- */

