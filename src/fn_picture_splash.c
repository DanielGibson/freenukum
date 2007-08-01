/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Splash a picture to the screen
 *******************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

#include "fn_draw.h"
#include "fn_picture.h"
#include "fn_error.h"
#include "fn_error_cmdline.h"
#include "fn.h"

/* --------------------------------------------------------------- */

int fn_picture_splash_show(char * datapath,
    char * filename,
    Uint8 pixelsize,
    SDL_Surface * screen)
{
  char * path;
  int fd;
  int res;
  SDL_Event event;
  SDL_Surface * picture;

  path = malloc(strlen(datapath) + strlen(filename) + 1);
  sprintf(path, "%s%s", datapath, filename);
  fd = open(path, O_RDONLY);

  if (fd == -1) {
    fn_error_printf(1024, "Could not open file %s for reading: %s",
        path,strerror(errno));
    free(path);
    return 0;
  }
  free(path);

  picture = fn_picture_load(fd, pixelsize);

  SDL_BlitSurface(picture, NULL, screen, NULL);
  SDL_UpdateRect(screen, 0, 0, 0, 0);
  SDL_FreeSurface(picture);

  while (1) {
    res = SDL_PollEvent(&event);
    if (res == 1) {
      switch(event.type) {
        case SDL_QUIT:
          return 1;
          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
            case SDLK_RETURN:
              return 1;
            default:
              /* ignore other keys */
              break;
          }
        case SDL_VIDEOEXPOSE:
          SDL_UpdateRect(screen, 0, 0, 0, 0);
          break;
        default:
          /* ignore unknown events */
          break;
      }
    }
  }
  return 0;
}
