/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Infobox drawing function
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

#include "fn_inputbox.h"
#include "fn_msgbox.h"
#include "fn_inputfield.h"

/* --------------------------------------------------------------- */

fn_inputbox_answer_t fn_inputbox_show(
    fn_environment_t * env,
    char * msg,
    char * answer,
    Uint8 answer_len)
{
  SDL_Surface * msgbox = NULL;
  SDL_Surface * temp = NULL;
  SDL_Surface * inputfield_surface = NULL;

  SDL_Rect dstrect;
  SDL_Rect inputfield_rect;

  int i = 0;
  int res = 0;

  SDL_Event event;

  char * buffer = malloc(strlen(msg) + answer_len + 30);
  strcpy(buffer, msg);
  char * walker = buffer + strlen(buffer);
  *walker = '\n';
  walker++;

  for (i = 0; i < answer_len; i++) {
    *walker = ' ';
    walker++;
  }
  sprintf(walker, "\n\n\nOK (Enter)   Abort (Esc)\n");

  Uint8 pixelsize = fn_environment_get_pixelsize(env);
  inputfield_surface = fn_environment_create_surface(env,
      FN_FONT_WIDTH * answer_len,
      FN_FONT_HEIGHT);

  msgbox = fn_msgbox(env, buffer);

  SDL_Surface * screen = fn_environment_get_screen(env);

  dstrect.x = ((screen->w) - (msgbox->w))/2;
  dstrect.y = ((screen->h) - (msgbox->h))/2;
  dstrect.w = msgbox->w;
  dstrect.h = msgbox->h;

  inputfield_rect.w = inputfield_surface->w;
  inputfield_rect.h = inputfield_surface->h;
  inputfield_rect.x = FN_FONT_WIDTH * pixelsize;
  inputfield_rect.y = msgbox->h - FN_FONT_HEIGHT * 4 * pixelsize;

  /* backup the background */
  temp = SDL_CreateRGBSurface(screen->flags,
      dstrect.w, dstrect.h,
      screen->format->BitsPerPixel,
      0, 0, 0, 0);
  SDL_BlitSurface(screen, &dstrect, temp, NULL);

  fn_inputfield_t * inputfield = fn_inputfield_new(
      answer,
      answer_len);

  fn_inputfield_blit(inputfield, inputfield_surface,
      env);
  SDL_BlitSurface(inputfield_surface, NULL, msgbox,
      &inputfield_rect);
  SDL_BlitSurface(msgbox, NULL, screen, &dstrect);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  while (1) {
    res = SDL_WaitEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_BACKSPACE:
              fn_inputfield_pressed_backspace(inputfield);
              break;
            case SDLK_DELETE:
              fn_inputfield_pressed_delete(inputfield);
              break;
            case SDLK_LEFT:
              fn_inputfield_pressed_left(inputfield);
              break;
            case SDLK_RIGHT:
              fn_inputfield_pressed_right(inputfield);
              break;
            case SDLK_SPACE:
            case SDLK_EXCLAIM:
            case SDLK_QUOTEDBL:
            case SDLK_HASH:
            case SDLK_DOLLAR:
            case SDLK_AMPERSAND:
            case SDLK_QUOTE:
            case SDLK_LEFTPAREN:
            case SDLK_RIGHTPAREN:
            case SDLK_ASTERISK:
            case SDLK_PLUS:
            case SDLK_COMMA:
            case SDLK_MINUS:
            case SDLK_PERIOD:
            case SDLK_SLASH:
            case SDLK_0:
            case SDLK_1:
            case SDLK_2:
            case SDLK_3:
            case SDLK_4:
            case SDLK_5:
            case SDLK_6:
            case SDLK_7:
            case SDLK_8:
            case SDLK_9:
            case SDLK_COLON:
            case SDLK_SEMICOLON:
            case SDLK_LESS:
            case SDLK_EQUALS:
            case SDLK_GREATER:
            case SDLK_QUESTION:
            case SDLK_AT:
            case SDLK_a:
            case SDLK_b:
            case SDLK_c:
            case SDLK_d:
            case SDLK_e:
            case SDLK_f:
            case SDLK_g:
            case SDLK_h:
            case SDLK_i:
            case SDLK_j:
            case SDLK_k:
            case SDLK_l:
            case SDLK_m:
            case SDLK_n:
            case SDLK_o:
            case SDLK_p:
            case SDLK_q:
            case SDLK_r:
            case SDLK_s:
            case SDLK_t:
            case SDLK_u:
            case SDLK_v:
            case SDLK_w:
            case SDLK_x:
            case SDLK_y:
            case SDLK_z:
              fn_inputfield_pressed_symbol(inputfield,
                  event.key.keysym.sym);
              break;
            case SDLK_RETURN:
              SDL_BlitSurface(temp, NULL, screen, &dstrect);
              SDL_FreeSurface(temp);
              SDL_FreeSurface(msgbox);
              fn_inputfield_free(inputfield);
              SDL_FreeSurface(inputfield_surface);
              return fn_inputbox_answer_ok;
              break;
            case SDLK_ESCAPE:
              SDL_BlitSurface(temp, NULL, screen, &dstrect);
              SDL_FreeSurface(temp);
              SDL_FreeSurface(msgbox);
              SDL_FreeSurface(inputfield_surface);
              fn_inputfield_free(inputfield);
              return fn_inputbox_answer_quit;
              break;
            default:
              /* ignore other keys */
              break;
          }
          fn_inputfield_blit(inputfield, inputfield_surface,
              env);
          SDL_BlitSurface(inputfield_surface, NULL, msgbox,
              &inputfield_rect);
          SDL_BlitSurface(msgbox, NULL, screen, &dstrect);
          SDL_UpdateRect(screen, 0, 0, 0, 0);
          break;
        case SDL_VIDEOEXPOSE:
          SDL_UpdateRect(screen, 0, 0, 0, 0);
          break;
        default:
          /* ignore other events */
          break;
      }
    }
  }

  free(buffer);
}

/* --------------------------------------------------------------- */
