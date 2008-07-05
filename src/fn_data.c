/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Functions for organizing level and game data.
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

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn_data.h"
#include "fn_error.h"

/* --------------------------------------------------------------- */

int fn_data_try_to_get_file(char * filename)
{
  char tempfilename[1024];
  strncpy(tempfilename, filename, 1024);
  int len = strlen(filename);
  int i = len;
  int fd = 0;

  while (1) {
    i--;
    if (tempfilename[i] >= 'A' && tempfilename[i] <= 'Z') {
      /* make lowercase */
      tempfilename[i] += 'a' - 'A';

      fd = open(tempfilename, O_RDONLY);
      if (fd != -1) {
        /* we found the file, so let's rename it */
        if (rename(tempfilename, filename) == 0) {
          return 0;
        } else {
          fn_error_printf(1024 * 3, "Could not rename file %s"
              " to %s", tempfilename, filename);
          return -1;
        }
      } else {
        close(fd);
      }

    } if (filename[i] == '/') {
      fn_error_printf(1024 * 2, "File %s not found.",
          filename);
      return -1;
    }
  }
}

/* --------------------------------------------------------------- */

int fn_data_check(char * dir, int episodenum)
{
  int fd = 0;
  int res = 0;
  char * files[] = {
    "ANIM0",
    "ANIM1",
    "ANIM2",
    "ANIM3",
    "ANIM4",
    "ANIM5",
    "BACK0",
    "BACK1",
    "BACK2",
    "BACK3",
    "BADGUY",
    "BORDER",
    "CREDITS",
    "DN",
    "DROP0",
    "DUKE",
    "DUKE1-B",
    "DUKE1",
    "END",
    "FONT1",
    "FONT2",
    "MAN0",
    "MAN1",
    "MAN2",
    "MAN3",
    "MAN4",
    "NUMBERS",
    "OBJECT0",
    "OBJECT1",
    "OBJECT2",
    "SOLID0",
    "SOLID1",
    "SOLID2",
    "SOLID3",
    "WORLDAL1",
    "WORLDAL2",
    "WORLDAL3",
    "WORLDAL4",
    "WORLDAL5",
    "WORLDAL6",
    "WORLDAL7",
    "WORLDAL8",
    "WORLDAL9",
    "WORLDALA",
    "WORLDALB",
    "WORLDALC",
    0
  };

  int i = 0;

  /* check if all files exist */
  while (!res) {
    if (files[i] == 0) {
      res = 1;
    } else {
      char filename[1024];
      snprintf(filename, 1024, "%s/%s.DN%d",
          dir, files[i], episodenum);
      fd = open(filename, O_RDONLY);
      if (fd == -1) {
        res = fn_data_try_to_get_file(filename);
      } else {
        close(fd);
      }
    }
    i++;
  }

  return res;
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
