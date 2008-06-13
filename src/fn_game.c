/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Gameplay functions
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

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/* --------------------------------------------------------------- */

#include "fn_game.h"
#include "fn_borders.h"
#include "fn_picture_splash.h"
#include "fn_infobox.h"
#include "fn_level.h"
#include "fn_drop.h"

/* --------------------------------------------------------------- */

Uint8  health = FN_NUM_MAXLIFE;
Uint8  firepower = 1;
Uint8  inventory = 0x00;
Uint32 score = 0;

/* --------------------------------------------------------------- */

Uint32 fn_game_timer_triggered(
    Uint32 interval,
    void * param)
{
  SDL_Event event;
  event.type = SDL_USEREVENT;
  event.user.code = fn_event_timer;
  event.user.data1 = 0;
  event.user.data2 = 0;
  SDL_PushEvent(&event);
  return interval;
}

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

  { /* start the game itself */

    int level = 1;
    int interlevel = 0;
    int success = 1;

    fn_infobox_show(pixelsize,
        tilecache,
        screen,
        "Sorry, gameplay is\n"
        "not implemented yet.\n"
        "You can browse through the level\n"
        "by pressing the cursor keys though.\n");

    while (success && level < 13) {
      if (interlevel) {
        /* interlevel */
        success = fn_game_start_in_level(2,
            pixelsize,
            tilecache,
            screen,
            datapath);
        level++;
        if (level == 2) {
          level++;
        }
        interlevel = 0;
      } else {
        /* real level */
        success = fn_game_start_in_level(level,
            pixelsize,
            tilecache,
            screen,
            datapath);
        interlevel = 1;
      }
    }

    if (success) {
      /* the player finished, so we show the end sequence */
      /* TODO */
    }
  }

}

int fn_game_start_in_level(
    int levelnumber,
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    SDL_Surface * screen,
    char * datapath)
{
  int returnvalue = 0;
  int fd = 0;
  fn_level_t * lv = 0;
  SDL_Rect dstrect;
  SDL_Rect srcrect;
  SDL_Event event;
  int res = 0;
  int doupdate = 1;
  int x = 0;
  int y = 0;
  SDL_Surface * level = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            FN_TILE_WIDTH * pixelsize * FN_LEVEL_WIDTH,
            FN_TILE_HEIGHT * pixelsize * FN_LEVEL_HEIGHT,
            FN_COLOR_DEPTH,
            0,
            0,
            0,
            0);

  SDL_Surface * backdrop = NULL;;
  int backdropnumber = 0;

  switch(levelnumber) {
    case 1:
      backdropnumber = 0;
      break;
    default:
      backdropnumber = 1;
      break;
  }

  char backdropfile[1024];
  snprintf(backdropfile, 1024, "%s/DROP%d.DN1",
      datapath, backdropnumber);
  fd = open(backdropfile, O_RDONLY);

  if (fd == -1)
  {
    fprintf(stderr, "Could not open file %s\n", backdropfile);
    perror("Can't open file");
    goto cleanup;
  }
  backdrop = fn_drop_load(fd, pixelsize);
  if (backdrop != NULL) {
    printf("loaded backdrop %s\n", backdropfile);
  } else {
    printf("could not load backdrop");
  }
  close(fd);

  SDL_TimerID tick;
  char levelfile[1024];
  snprintf(levelfile, 1024, "%s/WORLDAL%X.DN1",
      datapath, levelnumber);
  fd = open(levelfile, O_RDONLY);

  if (fd == -1)
  {
    fprintf(stderr, "Could not open file %s\n", levelfile);
    perror("Can't open file");
    goto cleanup;
  }

  lv = fn_level_load(fd, pixelsize, tilecache, screen);
  if (lv == NULL)
  {
    close(fd);
    fprintf(stderr, "Could not load level from file %s\n", levelfile);
    goto cleanup;
  }
  close(fd);

  fn_hero_t * hero = fn_level_get_hero(lv);

  dstrect.x = FN_TILE_WIDTH * pixelsize;
  dstrect.y = FN_TILE_HEIGHT * pixelsize;
  dstrect.w = (FN_LEVELWINDOW_WIDTH + 2) * pixelsize * FN_TILE_WIDTH;
  dstrect.h = (FN_LEVELWINDOW_HEIGHT + 2) * pixelsize * FN_TILE_HEIGHT;
  /* TODO get this dynamically from the hero struct. */
  /*srcrect.x = 50 * pixelsize * FN_TILE_WIDTH; */
  /* TODO get this dynamically from the hero struct. */
  /* srcrect.y = 0 * pixelsize * FN_TILE_HEIGHT; */
  srcrect.w = FN_LEVELWINDOW_WIDTH * pixelsize * FN_TILE_WIDTH;
  srcrect.h = FN_LEVELWINDOW_HEIGHT * pixelsize * FN_TILE_HEIGHT;

  tick = SDL_AddTimer(100, fn_game_timer_triggered, 0);

  {
    /* make the first frame appear */
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = fn_event_heromoved;
    event.user.data1 = hero;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
  }

  /* The mainloop of the level */
  while (fn_level_keep_on_playing(lv))
  {
    if (doupdate) {
      /*
      printf("starting blit of level.\n");
      printf("srcrect: x %d, y %d, w %d, h %d\n", srcrect.x, srcrect.y,
          srcrect.w, srcrect.h);
          */
      fn_level_blit_to_surface(lv,
          level,
          &srcrect,
          &srcrect,
          NULL,
          NULL);
      SDL_BlitSurface(level, &srcrect, screen, &dstrect);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      doupdate = 0;
    }

    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_QUIT:
          printf("window close desired\n");
          goto cleanup;
          break;
        case SDL_KEYDOWN:
          printf("key down.\n");
          switch(event.key.keysym.sym) {
            case SDLK_q:
            case SDLK_ESCAPE:
              printf("quitkey pressed\n");
              goto cleanup;
              break;
            case SDLK_DOWN:
              if (event.key.keysym.mod & KMOD_SHIFT) {
                if (srcrect.y + srcrect.h
                    < FN_LEVEL_HEIGHT * pixelsize * FN_TILE_HEIGHT) {
                  srcrect.y += pixelsize * FN_HALFTILE_HEIGHT;
                }
              } else {
                /* TODO move our hero */
              }
              printf("downkey pressed - y: %d\n", srcrect.y);
              doupdate = 1;
              break;
            case SDLK_UP:
              if (event.key.keysym.mod & KMOD_SHIFT) {
                if (srcrect.y > 0) {
                  srcrect.y -= pixelsize * FN_HALFTILE_HEIGHT;
                }
              } else {
                fn_level_hero_interact_start(lv);
              }
              printf("upkey pressed - y: %d\n", srcrect.y);
              doupdate = 1;
              break;
            case SDLK_LEFT:
              if (event.key.keysym.mod & KMOD_SHIFT) {
                if (srcrect.x > 0) {
                  srcrect.x -= pixelsize * FN_HALFTILE_WIDTH;
                }
              } else {
                fn_hero_set_direction(hero,
                    fn_horizontal_direction_left);
                fn_hero_set_motion(hero, FN_HERO_MOTION_WALKING);
                fn_hero_update_animation(hero);
              }
              printf("leftkey pressed - x: %d\n", srcrect.x);
              doupdate = 1;
              break;
            case SDLK_RIGHT:
              if (event.key.keysym.mod & KMOD_SHIFT) {
                if (srcrect.x + srcrect.w
                    < FN_LEVEL_WIDTH * pixelsize * FN_TILE_WIDTH) {
                  srcrect.x += pixelsize * FN_HALFTILE_WIDTH;
                }
              } else {
                fn_hero_set_direction(hero,
                    fn_horizontal_direction_right);
                fn_hero_set_motion(hero, FN_HERO_MOTION_WALKING);
                fn_hero_update_animation(hero);
              }
              doupdate = 1;
              printf("rightkey pressed - x: %d\n", srcrect.x);
              break;
            case SDLK_LCTRL:
              fn_hero_set_flying(hero, FN_HERO_FLYING_TRUE);
              fn_hero_update_animation(hero);
              break;
            case SDLK_LALT:
              fn_hero_fire_start(hero);
              fn_level_fire_shot(lv);
              fn_hero_update_animation(hero);
              break;
            default:
              printf("unknown key pressed.\n");
              /* do nothing on other key input (yet) */
              break;
          }
          break;
        case SDL_KEYUP:
          switch(event.key.keysym.sym) {
            case SDLK_UP:
              fn_level_hero_interact_stop(lv);
              doupdate = 1;
              break;
            case SDLK_LEFT:
            case SDLK_RIGHT:
              fn_hero_set_motion(hero, FN_HERO_MOTION_NONE);
              fn_hero_update_animation(hero);
            case SDLK_LALT:
              fn_hero_fire_stop(hero);
              fn_hero_update_animation(hero);
              break;
            default:
              /* do nothing on other keys. */
              break;
          }
          break;
        case SDL_VIDEOEXPOSE:
          printf("video expose\n");
          SDL_UpdateRect(screen, 0, 0, 0, 0);
          break;
        case SDL_USEREVENT:
          switch(event.user.code) {
            case fn_event_timer:
              fn_level_act(lv);
              doupdate = 1;
              break;
            case fn_event_heromoved:
              x = fn_hero_get_x(hero);
              y = fn_hero_get_y(hero);
              srcrect.x =
                (x - FN_LEVELWINDOW_WIDTH) *
                FN_HALFTILE_WIDTH * pixelsize;
              srcrect.y =
                (y - FN_LEVELWINDOW_HEIGHT + 2) *
                FN_HALFTILE_HEIGHT * pixelsize;
              break;
            case fn_event_heroscored:
              fn_borders_blit_score(
                  screen,
                  tilecache,
                  pixelsize,
                  fn_hero_get_score(hero));
              break;
            case fn_event_hero_inventory_changed:
              fn_borders_blit_inventory(
                  screen,
                  tilecache,
                  pixelsize,
                  fn_hero_get_inventory(hero));
            case fn_event_hero_health_changed:
              fn_borders_blit_life(
                  screen,
                  tilecache,
                  pixelsize,
                  fn_hero_get_health(hero));
            default:
              /* don't do anything on other events. */
              break;
          }
          break;
        case SDL_MOUSEMOTION:
          /* we don't do anything on mouse movement */
          break;
        default:
          printf("unknown event happened.\n");
          /* do nothing on any other events. */
          break;
      }
    }
    returnvalue = lv->levelpassed;
  }

cleanup:
  if (backdrop != NULL) {
    SDL_FreeSurface(backdrop);
  }
  SDL_RemoveTimer(tick);
  fn_level_free(lv);
  SDL_FreeSurface(level);

  return returnvalue;
}

