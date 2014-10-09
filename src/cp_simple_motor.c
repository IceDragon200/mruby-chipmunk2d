#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_simple_motor.h"

static struct RClass *mrb_cp_simple_motor_class;

void
mrb_cp_simple_motor_free(mrb_state *mrb, void *ptr)
{
  cpSimpleMotor *mrb_cp_simple_motor = ptr;

  if (mrb_cp_simple_motor) {
    mrb_free(mrb, mrb_cp_simple_motor);
  }
}

struct mrb_data_type mrb_cp_simple_motor_type = { "Chipmunk2d::SimpleMotor", mrb_cp_simple_motor_free };

void
mrb_cp_simple_motor_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_simple_motor_class = mrb_define_class_under(mrb, cp_module, "SimpleMotor", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_simple_motor_class, MRB_TT_DATA);
}
