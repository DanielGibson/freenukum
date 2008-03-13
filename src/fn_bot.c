/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Bot struct
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

#include "fn_bot.h"
#include "fn_object.h"

/* --------------------------------------------------------------- */

fn_bot_t * fn_bot_create(
    fn_bot_type_e type,
    fn_hero_t * hero,
    fn_tilecache_t * tilecache,
    Uint8 pixelsize,
    size_t x,
    size_t y)
{
  fn_bot_t * bot = malloc(sizeof(fn_bot_t));
  bot->x = x;
  bot->y = y;
  bot->pixelsize = pixelsize;
  bot->tilecache = tilecache;
  bot->type = type;
  bot->hero = hero;

  switch(type) {
    case FN_BOT_TYPE_FIREWHEEL:
      /* TODO */
      break;
    case FN_BOT_TYPE_FLAMEGNOME:
      /* TODO */
      break;
    case FN_BOT_TYPE_FLYINGBOT:
      /* TODO */
      break;
    case FN_BOT_TYPE_FOOTBOT:
      /* TODO */
      break;
    case FN_BOT_TYPE_HELICOPTER:
      /* TODO */
      break;
    case FN_BOT_TYPE_RABBITOID:
      /* TODO */
      break;
    case FN_BOT_TYPE_REDBALL_JUMPING:
      /* TODO */
      break;
    case FN_BOT_TYPE_REDBALL_LYING:
      /* TODO */
      break;
    case FN_BOT_TYPE_ROBOT:
      /* TODO */
      break;
    case FN_BOT_TYPE_SNAKEBOT:
      /* TODO */
      break;
    case FN_BOT_TYPE_TANKBOT:
      /* TODO */
      break;
    case FN_BOT_TYPE_WALLCRAWLER_LEFT:
      /* TODO */
      break;
    case FN_BOT_TYPE_WALLCRAWLER_RIGHT:
      /* TODO */
      break;
    case FN_BOT_TYPE_DRPROTON:
      /* TODO */
      break;
    case FN_BOT_TYPE_CAMERA:
      /* no data to store here. */
      break;
    default:
      /* TODO - unknown bot */
      break;
  };
  return bot;
}

/* --------------------------------------------------------------- */

void fn_bot_free(fn_bot_t * bot)
{
  free(bot);
}

/* --------------------------------------------------------------- */

void fn_bot_blit(fn_bot_t * bot, SDL_Surface * target)
{
  SDL_Rect dstrect;
  SDL_Surface * tile = NULL;
  dstrect.x = bot->x * bot->pixelsize * FN_HALFTILE_WIDTH;
  dstrect.y = bot->y * bot->pixelsize * FN_HALFTILE_HEIGHT;
  dstrect.w = FN_TILE_WIDTH * bot->pixelsize;
  dstrect.h = FN_TILE_HEIGHT * bot->pixelsize;
  switch(bot->type) {
    case FN_BOT_TYPE_FIREWHEEL:
      /* TODO */
      break;
    case FN_BOT_TYPE_FLAMEGNOME:
      /* TODO */
      break;
    case FN_BOT_TYPE_FLYINGBOT:
      /* TODO */
      break;
    case FN_BOT_TYPE_FOOTBOT:
      {
        tile = fn_tilecache_get_tile(bot->tilecache,
            ANIM_FOOTBOT + 2);
        SDL_BlitSurface(tile, NULL, target, &dstrect);

        dstrect.x += FN_TILE_WIDTH * bot->pixelsize;

        tile = fn_tilecache_get_tile(bot->tilecache,
            ANIM_FOOTBOT + 3);
        SDL_BlitSurface(tile, NULL, target, &dstrect);

        dstrect.x -= FN_TILE_WIDTH * bot->pixelsize;
        dstrect.y -= FN_TILE_HEIGHT * bot->pixelsize;

        tile = fn_tilecache_get_tile(bot->tilecache,
            ANIM_FOOTBOT + 0);
        SDL_BlitSurface(tile, NULL, target, &dstrect);

        dstrect.x += FN_TILE_WIDTH * bot->pixelsize;

        tile = fn_tilecache_get_tile(bot->tilecache,
            ANIM_FOOTBOT + 1);
        SDL_BlitSurface(tile, NULL, target, &dstrect);
      }
      /* TODO */
      break;
    case FN_BOT_TYPE_HELICOPTER:
      /* TODO */
      break;
    case FN_BOT_TYPE_RABBITOID:
      /* TODO */
      break;
    case FN_BOT_TYPE_REDBALL_JUMPING:
      /* TODO */
      break;
    case FN_BOT_TYPE_REDBALL_LYING:
      /* TODO */
      break;
    case FN_BOT_TYPE_ROBOT:
      /* TODO get animation type */
      tile = fn_tilecache_get_tile(bot->tilecache,
          ANIM_ROBOT);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      break;
    case FN_BOT_TYPE_SNAKEBOT:
      /* TODO */
      break;
    case FN_BOT_TYPE_TANKBOT:
      /* TODO */
      {
        tile = fn_tilecache_get_tile(bot->tilecache,
            ANIM_CARBOT);
        SDL_BlitSurface(tile, NULL, target, &dstrect);
        dstrect.x += FN_TILE_WIDTH * bot->pixelsize;
        tile = fn_tilecache_get_tile(bot->tilecache,
            ANIM_CARBOT + 1);
        SDL_BlitSurface(tile, NULL, target, &dstrect);
      }
      break;
    case FN_BOT_TYPE_WALLCRAWLER_LEFT:
      tile = fn_tilecache_get_tile(bot->tilecache,
          ANIM_WALLCRAWLERBOT_LEFT);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_BOT_TYPE_WALLCRAWLER_RIGHT:
      tile = fn_tilecache_get_tile(bot->tilecache,
          ANIM_WALLCRAWLERBOT_RIGHT);
      SDL_BlitSurface(tile, NULL, target, &dstrect);
      /* TODO */
      break;
    case FN_BOT_TYPE_DRPROTON:
      /* TODO */
      break;
    case FN_BOT_TYPE_CAMERA:
      {
        size_t x = fn_hero_get_x(bot->hero);
        if (x-1 > bot->x) {
          tile = fn_tilecache_get_tile(bot->tilecache,
              ANIM_CAMERA_RIGHT);
        } else if (x+1 < bot->x) {
          tile = fn_tilecache_get_tile(bot->tilecache,
              ANIM_CAMERA_LEFT);
        } else {
          tile = fn_tilecache_get_tile(bot->tilecache,
              ANIM_CAMERA_CENTER);
        }
        SDL_BlitSurface(tile, NULL, target, &dstrect);
      }
      break;
    default:
      /* TODO - unknown bot */
      break;
  }
}

/* --------------------------------------------------------------- */

size_t fn_bot_get_x(fn_bot_t * bot)
{
  return bot->x;
}

/* --------------------------------------------------------------- */

size_t fn_bot_get_y(fn_bot_t * bot)
{
  return bot->y;
}

/* --------------------------------------------------------------- */

int fn_bot_get_shot(fn_bot_t * bot)
{
  /* TODO */
  return 0;
}

/* --------------------------------------------------------------- */

void fn_bot_next_animation_frame(fn_bot_t * bot)
{
  /* TODO */
}

/* --------------------------------------------------------------- */

int fn_bot_action_progress(fn_bot_t * bot)
{
  /* TODO */
  return 1;
}

