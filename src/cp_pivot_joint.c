#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_pivot_joint.h"
#include "cp_constraint.h"
#include "cp_body.h"
#include "cp_vect.h"

static struct RClass *mrb_cp_pivot_joint_class;

/*
 * Chipmunk2d::PivotJoint#initialize(a, b, anchor_a, anchor_b)
 * @param [Chipmunk2d::Body] a
 * @param [Chipmunk2d::Body] b
 * @param [Chipmunk2d::Vect] anchor_a
 * @param [Chipmunk2d::Vect] anchor_b
 * @return [self]
 */
static mrb_value
pivot_joint_initialize(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpBody *a;
  cpBody *b;
  cpVect *anchor_a;
  cpVect *anchor_b;
  mrb_value a_obj;
  mrb_value b_obj;
  anchor_b = NULL;
  mrb_get_args(mrb, "ood|d",
                    &a_obj,
                    &b_obj,
                    &anchor_a, &mrb_cp_vect_type,
                    &anchor_b, &mrb_cp_vect_type);
  a = mrb_data_get_ptr(mrb, a_obj, &mrb_cp_body_type);
  b = mrb_data_get_ptr(mrb, b_obj, &mrb_cp_body_type);
  mrb_cp_constraint_cleanup(mrb, self);
  if (anchor_b) {
    /* AnchorA, AnchorB */
    constraint = cpPivotJointNew2(a, b, *anchor_a, *anchor_b);
  } else {
    /* Pivot */
    constraint = cpPivotJointNew(a, b, *anchor_a);
  }
  mrb_cp_constraint_init_bind(mrb, self, constraint);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "body_a"), a_obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "body_b"), b_obj);
  return self;
}

/*
 * Chipmunk2d::PivotJoint#anchor_a
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
pivot_joint_get_anchor_a(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect anchor_a;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  anchor_a = cpPivotJointGetAnchorA(constraint);
  return mrb_cp_vect_value(mrb, anchor_a);
}

/*
 * Chipmunk2d::PivotJoint#anchor_a=(anchor_a)
 * @param [Chipmunk2d::Vect] anchor_a
 */
static mrb_value
pivot_joint_set_anchor_a(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect *anchor_a;
  mrb_get_args(mrb, "d", &anchor_a, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpPivotJointSetAnchorA(constraint, *anchor_a);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::PivotJoint#anchor_b
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
pivot_joint_get_anchor_b(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect anchor_b;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  anchor_b = cpPivotJointGetAnchorB(constraint);
  return mrb_cp_vect_value(mrb, anchor_b);
}

/*
 * Chipmunk2d::PivotJoint#anchor_b=(anchor_b)
 * @param [Chipmunk2d::Vect] anchor_b
 */
static mrb_value
pivot_joint_set_anchor_b(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect *anchor_b;
  mrb_get_args(mrb, "d", &anchor_b, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpPivotJointSetAnchorB(constraint, *anchor_b);
  return mrb_nil_value();
}

void
mrb_cp_pivot_joint_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_pivot_joint_class = mrb_define_class_under(mrb, cp_module, "PivotJoint", mrb_cp_get_constraint_class());
  MRB_SET_INSTANCE_TT(mrb_cp_pivot_joint_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_pivot_joint_class, "initialize", pivot_joint_initialize,    MRB_ARGS_ARG(3,1));
  mrb_define_method(mrb, mrb_cp_pivot_joint_class, "anchor_a",   pivot_joint_get_anchor_a,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_pivot_joint_class, "anchor_a=",  pivot_joint_set_anchor_a,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_pivot_joint_class, "anchor_b",   pivot_joint_get_anchor_b,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_pivot_joint_class, "anchor_b=",  pivot_joint_set_anchor_b,  MRB_ARGS_REQ(1));
}
