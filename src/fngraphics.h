/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Graphics Subsystem
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

#ifndef FNGRAPHICS_H
#define FNGRAPHICS_H

/* =============================================================== */

#include <glib-object.h>

/* =============================================================== */

#include "fnscreen.h"
#include "fntexturefactory.h"

/* =============================================================== */

G_BEGIN_DECLS

/* =============================================================== */

typedef struct _FnGraphicsPrivate FnGraphicsPrivate;

/* =============================================================== */

typedef struct _FnGraphics {
  GObject g_object_instance;
  FnGraphicsPrivate * priv;
} FnGraphics;

/* =============================================================== */

typedef struct _FnGraphicsClass {
  GObjectClass g_object_class;
} FnGraphicsClass;

/* =============================================================== */

#define FN_TYPE_GRAPHICS (fn_graphics_get_type())
#define FN_GRAPHICS(o) \
  (G_TYPE_CHECK_INSTANCE_CAST((o), FN_TYPE_GRAPHICS, FnGraphics))
#define FN_GRAPHICS_CLASS(c) \
  (G_TYPE_CHECK_CLASS_CAST((c), FN_TYPE_GRAPHICS, FnGraphicsClass))
#define FN_IS_GRAPHICS(o) \
  (G_TYPE_CHECK_INSTANCE_TYPE((o), FN_TYPE_GRAPHICS))
#define FN_IS_GRAPHICS_CLASS(c) \
  (G_TYPE_CHECK_CLASS_TYPE((c), FN_TYPE_GRAPHICS))
#define FN_GRAPHICS_GET_CLASS(o) \
  (G_TYPE_INSTANCE_GET_CLASS( \
                              (o), \
                              FN_TYPE_GRAPHICS, \
                              FnGraphicsClass))

/* =============================================================== */

GType fn_graphics_get_type(void);

/* =============================================================== */

FnGraphics *
fn_graphics_new();

/* =============================================================== */

FnScreen *
fn_graphics_get_screen(FnGraphics * graphics);

/* =============================================================== */

gboolean
fn_graphics_is_initialized(FnGraphics * graphics);

/* =============================================================== */

FnTextureFactory *
fn_graphics_get_texture_factory(FnGraphics * graphics);

/* =============================================================== */

G_END_DECLS

/* =============================================================== */

#endif /* FNGRAPHICS_H */
