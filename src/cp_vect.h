#ifndef MRB_CP_VECT_H
#define MRB_CP_VECT_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_common.h"

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_vect_type;

static inline cpVect*
mrb_cp_get_vect_ptr(mrb_state* mrb, mrb_value value)
{
  return (cpVect*)mrb_data_get_ptr(mrb, value, &mrb_cp_vect_type);
}

MRB_CP_EXTERN mrb_value mrb_cp_vect_value(mrb_state* mrb, cpVect vect);
MRB_CP_EXTERN void mrb_cp_vect_init(mrb_state* mrb, struct RClass* cp_module);

#endif
