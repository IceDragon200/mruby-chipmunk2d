#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_shape_filter.h"

static struct RClass *mrb_cp_shape_filter_class;

void
mrb_cp_shape_filter_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_shape_filter_class = mrb_define_class_under(mrb, cp_module, "ShapeFilter", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_shape_filter_class, MRB_TT_DATA);
}
