/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Test for Messagebox Drawing functions
 *******************************************************************/

#include <SDL/SDL.h>
#include <stdlib.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_msgbox.h"
#include "fn_tilecache.h"

/* --------------------------------------------------------------- */

int main(int argc, char ** argv)
{
    SDL_Surface * screen;
    SDL_Surface * msgbox;
    fn_msgbox_t mb;
    Uint8 width = 13;
    Uint8 height = 9;
    Uint8 pixelsize = 2;
    fn_tilecache_t tc;
    int res;
    int quit = 0;
    SDL_Event event;
    char * homedir;
    char tilespath[1024];

    char * msg[] = {
        " FREENUKUM MAIN MENU",
        " ------------------- ",
        "",
        "S)tart a new game",
        "R)estore an old game",
        "I)nstructions",
        "O)rdering information",
        "G)ame setup",
        "H)igh scores",
        "P)reviews/Main Demo!",
        "V)iew user demo",
        "T)itle screen",
        "C)redits",
        "Q)it to DOS",
        0
    };

    homedir = getenv("HOME");

    if (homedir == NULL) {
      printf("%s\n", "HOME directory path not set.");
      exit(1);
    }

    snprintf(tilespath, 1024, "%s%s", homedir, "/.freenukum/duke/");

    fn_tilecache_init(&tc, pixelsize);

    res = fn_tilecache_loadtiles(&tc, tilespath);
    if (res == -1)
    {
        printf("Could not load tiles.\n");
        printf("Copy the original game files to %s.\n", tilespath);
        exit(1);
    }

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Can't init SDL: %s\n", SDL_GetError());
        return -1;
    }

    screen = SDL_SetVideoMode(
            FN_PART_WIDTH * pixelsize * width,
            FN_PART_HEIGHT * pixelsize * height,
            FN_COLOR_DEPTH,
            SDL_SWSURFACE);

    if (screen == NULL)
    {
        fprintf(stderr, "Can't set video mode: %s\n", SDL_GetError());
        return -1;
    }

    fn_msgbox_init(&mb, pixelsize, width, height);
    fn_msgbox_settext(&mb, msg);

    msgbox = fn_msgbox_getsurface(&mb, &tc);

    SDL_BlitSurface(msgbox, NULL, screen, NULL);
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

