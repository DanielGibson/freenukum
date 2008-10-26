/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Main menu
 *
 * *****************************************************************
 *
 * Copyright 2008 Wolfgang Silbermayr
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

#ifndef FN_MENU_H
#define FN_MENU_H

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_msgbox.h"
#include "fn_list.h"

/* --------------------------------------------------------------- */

typedef struct fn_menuentry_t {
  /**
   * Shortcut for the entry.
   */
  char shortcut;
  /**
   * Name which is shown to the user.
   */
  char * name;
  /**
   * The value which is returned on choice.
   */
  char value;
} fn_menuentry_t;

/* --------------------------------------------------------------- */

typedef struct fn_menu_t {
  /**
   * The header text
   */
  char * text;
  /**
   * The list of entries.
   */
  fn_list_t * entries;
  /**
   * The currently active entry.
   */
  fn_list_t * currententry;
  /**
   * The number of entries.
   */
  Uint16 num_entries;
  /**
   * The width of the window (in letters).
   */
  Uint16 width;
} fn_menu_t;

/* --------------------------------------------------------------- */

fn_menu_t * fn_menu_create(char * text);

/* --------------------------------------------------------------- */

void fn_menu_free(fn_menu_t * menu);

/* --------------------------------------------------------------- */

char fn_menu_get_choice(
    fn_menu_t * menu,
    fn_environment_t * env);

/* --------------------------------------------------------------- */

void fn_menu_append_entry(
    fn_menu_t * menu,
    char shortcut,
    char * name,
    char value);

/* --------------------------------------------------------------- */

#endif /* FN_MENU_H */
