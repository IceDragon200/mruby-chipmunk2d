#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_simple_motor.h"
#include "cp_constraint.h"
#include "cp_body.h"

static struct RClass* mrb_cp_simple_motor_class;

static mrb_value
simple_motor_initialize(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpBody* a;
  cpBody* b;
  mrb_value a_obj;
  mrb_value b_obj;
  mrb_float rate;
  mrb_get_args(mrb, "oof", &a_obj, &b_obj, &rate);
  a = mrb_cp_get_body_ptr(mrb, a_obj);
  b = mrb_cp_get_body_ptr(mrb, b_obj);
  mrb_cp_constraint_cleanup(mrb, self);
  constraint = cpSimpleMotorNew(a, b, (cpFloat)rate);
  mrb_cp_constraint_init_bind(mrb, self, constraint);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "body_a"), a_obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "body_b"), b_obj);
  return self;
}

static mrb_value
simple_motor_get_rate(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpFloat rate;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  rate = cpSimpleMotorGetRate(constraint);
  return mrb_float_value(mrb, (mrb_float)rate);
}

static mrb_value
simple_motor_set_rate(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  mrb_float rate;
  mrb_get_args(mrb, "f", &rate);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpSimpleMotorSetRate(constraint, (cpFloat)rate);
  return mrb_nil_value();
}

MRB_CP_EXTERN void
mrb_cp_simple_motor_init(mrb_state* mrb, struct RClass* cp_module)
{
  mrb_cp_simple_motor_class = mrb_define_class_under(mrb, cp_module, "SimpleMotor", mrb_cp_get_constraint_class());
  MRB_SET_INSTANCE_TT(mrb_cp_simple_motor_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_simple_motor_class, "initialize", simple_motor_initialize,    MRB_ARGS_REQ(3));
  mrb_define_method(mrb, mrb_cp_simple_motor_class, "rate",       simple_motor_get_rate,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_simple_motor_class, "rate=",      simple_motor_set_rate,      MRB_ARGS_REQ(1));
}
