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

#include <SDL.h>

/* =============================================================== */

#include "fngraphicoptions.h"

/* =============================================================== */

struct _FnGraphicOptionsPrivate
{
  guint bpp;
  guint scale;
  guint sdl_flags;
  guint transparent;
};

/* =============================================================== */

enum {
  PROP_BPP = 1,
  PROP_SCALE,
  PROP_SDL_FLAGS,
  PROP_TRANSPARENT
};

/* =============================================================== */

#define FN_GRAPHIC_OPTIONS_DEFAULT_BPP   0
#define FN_GRAPHIC_OPTIONS_DEFAULT_SCALE 1
#define FN_GRAPHIC_OPTIONS_DEFAULT_SDL_FLAGS \
  (SDL_HWSURFACE | SDL_HWACCEL | SDL_ANYFORMAT)
#define FN_GRAPHIC_OPTIONS_DEFAULT_TRANSPARENT 0

/* =============================================================== */

#define FN_GRAPHIC_OPTIONS_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE(\
                               (o), \
                               FN_TYPE_GRAPHIC_OPTIONS, \
                               FnGraphicOptionsPrivate))

/* =============================================================== */

static void
fn_graphic_options_init(FnGraphicOptions * options);

/* --------------------------------------------------------------- */

static void
fn_graphic_options_class_init(FnGraphicOptionsClass * c);

/* --------------------------------------------------------------- */

static GObject *
fn_graphic_options_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties);

/* --------------------------------------------------------------- */

static void
fn_graphic_options_dispose(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_graphic_options_finalize(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_graphic_options_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec);

/* --------------------------------------------------------------- */

static void
fn_graphic_options_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec);

/* =============================================================== */

static void
fn_graphic_options_class_init(FnGraphicOptionsClass * c)
{
  GObjectClass * g_object_class;

  GParamSpec * bpp_param;
  GParamSpec * scale_param;
  GParamSpec * sdl_flags_param;
  GParamSpec * transparent_param;
  
  g_object_class = G_OBJECT_CLASS(c);

  g_type_class_add_private(c, sizeof(FnGraphicOptionsPrivate));

  g_object_class->set_property = fn_graphic_options_set_property;
  g_object_class->get_property = fn_graphic_options_get_property;
  g_object_class->constructor  = fn_graphic_options_constructor;
  g_object_class->dispose      = fn_graphic_options_dispose;
  g_object_class->finalize     = fn_graphic_options_finalize;

  bpp_param = g_param_spec_uint(
      "bpp",
      "BPP",
      "Bits per pixel",
      0,
      G_MAXUINT,
      FN_GRAPHIC_OPTIONS_DEFAULT_BPP,
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );
  g_object_class_install_property(
      g_object_class,
      PROP_BPP,
      bpp_param);

  scale_param = g_param_spec_uint(
      "scale",
      "Scale",
      "The scale of one pixel",
      1,
      G_MAXUINT,
      FN_GRAPHIC_OPTIONS_DEFAULT_SCALE,
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );
  g_object_class_install_property(
      g_object_class,
      PROP_SCALE,
      scale_param);

  sdl_flags_param = g_param_spec_uint(
      "sdl_flags",
      "SdlFlags",
      "The SDL flags",
      0,
      G_MAXUINT,
      FN_GRAPHIC_OPTIONS_DEFAULT_SDL_FLAGS,
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );
  g_object_class_install_property(
      g_object_class,
      PROP_SDL_FLAGS,
      sdl_flags_param);

  transparent_param = g_param_spec_uint(
      "transparent",
      "Transparent",
      "The transparent color",
      0,
      G_MAXUINT,
      FN_GRAPHIC_OPTIONS_DEFAULT_TRANSPARENT,
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );
  g_object_class_install_property(
      g_object_class,
      PROP_TRANSPARENT,
      transparent_param);
}

/* =============================================================== */

G_DEFINE_TYPE(
    FnGraphicOptions,
    fn_graphic_options,
    FN_TYPE_GRAPHIC_OPTIONS);

/* =============================================================== */

static void
fn_graphic_options_init(FnGraphicOptions * options)
{
  options->priv = FN_GRAPHIC_OPTIONS_GET_PRIVATE(options);
}

/* --------------------------------------------------------------- */

static void
fn_graphic_options_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec)
{
  FnGraphicOptions * options;
  options = FN_GRAPHIC_OPTIONS(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static void
fn_graphic_options_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec)
{
  FnGraphicOptions * options;
  options = FN_GRAPHIC_OPTIONS(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static GObject *
fn_graphic_options_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties)
{
  GObject * obj;
  GObjectClass * parent_class =
    G_OBJECT_CLASS(fn_graphic_options_parent_class);

  obj = parent_class->constructor(gtype, n_properties, properties);

  FnGraphicOptions * options;
  options = FN_GRAPHIC_OPTIONS(obj);
  FnGraphicOptionsPrivate * priv;
  priv = options->priv;

  return obj;
}

/* --------------------------------------------------------------- */

static void
fn_graphic_options_dispose(GObject * gobject)
{
}

/* --------------------------------------------------------------- */

static void
fn_graphic_options_finalize(GObject * gobject)
{
}

/* =============================================================== */

