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

#ifndef FN_DATA_H
#define FN_DATA_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <SDL.h>
#ifdef HAVE_SDL_SDL_TTF_H
#include <SDL/SDL_ttf.h>
#endif /* HAVE_SDL_SDL_TTF_H */

/* --------------------------------------------------------------- */

/**
 * Check if data is present for an episode.
 *
 * @param  path        The path of the data.
 * @param  episodenum  The number of the episode.
 */
int fn_data_check(char * path, int episodenum);

/* --------------------------------------------------------------- */

/**
 * Check if automatic download of shareware episode is possible
 *
 * @return  1 if it is possible, otherwise 0.
 */
int fn_data_download_possible(void);

/* --------------------------------------------------------------- */

#ifdef HAVE_AUTOMATIC_DOWNLOAD
/**
 * Automatically download of shareware episode.
 *
 * @param  screen    The screen on which to show the download progress.
 * @param  font      The font which is used for progress display.
 * @param  fontheight  The height of the font.
 * @param  datapath  The path to which the episode should be stored.
 *
 * @return 1 on success, 0 on failure.
 */
int fn_data_download(
    SDL_Surface * screen,
    TTF_Font * font,
    int fontheight,
    char * datapath);
#endif /* HAVE_AUTOMATIC_DOWNLOAD */

/* --------------------------------------------------------------- */

#ifdef HAVE_SDL_SDL_TTF_H
void fn_data_display_text(
    SDL_Surface * screen,
    int x,
    int y,
    TTF_Font * font,
    char * message);
#endif /* HAVE_SDL_SDL_TTF_H */

#endif /* FN_DATA_H */

