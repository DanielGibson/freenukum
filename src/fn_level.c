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
#include "fn_hero.h"
#include "fn_object.h"

/* --------------------------------------------------------------- */

fn_level_t * fn_level_load(int fd,
    size_t pixelsize,
    fn_tilecache_t * tilecache)
{
  size_t i = 0;
  fn_level_t * lv = malloc(sizeof(fn_level_t));
  memset(lv, 0, sizeof(fn_level_t));
  Uint16 tilenr;
  Uint8 uppertile;
  Uint8 lowertile;
  Uint16 previous_solid = SOLID_START;
  Uint16 previous_nonsolid = BACKGROUND_START;

  lv->pixelsize = pixelsize;
  lv->tilecache = tilecache;
  lv->layer_background = SDL_CreateRGBSurface(
      SDL_SWSURFACE,
      FN_PART_WIDTH * pixelsize * FN_LEVEL_WIDTH,
      FN_PART_HEIGHT * pixelsize * FN_LEVEL_HEIGHT,
      FN_COLOR_DEPTH,
      0,
      0,
      0,
      0);

  lv->pixelsize = pixelsize;
  lv->tilecache = tilecache;
  lv->layer_hero = SDL_CreateRGBSurface(
      SDL_SWSURFACE,
      FN_PART_WIDTH * pixelsize * FN_LEVEL_WIDTH,
      FN_PART_HEIGHT * pixelsize * FN_LEVEL_HEIGHT,
      FN_COLOR_DEPTH,
      0,
      0,
      0,
      0);

  lv->layer_animations = SDL_CreateRGBSurface(
      SDL_SWSURFACE,
      FN_PART_WIDTH * pixelsize * FN_LEVEL_WIDTH,
      FN_PART_HEIGHT * pixelsize * FN_LEVEL_HEIGHT,
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
      if (lv->solid[y][x]) {
        previous_solid = tilenr;
      } else {
        previous_nonsolid = tilenr;
      }
    }

    switch(tilenr) {
      case 0x3000: /* grey box, empty */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
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
        /* TODO */
        break;
      case 0x3007: /* rocket which gets started if shot
                    * and leaves a blue box with a balloon */
        /* TODO */
        break;
      case 0x3008: /* grey box with clamps inside */
        /* TODO */
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
        /* TODO */
        break;
      case 0x300d: /* carbot */
        /* TODO */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        break;
      case 0x300e: /* fire wheel bot */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x300F: /* grey box with gun inside */
        /* TODO */
        break;
      case 0x3010: /* robot */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3011: /* exit door */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        /* TODO */
        break;
      case 0x3012: /* grey box with bomb inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
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
        /* TODO */
        break;
      case 0x3016: /* crab bot crawling along wall left of him */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        /* TODO */
        break;
      case 0x3017: /* crab bot crawling along wall right of him */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        /* TODO */
        break;
      case 0x3018: /* red box with chicken inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
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
        /* TODO */
        break;
      case 0x301e: /* blue box with joystick inside */
        /* TODO */
        break;
      case 0x301f: /* blue box with disk inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3020: /* grey box with glove inside */
        /* TODO */
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
        /* TODO */
        break;
      case 0x3024: /* camera */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO*/
        break;
      case 0x3025: /* broken wall background */
        /* take the part from one above */
        if (y > 0) {
          lv->tiles[y][x] = lv->tiles[y-1][x];
        }
        /* add the animation object */
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, ANIM_BROKENWALLBG);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
        }
        break;
      case 0x3026: /* left end of background stone wall */
        /* TODO */
        break;
      case 0x3027: /* right end of background stone wall */
        /* TODO */
        break;
      case 0x3028: /* window inside background stone wall */
        lv->tiles[y][x] = 0;
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, ANIM_STONEWINDOWBG);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
        }
        break;
      case 0x3029: /* grey box with full life */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x302a: /* "ACME" brick that comes falling down */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
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
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_SPIKE);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
        }
        /* TODO */
        break;
      case 0x302d: /* blue box with flag inside */
        /* TODO */
        break;
      case 0x302e: /* blue box with radio inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
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
        /* TODO */
        break;
      case 0x3034: /* slot for access card */
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_ACCESS_CARD_SLOT);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
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
        /* TODO */
        break;
      case 0x3038: /* grey box with a U inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3039: /* grey box with a K inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x303a: /* grey box with a E inside */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
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
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, ANIM_WINDOWBG);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
        }
        break;
      case 0x303f: /* window - right part */
        lv->tiles[y][x] = 0;
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, ANIM_WINDOWBG + 1);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
        }
        break;
      case 0x3040: /* the notebook */
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_NOTE);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
        }
        /* TODO */
        break;
      case 0x3041: /* the surveillance screen */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile1 = fn_tilecache_get_tile(
              lv->tilecache, ANIM_BADGUYSCREEN);
          SDL_Surface * tile2 = fn_tilecache_get_tile(
              lv->tilecache, ANIM_BADGUYSCREEN+1);
          SDL_Surface * tile = SDL_CreateRGBSurface(
              SDL_SWSURFACE,
              FN_PART_WIDTH * pixelsize * 2,
              FN_PART_HEIGHT * pixelsize,
              FN_COLOR_DEPTH, 0, 0, 0, 0);
          SDL_Rect r;
          r.x = FN_PART_WIDTH * pixelsize;
          r.y = 0;
          r.w = FN_PART_WIDTH * pixelsize;
          r.h = FN_PART_HEIGHT * pixelsize;
          SDL_BlitSurface(tile1, NULL, tile, NULL);
          SDL_BlitSurface(tile2, NULL, tile, &r);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
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
        /* TODO */
        break;
      case 0x3045: /* green key */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3046: /* blue key */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3047: /* pink key */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3048: /* red keyhole */
        /* add the animation object */
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_KEYHOLE_RED);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
        }
        /* TODO */
        break;
      case 0x3049: /* green keyhole */
        /* add the animation object */
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_KEYHOLE_GREEN);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
        }
        /* TODO */
        break;
      case 0x304a: /* blue keyhole */
        /* add the animation object */
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_KEYHOLE_BLUE);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
        }
        /* TODO */
        break;
      case 0x304b: /* pink keyhole */
        /* add the animation object */
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_KEYHOLE_PINK);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
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
        /* TODO */
        break;
      case 0x3051: /* single chicken on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3052: /* soda on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3053: /* a disk on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3054: /* a joystick on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3055: /* a flag on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
        break;
      case 0x3056: /* a radio on its own */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* TODO */
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
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_SPIKES_UP);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
        }
        /* TODO */
        break;
      case 0x3059: /* spikes showing down */
        if (x > 0) {
          lv->tiles[y][x] = lv->tiles[y][x-1];
        }
        /* add the animation object */
        if (lv->num_animations < FN_MAX_ANIMATIONS) {
          SDL_Surface * tile = fn_tilecache_get_tile(
              lv->tilecache, OBJ_SPIKES_DOWN);
          fn_animation_init(&(lv->animations[lv->num_animations++]),
              1, /* number of frames */
              &tile, /* surface(s) */
              0, /* start frame */
              x, y, lv->pixelsize);
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

void fn_level_destroy(fn_level_t * level)
{
  free(level);
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

Uint8 fn_level_is_solid(fn_level_t * lv, size_t x, size_t y)
{
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
  SDL_Rect r;
  SDL_Surface * tile;
  Uint32 transparent = SDL_MapRGB(lv->layer_background->format, 100, 1, 1);
  r.x = 0;
  r.y = 0;
  r.w = FN_PART_WIDTH * lv->pixelsize;
  r.h = FN_PART_HEIGHT * lv->pixelsize;

  /* load the background tiles */
  SDL_FillRect(lv->layer_background, NULL, transparent);
  SDL_SetColorKey(lv->layer_background, SDL_SRCCOLORKEY, transparent);
  for (j = 0; j != FN_LEVEL_HEIGHT; j++)
  {
    for (i = 0; i != FN_LEVEL_WIDTH; i++)
    {
      r.x = i * FN_PART_WIDTH * lv->pixelsize;
      r.y = j * FN_PART_HEIGHT * lv->pixelsize;
      if (r.x < FN_PART_WIDTH * lv->pixelsize * FN_LEVEL_WIDTH &&
          r.y < FN_PART_HEIGHT * lv->pixelsize * FN_LEVEL_HEIGHT)
      {
        int tilenr = fn_level_get_tile(lv, i, j);
        if (tilenr < (48 * 8)) {
          tile = fn_tilecache_get_tile(lv->tilecache, tilenr);
        } else {
          tile = fn_tilecache_get_tile(lv->tilecache, 0);
        }
        SDL_BlitSurface(tile, NULL, lv->layer_background, &r);
      }
    }
  }

  /* blit the animation objects */
  SDL_FillRect(lv->layer_animations, NULL, transparent);
  SDL_SetColorKey(lv->layer_animations, SDL_SRCCOLORKEY, transparent);
  for (i = 0; i < lv->num_animations; i++) {
    fn_animation_blit(&(lv->animations[i]), lv->layer_animations);
  }

  /* blit the hero */
  SDL_FillRect(lv->layer_hero, NULL, transparent);
  SDL_SetColorKey(lv->layer_hero, SDL_SRCCOLORKEY, transparent);
  fn_hero_blit(&(lv->hero),
      lv->layer_hero,
      lv->tilecache,
      lv->pixelsize);

  /* blit the whole thing to the caller */
  SDL_BlitSurface(lv->layer_background, sourcerect, target, targetrect);
  SDL_BlitSurface(lv->layer_animations, sourcerect, target, targetrect);
  SDL_BlitSurface(lv->layer_hero, sourcerect, target, targetrect);
}
