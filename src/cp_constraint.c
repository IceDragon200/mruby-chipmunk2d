#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_constraint.h"
#include "cp_private.h"

static struct RClass *mrb_cp_constraint_class;

void
mrb_cp_constraint_free(mrb_state *mrb, void *ptr)
{
  cpConstraint *constraint = ptr;
  mrb_cp_constraint_user_data *user_data;

  if (constraint) {
    user_data = (mrb_cp_constraint_user_data*)cpConstraintGetUserData(constraint);
    if (user_data) {
      mrb_cp_constraint_user_data_free(mrb, user_data);
    }
    cpConstraintFree(constraint);
  }
}

void
mrb_cp_constraint_mark(mrb_state *mrb, void *ptr)
{
  cpConstraint *constraint = ptr;
  mrb_cp_constraint_user_data *user_data;
  if (constraint) {
    user_data = (mrb_cp_constraint_user_data*)cpConstraintGetUserData(constraint);
    if (user_data) {
      mrb_cp_constraint_user_data_mark(mrb, user_data);
    }
  }
}

struct mrb_data_type mrb_cp_constraint_type = { "Chipmunk2d::Constraint", mrb_cp_constraint_free };

static mrb_value
constraint_initialize(mrb_state *mrb, mrb_value self)
{
  //mrb_cp_constraint_user_data_new
  return self;
}

/*
 * @return [Chipmunk2d::Space, nil]
 */
static mrb_value
constraint_get_space(mrb_state *mrb, mrb_value self)
{
  mrb_sym space_sym;

  space_sym = mrb_intern_cstr(mrb, "space");
  return mrb_iv_get(mrb, self, space_sym);
}

static mrb_value
constraint_get_mrb_cp_body(mrb_state *mrb, mrb_value self, cpBody *body)
{
  mrb_cp_body_user_data *user_data;
  if (body) {
    user_data = (mrb_cp_body_user_data*)cpBodyGetUserData(body);
    if (!user_data) {
      mrb_raise(mrb, E_RUNTIME_ERROR,
                     "body does not have a internal user_data!");
    } else {
      return user_data->body;
    }
  }
  return mrb_nil_value();
}

static mrb_value
constraint_get_body_a(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpConstraint *constraint;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);

  body = cpConstraintGetBodyA(constraint);

  return constraint_get_mrb_cp_body(mrb, self, body);
}

static mrb_value
constraint_get_body_b(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpConstraint *constraint;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);

  body = cpConstraintGetBodyB(constraint);

  return constraint_get_mrb_cp_body(mrb, self, body);
}

static mrb_value
constraint_get_max_force(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat max_force;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);

  max_force = cpConstraintGetMaxForce(constraint);
  return mrb_float_value(mrb, max_force);
}

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

static mrb_value
constraint_get_error_bias(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat error_bias;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);

  error_bias = cpConstraintGetErrorBias(constraint);
  return mrb_float_value(mrb, error_bias);
}

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

static mrb_value
constraint_get_max_bias(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat max_bias;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);

  max_bias = cpConstraintGetMaxBias(constraint);
  return mrb_float_value(mrb, max_bias);
}

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

static mrb_value
constraint_get_collide_bodies(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpBool collide_bodies;
  constraint = mrb_data_get_ptr(mrb, self, &mrb_cp_constraint_type);

  collide_bodies = cpConstraintGetCollideBodies(constraint);
  return mrb_bool_value(collide_bodies);
}

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
