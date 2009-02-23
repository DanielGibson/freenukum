/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Graphic Options
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

#ifndef FNGRAPHICOPTIONS_H
#define FNGRAPHICOPTIONS_H

/* =============================================================== */

#include <glib-object.h>

/* =============================================================== */

G_BEGIN_DECLS

/* =============================================================== */

typedef struct _FnGraphicOptionsPrivate FnGraphicOptionsPrivate;

/* =============================================================== */

typedef struct _FnGraphicOptions {
  GObject g_object_instance;
  FnGraphicOptionsPrivate * priv;
} FnGraphicOptions;

/* =============================================================== */

typedef struct _FnGraphicOptionsClass {
  GObjectClass g_object_class;
} FnGraphicOptionsClass;

/* =============================================================== */

#define FN_TYPE_GRAPHIC_OPTIONS (fn_graphic_options_get_type())
#define FN_GRAPHIC_OPTIONS(o) \
  (G_TYPE_CHECK_INSTANCE_CAST((o), \
                              FN_TYPE_GRAPHIC_OPTIONS, \
                              FnGraphicOptions))
#define FN_GRAPHIC_OPTIONS_CLASS(c) \
  (G_TYPE_CHECK_CLASS_CAST((c), \
                           FN_TYPE_GRAPHIC_OPTIONS, \
                           FnGraphicOptionsClass))
#define FN_IS_GRAPHIC_OPTIONS(o) \
  (G_TYPE_CHECK_INSTANCE_TYPE((o), FN_TYPE_GRAPHIC_OPTIONS))
#define FN_IS_GRAPHIC_OPTIONS_CLASS(c) \
  (G_TYPE_CHECK_CLASS_TYPE((c), FN_TYPE_GRAPHIC_OPTIONS))
#define FN_GRAPHIC_OPTIONS_GET_CLASS(o) \
  (G_TYPE_INSTANCE_GET_CLASS( \
                              (o), \
                              FN_TYPE_GRAPHIC_OPTIONS, \
                              FnGraphicOptionsClass))

/* =============================================================== */

GType fn_graphic_options_get_type(void);

/* =============================================================== */

FnGraphicOptions * fn_graphic_options_new_with_defaults();

/* =============================================================== */

guint
fn_graphic_options_get_scale(FnGraphicOptions * options);

/* =============================================================== */

guint
fn_graphic_options_get_sdl_flags(FnGraphicOptions * options);

/* =============================================================== */

guint
fn_graphic_options_get_bpp(FnGraphicOptions * options);

/* =============================================================== */

guint
fn_graphic_options_get_transparent(FnGraphicOptions * options);

/* =============================================================== */

G_END_DECLS

/* =============================================================== */

#endif /* FNGRAPHICOPTIONS_H */
