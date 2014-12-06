#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_poly_shape.h"
#include "cp_private.h"
#include "cp_bb.h"
#include "cp_body.h"
#include "cp_shape.h"
#include "cp_transform.h"
#include "cp_vect.h"

static struct RClass *mrb_cp_poly_shape_class;
static struct RClass *mrb_cp_box_shape_class;

static cpVect *
poly_shape_verts_extract(mrb_state *mrb, int count, mrb_value *averts)
{
  cpVect *verts;
  int i;
  verts = (cpVect*)malloc(sizeof(cpVect) * count);
  for (i = 0; i < count; ++i) {
    verts[i] = *(cpVect*)mrb_data_get_ptr(mrb, averts[i], &mrb_cp_vect_type);
  }
  return verts;
}

/*
 * @overload Chipmunk2d::PolyShape#initialize(body, verts, transform, radius)
 *   @param [Chipmunk2d::Body] body
 *   @param [Array<Chipmunk2d::Vect>] verts
 *   @param [Chipmunk2d::Transform] transform
 *   @param [Float] radius
 * @overload Chipmunk2d::PolyShape#initialize(body, verts, radius)
 *   @param [Chipmunk2d::Body] body
 *   @param [Array<Chipmunk2d::Vect>] verts
 *   @param [Float] radius
 */
static mrb_value
poly_shape_initialize(mrb_state *mrb, mrb_value self)
{
  cpShape *shape;
  cpBody *body;
  cpVect *verts; /* Array<cpVert> */
  cpTransform *transform;
  mrb_value *averts;
  mrb_value body_obj;
  mrb_int count;
  mrb_float radius;
  int argc;
  mrb_cp_shape_cleanup(mrb, self);
  argc = mrb_cp_argc(mrb);
  shape = NULL;
  if (argc == 4) {
    mrb_get_args(mrb, "oadf", &body_obj, &averts, &count,
                              &transform, &mrb_cp_transform_type,
                              &radius);
    body = mrb_data_get_ptr(mrb, body_obj, &mrb_cp_body_type);
    verts = poly_shape_verts_extract(mrb, count, averts);
    shape = cpPolyShapeNew(body, (int)count, verts, *transform, (cpFloat)radius);
    free(verts);
  } else if (argc == 3) {
    mrb_get_args(mrb, "oaf", &body_obj, &averts, &count, &radius);
    body = mrb_data_get_ptr(mrb, body_obj, &mrb_cp_body_type);
    verts = poly_shape_verts_extract(mrb, count, averts);
    shape = cpPolyShapeNewRaw(body, (int)count, verts, (cpFloat)radius);
    free(verts);
  } else {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "expected 3 or 4");
    return mrb_nil_value();
  }
  mrb_cp_shape_init_bind(mrb, self, shape);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body"), body_obj);
  return self;
}

static mrb_value
poly_shape_count(mrb_state *mrb, mrb_value self)
{
  cpShape *shape;
  int count;
  Data_Get_Struct(mrb, self, &mrb_cp_shape_type, shape);
  count = cpPolyShapeGetCount(shape);
  return mrb_fixnum_value(count);
}

static mrb_value
poly_shape_vert(mrb_state *mrb, mrb_value self)
{
  cpShape *shape;
  cpVect vert;
  mrb_int index;
  mrb_get_args(mrb, "i", &index);
  Data_Get_Struct(mrb, self, &mrb_cp_shape_type, shape);
  vert = cpPolyShapeGetVert(shape, index);
  return mrb_cp_vect_value(mrb, vert);
}

static mrb_value
poly_shape_radius(mrb_state *mrb, mrb_value self)
{
  cpShape *shape;
  cpFloat radius;
  Data_Get_Struct(mrb, self, &mrb_cp_shape_type, shape);
  radius = cpPolyShapeGetRadius(shape);
  return mrb_float_value(mrb, radius);
}

/*
 * @overload Chipmunk2d::BoxShape#initialize(body, width, height, radius)
 *   @param [Chipmunk2d::Body] body
 *   @param [Float] width
 *   @param [Float] height
 * @overload Chipmunk2d::BoxShape#initialize(body, bb, radius)
 *   @param [Chipmunk2d::Body] body
 *   @param [Chipmunk2d::BB] bb
 *   @param [Float] radius
 */
static mrb_value
box_shape_initialize(mrb_state *mrb, mrb_value self)
{
  cpShape *shape;
  cpBody *body;
  cpBB *box;
  mrb_float width;
  mrb_float height;
  mrb_float radius;
  mrb_value body_obj;
  int argc;
  mrb_cp_shape_cleanup(mrb, self);
  argc = mrb_cp_argc(mrb);
  shape = NULL;
  if (argc == 4) {
    mrb_get_args(mrb, "offf", &body_obj, &width, &height, &radius);
    body = mrb_data_get_ptr(mrb, body_obj, &mrb_cp_body_type);
    shape = cpBoxShapeNew(body, (cpFloat)width, (cpFloat)height, (cpFloat)radius);
  } else if (argc == 3) {
    mrb_get_args(mrb, "odf", &body_obj, &box, &mrb_cp_bb_type, &radius);
    body = mrb_data_get_ptr(mrb, body_obj, &mrb_cp_body_type);
    shape = cpBoxShapeNew2(body, *box, (cpFloat)radius);
  } else {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "expected 2 or 3");
    return mrb_nil_value();
  }
  mrb_cp_shape_init_bind(mrb, self, shape);
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "body"), body_obj);
  return self;
}

void
mrb_cp_poly_shape_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_poly_shape_class = mrb_define_class_under(mrb, cp_module, "PolyShape", mrb_cp_get_shape_class());
  MRB_SET_INSTANCE_TT(mrb_cp_poly_shape_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_poly_shape_class, "initialize", poly_shape_initialize, MRB_ARGS_ARG(3,1));
  mrb_define_method(mrb, mrb_cp_poly_shape_class, "count",      poly_shape_count,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_poly_shape_class, "vert",       poly_shape_vert,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_poly_shape_class, "radius",     poly_shape_radius,     MRB_ARGS_NONE());

  mrb_cp_box_shape_class = mrb_define_class_under(mrb, cp_module, "BoxShape", mrb_cp_poly_shape_class);
  MRB_SET_INSTANCE_TT(mrb_cp_box_shape_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_cp_box_shape_class, "initialize", box_shape_initialize, MRB_ARGS_ARG(3,1));
}
