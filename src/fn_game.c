/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Gameplay functions
 *
 * *****************************************************************
 *
 * Copyright 2007 Wolfgang Silbermayr
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

#include "fn_game.h"
#include "fn_borders.h"
#include "fn_picture_splash.h"
#include "fn_infobox.h"
#include "fn_level.h"

/* --------------------------------------------------------------- */

Uint8  health = FN_NUM_MAXLIFE;
Uint8  firepower = 1;
Uint8  inventory = 0x00;
Uint32 score = 0;

/* --------------------------------------------------------------- */

void fn_game_start(
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    SDL_Surface * screen,
    char * datapath)
{
  int res;

  char * msg1 =
    "So you're the pitiful\n"
    "hero they sent to stop\n"
    "me.  I, Dr. Proton, will\n"
    "soon rule the world!\n";
  char * msg2 =
    "You're wrong, Proton\n"
    "breath.  I'll be done\n"
    "with you and still have\n"
    "time to watch Oprah!\n";

  res = fn_picture_splash_show_with_message(
      datapath,
      "BADGUY.DN1",
      (Uint8)pixelsize,
      screen,
      tilecache,
      msg1,
      0,
      120);

  res = fn_picture_splash_show_with_message(
      datapath,
      "DUKE.DN1",
      (Uint8)pixelsize,
      screen,
      tilecache,
      msg2,
      100,
      120);

  SDL_FillRect(screen, NULL, 0);

  fn_borders_blit(
      screen,
      tilecache,
      pixelsize);

  fn_borders_blit_life(
      screen,
      tilecache,
      pixelsize,
      health
      );

  fn_borders_blit_score(
      screen,
      tilecache,
      pixelsize,
      score
      );

  fn_borders_blit_firepower(
      screen,
      tilecache,
      pixelsize,
      firepower);

  fn_borders_blit_inventory(
      screen,
      tilecache,
      pixelsize,
      inventory);

  SDL_UpdateRect(screen, 0, 0, 0, 0);

  fn_infobox_show(pixelsize,
      tilecache,
      screen,
      "Sorry, gameplay is\n"
      "not implemented yet.\n");

}
