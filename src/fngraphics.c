/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Graphics subsystem
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

#include "fngraphics.h"

/* =============================================================== */

struct _FnGraphicsPrivate
{
  FnScreen * screen;
  gboolean fullscreen;
  gboolean initialized;
};

/* =============================================================== */

#define FN_GRAPHICS_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE(\
                               (o), \
                               FN_TYPE_GRAPHICS, \
                               FnGraphicsPrivate))

/* =============================================================== */

static void
fn_graphics_init(FnGraphics * graphics);

/* --------------------------------------------------------------- */

static void
fn_graphics_class_init(FnGraphicsClass * c);

/* --------------------------------------------------------------- */

static GObject *
fn_graphics_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties);

/* --------------------------------------------------------------- */

static void
fn_graphics_dispose(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_graphics_finalize(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_graphics_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec);
/* --------------------------------------------------------------- */

static void
fn_graphics_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec);

/* =============================================================== */

static void
fn_graphics_class_init(FnGraphicsClass * c)
{
  GObjectClass * g_object_class;

  g_object_class = G_OBJECT_CLASS(c);

  g_type_class_add_private(c, sizeof(FnGraphicsPrivate));

  g_object_class->set_property = fn_graphics_set_property;
  g_object_class->get_property = fn_graphics_get_property;
  g_object_class->constructor  = fn_graphics_constructor;
  g_object_class->dispose      = fn_graphics_dispose;
  g_object_class->finalize     = fn_graphics_finalize;
}

/* =============================================================== */

G_DEFINE_TYPE(FnGraphics, fn_graphics, G_TYPE_OBJECT);

/* =============================================================== */

FnGraphics *
fn_graphics_new()
{
  FnGraphics * graphics = g_object_new(
      FN_TYPE_GRAPHICS,
      NULL);
  return graphics;
}

/* =============================================================== */

static void
fn_graphics_init(FnGraphics * graphics)
{
  graphics->priv = FN_GRAPHICS_GET_PRIVATE(graphics);
}

/* --------------------------------------------------------------- */

static void
fn_graphics_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec)
{
  FnGraphics * graphics;
  graphics = FN_GRAPHICS(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static void
fn_graphics_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec)
{
  FnGraphics * graphics;
  graphics = FN_GRAPHICS(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static GObject *
fn_graphics_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties)
{
  GObject * obj;
  GObjectClass * parent_class =
    G_OBJECT_CLASS(fn_graphics_parent_class);

  obj = parent_class->constructor(gtype, n_properties, properties);

  FnGraphics * graphics;
  graphics = FN_GRAPHICS(obj);
  FnGraphicsPrivate * priv;
  priv = graphics->priv;

  priv->initialized = FALSE;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
    return obj;
  }

  g_print("Initialized graphics\n");

  /* TODO create reference to screen */

  priv->initialized = TRUE;

  return obj;
}

/* --------------------------------------------------------------- */

static void
fn_graphics_dispose(GObject * gobject)
{
  /* TODO release reference to screen */
}

/* --------------------------------------------------------------- */

static void
fn_graphics_finalize(GObject * gobject)
{
  SDL_Quit();
}

/* --------------------------------------------------------------- */
