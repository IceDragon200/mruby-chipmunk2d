#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_arbiter.h"
#include "cp_space.h"
#include "cp_vect.h"
#include "cp_private.h"

static struct RClass *mrb_cp_arbiter_class;
static struct RClass *mrb_cp_arbiter_contact_point_class;
static struct RClass *mrb_cp_arbiter_contact_point_set_class;

void
mrb_cp_arbiter_free(mrb_state *mrb, void *ptr)
{
  cpArbiter *mrb_cp_arbiter = ptr;

  if (mrb_cp_arbiter) {
    mrb_free(mrb, mrb_cp_arbiter);
  }
}

void
mrb_cp_arbiter_mark(mrb_state *mrb, void *ptr)
{
  cpArbiter *mrb_cp_arbiter = ptr;

  if (mrb_cp_arbiter) {
    mrb_free(mrb, mrb_cp_arbiter);
  }
}

struct mrb_data_type mrb_cp_arbiter_type = { "Chipmunk2d::Arbiter", mrb_cp_arbiter_free };

static mrb_value
mrb_cp_arbiter_contact_points_value(mrb_state *mrb, cpContactPointSet *contact_point_set)
{
  mrb_value points;
  mrb_value point;
  int i;

  points = mrb_ary_new_capa(mrb, contact_point_set->count);
  for (i = 0; i < contact_point_set->count; ++i) {
    point = mrb_obj_new(mrb, mrb_cp_arbiter_contact_point_class, 0, NULL);
    mrb_iv_set(mrb, point, mrb_intern_cstr(mrb, "@point_a"),  mrb_cp_vect_value(mrb, contact_point_set->points[i].pointA));
    mrb_iv_set(mrb, point, mrb_intern_cstr(mrb, "@point_b"),  mrb_cp_vect_value(mrb, contact_point_set->points[i].pointB));
    mrb_iv_set(mrb, point, mrb_intern_cstr(mrb, "@distance"), mrb_float_value(mrb, contact_point_set->points[i].distance));
    mrb_ary_set(mrb, points, i, point);
  }
  return points;
}

static mrb_value
arbiter_contact_point_set_get_count(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@count"));
}

static mrb_value
arbiter_contact_point_set_set_count(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@count"), obj);
  return mrb_nil_value();
}

static mrb_value
arbiter_contact_point_set_get_normal(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@normal"));
}

static mrb_value
arbiter_contact_point_set_set_normal(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@normal"), obj);
  return mrb_nil_value();
}

static mrb_value
arbiter_contact_point_set_get_points(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@points"));
}

static mrb_value
arbiter_contact_point_set_set_points(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@points"), obj);
  return mrb_nil_value();
}

static mrb_value
arbiter_contact_point_get_point_a(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@point_a"));
}

static mrb_value
arbiter_contact_point_set_point_a(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@point_a"), obj);
  return mrb_nil_value();
}

static mrb_value
arbiter_contact_point_get_point_b(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@point_b"));
}

static mrb_value
arbiter_contact_point_set_point_b(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@point_b"), obj);
  return mrb_nil_value();
}

static mrb_value
arbiter_contact_point_get_distance(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@distance"));
}

static mrb_value
arbiter_contact_point_set_distance(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@distance"), obj);
  return mrb_nil_value();
}

static mrb_value
arbiter_get_restitution(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_float_value(mrb, cpArbiterGetRestitution(arbiter));
}

static mrb_value
arbiter_set_restitution(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  mrb_float restitution;
  mrb_get_args(mrb, "f", &restitution);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterSetRestitution(arbiter, (cpFloat)restitution);
  return mrb_nil_value();
}

static mrb_value
arbiter_get_friction(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_float_value(mrb, cpArbiterGetFriction(arbiter));
}

static mrb_value
arbiter_set_friction(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  mrb_float friction;
  mrb_get_args(mrb, "f", &friction);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterSetFriction(arbiter, (cpFloat)friction);
  return mrb_nil_value();
}

cpVect cpArbiterGetSurfaceVelocity(cpArbiter *arb);

static mrb_value
arbiter_get_surface_velocity(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpVect vect;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  vect = cpArbiterGetSurfaceVelocity(arbiter);
  return mrb_cp_vect_value(mrb, vect);
}

static mrb_value
arbiter_set_surface_velocity(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpVect *vect;
  mrb_get_args(mrb, "d", &vect, &mrb_cp_vect_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterSetSurfaceVelocity(arbiter, *vect);
  return mrb_nil_value();
}

static mrb_value
arbiter_total_impulse(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpVect vect;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  vect = cpArbiterTotalImpulse(arbiter);
  return mrb_cp_vect_value(mrb, vect);
}

static mrb_value
arbiter_total_ke(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpFloat ke;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  ke = cpArbiterTotalKE(arbiter);
  return mrb_float_value(mrb, (cpBool)ke);
}

static mrb_value
arbiter_ignore(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpFloat ignore;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  ignore = cpArbiterIgnore(arbiter);
  return mrb_bool_value(ignore);
}

static mrb_value
arbiter_shapes(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpShape *shape1;
  cpShape *shape2;
  mrb_value argv[2] = { mrb_nil_value(), mrb_nil_value() };
  mrb_cp_shape_user_data *user_data;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);

  cpArbiterGetShapes(arbiter, &shape1, &shape2);

  user_data = cpShapeGetUserData(shape1);
  if (user_data) {
    argv[0] = user_data->shape;
  }

  user_data = cpShapeGetUserData(shape2);
  if (user_data) {
    argv[1] = user_data->shape;
  }

  return mrb_ary_new_from_values(mrb, 2, argv);
}

static mrb_value
arbiter_bodies(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpBody *body1;
  cpBody *body2;
  mrb_value argv[2] = { mrb_nil_value(), mrb_nil_value() };
  mrb_cp_body_user_data *user_data;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);

  cpArbiterGetBodies(arbiter, &body1, &body2);

  user_data = cpBodyGetUserData(body1);
  if (user_data) {
    argv[0] = user_data->body;
  }

  user_data = cpBodyGetUserData(body2);
  if (user_data) {
    argv[1] = user_data->body;
  }

  return mrb_ary_new_from_values(mrb, 2, argv);
}

static mrb_value
arbiter_get_contact_point_set(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpContactPointSet contact_point_set;
  mrb_value cps;

  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);

  contact_point_set = cpArbiterGetContactPointSet(arbiter);

  cps = mrb_obj_new(mrb, mrb_cp_arbiter_contact_point_set_class, 0, NULL);
  mrb_iv_set(mrb, cps, mrb_intern_cstr(mrb, "@count"), mrb_fixnum_value(contact_point_set.count));
  mrb_iv_set(mrb, cps, mrb_intern_cstr(mrb, "@normal"), mrb_cp_vect_value(mrb, contact_point_set.normal));
  mrb_iv_set(mrb, cps, mrb_intern_cstr(mrb, "@points"), mrb_cp_arbiter_contact_points_value(mrb, &contact_point_set));

  return cps;
}

static mrb_value
arbiter_set_contact_point_set(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_nil_value();
}

static mrb_value
arbiter_is_first_contact(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterIsFirstContact(arbiter));
}

static mrb_value
arbiter_is_removal(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterIsRemoval(arbiter));
}

static mrb_value
arbiter_get_normal(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_cp_vect_value(mrb, cpArbiterGetNormal(arbiter));
}

static mrb_value
arbiter_get_point_a(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  mrb_int i;
  mrb_get_args(mrb, "i", &i);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_cp_vect_value(mrb, cpArbiterGetPointA(arbiter, i));
}

static mrb_value
arbiter_get_point_b(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  mrb_int i;
  mrb_get_args(mrb, "i", &i);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_cp_vect_value(mrb, cpArbiterGetPointB(arbiter, i));
}

static mrb_value
arbiter_get_depth(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  mrb_int i;
  mrb_get_args(mrb, "i", &i);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_float_value(mrb, cpArbiterGetDepth(arbiter, i));
}

static mrb_value
arbiter_call_wildcard_begin_a(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterCallWildcardBeginA(arbiter, space));
}

static mrb_value
arbiter_call_wildcard_begin_b(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterCallWildcardBeginB(arbiter, space));
}

static mrb_value
arbiter_call_wildcard_pre_solve_a(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterCallWildcardPreSolveA(arbiter, space));
}

static mrb_value
arbiter_call_wildcard_pre_solve_b(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterCallWildcardBeginA(arbiter, space));
}

static mrb_value
arbiter_call_wildcard_post_solve_a(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterCallWildcardPostSolveA(arbiter, space);
  return mrb_nil_value();
}

static mrb_value
arbiter_call_wildcard_post_solve_b(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterCallWildcardPostSolveB(arbiter, space);
  return mrb_nil_value();
}

static mrb_value
arbiter_call_wildcard_separate_a(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterCallWildcardSeparateA(arbiter, space);
  return mrb_nil_value();
}

static mrb_value
arbiter_call_wildcard_separate_b(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterCallWildcardSeparateB(arbiter, space);
  return mrb_nil_value();
}

void
mrb_cp_arbiter_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_arbiter_class = mrb_define_class_under(mrb, cp_module, "Arbiter", mrb->object_class);
  mrb_cp_arbiter_contact_point_class = mrb_define_class_under(mrb, mrb_cp_arbiter_class, "ContactPoint", mrb->object_class);
  mrb_cp_arbiter_contact_point_set_class = mrb_define_class_under(mrb, mrb_cp_arbiter_class, "ContactPointSet", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_arbiter_class, MRB_TT_DATA);
  MRB_SET_INSTANCE_TT(mrb_cp_arbiter_contact_point_class, MRB_TT_OBJECT);
  MRB_SET_INSTANCE_TT(mrb_cp_arbiter_contact_point_set_class, MRB_TT_OBJECT);

  mrb_define_method(mrb, mrb_cp_arbiter_class, "restitution",                arbiter_get_restitution,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "restitution=",               arbiter_set_restitution,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "friction",                   arbiter_get_friction,               MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "friction=",                  arbiter_set_friction,               MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "surface_velocity",           arbiter_get_surface_velocity,       MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "surface_velocity=",          arbiter_set_surface_velocity,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "total_impulse",              arbiter_total_impulse,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "total_ke",                   arbiter_total_ke,                   MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "ignore",                     arbiter_ignore,                     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "shapes",                     arbiter_shapes,                     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "bodies",                     arbiter_bodies,                     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "contact_point_set",          arbiter_get_contact_point_set,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "contact_point_set=",         arbiter_set_contact_point_set,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "first_contact?",             arbiter_is_first_contact,           MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "removal?",                   arbiter_is_removal,                 MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "normal",                     arbiter_get_normal,                 MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_class, "point_a",                    arbiter_get_point_a,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "point_b",                    arbiter_get_point_b,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "depth",                      arbiter_get_depth,                  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "call_wildcard_begin_a",      arbiter_call_wildcard_begin_a,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "call_wildcard_begin_b",      arbiter_call_wildcard_begin_b,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "call_wildcard_pre_solve_a",  arbiter_call_wildcard_pre_solve_a,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "call_wildcard_pre_solve_b",  arbiter_call_wildcard_pre_solve_b,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "call_wildcard_post_solve_a", arbiter_call_wildcard_post_solve_a, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "call_wildcard_post_solve_b", arbiter_call_wildcard_post_solve_b, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "call_wildcard_separate_a",   arbiter_call_wildcard_separate_a,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_class, "call_wildcard_separate_b",   arbiter_call_wildcard_separate_b,   MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_class, "point_a",   arbiter_contact_point_get_point_a,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_class, "point_a=",  arbiter_contact_point_set_point_a,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_class, "point_b",   arbiter_contact_point_get_point_b,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_class, "point_b=",  arbiter_contact_point_set_point_b,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_class, "distance",  arbiter_contact_point_get_distance, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_class, "distance=", arbiter_contact_point_set_distance, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_set_class, "count",   arbiter_contact_point_set_get_count,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_set_class, "count=",  arbiter_contact_point_set_set_count,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_set_class, "normal",  arbiter_contact_point_set_get_normal, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_set_class, "normal=", arbiter_contact_point_set_set_normal, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_set_class, "points",  arbiter_contact_point_set_get_points, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_arbiter_contact_point_set_class, "points=", arbiter_contact_point_set_set_points, MRB_ARGS_REQ(1));
}
