/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Border drawing functions
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

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_borders.h"
#include "fn_object.h"
#include "fn_text.h"

/* --------------------------------------------------------------- */

void fn_borders_blit_tile(
    SDL_Surface * screen,
    SDL_Surface * tile,
    int x,
    int y,
    Uint8 pixelsize)
{
  SDL_Rect dstrect;
  dstrect.x = FN_PART_WIDTH/2 * pixelsize * x;
  dstrect.y = FN_PART_HEIGHT/2 * pixelsize * y;
  SDL_BlitSurface(
      tile,
      NULL,
      screen,
      &dstrect);
}

/* --------------------------------------------------------------- */

void fn_borders_blit_array(
    SDL_Surface * screen,
    fn_tilecache_t * tc,
    Uint8 pixelsize,
    int * borders,
    Uint8 width,
    Uint8 height,
    int tile_base)
{
  int i;
  int pos;

  for (i = 0; i < width * height; i++) {
    if ((pos = borders [i]) >= 0) {
      fn_borders_blit_tile(
          screen,
          fn_tilecache_get_tile(tc, tile_base + pos),
          i % width,
          i / width,
          pixelsize);
    }
  }

}

/* --------------------------------------------------------------- */

void fn_borders_blit(
    SDL_Surface * screen,
    fn_tilecache_t * tc,
    Uint8 pixelsize)
{
  static int borders
    [ (2*FN_WINDOW_HEIGHT/FN_PART_HEIGHT)
    * (2*FN_WINDOW_WIDTH/FN_PART_WIDTH)]
    =
  {
      4,-1, 2,-1, 2,-1, 2,-1, 2,-1, 2,-1, 2,-1, 2,-1, 2,-1, 2,-1,
      2,-1, 2,-1, 2,-1, 2,-1, 5,-1, 8,-1,38,-1,39,-1, 8,-1, 9,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

      0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

      0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,14,-1, 8,-1,36,-1,37,-1, 8,-1,15,-1,

      0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,

      0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

      0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,14,-1, 8,33,-1,34,-1,35,-1, 8,15,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

      0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

      0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

      0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,14,-1, 8,30,-1,31,-1,32,-1, 8,15,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

      0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

      0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

      7,-1, 3,-1, 3,-1, 3, -1,3,-1, 3,26,-1,27,-1,28,-1,29,-1, 3,
      3,-1, 3,-1, 3,-1, 3,-1, 6,-1, 8,-1, 8,-1, 8,-1, 8,-1,11,-1,
 
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

  };

  fn_borders_blit_array(
    screen,
    tc,
    pixelsize,
    borders,
    2 * FN_WINDOW_WIDTH / FN_PART_WIDTH,
    2 * FN_WINDOW_HEIGHT / FN_PART_HEIGHT,
    BORD_GREY_START
    );
}

/* --------------------------------------------------------------- */

void fn_borders_blit_life(
    SDL_Surface * screen,
    fn_tilecache_t * tc,
    Uint8 pixelsize,
    Uint8 life)
{
  SDL_Surface * lifesurface;
  SDL_Rect dstrect;

  int i;

  int lifetiles[FN_NUM_MAXLIFE] = {
    OBJ_NONHEALTH,
    OBJ_NONHEALTH,
    OBJ_NONHEALTH,
    OBJ_NONHEALTH,
    OBJ_NONHEALTH,
    OBJ_NONHEALTH,
    OBJ_NONHEALTH,
  };

  for (i = 0; i < life; i++) {
    *(lifetiles + i) = OBJ_HEALTH;
  }

  lifesurface = SDL_CreateRGBSurface(
      SDL_SWSURFACE,
      FN_FONT_WIDTH * pixelsize * FN_NUM_MAXLIFE,
      FN_PART_HEIGHT * pixelsize,
      FN_COLOR_DEPTH,
      0,
      0,
      0,
      0);

  fn_borders_blit_array(
      lifesurface, tc, pixelsize, lifetiles, FN_NUM_MAXLIFE, 1, 0
      );

  dstrect.x = 30 * pixelsize * FN_FONT_WIDTH;
  dstrect.y = 7.5 * pixelsize * FN_FONT_HEIGHT;
  dstrect.w = FN_NUM_MAXLIFE * FN_FONT_WIDTH * pixelsize;
  dstrect.h = FN_PART_HEIGHT * pixelsize;

  SDL_BlitSurface(lifesurface, NULL, screen, &dstrect);
  SDL_FreeSurface(lifesurface);
}

/* --------------------------------------------------------------- */

void fn_borders_blit_score(
    SDL_Surface * screen,
    fn_tilecache_t * tc,
    Uint8 pixelsize,
    Uint32 score)
{
  SDL_Surface * scoresurface;
  SDL_Rect dstrect;

  char scoretext[FN_SCORE_DIGITS+1];

  sprintf(scoretext, "%08d", score);

  scoresurface = SDL_CreateRGBSurface(
      SDL_SWSURFACE,
      FN_FONT_WIDTH * pixelsize * FN_SCORE_DIGITS,
      FN_FONT_HEIGHT * pixelsize,
      FN_COLOR_DEPTH,
      0,
      0,
      0,
      0);

  fn_text_print(
      scoresurface,
      NULL,
      tc,
      scoretext,
      pixelsize
      );

  dstrect.x = 30 * pixelsize * FN_FONT_WIDTH;
  dstrect.y = 3 * pixelsize * FN_FONT_HEIGHT;
  dstrect.w = FN_NUM_MAXLIFE * FN_FONT_WIDTH * pixelsize;
  dstrect.h = FN_PART_HEIGHT * pixelsize;

  SDL_BlitSurface(scoresurface, NULL, screen, &dstrect);
  SDL_FreeSurface(scoresurface);
}

/* --------------------------------------------------------------- */

void fn_borders_blit_firepower(
    SDL_Surface * screen,
    fn_tilecache_t * tc,
    Uint8 pixelsize,
    Uint8 firepower)
{
  SDL_Surface * firepowersurface;
  SDL_Rect dstrect;

  int i;

  /* height of 4,
   * width of 2*FN_NUM_MAXFIREPOWER */
  int firepowertiles[FN_NUM_MAXFIREPOWER * 2 * 4] = {
    -1, -1, -1, OBJ_GUN, -1, -1, -1, -1,
    -1, -1, -1,      -1, -1, -1, -1, -1,
    -1, -1, -1,      -1, -1, -1, -1, -1,
    -1, -1, -1,      -1, -1, -1, -1, -1
  };

  for (i = 0; i < firepower; i++) {
    *(firepowertiles + FN_NUM_MAXFIREPOWER * 4 + i*2) = OBJ_SHOT;
  }

  firepowersurface = SDL_CreateRGBSurface(
      SDL_SWSURFACE,
      FN_PART_WIDTH * pixelsize * FN_NUM_MAXFIREPOWER,
      FN_PART_HEIGHT * pixelsize * 2,
      FN_COLOR_DEPTH,
      0,
      0,
      0,
      0);

  fn_borders_blit_array(
      firepowersurface, tc, pixelsize, firepowertiles,
      FN_NUM_MAXFIREPOWER * 2, 4, 0
      );

  dstrect.x = 30 * pixelsize * FN_FONT_WIDTH;
  dstrect.y = 12 * pixelsize * FN_FONT_HEIGHT;
  dstrect.w = FN_NUM_MAXFIREPOWER * FN_PART_WIDTH * pixelsize;
  dstrect.h = FN_PART_HEIGHT * 2 * pixelsize;

  SDL_BlitSurface(firepowersurface, NULL, screen, &dstrect);
  SDL_FreeSurface(firepowersurface);
}

/* --------------------------------------------------------------- */

void fn_borders_blit_inventory(
    SDL_Surface * screen,
    fn_tilecache_t * tc,
    Uint8 pixelsize,
    Uint8 inventory)
{
  SDL_Surface * inventorysurface;
  SDL_Rect dstrect;

  int i;

  int inventorytiles[FN_SIZE_INVENTORY * 2 * 2] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1
  };

  for (i = 0; i < FN_SIZE_INVENTORY; i++) {
    if (inventory & FN_INVENTORY_KEY_RED)
      inventorytiles[0] = OBJ_KEY_RED;
    if (inventory & FN_INVENTORY_KEY_GREEN)
      inventorytiles[2] = OBJ_KEY_GREEN;
    if (inventory & FN_INVENTORY_KEY_BLUE)
      inventorytiles[4] = OBJ_KEY_BLUE;
    if (inventory & FN_INVENTORY_KEY_PINK)
      inventorytiles[6] = OBJ_KEY_PINK;
    if (inventory & FN_INVENTORY_BOOT)
      inventorytiles[16] = OBJ_BOOT;
    if (inventory & FN_INVENTORY_ROBOHAND)
      inventorytiles[18] = OBJ_ROBOHAND;
    if (inventory & FN_INVENTORY_CLAMP)
      inventorytiles[20] = OBJ_CLAMP;
    if (inventory & FN_INVENTORY_ACCESS_CARD)
      inventorytiles[22] = OBJ_ACCESS_CARD;
  }

  inventorysurface = SDL_CreateRGBSurface(
      SDL_SWSURFACE,
      FN_PART_WIDTH * pixelsize * FN_SIZE_INVENTORY/2,
      FN_PART_HEIGHT * pixelsize * 2,
      FN_COLOR_DEPTH,
      0,
      0,
      0,
      0);

  fn_borders_blit_array(
      inventorysurface, tc, pixelsize, inventorytiles,
      FN_NUM_MAXFIREPOWER * 2, 4, 0
      );

  dstrect.x = 30 * pixelsize * FN_FONT_WIDTH;
  dstrect.y = 18 * pixelsize * FN_FONT_HEIGHT;
  dstrect.w = FN_NUM_MAXFIREPOWER * FN_PART_WIDTH * pixelsize;
  dstrect.h = FN_PART_HEIGHT * 2 * pixelsize;

  SDL_BlitSurface(inventorysurface, NULL, screen, &dstrect);
  SDL_FreeSurface(inventorysurface);
}

/* --------------------------------------------------------------- */
