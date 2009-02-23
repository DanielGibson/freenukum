/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Texture Factory
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

#ifndef FNTEXTUREFACTORY_H
#define FNTEXTUREFACTORY_H

/* =============================================================== */

#include <glib-object.h>

/* =============================================================== */

#include "fngraphicoptions.h"
#include "fntexture.h"

/* =============================================================== */

G_BEGIN_DECLS

/* =============================================================== */

typedef struct _FnTextureFactoryPrivate FnTextureFactoryPrivate;

/* =============================================================== */

typedef struct _FnTextureFactory {
  GObject g_object_instance;
  FnTextureFactoryPrivate * priv;
} FnTextureFactory;

/* =============================================================== */

typedef struct _FnTextureFactoryClass {
  GObjectClass g_object_class;
} FnTextureFactoryClass;

/* =============================================================== */

#define FN_TYPE_TEXTURE_FACTORY (fn_texture_factory_get_type())
#define FN_TEXTURE_FACTORY(o) \
  (G_TYPE_CHECK_INSTANCE_CAST((o), \
                              FN_TYPE_TEXTURE_FACTORY, \
                              FnTextureFactory))
#define FN_TEXTURE_FACTORY_CLASS(c) \
  (G_TYPE_CHECK_CLASS_CAST((c), \
                           FN_TYPE_TEXTURE_FACTORY, \
                           FnTextureFactoryClass))
#define FN_IS_TEXTURE_FACTORY(o) \
  (G_TYPE_CHECK_INSTANCE_TYPE((o), FN_TYPE_TEXTURE_FACTORY))
#define FN_IS_TEXTURE_FACTORY_CLASS(c) \
  (G_TYPE_CHECK_CLASS_TYPE((c), FN_TYPE_TEXTURE_FACTORY))
#define FN_TEXTURE_FACTORY_GET_CLASS(o) \
  (G_TYPE_INSTANCE_GET_CLASS( \
                              (o), \
                              FN_TYPE_TEXTURE_FACTORY, \
                              FnTextureFactoryClass))

/* =============================================================== */

GType fn_texture_factory_get_type(void);

/* =============================================================== */

FnTextureFactory * fn_texture_factory_new_with_options(
    FnGraphicOptions * options);

/* =============================================================== */

FnTexture * fn_texture_factory_produce_texture(
    guint pixel_width,
    guint pixel_height
    );

/* =============================================================== */

G_END_DECLS

/* =============================================================== */
#endif /* FNTEXTUREFACTORY_H */
