/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Border drawing functions
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
#include "fn_environment.h"
#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

void fn_borders_blit(
    fn_environment_t * env);

/* --------------------------------------------------------------- */

void fn_borders_blit_life(
    fn_environment_t * env);

/* --------------------------------------------------------------- */

void fn_borders_blit_score(
    fn_environment_t * env);

/* --------------------------------------------------------------- */

void fn_borders_blit_firepower(
    fn_environment_t * env);

/* --------------------------------------------------------------- */

void fn_borders_blit_inventory(
    fn_environment_t * env);

/* --------------------------------------------------------------- */
