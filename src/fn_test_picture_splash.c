/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tests for picture splash functions
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

#include "fn.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"
#include "fn_picture_splash.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  fn_environment_t * env = fn_environment_create();
  fn_environment_load_tilecache(env);
  int res;
  SDL_Surface * screen;

  fn_error_set_handler(fn_error_print_commandline);

  screen = fn_environment_get_screen(env);

  res = fn_picture_splash_show(env, "DN.DN1");
  
  return 0;
}
