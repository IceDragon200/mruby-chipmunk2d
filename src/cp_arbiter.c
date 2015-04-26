#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_arbiter.h"
#include "cp_body.h"
#include "cp_contact_point.h"
#include "cp_shape.h"
#include "cp_space.h"
#include "cp_vect.h"
#include "cp_private.h"

static struct RClass *mrb_cp_arbiter_class;

void
mrb_cp_arbiter_user_data_free(mrb_state *mrb, struct mrb_cp_arbiter_user_data *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

void
mrb_cp_arbiter_free(mrb_state *mrb, void *ptr)
{
  cpArbiter *arbiter;
  arbiter = ptr;
  if (arbiter) {
    struct mrb_cp_arbiter_user_data *user_data = cpArbiterGetUserData(arbiter);
    mrb_cp_arbiter_user_data_free(mrb, user_data);
    mrb_free(mrb, arbiter);
  }
}

const struct mrb_data_type mrb_cp_arbiter_type = { "cpArbiter", mrb_cp_arbiter_free };

struct mrb_cp_arbiter_user_data*
mrb_cp_arbiter_user_data_new(mrb_state *mrb)
{
  struct mrb_cp_arbiter_user_data *user_data = mrb_malloc(mrb, sizeof(struct mrb_cp_arbiter_user_data));
  user_data->arbiter = mrb_nil_value();
  user_data->space = mrb_nil_value();
  return user_data;
}

/*
 * @return [Chipmunk2d::Arbiter, nil]
 */
mrb_value
mrb_cp_arbiter_get_mrb_obj(mrb_state *mrb, const cpArbiter *arbiter)
{
  struct mrb_cp_arbiter_user_data *user_data;
  user_data = cpArbiterGetUserData(arbiter);
  if (user_data) {
    return user_data->arbiter;
  } else {
    return mrb_nil_value();
  }
}

/*
 *
 */
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
  shape1 = NULL;
  shape2 = NULL;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterGetShapes(arbiter, &shape1, &shape2);
  argv[0] = mrb_cp_shape_get_mrb_obj(mrb, shape1);
  argv[1] = mrb_cp_shape_get_mrb_obj(mrb, shape2);
  return mrb_ary_new_from_values(mrb, 2, argv);
}

/*
 * @return [Array<Chipmunk2d::Body>]
 */
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

/*
 * @return [Chipmunk2d::ContactPointSet]
 */
static mrb_value
arbiter_get_contact_point_set(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpContactPointSet contact_point_set;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  contact_point_set = cpArbiterGetContactPointSet(arbiter);
  return mrb_cp_contact_point_set_value(mrb, &contact_point_set);
}

/*
 * @return [nil]
 */
static mrb_value
arbiter_set_contact_point_set(mrb_state *mrb, mrb_value self)
{
  /* TODO */
  //cpArbiter *arbiter;
  //mrb_value obj;
  //mrb_get_args(mrb, "o", &obj);
  //arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_nil_value();
}

/*
 * @return [Boolean]
 */
static mrb_value
arbiter_is_first_contact(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterIsFirstContact(arbiter));
}

/*
 * @return [Boolean]
 */
static mrb_value
arbiter_is_removal(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterIsRemoval(arbiter));
}

/*
 * @param [Integer] i  i-th contact point
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
arbiter_get_normal(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_cp_vect_value(mrb, cpArbiterGetNormal(arbiter));
}

/*
 * @param [Integer] i  i-th contact point
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
arbiter_get_point_a(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  mrb_int i;
  mrb_get_args(mrb, "i", &i);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_cp_vect_value(mrb, cpArbiterGetPointA(arbiter, i));
}

/*
 * @param [Integer] i  i-th contact point
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
arbiter_get_point_b(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  mrb_int i;
  mrb_get_args(mrb, "i", &i);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_cp_vect_value(mrb, cpArbiterGetPointB(arbiter, i));
}

/*
 * @param [Integer] i  i-th contact point
 * @return [Float] depth
 */
static mrb_value
arbiter_get_depth(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  mrb_int i;
  mrb_get_args(mrb, "i", &i);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_float_value(mrb, cpArbiterGetDepth(arbiter, i));
}

/*
 * @param [Chipmunk2d::Space] space
 * @return [Boolean]
 */
static mrb_value
arbiter_call_wildcard_begin_a(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &space, &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterCallWildcardBeginA(arbiter, space));
}

/*
 * @param [Chipmunk2d::Space] space
 * @return [Boolean]
 */
static mrb_value
arbiter_call_wildcard_begin_b(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &space, &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterCallWildcardBeginB(arbiter, space));
}

/*
 * @param [Chipmunk2d::Space] space
 * @return [Boolean]
 */
static mrb_value
arbiter_call_wildcard_pre_solve_a(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &space, &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterCallWildcardPreSolveA(arbiter, space));
}

/*
 * @param [Chipmunk2d::Space] space
 * @return [Boolean]
 */
static mrb_value
arbiter_call_wildcard_pre_solve_b(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &space, &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  return mrb_bool_value(cpArbiterCallWildcardBeginA(arbiter, space));
}

/*
 * @param [Chipmunk2d::Space] space
 * @return [nil]
 */
static mrb_value
arbiter_call_wildcard_post_solve_a(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &space, &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterCallWildcardPostSolveA(arbiter, space);
  return mrb_nil_value();
}

/*
 * @param [Chipmunk2d::Space] space
 * @return [nil]
 */
static mrb_value
arbiter_call_wildcard_post_solve_b(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &space, &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterCallWildcardPostSolveB(arbiter, space);
  return mrb_nil_value();
}

/*
 * @param [Chipmunk2d::Space] space
 * @return [nil]
 */
static mrb_value
arbiter_call_wildcard_separate_a(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &space, &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterCallWildcardSeparateA(arbiter, space);
  return mrb_nil_value();
}

/*
 * @param [Chipmunk2d::Space] space
 * @return [nil]
 */
static mrb_value
arbiter_call_wildcard_separate_b(mrb_state *mrb, mrb_value self)
{
  cpArbiter *arbiter;
  cpSpace *space;
  mrb_get_args(mrb, "d", &space, &mrb_cp_space_type);
  arbiter = mrb_data_get_ptr(mrb, self, &mrb_cp_arbiter_type);
  cpArbiterCallWildcardSeparateB(arbiter, space);
  return mrb_nil_value();
}

void
mrb_cp_arbiter_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_arbiter_class = mrb_define_class_under(mrb, cp_module, "Arbiter", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_arbiter_class, MRB_TT_DATA);

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
}
