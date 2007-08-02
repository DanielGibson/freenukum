/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tests for Settings functions
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

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "fn_settings.h"
#include "fn_error.h"

/* --------------------------------------------------------------- */

int main()
{
  fn_settings_t * s;
  int res;

  char settingspath[1024];
  char * homedir;

  /*
  s = fn_settings_new();

  fn_settings_set_longint(s, "testsetting_num", 132);
  fn_settings_set_bool(s, "testsetting_bool1", 1);
  fn_settings_set_string(s, "testsetting_string1", "uiae");
  fn_settings_set_bool(s, "testsetting_bool2", 0);
  fn_settings_set_string(s, "testsetting_string1", "drtn");
  fn_settings_set_string(s, "testsetting_string2", "hello");
  */
  
  homedir = getenv("HOME");

  if (homedir == NULL) {
    printf("%s\n", "HOME directory path not set.");
    exit(1);
  }
  snprintf(settingspath, 1024, "%s%s", homedir, "/.freenukum/config");

  s = fn_settings_new_from_file(settingspath);
  res = fn_settings_store(s, settingspath);

  printf("result: %d\n", res);
  printf("error: %s\n", strerror(errno));

  fn_settings_free(s);

  return 0;
}
