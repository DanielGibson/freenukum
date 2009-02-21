/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Actor
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

#include "fnactor.h"

/* =============================================================== */

struct _FnActorPrivate
{
};

/* =============================================================== */

#define FN_ACTOR_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE((o), FN_TYPE_ACTOR, FnActorPrivate))

/* =============================================================== */

static void
fn_actor_init(FnActor * actor);

/* --------------------------------------------------------------- */

static void
fn_actor_class_init(FnActorClass * c);

/* --------------------------------------------------------------- */

static GObject *
fn_actor_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties);

/* --------------------------------------------------------------- */

static void
fn_actor_dispose(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_actor_finalize(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_actor_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec);

/* --------------------------------------------------------------- */

static void
fn_actor_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec);

/* =============================================================== */

static void
fn_actor_class_init(FnActorClass * c)
{
  GObjectClass * g_object_class;

  g_object_class = G_OBJECT_CLASS(c);

  g_type_class_add_private(c, sizeof(FnActorPrivate));

  g_object_class->set_property = fn_actor_set_property;
  g_object_class->get_property = fn_actor_get_property;
  g_object_class->constructor  = fn_actor_constructor;
  g_object_class->dispose      = fn_actor_dispose;
  g_object_class->finalize     = fn_actor_finalize;
}

/* =============================================================== */

G_DEFINE_ABSTRACT_TYPE(FnActor, fn_actor, G_TYPE_OBJECT);

/* =============================================================== */

static void
fn_actor_init(FnActor * actor)
{
  actor->priv = FN_ACTOR_GET_PRIVATE(actor);
}

/* --------------------------------------------------------------- */

static void
fn_actor_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec)
{
  FnActor * actor;
  actor = FN_ACTOR(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static void
fn_actor_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec)
{
  FnActor * actor;
  actor = FN_ACTOR(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static GObject *
fn_actor_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties)
{
  GObject * obj;
  GObjectClass * parent_class = G_OBJECT_CLASS(fn_actor_parent_class);

  obj = parent_class->constructor(gtype, n_properties, properties);

  FnActor * actor;
  actor = FN_ACTOR(obj);
  FnActorPrivate * priv;
  priv = actor->priv;

  return obj;
}

/* --------------------------------------------------------------- */

static void
fn_actor_dispose(GObject * gobject)
{
}

/* --------------------------------------------------------------- */

static void
fn_actor_finalize(GObject * gobject)
{
}

/* --------------------------------------------------------------- */
