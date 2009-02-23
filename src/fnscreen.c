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
  SDL_Surface * surface;
  guint width;
  guint height;
  guint scale;
  guint bpp;
  guint sdl_flags;
};

/* =============================================================== */

enum {
  PROP_WIDTH = 1,
  PROP_HEIGHT,
  PROP_SCALE,
  PROP_BPP,
  PROP_SDL_FLAGS
};

/* =============================================================== */

#define FN_SCREEN_DEFAULT_HEIGHT 200
#define FN_SCREEN_DEFAULT_WIDTH  320
#define FN_SCREEN_DEFAULT_SCALE  2
#define FN_SCREEN_DEFAULT_BPP    0
#define FN_SCREEN_DEFAULT_SDL_FLAGS \
  (SDL_HWSURFACE | SDL_HWACCEL | SDL_ANYFORMAT)

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

  GParamSpec * width_param;
  GParamSpec * height_param;
  GParamSpec * scale_param;
  GParamSpec * bpp_param;
  GParamSpec * sdl_flags_param;

  g_object_class = G_OBJECT_CLASS(c);

  g_type_class_add_private(c, sizeof(FnScreenPrivate));

  g_object_class->set_property = fn_screen_set_property;
  g_object_class->get_property = fn_screen_get_property;
  g_object_class->constructor  = fn_screen_constructor;
  g_object_class->dispose      = fn_screen_dispose;
  g_object_class->finalize     = fn_screen_finalize;

  width_param = g_param_spec_uint(
      "width",
      "Width",
      "The width (in unscaled pixels) of the screen",
      0,
      G_MAXUINT,
      FN_SCREEN_DEFAULT_WIDTH,
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );

  g_object_class_install_property(
      g_object_class,
      PROP_WIDTH,
      width_param);


  height_param = g_param_spec_uint(
      "height",
      "Height",
      "The height (in unscaled pixels) of the screen",
      0,
      G_MAXUINT,
      FN_SCREEN_DEFAULT_HEIGHT,
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );

  g_object_class_install_property(
      g_object_class,
      PROP_HEIGHT,
      height_param);


  scale_param = g_param_spec_uint(
      "scale",
      "Scale",
      "The scale factor (final size of one pixel)",
      0,
      G_MAXUINT,
      FN_SCREEN_DEFAULT_SCALE,
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );

  g_object_class_install_property(
      g_object_class,
      PROP_SCALE,
      scale_param);


  bpp_param = g_param_spec_uint(
      "bpp",
      "BPP",
      "The bits per pixel in the SDL screen",
      0,
      G_MAXUINT,
      FN_SCREEN_DEFAULT_BPP,
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );

  g_object_class_install_property(
      g_object_class,
      PROP_BPP,
      bpp_param);


  sdl_flags_param = g_param_spec_uint(
      "sdl_flags",
      "SDL_Flags",
      "The sdl flags for initializing the sdl screen",
      0,
      G_MAXUINT,
      FN_SCREEN_DEFAULT_SDL_FLAGS,
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );

  g_object_class_install_property(
      g_object_class,
      PROP_SDL_FLAGS,
      sdl_flags_param);
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

  priv->surface =
    SDL_SetVideoMode(
        priv->width * priv->scale,
        priv->height * priv->scale,
        priv->bpp,
        priv->sdl_flags
        );

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
  g_return_if_fail(FN_IS_SCREEN(gobject));
  FnScreen * screen = FN_SCREEN(gobject);
  FnScreenPrivate * priv = screen->priv;
  if (priv->surface != NULL) {
    SDL_FreeSurface(priv->surface); priv->surface = NULL;
  }
}

/* =============================================================== */

FnScreen *
fn_screen_new_with_defaults()
{
  FnScreen * screen = g_object_new(
      FN_TYPE_SCREEN,
      NULL);
  return screen;
}

/* =============================================================== */

void
fn_screen_clone_texture(
    FnScreen * screen, FnGeometry * screengeometry,
    FnTexture * source, FnGeometry * sourcegeometry)
{
  g_return_if_fail(FN_IS_SCREEN(screen));
  g_return_if_fail(FN_IS_TEXTURE(source));
  g_return_if_fail(
      screengeometry == NULL || FN_IS_GEOMETRY(screengeometry));
  g_return_if_fail(
      sourcegeometry == NULL || FN_IS_GEOMETRY(sourcegeometry));

  SDL_Rect * sourcerect = NULL;
  SDL_Rect * targetrect = NULL;

  FnScreenPrivate * priv = screen->priv;

  if (sourcegeometry != NULL) {
    sourcerect = g_malloc0(sizeof(SDL_Rect));
    fn_geometry_get_data(sourcegeometry,
        (gint  *) &(sourcerect->x),
        (gint  *) &(sourcerect->y),
        (guint *) &(sourcerect->w),
        (guint *) &(sourcerect->h));
    sourcerect->x *= priv->scale;
    sourcerect->y *= priv->scale;
    sourcerect->w *= priv->scale;
    sourcerect->h *= priv->scale;
  }

  if (screengeometry != NULL) {
    targetrect = g_malloc0(sizeof(SDL_Rect));
    fn_geometry_get_data(screengeometry,
        (gint  *) &(targetrect->x),
        (gint  *) &(targetrect->y),
        (guint *) &(targetrect->w),
        (guint *) &(targetrect->h));
    targetrect->x *= priv->scale;
    targetrect->y *= priv->scale;
    targetrect->w *= priv->scale;
    targetrect->h *= priv->scale;
  }

  fn_texture_blit_to_sdl_surface(
      source,sourcerect,
      screen->priv->surface, targetrect);

  if (sourcerect != NULL) {
    g_free(sourcerect);
  }
  if (targetrect != NULL) {
    g_free(targetrect);
  }
}

/* =============================================================== */
