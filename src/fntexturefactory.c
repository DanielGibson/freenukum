/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Texture Factory
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

/* =============================================================== */

#include "fntexturefactory.h"

/* =============================================================== */

struct _FnTextureFactoryPrivate
{
  FnGraphicOptions * options;
};

/* =============================================================== */

enum {
  PROP_GRAPHIC_OPTIONS = 1
};

/* =============================================================== */

#define FN_TEXTURE_FACTORY_GET_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE(\
                               (o), \
                               FN_TYPE_TEXTURE_FACTORY, \
                               FnTextureFactoryPrivate))
/* =============================================================== */

static void
fn_texture_factory_init(FnTextureFactory * factory);

/* --------------------------------------------------------------- */

static void
fn_texture_factory_class_init(FnTextureFactoryClass * c);

/* --------------------------------------------------------------- */

static GObject *
fn_texture_factory_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties);

/* --------------------------------------------------------------- */

static void
fn_texture_factory_dispose(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_texture_factory_finalize(GObject * gobject);

/* --------------------------------------------------------------- */

static void
fn_texture_factory_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec);

/* --------------------------------------------------------------- */

static void
fn_texture_factory_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec);

/* --------------------------------------------------------------- */

static void
fn_texture_factory_class_init(FnTextureFactoryClass * c)
{
  GObjectClass * g_object_class;

  GParamSpec * graphic_options_param;

  g_object_class = G_OBJECT_CLASS(c);

  g_type_class_add_private(c, sizeof(FnTextureFactoryPrivate));

  g_object_class->set_property = fn_texture_factory_set_property;
  g_object_class->get_property = fn_texture_factory_get_property;
  g_object_class->constructor  = fn_texture_factory_constructor;
  g_object_class->dispose      = fn_texture_factory_dispose;
  g_object_class->finalize     = fn_texture_factory_finalize;

  graphic_options_param = g_param_spec_pointer(
      "graphic_options",
      "GraphicOptions",
      "The graphic options used to produce new textures",
      G_PARAM_CONSTRUCT_ONLY |
      G_PARAM_STATIC_STRINGS |
      G_PARAM_READWRITE
      );

  g_object_class_install_property(
      g_object_class,
      PROP_GRAPHIC_OPTIONS,
      graphic_options_param);
}

/* =============================================================== */

G_DEFINE_TYPE(
    FnTextureFactory,
    fn_texture_factory,
    FN_TYPE_TEXTURE_FACTORY);

/* =============================================================== */

static void
fn_texture_factory_init(FnTextureFactory * factory)
{
  factory->priv = FN_TEXTURE_FACTORY_GET_PRIVATE(factory);
}

/* --------------------------------------------------------------- */

static void
fn_texture_factory_set_property(
    GObject * object,
    guint prop_id,
    const GValue * value,
    GParamSpec * pspec)
{
  FnTextureFactory * factory;
  factory = FN_TEXTURE_FACTORY(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static void
fn_texture_factory_get_property(
    GObject * object,
    guint prop_id,
    GValue * value,
    GParamSpec * pspec)
{
  FnTextureFactory * factory;
  factory = FN_TEXTURE_FACTORY(object);

  switch(prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* --------------------------------------------------------------- */

static GObject *
fn_texture_factory_constructor(
    GType                   gtype,
    guint                   n_properties,
    GObjectConstructParam * properties)
{
  GObject * obj;
  GObjectClass * parent_class =
    G_OBJECT_CLASS(fn_texture_factory_parent_class);

  obj = parent_class->constructor(gtype, n_properties, properties);

  FnTextureFactory * factory;
  factory = FN_TEXTURE_FACTORY(obj);
  FnTextureFactoryPrivate * priv;
  priv = factory->private;

  return obj;
}

/* --------------------------------------------------------------- */

static void
fn_texture_factory_dispose(GObject * gobject)
{
}

/* --------------------------------------------------------------- */

static void
fn_texture_factory_finalize(GObject * gobject)
{
}

/* =============================================================== */

FnTexture *
fn_texture_factory_produce_texture(FnTextureFactory * factory,
    guint width,
    guint height)
{
  g_return_val_if_fail(FN_IS_TEXTURE_FACTORY(factory), NULL);

  FnTextureFactoryPrivate * priv = factory->priv;

  FnTexture * texture = fn_texture_new_with_options(
      priv->graphic_options,
      width,
      height);
  return texture;
}

/* --------------------------------------------------------------- */
