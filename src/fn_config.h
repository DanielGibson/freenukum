/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Configuration functions
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
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *******************************************************************/

#ifndef FN_CONFIG_H
#define FN_CONFIG_H

/* --------------------------------------------------------------- */

typedef struct {
} fn_config_t;

/* --------------------------------------------------------------- */

fn_config_t * fn_config_new(char * path);

void fn_config_free(fn_config_t * c);

int fn_config_getoption(fn_config_t * c, char * option, void ** result);



/* --------------------------------------------------------------- */

#endif // FN_CONFIG_H
