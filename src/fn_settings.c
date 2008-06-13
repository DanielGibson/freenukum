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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* --------------------------------------------------------------- */

#include "fn_settings.h"

/* --------------------------------------------------------------- */

#define MAX(X,Y) ((X)>(Y) ? (X) : (Y))
#define STRLEN_OF_INT(X) strlen(#X)

/* =============================================================== *
 * Local functions
 * =============================================================== */

fn_settings_option_t * _fn_settings_find_option(
    fn_settings_option_t * start,
    char * name)
{
  while (start != NULL) {
    if (strcasecmp(start->name, name) == 0)
      return start;
    start = start->next;
  }
  return NULL;
}

/* --------------------------------------------------------------- */

fn_settings_option_t * _fn_settings_create_option(
    fn_settings_t * s,
    char * name)
{
  fn_settings_option_t * option;

  option = _fn_settings_find_option(s->options, name);
  if (option == NULL) {
    option = malloc(sizeof(fn_settings_option_t));
    option->name = malloc(strlen(name) + 1);
    strcpy(option->name, name);
    option->value = NULL;
    option->next = NULL;
    if (s->options == NULL) {
      s->options = option;
      s->end = option;
    }
    else {
      s->end->next = option;
      s->end = option;
    }
  }

  return option;
}

/* =============================================================== *
 * Exported functions
 * =============================================================== */

fn_settings_t * fn_settings_new()
{
  fn_settings_t * s;

  s = malloc(sizeof(fn_settings_t));

  s->options = NULL;
  s->end = NULL;

  return s;
}

/* --------------------------------------------------------------- */

fn_settings_t * fn_settings_new_from_file(char * path)
{
  fn_settings_t * s;

  FILE * fh;

  char buffer[1024];
  char * start, * end;
  char * name_start, * name_end;
  char * value_start, * value_end;
  char c;

  fh = fopen(path, "r");
  if(fh == NULL) {
    return NULL;
  }

  s = fn_settings_new();

  /* get each line of the file */
  while (fgets(buffer, sizeof(buffer), fh))
  {
    fn_settings_option_t * o;

    /* trim whitespace from left */
    for (start = buffer; *start == ' ' || *start == '\t'; start++);

    /* trim whitespace from right */
    end = start + strlen(start);
    while (end > start
        && ((c = end[-1]) == '\n' || c == '\r' || c == ' ' || c == '\t'))
    {
      end--;
    }
    *end = '\0';

    name_start = start;
    /* find the '=' sign */
    for(name_end = start; name_end != end && *name_end != '='; name_end++);

    /* ignore lines without '=' sign */
    if (name_end == end)
      continue;

    /* get the value (trim whitespace after '=' sign) */
    value_end = end;
    for (value_start = name_end + 1;
        value_start < value_end
        && (*value_start == ' ' || *value_start == '\t');
        value_start++);

    /* get the name (trim whitespace before '=' sign) */
    while (name_end > name_start
        && ((c = name_end[-1]) == ' ' || c == '\t'))
    {
      name_end--;
    }
    *name_end = '\0';

    /* create a new option node */
    o = malloc(sizeof(fn_settings_option_t));

    o->name = malloc(strlen(name_start)+1);
    strcpy(o->name, name_start);

    o->value = malloc(strlen(value_start)+1);
    strcpy(o->value, value_start);

    o->next = NULL;

    /* append the node */
    if (s->end == NULL) {
      /* s still empty */
      s->end = o;
      s->options = o;
    }
    else {
      /* s non-empty */
      s->end->next = o;
      s->end = o;
    }
  }
  fclose(fh);
  return s;
}

/* --------------------------------------------------------------- */

void fn_settings_free(fn_settings_t * s)
{
  fn_settings_option_t * option_to_delete;
  if(s->options != NULL)
  {
    while(s->options->next != NULL) {
      option_to_delete = s->options;
      s->options = s->options->next;
      free(option_to_delete);
    }
    free(s->options);
  }
  free(s);
}

/* --------------------------------------------------------------- */

int fn_settings_store(fn_settings_t * s, char * path)
{
  FILE * fh;
  fn_settings_option_t * option;

  fh = fopen(path, "w");
  if(fh == NULL)
    return 0;

  if (s->options) {
    option = s->options;
    while (option != NULL)
    {
      fprintf(fh, "%s=%s\n", option->name, option->value);
      option = option->next;
    }
  }

  fclose(fh);
  return 1;
}

/* --------------------------------------------------------------- */

int fn_settings_get_bool(fn_settings_t * s,
    char * name,
    int * target)
{
  fn_settings_option_t * option;
  option = _fn_settings_find_option(s->options, name);
  if (option != NULL) {
    if (strcasecmp(option->value, "true") == 0
        || strcasecmp(option->value, "1") == 0)
      *target = 1;
    else
      *target = 0;
    return 1;
  }
  return 0;
}

/* --------------------------------------------------------------- */

void fn_settings_get_bool_with_default(fn_settings_t * s,
    char * name,
    int * target,
    int defval)
{
  if (!fn_settings_get_bool(s, name, target)) {
    fn_settings_set_bool(s, name, defval);
    *target = defval;
  }
}

/* --------------------------------------------------------------- */

int fn_settings_get_longint(fn_settings_t * s,
    char * name,
    long int * target)
{
  fn_settings_option_t * option;
  char * end;

  option = _fn_settings_find_option(s->options, name);
  if (option != NULL) {
    *target = strtol(option->value, &end, 0);
    if (*end == '\0' && *(option->value) != '\0')
      return 1;
    return 0;
  }
  return 0;
}

/* --------------------------------------------------------------- */

void fn_settings_get_longint_with_default(fn_settings_t * s,
    char * name,
    long int * target,
    long int defval)
{
  if (!fn_settings_get_longint(s, name, target)) {
    fn_settings_set_longint(s, name, defval);
    *target = defval;
  }
}

/* --------------------------------------------------------------- */

int fn_settings_get_string(fn_settings_t * s,
    char * name,
    char ** target)
{
  fn_settings_option_t * option;

  option = _fn_settings_find_option(s->options, name);
  if (option != NULL) {
    *target = malloc(strlen(option->value)+1);
    strcpy(*target, option->value);
    return 1;
  }
  return 0;
}

/* --------------------------------------------------------------- */

void fn_settings_get_string_with_default(fn_settings_t * s,
    char * name,
    char ** target,
    char * defval)
{
  if (!fn_settings_get_string(s, name, target)) {
    fn_settings_set_string(s, name, defval);
    *target = malloc(strlen(name)+1);
    strcpy(*target, name);
  }
}

/* --------------------------------------------------------------- */

void fn_settings_set_bool(fn_settings_t * s,
    char * name,
    int source)
{
  fn_settings_option_t * option;

  option = _fn_settings_find_option(s->options, name);
  if (option == NULL) {
    option = _fn_settings_create_option(s, name);
  }
  option->value = realloc(option->value, 6);
  sprintf(option->value, (source ? "true" : "false"));
}

/* --------------------------------------------------------------- */

void fn_settings_set_longint(fn_settings_t * s,
    char * name,
    long int source)
{
  fn_settings_option_t * option;

  option = _fn_settings_find_option(s->options, name);
  if (option == NULL) {
    option = _fn_settings_create_option(s, name);
  }
  option->value = realloc(option->value,
      MAX(STRLEN_OF_INT(LONG_MAX), STRLEN_OF_INT(LONG_MIN)) + 1);
  sprintf(option->value, "%ld", source);
}

/* --------------------------------------------------------------- */

void fn_settings_set_string(fn_settings_t * s,
    char * name,
    char * source)
{
  fn_settings_option_t * option;

  option = _fn_settings_find_option(s->options, name);
  if (option == NULL) {
    option = _fn_settings_create_option(s, name);
  }
  option->value = realloc(option->value, strlen(source) + 1);
  strcpy(option->value, source);
}

/* --------------------------------------------------------------- */

