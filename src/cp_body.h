#ifndef MRB_CP_BODY_H
#define MRB_CP_BODY_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

typedef struct mrb_cp_body_user_data {
  mrb_value body;
  mrb_value space;
} mrb_cp_body_user_data;

extern const struct mrb_data_type mrb_cp_body_type;
mrb_cp_body_user_data* mrb_cp_body_user_data_new(mrb_state *mrb);
void mrb_cp_body_user_data_free(mrb_state *mrb, mrb_cp_body_user_data* ptr);
void mrb_cp_body_free(mrb_state *mrb, void *ptr);
void mrb_cp_body_init(mrb_state *mrb, struct RClass *cp_module);
mrb_value mrb_cp_body_value(mrb_state *mrb, cpBody *body);

#endif
