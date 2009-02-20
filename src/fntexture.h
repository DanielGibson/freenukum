/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Texture
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

#ifndef FNTEXTURE_H
#define FNTEXTURE_H

/* =============================================================== */

#include <SDL.h>
#include <glib-object.h>

/* =============================================================== */

#include "fngeometry.h"
#include "fn_environment.h"

/* =============================================================== */

G_BEGIN_DECLS

/* =============================================================== */

#define FN_TEXTURE_DEFAULT_WIDTH 32
#define FN_TEXTURE_DEFAULT_HEIGHT 32

/* =============================================================== */

typedef struct _FnTexturePrivate FnTexturePrivate;

/* =============================================================== */

typedef struct _FnTexture {
  GObject g_object_instance;
  FnTexturePrivate * priv;
} FnTexture;

/* =============================================================== */

typedef struct _FnTextureClass {
  GObjectClass g_object_class;
} FnTextureClass;

/* =============================================================== */

#define FN_TYPE_TEXTURE (fn_texture_get_type())
#define FN_TEXTURE(o) \
  (G_TYPE_CHECK_INSTANCE_CAST((o), FN_TYPE_TEXTURE, FnTexture))
#define FN_TEXTURE_CLASS(c) \
  (G_TYPE_CHECK_CLASS_CAST((c), FN_TYPE_TEXTURE, FnTextureClass))
#define FN_IS_TEXTURE(o) \
  (G_TYPE_CHECK_INSTANCE_TYPE((o), FN_TYPE_TEXTURE))
#define FN_IS_TEXTURE_CLASS(c) \
  (G_TYPE_CHECK_CLASS_TYPE((c), FN_TYPE_TEXTURE))
#define FN_TEXTURE_GET_CLASS(o) \
  (G_TYPE_INSTANCE_GET_CLASS((o), FN_TYPE_TEXTURE, FnTextureClass))

/* =============================================================== */

GType fn_texture_get_type(void);

/* =============================================================== */

FnTexture * fn_texture_new_with_environment(
    guint width,
    guint height,
    fn_environment_t * env
    );

/* =============================================================== */

void
fn_texture_set_data_zero(
    FnTexture * texture);

/* =============================================================== */

void
fn_texture_set_data(
    FnTexture * texture,
    guchar * data);

/* =============================================================== */

void
fn_texture_blit_to_sdl_surface(
    FnTexture * texture,
    SDL_Rect * srcrect,
    SDL_Surface * destination,
    SDL_Rect * dstrect);

/* =============================================================== */

/* TODO write documentation that sourcegeometry as well
   as targetgeometry can be NULL.
   */
void
fn_texture_clone_to_texture(
    FnTexture * source,
    FnGeometry * sourcegeometry,
    FnTexture * target,
    FnGeometry * targetgeometry);

/* =============================================================== */

G_END_DECLS

/* =============================================================== */

#endif /* FNTEXTURE_H */
