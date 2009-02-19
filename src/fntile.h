/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Tile
 *
 * *****************************************************************
 *
 * Copyright 2009 Wolfgang Silbermayr
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

#ifndef FNTILE_H
#define FNTILE_H

/* =============================================================== */

#include <SDL.h>
#include <glib-object.h>

/* =============================================================== */

#include "fn_environment.h"

/* =============================================================== */

G_BEGIN_DECLS

/* =============================================================== */

typedef struct _FnTilePrivate FnTilePrivate;

/* =============================================================== */

typedef struct _FnTile {
  GObject g_object_instance;
  FnTilePrivate * priv;
} FnTile;

/* =============================================================== */

typedef struct _FnTileClass {
  GObjectClass g_object_class;
} FnTileClass;

/* =============================================================== */

#define FN_TYPE_TILE (fn_tile_get_type())
#define FN_TILE(o) \
  (G_TYPE_CHECK_INSTANCE_CAST((o), FN_TYPE_TILE, FnTile))
#define FN_TILE_CLASS(c) \
  (G_TYPE_CHECK_CLASS_CAST((c), FN_TYPE_TILE, FnTileClass))
#define FN_IS_TILE(o) \
  (G_TYPE_CHECK_INSTANCE_TYPE((o), FN_TYPE_TILE))
#define FN_IS_TILE_CLASS(c) \
  (G_TYPE_CHECK_CLASS_TYPE((c), FN_TYPE_TILE))
#define FN_TILE_GET_CLASS(o) \
  (G_TYPE_INSTANCE_GET_CLASS((o), FN_TYPE_TILE, FnTileClass))

/* =============================================================== */

GType fn_tile_get_type(void);

/* =============================================================== */

FnTile * fn_tile_new_with_environment(
    guint width,
    guint height,
    fn_environment_t * env
    );

/* =============================================================== */

void
fn_tile_set_data(
    FnTile * tile,
    guchar * data);

/* =============================================================== */

void
FnTileBlitToSdlSurface(
    FnTile * tile,
    SDL_Rect * srcrect,
    SDL_Surface * destination,
    SDL_Rect * dstrect);

/* =============================================================== */

G_END_DECLS

/* =============================================================== */

#endif /* FNTILE_H */
