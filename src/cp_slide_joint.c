#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_slide_joint.h"
#include "cp_constraint.h"
#include "cp_body.h"
#include "cp_vect.h"

static struct RClass *mrb_cp_slide_joint_class;

/*
 * Chipmunk2d::SlideJoint#initialize(a, b, anchor_a, anchor_b, min, max)
 * @param [Chipmunk2d::Body] a
 * @param [Chipmunk2d::Body] b
 * @param [Chipmunk2d::Vect] anchor_a
 * @param [Chipmunk2d::Vect] anchor_b
 * @param [Float] min
 * @param [Float] max
 */
static mrb_value
slide_joint_initialize(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpBody *a;
  cpBody *b;
  cpVect *anchor_a;
  cpVect *anchor_b;
  mrb_value a_obj;
  mrb_value b_obj;
  mrb_float min;
  mrb_float max;
  mrb_get_args(mrb, "ooddff",
                    &a_obj,
                    &b_obj,
                    &anchor_a, &mrb_cp_vect_type,
                    &anchor_b, &mrb_cp_vect_type,
                    &min,
                    &max);
  a = mrb_data_get_ptr(mrb, a_obj, &mrb_cp_body_type);
  b = mrb_data_get_ptr(mrb, b_obj, &mrb_cp_body_type);
  mrb_cp_constraint_cleanup(mrb, self);
  constraint = cpSlideJointNew(a, b, *anchor_a, *anchor_b, (cpFloat)min, (cpFloat)max);
  mrb_cp_constraint_init_bind(mrb, self, constraint);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body_a"), a_obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body_b"), b_obj);
  return self;
}

/*
 * Chipmunk2d::SlideJoint#anchor_a
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
slide_joint_get_anchor_a(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect anchor_a;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  anchor_a = cpSlideJointGetAnchorA(constraint);
  return mrb_cp_vect_value(mrb, anchor_a);
}

/*
 * Chipmunk2d::SlideJoint#anchor_a=(anchor_a)
 * @param [Chipmunk2d::Vect] anchor_a
 */
static mrb_value
slide_joint_set_anchor_a(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect *anchor_a;
  mrb_get_args(mrb, "d", &anchor_a, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpSlideJointSetAnchorA(constraint, *anchor_a);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::SlideJoint#anchor_b
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
slide_joint_get_anchor_b(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect anchor_b;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  anchor_b = cpSlideJointGetAnchorB(constraint);
  return mrb_cp_vect_value(mrb, anchor_b);
}

/*
 * Chipmunk2d::SlideJoint#anchor_b=(anchor_b)
 * @param [Chipmunk2d::Vect] anchor_b
 */
static mrb_value
slide_joint_set_anchor_b(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect *anchor_b;
  mrb_get_args(mrb, "d", &anchor_b, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpSlideJointSetAnchorB(constraint, *anchor_b);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::SlideJoint#min
 * @return [Float]
 */
static mrb_value
slide_joint_get_min(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat mn;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  mn = cpSlideJointGetMin(constraint);
  return mrb_float_value(mrb, (mrb_float)mn);
}

/*
 * Chipmunk2d::SlideJoint#min=(min)
 * @param [Float] min
 */
static mrb_value
slide_joint_set_min(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat mn;
  mrb_get_args(mrb, "f", &mn);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpSlideJointSetMin(constraint, mn);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::SlideJoint#max
 * @return [Float]
 */
static mrb_value
slide_joint_get_max(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat mx;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  mx = cpSlideJointGetMax(constraint);
  return mrb_float_value(mrb, (mrb_float)mx);
}

/*
 * Chipmunk2d::SlideJoint#max=(max)
 * @param [Float] max
 */
static mrb_value
slide_joint_set_max(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat mx;
  mrb_get_args(mrb, "f", &mx);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpSlideJointSetMax(constraint, mx);
  return mrb_nil_value();
}

void
mrb_cp_slide_joint_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_slide_joint_class = mrb_define_class_under(mrb, cp_module, "SlideJoint", mrb_cp_get_constraint_class());
  MRB_SET_INSTANCE_TT(mrb_cp_slide_joint_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_slide_joint_class, "initialize", slide_joint_initialize,    MRB_ARGS_REQ(6));
  mrb_define_method(mrb, mrb_cp_slide_joint_class, "anchor_a",   slide_joint_get_anchor_a,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_slide_joint_class, "anchor_a=",  slide_joint_set_anchor_a,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_slide_joint_class, "anchor_b",   slide_joint_get_anchor_b,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_slide_joint_class, "anchor_b=",  slide_joint_set_anchor_b,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_slide_joint_class, "min",        slide_joint_get_min,       MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_slide_joint_class, "min=",       slide_joint_set_min,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_slide_joint_class, "max",        slide_joint_get_max,       MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_slide_joint_class, "max=",       slide_joint_set_max,       MRB_ARGS_REQ(1));
}
