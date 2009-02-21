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

#include <SDL.h>

/* =============================================================== */

#include "fn.h"
#include "fn_environment.h"
#include "fntexture.h"

/* =============================================================== */

struct _FnTexturePrivate
{
  guint width;
  guint height;
  SDL_Surface * surface;
  fn_environment_t * env;
};

/* =============================================================== */

#define FN_TEXTURE_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE((o), FN_TYPE_TEXTURE, FnTexturePrivate))

/* =============================================================== */

enum {
  PROP_WIDTH = 1,
  PROP_HEIGHT,
  PROP_ENVIRONMENT,
  PROP_DATA
};

/* =============================================================== */

static void
fn_texture_init(FnTexture * texture);

/* --------------------------------------------------------------- */

static void
fn_texture_class_init(FnTextureClass * c);

/* --------------------------------------------------------------- */

static GObject *
fn_texture_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties);

/* --------------------------------------------------------------- */

static void
fn_texture_dispose(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_texture_finalize(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_texture_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec);

/* --------------------------------------------------------------- */

static void
fn_texture_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec);

/* =============================================================== */

static void
fn_texture_class_init(FnTextureClass * c)
{
  GObjectClass * g_object_class;

  GParamSpec * width_param;
  GParamSpec * height_param;
  GParamSpec * environment_param;

  g_object_class = G_OBJECT_CLASS(c);

  g_type_class_add_private(c, sizeof(FnTexturePrivate));

  g_object_class->set_property = fn_texture_set_property;
  g_object_class->get_property = fn_texture_get_property;
  g_object_class->constructor  = fn_texture_constructor;
  g_object_class->dispose      = fn_texture_dispose;
  g_object_class->finalize     = fn_texture_finalize;

  width_param = g_param_spec_uint(
      "width",
      "Width",
      "The width (in pixels) of the texture",
      0,
      G_MAXUINT,
      FN_TEXTURE_DEFAULT_WIDTH,
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_WRITABLE
      );

  g_object_class_install_property(
      G_OBJECT_CLASS(g_object_class),
      PROP_WIDTH,
      width_param);

  height_param = g_param_spec_uint(
      "height",
      "Height",
      "The height (in pixels) of the texture",
      0,
      G_MAXUINT,
      FN_TEXTURE_DEFAULT_HEIGHT,
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_WRITABLE
      );

  g_object_class_install_property(
      G_OBJECT_CLASS(g_object_class),
      PROP_HEIGHT,
      height_param);

  environment_param = g_param_spec_pointer(
      "environment",
      "Environment",
      "The environment struct",
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_WRITABLE
      );

  g_object_class_install_property(
      G_OBJECT_CLASS(g_object_class),
      PROP_ENVIRONMENT,
      environment_param);
}

/* =============================================================== */

FnTexture * fn_texture_new_with_environment(
    guint width,
    guint height,
    fn_environment_t * env
    )
{
  /* TODO remove this function once environment is obsolete,
   * and replace it with fn_texture_new */
  FnTexture * texture = g_object_new(
      FN_TYPE_TEXTURE,
      "width", width,
      "height", height,
      "environment", env,
      NULL
      );
  return texture;
}

/* =============================================================== */

static void
fn_texture_init(FnTexture * texture)
{
  texture->priv = FN_TEXTURE_GET_PRIVATE(texture);
}

/* --------------------------------------------------------------- */

static void
fn_texture_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec)
{
  FnTexture * texture = FN_TEXTURE(object);

  switch(prop_id) {
    case PROP_WIDTH:
      /* TODO write width setter function */
      texture->priv->width = g_value_get_uint(value);
      break;

    case PROP_HEIGHT:
      /* TODO write height setter function */
      texture->priv->height = g_value_get_uint(value);
      break;

    case PROP_ENVIRONMENT:
      /* TODO write environment setter function */
      texture->priv->env = g_value_get_pointer(value);
      break;

    case PROP_DATA:
      fn_texture_set_data(texture, g_value_get_pointer(value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

/* --------------------------------------------------------------- */

static void
fn_texture_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec)
{
  FnTexture * texture = FN_TEXTURE(object);

  switch(prop_id) {
    case PROP_WIDTH:
      /* TODO write width getter function */
      g_value_set_uint(value, texture->priv->width);
      break;

    case PROP_HEIGHT:
      /* TODO write height getter function */
      g_value_set_uint(value, texture->priv->height);
      break;

    case PROP_ENVIRONMENT:
      /* TODO write environment getter function */
      g_value_set_pointer(value, texture->priv->env);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

/* =============================================================== */

G_DEFINE_TYPE(FnTexture, fn_texture, G_TYPE_OBJECT);

/* =============================================================== */

static GObject *
fn_texture_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties)
{
  GObject * obj;
  GObjectClass * parent_class = G_OBJECT_CLASS(fn_texture_parent_class);

  obj = parent_class->constructor(gtype, n_properties, properties);

  FnTexture * texture = FN_TEXTURE(obj);
  FnTexturePrivate * priv = texture->priv;

  SDL_Surface * surface = fn_environment_create_surface(
      priv->env,
      priv->width,
      priv->height);
  SDL_FillRect(
      surface,
      NULL,
      0);

  texture->priv->surface = surface;

  return obj;
}

/* =============================================================== */

static void
fn_texture_dispose(GObject * gobject)
{
}

/* =============================================================== */

static void
fn_texture_finalize(GObject * gobject)
{
  FnTexture * texture = FN_TEXTURE(gobject);

  SDL_FreeSurface(texture->priv->surface);

  G_OBJECT_CLASS(fn_texture_parent_class)->finalize(gobject);
}

/* =============================================================== */

void
fn_texture_set_data(
    FnTexture * texture,
    guchar * data)
{
  g_return_if_fail(FN_IS_TEXTURE(texture));
  FnTexturePrivate * priv = texture->priv;
  Uint32 transparent = fn_environment_get_transparent(priv->env);
  SDL_Surface * surface = priv->surface;

  guint i = 0;
  guint j = 0;
  guchar * iter = data;

  guchar pixelsize = fn_environment_get_pixelsize(priv->env);

  SDL_Rect r;
  r.x = 0;
  r.y = 0;
  r.w = pixelsize;
  r.h = pixelsize;

  SDL_PixelFormat * fmt = surface->format;
  Uint32 color;

  for (i = 0; i < priv->height; i++)
  {
    for (j = 0; j < priv->width; j++)
    {
      guchar red    = iter[0];
      guchar green  = iter[1];
      guchar blue   = iter[2];
      guchar opaque = iter[3];

      if (opaque == 0) {
        color = transparent;
      } else {
        color = SDL_MapRGB(fmt, red, green, blue);
      }

      r.x = j * pixelsize;
      r.y = i * pixelsize;

      SDL_FillRect(surface, &r, color);

      iter += 4;
    }
  }

  priv->surface = surface;
}

/* =============================================================== */

void
fn_texture_blit_to_sdl_surface(
    FnTexture * texture,
    SDL_Rect * srcrect,
    SDL_Surface * destination,
    SDL_Rect * dstrect)
{
  g_return_if_fail(FN_IS_TEXTURE(texture));
  FnTexturePrivate * priv = texture->priv;
  SDL_Surface * src = priv->surface;

  SDL_BlitSurface(src, srcrect, destination, dstrect);
}

/* =============================================================== */

void
fn_texture_clone_to_texture(
    FnTexture * source,
    FnGeometry * sourcegeometry,
    FnTexture * target,
    FnGeometry * targetgeometry)
{
  g_return_if_fail(FN_IS_TEXTURE(source));
  g_return_if_fail(FN_IS_TEXTURE(target));
  if (sourcegeometry != NULL) {
    g_return_if_fail(FN_IS_GEOMETRY(sourcegeometry));
  }
  if (targetgeometry != NULL) {
    g_return_if_fail(FN_IS_GEOMETRY(targetgeometry));
  }

  FnTexturePrivate * sourcepriv = source->priv;
  FnTexturePrivate * targetpriv = target->priv;

  SDL_Rect * sourcerect = NULL;
  if (sourcegeometry != NULL) {
    sourcerect = g_malloc0(sizeof(SDL_Rect));
    fn_geometry_get_data(sourcegeometry,
        (gint  *) &(sourcerect->x),
        (gint  *) &(sourcerect->y),
        (guint *) &(sourcerect->w),
        (guint *) &(sourcerect->h));
  }

  SDL_Rect * targetrect = NULL;
  if (targetgeometry != NULL) {
    targetrect = g_malloc0(sizeof(SDL_Rect));
    fn_geometry_get_data(targetgeometry,
        (gint  *) &(targetrect->x),
        (gint  *) &(targetrect->y),
        (guint *) &(targetrect->w),
        (guint *) &(targetrect->h));
  }

  SDL_BlitSurface(
      sourcepriv->surface, sourcerect,
      targetpriv->surface, targetrect);

  if (sourcerect != NULL) {
    g_free(sourcerect);
  }
  if (targetrect != NULL) {
    g_free(targetrect);
  }
}

/* =============================================================== */

guint
fn_texture_get_width(FnTexture * texture)
{
  g_return_val_if_fail(FN_IS_TEXTURE(texture), 0);
  return texture->priv->width;
}

/* =============================================================== */

guint
fn_texture_get_height(FnTexture * texture)
{
  g_return_val_if_fail(FN_IS_TEXTURE(texture), 0);
  return texture->priv->height;
}

/* =============================================================== */

void
fn_texture_fill_area(
    FnTexture * texture,
    FnGeometry * area,
    guchar red,
    guchar green,
    guchar blue)
{
  g_return_if_fail(FN_IS_TEXTURE(texture));
  if (area != NULL) {
    g_return_if_fail(FN_IS_GEOMETRY(area));
  }

  gint x;
  gint y;
  guint width;
  guint height;

  if (area != NULL) {
    fn_geometry_get_data(area, &x, &y, &width, &height);
  } else {
    x = 0;
    y = 0;
    width = fn_texture_get_width(texture);
    height = fn_texture_get_height(texture);
  }
  SDL_Rect rect = { x, y, width, height };

  Uint32 cursorcolor = SDL_MapRGB(
      texture->priv->surface->format, red, green, blue);
  SDL_FillRect(texture->priv->surface, &rect, cursorcolor);
}

/* =============================================================== */

