/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Main menu
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

#include "fn_mainmenu.h"
#include "fn_menu.h"
#include "fn_msgbox.h"

/* --------------------------------------------------------------- */

int fn_mainmenu(fn_tilecache_t * tilecache,
    Uint8 pixelsize,
    SDL_Surface * screen)
{
  int choice = 0;
  char * msg =
    "\n"
    "  FREENUKUM MAIN MENU \n"
    "  ------------------- \n"
    "\n";
  fn_menu_t * menu = fn_menu_create(msg);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_START,
      "S)tart a new game",
      FN_MENUCHOICE_START);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_RESTORE,
      "R)estore an old game",
      FN_MENUCHOICE_RESTORE);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_INSTRUCTIONS,
      "I)nstructions",
      FN_MENUCHOICE_INSTRUCTIONS);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_ORDERINGINFO,
      "O)rdering information",
      FN_MENUCHOICE_ORDERINGINFO);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_FULLSCREENTOGGLE,
      "F)ullscreen toggle",
      FN_MENUCHOICE_FULLSCREENTOGGLE);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_EPISODECHANGE,
      "E)pisode change",
      FN_MENUCHOICE_EPISODECHANGE);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_HIGHSCORES,
      "H)igh scores",
      FN_MENUCHOICE_HIGHSCORES);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_PREVIEWS,
      "P)reviews/Main Demo!",
      FN_MENUCHOICE_PREVIEWS);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_VIEWUSERDEMO,
      "V)iew user demo",
      FN_MENUCHOICE_VIEWUSERDEMO);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_TITLESCREEN,
      "T)itle screen",
      FN_MENUCHOICE_TITLESCREEN);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_CREDITS,
      "C)redits",
      FN_MENUCHOICE_CREDITS);
  fn_menu_append_entry(
      menu,
      FN_MENUCHOICE_QUIT,
      "Q)it to DOS",
      FN_MENUCHOICE_QUIT);

  choice = fn_menu_get_choice(menu, tilecache, pixelsize, screen);

  if (choice == '\0') {
    choice = FN_MENUCHOICE_QUIT;
  }

  return choice;
}
