/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Infobox drawing function test
 *******************************************************************/

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn_tilecache.h"
#include "fn_infobox.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv) {
  SDL_Surface * screen;
  fn_tilecache_t tilecache;
  Uint8 pixelsize = 2;

  char * homedir;
  char tilespath[1024];
  
  int res;

  homedir = getenv("HOME");
  if (homedir == NULL) {
    printf("%s\n", "HOME directory path not set.");
    exit(1);
  }
  snprintf(tilespath, 1024, "%s%s", homedir, "/.freenukum/duke/");

  fn_tilecache_init(&tilecache, pixelsize);

  res = fn_tilecache_loadtiles(&tilecache, tilespath);

  if (res == -1) {
    printf("Could not load tiles.\n");
    printf("Copy the original game files to %s.\n", tilespath);
    exit(1);
  }

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
    return -1;
  }

  screen = SDL_SetVideoMode(
      FN_WINDOW_WIDTH * pixelsize,
      FN_WINDOW_HEIGHT * pixelsize,
      FN_COLOR_DEPTH,
      SDL_SWSURFACE);
  if (screen == NULL) {
    fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
    return -1;
  }

  fn_infobox_show(pixelsize, &tilecache, screen, "This is...");
  fn_infobox_show(pixelsize, &tilecache, screen, "...the great\nInfobox test case.");
  fn_infobox_show(pixelsize, &tilecache, screen, "now\nwith\neven\nmore\nlines.");
  
  return 0;
}
