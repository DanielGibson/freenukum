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

#include <SDL.h>

/* =============================================================== */

#include "fn.h"
#include "fn_environment.h"
#include "fntile.h"

/* =============================================================== */

struct _FnTilePrivate
{
  guint width;
  guint height;
  SDL_Surface * surface;
  fn_environment_t * env;
};

/* =============================================================== */

#define FN_TILE_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE((o), FN_TYPE_TILE, FnTilePrivate))

/* =============================================================== */

enum {
  PROP_WIDTH = 1,
  PROP_HEIGHT,
  PROP_ENVIRONMENT,
  PROP_DATA
};

/* =============================================================== */

static void
fn_tile_init(FnTile * tile);

/* --------------------------------------------------------------- */

static void
fn_tile_class_init(FnTileClass * c);

/* --------------------------------------------------------------- */

static void
fn_tile_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec);

/* --------------------------------------------------------------- */

static void
fn_tile_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec);

/* =============================================================== */

GType fn_tile_get_type(void)
{
  static GType fn_tile_type = 0;

  if (!fn_tile_type)
  {
    const GTypeInfo fn_tile_info =
    {
      sizeof(FnTileClass),
      NULL,
      NULL,
      (GClassInitFunc)fn_tile_class_init,
      NULL,
      NULL,
      sizeof(FnTile),
      0,
      (GInstanceInitFunc)fn_tile_init
    };

    fn_tile_type =
      g_type_register_static(
          G_TYPE_OBJECT,
          "FnTile",
          &fn_tile_info,
          0);
  }

  return fn_tile_type;
}

/* --------------------------------------------------------------- */

static void
fn_tile_class_init(FnTileClass * c)
{
  GObjectClass * g_object_class;

  GParamSpec * width_param;
  GParamSpec * height_param;
  GParamSpec * environment_param;

  g_object_class = G_OBJECT_CLASS(c);

  g_type_class_add_private(c, sizeof(FnTilePrivate));

  g_object_class->set_property = fn_tile_set_property;
  g_object_class->get_property = fn_tile_get_property;

  width_param = g_param_spec_uint(
      "width",
      "Width",
      "The width (in pixels) of the tile",
      0,
      G_MAXUINT,
      FN_TILE_WIDTH,
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
      "The height (in pixels) of the tile",
      0,
      G_MAXUINT,
      FN_TILE_HEIGHT,
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

FnTile * fn_tile_new_with_environment(
    guint width,
    guint height,
    fn_environment_t * env
    )
{
  /* TODO remove this function once environment is obsolete,
   * and replace it with fn_tile_new */
  FnTile * tile = g_object_new(
      FN_TYPE_TILE,
      "width", width,
      "height", height,
      "environment", env,
      NULL
      );
  return tile;
}

/* =============================================================== */

static void
fn_tile_init(FnTile * tile)
{
  tile->priv = FN_TILE_GET_PRIVATE(tile);
}

/* --------------------------------------------------------------- */

static void
fn_tile_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec)
{
  FnTile * tile = FN_TILE(object);

  switch(prop_id) {
    case PROP_WIDTH:
      /* TODO write width setter function */
      tile->priv->width = g_value_get_uint(value);
      break;

    case PROP_HEIGHT:
      /* TODO write height setter function */
      tile->priv->height = g_value_get_uint(value);
      break;

    case PROP_ENVIRONMENT:
      /* TODO write environment setter function */
      tile->priv->env = g_value_get_pointer(value);
      break;

    case PROP_DATA:
      fn_tile_set_data(tile, g_value_get_pointer(value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

/* --------------------------------------------------------------- */

static void
fn_tile_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec)
{
  FnTile * tile = FN_TILE(object);

  switch(prop_id) {
    case PROP_WIDTH:
      /* TODO write width getter function */
      g_value_set_uint(value, tile->priv->width);
      break;

    case PROP_HEIGHT:
      /* TODO write height getter function */
      g_value_set_uint(value, tile->priv->height);
      break;

    case PROP_ENVIRONMENT:
      /* TODO write environment getter function */
      g_value_set_pointer(value, tile->priv->env);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

/* =============================================================== */

void
fn_tile_set_data(
    FnTile * tile,
    guchar * data)
{
  /* TODO check if object is really of FnTile type */
  FnTilePrivate * priv = tile->priv;
  Uint32 transparent = fn_environment_get_transparent(priv->env);
  SDL_Surface * surface = fn_environment_create_surface(
      priv->env,
      priv->width,
      priv->height);

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
fn_tile_blit_to_sdl_surface(
    FnTile * tile,
    SDL_Rect * srcrect,
    SDL_Surface * destination,
    SDL_Rect * dstrect)
{
  /* TODO check for right gobject type of tile */
  FnTilePrivate * priv = tile->priv;
  SDL_Surface * src = priv->surface;

  SDL_BlitSurface(src, srcrect, destination, dstrect);
}

/* =============================================================== */
