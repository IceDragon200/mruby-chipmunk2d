#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_constraint.h"
#include "cp_body.h"
#include "cp_shape.h"
#include "cp_private.h"

static struct RClass *mrb_cp_constraint_class;

mrb_cp_constraint_user_data*
mrb_cp_constraint_user_data_new(mrb_state *mrb)
{
  mrb_cp_constraint_user_data *user_data =
    mrb_malloc(mrb, sizeof(mrb_cp_constraint_user_data));

  user_data->constraint = mrb_nil_value();
  user_data->space = mrb_nil_value();

  return user_data;
}

void
mrb_cp_constraint_user_data_free(mrb_state *mrb, mrb_cp_constraint_user_data *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

struct RClass*
mrb_cp_get_constraint_class()
{
  return mrb_cp_constraint_class;
}

void
mrb_cp_constraint_free(mrb_state *mrb, void *ptr)
{
  cpConstraint *constraint = ptr;
  mrb_cp_constraint_user_data *user_data;

  if (constraint) {
    user_data = cpConstraintGetUserData(constraint);
    if (user_data) {
      mrb_cp_constraint_user_data_free(mrb, user_data);
    }
    cpConstraintFree(constraint);
  }
}

struct mrb_data_type mrb_cp_constraint_type = { "Chipmunk2d::Constraint", mrb_cp_constraint_free };

mrb_value
mrb_cp_constraint_get_mrb_obj(mrb_state *mrb, const cpConstraint *constraint)
{
  struct mrb_cp_constraint_user_data *user_data;
  user_data = cpConstraintGetUserData(constraint);
  if (user_data) {
    return user_data->constraint;
  } else {
    return mrb_nil_value();
  }
}

void
mrb_cp_constraint_cleanup(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  constraint = (cpConstraint*)DATA_PTR(self);
  if (constraint) {
    mrb_cp_constraint_free(mrb, constraint);
  }
}

void
mrb_cp_constraint_init_bind(mrb_state *mrb, mrb_value self, cpConstraint *constraint)
{
  mrb_cp_constraint_user_data *user_data;
  user_data = mrb_cp_constraint_user_data_new(mrb);
  user_data->constraint = self;
  cpConstraintSetUserData(constraint, user_data);
  mrb_data_init(self, constraint, &mrb_cp_constraint_type);
}

/*
 * @return [Chipmunk2d::Body]
 * @private api
 */
static mrb_value
constraint_get_mrb_cp_body(mrb_state *mrb, mrb_value self, cpBody *body)
{
  mrb_cp_body_user_data *user_data;
  if (body) {
    user_data = cpBodyGetUserData(body);
    if (!user_data) {
      mrb_raise(mrb, E_RUNTIME_ERROR,
                     "body does not have a valid user_data!");
    } else {
      return user_data->body;
    }
  }
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Constraint#initialize
 * @return [self]
 */
static mrb_value
constraint_initialize(mrb_state *mrb, mrb_value self)
{
  /* Please, for goodness sake (me) don't ever initialize a `Constraint` */
  mrb_raise(mrb, E_RUNTIME_ERROR, "You may not create a `Constraint` Object.");
  return self;
}

/*
 * Chipmunk2d::Constraint#space
 * @return [Chipmunk2d::Space]
 */
static mrb_value
constraint_get_space(mrb_state *mrb, mrb_value self)
{
  mrb_sym space_sym = mrb_intern_cstr(mrb, "space");
  return mrb_iv_get(mrb, self, space_sym);
}

/*
 * Chipmunk2d::Constraint#body_a
 * @return [Chipmunk2d::Body]
 */
static mrb_value
constraint_get_body_a(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpConstraint *constraint;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);
  body = cpConstraintGetBodyA(constraint);
  return constraint_get_mrb_cp_body(mrb, self, body);
}

/*
 * Chipmunk2d::Constraint#body_b
 * @return [Chipmunk2d::Body]
 */
static mrb_value
constraint_get_body_b(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpConstraint *constraint;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);
  body = cpConstraintGetBodyB(constraint);
  return constraint_get_mrb_cp_body(mrb, self, body);
}

/*
 * Chipmunk2d::Constraint#max_force
 * @return [Float]
 */
static mrb_value
constraint_get_max_force(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat max_force;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);
  max_force = cpConstraintGetMaxForce(constraint);
  return mrb_float_value(mrb, max_force);
}

/*
 * Chipmunk2d::Constraint#max_force=(max_force)
 * @param [Float] max_force
 */
static mrb_value
constraint_set_max_force(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  mrb_float max_force;
  mrb_get_args(mrb, "f", &max_force);
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);
  cpConstraintSetMaxForce(constraint, (cpFloat)max_force);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Constraint#error_bias
 * @return [Float]
 */
static mrb_value
constraint_get_error_bias(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat error_bias;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);

  error_bias = cpConstraintGetErrorBias(constraint);
  return mrb_float_value(mrb, error_bias);
}

/*
 * Chipmunk2d::Constraint#error_bias=(error_bias)
 * @param [Float] error_bias
 */
static mrb_value
constraint_set_error_bias(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  mrb_float error_bias;
  mrb_get_args(mrb, "f", &error_bias);

  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);

  cpConstraintSetErrorBias(constraint, (cpFloat)error_bias);

  return mrb_nil_value();
}

/*
 * Chipmunk2d::Constraint#max_bias
 * @return [Float]
 */
static mrb_value
constraint_get_max_bias(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat max_bias;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);
  max_bias = cpConstraintGetMaxBias(constraint);
  return mrb_float_value(mrb, max_bias);
}

/*
 * Chipmunk2d::Constraint#max_bias=(max_bias)
 * @param [Float] max_bias
 */
static mrb_value
constraint_set_max_bias(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  mrb_float max_bias;
  mrb_get_args(mrb, "f", &max_bias);

  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);

  cpConstraintSetMaxBias(constraint, (cpFloat)max_bias);

  return mrb_nil_value();
}

/*
 * Chipmunk2d::Constraint#collide_bodies
 * @return [Boolean]
 */
static mrb_value
constraint_get_collide_bodies(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpBool collide_bodies;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);

  collide_bodies = cpConstraintGetCollideBodies(constraint);
  return mrb_bool_value(collide_bodies);
}

/*
 * Chipmunk2d::Constraint#collide_bodies=(collide_bodies)
 * @param [Boolean] collide_bodies
 */
static mrb_value
constraint_set_collide_bodies(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  mrb_bool collide_bodies;
  mrb_get_args(mrb, "b", &collide_bodies);
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);
  cpConstraintSetCollideBodies(constraint, (cpBool)collide_bodies);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Constraint#impulse
 * @return [Float]
 */
static mrb_value
constraint_get_impulse(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat impulse;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);
  impulse = cpConstraintGetImpulse(constraint);
  return mrb_float_value(mrb, impulse);
}

void
mrb_cp_constraint_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_constraint_class = mrb_define_class_under(mrb, cp_module, "Constraint", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_constraint_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_constraint_class, "initialize",      constraint_initialize,         MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_constraint_class, "space",           constraint_get_space,          MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_constraint_class, "body_a",          constraint_get_body_a,         MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_constraint_class, "body_b",          constraint_get_body_b,         MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_constraint_class, "max_force",       constraint_get_max_force,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_constraint_class, "max_force=",      constraint_set_max_force,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_constraint_class, "error_bias",      constraint_get_error_bias,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_constraint_class, "error_bias=",     constraint_set_error_bias,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_constraint_class, "max_bias",        constraint_get_max_bias,       MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_constraint_class, "max_bias=",       constraint_set_max_bias,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_constraint_class, "collide_bodies",  constraint_get_collide_bodies, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_constraint_class, "collide_bodies=", constraint_set_collide_bodies, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_constraint_class, "impulse",         constraint_get_impulse,        MRB_ARGS_NONE());
}
