/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Picture Drawing functions
 *******************************************************************/

#include <stdlib.h>
#include <unistd.h>

/* --------------------------------------------------------------- */

#include "fn.h"
#include "fn_draw.h"
#include "fn_picture.h"

/* --------------------------------------------------------------- */

SDL_Surface * fn_picture_load(int fd, Uint8 pixelsize)
{
    SDL_Surface * picture;
    SDL_Rect r;
    size_t num_read = 0;

    picture = SDL_CreateRGBSurface(
              SDL_SWSURFACE,     /* flags */
              FN_WINDOW_WIDTH * pixelsize,   /* width */
              FN_WINDOW_HEIGHT * pixelsize,  /* height */
              FN_COLOR_DEPTH,    /* depth */
              0,                 /* Rmask */
              0,                 /* Gmask */
              0,                 /* Bmask */
              0                  /* Amask */
              );

    size_t num_loads = FN_PICTURE_WIDTH * FN_PICTURE_HEIGHT;
    size_t i = 0;

    fn_byterow_t br[num_loads];
    char readbuf[num_loads];

    r.x = 0;
    r.y = 0;
    r.w = 8 * pixelsize;
    r.h = 1 * pixelsize;

    while(i != 5)
    {
        /* only read the first four cycles, we use the
         * fifth one to set transparency to off
         * and to draw the picture
         */
        if (i < 5)
        {
            read(fd, readbuf, num_loads);
        }
        while (num_read != num_loads)
        {
            switch(i)
            {
                case 0:
                    (br+num_read)->blue     = readbuf[num_read];
                    break;
                case 1:
                    (br+num_read)->green    = readbuf[num_read];
                    break;
                case 2:
                    (br+num_read)->red      = readbuf[num_read];
                    break;
                case 3:
                    (br+num_read)->brighten = readbuf[num_read];
                    break;
                case 4:
                    (br+num_read)->trans    = 0xFF;
                    fn_draw_byterow(
                            picture,
                            r,
                            br+num_read,
                            0,
                            pixelsize);
                    r.x += 8 * pixelsize;
                    if (r.x == FN_WINDOW_WIDTH * pixelsize)
                    {
                        r.x = 0;
                        r.y += pixelsize;
                    }
                    break;
                default:
                    /* Do nothing here */
                    break;
            }
            num_read++;
        }
        num_read = 0;
        i++;
    }
    return picture;
}

/* --------------------------------------------------------------- */

