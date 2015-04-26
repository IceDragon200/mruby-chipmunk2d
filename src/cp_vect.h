#ifndef MRB_CP_VECT_H
#define MRB_CP_VECT_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

void mrb_cp_vect_free(mrb_state *mrb, void *ptr);
extern const struct mrb_data_type mrb_cp_vect_type;
mrb_value mrb_cp_vect_value(mrb_state *mrb, cpVect vect);
void mrb_cp_vect_init(mrb_state *mrb, struct RClass *cp_module);

#endif
