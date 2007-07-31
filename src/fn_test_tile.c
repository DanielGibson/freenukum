/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tile loader tester
 * $Id: fn_test_tile.c 13 2006-06-10 16:01:24Z sttereo3 $
 *******************************************************************/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn_tile.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    int fd;
    Uint8 pixelsize = 2;
    SDL_Event event;
    int res = 0;
    int quit = 0;
    
    if (argc != 2)
    {
        fprintf(stderr, "\nShows the tiles that can be found inside "
                "an original Duke Nukem file.\n");
        fprintf(stderr, "Usage: %s <FILENAME>\n", argv[0]);
        fprintf(stderr, "FILENAME is usually one of the following:\n"
                "ANIM0.DN1 to ANIM5.DN1, BORDER.DN1, FONT1.DN1, FONT2.DN1,\n"
                "NUMBERS.DN1, OBJECT0.DN1 to OBJECT2.DN1, SOLID0.DN1"
                " to SOLID3.DN1\n\n");
        return -1;
    }

    fd = open(argv[1], O_RDONLY);

    SDL_Surface * screen;
    SDL_Surface * tile;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
        return -1;
    }

    fn_tileheader_t h;
    fn_tile_loadheader(fd, &h);
 
    screen = SDL_SetVideoMode(
            h.width * 8 * h.tiles * pixelsize,
            h.height * pixelsize,
            FN_COLOR_DEPTH,
            SDL_SWSURFACE);

    if (screen == NULL)
    {
        fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = h.width * 8 * pixelsize;
    r.h = h.height * pixelsize;
    size_t i = 0;
    while (i != h.tiles)
    {
        tile = fn_tile_load(fd, pixelsize, &h);
        SDL_BlitSurface(tile, NULL, screen, &r);
        SDL_FreeSurface(tile);
        i++;
        r.x += 8 * h.width * pixelsize;
        r.y = 0;
    }
    SDL_UpdateRect(screen, 0, 0, 0, 0);

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

