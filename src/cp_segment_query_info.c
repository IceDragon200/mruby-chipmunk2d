#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_segment_query_info.h"
#include "cp_shape.h"
#include "cp_vect.h"

static struct RClass* mrb_cp_segment_query_info_class;
static void segment_query_info_set_shape_m(mrb_state* mrb, mrb_value self, mrb_value shape);

static void
mrb_cp_segment_query_info_free(mrb_state* mrb, void* ptr)
{
  cpSegmentQueryInfo* segment_query_info = (cpSegmentQueryInfo*)ptr;

  if (segment_query_info) {
    mrb_free(mrb, segment_query_info);
  }
}

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_segment_query_info_type = { "cpSegmentQueryInfo", mrb_cp_segment_query_info_free };

MRB_CP_EXTERN mrb_value
mrb_cp_segment_query_info_value(mrb_state* mrb, cpSegmentQueryInfo segment_query_info)
{
  cpSegmentQueryInfo* result_segment_query_info;
  mrb_value result;
  result = mrb_obj_new(mrb, mrb_cp_segment_query_info_class, 0, NULL);
  result_segment_query_info = mrb_cp_get_segment_query_info_ptr(mrb, result);
  *result_segment_query_info = segment_query_info;
  return result;
}

static mrb_value
segment_query_info_initialize(mrb_state* mrb, mrb_value self)
{
  cpSegmentQueryInfo* segment_query_info;
  cpVect* point;
  cpVect* normal;
  mrb_float alpha;
  mrb_value shape;
  shape = mrb_nil_value();
  point = NULL;
  normal = NULL;
  alpha = 0.0;
  mrb_get_args(mrb, "|oddf", &shape,
               &point, &mrb_cp_vect_type,
               &normal, &mrb_cp_vect_type,
               &alpha);
  segment_query_info = (cpSegmentQueryInfo*)DATA_PTR(self);

  if (segment_query_info) {
    mrb_cp_segment_query_info_free(mrb, segment_query_info);
  }

  segment_query_info = (cpSegmentQueryInfo*)mrb_malloc(mrb, sizeof(cpSegmentQueryInfo));
  segment_query_info_set_shape_m(mrb, self, shape);

  if (point) {
    segment_query_info->point = *point;
  }

  if (normal) {
    segment_query_info->normal = *normal;
  }

  segment_query_info->alpha = alpha;
  mrb_data_init(self, segment_query_info, &mrb_cp_segment_query_info_type);
  return self;
}

static void
segment_query_info_set_shape_m(mrb_state* mrb, mrb_value self, mrb_value shape)
{
  cpSegmentQueryInfo* segment_query_info;
  cpShape* shape_ptr;
  mrb_sym shape_sym;
  shape_ptr = NULL;

  if (!mrb_nil_p(shape)) {
    shape_ptr = mrb_cp_get_shape_ptr(mrb, shape);
  }

  segment_query_info = mrb_cp_get_segment_query_info_ptr(mrb, self);
  segment_query_info->shape = shape_ptr;
  shape_sym = mrb_intern_lit(mrb, "shape");
  mrb_iv_set(mrb, self, shape_sym, shape);
}

static mrb_value
segment_query_info_get_shape(mrb_state* mrb, mrb_value self)
{
  mrb_sym shape_sym;
  shape_sym = mrb_intern_lit(mrb, "shape");
  return mrb_iv_get(mrb, self, shape_sym);
}

static mrb_value
segment_query_info_set_shape(mrb_state* mrb, mrb_value self)
{
  mrb_value shape;
  mrb_get_args(mrb, "o", &shape);
  segment_query_info_set_shape_m(mrb, self, shape);
  return mrb_nil_value();
}

static mrb_value
segment_query_info_get_point(mrb_state* mrb, mrb_value self)
{
  cpSegmentQueryInfo* segment_query_info;
  cpVect point;
  segment_query_info = mrb_cp_get_segment_query_info_ptr(mrb, self);
  point = segment_query_info->point;
  return mrb_cp_vect_value(mrb, point);
}

static mrb_value
segment_query_info_set_point(mrb_state* mrb, mrb_value self)
{
  cpSegmentQueryInfo* segment_query_info;
  cpVect* point;
  mrb_get_args(mrb, "d", &point, &mrb_cp_vect_type);
  segment_query_info = mrb_cp_get_segment_query_info_ptr(mrb, self);
  segment_query_info->point = *point;
  return mrb_nil_value();
}

static mrb_value
segment_query_info_get_normal(mrb_state* mrb, mrb_value self)
{
  cpSegmentQueryInfo* segment_query_info;
  cpVect normal;
  segment_query_info = mrb_cp_get_segment_query_info_ptr(mrb, self);
  normal = segment_query_info->normal;
  return mrb_cp_vect_value(mrb, normal);
}

static mrb_value
segment_query_info_set_normal(mrb_state* mrb, mrb_value self)
{
  cpSegmentQueryInfo* segment_query_info;
  cpVect* normal;
  mrb_get_args(mrb, "d", &normal, &mrb_cp_vect_type);
  segment_query_info = mrb_cp_get_segment_query_info_ptr(mrb, self);
  segment_query_info->normal = *normal;
  return mrb_nil_value();
}

static mrb_value
segment_query_info_get_alpha(mrb_state* mrb, mrb_value self)
{
  cpSegmentQueryInfo* segment_query_info;
  cpFloat alpha;
  segment_query_info = mrb_cp_get_segment_query_info_ptr(mrb, self);
  alpha = segment_query_info->alpha;
  return mrb_float_value(mrb, (mrb_float)alpha);
}

static mrb_value
segment_query_info_set_alpha(mrb_state* mrb, mrb_value self)
{
  cpSegmentQueryInfo* segment_query_info;
  mrb_float alpha;
  mrb_get_args(mrb, "f", &alpha);
  segment_query_info = mrb_cp_get_segment_query_info_ptr(mrb, self);
  segment_query_info->alpha = (cpFloat)alpha;
  return mrb_nil_value();
}

MRB_CP_EXTERN void
mrb_cp_segment_query_info_init(mrb_state* mrb, struct RClass* cp_module)
{
  mrb_cp_segment_query_info_class = mrb_define_class_under(mrb, cp_module, "SegmentQueryInfo", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_segment_query_info_class, MRB_TT_DATA);
  mrb_define_method(mrb, mrb_cp_segment_query_info_class, "initialize", segment_query_info_initialize, MRB_ARGS_ARG(0,4));
  mrb_define_method(mrb, mrb_cp_segment_query_info_class, "shape",   segment_query_info_get_shape,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_segment_query_info_class, "shape=",  segment_query_info_set_shape,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_segment_query_info_class, "point",   segment_query_info_get_point,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_segment_query_info_class, "point=",  segment_query_info_set_point,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_segment_query_info_class, "normal",  segment_query_info_get_normal, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_segment_query_info_class, "normal=", segment_query_info_set_normal, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_segment_query_info_class, "alpha",   segment_query_info_get_alpha,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_segment_query_info_class, "alpha=",  segment_query_info_set_alpha,  MRB_ARGS_REQ(1));
}
