#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_shape_filter.h"

static struct RClass* mrb_cp_shape_filter_class;

static void
mrb_cp_shape_filter_free(mrb_state* mrb, void* ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_shape_filter_type = { "cpShapeFilter", mrb_cp_shape_filter_free };

/*
 * @return [Chipmunk2d::ShapeFilter]
 */
MRB_CP_EXTERN mrb_value
mrb_cp_shape_filter_value(mrb_state* mrb, cpShapeFilter filter)
{
  cpShapeFilter* result_filter;
  mrb_value result;
  result = mrb_obj_new(mrb, mrb_cp_shape_filter_class, 0, NULL);
  result_filter = mrb_cp_get_shape_filter_ptr(mrb, result);

  if (result_filter) {
    mrb_cp_shape_filter_free(mrb, result_filter);
  }

  result_filter = (cpShapeFilter*)mrb_malloc(mrb, sizeof(cpShapeFilter));
  *result_filter = filter;
  mrb_data_init(result, result_filter, &mrb_cp_shape_filter_type);
  return result;
}

/*
 * @overload Chipmunk2d::ShapeFilter#initialize
 * @overload Chipmunk2d::ShapeFilter#initialize(group, catergories, mask)
 *   @param [Integer] group
 *   @param [Integer] catergories
 *   @param [Integer] mask
 * @return [self]
 */
static mrb_value
shape_filter_initialize(mrb_state* mrb, mrb_value self)
{
  cpShapeFilter* filter;
  mrb_int group = CP_NO_GROUP;
  mrb_int categories = CP_ALL_CATEGORIES;
  mrb_int mask = CP_ALL_CATEGORIES;
  mrb_get_args(mrb, "|iii", &group, &categories, &mask);
  filter = (cpShapeFilter*)DATA_PTR(self);

  if (filter) {
    mrb_cp_shape_filter_free(mrb, filter);
  }

  filter = (cpShapeFilter*)mrb_malloc(mrb, sizeof(cpShapeFilter));
  filter->group = (cpGroup)group;
  filter->categories = (cpBitmask)categories;
  filter->mask = (cpBitmask)mask;
  mrb_data_init(self, filter, &mrb_cp_shape_filter_type);
  return self;
}

/*
 * Chipmunk2d::ShapeFilter#group
 * @return [Integer]
 */
static mrb_value
shape_filter_get_group(mrb_state* mrb, mrb_value self)
{
  cpShapeFilter* filter;
  cpGroup group;
  filter = mrb_cp_get_shape_filter_ptr(mrb, self);
  group = filter->group;
  return mrb_fixnum_value((mrb_int)group);
}

/*
 * Chipmunk2d::ShapeFilter#group=(group)
 * @param [Integer] group
 */
static mrb_value
shape_filter_set_group(mrb_state* mrb, mrb_value self)
{
  cpShapeFilter* filter;
  mrb_int group;
  mrb_get_args(mrb, "i", &group);
  filter = mrb_cp_get_shape_filter_ptr(mrb, self);
  filter->group = (cpGroup)group;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::ShapeFilter#catergories
 * @return [Integer]
 */
static mrb_value
shape_filter_get_categories(mrb_state* mrb, mrb_value self)
{
  cpShapeFilter* filter;
  cpBitmask categories;
  filter = mrb_cp_get_shape_filter_ptr(mrb, self);
  categories = filter->categories;
  return mrb_fixnum_value((mrb_int)categories);
}

/*
 * Chipmunk2d::ShapeFilter#catergories=(catergories)
 * @param [Integer] catergories
 */
static mrb_value
shape_filter_set_categories(mrb_state* mrb, mrb_value self)
{
  cpShapeFilter* filter;
  mrb_int categories;
  mrb_get_args(mrb, "i", &categories);
  filter = mrb_cp_get_shape_filter_ptr(mrb, self);
  filter->categories = (cpBitmask)categories;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::ShapeFilter#mask
 * @return [Integer]
 */
static mrb_value
shape_filter_get_mask(mrb_state* mrb, mrb_value self)
{
  cpShapeFilter* filter;
  cpBitmask mask;
  filter = mrb_cp_get_shape_filter_ptr(mrb, self);
  mask = filter->mask;
  return mrb_fixnum_value((mrb_int)mask);
}

/*
 * Chipmunk2d::ShapeFilter#mask=(mask)
 * @param [Integer] mask
 */
static mrb_value
shape_filter_set_mask(mrb_state* mrb, mrb_value self)
{
  cpShapeFilter* filter;
  mrb_int mask;
  mrb_get_args(mrb, "i", &mask);
  filter = mrb_cp_get_shape_filter_ptr(mrb, self);
  filter->mask = (cpBitmask)mask;
  return mrb_nil_value();
}

MRB_CP_EXTERN void
mrb_cp_shape_filter_init(mrb_state* mrb, struct RClass* cp_module)
{
  mrb_cp_shape_filter_class = mrb_define_class_under(mrb, cp_module, "ShapeFilter", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_shape_filter_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_shape_filter_class, "initialize",   shape_filter_initialize,     MRB_ARGS_ARG(0,3));
  mrb_define_method(mrb, mrb_cp_shape_filter_class, "group",        shape_filter_get_group,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_filter_class, "group=",       shape_filter_set_group,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_filter_class, "categories",   shape_filter_get_categories, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_filter_class, "categories=",  shape_filter_set_categories, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_filter_class, "mask",         shape_filter_get_mask,       MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_filter_class, "mask=",        shape_filter_set_mask,       MRB_ARGS_REQ(1));
  mrb_define_const(mrb, mrb_cp_shape_filter_class, "NO_GROUP",       mrb_fixnum_value(CP_NO_GROUP));
  mrb_define_const(mrb, mrb_cp_shape_filter_class, "ALL_CATEGORIES", mrb_fixnum_value(CP_ALL_CATEGORIES));
  mrb_define_const(mrb, mrb_cp_shape_filter_class, "ALL",            mrb_cp_shape_filter_value(mrb, CP_SHAPE_FILTER_ALL));
  mrb_define_const(mrb, mrb_cp_shape_filter_class, "NONE",           mrb_cp_shape_filter_value(mrb, CP_SHAPE_FILTER_NONE));
}
