#ifndef MRB_CP_SHAPE_FILTER_H
#define MRB_CP_SHAPE_FILTER_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

void mrb_cp_shape_filter_free(mrb_state *mrb, void *ptr);
extern const struct mrb_data_type mrb_cp_shape_filter_type;
void mrb_cp_shape_filter_init(mrb_state *mrb, struct RClass *cp_module);
mrb_value mrb_cp_shape_filter_value(mrb_state *mrb, cpShapeFilter filter);

#endif
