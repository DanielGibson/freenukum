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

#ifndef FN_INPUTBOX_H
#define FN_INPUTBOX_H

/* --------------------------------------------------------------- */

#include <SDL.h>

/* --------------------------------------------------------------- */

#include "fn_inputbox.h"
#include "fn_tilecache.h"
#include "fn_environment.h"

/* --------------------------------------------------------------- */

typedef enum fn_inputbox_answer_t {
  fn_inputbox_answer_ok,
  fn_inputbox_answer_quit
} fn_inputbox_answer_t;

/* --------------------------------------------------------------- */

/**
 * Display an inputbox and get the result.
 *
 * @param  env         The environment.
 * @param  msg         The message to display.
 * @param  answer      The buffer for the answer.
 *                     This must be already allocated with
 *                     answer_len+1 bytes.
 * @param  answer_len  The maximum length for the answer.
 *
 * @return  fn_inputbox_answer_ok if the user pressed enter,
 *          fn_inputbox_answer_quit if the user pressed escape.
 */
fn_inputbox_answer_t fn_inputbox_show(
    fn_environment_t * env,
    char * msg,
    char * answer,
    Uint8 answer_len);

/* --------------------------------------------------------------- */

#endif /* FN_INPUTBOX_H */
