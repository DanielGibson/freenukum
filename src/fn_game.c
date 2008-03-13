/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Gameplay functions
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

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/* --------------------------------------------------------------- */

#include "fn_game.h"
#include "fn_borders.h"
#include "fn_picture_splash.h"
#include "fn_infobox.h"
#include "fn_level.h"

/* --------------------------------------------------------------- */

Uint8  health = FN_NUM_MAXLIFE;
Uint8  firepower = 1;
Uint8  inventory = 0x00;
Uint32 score = 0;

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

    fn_infobox_show(pixelsize,
        tilecache,
        screen,
        "Sorry, gameplay is\n"
        "not implemented yet.\n"
        "You can browse through the level\n"
        "by pressing the cursor keys though.\n");

    fn_game_start_in_level('1',
        pixelsize,
        tilecache,
        screen,
        datapath);
  }

}

void fn_game_start_in_level(
    char levelnumber,
    Uint8 pixelsize,
    fn_tilecache_t * tilecache,
    SDL_Surface * screen,
    char * datapath)
{
  int fd = 0;
  fn_level_t * lv = 0;
  SDL_Rect dstrect;
  SDL_Rect srcrect;
  SDL_Event event;
  int res = 0;
  int doupdate = 1;
  SDL_Surface * level = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            FN_PART_WIDTH * pixelsize * FN_LEVEL_WIDTH,
            FN_PART_HEIGHT * pixelsize * FN_LEVEL_HEIGHT,
            FN_COLOR_DEPTH,
            0,
            0,
            0,
            0);
  char levelfile[1024];
  snprintf(levelfile, 1024, "%s/WORLDAL%c.DN1",
      datapath, levelnumber);
  fd = open(levelfile, O_RDONLY);

  if (fd == -1)
  {
    fprintf(stderr, "Could not open file %s\n", levelfile);
    perror("Can't open file");
    goto cleanup;
  }

  lv = fn_level_load(fd, pixelsize, tilecache);
  if (lv == NULL)
  {
    close(fd);
    fprintf(stderr, "Could not load level from file %s\n", levelfile);
    goto cleanup;
  }
  close(fd);

  dstrect.x = FN_PART_WIDTH * pixelsize;
  dstrect.y = FN_PART_HEIGHT * pixelsize;
  dstrect.w = FN_LEVELWINDOW_WIDTH * pixelsize * FN_PART_WIDTH;
  dstrect.h = FN_LEVELWINDOW_HEIGHT * pixelsize * FN_PART_HEIGHT;
  /* TODO get this dynamically from the hero struct. */
  srcrect.x = 50 * pixelsize * FN_PART_WIDTH;
  /* TODO get this dynamically from the hero struct. */
  srcrect.y = 0 * pixelsize * FN_PART_HEIGHT;
  srcrect.w = FN_LEVELWINDOW_WIDTH * pixelsize * FN_PART_WIDTH;
  srcrect.h = FN_LEVELWINDOW_HEIGHT * pixelsize * FN_PART_HEIGHT;

  /* The mainloop of the level */
  while (fn_level_keep_on_playing(lv))
  {
    if (doupdate) {
      printf("starting blit of level.\n");
      printf("srcrect: x %d, y %d, w %d, h %d\n", srcrect.x, srcrect.y,
          srcrect.w, srcrect.h);
      fn_level_blit_to_surface(lv,
          level,
          &srcrect,
          &srcrect);
      printf("starting blit to screen.\n");
      SDL_BlitSurface(level, &srcrect, screen, &dstrect);
      printf("updating screen.\n");
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      doupdate = 0;
    }

    printf("waiting for event... ");
    res = SDL_WaitEvent(&event);
    printf("event occured.\n");
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
              if (srcrect.y + srcrect.h
                  < FN_LEVEL_HEIGHT * pixelsize * FN_PART_HEIGHT) {
                srcrect.y += pixelsize * FN_PART_HEIGHT;
              }
              printf("downkey pressed - y: %d\n", srcrect.y);
              doupdate = 1;
              break;
            case SDLK_UP:
              if (srcrect.y > 0) {
                srcrect.y -= pixelsize * FN_PART_HEIGHT;
              }
              printf("upkey pressed - y: %d\n", srcrect.y);
              doupdate = 1;
              break;
            case SDLK_LEFT:
              if (srcrect.x > 0) {
                srcrect.x -= pixelsize * FN_PART_WIDTH;
              }
              printf("leftkey pressed - x: %d\n", srcrect.x);
              doupdate = 1;
              break;
            case SDLK_RIGHT:
              if (srcrect.x + srcrect.w
                  < FN_LEVEL_WIDTH * pixelsize * FN_PART_WIDTH) {
                srcrect.x += pixelsize * FN_PART_WIDTH;
              }
              doupdate = 1;
              printf("rightkey pressed - x: %d\n", srcrect.x);
              break;
            default:
              printf("unknown key pressed.\n");
              /* do nothing on other key input (yet) */
              break;
          }
          break;
        case SDL_VIDEOEXPOSE:
          printf("video expose\n");
          SDL_UpdateRect(screen, 0, 0, 0, 0);
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
  fn_level_free(lv);
  SDL_FreeSurface(level);
}

