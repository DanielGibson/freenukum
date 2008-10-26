/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for hero blitting
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
#include "fn_tile.h"
#include "fn_tilecache.h"
#include "fn_hero.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"

/* --------------------------------------------------------------- */

#define EVENT_CODE_TIMER 1

/* --------------------------------------------------------------- */

Uint32 animate(Uint32 interval, void * param) {
  SDL_Event userevent;

  userevent.type = SDL_USEREVENT;
  userevent.user.code = EVENT_CODE_TIMER;
  userevent.user.data1 = NULL;
  userevent.user.data2 = NULL;
  SDL_PushEvent(&userevent);
  return interval;
}

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
  fn_environment_t * env = fn_environment_create();
  fn_environment_load_tilecache(env);
  fn_hero_t * hero;

  int res;
  SDL_Event event;


  int quit = 0;

  SDL_TimerID timer;

  fn_error_set_handler(fn_error_print_commandline);

  /* here comes the hero!!!!! */
  hero = fn_hero_create(0, 0);
  SDL_Surface * screen = fn_environment_get_screen(env);
  fn_hero_blit(hero, screen, NULL);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  timer = SDL_AddTimer(250, animate, NULL);

  while (quit == 0) {
    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_QUIT:
          quit = 1;
          break;
        case SDL_USEREVENT:
          if (event.user.code == EVENT_CODE_TIMER) {
            SDL_FillRect(screen, NULL, 0);
            fn_hero_update_animation(hero);
            fn_hero_next_animationframe(hero);
            fn_hero_blit(hero, screen, NULL);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
          }
          break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
          switch(event.key.keysym.sym) {
            case SDLK_q:
            case SDLK_ESCAPE:
              quit = 1;
              break;
            case SDLK_RIGHT:
            case SDLK_LEFT:
              if (event.key.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT) {
                  fn_hero_set_direction(hero,
                      fn_horizontal_direction_right);
                } else {
                  fn_hero_set_direction(hero,
                      fn_horizontal_direction_left);
                }
                fn_hero_set_motion(hero, FN_HERO_MOTION_WALKING);
              } else if (event.key.type == SDL_KEYUP) {
                fn_hero_set_motion(hero, FN_HERO_MOTION_NONE);
              }
              break;
            case SDLK_LCTRL:
            case SDLK_RCTRL:
              if (event.key.type == SDL_KEYDOWN) {
                fn_hero_jump(hero);
              }
              break;
            case SDLK_LALT:
            case SDLK_RALT:
              fn_hero_set_flying(hero, FN_HERO_FLYING_FALSE);
              break;
            default:
              /* do nothing, ignoring other keys. */
              break;
          }
        case SDL_VIDEOEXPOSE:
          SDL_UpdateRect(screen, 0, 0, 0, 0);
          break;
        default:
          /* do nothing */
          break;
      }
    }
  }

  return 0;
}
