#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_mat2x2.h"
#include "cp_vect.h"

static struct RClass *mrb_cp_mat2x2_class;

void
mrb_cp_mat2x2_free(mrb_state *mrb, void *ptr)
{
  cpMat2x2 *mat2x2 = ptr;
  if (mat2x2) {
    mrb_free(mrb, mat2x2);
  }
}

struct mrb_data_type mrb_cp_mat2x2_type = { "Chipmunk2d::Mat2x2", mrb_cp_mat2x2_free };

/*
 * Chipmunk2d::Mat2x2#initialize(a, b, c, d)
 * @param [Float] a
 * @param [Float] b
 * @param [Float] c
 * @param [Float] d
 * @return [self]
 */
static mrb_value
mat2x2_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float a;
  mrb_float b;
  mrb_float c;
  mrb_float d;
  cpMat2x2 *mat2x2;
  mrb_get_args(mrb, "ffff", &a, &b, &c, &d);
  mat2x2 = (cpMat2x2*)DATA_PTR(self);
  if (mat2x2) {
    mrb_cp_mat2x2_free(mrb, mat2x2);
  }
  mat2x2 = mrb_malloc(mrb, sizeof(cpMat2x2));
  *mat2x2 = cpMat2x2New(a, b, c, d);
  mrb_data_init(self, mat2x2, &mrb_cp_mat2x2_type);
  return self;
}

/*
 * Chipmunk2d::Mat2x2#a
 * @return [Float]
 */
static mrb_value
mat2x2_get_a(mrb_state *mrb, mrb_value self)
{
  cpMat2x2 *mat2x2;
  mat2x2 = mrb_data_get_ptr(mrb, self, &mrb_cp_mat2x2_type);
  return mrb_float_value(mrb, (mrb_float)mat2x2->a);
}

/*
 * Chipmunk2d::Mat2x2#a=
 * @param [Float] a
 */
static mrb_value
mat2x2_set_a(mrb_state *mrb, mrb_value self)
{
  cpMat2x2 *mat2x2;
  mrb_float a;
  mrb_get_args(mrb, "f", &a);
  mat2x2 = mrb_data_get_ptr(mrb, self, &mrb_cp_mat2x2_type);
  mat2x2->a = (cpFloat)a;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Mat2x2#b
 * @return [Float]
 */
static mrb_value
mat2x2_get_b(mrb_state *mrb, mrb_value self)
{
  cpMat2x2 *mat2x2;
  mat2x2 = mrb_data_get_ptr(mrb, self, &mrb_cp_mat2x2_type);
  return mrb_float_value(mrb, (mrb_float)mat2x2->b);
}

/*
 * Chipmunk2d::Mat2x2#b=
 * @param [Float] b
 */
static mrb_value
mat2x2_set_b(mrb_state *mrb, mrb_value self)
{
  cpMat2x2 *mat2x2;
  mrb_float b;
  mrb_get_args(mrb, "f", &b);
  mat2x2 = mrb_data_get_ptr(mrb, self, &mrb_cp_mat2x2_type);
  mat2x2->b = (cpFloat)b;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Mat2x2#c
 * @return [Float]
 */
static mrb_value
mat2x2_get_c(mrb_state *mrb, mrb_value self)
{
  cpMat2x2 *mat2x2;
  mat2x2 = mrb_data_get_ptr(mrb, self, &mrb_cp_mat2x2_type);
  return mrb_float_value(mrb, (mrb_float)mat2x2->c);
}

/*
 * Chipmunk2d::Mat2x2#c=
 * @param [Float] c
 */
static mrb_value
mat2x2_set_c(mrb_state *mrb, mrb_value self)
{
  cpMat2x2 *mat2x2;
  mrb_float c;
  mrb_get_args(mrb, "f", &c);
  mat2x2 = mrb_data_get_ptr(mrb, self, &mrb_cp_mat2x2_type);
  mat2x2->c = (cpFloat)c;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Mat2x2#d
 * @return [Float]
 */
static mrb_value
mat2x2_get_d(mrb_state *mrb, mrb_value self)
{
  cpMat2x2 *mat2x2;
  mat2x2 = mrb_data_get_ptr(mrb, self, &mrb_cp_mat2x2_type);
  return mrb_float_value(mrb, (mrb_float)mat2x2->d);
}

/*
 * Chipmunk2d::Mat2x2#d=
 * @param [Float] d
 */
static mrb_value
mat2x2_set_d(mrb_state *mrb, mrb_value self)
{
  cpMat2x2 *mat2x2;
  mrb_float d;
  mrb_get_args(mrb, "f", &d);
  mat2x2 = mrb_data_get_ptr(mrb, self, &mrb_cp_mat2x2_type);
  mat2x2->d = (cpFloat)d;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Mat2x2#transform(vect)
 * @param [Chipmunk2d::Vect] vect
 */
static mrb_value
mat2x2_transform(mrb_state *mrb, mrb_value self)
{
  cpMat2x2 *mat2x2;
  cpVect *vect;
  mrb_get_args(mrb, "d", &vect, &mrb_cp_vect_type);
  mat2x2 = mrb_data_get_ptr(mrb, self, &mrb_cp_mat2x2_type);
  return mrb_cp_vect_value(mrb, cpMat2x2Transform(*mat2x2, *vect));
}

void
mrb_cp_mat2x2_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_mat2x2_class = mrb_define_class_under(mrb, cp_module, "Mat2x2", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_mat2x2_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_mat2x2_class, "initialize", mat2x2_initialize, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, mrb_cp_mat2x2_class, "a",          mat2x2_get_a,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_mat2x2_class, "a=",         mat2x2_set_a,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_mat2x2_class, "b",          mat2x2_get_b,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_mat2x2_class, "b=",         mat2x2_set_b,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_mat2x2_class, "c",          mat2x2_get_c,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_mat2x2_class, "c=",         mat2x2_set_c,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_mat2x2_class, "d",          mat2x2_get_d,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_mat2x2_class, "d=",         mat2x2_set_d,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_mat2x2_class, "transform",  mat2x2_transform,  MRB_ARGS_REQ(1));
}
