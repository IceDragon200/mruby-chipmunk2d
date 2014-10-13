#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_shape.h"
#include "cp_private.h"

static struct RClass *mrb_cp_shape_class;

void
mrb_cp_shape_free(mrb_state *mrb, void *ptr)
{
  cpShape *mrb_cp_shape = ptr;

  if (mrb_cp_shape) {
    cpShapeFree(mrb_cp_shape);
  }
}

struct mrb_data_type mrb_cp_shape_type = { "Chipmunk2d::Shape", mrb_cp_shape_free };

struct RClass*
mrb_cp_get_shape_class()
{
  return mrb_cp_shape_class;
}

void
mrb_cp_shape_cleanup(mrb_state *mrb, mrb_value self)
{
  cpShape *shape;
  shape = (cpShape*)DATA_PTR(self);
  if (shape) {
    mrb_cp_shape_free(mrb, shape);
  }
}

void
mrb_cp_shape_init_bind(mrb_state *mrb, mrb_value self, cpShape *shape)
{
  mrb_cp_shape_user_data *user_data;
  user_data = mrb_cp_shape_user_data_new(mrb);
  user_data->shape = self;
  cpShapeSetUserData(shape, user_data);
  mrb_data_init(self, shape, &mrb_cp_shape_type);
}

void
mrb_cp_shape_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_shape_class = mrb_define_class_under(mrb, cp_module, "Shape", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_shape_class, MRB_TT_DATA);
}
