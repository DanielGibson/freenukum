/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Main menu
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

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* --------------------------------------------------------------- */

#include "fn_menu.h"
#include "fn_text.h"
#include "fn_object.h"

/* --------------------------------------------------------------- */

#define MAXVAL(X,Y) ((X) > (Y) ? (X) : (Y))

/* --------------------------------------------------------------- */

fn_menuentry_t * fn_menuentry_create(
    char shortcut,
    char * name,
    char value)
{
  fn_menuentry_t * entry = malloc(sizeof(fn_menuentry_t));

  entry->shortcut = shortcut;
  entry->name = name;
  entry->value = value;

  return entry;
}

/* --------------------------------------------------------------- */

void fn_menuentry_free(fn_menuentry_t * entry)
{
  free(entry); entry = 0;
}

/* --------------------------------------------------------------- */

fn_menu_t * fn_menu_create(char * text)
{
  fn_menu_t * menu = malloc(sizeof(fn_menu_t));

  menu->text = text;
  menu->entries = NULL;
  menu->currententry = 0;
  menu->num_entries = 0;
  menu->width = 0;

  return menu;
}

/* --------------------------------------------------------------- */

void fn_menu_free(fn_menu_t * menu)
{
  fn_list_t * iter = NULL;
  for (iter = fn_list_first(menu->entries);
      iter != fn_list_last(menu->entries);
      iter = fn_list_next(iter))
  {
    fn_menuentry_free((fn_menuentry_t *)iter->data);
  }
  fn_list_free(menu->entries);
}

/* --------------------------------------------------------------- */

Uint32 fn_menu_timer_triggered(
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

char fn_menu_get_choice(fn_menu_t * menu,
    fn_environment_t * env)
{
  /* TODO This is a dirty workaround which should be removed. */
  Uint16 textrows = 0;
  Uint16 textcols = 0;

  fn_msgbox_get_text_information(menu->text, &textcols, &textrows);

  textcols = MAXVAL(textcols, menu->width);

  char * placeholder =
    malloc((menu->num_entries + textrows) * textcols + 4);
  int i = 0;
  sprintf(placeholder, "%s", menu->text);
  char * walker = placeholder + strlen(menu->text);
  while (i < textcols + 2) {
    *walker = ' ';
    walker++;
    i++;
  }
  while (i < textcols + menu->num_entries + 3) {
    *walker = '\n';
    walker++;
    i++;
  }
  *walker = '\0';

  SDL_Surface * box = fn_msgbox(
      env,
      placeholder);
  free(placeholder);

  SDL_Surface * target =
    fn_environment_create_surface_with_aboslute_size(env,
      box->w,
      box->h);

  SDL_Rect targetrect;

  fn_menuentry_t * entry = NULL;

  SDL_Rect destrect;
  destrect.x = ((fn_environment_get_screen(env)->w)-(target->w))/2;
  destrect.y = ((fn_environment_get_screen(env)->h)-(target->h))/2;
  destrect.w = target->w;
  destrect.h = target->h;

  char choice = '\0';
  SDL_Event event;

  int animationframe = 0;
  int res = 0;

  SDL_EnableKeyRepeat(
      SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

  SDL_TimerID tick = 0;
  tick = SDL_AddTimer(80, fn_menu_timer_triggered, 0);

  Uint8 pixelsize = fn_environment_get_pixelsize(env);

  SDL_Rect pointrect;
  pointrect.x = FN_FONT_WIDTH * pixelsize + destrect.x;
  pointrect.w = FN_FONT_WIDTH * pixelsize;
  pointrect.y = FN_FONT_HEIGHT * pixelsize + destrect.y;
  pointrect.h = FN_FONT_HEIGHT * pixelsize;

  int updateWholeMenu = 0;
  int updateWholeScreen = 1;
  int changed = 1;

  int choice_made = 0;
  while (!choice_made) {

    fn_list_t * iter = NULL;
    SDL_Surface * screen = fn_environment_get_screen(env);

    if (changed) {
      SDL_BlitSurface(box, NULL, target, NULL);
      i = 0;
      for (iter = fn_list_first(menu->entries);
          iter != fn_list_last(menu->entries);
          iter = fn_list_next(iter))
      {
        targetrect.w = FN_FONT_WIDTH * pixelsize * menu->width;
        targetrect.x = FN_FONT_WIDTH * pixelsize * 3;
        targetrect.y = FN_FONT_HEIGHT * pixelsize * (i + textrows + 1);
        targetrect.h = FN_FONT_HEIGHT * pixelsize;
        entry = (fn_menuentry_t *)iter->data;
        fn_text_print(
            target,
            &targetrect,
            env,
            entry->name
            );
        if (i == menu->currententry) {
          targetrect.x -= FN_FONT_WIDTH * pixelsize * 2;
          pointrect.y = targetrect.y + destrect.y;
          fn_tile_blit_to_sdl_surface(
              fn_environment_get_tile(
                env,
                OBJ_POINT + animationframe),
              NULL,
              target,
              &targetrect);
        }
        i++;
      }

      SDL_BlitSurface(target, NULL,
          screen, &destrect);
      if (updateWholeScreen) {
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        updateWholeMenu = 0;
        updateWholeScreen = 0;
      } else if (updateWholeMenu) {
        SDL_UpdateRect(screen,
            destrect.x,
            destrect.y,
            destrect.w,
            destrect.h);
        updateWholeMenu = 0;
      } else {
        SDL_UpdateRect(screen,
            pointrect.x,
            pointrect.y,
            pointrect.w,
            pointrect.h);
      }
      changed = 0;
    }

    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_RETURN:
              entry = fn_menu_get_current_entry(menu);
              choice = entry->shortcut;
              choice_made = 1;
              break;
            case SDLK_ESCAPE:
              choice_made = 1;
              break;
            case SDLK_DOWN:
              menu->currententry++;
              menu->currententry %= menu->num_entries;
              entry = fn_menu_get_current_entry(menu);
              updateWholeMenu = 1;
              break;
            case SDLK_UP:
              if (menu->currententry == 0) {
                menu->currententry = menu->num_entries;
              }
              menu->currententry--;
              entry = fn_menu_get_current_entry(menu);
              updateWholeMenu = 1;
              break;
            default:
              for (iter = fn_list_first(menu->entries);
                  iter != fn_list_last(menu->entries) && !choice;
                  iter = fn_list_next(iter))
              {
                entry = (fn_menuentry_t *)iter->data;
                if (entry->shortcut == event.key.keysym.sym) {
                  choice = entry->shortcut;
                  choice_made = 1;
                }
              }
              break;
          }
          break;
        case SDL_MOUSEMOTION:
          {
            int x = (event.motion.x - destrect.x) / pixelsize
              - FN_FONT_WIDTH * 3;
            int y = (event.motion.y - destrect.y) / pixelsize
              - FN_FONT_HEIGHT * (textrows + 1);
            if (x > 0 && x < FN_FONT_WIDTH * menu->width) {
              int menuitem = y / FN_FONT_HEIGHT;
              if (menuitem >= 0 && menuitem < menu->num_entries) {
                menu->currententry = menuitem;
                updateWholeMenu = 1;
              }
            }
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT) {
            /* we only use left mouse button in the menu */
            int x = (event.button.x - destrect.x) / pixelsize
              - FN_FONT_WIDTH * 3;
            int y = (event.button.y - destrect.y) / pixelsize
              - FN_FONT_HEIGHT * (textrows + 1);
            if (x > 0 && x < FN_FONT_WIDTH * menu->width) {
              int menuitem = y / FN_FONT_HEIGHT;
              if (menuitem >= 0 && menuitem < menu->num_entries) {
                i = 0;
                iter = fn_list_first(menu->entries);
                while (i < menuitem) {
                  iter = fn_list_next(iter);
                  i++;
                }
                entry = (fn_menuentry_t *)iter->data;
                choice = entry->shortcut;
                choice_made = 1;
              }
            }
          }
          break;
        case SDL_VIDEOEXPOSE:
          SDL_UpdateRect(screen, 0, 0, 0, 0);
          break;
        case SDL_USEREVENT:
          /* timer tick */
          animationframe++;
          animationframe %= 4;
          changed = 1;
          break;
        default:
          /* ignore other events */
          break;
      }
    }
  }

  SDL_EnableKeyRepeat(0, 0);
  SDL_RemoveTimer(tick);
  SDL_FreeSurface(target);
  SDL_FreeSurface(box);

  return choice;
}

/* --------------------------------------------------------------- */

void fn_menu_append_entry(
    fn_menu_t * menu,
    char shortcut,
    char * name,
    char value)
{
  fn_menuentry_t * entry = fn_menuentry_create(shortcut, name, value); 

  menu->width = MAXVAL(menu->width, strlen(name));

  menu->entries = fn_list_append(menu->entries, entry);
  menu->num_entries++;
}

/* --------------------------------------------------------------- */

fn_menuentry_t * fn_menu_get_current_entry(
    fn_menu_t * menu)
{
  Uint16 i = 0;
  fn_list_t * iter = fn_list_first(menu->entries);

  assert(menu->currententry < menu->num_entries);

  while (i < menu->currententry) {
    iter = fn_list_next(iter);
    i++;
  }
  fn_menuentry_t * ret = (fn_menuentry_t *)iter->data;
  return ret;
}

/* --------------------------------------------------------------- */
