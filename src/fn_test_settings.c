/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tests for Settings functions
 * $Id: fn_test_settings.c 14 2006-07-02 11:02:37Z sttereo3 $
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
