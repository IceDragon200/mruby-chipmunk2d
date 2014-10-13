#ifndef MRB_CP_ARBITER_H
#define MRB_CP_ARBITER_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

void mrb_cp_arbiter_init(mrb_state *mrb, struct RClass *cp_module);

struct mrb_data_type mrb_cp_arbiter_type;

void mrb_cp_arbiter_init(mrb_state *mrb, struct RClass *cp_module);

#endif
