#ifndef MRB_CP_ARBITER_H
#define MRB_CP_ARBITER_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_common.h"

struct mrb_cp_arbiter_user_data {
  mrb_value arbiter;
  mrb_value space;
};

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_arbiter_type;

static inline cpArbiter*
mrb_cp_get_arbiter_ptr(mrb_state* mrb, mrb_value value)
{
  return (cpArbiter*)mrb_data_get_ptr(mrb, value, &mrb_cp_arbiter_type);
}

MRB_CP_EXTERN void mrb_cp_arbiter_init(mrb_state* mrb, struct RClass* cp_module);
MRB_CP_EXTERN mrb_value mrb_cp_arbiter_get_mrb_obj(mrb_state* mrb, const cpArbiter* arbiter);
MRB_CP_EXTERN mrb_value mrb_cp_arbiter_value(mrb_state* mrb, cpArbiter* arbiter);

#endif
