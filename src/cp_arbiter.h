#ifndef MRB_CP_ARBITER_H
#define MRB_CP_ARBITER_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

struct mrb_cp_arbiter_user_data {
  mrb_value arbiter;
  mrb_value space;
};

extern const struct mrb_data_type mrb_cp_arbiter_type;
struct mrb_cp_arbiter_user_data* mrb_cp_arbiter_user_data_new(mrb_state *mrb);
void mrb_cp_arbiter_user_data_free(mrb_state *mrb, struct mrb_cp_arbiter_user_data* ptr);
void mrb_cp_arbiter_init(mrb_state *mrb, struct RClass *cp_module);
mrb_value mrb_cp_arbiter_get_mrb_obj(mrb_state *mrb, const cpArbiter *arbiter);
mrb_value mrb_cp_arbiter_value(mrb_state *mrb, cpArbiter *arbiter);

#endif
