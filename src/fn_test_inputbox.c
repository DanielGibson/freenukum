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
#include "fn_inputbox.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv) {
  SDL_Surface * screen;

  fn_environment_t * env = fn_environment_create();
  fn_environment_load_tilecache(env);
  
  screen = fn_environment_get_screen(env);

  char answer[30] = "";
  fn_inputbox_answer_t entered =
    fn_inputbox_show(env,
        "Please enter your name:",
        answer,
        30);

  if (entered == fn_inputbox_answer_ok) {
    printf("Okay.\n");
    printf("You entered %s.\n", answer);
  } else {
    printf("Aborted.\n");
  }
        
  return 0;
}


