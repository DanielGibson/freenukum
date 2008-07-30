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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#ifndef HAVE_AUTOMATIC_DOWNLOAD
#ifdef HAVE_SDL_SDL_TTF_H
#ifdef HAVE_LIBCURL
#define HAVE_AUTOMATIC_DOWNLOAD 1
#endif /* HAVE_LIBCURL */
#endif /* HAVE_SDL_SDL_TTF_H */
#endif /* HAVE_AUTOMATIC_DOWNLOAD */

#ifdef HAVE_SDL_SDL_TTF_H
#include <SDL/SDL_ttf.h>
#endif /* HAVE_SDL_SDL_TTF_H */

/* --------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

#ifdef HAVE_AUTOMATIC_DOWNLOAD
#include <curl/curl.h>
#endif /* HAVE_AUTOMATIC_DOWNLOAD */

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

    }
    if (filename[i] == '/') {
      /* output disabled because it confuses users
      fn_error_printf(1024 * 2, "File %s not found.",
          filename);
          */
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

int fn_data_download_possible(void)
{
#ifndef HAVE_AUTOMATIC_DOWNLOAD
  return 0;
#else /* HAVE_AUTOMATIC_DOWNLOAD */
#ifdef WIN32
  /* we can run dos executables on win32 */
  return 1;
#else /* WIN32 */
  printf(
      "###################################################\n"
      "The following output is not generated by freenukum\n"
      "Freenukum is trying to call dosbox in order to find\n"
      "out if the original shareware episode can be\n"
      "unpacked automatically.\n"
      "---------------------------------------------------\n");
  int no_dosbox = system("dosbox --version");
  printf(
      "###################################################\n");
  if (no_dosbox) {
    printf(
        "No dosbox installation found.\n");
  } else {
    printf(
        "Dosbox is installed. It can be used to automatically\n"
        "unpack the original shareware episode.\n");
  }
  printf(
      "###################################################\n");
  return no_dosbox == 0;
#endif /* WIN32 */
#endif /* HAVE_AUTOMATIC_DOWNLOAD */
}

/* --------------------------------------------------------------- */

#ifdef HAVE_AUTOMATIC_DOWNLOAD

/* --------------------------------------------------------------- */

struct FtpFile {
  const char * filename;
  FILE * stream;
};

/* --------------------------------------------------------------- */

struct ProgressData {
  SDL_Surface * screen;
  TTF_Font * font;
  int x;
  int y;
  int height;
};

/* --------------------------------------------------------------- */

static size_t fn_data_downloaded_write(
    void * buffer, size_t size, size_t nmemb, void * stream)
{
  struct FtpFile * out = (struct FtpFile *) stream;
  if (out && !out->stream) {
    /* open file for writing */
    out->stream = fopen(out->filename, "wb");
    if (!out->stream) {
      return -1; /* failure, can't open file to write */
    }
  }
  return fwrite(buffer, size, nmemb, out->stream);
}

/* --------------------------------------------------------------- */

int fn_data_downloaded_progress(void * cdata,
    double dltotal,
    double dlnow,
    double utotal,
    double unow)
{
  struct ProgressData * data = (struct ProgressData *)cdata;
  if (data->screen != NULL && data->font != NULL) {
    int fullwidth = data->screen->w - data->x * 2;
    SDL_Rect destrect;
    destrect.x = data->x;
    destrect.y = data->y;
    destrect.h = data->height;
    destrect.w = fullwidth * dlnow / dltotal;
    Uint32 blue = SDL_MapRGB(data->screen->format, 0, 0, 255);
    SDL_FillRect(data->screen, &destrect, blue);
    char progress[10] = "";
    snprintf(progress, 10, "%d%%", (int)(100 * dlnow / dltotal));
    destrect.y += data->height;
    Uint32 black = SDL_MapRGB(data->screen->format, 0, 0, 0);
    SDL_FillRect(data->screen, &destrect, black);
    fn_data_display_text(data->screen,
        destrect.x, destrect.y, data->font, progress);
    SDL_UpdateRect(data->screen,
        0, 0, data->screen->w, data->screen->h);
  }
  return 0;
}

/* --------------------------------------------------------------- */

int fn_data_download(
    SDL_Surface * screen,
    TTF_Font * font,
    int fontheight,
    char * datapath)
{
  char temppath[1024] = "";
  char tempfile[1024] = "";
  DIR * tempdir = NULL;
  int res = 0;
  CURL * curl = NULL;
  CURLcode curlres;
  struct FtpFile store = {
    tempfile,
    NULL
  };
  struct ProgressData progress = {
    screen,
    font,
    fontheight * 3,
    fontheight * 4,
    fontheight
  };

  snprintf(temppath, 1024, "%s%s", datapath, "/temp");
  snprintf(tempfile, 1024, "%s%s", temppath, "/1duke.zip");

  /* Check if the temp path exists and create it if it does
   * not exist yet. */
  tempdir = opendir(temppath);
  if (tempdir == NULL) {
    res = mkdir(temppath, S_IRUSR | S_IWUSR | S_IXUSR |
        S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    if (res) {
      fn_error_printf(1024,
          "Could not create the temp directory %s: %s",
          temppath, strerror(errno));
      return 0;
    }
  }

  /* delete the temporary file if it exists from previous runs */
  unlink(tempfile);

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if (!curl) {
    return 0;
  }

  char * url = "ftp://ftp.3drealms.com/share/1duke.zip";

  curl_easy_setopt(curl, CURLOPT_URL,
      url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
      fn_data_downloaded_write);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA,
      &store);
  curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION,
      fn_data_downloaded_progress);
  curl_easy_setopt(curl, CURLOPT_PROGRESSDATA,
      &progress);
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS,
      0);
  curl_easy_setopt(curl, CURLOPT_NOSIGNAL,
      0);
  Uint32 black = SDL_MapRGB(screen->format, 0, 0, 0);
  SDL_FillRect(screen, NULL, black);
  char message[255] = "";
  snprintf(message, 255, "Downloading file from\n"
      "%s\n"
      "This may take some time, please be patient...\n"
      , url);
  fn_data_display_text(screen, 0, 0, font, message);

  SDL_Rect destrect;
  destrect.x = progress.x;
  destrect.y = progress.y;
  destrect.h = progress.height;
  destrect.w = screen->w - progress.x * 2;
  Uint32 grey = SDL_MapRGB(screen->format, 255, 255, 128);
  SDL_FillRect(screen, &destrect, grey);

  SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);

  fn_data_downloaded_progress(&progress,
      100, 0, 100, 0);
  curlres = curl_easy_perform(curl);

  /* always clean up */
  curl_easy_cleanup(curl);

  if (curlres != CURLE_OK) {
    return 0;
  }

  if (0) {
    printf("File successfully downloaded\n");
    return 1;
  }

  return 0;
}

#endif /* HAVE_AUTOMATIC_DOWNLOAD */

/* --------------------------------------------------------------- */

#ifdef HAVE_SDL_SDL_TTF_H
void fn_data_display_text(
    SDL_Surface * screen,
    int x,
    int y,
    TTF_Font * font,
    char * message)
{
  SDL_Rect destrect;
  destrect.x = x;
  destrect.y = y;
  SDL_Color fgcolor = { 255, 255, 255 };
  SDL_Color bgcolor = { 0, 0, 0 };
  SDL_Surface * text = NULL;
  int textheight = 0;

  char * iter = message;
  char * end = message + strlen(message);
  while (iter < end) {
    char * linebreak = strchr(iter, '\n');
    if (linebreak == NULL) {
      /* last line */
      if (strlen(iter) > 0) {
        text = TTF_RenderText_Shaded(font, iter, fgcolor, bgcolor);
        SDL_BlitSurface(text, NULL, screen, &destrect);
        SDL_FreeSurface(text);
      }
      iter = end;
    } else {
      /* line in between */
      *linebreak = 0;
      if (strlen(iter) > 0) {
        text = TTF_RenderText_Shaded(font, iter, fgcolor, bgcolor);
        textheight = text->h;
        SDL_BlitSurface(text, NULL, screen, &destrect);
        SDL_FreeSurface(text);
      }
      destrect.y += textheight;
      *linebreak = '\n';
      iter = linebreak + 1;
    }
  }
}
#endif /* HAVE_SDL_SDL_TTF_H */
