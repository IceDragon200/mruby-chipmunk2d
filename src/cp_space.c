#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_space.h"
#include "cp_private.h"

static struct RClass *mrb_cp_space_class;

void
mrb_cp_space_free(mrb_state *mrb, void *ptr)
{
  cpSpace *space = ptr;

  if (space) {
    cpSpaceFree(space);
  }
}

struct mrb_data_type mrb_cp_space_type = { "Chipmunk2d::Space", mrb_cp_space_free };

static mrb_value
space_initialize(mrb_state *mrb, mrb_value self)
{
  cpSpace *space;

  space = (cpSpace*)DATA_PTR(self);
  if (space) {
    mrb_cp_space_free(mrb, space);
  }

  space = cpSpaceNew();
  mrb_data_init(self, space, &mrb_cp_space_type);

  return self;
}

static mrb_value
space_get_iterations(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_set_iterations(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_get_gravity(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_set_gravity(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_get_damping(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_set_damping(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_get_idle_speed_threshold(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_set_idle_speed_threshold(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_get_sleep_time_threshold(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_set_sleep_time_threshold(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_get_collision_slop(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_set_collision_slop(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_get_collision_bias(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_set_collision_bias(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_get_collision_persistence(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_set_collision_persistence(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_get_static_body(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_get_current_time_step(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_is_locked(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_add_default_collision_handler(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_add_collision_handler(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_add_wildcard_handler(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_add_shape(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_add_body(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_add_constraint(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_remove_shape(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_remove_body(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_remove_constraint(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_contains_shape(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_contains_body(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_contains_constraint(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_add_post_step_callback(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_point_query(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_point_query_nearest(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_segment_query(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_segment_query_first(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_bb_query(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_shape_query(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_each_body(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_each_shape(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_each_constraint(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_reindex_static(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_reindex_shape(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_reindex_shapes_for_body(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_use_spatial_hash(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value
space_step(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

void
mrb_cp_space_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_space_class = mrb_define_class_under(mrb, cp_module, "Space", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_space_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_cp_space_class, "initialize",                    space_initialize,                    MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "iterations",                    space_get_iterations,                MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "iterations=",                   space_set_iterations,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "gravity",                       space_get_gravity,                   MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "gravity=",                      space_set_gravity,                   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "damping",                       space_get_damping,                   MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "damping=",                      space_set_damping,                   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "idle_speed_threshold",          space_get_idle_speed_threshold,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "idle_speed_threshold=",         space_set_idle_speed_threshold,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "sleep_time_threshold",          space_get_sleep_time_threshold,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "sleep_time_threshold=",         space_set_sleep_time_threshold,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "collision_slop",                space_get_collision_slop,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "collision_slop=",               space_set_collision_slop,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "collision_bias",                space_get_collision_bias,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "collision_bias=",               space_set_collision_bias,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "collision_persistence",         space_get_collision_persistence,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "collision_persistence=",        space_set_collision_persistence,     MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_cp_space_class, "static_body",                   space_get_static_body,               MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "current_time_step",             space_get_current_time_step,         MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "locked?",                       space_is_locked,                     MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_cp_space_class, "add_default_collision_handler", space_add_default_collision_handler, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "add_collision_handler",         space_add_collision_handler,         MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_space_class, "add_wildcard_handler",          space_add_wildcard_handler,          MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_cp_space_class, "add_shape",                     space_add_shape,                     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "add_body",                      space_add_body,                      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "add_constraint",                space_add_constraint,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "remove_shape",                  space_remove_shape,                  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "remove_body",                   space_remove_body,                   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "remove_constraint",             space_remove_constraint,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "contains_shape?",               space_contains_shape,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "contains_body?",                space_contains_body,                 MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "contains_constraint?",          space_contains_constraint,           MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_cp_space_class, "add_post_step_callback",        space_add_post_step_callback,        MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_cp_space_class, "point_query",                   space_point_query,                   MRB_ARGS_REQ(4));
  mrb_define_method(mrb, mrb_cp_space_class, "point_query_nearest",           space_point_query_nearest,           MRB_ARGS_REQ(4));

  mrb_define_method(mrb, mrb_cp_space_class, "segment_query",                 space_segment_query,                 MRB_ARGS_REQ(5));
  mrb_define_method(mrb, mrb_cp_space_class, "segment_query_first",           space_segment_query_first,           MRB_ARGS_REQ(5));

  mrb_define_method(mrb, mrb_cp_space_class, "bb_query",                      space_bb_query,                      MRB_ARGS_REQ(3));
  mrb_define_method(mrb, mrb_cp_space_class, "shape_query",                   space_shape_query,                   MRB_ARGS_REQ(2));

  mrb_define_method(mrb, mrb_cp_space_class, "each_body",                     space_each_body,                     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "each_shape",                    space_each_shape,                    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "each_constraint",               space_each_constraint,               MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_cp_space_class, "reindex_static",                space_reindex_static,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "reindex_shape",                 space_reindex_shape,                 MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "reindex_shapes_for_body",       space_reindex_shapes_for_body,       MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_cp_space_class, "use_spatial_hash",              space_use_spatial_hash,              MRB_ARGS_REQ(2));

  mrb_define_method(mrb, mrb_cp_space_class, "step",                          space_step,                          MRB_ARGS_REQ(1));
}
