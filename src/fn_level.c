/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Level functions
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

#include "fn_level.h"
#include "fn_actor.h"
#include "fn_hero.h"
#include "fn_object.h"

/* --------------------------------------------------------------- */

fn_level_t * fn_level_load(int fd,
    Uint8 pixelsize,
    fn_tilecache_t * tilecache)
{
  size_t i = 0;
  fn_level_t * lv = malloc(sizeof(fn_level_t));
  memset(lv, 0, sizeof(fn_level_t));
  Uint16 tilenr;
  Uint8 uppertile;
  Uint8 lowertile;

  lv->animated_frames = 0;

  lv->levelpassed = 0;

  lv->actors = NULL;
  lv->bots = NULL;
  lv->animations = NULL;

  lv->do_play = 1;
  lv->pixelsize = pixelsize;
  lv->tilecache = tilecache;

  lv->surface = SDL_CreateRGBSurface(
      SDL_SWSURFACE,
      FN_TILE_WIDTH * pixelsize * FN_LEVEL_WIDTH,
      FN_TILE_HEIGHT * pixelsize * FN_LEVEL_HEIGHT,
      FN_COLOR_DEPTH,
      0,
      0,
      0,
      0);

  while (i != FN_LEVEL_HEIGHT * FN_LEVEL_WIDTH)
  {
    size_t x = i%FN_LEVEL_WIDTH;
    size_t y = i/FN_LEVEL_WIDTH;

    /* we don't only want to run on big-endian systems,
     * so we load the bytes separately.
     */
    read(fd, &lowertile, 1);
    read(fd, &uppertile, 1);
    tilenr = (uppertile << 8) | lowertile;

    lv->raw[y][x] = tilenr;

    if ((tilenr >= 4) && (tilenr <= 0x2fe0)) {
      lv->tiles[y][x] = tilenr / 0x20;
      lv->solid[y][x] = (tilenr >= 0x1800);
    }

    switch(tilenr) {
      case 0x0080: /* written text on black screen */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_TEXT_ON_SCREEN_BACKGROUND,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0100: /* blue high voltage flash */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_HIGH_VOLTAGE_FLASH_BACKGROUND,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0180: /* red flash light */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_RED_FLASHLIGHT_BACKGROUND,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0200: /* blue high voltage flash */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BLUE_FLASHLIGHT_BACKGROUND,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0280: /* key panel on the wall */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_KEYPANEL_BACKGROUND,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0300: /* red rotation light */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_RED_ROTATIONLIGHT_BACKGROUND,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0380: /* flashing up arrow */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_UPARROW_BACKGROUND,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0400: /* background blinking blue box */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BLUE_LIGHT_BACKGROUND1,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0420: /* background blinking blue box */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BLUE_LIGHT_BACKGROUND2,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0440: /* background blinking blue box */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BLUE_LIGHT_BACKGROUND3,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0460: /* background blinking blue box */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BLUE_LIGHT_BACKGROUND4,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0480: /* background green poison liquid */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_GREEN_POISON_BACKGROUND,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x0500: /* background lava */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_LAVA_BACKGROUND,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3000: /* grey box, empty */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_EMPTY,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3001: /* lift */
        /* TODO */
        break;
      case 0x3002: /* left end of left-moving conveyor */
        /* TODO */
        break;
      case 0x3003: /* right end of left-moving conveyor */
        /* TODO */
        break;
      case 0x3004: /* left end of right-moving conveyor */
        /* TODO */
        break;
      case 0x3005: /* right end of right-moving conveyor */
        /* TODO */
        break;
      case 0x3006: /* grey box with boots inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_BOOTS,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3007: /* rocket which gets started if shot
                    * and leaves a blue box with a balloon */
        /* TODO */
        break;
      case 0x3008: /* grey box with clamps inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_CLAMPS,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3009: /* fire burning to the right */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        /* TODO */
        break;
      case 0x300A: /* fire burning to the left */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        /* TODO */
        break;
      case 0x300b: /* flying techbot */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x300c: /* footbot */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->bots = g_list_append(lv->bots, fn_bot_create(
              FN_BOT_TYPE_FOOTBOT, &(lv->hero), lv->tilecache,
              lv->pixelsize, x*2, y*2));
        break;
      case 0x300d: /* carbot */
        /* TODO */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->bots = g_list_append(lv->bots, fn_bot_create(
              FN_BOT_TYPE_TANKBOT, &(lv->hero), lv->tilecache,
              lv->pixelsize, x*2, y*2));
        break;
      case 0x300e: /* fire wheel bot */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x300F: /* grey box with gun inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_GUN,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3010: /* robot */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->bots = g_list_append(lv->bots, fn_bot_create(
              FN_BOT_TYPE_ROBOT, &(lv->hero), lv->tilecache,
              lv->pixelsize, x*2, y*2));
        break;
      case 0x3011: /* exit door */
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_EXITDOOR,
              x * FN_TILE_WIDTH, (y-1) * FN_TILE_WIDTH));
        break;
      case 0x3012: /* grey box with bomb inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_BOMB,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3013: /* bot consisting of several white-blue balls */
        /* TODO */
        break;
      case 0x3014: /* water mirroring everything that is above */
        /* TODO */
        break;
      case 0x3015: /* red box with soda inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_RED_SODA,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3016: /* crab bot crawling along wall left of him */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
          lv->bots = g_list_append(lv->bots, fn_bot_create(
              FN_BOT_TYPE_WALLCRAWLER_LEFT, &(lv->hero), lv->tilecache,
              lv->pixelsize, x*2, y*2));
        break;
      case 0x3017: /* crab bot crawling along wall right of him */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->bots = g_list_append(lv->bots, fn_bot_create(
              FN_BOT_TYPE_WALLCRAWLER_RIGHT, &(lv->hero), lv->tilecache,
              lv->pixelsize, x*2, y*2));
        break;
      case 0x3018: /* red box with chicken inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_RED_CHICKEN,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3019: /* floor that breaks on second jump onto it */
        /* TODO */
        break;
      case 0x301a: /* horizontal laser beam which gets deactivated when mill is shot */
        /* TODO */
        break;
      case 0x301b: /* fan wheel mounted on right wall blowing to the left */
        /* TODO */
        break;
      case 0x301c: /* fan wheel mounted on left wall blowing to the right*/
        /* TODO */
        break;
      case 0x301d: /* blue box with football insdie */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_BLUE_FOOTBALL,
              x * FN_TILE_WIDTH, y * FN_TILE_WIDTH));
        break;
      case 0x301e: /* blue box with joystick inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_BLUE_JOYSTICK,
              x * FN_TILE_WIDTH, y * FN_TILE_WIDTH));
        break;
      case 0x301f: /* blue box with disk inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_BLUE_DISK,
              x * FN_TILE_WIDTH, y * FN_TILE_WIDTH));
        break;
      case 0x3020: /* grey box with glove inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_GLOVE,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3021: /* laser beam which is deactivated by access card */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3022: /* helicopter */
        /* TODO */
        break;
      case 0x3023: /* blue box with balloon inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_BLUE_BALLOON,
              x * FN_TILE_WIDTH, y * FN_TILE_WIDTH));
        break;
      case 0x3024: /* camera */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->bots = g_list_append(lv->bots, fn_bot_create(
              FN_BOT_TYPE_CAMERA, &(lv->hero), lv->tilecache,
              lv->pixelsize, x*2, y*2));
        break;
      case 0x3025: /* broken wall background */
        /* take the part from one above */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        /* add the animation object */
        SDL_Surface * tile = fn_tilecache_get_tile(
            lv->tilecache, ANIM_BROKENWALLBG);
        lv->animations = g_list_append(lv->animations,
            fn_animation_create(
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize));
        break;
      case 0x3026: /* left end of background stone wall */
        /* TODO */
        break;
      case 0x3027: /* right end of background stone wall */
        /* TODO */
        break;
      case 0x3028: /* window inside background stone wall */
        lv->tiles[y][x] = 0;
        {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, ANIM_STONEWINDOWBG);
          lv->animations = g_list_append(lv->animations,
              fn_animation_create(
                1, /* number of frames */
                &tile, /* surface(s) */
                0, /* start frame */
                x, y, lv->pixelsize));
              }
        break;
      case 0x3029: /* grey box with full life */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_FULL_LIFE,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x302a: /* "ACME" brick that comes falling down */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->solid[y][x] = 1;
        /* TODO */
        break;
      case 0x302b: /* rotating mill that can kill duke on touch */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        /* TODO */
        break;
      case 0x302c: /* single spike standing out of the floor */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        {
          lv->actors = g_list_append(lv->actors,
              fn_actor_create(lv,
                FN_ACTOR_SPIKES_DOWN,
                x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
          break;
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_SPIKE);
          lv->animations = g_list_append(lv->animations,
              fn_animation_create(
                1, /* number of frames */
                &tile, /* surface(s) */
                0, /* start frame */
                x, y, lv->pixelsize));
        }
        /* TODO */
        break;
      case 0x302d: /* blue box with flag inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_BLUE_FLAG,
              x * FN_TILE_WIDTH, y * FN_TILE_WIDTH));
        break;
      case 0x302e: /* blue box with radio inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_BLUE_RADIO,
              x * FN_TILE_WIDTH, y * FN_TILE_WIDTH));
        break;
      case 0x302f: /* beaming station */
        /* TODO */
        break;
      case 0x3030: /* beaming station */
        /* TODO */
        break;
      case 0x3031: /* jumping mines */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3032: /* we found our hero! */
        fn_hero_init(&(lv->hero), x * 2, y * 2);
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        break;
      case 0x3033: /* grey box with the access card inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_ACCESS_CARD,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3034: /* slot for access card */
        {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_ACCESS_CARD_SLOT);
          lv->animations = g_list_append(lv->animations, fn_animation_create(
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize));
        }
        /* TODO */
        break;
      case 0x3035: /* slot for glove */
        /* TODO */
        break;
      case 0x3036: /* floor which expands to right by access of glove slot */
        /* TODO */
        break;
      case 0x3037: /* grey box with a D inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_LETTER_D,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3038: /* grey box with a U inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_LETTER_U,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3039: /* grey box with a K inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_LETTER_K,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x303a: /* grey box with a E inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_BOX_GREY_LETTER_E,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x303b: /* bunny bot */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x303c: /* fire gnome */
        /* TODO */
        break;
      case 0x303d: /* fence with backdrop 1 behind it */
        /* TODO */
        break;
      case 0x303e: /* window - left part */
        lv->tiles[y][x] = 0;
        {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, ANIM_WINDOWBG);
          lv->animations = g_list_append(lv->animations,
              fn_animation_create(
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize));
        }
        break;
      case 0x303f: /* window - right part */
        lv->tiles[y][x] = 0;
        {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, ANIM_WINDOWBG + 1);
          lv->animations = g_list_append(lv->animations,
              fn_animation_create(
                1, /* number of frames */
                &tile, /* surface(s) */
                0, /* start frame */
                x, y, lv->pixelsize));
        }
        break;
      case 0x3040: /* the notebook */
        {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_NOTE);
          lv->animations = g_list_append(lv->animations,
          fn_animation_create(
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize));
        }
        /* TODO */
        break;
      case 0x3041: /* the surveillance screen */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        {
          SDL_Surface * tile1 = fn_tilecache_get_tile(
              lv->tilecache, ANIM_BADGUYSCREEN);
          SDL_Surface * tile2 = fn_tilecache_get_tile(
              lv->tilecache, ANIM_BADGUYSCREEN+1);
          SDL_Surface * tile = SDL_CreateRGBSurface(
              SDL_SWSURFACE,
              FN_TILE_WIDTH * pixelsize * 2,
              FN_TILE_HEIGHT * pixelsize,
              FN_COLOR_DEPTH, 0, 0, 0, 0);
          SDL_Rect r;
          r.x = FN_TILE_WIDTH * pixelsize;
          r.y = 0;
          r.w = FN_TILE_WIDTH * pixelsize;
          r.h = FN_TILE_HEIGHT * pixelsize;
          SDL_BlitSurface(tile1, NULL, tile, NULL);
          SDL_BlitSurface(tile2, NULL, tile, &r);
          lv->animations = g_list_append(lv->animations,
              fn_animation_create(
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize));
        }
        /* TODO */
        break;
      case 0x3043: /* dr proton -the final opponent */
        /* TODO */
        break;
      case 0x3044: /* red key */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_KEY_RED,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3045: /* green key */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_KEY_GREEN,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        /* TODO */
        break;
      case 0x3046: /* blue key */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_KEY_BLUE,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        /* TODO */
        break;
      case 0x3047: /* pink key */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_KEY_PINK,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        /* TODO */
        break;
      case 0x3048: /* red keyhole */
        /* add the animation object */
        {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_KEYHOLE_RED);
          lv->animations = g_list_append(lv->animations,
              fn_animation_create(
                1, /* number of frames */
                &tile, /* surface(s) */
                0, /* start frame */
                x, y, lv->pixelsize));
        }
        /* TODO */
        break;
      case 0x3049: /* green keyhole */
        /* add the animation object */
        {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_KEYHOLE_GREEN);
          lv->animations = g_list_append(lv->animations,
              fn_animation_create(
                1, /* number of frames */
                &tile, /* surface(s) */
                0, /* start frame */
                x, y, lv->pixelsize));
        }
        /* TODO */
        break;
      case 0x304a: /* blue keyhole */
        /* add the animation object */
        {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_KEYHOLE_BLUE);
          lv->animations = g_list_append(lv->animations,
              fn_animation_create(
                1, /* number of frames */
                &tile, /* surface(s) */
                0, /* start frame */
                x, y, lv->pixelsize));
        }
        /* TODO */
        break;
      case 0x304b: /* pink keyhole */
        /* add the animation object */
        {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_KEYHOLE_PINK);
          lv->animations = g_list_append(lv->animations,
              fn_animation_create(
                1, /* number of frames */
                &tile, /* surface(s) */
                0, /* start frame */
                x, y, lv->pixelsize));
        }
        /* TODO */
        break;
      case 0x304c: /* red door */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x304d: /* green door */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x304e: /* blue door */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x304f: /* pink door */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3050: /* football on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_FOOTBALL,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3051: /* single chicken on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_CHICKEN_SINGLE,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3052: /* soda on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_SODA,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3053: /* a disk on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_DISK,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3054: /* a joystick on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_JOYSTICK,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3055: /* a flag on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_FLAG,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3056: /* a radio on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        lv->actors = g_list_append(lv->actors,
            fn_actor_create(lv,
              FN_ACTOR_RADIO,
              x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
        break;
      case 0x3057: /* the red mine lying on the ground */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        /* TODO */
        break;
      case 0x3058: /* spikes showing up */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        /* add the animation object */
        {
          lv->actors = g_list_append(lv->actors,
              fn_actor_create(lv,
                FN_ACTOR_SPIKES_UP,
                x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
          break;
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_SPIKES_UP);
          lv->animations = g_list_append(lv->animations,
              fn_animation_create(
                1, /* number of frames */
                &tile, /* surface(s) */
                0, /* start frame */
                x, y, lv->pixelsize));
        }
        /* TODO */
        break;
      case 0x3059: /* spikes showing down */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* add the animation object */
        {
          lv->actors = g_list_append(lv->actors,
              fn_actor_create(lv,
                FN_ACTOR_SPIKES_DOWN,
                x * FN_TILE_WIDTH, y * FN_TILE_HEIGHT));
          break;
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_SPIKES_DOWN);
          lv->animations = g_list_append(lv->animations,
          fn_animation_create(
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize));
        }
        /* TODO */
        break;
      default:
        if (tilenr / 0x20 >= SOLID_END) {
          fprintf(stderr, "Unknown tile 0x%04x at x: %d, y: %d\n",
              tilenr, x, y);
          lv->tiles[y][x] = 2;
        }
        break;
    }

    i++;
  }
  return lv;
}

/* --------------------------------------------------------------- */

void fn_level_free(fn_level_t * lv)
{
  GList * iter = NULL;
  for (iter = g_list_first(lv->animations);
      iter != g_list_last(lv->animations);
      iter = g_list_next(iter)) {
    fn_animation_free((fn_animation_t *)iter->data);
  }
  g_list_free(lv->animations);

  for (iter = g_list_first(lv->bots);
      iter != g_list_last(lv->bots);
      iter = g_list_next(iter)) {
    fn_bot_free((fn_bot_t *)iter->data);
  }
  g_list_free(lv->bots);

  free(lv);
}

/* --------------------------------------------------------------- */

Uint16 fn_level_get_tile(fn_level_t * lv, size_t x, size_t y)
{
  return lv->tiles[y][x];
}

/* --------------------------------------------------------------- */

Uint16 fn_level_get_raw(fn_level_t * lv, size_t x, size_t y)
{
  return lv->raw[y][x];
}

/* --------------------------------------------------------------- */

Uint8 fn_level_is_solid(fn_level_t * lv, int x, int y)
{
  if (x < 0 || y < 0 || x > FN_LEVEL_WIDTH || y > FN_LEVEL_HEIGHT) {
    return 1;
  }
  return lv->solid[y][x];
}

/* --------------------------------------------------------------- */

void fn_level_blit_to_surface(fn_level_t * lv,
    SDL_Surface * target,
    SDL_Rect * targetrect,
    SDL_Rect * sourcerect)
{
  int j = 0;
  int i = 0;
  int x_start = 0;
  int x_end = FN_LEVEL_WIDTH;
  int y_start = 0;
  int y_end = FN_LEVEL_HEIGHT;
  SDL_Rect r;
  GList * iter = NULL;

  /* calculate the bounds of the area we have to blit. */
  if (sourcerect) {
    x_start = (sourcerect->x / FN_TILE_WIDTH / lv->pixelsize)
      - (FN_LEVELWINDOW_WIDTH / 2);
    if (x_start < 0) {
      x_start = 0;
    }
    x_end = x_start + (sourcerect->w / FN_TILE_WIDTH / lv->pixelsize) * 2;
    if (x_end > FN_LEVEL_WIDTH) {
      x_end = FN_LEVEL_WIDTH;
      x_start = x_end - FN_LEVELWINDOW_WIDTH * 2;
    }

    y_start = (sourcerect->y / FN_TILE_HEIGHT / lv->pixelsize)
      - (FN_LEVELWINDOW_HEIGHT / 2);
    if (y_start < 0) {
      y_start = 0;
    }
    y_end = y_start + (sourcerect->h / FN_TILE_HEIGHT / lv->pixelsize) * 2;
    if (y_end > FN_LEVEL_HEIGHT) {
      y_end = FN_LEVEL_HEIGHT;
      y_start = y_end - FN_LEVELWINDOW_HEIGHT * 2;
    }
  }

  SDL_Surface * tile;
  r.x = 0;
  r.y = 0;
  r.w = FN_TILE_WIDTH * lv->pixelsize;
  r.h = FN_TILE_HEIGHT * lv->pixelsize;

  /* load the background tiles */
  SDL_FillRect(lv->surface, sourcerect, 0);
  for (j = y_start; j != y_end; j++)
  {
    for (i = x_start; i != x_end; i++)
    {
      r.x = i * FN_TILE_WIDTH * lv->pixelsize;
      r.y = j * FN_TILE_HEIGHT * lv->pixelsize;
      if (r.x < FN_TILE_WIDTH * lv->pixelsize * FN_LEVEL_WIDTH &&
          r.y < FN_TILE_HEIGHT * lv->pixelsize * FN_LEVEL_HEIGHT)
      {
        int tilenr = fn_level_get_tile(lv, i, j);
        if (tilenr < (48 * 8)) {
          tile = fn_tilecache_get_tile(lv->tilecache, tilenr);
        } else {
          tile = fn_tilecache_get_tile(lv->tilecache, 0);
        }
        SDL_BlitSurface(tile, NULL, lv->surface, &r);
      }
    }
  }

  /* blit the actors */
  for (iter = g_list_first(lv->actors);
      iter != NULL;
      iter = g_list_next(iter)) {
    fn_actor_t * actor = (fn_actor_t *)iter->data;

    Uint16 x = fn_actor_get_x(actor) / FN_TILE_WIDTH;
    Uint16 y = fn_actor_get_y(actor) / FN_TILE_HEIGHT;

    if (x > x_start && y > y_start && x < x_end && y < y_end) {
      fn_actor_blit(actor);
    }
  }

  /* blit the animation objects */
  for (iter = g_list_first(lv->animations);
      iter != NULL;
      iter = g_list_next(iter)) {
    fn_animation_t * animation = (fn_animation_t *)iter->data;
    Uint16 x = fn_animation_get_x(animation);
    Uint16 y = fn_animation_get_y(animation);
    if (x > x_start && y > y_start && x < x_end && y < y_end) {
      fn_animation_blit(animation, lv->surface);
    }
  }

  /* blit the bots */
  for (iter = g_list_first(lv->bots);
      iter != NULL;
      iter = g_list_next(iter)) {
    fn_bot_t * bot = (fn_bot_t *)iter->data;
    int x = fn_bot_get_x(bot) / 2;
    int y = fn_bot_get_y(bot) / 2;
    if (x > x_start && y > y_start && x < x_end && y < y_end) {
      fn_bot_blit(bot, lv->surface);
    }
  }

  /* blit the hero */
  fn_hero_blit(&(lv->hero),
      lv->surface,
      lv->tilecache,
      lv->pixelsize);


  /* blit the whole thing to the caller */
  SDL_BlitSurface(lv->surface, sourcerect, target, targetrect);
}

/* --------------------------------------------------------------- */

SDL_Surface * fn_level_get_surface(fn_level_t * lv)
{
  return lv->surface;
}

/* --------------------------------------------------------------- */

fn_tilecache_t * fn_level_get_tilecache(fn_level_t * lv)
{
  return lv->tilecache;
}

/* --------------------------------------------------------------- */

Uint8 fn_level_get_pixelsize(fn_level_t * lv)
{
  return lv->pixelsize;
}

/* --------------------------------------------------------------- */

int fn_level_keep_on_playing(fn_level_t * lv) {
  return lv->do_play;
}

/* --------------------------------------------------------------- */

fn_hero_t * fn_level_get_hero(fn_level_t * lv) {
  return &(lv->hero);
}

/* --------------------------------------------------------------- */

int fn_level_act(fn_level_t * lv) {
  GList * iter = NULL;
  int res = 0;
  int cleanup = 0;

  lv->animated_frames ++;
  lv->animated_frames %= 1;
  if (lv->animated_frames == 0) {
    /* do some action, not just animation */
    fn_hero_act(&(lv->hero), lv);
  }

  for (iter = g_list_first(lv->actors);
      iter != NULL;
      iter = g_list_next(iter)) {
    fn_actor_t * actor = (fn_actor_t *)iter->data;

    res = fn_actor_act(actor);
    if (res == 0) {
      /* set the cleanup flag and free the memory */
      cleanup = 1;
      iter->data = 0;
      fn_actor_free(actor); actor = NULL;
    }
  }

  if (cleanup) {
    /* clean up the actors that are finished */
    cleanup = 0;
    lv->actors = g_list_remove_all(lv->actors, 0);
  }

  for (iter = g_list_first(lv->animations);
      iter != NULL;
      iter = g_list_next(iter)) {
    fn_animation_t * anim = (fn_animation_t *)iter->data;
    fn_animation_act(anim);
  }

  fn_hero_next_animationframe(&(lv->hero));
  fn_hero_update_animation(&(lv->hero));

  return 1;
};

/* --------------------------------------------------------------- */

void fn_level_hero_interact_start(fn_level_t * lv)
{
  fn_error_print_commandline("Started interact");
  GList * iter = NULL;
  for (iter = g_list_first(lv->actors);
      iter != NULL;
      iter = g_list_next(iter)) {
    fn_actor_t * actor = (fn_actor_t *)iter->data;
    fn_hero_t * hero = fn_level_get_hero(lv);

    if (actor->x >= (hero->x-2) * FN_HALFTILE_WIDTH &&
        actor->x <= (hero->x+2) * FN_HALFTILE_WIDTH &&
        actor->y >= (hero->y-2) * FN_HALFTILE_HEIGHT &&
        actor->y <= (hero->y+2) * FN_HALFTILE_HEIGHT) {

      fn_actor_hero_interact_start(actor);
    }
  }
}

/* --------------------------------------------------------------- */

void fn_level_hero_interact_stop(fn_level_t * lv)
{
  GList * iter = NULL;
  for (iter = g_list_first(lv->actors);
      iter != NULL;
      iter = g_list_next(iter)) {
    fn_actor_t * actor = (fn_actor_t *)iter->data;
    fn_hero_t * hero = fn_level_get_hero(lv);

    if (actor->x >= (hero->x - FN_TILE_WIDTH) &&
        actor->x <= (hero->x + FN_TILE_WIDTH) &&
        actor->y >= (hero->y - FN_TILE_HEIGHT) &&
        actor->y <= (hero->y + FN_TILE_HEIGHT)) {
      fn_actor_hero_interact_stop(actor);
    }
  }
}

/* --------------------------------------------------------------- */

fn_actor_t * fn_level_add_actor(fn_level_t * lv,
    fn_actor_type_e type,
    Uint16 x,
    Uint16 y)
{
  fn_actor_t * actor = fn_actor_create(lv, type, x, y);
  lv->actors = g_list_append(lv->actors, actor);
  return actor;
}

/* --------------------------------------------------------------- */

