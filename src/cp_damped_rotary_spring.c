#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_damped_rotary_spring.h"
#include "cp_constraint.h"
#include "cp_body.h"

static struct RClass *mrb_cp_damped_rotary_spring_class;

/*
 * @param [Chipmunk2d::Body] a
 * @param [Chipmunk2d::Body] b
 * @param [Float] rest_angle
 * @param [Float] stiffness
 * @param [Float] damping
 */
static mrb_value
damped_rotary_spring_initialize(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpBody *a;
  cpBody *b;
  mrb_value a_obj;
  mrb_value b_obj;
  mrb_float rest_angle;
  mrb_float stiffness;
  mrb_float damping;
  mrb_get_args(mrb, "oofff", &a_obj, &b_obj, &rest_angle, &stiffness, &damping);
  a = mrb_data_get_ptr(mrb, a_obj, &mrb_cp_body_type);
  b = mrb_data_get_ptr(mrb, b_obj, &mrb_cp_body_type);
  mrb_cp_constraint_cleanup(mrb, self);
  constraint = cpDampedRotarySpringNew(a, b, (cpFloat)rest_angle, (cpFloat)stiffness, (cpFloat)damping);
  mrb_cp_constraint_init_bind(mrb, self, constraint);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body_a"), a_obj);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body_b"), b_obj);
  return self;
}

static mrb_value
damped_rotary_spring_get_rest_angle(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat rest_angle;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  rest_angle = cpDampedRotarySpringGetRestAngle(constraint);
  return mrb_float_value(mrb, (mrb_float)rest_angle);
}

static mrb_value
damped_rotary_spring_set_rest_angle(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat rest_angle;
  mrb_get_args(mrb, "f", &rest_angle);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpDampedRotarySpringSetRestAngle(constraint, rest_angle);
  return mrb_nil_value();
}

static mrb_value
damped_rotary_spring_get_stiffness(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat stiffness;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  stiffness = cpDampedRotarySpringGetStiffness(constraint);
  return mrb_float_value(mrb, (mrb_float)stiffness);
}

static mrb_value
damped_rotary_spring_set_stiffness(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat stiffness;
  mrb_get_args(mrb, "f", &stiffness);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpDampedRotarySpringSetStiffness(constraint, stiffness);
  return mrb_nil_value();
}

static mrb_value
damped_rotary_spring_get_damping(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat damping;
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  damping = cpDampedRotarySpringGetDamping(constraint);
  return mrb_float_value(mrb, (mrb_float)damping);
}

static mrb_value
damped_rotary_spring_set_damping(mrb_state *mrb, mrb_value self)
{
  cpConstraint *constraint;
  cpFloat damping;
  mrb_get_args(mrb, "f", &damping);
  Data_Get_Struct(mrb, self, &mrb_cp_constraint_type, constraint);
  cpDampedRotarySpringSetDamping(constraint, damping);
  return mrb_nil_value();
}

void
mrb_cp_damped_rotary_spring_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_damped_rotary_spring_class = mrb_define_class_under(mrb, cp_module, "DampedRotarySpring", mrb_cp_get_constraint_class());
  MRB_SET_INSTANCE_TT(mrb_cp_damped_rotary_spring_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_damped_rotary_spring_class, "initialize",  damped_rotary_spring_initialize,     MRB_ARGS_REQ(5));
  mrb_define_method(mrb, mrb_cp_damped_rotary_spring_class, "rest_angle",  damped_rotary_spring_get_rest_angle, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_damped_rotary_spring_class, "rest_angle=", damped_rotary_spring_set_rest_angle, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_damped_rotary_spring_class, "stiffness",   damped_rotary_spring_get_stiffness,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_damped_rotary_spring_class, "stiffness=",  damped_rotary_spring_set_stiffness,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_damped_rotary_spring_class, "damping",     damped_rotary_spring_get_damping,    MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_damped_rotary_spring_class, "damping=",    damped_rotary_spring_set_damping,    MRB_ARGS_REQ(1));
}
