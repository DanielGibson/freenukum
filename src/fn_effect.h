/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Blending effect functions
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

#include <SDL.h>

/* --------------------------------------------------------------- */

void fn_effect_blend_step(
    SDL_Surface * s,
    Uint32 blendcolor,
    Uint32 removecolor,
    Uint8 pixelsize);

void fn_effect_blend(
    SDL_Surface * s,
    Uint8 step,
    Uint32 blendcolor,
    Uint8 pixelsize);
