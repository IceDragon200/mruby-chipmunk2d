#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_pin_joint.h"

static struct RClass *mrb_cp_pin_joint_class;

void
mrb_cp_pin_joint_free(mrb_state *mrb, void *ptr)
{
  cpPinJoint *mrb_cp_pin_joint = ptr;

  if (mrb_cp_pin_joint) {
    mrb_free(mrb, mrb_cp_pin_joint);
  }
}

struct mrb_data_type mrb_cp_pin_joint_type = { "Chipmunk2d::PinJoint", mrb_cp_pin_joint_free };

void
mrb_cp_pin_joint_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_pin_joint_class = mrb_define_class_under(mrb, cp_module, "PinJoint", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_pin_joint_class, MRB_TT_DATA);
}
