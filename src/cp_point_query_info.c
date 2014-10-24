#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_point_query_info.h"
#include "cp_shape.h"
#include "cp_vect.h"

static struct RClass *mrb_cp_point_query_info_class;
static void point_query_info_set_shape_m(mrb_state *mrb, mrb_value self, mrb_value shape);

void
mrb_cp_point_query_info_free(mrb_state *mrb, void *ptr)
{
  cpPointQueryInfo *point_query_info;
  point_query_info = ptr;
  if (point_query_info) {
    mrb_free(mrb, point_query_info);
  }
}

struct mrb_data_type mrb_cp_point_query_info_type = { "Chipmunk2d::PointQueryInfo", mrb_cp_point_query_info_free };

void
mrb_cp_point_query_info_reverse_refresh(mrb_state *mrb, mrb_value self)
{
  cpPointQueryInfo *point_query_info;
  mrb_value shape_obj;
  point_query_info = mrb_data_get_ptr(mrb, self, &mrb_cp_point_query_info_type);
  if (point_query_info->shape) {
    shape_obj = mrb_cp_shape_get_mrb_obj(mrb, point_query_info->shape);
    point_query_info_set_shape_m(mrb, self, shape_obj);
  } else {
    point_query_info_set_shape_m(mrb, self, mrb_nil_value());
  }
}

mrb_value
mrb_cp_point_query_info_value(mrb_state *mrb, cpPointQueryInfo point_query_info)
{
  cpPointQueryInfo *result_point_query_info;
  mrb_value result;
  result = mrb_obj_new(mrb, mrb_cp_point_query_info_class, 0, NULL);
  result_point_query_info = mrb_data_get_ptr(mrb, result, &mrb_cp_point_query_info_type);
  *result_point_query_info = point_query_info;
  return result;
}

static mrb_value
point_query_info_initialize(mrb_state *mrb, mrb_value self)
{
  cpPointQueryInfo *point_query_info;
  cpVect *point;
  cpVect *gradient;
  mrb_float distance;
  mrb_value shape;
  shape = mrb_nil_value();
  point = NULL;
  gradient = NULL;
  distance = 0.0;
  mrb_get_args(mrb, "|odfd", &shape,
                             &point, &mrb_cp_vect_type,
                             &distance,
                             &gradient, &mrb_cp_vect_type);
  point_query_info = DATA_PTR(self);
  if (point_query_info) {
    mrb_cp_point_query_info_free(mrb, point_query_info);
  }
  point_query_info = mrb_malloc(mrb, sizeof(cpPointQueryInfo));
  point_query_info_set_shape_m(mrb, self, shape);
  if (point)
    point_query_info->point = *point;
  point_query_info->distance = distance;
  if (gradient)
    point_query_info->gradient = *gradient;
  mrb_data_init(self, point_query_info, &mrb_cp_point_query_info_type);
  return self;
}

static void
point_query_info_set_shape_m(mrb_state *mrb, mrb_value self, mrb_value shape)
{
  cpPointQueryInfo *point_query_info;
  cpShape *shape_ptr;
  mrb_sym shape_sym;
  shape_ptr = NULL;
  if (!mrb_nil_p(shape)) {
    shape_ptr = mrb_data_get_ptr(mrb, shape, &mrb_cp_shape_type);
  }
  point_query_info = mrb_data_get_ptr(mrb, self, &mrb_cp_point_query_info_type);
  point_query_info->shape = shape_ptr;
  shape_sym = mrb_intern_cstr(mrb, "shape");
  mrb_iv_set(mrb, self, shape_sym, shape);
}

static mrb_value
point_query_info_get_shape(mrb_state *mrb, mrb_value self)
{
  mrb_sym shape_sym;
  shape_sym = mrb_intern_cstr(mrb, "shape");
  return mrb_iv_get(mrb, self, shape_sym);
}

static mrb_value
point_query_info_set_shape(mrb_state *mrb, mrb_value self)
{
  mrb_value shape;
  mrb_get_args(mrb, "o", &shape);
  point_query_info_set_shape_m(mrb, self, shape);
  return mrb_nil_value();
}

static mrb_value
point_query_info_get_point(mrb_state *mrb, mrb_value self)
{
  cpPointQueryInfo *point_query_info;
  cpVect point;
  point_query_info = mrb_data_get_ptr(mrb, self, &mrb_cp_point_query_info_type);
  point = point_query_info->point;
  return mrb_cp_vect_value(mrb, point);
}

static mrb_value
point_query_info_set_point(mrb_state *mrb, mrb_value self)
{
  cpPointQueryInfo *point_query_info;
  cpVect *point;
  mrb_get_args(mrb, "d", &point, &mrb_cp_vect_type);
  point_query_info = mrb_data_get_ptr(mrb, self, &mrb_cp_point_query_info_type);
  point_query_info->point = *point;
  return mrb_nil_value();
}

static mrb_value
point_query_info_get_gradient(mrb_state *mrb, mrb_value self)
{
  cpPointQueryInfo *point_query_info;
  cpVect gradient;
  point_query_info = mrb_data_get_ptr(mrb, self, &mrb_cp_point_query_info_type);
  gradient = point_query_info->gradient;
  return mrb_cp_vect_value(mrb, gradient);
}

static mrb_value
point_query_info_set_gradient(mrb_state *mrb, mrb_value self)
{
  cpPointQueryInfo *point_query_info;
  cpVect *gradient;
  mrb_get_args(mrb, "d", &gradient, &mrb_cp_vect_type);
  point_query_info = mrb_data_get_ptr(mrb, self, &mrb_cp_point_query_info_type);
  point_query_info->gradient = *gradient;
  return mrb_nil_value();
}

static mrb_value
point_query_info_get_distance(mrb_state *mrb, mrb_value self)
{
  cpPointQueryInfo *point_query_info;
  cpFloat distance;
  point_query_info = mrb_data_get_ptr(mrb, self, &mrb_cp_point_query_info_type);
  distance = point_query_info->distance;
  return mrb_float_value(mrb, (mrb_float)distance);
}

static mrb_value
point_query_info_set_distance(mrb_state *mrb, mrb_value self)
{
  cpPointQueryInfo *point_query_info;
  cpFloat distance;
  mrb_get_args(mrb, "f", &distance);
  point_query_info = mrb_data_get_ptr(mrb, self, &mrb_cp_point_query_info_type);
  point_query_info->distance = distance;
  return mrb_nil_value();
}

void
mrb_cp_point_query_info_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_point_query_info_class = mrb_define_class_under(mrb, cp_module, "PointQueryInfo", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_point_query_info_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_point_query_info_class, "initialize", point_query_info_initialize,   MRB_ARGS_ARG(0,4));
  mrb_define_method(mrb, mrb_cp_point_query_info_class, "shape",      point_query_info_get_shape,    MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_point_query_info_class, "shape=",     point_query_info_set_shape,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_point_query_info_class, "point",      point_query_info_get_point,    MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_point_query_info_class, "point=",     point_query_info_set_point,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_point_query_info_class, "distance",   point_query_info_get_distance, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_point_query_info_class, "distance=",  point_query_info_set_distance, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_point_query_info_class, "gradient",   point_query_info_get_gradient, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_point_query_info_class, "gradient=",  point_query_info_set_gradient, MRB_ARGS_REQ(1));
}
