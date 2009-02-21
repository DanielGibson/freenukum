/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Game Screen
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

#include "fnscreen.h"

/* =============================================================== */

struct _FnScreenPrivate
{
  SDL_Surface * screen;
};

/* =============================================================== */

#define FN_SCREEN_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE((o), FN_TYPE_SCREEN, FnScreenPrivate))

/* =============================================================== */

static void
fn_screen_init(FnScreen * screen);

/* --------------------------------------------------------------- */

static void
fn_screen_class_init(FnScreenClass * c);

/* --------------------------------------------------------------- */

static GObject *
fn_screen_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties);

/* --------------------------------------------------------------- */

static void
fn_screen_dispose(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_screen_finalize(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_screen_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec);

/* --------------------------------------------------------------- */

static void
fn_screen_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec);

/* =============================================================== */

static void
fn_screen_class_init(FnScreenClass * c)
{
  GObjectClass * g_object_class;

  g_object_class = G_OBJECT_CLASS(c);

  g_type_class_add_private(c, sizeof(FnScreenPrivate));

  g_object_class->set_property = fn_screen_set_property;
  g_object_class->get_property = fn_screen_get_property;
  g_object_class->constructor  = fn_screen_constructor;
  g_object_class->dispose      = fn_screen_dispose;
  g_object_class->finalize     = fn_screen_finalize;
}

/* =============================================================== */

G_DEFINE_TYPE(FnScreen, fn_screen, FN_TYPE_ACTOR);

/* =============================================================== */

static void
fn_screen_init(FnScreen * screen)
{
  screen->priv = FN_SCREEN_GET_PRIVATE(screen);
}

/* --------------------------------------------------------------- */

static void
fn_screen_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec)
{
  FnScreen * screen;
  screen = FN_SCREEN(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static void
fn_screen_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec)
{
  FnScreen * screen;
  screen = FN_SCREEN(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static GObject *
fn_screen_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties)
{
  GObject * obj;
  GObjectClass * parent_class =
    G_OBJECT_CLASS(fn_screen_parent_class);

  obj = parent_class->constructor(gtype, n_properties, properties);

  FnScreen * screen;
  screen = FN_SCREEN(obj);
  FnScreenPrivate * priv;
  priv = screen->priv;

  /* TODO initialize the screen */

  return obj;
}

/* --------------------------------------------------------------- */

static void
fn_screen_dispose(GObject * gobject)
{
}

/* --------------------------------------------------------------- */

static void
fn_screen_finalize(GObject * gobject)
{
  /* TODO remove the screen */
}

/* --------------------------------------------------------------- */
