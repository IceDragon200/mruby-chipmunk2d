#ifndef MRB_CP_SPACE_H
#define MRB_CP_SPACE_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_common.h"

typedef struct mrb_cp_space_user_data {
  mrb_value space;
} mrb_cp_space_user_data;

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_space_type;

static inline cpSpace*
mrb_cp_get_space_ptr(mrb_state* mrb, mrb_value value)
{
  return (cpSpace*)mrb_data_get_ptr(mrb, value, &mrb_cp_space_type);
}

MRB_CP_EXTERN mrb_cp_space_user_data* mrb_cp_space_user_data_new(mrb_state* mrb);
MRB_CP_EXTERN void mrb_cp_space_user_data_free(mrb_state* mrb, mrb_cp_space_user_data* ptr);
MRB_CP_EXTERN void mrb_cp_space_init(mrb_state* mrb, struct RClass* cp_module);

#endif
