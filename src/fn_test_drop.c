/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for Drop (Level Background) loader
 * $Id: fn_test_drop.c 14 2006-07-02 11:02:37Z sttereo3 $
 *******************************************************************/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn_drop.h"
#include "fn.h"
#include "fn_tile.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    int fd;
    fn_tileheader_t h;
    Uint8 pixelsize = 3;
    int quit = 0;
    int res;
    SDL_Event event;
    
    if (argc != 2)
    {
        fprintf(stderr, "\nShow an original Duke Nukem backdrop.\n");
        fprintf(stderr, "Usage: %s <FILENAME>\n", argv[0]);
        fprintf(stderr, "FILENAME is usually something like DROP1.DN1\n\n");
        fprintf(stderr, "filename is usually something like DROP1.DN1\n");
        return -1;
    }

    fd = open(argv[1], O_RDONLY);

    SDL_Surface * screen;
    SDL_Surface * drop;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
        return -1;
    }

    screen = SDL_SetVideoMode(
            FN_DROP_WIDTH * FN_PART_WIDTH * pixelsize,
            FN_DROP_HEIGHT * FN_PART_HEIGHT * pixelsize,
            FN_COLOR_DEPTH,
            SDL_SWSURFACE);

    if (screen == NULL)
    {
        fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
        return -1;
    }

    fn_tile_loadheader(fd, &h);

    drop = fn_drop_load(fd, pixelsize);

    SDL_BlitSurface(drop, NULL, screen, NULL);
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    
    SDL_FreeSurface(drop);

    while (quit == 0)
    {
        res = SDL_PollEvent(&event);
        if (res == 1)
        {
            int multiplier = 1;
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.mod & KMOD_CTRL)
                    {
                        multiplier = 160;
                    }
                    else
                    {
                        multiplier = 16;
                    }
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_q:
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;
                        default:
                            /* do nothing, ignoring other keys. */
                            break;
                    }
                case SDL_VIDEOEXPOSE:
                    SDL_UpdateRect(screen, 0, 0, 0, 0);
                    break;
                default:
                    /* do nothing */
                    break;
            }
        }
    }


    return 0;
}

/* --------------------------------------------------------------- */

