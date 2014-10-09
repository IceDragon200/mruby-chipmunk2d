#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_poly_shape.h"

static struct RClass *mrb_cp_poly_shape_class;

void
mrb_cp_poly_shape_free(mrb_state *mrb, void *ptr)
{
  cpPolyShape *mrb_cp_poly_shape = ptr;

  if (mrb_cp_poly_shape) {
    mrb_free(mrb, mrb_cp_poly_shape);
  }
}

struct mrb_data_type mrb_cp_poly_shape_type = { "Chipmunk2d::PolyShape", mrb_cp_poly_shape_free };

void
mrb_cp_poly_shape_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_poly_shape_class = mrb_define_class_under(mrb, cp_module, "PolyShape", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_poly_shape_class, MRB_TT_DATA);
}
