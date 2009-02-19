/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Geometry
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

#include "fngeometry.h"

/* =============================================================== */

struct _FnGeometryPrivate
{
  gint x;
  gint y;
  guint width;
  guint height;
};

/* =============================================================== */

#define FN_GEOMETRY_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE(\
                               (o),\
                               FN_TYPE_GEOMETRY,\
                               FnGeometryPrivate))

/* =============================================================== */

enum {
  PROP_X = 1,
  PROP_Y,
  PROP_WIDTH,
  PROP_HEIGHT
};

/* =============================================================== */

static void
fn_geometry_init(FnGeometry * geometry);

/* --------------------------------------------------------------- */

static void
fn_geometry_class_init(FnGeometryClass * c);

/* --------------------------------------------------------------- */

static void
fn_geometry_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec);

/* --------------------------------------------------------------- */

static void
fn_geometry_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec);

/* =============================================================== */

GType
fn_geometry_get_type(void)
{
  static GType fn_geometry_type = 0;

  if (!fn_geometry_type)
  {
    const GTypeInfo fn_geometry_info =
    {
      sizeof(FnGeometryClass),
      NULL,
      NULL,
      (GClassInitFunc)fn_geometry_class_init,
      NULL,
      NULL,
      sizeof(FnGeometry),
      0,
      (GInstanceInitFunc)fn_geometry_init
    };

    fn_geometry_type =
      g_type_register_static(
          G_TYPE_OBJECT,
          "FnGeometry",
          &fn_geometry_info,
          0);
  }
  return fn_geometry_type;
}

/* --------------------------------------------------------------- */

static void
fn_geometry_class_init(FnGeometryClass * c)
{
  GObjectClass * g_object_class;

  GParamSpec * x_param;
  GParamSpec * y_param;
  GParamSpec * width_param;
  GParamSpec * height_param;

  g_object_class = G_OBJECT_CLASS(c);

  g_type_class_add_private(c, sizeof(FnGeometryPrivate));
  
  g_object_class->set_property = fn_geometry_set_property;
  g_object_class->get_property = fn_geometry_get_property;

  x_param = g_param_spec_uint(
      "x",
      "X",
      "The x coordinate (in pixels)",
      0,
      G_MAXUINT,
      0,
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );

  g_object_class_install_property(
      G_OBJECT_CLASS(g_object_class),
      PROP_X,
      x_param);

  y_param = g_param_spec_uint(
      "y",
      "Y",
      "The y coordinate (in pixels)",
      0,
      G_MAXUINT,
      0,
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );

  g_object_class_install_property(
      G_OBJECT_CLASS(g_object_class),
      PROP_Y,
      y_param);

  width_param = g_param_spec_uint(
      "width",
      "Width",
      "The width (in pixels)",
      0,
      G_MAXUINT,
      0,
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );

  g_object_class_install_property(
      G_OBJECT_CLASS(g_object_class),
      PROP_WIDTH,
      width_param);

  height_param = g_param_spec_uint(
      "height",
      "Height",
      "The height (in pixels)",
      0,
      G_MAXUINT,
      0,
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );

  g_object_class_install_property(
      G_OBJECT_CLASS(g_object_class),
      PROP_HEIGHT,
      height_param);
}

/* =============================================================== */

FnGeometry * fn_geometry_new(
    gint x,
    gint y,
    guint width,
    guint height)
{
  FnGeometry * geometry = g_object_new(
      FN_TYPE_GEOMETRY,
      "x", x,
      "y", y,
      "width", width,
      "height", height,
      NULL);
  return geometry;
}

/* =============================================================== */

static void
fn_geometry_init(FnGeometry * geometry)
{
  geometry->priv = FN_GEOMETRY_GET_PRIVATE(geometry);
}

/* =============================================================== */

static void
fn_geometry_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec)
{
  FnGeometry * geometry = FN_GEOMETRY(object);

  switch(prop_id)
  {

    case PROP_X:
      fn_geometry_set_x(geometry, g_value_get_int(value));
      break;

    case PROP_Y:
      fn_geometry_set_y(geometry, g_value_get_int(value));
      break;

    case PROP_WIDTH:
      fn_geometry_set_width(geometry, g_value_get_uint(value));
      break;

    case PROP_HEIGHT:
      fn_geometry_set_height(geometry, g_value_get_uint(value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

/* --------------------------------------------------------------- */

static void
fn_geometry_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec)
{
  FnGeometry * geometry = FN_GEOMETRY(object);

  switch(prop_id)
  {

    case PROP_X:
      g_value_set_int(value, fn_geometry_get_x(geometry));
      break;

    case PROP_Y:
      g_value_set_int(value, fn_geometry_get_y(geometry));
      break;

    case PROP_WIDTH:
      g_value_set_uint(value, fn_geometry_get_width(geometry));
      break;

    case PROP_HEIGHT:
      g_value_set_uint(value, fn_geometry_get_height(geometry));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

/* =============================================================== */

void
fn_geometry_set_x(FnGeometry * geometry, gint x)
{
  g_return_if_fail(FN_IS_GEOMETRY(geometry));
  geometry->priv->x = x;
  /* TODO emit change signal */
}

/* --------------------------------------------------------------- */

void
fn_geometry_set_y(FnGeometry * geometry, gint y)
{
  g_return_if_fail(FN_IS_GEOMETRY(geometry));
  geometry->priv->y = y;
  /* TODO emit change signal */
}

/* --------------------------------------------------------------- */

void
fn_geometry_set_width(FnGeometry * geometry, guint width)
{
  g_return_if_fail(FN_IS_GEOMETRY(geometry));
  geometry->priv->width = width;
  /* TODO emit change signal */
}

/* --------------------------------------------------------------- */

void
fn_geometry_set_height(FnGeometry * geometry, guint height)
{
  g_return_if_fail(FN_IS_GEOMETRY(geometry));
  geometry->priv->height = height;
  /* TODO emit change signal */
}

/* --------------------------------------------------------------- */

void
fn_geometry_set_data(FnGeometry * geometry,
    gint x,
    gint y,
    guint width,
    guint height)
{
  g_return_if_fail(FN_IS_GEOMETRY(geometry));
  geometry->priv->x = x;
  geometry->priv->y = y;
  geometry->priv->width = width;
  geometry->priv->height = height;
  /* TODO emit change signal */
}

/* --------------------------------------------------------------- */

gint
fn_geometry_get_x(FnGeometry * geometry)
{
  g_return_val_if_fail(FN_IS_GEOMETRY(geometry), 0);
  return geometry->priv->x;
}

/* --------------------------------------------------------------- */

gint
fn_geometry_get_y(FnGeometry * geometry)
{
  g_return_val_if_fail(FN_IS_GEOMETRY(geometry), 0);
  return geometry->priv->y;
}

/* --------------------------------------------------------------- */

guint
fn_geometry_get_width(FnGeometry * geometry)
{
  g_return_val_if_fail(FN_IS_GEOMETRY(geometry), 0);
  return geometry->priv->width;
}

/* --------------------------------------------------------------- */

guint
fn_geometry_get_height(FnGeometry * geometry)
{
  g_return_val_if_fail(FN_IS_GEOMETRY(geometry), 0);
  return geometry->priv->height;
}

/* --------------------------------------------------------------- */

void
fn_geometry_get_data(
    FnGeometry * geometry,
    gint * x,
    gint * y,
    guint * width,
    guint * height)
{
  g_return_if_fail(FN_IS_GEOMETRY(geometry));
  if (x != NULL) {
    *x = geometry->priv->x;
  }
  if (y != NULL) {
    *y = geometry->priv->y;
  }
  if (width != NULL) {
    *width = geometry->priv->width;
  }
  if (height != NULL) {
    *height = geometry->priv->height;
  }
}

/* =============================================================== */
