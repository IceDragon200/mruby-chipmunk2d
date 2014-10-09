#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_damped_spring.h"

static struct RClass *mrb_cp_damped_spring_class;

void
mrb_cp_damped_spring_free(mrb_state *mrb, void *ptr)
{
  cpDampedSpring *mrb_cp_damped_spring = ptr;

  if (mrb_cp_damped_spring) {
    mrb_free(mrb, mrb_cp_damped_spring);
  }
}

struct mrb_data_type mrb_cp_damped_spring_type = { "Chipmunk2d::DampedSpring", mrb_cp_damped_spring_free };

void
mrb_cp_damped_spring_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_damped_spring_class = mrb_define_class_under(mrb, cp_module, "DampedSpring", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_damped_spring_class, MRB_TT_DATA);
}
