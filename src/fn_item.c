/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Item struct
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

#include "fn_item.h"
#include "fn_object.h"

fn_item_t * fn_item_create(
    fn_item_type_e type,
    fn_tilecache_t * tilecache,
    Uint8 pixelsize,
    size_t x,
    size_t y)
{
  fn_item_t * item = malloc(sizeof(fn_item_t));
  item->type = type;
  item->tilecache = tilecache;
  item->pixelsize = pixelsize;
  item->x = x;
  item->y = y;
  return item;
}

void fn_item_blit(
    fn_item_t * item,
    SDL_Surface * target)
{
  SDL_Rect dstrect;
  SDL_Surface * tile = NULL;
  dstrect.x = item->x * item->pixelsize * FN_HALFTILE_WIDTH;
  dstrect.y = item->y * item->pixelsize * FN_HALFTILE_HEIGHT;
  dstrect.w = FN_TILE_WIDTH * item->pixelsize;
  dstrect.h = FN_TILE_HEIGHT * item->pixelsize;

  /* build up the tile surface and blit it */
  switch(item->type) {
    case FN_ITEM_TYPE_BOX_GREY_EMPTY:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_BOOTS:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_CLAMPS:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_GUN:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_BOMB:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_RED_SODA:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_RED);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_RED_CHICKEN:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_RED);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_BLUE_FOOTBALL:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_BLUE);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_BLUE_JOYSTICK:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_BLUE);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_BLUE_DISK:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_BLUE);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_GLOVE:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_BLUE_BALLOON:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_BLUE);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_FULL_LIFE:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_BLUE_FLAG:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_BLUE);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_BLUE_RADIO:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_BLUE);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_ACCESS_CARD:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_D:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_U:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_K:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_BOX_GREY_E:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_BOX_GREY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_FOOTBALL:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_FOOTBALL);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_CHICKEN_SINGLE:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_CHICKEN_SINGLE);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_CHICKEN_DOUBLE:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_CHICKEN_DOUBLE);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_SODA:
      tile = fn_tilecache_get_tile(item->tilecache,
          ANIM_SODA);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_SODA_FLYING:
      tile = fn_tilecache_get_tile(item->tilecache,
          ANIM_SODAFLY);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_DISK:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_DISK);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_JOYSTICK:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_JOYSTICK);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_FLAG:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_FLAG);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_ITEM_TYPE_RADIO:
      tile = fn_tilecache_get_tile(item->tilecache,
          OBJ_RADIO);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    default:
      /* TODO */
      break;
  }
}

void fn_item_free(fn_item_t * item) {
  free(item);
}

void fn_item_hero_touch(
    fn_item_t * item,
    fn_hero_t * hero)
{
  switch(item->type) {
    case FN_ITEM_TYPE_FOOTBALL:
      /* TODO */
      break;
    default:
      /* TODO */
      break;
  }
}

size_t fn_item_get_x(fn_item_t * item)
{
  return item->x;
}

size_t fn_item_get_y(fn_item_t * item)
{
  return item->y;
}
