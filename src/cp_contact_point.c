#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_space.h"
#include "cp_vect.h"
#include "cp_private.h"

static struct RClass *mrb_cp_contact_point_class;
static struct RClass *mrb_cp_contact_point_set_class;

static mrb_value
mrb_cp_contact_points_value(mrb_state *mrb, cpContactPointSet *contact_point_set)
{
  mrb_value points;
  mrb_value point;
  int i;

  points = mrb_ary_new_capa(mrb, contact_point_set->count);
  for (i = 0; i < contact_point_set->count; ++i) {
    point = mrb_obj_new(mrb, mrb_cp_contact_point_class, 0, NULL);
    mrb_iv_set(mrb, point, mrb_intern_cstr(mrb, "@point_a"),  mrb_cp_vect_value(mrb, contact_point_set->points[i].pointA));
    mrb_iv_set(mrb, point, mrb_intern_cstr(mrb, "@point_b"),  mrb_cp_vect_value(mrb, contact_point_set->points[i].pointB));
    mrb_iv_set(mrb, point, mrb_intern_cstr(mrb, "@distance"), mrb_float_value(mrb, contact_point_set->points[i].distance));
    mrb_ary_set(mrb, points, i, point);
  }
  return points;
}

mrb_value
mrb_cp_contact_point_set_value(mrb_state *mrb, cpContactPointSet *points)
{
  mrb_value cps;
  cps = mrb_obj_new(mrb, mrb_cp_contact_point_set_class, 0, NULL);
  mrb_iv_set(mrb, cps, mrb_intern_cstr(mrb, "@count"), mrb_fixnum_value(points->count));
  mrb_iv_set(mrb, cps, mrb_intern_cstr(mrb, "@normal"), mrb_cp_vect_value(mrb, points->normal));
  mrb_iv_set(mrb, cps, mrb_intern_cstr(mrb, "@points"), mrb_cp_contact_points_value(mrb, points));
  return cps;
}

static mrb_value
contact_point_set_get_count(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@count"));
}

static mrb_value
contact_point_set_set_count(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@count"), obj);
  return mrb_nil_value();
}

static mrb_value
contact_point_set_get_normal(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@normal"));
}

static mrb_value
contact_point_set_set_normal(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@normal"), obj);
  return mrb_nil_value();
}

static mrb_value
contact_point_set_get_points(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@points"));
}

static mrb_value
contact_point_set_set_points(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@points"), obj);
  return mrb_nil_value();
}

static mrb_value
contact_point_get_point_a(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@point_a"));
}

static mrb_value
contact_point_set_point_a(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@point_a"), obj);
  return mrb_nil_value();
}

static mrb_value
contact_point_get_point_b(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@point_b"));
}

static mrb_value
contact_point_set_point_b(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@point_b"), obj);
  return mrb_nil_value();
}

static mrb_value
contact_point_get_distance(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@distance"));
}

static mrb_value
contact_point_set_distance(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@distance"), obj);
  return mrb_nil_value();
}

void
mrb_cp_contact_point_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_contact_point_class = mrb_define_class_under(mrb, cp_module, "ContactPoint", mrb->object_class);
  mrb_cp_contact_point_set_class = mrb_define_class_under(mrb, cp_module, "ContactPointSet", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_contact_point_class, MRB_TT_OBJECT);
  MRB_SET_INSTANCE_TT(mrb_cp_contact_point_set_class, MRB_TT_OBJECT);

  mrb_define_method(mrb, mrb_cp_contact_point_class, "point_a",   contact_point_get_point_a,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_contact_point_class, "point_a=",  contact_point_set_point_a,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_contact_point_class, "point_b",   contact_point_get_point_b,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_contact_point_class, "point_b=",  contact_point_set_point_b,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_contact_point_class, "distance",  contact_point_get_distance, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_contact_point_class, "distance=", contact_point_set_distance, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_cp_contact_point_set_class, "count",   contact_point_set_get_count,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_contact_point_set_class, "count=",  contact_point_set_set_count,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_contact_point_set_class, "normal",  contact_point_set_get_normal, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_contact_point_set_class, "normal=", contact_point_set_set_normal, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_contact_point_set_class, "points",  contact_point_set_get_points, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_contact_point_set_class, "points=", contact_point_set_set_points, MRB_ARGS_REQ(1));
}
