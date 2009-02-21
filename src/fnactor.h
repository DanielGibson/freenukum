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

#ifndef FNACTOR_H
#define FNACTOR_H

/* =============================================================== */

#include <SDL.h>
#include <glib-object.h>

/* =============================================================== */

G_BEGIN_DECLS

/* =============================================================== */

typedef struct _FnActorPrivate FnActorPrivate;

/* =============================================================== */

typedef struct _FnActor {
  GObject g_object_instance;
  FnActorPrivate * priv;
} FnActor;

/* =============================================================== */

typedef struct _FnActorClass {
  GObjectClass g_object_class;
} FnActorClass;

/* =============================================================== */

#define FN_TYPE_ACTOR (fn_actor_get_type())
#define FN_ACTOR(o) \
  (G_TYPE_CHECK_INSTANCE_CAST((o), FN_TYPE_ACTOR, FnActor))
#define FN_ACTOR_CLASS(c) \
  (G_TYPE_CHECK_CLASS_CAST((c), FN_TYPE_ACTOR, FnActorClass))
#define FN_IS_ACTOR(o) \
  (G_TYPE_CHECK_INSTANCE_TYPE((o), FN_TYPE_ACTOR))
#define FN_IS_ACTOR_CLASS(c) \
  (G_TYPE_CHECK_CLASS_TYPE((c), FN_TYPE_ACTOR))
#define FN_ACTOR_GET_CLASS(o) \
  (G_TYPE_INSTANCE_GET_CLASS((o), FN_TYPE_ACTOR, FnActorClass))

/* =============================================================== */

GType fn_actor_get_type(void);

/* =============================================================== */

G_END_DECLS

/* =============================================================== */

#endif /* FNACTOR_H */
