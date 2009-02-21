/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Actor Group
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

#include "fnactorgroup.h"

/* =============================================================== */

struct _FnActorGroupPrivate
{
};

/* =============================================================== */

#define FN_ACTOR_GROUP_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE(\
                               (o), \
                               FN_TYPE_ACTOR_GROUP, \
                               FnActorGroupPrivate))

/* =============================================================== */

static void
fn_actor_group_init(FnActorGroup * group);

/* --------------------------------------------------------------- */

static void
fn_actor_group_class_init(FnActorGroupClass * c);

/* --------------------------------------------------------------- */

static GObject *
fn_actor_group_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties);

/* --------------------------------------------------------------- */

static void
fn_actor_group_dispose(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_actor_group_finalize(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_actor_group_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec);

/* --------------------------------------------------------------- */

static void
fn_actor_group_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec);

/* =============================================================== */

static void
fn_actor_group_class_init(FnActorGroupClass * c)
{
  GObjectClass * g_object_class;

  g_object_class = G_OBJECT_CLASS(c);

  g_type_class_add_private(c, sizeof(FnActorGroupPrivate));

  g_object_class->set_property = fn_actor_group_set_property;
  g_object_class->get_property = fn_actor_group_get_property;
  g_object_class->constructor  = fn_actor_group_constructor;
  g_object_class->dispose      = fn_actor_group_dispose;
  g_object_class->finalize     = fn_actor_group_finalize;
}

/* =============================================================== */

G_DEFINE_TYPE(FnActorGroup, fn_actor_group, FN_TYPE_ACTOR);

/* =============================================================== */

static void
fn_actor_group_init(FnActorGroup * group)
{
  group->priv = FN_ACTOR_GROUP_GET_PRIVATE(group);
}

/* --------------------------------------------------------------- */

static void
fn_actor_group_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec)
{
  FnActorGroup * group;
  group = FN_ACTOR_GROUP(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static void
fn_actor_group_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec)
{
  FnActorGroup * group;
  group = FN_ACTOR_GROUP(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static GObject *
fn_actor_group_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties)
{
  GObject * obj;
  GObjectClass * parent_class =
    G_OBJECT_CLASS(fn_actor_group_parent_class);

  obj = parent_class->constructor(gtype, n_properties, properties);

  FnActorGroup * group;
  group = FN_ACTOR_GROUP(obj);
  FnActorGroupPrivate * priv;
  priv = group->priv;

  return obj;
}

/* --------------------------------------------------------------- */

static void
fn_actor_group_dispose(GObject * gobject)
{
}

/* --------------------------------------------------------------- */

static void
fn_actor_group_finalize(GObject * gobject)
{
}

/* --------------------------------------------------------------- */

