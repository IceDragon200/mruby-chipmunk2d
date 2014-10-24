#ifndef MRB_CP_BB_H
#define MRB_CP_BB_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

struct mrb_data_type mrb_cp_bb_type;
void mrb_cp_bb_free(mrb_state *mrb, void *ptr);
void mrb_cp_bb_init(mrb_state *mrb, struct RClass *cp_module);
mrb_value mrb_cp_bb_value(mrb_state *mrb, cpBB bb);

#endif
