#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_groove_joint.h"
#include "cp_constraint.h"
#include "cp_body.h"
#include "cp_vect.h"

static struct RClass *mrb_cp_groove_joint_class;

/*
 * Chipmunk2d::GrooveJoint#initialize(a, b, groove_a, groove_b, anchor_b)
 * @param [Chipmunk2d::Body] a
 * @param [Chipmunk2d::Body] b
 * @param [Chipmunk2d::Vect] groove_a
 * @param [Chipmunk2d::Vect] groove_b
 * @param [Chipmunk2d::Vect] anchor_b
 * @return [self]
 */
static mrb_value
groove_joint_initialize(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpBody *a;
  cpBody *b;
  cpVect *groove_a;
  cpVect *groove_b;
  cpVect *anchor_b;
  mrb_value a_obj;
  mrb_value b_obj;
  mrb_get_args(mrb, "ooddd",
                    &a_obj,
                    &b_obj,
                    &groove_a, &mrb_cp_vect_type,
                    &groove_b, &mrb_cp_vect_type,
                    &anchor_b, &mrb_cp_vect_type);
  a = mrb_data_get_ptr(mrb, a_obj, &mrb_cp_body_type);
  b = mrb_data_get_ptr(mrb, b_obj, &mrb_cp_body_type);
  mrb_cp_constraint_cleanup(mrb, self);
  constraint = cpGrooveJointNew(a, b, *groove_a, *groove_b, *anchor_b);
  mrb_cp_constraint_init_bind(mrb, self, constraint);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body_a"), a_obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body_b"), b_obj);
  return self;
}

/*
 * Chipmunk2d::GrooveJoint#groove_a
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
groove_joint_get_groove_a(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect groove_a;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  groove_a = cpGrooveJointGetGrooveA(constraint);
  return mrb_cp_vect_value(mrb, groove_a);
}

/*
 * Chipmunk2d::GrooveJoint#groove_a=(groove_a)
 * @param [Chipmunk2d::Vect] groove_a
 */
static mrb_value
groove_joint_set_groove_a(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect *groove_a;
  mrb_get_args(mrb, "d", &groove_a, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpGrooveJointSetGrooveA(constraint, *groove_a);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::GrooveJoint#groove_b
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
groove_joint_get_groove_b(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect groove_b;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  groove_b = cpGrooveJointGetGrooveB(constraint);
  return mrb_cp_vect_value(mrb, groove_b);
}

/*
 * Chipmunk2d::GrooveJoint#groove_b=(groove_b)
 * @param [Chipmunk2d::Vect] groove_b
 */
static mrb_value
groove_joint_set_groove_b(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect *groove_b;
  mrb_get_args(mrb, "d", &groove_b, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpGrooveJointSetGrooveB(constraint, *groove_b);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::GrooveJoint#anchor_b
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
groove_joint_get_anchor_b(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect anchor_b;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  anchor_b = cpGrooveJointGetAnchorB(constraint);
  return mrb_cp_vect_value(mrb, anchor_b);
}

/*
 * Chipmunk2d::GrooveJoint#anchor_b=(anchor_b)
 * @param [Chipmunk2d::Vect] anchor_b
 */
static mrb_value
groove_joint_set_anchor_b(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect *anchor_b;
  mrb_get_args(mrb, "d", &anchor_b, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpGrooveJointSetAnchorB(constraint, *anchor_b);
  return mrb_nil_value();
}

void
mrb_cp_groove_joint_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_groove_joint_class = mrb_define_class_under(mrb, cp_module, "GrooveJoint", mrb_cp_get_constraint_class());
  MRB_SET_INSTANCE_TT(mrb_cp_groove_joint_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_groove_joint_class, "initialize", groove_joint_initialize,    MRB_ARGS_REQ(5));
  mrb_define_method(mrb, mrb_cp_groove_joint_class, "groove_a",   groove_joint_get_groove_a,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_groove_joint_class, "groove_a=",  groove_joint_set_groove_a,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_groove_joint_class, "groove_b",   groove_joint_get_groove_b,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_groove_joint_class, "groove_b=",  groove_joint_set_groove_b,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_groove_joint_class, "anchor_b",   groove_joint_get_anchor_b,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_groove_joint_class, "anchor_b=",  groove_joint_set_anchor_b,  MRB_ARGS_REQ(1));
}
