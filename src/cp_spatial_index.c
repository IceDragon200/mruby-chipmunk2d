#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_spatial_index.h"

static struct RClass *mrb_cp_spatial_index_class;

void
mrb_cp_spatial_index_free(mrb_state *mrb, void *ptr)
{
  cpSpatialIndex *mrb_cp_spatial_index = ptr;

  if (mrb_cp_spatial_index) {
    mrb_free(mrb, mrb_cp_spatial_index);
  }
}

struct mrb_data_type mrb_cp_spatial_index_type = { "Chipmunk2d::SpatialIndex", mrb_cp_spatial_index_free };

void
mrb_cp_spatial_index_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_spatial_index_class = mrb_define_class_under(mrb, cp_module, "SpatialIndex", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_spatial_index_class, MRB_TT_DATA);
  /* */
}
