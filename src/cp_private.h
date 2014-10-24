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

typedef struct mrb_cp_space_user_data {
  mrb_value space;
} mrb_cp_space_user_data;

struct mrb_cp_callback_data {
  mrb_state *mrb;
  mrb_value blk;
};

mrb_cp_constraint_user_data* mrb_cp_constraint_user_data_new(mrb_state *mrb);
void mrb_cp_constraint_user_data_free(mrb_state *mrb, mrb_cp_constraint_user_data* ptr);

mrb_cp_body_user_data* mrb_cp_body_user_data_new(mrb_state *mrb);
void mrb_cp_body_user_data_free(mrb_state *mrb, mrb_cp_body_user_data* ptr);

mrb_cp_shape_user_data* mrb_cp_shape_user_data_new(mrb_state *mrb);
void mrb_cp_shape_user_data_free(mrb_state *mrb, mrb_cp_shape_user_data* ptr);

mrb_cp_space_user_data* mrb_cp_space_user_data_new(mrb_state *mrb);
void mrb_cp_space_user_data_free(mrb_state *mrb, mrb_cp_space_user_data* ptr);

static inline mrb_value
mrb_cp_ary_delete(mrb_state *mrb, mrb_value ary, mrb_value obj)
{
  return mrb_funcall(mrb, ary, "delete", 1, obj);
}

static inline int
mrb_cp_argc(mrb_state *mrb)
{
  return mrb->c->ci->argc;
}
#endif
