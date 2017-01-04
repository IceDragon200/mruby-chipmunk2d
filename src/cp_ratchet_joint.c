#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_ratchet_joint.h"
#include "cp_constraint.h"
#include "cp_body.h"

static struct RClass* mrb_cp_ratchet_joint_class;

/*
 * @param [Chipmunk2d::Body] a
 * @param [Chipmunk2d::Body] b
 * @param [Float] phase
 * @param [Float] ratchet
 */
static mrb_value
ratchet_joint_initialize(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpBody* a;
  cpBody* b;
  mrb_value a_obj;
  mrb_value b_obj;
  mrb_float phase;
  mrb_float ratchet;
  mrb_get_args(mrb, "ooff", &a_obj, &b_obj, &phase, &ratchet);
  a = mrb_cp_get_body_ptr(mrb, a_obj);
  b = mrb_cp_get_body_ptr(mrb, b_obj);
  mrb_cp_constraint_cleanup(mrb, self);
  constraint = cpRatchetJointNew(a, b, (cpFloat)phase, (cpFloat)ratchet);
  mrb_cp_constraint_init_bind(mrb, self, constraint);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "body_a"), a_obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "body_b"), b_obj);
  return self;
}

static mrb_value
ratchet_joint_get_angle(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpFloat angle;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  angle = cpRatchetJointGetAngle(constraint);
  return mrb_float_value(mrb, (mrb_float)angle);
}

static mrb_value
ratchet_joint_set_angle(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  mrb_float angle;
  mrb_get_args(mrb, "f", &angle);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpRatchetJointSetAngle(constraint, (cpFloat)angle);
  return mrb_nil_value();
}

static mrb_value
ratchet_joint_get_phase(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpFloat phase;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  phase = cpRatchetJointGetPhase(constraint);
  return mrb_float_value(mrb, (mrb_float)phase);
}

static mrb_value
ratchet_joint_set_phase(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  mrb_float phase;
  mrb_get_args(mrb, "f", &phase);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpRatchetJointSetPhase(constraint, (cpFloat)phase);
  return mrb_nil_value();
}

static mrb_value
ratchet_joint_get_ratchet(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpFloat ratchet;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  ratchet = cpRatchetJointGetRatchet(constraint);
  return mrb_float_value(mrb, (mrb_float)ratchet);
}

static mrb_value
ratchet_joint_set_ratchet(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  mrb_float ratchet;
  mrb_get_args(mrb, "f", &ratchet);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpRatchetJointSetRatchet(constraint, (cpFloat)ratchet);
  return mrb_nil_value();
}

MRB_CP_EXTERN void
mrb_cp_ratchet_joint_init(mrb_state* mrb, struct RClass* cp_module)
{
  mrb_cp_ratchet_joint_class = mrb_define_class_under(mrb, cp_module, "RatchetJoint", mrb_cp_get_constraint_class());
  MRB_SET_INSTANCE_TT(mrb_cp_ratchet_joint_class, MRB_TT_DATA);
  mrb_define_method(mrb, mrb_cp_ratchet_joint_class, "initialize", ratchet_joint_initialize,  MRB_ARGS_REQ(4));
  mrb_define_method(mrb, mrb_cp_ratchet_joint_class, "angle",      ratchet_joint_get_angle,   MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_ratchet_joint_class, "angle=",     ratchet_joint_set_angle,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_ratchet_joint_class, "phase",      ratchet_joint_get_phase,   MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_ratchet_joint_class, "phase=",     ratchet_joint_set_phase,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_ratchet_joint_class, "ratchet",    ratchet_joint_get_ratchet, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_ratchet_joint_class, "ratchet=",   ratchet_joint_set_ratchet, MRB_ARGS_REQ(1));
}
