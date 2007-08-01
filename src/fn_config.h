/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Configuration functions
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
