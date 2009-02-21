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

#ifndef FNGEOMETRY_H
#define FNGEOMETRY_H

/* =============================================================== */

#include <glib-object.h>

/* =============================================================== */

G_BEGIN_DECLS

/* =============================================================== */

typedef struct _FnGeometryPrivate FnGeometryPrivate;

/* =============================================================== */

typedef struct _FnGeometry {
  GObject g_object_instance;
  FnGeometryPrivate * priv;
} FnGeometry;

/* =============================================================== */

typedef struct _FnGeometryClass {
  GObjectClass g_object_class;
} FnGeometryClass;

/* =============================================================== */

#define FN_TYPE_GEOMETRY (fn_geometry_get_type())
#define FN_GEOMETRY(o) \
  (G_TYPE_CHECK_INSTANCE_CAST((o), FN_TYPE_GEOMETRY, FnGeometry))
#define FN_GEOMETRY_CLASS(c) \
  (G_TYPE_CHECK_CLASS_CAST((c), FN_TYPE_GEOMETRY, FnGeometryClass))
#define FN_IS_GEOMETRY(o) \
  (G_TYPE_CHECK_INSTANCE_TYPE((o), FN_TYPE_GEOMETRY))
#define FN_IS_GEOMETRY_CLASS(c) \
  (G_TYPE_CHECK_CLASS_TYPE((c), FN_TYPE_GEOMETRY))
#define FN_GEOMETRY_GET_CLASS(o) \
  (G_TYPE_INSTANCE_GET_CLASS((o), FN_TYPE_GEOMETRY, FnGeometryClass))

/* =============================================================== */

GType fn_geometry_get_type(void);

/* =============================================================== */

FnGeometry
* fn_geometry_new(
    gint x, gint y, guint width, guint height);

/* =============================================================== */

void
fn_geometry_set_x(FnGeometry * geometry, gint x);

/* --------------------------------------------------------------- */

void
fn_geometry_set_y(FnGeometry * geometry, gint y);

/* --------------------------------------------------------------- */

void
fn_geometry_set_width(FnGeometry * geometry, guint width);

/* --------------------------------------------------------------- */

void
fn_geometry_set_height(FnGeometry * geometry, guint height);

/* --------------------------------------------------------------- */

void
fn_geometry_set_data(
    FnGeometry * geometry,
    gint x,
    gint y,
    guint width,
    guint height);

/* --------------------------------------------------------------- */

/* TODO document that any param except geometry can be NULL.
 * If a parameter is NULL, it is simply not returned.
 */
void
fn_geometry_get_data(
    FnGeometry * geometry,
    gint * x,
    gint * y,
    guint * width,
    guint * height);

/* --------------------------------------------------------------- */

gint
fn_geometry_get_x(FnGeometry * geometry);

/* --------------------------------------------------------------- */

gint
fn_geometry_get_y(FnGeometry * geometry);

/* --------------------------------------------------------------- */

guint
fn_geometry_get_width(FnGeometry * geometry);

/* --------------------------------------------------------------- */

guint
fn_geometry_get_height(FnGeometry * geometry);

/* --------------------------------------------------------------- */

void
fn_geometry_add_x(FnGeometry * geometry, gint x_to_add);

/* --------------------------------------------------------------- */

void
fn_geometry_add_y(FnGeometry * geometry, gint y_to_add);

/* --------------------------------------------------------------- */

FnGeometry *
fn_geometry_clone(FnGeometry * geometry);

/* =============================================================== */

G_END_DECLS

/* =============================================================== */

#endif /* FNGEOMETRY_H */

