#ifndef MRB_CP_MAT2x2_H
#define MRB_CP_MAT2x2_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

void mrb_cp_mat2x2_free(mrb_state *mrb, void *ptr);

struct mrb_data_type mrb_cp_mat2x2_type;

void mrb_cp_mat2x2_init(mrb_state *mrb, struct RClass *cp_module);

#endif
