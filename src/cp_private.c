#include <mruby.h>
#include <mruby/value.h>
#include "cp_private.h"

mrb_cp_constraint_user_data*
mrb_cp_constraint_user_data_new(mrb_state *mrb)
{
  mrb_cp_constraint_user_data *user_data =
    mrb_malloc(mrb, sizeof(mrb_cp_constraint_user_data));

  user_data->constraint = mrb_nil_value();
  user_data->space = mrb_nil_value();

  return user_data;
}

void
mrb_cp_constraint_user_data_free(mrb_state *mrb, mrb_cp_constraint_user_data *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

void
mrb_cp_constraint_user_data_mark(mrb_state *mrb, mrb_cp_constraint_user_data *ptr)
{
  if (!mrb_nil_p(ptr->space)) {
    mrb_gc_mark_value(mrb, ptr->space);
  }
}

mrb_cp_body_user_data*
mrb_cp_body_user_data_new(mrb_state *mrb)
{
  mrb_cp_body_user_data *user_data =
    mrb_malloc(mrb, sizeof(mrb_cp_body_user_data));

  user_data->body = mrb_nil_value();
  user_data->space = mrb_nil_value();

  return user_data;
}

void
mrb_cp_body_user_data_free(mrb_state *mrb, mrb_cp_body_user_data *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

void
mrb_cp_body_user_data_mark(mrb_state *mrb, mrb_cp_body_user_data *ptr)
{
  if (!mrb_nil_p(ptr->space)) {
    mrb_gc_mark_value(mrb, ptr->space);
  }
}

mrb_cp_shape_user_data*
mrb_cp_shape_user_data_new(mrb_state *mrb)
{
  mrb_cp_shape_user_data *user_data =
    mrb_malloc(mrb, sizeof(mrb_cp_shape_user_data));

  user_data->shape = mrb_nil_value();
  user_data->space = mrb_nil_value();

  return user_data;
}

void
mrb_cp_shape_user_data_free(mrb_state *mrb, mrb_cp_shape_user_data *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

void
mrb_cp_shape_user_data_mark(mrb_state *mrb, mrb_cp_shape_user_data *ptr)
{
  if (!mrb_nil_p(ptr->space)) {
    mrb_gc_mark_value(mrb, ptr->space);
  }
}
