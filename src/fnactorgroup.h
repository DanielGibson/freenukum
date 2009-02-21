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

#ifndef FNACTORGROUP_H
#define FNACTORGROUP_H

/* =============================================================== */

#include <SDL.h>
#include <glib-object.h>

/* =============================================================== */

#include "fnactor.h"

/* =============================================================== */

G_BEGIN_DECLS

/* =============================================================== */

typedef struct _FnActorGroupPrivate FnActorGroupPrivate;

/* =============================================================== */

typedef struct _FnGroupActor {
  FnActor fn_actor_instance;
  FnActorGroupPrivate * priv;
} FnActorGroup;

/* =============================================================== */

typedef struct _FnActorGroupClass {
  FnActorClass fn_actor_class;
} FnActorGroupClass;

/* =============================================================== */

#define FN_TYPE_ACTOR_GROUP (fn_actor_group_get_type())
#define FN_ACTOR_GROUP(o) \
  (G_TYPE_CHECK_INSTANCE_CAST((o), FN_TYPE_ACTOR_GROUP, FnActorGroup))
#define FN_ACTOR_GROUP_CLASS(c) \
  (G_TYPE_CHECK_CLASS_CAST((c), FN_TYPE_ACTOR_GROUP, FnActorGroupClass))
#define FN_IS_ACTOR_GROUP(o) \
  (G_TYPE_CHECK_INSTANCE_TYPE((o), FN_TYPE_ACTOR_GROUP))
#define FN_IS_ACTOR_GROUP_CLASS(c) \
  (G_TYPE_CHECK_CLASS_TYPE((c), FN_TYPE_ACTOR_GROUP))
#define FN_ACTOR_GROUP_GET_CLASS(o) \
  (G_TYPE_INSTANCE_GET_CLASS( \
                              (o), \
                              FN_TYPE_ACTOR_GROUP, \
                              FnActorGroupClass))

/* =============================================================== */

GType fn_actor_group_get_type(void);

/* =============================================================== */

G_END_DECLS

/* =============================================================== */

#endif /* FNACTORGROUP_H */

