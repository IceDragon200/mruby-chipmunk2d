#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_pin_joint.h"
#include "cp_constraint.h"
#include "cp_body.h"
#include "cp_vect.h"

static struct RClass* mrb_cp_pin_joint_class;

/*
 * Chipmunk2d::PinJoint#initialize(a, b, anchor_a, anchor_b)
 * @param [Chipmunk2d::Body] a
 * @param [Chipmunk2d::Body] b
 * @param [Chipmunk2d::Vect] anchor_a
 * @param [Chipmunk2d::Vect] anchor_b
 */
static mrb_value
pin_joint_initialize(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpBody* a;
  cpBody* b;
  cpVect* anchor_a;
  cpVect* anchor_b;
  mrb_value a_obj;
  mrb_value b_obj;
  mrb_get_args(mrb, "oodd",
               &a_obj,
               &b_obj,
               &anchor_a, &mrb_cp_vect_type,
               &anchor_b, &mrb_cp_vect_type);
  a = mrb_cp_get_body_ptr(mrb, a_obj);
  b = mrb_cp_get_body_ptr(mrb, b_obj);
  mrb_cp_constraint_cleanup(mrb, self);
  constraint = cpPinJointNew(a, b, *anchor_a, *anchor_b);
  mrb_cp_constraint_init_bind(mrb, self, constraint);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "body_a"), a_obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "body_b"), b_obj);
  return self;
}

/*
 * Chipmunk2d::PinJoint#anchor_a
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
pin_joint_get_anchor_a(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpVect anchor_a;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  anchor_a = cpPinJointGetAnchorA(constraint);
  return mrb_cp_vect_value(mrb, anchor_a);
}

/*
 * Chipmunk2d::PinJoint#anchor_a=(anchor_a)
 * @param [Chipmunk2d::Vect] anchor_a
 */
static mrb_value
pin_joint_set_anchor_a(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpVect* anchor_a;
  mrb_get_args(mrb, "d", &anchor_a, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpPinJointSetAnchorA(constraint, *anchor_a);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::PinJoint#anchor_b
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
pin_joint_get_anchor_b(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpVect anchor_b;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  anchor_b = cpPinJointGetAnchorB(constraint);
  return mrb_cp_vect_value(mrb, anchor_b);
}

/*
 * Chipmunk2d::PinJoint#anchor_b=(anchor_b)
 * @param [Chipmunk2d::Vect] anchor_b
 */
static mrb_value
pin_joint_set_anchor_b(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpVect* anchor_b;
  mrb_get_args(mrb, "d", &anchor_b, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpPinJointSetAnchorB(constraint, *anchor_b);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::PinJoint#dist
 * @return [Float]
 */
static mrb_value
pin_joint_get_dist(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  cpFloat dist;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  dist = cpPinJointGetDist(constraint);
  return mrb_float_value(mrb, (mrb_float)dist);
}

/*
 * Chipmunk2d::PinJoint#dist=(dist)
 * @param [Float] dist
 */
static mrb_value
pin_joint_set_dist(mrb_state* mrb, mrb_value self)
{
  cpConstraint* constraint;
  mrb_float dist;
  mrb_get_args(mrb, "f", &dist);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpPinJointSetDist(constraint, (cpFloat)dist);
  return mrb_nil_value();
}

MRB_CP_EXTERN void
mrb_cp_pin_joint_init(mrb_state* mrb, struct RClass* cp_module)
{
  mrb_cp_pin_joint_class = mrb_define_class_under(mrb, cp_module, "PinJoint", mrb_cp_get_constraint_class());
  MRB_SET_INSTANCE_TT(mrb_cp_pin_joint_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_pin_joint_class, "initialize", pin_joint_initialize,    MRB_ARGS_REQ(4));
  mrb_define_method(mrb, mrb_cp_pin_joint_class, "anchor_a",   pin_joint_get_anchor_a,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_pin_joint_class, "anchor_a=",  pin_joint_set_anchor_a,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_pin_joint_class, "anchor_b",   pin_joint_get_anchor_b,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_pin_joint_class, "anchor_b=",  pin_joint_set_anchor_b,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_pin_joint_class, "dist",       pin_joint_get_dist,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_pin_joint_class, "dist=",      pin_joint_set_dist,      MRB_ARGS_REQ(1));
}
