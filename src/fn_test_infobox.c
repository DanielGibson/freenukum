/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Infobox drawing function test
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

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"
#include "fn_infobox.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv) {
  fn_environment_t * env = fn_environment_create();
  fn_environment_load_tilecache(env);

  fn_infobox_show(env, "This is...\n");
  fn_infobox_show(env, "...the great\nInfobox test case.\n");
  fn_infobox_show(env, "now\nwith\neven\nmore\nlines.\n");
  
  return 0;
}

