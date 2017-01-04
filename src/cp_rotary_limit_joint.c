#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_rotary_limit_joint.h"
#include "cp_constraint.h"
#include "cp_body.h"

static struct RClass* mrb_cp_rotary_limit_joint_class;

static mrb_value
rotary_limit_joint_initialize(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpBody* a;
  cpBody* b;
  mrb_value a_obj;
  mrb_value b_obj;
  mrb_float min;
  mrb_float max;
  mrb_get_args(mrb, "ooff", &a_obj, &b_obj, &min, &max);
  a = mrb_cp_get_body_ptr(mrb, a_obj);
  b = mrb_cp_get_body_ptr(mrb, b_obj);
  mrb_cp_constraint_cleanup(mrb, self);
  constraint = cpRotaryLimitJointNew(a, b, (cpFloat)min, (cpFloat)max);
  mrb_cp_constraint_init_bind(mrb, self, constraint);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "body_a"), a_obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "body_b"), b_obj);
  return self;
}

static mrb_value
rotary_limit_joint_get_min(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpFloat mn;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  mn = cpRotaryLimitJointGetMin(constraint);
  return mrb_float_value(mrb, (mrb_float)mn);
}

static mrb_value
rotary_limit_joint_set_min(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  mrb_float mn;
  mrb_get_args(mrb, "f", &mn);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpRotaryLimitJointSetMin(constraint, (cpFloat)mn);
  return mrb_nil_value();
}

static mrb_value
rotary_limit_joint_get_max(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpFloat mx;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  mx = cpRotaryLimitJointGetMax(constraint);
  return mrb_float_value(mrb, (mrb_float)mx);
}

static mrb_value
rotary_limit_joint_set_max(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  mrb_float mx;
  mrb_get_args(mrb, "f", &mx);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpRotaryLimitJointSetMax(constraint, (cpFloat)mx);
  return mrb_nil_value();
}

MRB_CP_EXTERN void
mrb_cp_rotary_limit_joint_init(mrb_state* mrb, struct RClass* cp_module)
{
  mrb_cp_rotary_limit_joint_class = mrb_define_class_under(mrb, cp_module, "RotaryLimitJoint", mrb_cp_get_constraint_class());
  MRB_SET_INSTANCE_TT(mrb_cp_rotary_limit_joint_class, MRB_TT_DATA);
  mrb_define_method(mrb, mrb_cp_rotary_limit_joint_class, "initialize", rotary_limit_joint_initialize,  MRB_ARGS_REQ(4));
  mrb_define_method(mrb, mrb_cp_rotary_limit_joint_class, "min",        rotary_limit_joint_get_min,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_rotary_limit_joint_class, "min=",       rotary_limit_joint_set_min,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_rotary_limit_joint_class, "max",        rotary_limit_joint_get_max,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_rotary_limit_joint_class, "max=",       rotary_limit_joint_set_max,     MRB_ARGS_REQ(1));
}
