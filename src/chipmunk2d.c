#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>

#include "cp_arbiter.h"
#include "cp_bb.h"
#include "cp_body.h"
#include "cp_constraint.h"
#include "cp_contact_point.h"
#include "cp_damped_rotary_spring.h"
#include "cp_damped_spring.h"
#include "cp_gear_joint.h"
#include "cp_groove_joint.h"
#include "cp_mat2x2.h"
#include "cp_pin_joint.h"
#include "cp_pivot_joint.h"
#include "cp_poly_shape.h"
#include "cp_ratchet_joint.h"
#include "cp_rotary_limit_joint.h"
#include "cp_segment_query_info.h"
#include "cp_shape.h"
#include "cp_shape_filter.h"
#include "cp_simple_motor.h"
#include "cp_slide_joint.h"
#include "cp_space.h"
#include "cp_spatial_index.h"
#include "cp_transform.h"
#include "cp_vect.h"

void
mrb_mruby_chipmunk2d_gem_init(mrb_state* mrb)
{
  struct RClass *cp_module;
  cp_module = mrb_define_module(mrb, "Chipmunk2d");

  mrb_cp_transform_init(mrb, cp_module);
  mrb_cp_vect_init(mrb, cp_module);
  mrb_cp_mat2x2_init(mrb, cp_module);
  mrb_cp_contact_point_init(mrb, cp_module);
  mrb_cp_segment_query_info_init(mrb, cp_module);
  mrb_cp_bb_init(mrb, cp_module);
  mrb_cp_arbiter_init(mrb, cp_module);
  mrb_cp_body_init(mrb, cp_module);
  mrb_cp_shape_filter_init(mrb, cp_module);
  mrb_cp_shape_init(mrb, cp_module);
  mrb_cp_poly_shape_init(mrb, cp_module);
  mrb_cp_space_init(mrb, cp_module);
  mrb_cp_spatial_index_init(mrb, cp_module);
  mrb_cp_constraint_init(mrb, cp_module);
  mrb_cp_damped_rotary_spring_init(mrb, cp_module);
  mrb_cp_damped_spring_init(mrb, cp_module);
  mrb_cp_gear_joint_init(mrb, cp_module);
  mrb_cp_groove_joint_init(mrb, cp_module);
  mrb_cp_pin_joint_init(mrb, cp_module);
  mrb_cp_pivot_joint_init(mrb, cp_module);
  mrb_cp_ratchet_joint_init(mrb, cp_module);
  mrb_cp_rotary_limit_joint_init(mrb, cp_module);
  mrb_cp_simple_motor_init(mrb, cp_module);
  mrb_cp_slide_joint_init(mrb, cp_module);
}

void
mrb_mruby_chipmunk2d_gem_final(mrb_state* mrb)
{
  //
}
