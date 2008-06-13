/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Settings functions
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

#ifndef FN_SETTINGS_H
#define FN_SETTINGS_H

/* --------------------------------------------------------------- */

#include <stdio.h>

/* --------------------------------------------------------------- */

#define FN_EXPAND_SETTINGS   100

/* --------------------------------------------------------------- */

/**
 * A structure containing an option.
 */
typedef struct fn_settings_option_t {

    /**
     * The name of the option.
     */
    char * name;

    /**
     * The value of the option.
     */
    char * value;

    /**
     * The next option
     */
    struct fn_settings_option_t * next;

} fn_settings_option_t;

/* --------------------------------------------------------------- */

/**
 * A structure containing a set of options.
 */
typedef struct fn_settings_t {

    /**
     * An array of pointers to options.
     */
    fn_settings_option_t * options;

    /**
     * A pointer to the last option.
     */
    fn_settings_option_t * end;

} fn_settings_t;

/* --------------------------------------------------------------- */

/**
 * Default initialization function for fn_settings_t.
 *
 * @return A newly created fn_settings_t struct.
 *
 * @see    fn_settings_free fn_settings_store fn_settings_new_from_file
 */
fn_settings_t * fn_settings_new(void);

/* --------------------------------------------------------------- */

/**
 * Initialization function for fn_settings_t loading from file.
 *
 * @param  path  The path from which the settings are loaded.
 *
 * @return A newly created fn_settings_t struct. If the file could
 *         not be read NULL is returned.
 *
 * @see    fn_settings_free fn_settings_store fn_settings_new
 */
fn_settings_t * fn_settings_new_from_file(char * path);

/* --------------------------------------------------------------- */

/**
 * Clean up a fn_settings_t struct.
 *
 * @param  s      The fn_settings_t struct to clean up.
 */
void fn_settings_free(fn_settings_t * s);

/* --------------------------------------------------------------- */

/**
 * Store the settings to a file.
 *
 * @param  s      The fn_settings_t struct to store.
 * @param  path   The path of the file.
 *
 * @return 1 on success, otherwise 0.
 */
int fn_settings_store(fn_settings_t * s, char * path);

/* --------------------------------------------------------------- */

/**
 * Get a bool value from the settings.
 *
 * @param  s       The fn_settings_t struct.
 * @param  name    The name of the option.
 * @param  target  The memory where the value is copied to.
 *
 * @return 1 if the value could be found, otherwise 0.
 */
int fn_settings_get_bool(fn_settings_t * s,
    char * name,
    int * target);

/* --------------------------------------------------------------- */

/**
 * Get a bool value from the settings and set it to a default value
 * if it is not yet stored.
 *
 * @param  s        The fn_settings_t struct.
 * @param  name     The name of the option.
 * @param  target   The memory where the value is copied to.
 * @param  defval   The default value.
 */
void fn_settings_get_bool_with_default(fn_settings_t * s,
    char * name,
    int * target,
    int defval);

/* --------------------------------------------------------------- */

/**
 * Get a long integer value from the settings.
 *
 * @param  s       The fn_settings_t struct.
 * @param  name    The name of the option.
 * @param  target  The memory where the value is copied to.
 *
 * @return 1 if the value could be found, otherwise 0.
 */
int fn_settings_get_longint(fn_settings_t * s,
    char * name,
    long int * target);

/* --------------------------------------------------------------- */

/**
 * Get a long integer value from the settings and set it to a default
 * value if it is not yet stored.
 *
 * @param  s       The fn_settings_t struct.
 * @param  name    The name of the option.
 * @param  target  The memory where the value is copied to.
 * @param  defval  The default value.
 */
void fn_settings_get_longint_with_default(fn_settings_t * s,
    char * name,
    long int * target,
    long int defval);

/* --------------------------------------------------------------- */

/**
 * Get a string value from the settings.
 *
 * @param  s       The fn_settings_t struct.
 * @param  name    The name of the option.
 * @param  target  A pointer to the char array. This is allocated
 *                 inside this function and has to be freed by the
 *                 caller afterwards.
 *
 * @return 1 if the value could be found, otherwise 0.
 */
int fn_settings_get_string(fn_settings_t * s,
    char * name,
    char ** target);

/* --------------------------------------------------------------- */

/**
 * Get a string value from the settings and set it to a default value
 * if it is not yet stored.
 *
 * @param  s       The fn_settings_t struct.
 * @param  name    The name of the option.
 * @param  target  A pointer to the char array. This is allocated
 *                 inside this function and has to be freed by the
 *                 caller afterwards.
 * @param  defval  The default value.
 */
void fn_settings_get_string_with_default(fn_settings_t * s,
    char * name,
    char ** target,
    char * defval);

/* --------------------------------------------------------------- */

/**
 * Set a bool value in the settings.
 *
 * @param  s        The fn_settings_t struct.
 * @param  name     The name of the option.
 * @param  source   The new value of the option.
 */
void fn_settings_set_bool(fn_settings_t * s,
    char * name,
    int source);

/* --------------------------------------------------------------- */

/**
 * Set a integer value in the settings.
 *
 * @param  s       The fn_settings_t struct.
 * @param  name    The name of the option.
 * @param  source  The new value of the option.
 */
void fn_settings_set_longint(fn_settings_t * s,
    char * name,
    long int source);

/* --------------------------------------------------------------- */

/**
 * Set a string value in the settings.
 *
 * @param  s       The fn_settings_t struct.
 * @param  name    The name of the option.
 * @param  source  The new value of the option.
 */
void fn_settings_set_string(fn_settings_t * s,
    char * name,
    char * source);

/* --------------------------------------------------------------- */

#endif /* FN_SETTINGS_H */
