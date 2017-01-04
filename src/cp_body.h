#ifndef MRB_CP_BODY_H
#define MRB_CP_BODY_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_common.h"

typedef struct mrb_cp_body_user_data {
  mrb_value body;
  mrb_value space;
} mrb_cp_body_user_data;

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_body_type;

static inline cpBody*
mrb_cp_get_body_ptr(mrb_state* mrb, mrb_value value)
{
  return (cpBody*)mrb_data_get_ptr(mrb, value, &mrb_cp_body_type);
}

MRB_CP_EXTERN mrb_cp_body_user_data* mrb_cp_body_user_data_new(mrb_state* mrb);
MRB_CP_EXTERN void mrb_cp_body_init(mrb_state* mrb, struct RClass* cp_module);
MRB_CP_EXTERN mrb_value mrb_cp_body_value(mrb_state* mrb, cpBody* body);

#endif
