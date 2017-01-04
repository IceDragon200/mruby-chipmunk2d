#ifndef MRB_CP_MAT2x2_H
#define MRB_CP_MAT2x2_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_common.h"

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_mat2x2_type;

static inline cpMat2x2*
mrb_cp_get_mat2x2_ptr(mrb_state* mrb, mrb_value value)
{
  return (cpMat2x2*)mrb_data_get_ptr(mrb, value, &mrb_cp_mat2x2_type);
}

MRB_CP_EXTERN void mrb_cp_mat2x2_init(mrb_state* mrb, struct RClass* cp_module);

#endif
