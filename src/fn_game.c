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
#include <stdlib.h>
#include <time.h>

/* --------------------------------------------------------------- */

#include "fn_environment.h"
#include "fn_hero.h"
#include "fn_game.h"
#include "fn_borders.h"
#include "fn_picture_splash.h"
#include "fn_infobox.h"
#include "fn_level.h"
#include "fn_drop.h"

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
    fn_environment_t * env)
{
  int res;

  /* Initialize Random Number Generator. */
  srand(time(NULL));

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

  char filename[30];

  snprintf(
      filename, 30, "BADGUY.DN%d", fn_environment_get_episode(env));
  res = fn_picture_splash_show_with_message(
      env,
      filename,
      msg1,
      0,
      144);

  snprintf(
      filename, 30, "DUKE.DN%d", fn_environment_get_episode(env));
  res = fn_picture_splash_show_with_message(
      env,
      filename,
      msg2,
      79,
      144);

  SDL_Surface * screen = fn_environment_get_screen(env);
  SDL_FillRect(screen, NULL, 0);

  fn_borders_blit(env);

  fn_borders_blit_life(env);

  fn_borders_blit_score(env);

  fn_borders_blit_firepower(env);

  fn_borders_blit_inventory(env);

  SDL_UpdateRect(screen, 0, 0, 0, 0);

  { /* start the game itself */

    int level = 1;
    int interlevel = 0;
    int success = 1;

    fn_infobox_show(env,
        "Get ready FreeNukum,\nyou are going in.\n");

    while (success && level < 13) {
      if (interlevel) {
        /* interlevel */
        success = fn_game_start_in_level(2,
            env);
        level++;
        if (level == 2) {
          level++;
        }
        interlevel = 0;
      } else {
        /* real level */
        success = fn_game_start_in_level(level,
            env);
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
    fn_environment_t * env)
{
  int returnvalue = 0;
  int fd = 0;
  fn_level_t * lv = NULL;
  SDL_Rect dstrect;
  SDL_Rect srcrect;
  SDL_Event event;
  int res = 0;
  int doupdate = 1;

  fn_hero_t * hero = fn_environment_get_hero(env);

  SDL_Surface * level = fn_environment_create_surface(
      env,
      FN_TILE_WIDTH * FN_LEVEL_WIDTH,
      FN_TILE_HEIGHT * FN_LEVEL_HEIGHT);

  SDL_Surface * backdrop = NULL;;
  SDL_TimerID tick = 0;
  int backdropnumber = 0;

  switch(levelnumber) {
    case 1:
      backdropnumber = 0;
      break;
    case 3:
      backdropnumber = 0;
      break;
    case 4:
      backdropnumber = 7;
      break;
    case 5:
      backdropnumber = 3;
      break;
    case 6:
      backdropnumber = 2;
      break;
    case 7:
      backdropnumber = 1;
      break;
    case 8:
      backdropnumber = 3;
      break;
    case 9:
      backdropnumber = 5;
      break;
    case 10:
      backdropnumber = 1;
      break;
    default:
      backdropnumber = 1;
      break;
  }

  char backdropfile[1024];
  snprintf(backdropfile,
      1024,
      "%s/DROP%d.DN%d",
      fn_environment_get_datapath(env),
      backdropnumber,
      fn_environment_get_episode(env));
  fd = open(backdropfile, O_RDONLY);

  if (fd == -1)
  {
    fprintf(stderr, "Could not open file %s\n", backdropfile);
    perror("Can't open file");
  } else {
    fn_tileheader_t h;
    fn_tile_loadheader(fd, &h);
    backdrop = fn_drop_load(fd,
        env);
    if (backdrop == NULL) {
      printf("could not load backdrop");
    }
    close(fd);
  }

  char levelfile[1024];
  snprintf(levelfile, 1024, "%s/WORLDAL%X.DN%d",
      fn_environment_get_datapath(env),
      levelnumber,
      fn_environment_get_episode(env));
  fd = open(levelfile, O_RDONLY);

  if (fd == -1)
  {
    fprintf(stderr, "Could not open file %s\n", levelfile);
    perror("Can't open file");
    goto cleanup;
  }

  lv = fn_level_load(fd, env);
  if (lv == NULL)
  {
    close(fd);
    fprintf(stderr, "Could not load level from file %s\n", levelfile);
    goto cleanup;
  }
  close(fd);

  Uint8 pixelsize = fn_environment_get_pixelsize(env);
  dstrect.x = FN_TILE_WIDTH * pixelsize;
  dstrect.y = FN_TILE_HEIGHT * pixelsize;
  dstrect.w = (FN_LEVELWINDOW_WIDTH + 2) * pixelsize * FN_TILE_WIDTH;
  dstrect.h = (FN_LEVELWINDOW_HEIGHT + 2) * pixelsize * FN_TILE_HEIGHT;

  srcrect.x = (fn_hero_get_x(hero)+FN_TILE_WIDTH) * pixelsize -
    dstrect.w / 2;
  srcrect.y = fn_hero_get_y(hero) * pixelsize - dstrect.h / 2;
  if (srcrect.x < 0) {
    srcrect.x = 0;
  }
  if (srcrect.y < 0) {
    srcrect.y = 0;
  }
  srcrect.w = FN_LEVELWINDOW_WIDTH * pixelsize * FN_TILE_WIDTH;
  srcrect.h = FN_LEVELWINDOW_HEIGHT * pixelsize * FN_TILE_HEIGHT;

  tick = SDL_AddTimer(80, fn_game_timer_triggered, 0);

  {
    /* make the first frame appear */
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = fn_event_heromoved;
    event.user.data1 = hero;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
  }

  Uint8 directions = 0;

  int updateWholeScreen = 1;

  SDL_Surface * screen =
    fn_environment_get_screen(env);

  /* The mainloop of the level */
  while (fn_level_keep_on_playing(lv))
  {
    if (doupdate) {
      SDL_Surface * screen = fn_environment_get_screen(env);
      fn_level_blit_to_surface(lv,
          level,
          &srcrect,
          &srcrect,
          backdrop,
          NULL);
      SDL_BlitSurface(level, &srcrect, screen, &dstrect);
      if (updateWholeScreen) {
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        updateWholeScreen = 0;
      } else {
        SDL_UpdateRect(screen,
            dstrect.x,
            dstrect.y,
            dstrect.w,
            dstrect.h);
      }
      doupdate = 0;
    }

    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_QUIT:
          goto cleanup;
          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_q:
            case SDLK_ESCAPE:
              goto cleanup;
              break;
            case SDLK_1:
              fn_hero_set_inventory(hero, fn_hero_get_inventory(hero) |
                  FN_INVENTORY_KEY_RED);
              updateWholeScreen = 1;
              break;
            case SDLK_2:
              fn_hero_set_inventory(hero, fn_hero_get_inventory(hero) |
                  FN_INVENTORY_KEY_GREEN);
              updateWholeScreen = 1;
              break;
            case SDLK_3:
              fn_hero_set_inventory(hero, fn_hero_get_inventory(hero) |
                  FN_INVENTORY_KEY_BLUE);
              updateWholeScreen = 1;
              break;
            case SDLK_4:
              fn_hero_set_inventory(hero, fn_hero_get_inventory(hero) |
                  FN_INVENTORY_KEY_PINK);
              updateWholeScreen = 1;
              break;
            case SDLK_5:
              fn_hero_set_inventory(hero, fn_hero_get_inventory(hero) |
                  FN_INVENTORY_BOOT);
              updateWholeScreen = 1;
              break;
            case SDLK_6:
              fn_hero_set_inventory(hero, fn_hero_get_inventory(hero) |
                  FN_INVENTORY_GLOVE);
              updateWholeScreen = 1;
              break;
            case SDLK_7:
              fn_hero_set_inventory(hero, fn_hero_get_inventory(hero) |
                  FN_INVENTORY_CLAMP);
              updateWholeScreen = 1;
              break;
            case SDLK_8:
              fn_hero_set_inventory(hero, fn_hero_get_inventory(hero) |
                  FN_INVENTORY_ACCESS_CARD);
              updateWholeScreen = 1;
              break;
            case SDLK_9:
              fn_hero_set_firepower(hero, fn_hero_get_firepower(hero) +
                  1);
              updateWholeScreen = 1;
              break;
            case SDLK_0:
              lv->levelpassed = 1;
              lv->do_play = 0;
              break;
            case SDLK_f:
              fn_environment_toggle_fullscreen(env);
              break;
            case SDLK_DOWN:
              if (event.key.keysym.mod & KMOD_SHIFT) {
                if (srcrect.y + srcrect.h
                    < FN_LEVEL_HEIGHT * pixelsize * FN_TILE_HEIGHT) {
                  srcrect.y += pixelsize * FN_HALFTILE_HEIGHT;
                }
              }
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
              doupdate = 1;
              break;
            case SDLK_LEFT:
              if (event.key.keysym.mod & KMOD_SHIFT) {
                if (srcrect.x > 0) {
                  srcrect.x -= pixelsize * FN_HALFTILE_WIDTH;
                }
              } else {
                directions |= FNK_LEFT_ENABLED;
                if (directions & FNK_RIGHT_ENABLED) {
                  fn_hero_set_motion(hero, FN_HERO_MOTION_NONE);
                } else {
                  fn_hero_set_direction(hero,
                      fn_horizontal_direction_left);
                  fn_hero_set_motion(hero, FN_HERO_MOTION_WALKING);
                }
                fn_hero_update_animation(hero);
              }
              doupdate = 1;
              break;
            case SDLK_RIGHT:
              if (event.key.keysym.mod & KMOD_SHIFT) {
                if (srcrect.x + srcrect.w
                    < FN_LEVEL_WIDTH * pixelsize * FN_TILE_WIDTH) {
                  srcrect.x += pixelsize * FN_HALFTILE_WIDTH;
                }
              } else {
                directions |= FNK_RIGHT_ENABLED;
                if (directions & FNK_LEFT_ENABLED) {
                  fn_hero_set_motion(hero, FN_HERO_MOTION_NONE);
                } else {
                  fn_hero_set_direction(hero,
                      fn_horizontal_direction_right);
                  fn_hero_set_motion(hero, FN_HERO_MOTION_WALKING);
                }
                fn_hero_update_animation(hero);
              }
              doupdate = 1;
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
              directions &= ~FNK_LEFT_ENABLED;
              if (directions & FNK_RIGHT_ENABLED) {
                fn_hero_set_direction(hero,
                    fn_horizontal_direction_right);
                fn_hero_set_motion(hero, FN_HERO_MOTION_WALKING);
              } else {
                fn_hero_set_motion(hero, FN_HERO_MOTION_NONE);
              }
              fn_hero_update_animation(hero);
              break;
            case SDLK_RIGHT:
              directions &= ~FNK_RIGHT_ENABLED;
              if (directions & FNK_LEFT_ENABLED) {
                  fn_hero_set_direction(hero,
                      fn_horizontal_direction_left);
                  fn_hero_set_motion(hero, FN_HERO_MOTION_WALKING);
              } else {
                fn_hero_set_motion(hero, FN_HERO_MOTION_NONE);
              }
              break;
            case SDLK_LALT:
              fn_hero_fire_stop(hero);
              fn_hero_update_animation(hero);
              break;
            default:
              /* do nothing on other keys. */
              break;
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
          switch(event.button.button) {
            case SDL_BUTTON_LEFT:
              fn_hero_fire_start(hero);
              fn_level_fire_shot(lv);
              fn_hero_update_animation(hero);
              break;
            case SDL_BUTTON_RIGHT:
              fn_hero_set_flying(hero, FN_HERO_FLYING_TRUE);
              fn_hero_update_animation(hero);
              break;
            case SDL_BUTTON_MIDDLE:
              fn_level_hero_interact_start(lv);
              doupdate = 1;
              break;
            default:
              /* do nothing on other buttons. */
              break;
          }
          break;
        case SDL_MOUSEBUTTONUP:
          switch(event.button.button) {
            case SDL_BUTTON_LEFT:
              fn_hero_fire_stop(hero);
              fn_hero_update_animation(hero);
              break;
            case SDL_BUTTON_RIGHT:
              break;
            case SDL_BUTTON_MIDDLE:
              fn_level_hero_interact_stop(lv);
              doupdate = 1;
              break;
            default:
              /* do nothing on other buttons. */
              break;
          }
        case SDL_VIDEOEXPOSE:
          SDL_UpdateRect(screen, 0, 0, 0, 0);
          break;
        case SDL_USEREVENT:
          switch(event.user.code) {
            case fn_event_timer:
              fn_level_act(lv);
              doupdate = 1;
              break;
            case fn_event_heromoved:
              {
                SDL_Rect * heropos = fn_hero_get_position(hero);
                srcrect.x = pixelsize *
                  (heropos->x + heropos->w / 2 -
                   FN_LEVELWINDOW_WIDTH * FN_TILE_WIDTH / 2);
                if (srcrect.x < 0) {
                  srcrect.x = 0;
                }
                srcrect.y = pixelsize *
                  (heropos->y -
                   FN_LEVELWINDOW_HEIGHT * FN_TILE_HEIGHT / 2);
                if (srcrect.y < 0) {
                  srcrect.y = 0;
                }
                if (srcrect.x + srcrect.w >
                    FN_LEVEL_WIDTH * FN_TILE_WIDTH * pixelsize)
                {
                  srcrect.x =
                    FN_LEVEL_WIDTH * FN_TILE_WIDTH * pixelsize -
                    srcrect.w;
                }
                if (srcrect.y + srcrect.h >
                    FN_LEVEL_HEIGHT * FN_TILE_HEIGHT * pixelsize)
                {
                  srcrect.y =
                    FN_LEVEL_HEIGHT * FN_TILE_HEIGHT * pixelsize -
                    srcrect.h;
                }
              }
              break;
            case fn_event_heroscored:
              fn_borders_blit_score(
                  env);
              /* TODO separately update this area. */
              updateWholeScreen = 1;
              break;
            case fn_event_hero_firepower_changed:
              fn_borders_blit_firepower(env);
              /* TODO separately update this area. */
              updateWholeScreen = 1;
              break;
            case fn_event_hero_inventory_changed:
              fn_borders_blit_inventory(env);
              /* TODO separately update this area. */
              updateWholeScreen = 1;
              break;
            case fn_event_hero_health_changed:
              fn_borders_blit_life(env);
              /* TODO separately update this area. */
              updateWholeScreen = 1;
              break;
            case fn_event_herolanded:
              fn_level_add_actor(lv, FN_ACTOR_DUSTCLOUD,
                  fn_hero_get_x(hero),
                  fn_hero_get_y(hero) + FN_TILE_HEIGHT
                  );
              break;
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
  }

cleanup:
  if (backdrop != NULL) {
    SDL_FreeSurface(backdrop);
  }
  if (lv != NULL) {
    returnvalue = lv->levelpassed;
    fn_level_free(lv);
  }
  SDL_RemoveTimer(tick);
  SDL_FreeSurface(level);

  return returnvalue;
}

