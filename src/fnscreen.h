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

#ifndef FNSCREEN_H
#define FNSCREEN_H

/* =============================================================== */

#include <glib-object.h>

/* =============================================================== */

#include "fntexture.h"
#include "fngeometry.h"
#include "fnactor.h"

/* =============================================================== */

G_BEGIN_DECLS

/* =============================================================== */

typedef struct _FnScreenPrivate FnScreenPrivate;

/* =============================================================== */

typedef struct _FnScreen {
  FnActor fn_actor_instance;
  FnScreenPrivate * priv;
} FnScreen;

/* =============================================================== */

typedef struct _FnScreenClass {
  FnActorClass fn_actor_class;
} FnScreenClass;

/* =============================================================== */

#define FN_TYPE_SCREEN (fn_screen_get_type())
#define FN_SCREEN(o) \
  (G_TYPE_CHECK_INSTANCE_CAST((o), FN_TYPE_SCREEN, FnScreen))
#define FN_SCREEN_CLASS(c) \
  (G_TYPE_CHECK_CLASS_CAST((c), FN_TYPE_SCREEN, FnScreenClass))
#define FN_IS_SCREEN(o) \
  (G_TYPE_CHECK_INSTANCE_TYPE((o), FN_TYPE_SCREEN))
#define FN_IS_SCREEN_CLASS(c) \
  (G_TYPE_CHECK_CLASS_TYPE((c), FN_TYPE_SCREEN))
#define FN_SCREEN_GET_CLASS(o) \
  (G_TYPE_INSTANCE_GET_CLASS( \
                              (o), \
                              FN_TYPE_SCREEN, \
                              FnScreenClass))

/* =============================================================== */

GType fn_screen_get_type(void);

/* =============================================================== */

FnScreen * fn_screen_new_with_defaults();

/* =============================================================== */

void
fn_screen_clone_texture(
    FnScreen * screen, FnGeometry * screengeometry,
    FnTexture * source, FnGeometry * sourcegeometry);

/* =============================================================== */

void
fn_screen_toggle_fullscreen(FnScreen * screen);

/* =============================================================== */

void
fn_screen_update(FnScreen * screen);

/* =============================================================== */

void
fn_screen_snapshot_push(FnScreen * screen);

/* =============================================================== */

void
fn_screen_snapshot_pop(FnScreen * screen);

/* =============================================================== */

guint
fn_screen_get_width(FnScreen * screen);

/* =============================================================== */

guint
fn_screen_get_height(FnScreen * screen);

/* =============================================================== */

G_END_DECLS

/* =============================================================== */

#endif /* FNSCREEN_H */
