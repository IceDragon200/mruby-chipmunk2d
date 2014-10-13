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
  cpVect *vect;
  int i;
  verts = (cpVect*)malloc(sizeof(cpVect) * count);
  for (i = 0; i < count; ++i) {
    Data_Get_Struct(mrb, averts[i], &mrb_cp_vect_type, vect);
    verts[i] = *vect;
  }
  return verts;
}

static mrb_value
poly_shape_initialize(mrb_state *mrb, mrb_value self)
{
  cpShape *shape;
  cpBody *body;
  cpVect *verts; /* Array<cpVert> */
  cpTransform *transform;
  mrb_value *averts;
  mrb_int count;
  mrb_float radius;
  int argc;
  mrb_cp_shape_cleanup(mrb, self);

  argc = mrb_cp_argc(mrb);

  shape = NULL;
  if (argc == 4) {
    mrb_get_args(mrb, "dadf",
                      &body, &mrb_cp_body_type,
                      &averts, &count,
                      &transform, &mrb_cp_transform_type,
                      &radius);
    verts = poly_shape_verts_extract(mrb, count, averts);
    shape = cpPolyShapeNew(body, (int)count, verts, *transform, (cpFloat)radius);
    free(verts);
  } else if (argc == 3) {
    mrb_get_args(mrb, "daf",
                      &body, &mrb_cp_body_type,
                      &averts, &count,
                      &radius);
    verts = poly_shape_verts_extract(mrb, count, averts);
    //shape = cpPolyShapeNewRaw(body, (int)count, verts, (cpFloat)radius);
    free(verts);
  }
  mrb_cp_shape_init_bind(mrb, self, shape);
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

static mrb_value
box_shape_initialize(mrb_state *mrb, mrb_value self)
{
  cpShape *shape;
  cpBody *body;
  cpBB *box;
  mrb_float width;
  mrb_float height;
  mrb_float radius;
  int argc;
  mrb_cp_shape_cleanup(mrb, self);
  argc = mrb_cp_argc(mrb);
  shape = NULL;
  if (argc == 4) {
    mrb_get_args(mrb, "dfff",
                      &body, &mrb_cp_body_type,
                      &width, &height, &radius);
    shape = cpBoxShapeNew(body, (cpFloat)width, (cpFloat)height, (cpFloat)radius);
  } else if (argc == 3) {
    mrb_get_args(mrb, "ddf",
                      &body, &mrb_cp_body_type,
                      &box, &mrb_cp_bb_type, &radius);
    shape = cpBoxShapeNew2(body, *box, (cpFloat)radius);
  } else {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "expected 2 or 3");
  }
  mrb_cp_shape_init_bind(mrb, self, shape);
  return self;
}

void
mrb_cp_poly_shape_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_poly_shape_class = mrb_define_class_under(mrb, cp_module, "PolyShape", mrb_cp_get_shape_class());
  MRB_SET_INSTANCE_TT(mrb_cp_poly_shape_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_cp_poly_shape_class, "initialize", poly_shape_initialize, MRB_ARGS_ARG(3,1));
  mrb_define_method(mrb, mrb_cp_poly_shape_class, "count",      poly_shape_count,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_poly_shape_class, "vert",       poly_shape_vert,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_poly_shape_class, "radius",     poly_shape_radius,     MRB_ARGS_NONE());

  mrb_cp_box_shape_class = mrb_define_class_under(mrb, cp_module, "BoxShape", mrb_cp_poly_shape_class);
  MRB_SET_INSTANCE_TT(mrb_cp_box_shape_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_cp_box_shape_class, "initialize", box_shape_initialize, MRB_ARGS_ARG(3,1));
}
