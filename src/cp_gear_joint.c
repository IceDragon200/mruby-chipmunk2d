#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_gear_joint.h"
#include "cp_constraint.h"
#include "cp_body.h"

static struct RClass *mrb_cp_gear_joint_class;

static mrb_value
gear_joint_initialize(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpBody *a;
  cpBody *b;
  mrb_value a_obj;
  mrb_value b_obj;
  mrb_float phase;
  mrb_float ratio;
  mrb_get_args(mrb, "ddff",
                    &a, &mrb_cp_body_type,
                    &b, &mrb_cp_body_type,
                    &phase,
                    &ratio);
  mrb_get_args(mrb, "oo", &a_obj, &b_obj);
  mrb_cp_constraint_cleanup(mrb, self);
  constraint = cpGearJointNew(a, b, (cpFloat)phase, (cpFloat)ratio);
  mrb_cp_constraint_init_bind(mrb, self, constraint);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body_a"), a_obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body_b"), b_obj);
  return self;
}

static mrb_value
gear_joint_get_phase(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat phase;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  phase = cpGearJointGetPhase(constraint);
  return mrb_float_value(mrb, (mrb_float)phase);
}

static mrb_value
gear_joint_set_phase(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat phase;
  mrb_get_args(mrb, "f", &phase);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpGearJointSetPhase(constraint, phase);
  return mrb_nil_value();
}

static mrb_value
gear_joint_get_ratio(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat ratio;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  ratio = cpGearJointGetRatio(constraint);
  return mrb_float_value(mrb, (mrb_float)ratio);
}

static mrb_value
gear_joint_set_ratio(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat ratio;
  mrb_get_args(mrb, "f", &ratio);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpGearJointSetRatio(constraint, ratio);
  return mrb_nil_value();
}

void
mrb_cp_gear_joint_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_gear_joint_class = mrb_define_class_under(mrb, cp_module, "GearJoint", mrb_cp_get_constraint_class());
  MRB_SET_INSTANCE_TT(mrb_cp_gear_joint_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_cp_gear_joint_class, "initialize", gear_joint_initialize, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, mrb_cp_gear_joint_class, "phase",      gear_joint_get_phase,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_gear_joint_class, "phase=",     gear_joint_set_phase,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_gear_joint_class, "ratio",      gear_joint_get_ratio,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_gear_joint_class, "ratio=",     gear_joint_set_ratio,  MRB_ARGS_REQ(1));
}
