#ifndef MRB_CP_CONSTRAINT_H
#define MRB_CP_CONSTRAINT_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

struct mrb_data_type mrb_cp_constraint_type;
struct RClass* mrb_cp_get_constraint_class();
void mrb_cp_constraint_free(mrb_state *mrb, void *ptr);
void mrb_cp_constraint_init(mrb_state *mrb, struct RClass *cp_module);
void mrb_cp_constraint_cleanup(mrb_state *mrb, mrb_value self);
void mrb_cp_constraint_init_bind(mrb_state *mrb, mrb_value self, cpConstraint *constraint);

#endif
