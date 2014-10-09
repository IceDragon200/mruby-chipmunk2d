#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_groove_joint.h"

static struct RClass *mrb_cp_groove_joint_class;

void
mrb_cp_groove_joint_free(mrb_state *mrb, void *ptr)
{
  cpGrooveJoint *mrb_cp_groove_joint = ptr;

  if (mrb_cp_groove_joint) {
    mrb_free(mrb, mrb_cp_groove_joint);
  }
}

struct mrb_data_type mrb_cp_groove_joint_type = { "Chipmunk2d::GrooveJoint", mrb_cp_groove_joint_free };

void
mrb_cp_groove_joint_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_groove_joint_class = mrb_define_class_under(mrb, cp_module, "GrooveJoint", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_groove_joint_class, MRB_TT_DATA);
}
