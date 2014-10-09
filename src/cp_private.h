#ifndef MRB_CP_PRIVATE_H
#define MRB_CP_PRIVATE_H

#include <mruby.h>
#include <mruby/value.h>
#include <chipmunk/chipmunk.h>

/* Since its difficult to keep track of the Chipmunk objects, its an idea
 * to keep the object hitchhiking on the Chipmunk object through its userdata.
 */
typedef struct mrb_cp_constraint_user_data {
  mrb_value constraint;
  mrb_value space;
} mrb_cp_constraint_user_data;

typedef struct mrb_cp_body_user_data {
  mrb_value body;
  mrb_value space;
} mrb_cp_body_user_data;

typedef struct mrb_cp_shape_user_data {
  mrb_value shape;
  mrb_value space;
} mrb_cp_shape_user_data;

mrb_cp_constraint_user_data* mrb_cp_constraint_user_data_new(mrb_state *mrb);
void mrb_cp_constraint_user_data_free(mrb_state *mrb, mrb_cp_constraint_user_data* ptr);
void mrb_cp_constraint_user_data_mark(mrb_state *mrb, mrb_cp_constraint_user_data* ptr);

mrb_cp_body_user_data* mrb_cp_body_user_data_new(mrb_state *mrb);
void mrb_cp_body_user_data_free(mrb_state *mrb, mrb_cp_body_user_data* ptr);
void mrb_cp_body_user_data_mark(mrb_state *mrb, mrb_cp_body_user_data* ptr);

mrb_cp_shape_user_data* mrb_cp_shape_user_data_new(mrb_state *mrb);
void mrb_cp_shape_user_data_free(mrb_state *mrb, mrb_cp_shape_user_data* ptr);
void mrb_cp_shape_user_data_mark(mrb_state *mrb, mrb_cp_shape_user_data* ptr);

#endif
