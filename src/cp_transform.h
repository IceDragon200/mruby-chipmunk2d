#ifndef MRB_CP_TRANSFORM_H
#define MRB_CP_TRANSFORM_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_common.h"

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_transform_type;

static inline cpTransform*
mrb_cp_get_transform_ptr(mrb_state* mrb, mrb_value value)
{
  return (cpTransform*)mrb_data_get_ptr(mrb, value, &mrb_cp_transform_type);
}

MRB_CP_EXTERN void mrb_cp_transform_init(mrb_state* mrb, struct RClass* cp_module);
MRB_CP_EXTERN mrb_value mrb_cp_transform_value(mrb_state* mrb, cpTransform transform);

#endif
