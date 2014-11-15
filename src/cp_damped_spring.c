#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_damped_spring.h"
#include "cp_constraint.h"
#include "cp_body.h"
#include "cp_vect.h"

static struct RClass *mrb_cp_damped_spring_class;

/*
 * Chipmunk2d::DampedSpring#initialize
 * @param [Chipmunk2d::Body] a
 * @param [Chipmunk2d::Body] b
 * @param [Chipmunk2d::Vect] anchor_a
 * @param [Chipmunk2d::Vect] anchor_b
 * @param [Float] rest_length
 * @param [Float] stiffness
 * @param [Float] damping
 */
static mrb_value
damped_spring_initialize(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpBody *a;
  cpBody *b;
  cpVect *anchor_a;
  cpVect *anchor_b;
  mrb_value a_obj;
  mrb_value b_obj;
  mrb_float rest_length;
  mrb_float stiffness;
  mrb_float damping;
  mrb_get_args(mrb, "ooddfff", &a_obj,
                               &b_obj,
                               &anchor_a, &mrb_cp_vect_type,
                               &anchor_b, &mrb_cp_vect_type,
                               &rest_length,
                               &stiffness,
                               &damping);
  a = mrb_data_get_ptr(mrb, a_obj, &mrb_cp_body_type);
  b = mrb_data_get_ptr(mrb, b_obj, &mrb_cp_body_type);
  mrb_cp_constraint_cleanup(mrb, self);
  constraint = cpDampedSpringNew(a, b, *anchor_a, *anchor_b, (cpFloat)rest_length, (cpFloat)stiffness, (cpFloat)damping);
  mrb_cp_constraint_init_bind(mrb, self, constraint);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body_a"), a_obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body_b"), b_obj);
  return self;
}

/*
 * Chipmunk2d::DampedSpring#anchor_a
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
damped_spring_get_anchor_a(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect anchor_a;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  anchor_a = cpDampedSpringGetAnchorA(constraint);
  return mrb_cp_vect_value(mrb, anchor_a);
}

/*
 * Chipmunk2d::DampedSpring#anchor_a=(anchor_a)
 * @param [Chipmunk2d::Vect] anchor_a
 */
static mrb_value
damped_spring_set_anchor_a(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect *anchor_a;
  mrb_get_args(mrb, "d", &anchor_a, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpDampedSpringSetAnchorA(constraint, *anchor_a);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::DampedSpring#anchor_b
 * @return [Chipmunk::Vect]
 */
static mrb_value
damped_spring_get_anchor_b(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect anchor_b;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  anchor_b = cpDampedSpringGetAnchorB(constraint);
  return mrb_cp_vect_value(mrb, anchor_b);
}

/*
 * Chipmunk2d::DampedSpring#anchor_b=(anchor_b)
 * @param [Chipmunk2d::Vect] anchor_b
 */
static mrb_value
damped_spring_set_anchor_b(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpVect *anchor_b;
  mrb_get_args(mrb, "d", &anchor_b, &mrb_cp_vect_type);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpDampedSpringSetAnchorB(constraint, *anchor_b);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::DampedSpring#rest_length
 * @return [Float]
 */
static mrb_value
damped_spring_get_rest_length(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat rest_length;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  rest_length = cpDampedSpringGetRestLength(constraint);
  return mrb_float_value(mrb, (mrb_float)rest_length);
}

/*
 * Chipmunk2d::DampedSpring#rest_length=(rest_length)
 * @param [Float] rest_length
 */
static mrb_value
damped_spring_set_rest_length(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat rest_length;
  mrb_get_args(mrb, "f", &rest_length);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpDampedSpringSetRestLength(constraint, rest_length);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::DampedSpring#stiffness
 * @return [Float]
 */
static mrb_value
damped_spring_get_stiffness(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat stiffness;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  stiffness = cpDampedSpringGetStiffness(constraint);
  return mrb_float_value(mrb, (mrb_float)stiffness);
}

/*
 * Chipmunk2d::DampedSpring#stiffness=(stiffness)
 * @param [Float] stiffness
 */
static mrb_value
damped_spring_set_stiffness(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat stiffness;
  mrb_get_args(mrb, "f", &stiffness);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpDampedSpringSetStiffness(constraint, stiffness);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::DampedSpring#damping
 * @return [Float]
 */
static mrb_value
damped_spring_get_damping(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat damping;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  damping = cpDampedSpringGetDamping(constraint);
  return mrb_float_value(mrb, (mrb_float)damping);
}

/*
 * Chipmunk2d::DampedSpring#damping=(damping)
 * @param [Float] damping
 */
static mrb_value
damped_spring_set_damping(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat damping;
  mrb_get_args(mrb, "f", &damping);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpDampedSpringSetDamping(constraint, damping);
  return mrb_nil_value();
}

void
mrb_cp_damped_spring_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_damped_spring_class = mrb_define_class_under(mrb, cp_module, "DampedSpring", mrb_cp_get_constraint_class());
  MRB_SET_INSTANCE_TT(mrb_cp_damped_spring_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "initialize",   damped_spring_initialize,      MRB_ARGS_REQ(7));
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "anchor_a",     damped_spring_get_anchor_a,    MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "anchor_a=",    damped_spring_set_anchor_a,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "anchor_b",     damped_spring_get_anchor_b,    MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "anchor_b=",    damped_spring_set_anchor_b,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "rest_length",  damped_spring_get_rest_length, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "rest_length=", damped_spring_set_rest_length, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "stiffness",    damped_spring_get_stiffness,   MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "stiffness=",   damped_spring_set_stiffness,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "damping",      damped_spring_get_damping,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_damped_spring_class, "damping=",     damped_spring_set_damping,     MRB_ARGS_REQ(1));
}
