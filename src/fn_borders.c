/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Border drawing functions
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
#include "fn_borders.h"
#include "fn_object.h"
#include "fn_text.h"

/* --------------------------------------------------------------- */

void fn_borders_blit_tile(
    fn_environment_t * env,
    FnTexture * target,
    FnTexture * tile,
    int x,
    int y)
{
  FnGeometry * dstrect;
  dstrect = fn_geometry_new(
      FN_HALFTILE_WIDTH * x,
      FN_HALFTILE_HEIGHT * y,
      0,
      0);
  fn_texture_clone_to_texture(
      tile,
      NULL,
      target,
      dstrect);
}

/* --------------------------------------------------------------- */

void fn_borders_blit_array(
    fn_environment_t * env,
    FnTexture * target,
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
          env,
          target,
          fn_environment_get_tile(env, tile_base + pos),
          i % width,
          i / width);
    }
  }

}

/* --------------------------------------------------------------- */

void fn_borders_blit(
    fn_environment_t * env)
{
  static int borders
    [ (2*FN_WINDOW_HEIGHT/FN_TILE_HEIGHT)
    * (2*FN_WINDOW_WIDTH/FN_TILE_WIDTH)]
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

  FnGraphicOptions * graphic_options =
    fn_environment_get_graphic_options(env);

  FnTexture * texture =
    fn_texture_new_with_options(
        FN_WINDOW_WIDTH,
        FN_WINDOW_HEIGHT,
        graphic_options);

  fn_borders_blit_array(
      env,
      texture,
      borders,
      2 * FN_WINDOW_WIDTH / FN_TILE_WIDTH,
      2 * FN_WINDOW_HEIGHT / FN_TILE_HEIGHT,
      BORD_GREY_START
      );

  FnScreen * screen =
    fn_environment_get_screen(env);

  fn_screen_clone_texture(screen, NULL, texture, NULL);

  g_object_unref(texture);
}

/* --------------------------------------------------------------- */

void fn_borders_blit_life(
    fn_environment_t * env)
{
  FnGraphicOptions * graphic_options;
  FnTexture * lifetexture;
  FnGeometry * dstrect;
  FnScreen * screen;

  graphic_options =
    fn_environment_get_graphic_options(env);
  lifetexture =
    fn_texture_new_with_options(
        FN_FONT_WIDTH * FN_NUM_MAXLIFE,
        FN_TILE_HEIGHT,
        graphic_options
        );
  dstrect =
    fn_geometry_new(
        30 * FN_FONT_WIDTH,
        7.5 * FN_FONT_HEIGHT,
        FN_NUM_MAXLIFE * FN_FONT_WIDTH,
        FN_TILE_HEIGHT);
  screen =
    fn_environment_get_screen(env);

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

  for (i = 0; i < fn_environment_get_health(env); i++) {
    *(lifetiles + i) = OBJ_HEALTH;
  }

  fn_borders_blit_array(
      env, lifetexture, lifetiles, FN_NUM_MAXLIFE, 1, 0
      );

  fn_screen_clone_texture(screen, dstrect, lifetexture, NULL);

  g_object_unref(lifetexture);
  g_object_unref(dstrect);
}

/* --------------------------------------------------------------- */

void fn_borders_blit_score(
    fn_environment_t * env)
{
  FnGraphicOptions * graphic_options;
  FnTexture * scoresurface;
  SDL_Rect dstrect;

  char scoretext[FN_SCORE_DIGITS+1];

  graphic_options =
    fn_environment_get_graphic_options(env);
  scoresurface = fn_texture_new_with_options(
      FN_FONT_WIDTH * FN_SCORE_DIGITS,
      FN_FONT_HEIGHT,
      graphic_options
      );

  sprintf(scoretext, "%08llu",
      (long long unsigned int)fn_environment_get_score(env));

  fn_text_print(
      scoresurface,
      NULL,
      env,
      scoretext
      );

  Uint8 pixelsize = fn_environment_get_pixelsize(env);
  dstrect.x = 30 * pixelsize * FN_FONT_WIDTH;
  dstrect.y = 3 * pixelsize * FN_FONT_HEIGHT;
  dstrect.w = FN_NUM_MAXLIFE * FN_FONT_WIDTH * pixelsize;
  dstrect.h = FN_TILE_HEIGHT * pixelsize;

  SDL_Surface * screen = fn_environment_get_screen_sdl(env);
  fn_texture_blit_to_sdl_surface(scoresurface, NULL, screen, &dstrect);
  g_object_unref(scoresurface);
}

/* --------------------------------------------------------------- */

void fn_borders_blit_firepower(
    fn_environment_t * env)
{
  FnGraphicOptions * graphic_options;
  FnTexture * firepowertexture;
  FnGeometry * destrect;
  FnScreen * screen;

  int i;

  /* height of 4,
   * width of 2*FN_NUM_MAXFIREPOWER */
  int firepowertiles[FN_NUM_MAXFIREPOWER * 2 * 4] = {
    -1, -1, -1, OBJ_GUN, -1, -1, -1, -1,
    -1, -1, -1,      -1, -1, -1, -1, -1,
    -1, -1, -1,      -1, -1, -1, -1, -1,
    -1, -1, -1,      -1, -1, -1, -1, -1
  };

  for (i = 0; i < fn_environment_get_firepower(env); i++) {
    *(firepowertiles + FN_NUM_MAXFIREPOWER * 4 + i*2) = OBJ_SHOT;
  }

  graphic_options =
    fn_environment_get_graphic_options(env);
  firepowertexture = fn_texture_new_with_options(
      FN_TILE_WIDTH * FN_NUM_MAXFIREPOWER,
      FN_TILE_HEIGHT * 2,
      graphic_options
      );

  fn_borders_blit_array(
      env,
      firepowertexture, firepowertiles,
      FN_NUM_MAXFIREPOWER * 2, 4, 0
      );

  destrect = fn_geometry_new(
      30 * FN_FONT_WIDTH,
      12 * FN_FONT_HEIGHT,
      FN_NUM_MAXFIREPOWER * FN_TILE_WIDTH,
      FN_TILE_HEIGHT * 2);

  screen = fn_environment_get_screen(env);

  fn_screen_clone_texture(screen, destrect, firepowertexture, NULL);
  g_object_unref(firepowertexture);
}

/* --------------------------------------------------------------- */

void fn_borders_blit_inventory(
    fn_environment_t * env)
{
  FnGraphicOptions * graphic_options;
  FnTexture * inventorytexture;
  FnGeometry * destrect;
  FnScreen * screen;

  int i;

  int inventorytiles[FN_SIZE_INVENTORY * 2 * 2] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1
  };

  Uint8 inventory = fn_environment_get_inventory(env);
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
    if (inventory & FN_INVENTORY_GLOVE)
      inventorytiles[18] = OBJ_ROBOHAND;
    if (inventory & FN_INVENTORY_CLAMP)
      inventorytiles[20] = OBJ_CLAMP;
    if (inventory & FN_INVENTORY_ACCESS_CARD)
      inventorytiles[22] = OBJ_ACCESS_CARD;
  }

  graphic_options = fn_environment_get_graphic_options(env);

  inventorytexture = fn_texture_new_with_options(
      FN_TILE_WIDTH * FN_SIZE_INVENTORY / 2,
      FN_TILE_HEIGHT * 2,
      graphic_options);

  fn_borders_blit_array(
      env,
      inventorytexture, inventorytiles,
      FN_NUM_MAXFIREPOWER * 2, 4, 0
      );

  destrect = fn_geometry_new(
      30 * FN_FONT_WIDTH,
      18 * FN_FONT_HEIGHT,
      FN_NUM_MAXFIREPOWER * FN_TILE_WIDTH,
      FN_TILE_HEIGHT * 2);

  fn_screen_clone_texture(screen, destrect, inventorytexture, NULL);
  g_object_unref(inventorytexture);
}

/* --------------------------------------------------------------- */
