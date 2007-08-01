/*******************************************************************
 * Project: FreeNukum 2D Jump'n Run
 * File:    Splash a picture to the screen
 *******************************************************************/

#ifndef FN_PICTURE_SPLASH
#define FN_PICTURE_SPLASH

/* --------------------------------------------------------------- */

#include <SDL/SDL.h>

/* --------------------------------------------------------------- */

/**
 * Show a splash picture on the screen.
 * This function waits for input of the Escape or Return key, then
 * it returns.
 * 
 * @param  datapath   The directory where the data files are stored.
 * @param  filename   The filename of the picture to show.
 *                    Usually one of: BADGUY.DN1, CREDITS.DN1, DN.DN1, DUKE.DN1
 * @param  pixelsize  The pixel size.
 * @param  screen     The surface to which the image is finally blitted.
 *
 * @return 1 on success, otherwise 0 (if for example the file could not be
 *         read. In that case, it also calls the fn_error_printf function).
 */
int fn_picture_splash_show(char * datapath,
    char * filename,
    Uint8 pixelsize,
    SDL_Surface * screen);

/* --------------------------------------------------------------- */

#endif /* FN_PICTURE_SPLASH */
