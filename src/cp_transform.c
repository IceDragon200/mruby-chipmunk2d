#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_transform.h"
#include "cp_vect.h"
#include "cp_bb.h"

static struct RClass* mrb_cp_transform_class;

static void
mrb_cp_transform_free(mrb_state* mrb, void* ptr)
{
  cpTransform* transform = (cpTransform*)ptr;

  if (transform) {
    mrb_free(mrb, transform);
  }
}

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_transform_type = { "cpTransform", mrb_cp_transform_free };

/*
 * @return [Chipmunk2d::Transform]
 */
MRB_CP_EXTERN mrb_value
mrb_cp_transform_value(mrb_state* mrb, cpTransform transform)
{
  mrb_value result;
  mrb_value zero = mrb_float_value(mrb, 0.0f);
  mrb_value argv[6] = { zero, zero, zero, zero, zero, zero };
  cpTransform* result_transform;
  result = mrb_obj_new(mrb, mrb_cp_transform_class, 6, argv);
  result_transform = mrb_cp_get_transform_ptr(mrb, result);
  *result_transform = transform;
  return result;
}

/*
 * Chipmunk2d::Transform#initialize(a, b, c, d, tx, ty)
 * @param [Float] a
 * @param [Float] b
 * @param [Float] c
 * @param [Float] d
 * @param [Float] tx
 * @param [Float] ty
 * @return [self]
 */
static mrb_value
transform_initialize(mrb_state* mrb, mrb_value self)
{
  mrb_float a;
  mrb_float b;
  mrb_float c;
  mrb_float d;
  mrb_float tx;
  mrb_float ty;
  cpTransform* transform;
  mrb_get_args(mrb, "ffffff", &a, &b, &c, &d, &tx, &ty);
  transform = (cpTransform*)DATA_PTR(self);

  if (transform) {
    mrb_cp_transform_free(mrb, transform);
  }

  transform = (cpTransform*)mrb_malloc(mrb, sizeof(cpTransform));
  *transform = cpTransformNew(a, b, c, d, tx, ty);
  mrb_data_init(self, transform, &mrb_cp_transform_type);
  return self;
}

/*
 * Chipmunk2d::Transform#a
 * @return [Float]
 */
static mrb_value
transform_get_a(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_float_value(mrb, transform->a);
}

/*
 * Chipmunk2d::Transform#a=(a)
 * @param [Float] a
 */
static mrb_value
transform_set_a(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  mrb_float a;
  mrb_get_args(mrb, "f", &a);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  transform->a = (cpFloat)a;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Transform#b
 * @return [Float]
 */
static mrb_value
transform_get_b(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_float_value(mrb, transform->b);
}

/*
 * Chipmunk2d::Transform#b=(b)
 * @param [Float] b
 */
static mrb_value
transform_set_b(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  mrb_float b;
  mrb_get_args(mrb, "f", &b);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  transform->b = (cpFloat)b;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Transform#c
 * @return [Float]
 */
static mrb_value
transform_get_c(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_float_value(mrb, transform->c);
}

/*
 * Chipmunk2d::Transform#c=(c)
 * @param [Float] c
 */
static mrb_value
transform_set_c(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  mrb_float c;
  mrb_get_args(mrb, "f", &c);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  transform->c = (cpFloat)c;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Transform#d
 * @return [Float]
 */
static mrb_value
transform_get_d(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_float_value(mrb, transform->d);
}

/*
 * Chipmunk2d::Transform#d=(d)
 * @param [Float] d
 */
static mrb_value
transform_set_d(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  mrb_float d;
  mrb_get_args(mrb, "f", &d);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  transform->d = (cpFloat)d;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Transform#tx
 * @return [Float]
 */
static mrb_value
transform_get_tx(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_float_value(mrb, transform->tx);
}

/*
 * Chipmunk2d::Transform#tx=(tx)
 * @param [Float] tx
 */
static mrb_value
transform_set_tx(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  mrb_float tx;
  mrb_get_args(mrb, "f", &tx);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  transform->tx = (cpFloat)tx;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Transform#ty
 * @return [Float]
 */
static mrb_value
transform_get_ty(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_float_value(mrb, transform->ty);
}

/*
 * Chipmunk2d::Transform#ty=(ty)
 * @param [Float] ty
 */
static mrb_value
transform_set_ty(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  mrb_float ty;
  mrb_get_args(mrb, "f", &ty);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  transform->ty = (cpFloat)ty;
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Transform#inverse
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_inverse(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_cp_transform_value(mrb, cpTransformInverse(*transform));
}

/*
 * Chipmunk2d::Transform#*(other)
 * @param [Chipmunk2d::Transform] other
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_mult(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  cpTransform* other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_transform_type);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_cp_transform_value(mrb, cpTransformMult(*transform, *other));
}

/*
 * Chipmunk2d::Transform#point(vect)
 * @param [Chipmunk2d::Vect] vect
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
transform_point(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  cpVect* vect;
  mrb_get_args(mrb, "d", &vect, &mrb_cp_vect_type);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_cp_vect_value(mrb, cpTransformPoint(*transform, *vect));
}

/*
 * Chipmunk2d::Transform#vect(vect)
 * @param [Chipmunk2d::Vect] vect
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
transform_vect(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  cpVect* vect;
  mrb_get_args(mrb, "d", &vect, &mrb_cp_vect_type);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_cp_vect_value(mrb, cpTransformVect(*transform, *vect));
}

/*
 * Chipmunk2d::Transform#bb(bb)
 * @param [Chipmunk2d::BB] bb
 * @return [Chipmunk2d::BB]
 */
static mrb_value
transform_bb(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  cpBB* bb;
  mrb_get_args(mrb, "d", &bb, &mrb_cp_bb_type);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_cp_bb_value(mrb, cpTransformbBB(*transform, *bb));
}

/*
 * Chipmunk2d::Transform#rigid_inverse
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_rigid_inverse(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_cp_transform_value(mrb, cpTransformRigidInverse(*transform));
}

/*
 * Chipmunk2d::Transform#wrap(other)
 * @param [Chipmunk2d::Transform] other
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_wrap(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  cpTransform* other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_transform_type);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_cp_transform_value(mrb, cpTransformWrap(*transform, *other));
}

/*
 * Chipmunk2d::Transform#wrap_inverse(other)
 * @param [Chipmunk2d::Transform] other
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_wrap_inverse(mrb_state* mrb, mrb_value self)
{
  cpTransform* transform;
  cpTransform* other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_transform_type);
  transform = mrb_cp_get_transform_ptr(mrb, self);
  return mrb_cp_transform_value(mrb, cpTransformWrapInverse(*transform, *other));
}

/*
 * Chipmunk2d::Transform.new_transpose(a, b, c, d, e, f)
 * @param [Float] a
 * @param [Float] b
 * @param [Float] c
 * @param [Float] d
 * @param [Float] e
 * @param [Float] f
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_s_new_transpose(mrb_state* mrb, mrb_value klass)
{
  mrb_float a;
  mrb_float b;
  mrb_float c;
  mrb_float d;
  mrb_float e;
  mrb_float f;
  cpTransform transform;
  mrb_get_args(mrb, "ffffff", &a, &b, &c, &d, &e, &f);
  transform = cpTransformNewTranspose((cpFloat)a, (cpFloat)b, (cpFloat)c,
                                      (cpFloat)d, (cpFloat)e, (cpFloat)f);
  return mrb_cp_transform_value(mrb, transform);
}

/*
 * Chipmunk2d::Transform.translate(vect)
 * @param [Chipmunk2d::Vect] vect
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_s_translate(mrb_state* mrb, mrb_value klass)
{
  cpVect* vect;
  mrb_get_args(mrb, "d", &vect, &mrb_cp_vect_type);
  return mrb_cp_transform_value(mrb, cpTransformTranslate(*vect));
}

/*
 * Chipmunk2d::Transform.scale(scale_x, scale_y)
 * @param [Float] scale_x
 * @param [Float] scale_y
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_s_scale(mrb_state* mrb, mrb_value klass)
{
  mrb_float scale_x;
  mrb_float scale_y;
  mrb_get_args(mrb, "ff", &scale_x, &scale_y);
  return mrb_cp_transform_value(mrb, cpTransformScale((cpFloat)scale_x,
                                (cpFloat)scale_y));
}

/*
 * Chipmunk2d::Transform.rotate(radians)
 * @param [Float] radians
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_s_rotate(mrb_state* mrb, mrb_value klass)
{
  mrb_float radians;
  mrb_get_args(mrb, "f", &radians);
  return mrb_cp_transform_value(mrb, cpTransformRotate((cpFloat)radians));
}

/*
 * Chipmunk2d::Transform.rigid(vect, radians)
 * @param [Chipmunk2d::Vect] vect
 * @param [Float] radians
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_s_rigid(mrb_state* mrb, mrb_value klass)
{
  cpVect* vect;
  mrb_float radians;
  mrb_get_args(mrb, "df", &vect, &mrb_cp_vect_type, &radians);
  return mrb_cp_transform_value(mrb, cpTransformRigid(*vect, (cpFloat)radians));
}

/*
 * Chipmunk2d::Transform.ortho(bb)
 * @param [Chipmunk2d::BB] bb
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_s_ortho(mrb_state* mrb, mrb_value klass)
{
  cpBB* bb;
  mrb_get_args(mrb, "d", &bb, &mrb_cp_bb_type);
  return mrb_cp_transform_value(mrb, cpTransformOrtho(*bb));
}

/*
 * Chipmunk2d::Transform.bone_scale(v0, v1)
 * @param [Chipmunk2d::Vect] v0
 * @param [Chipmunk2d::Vect] v1
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_s_bone_scale(mrb_state* mrb, mrb_value klass)
{
  cpVect* v0;
  cpVect* v1;
  mrb_get_args(mrb, "dd", &v0, &mrb_cp_vect_type,
               &v1, &mrb_cp_vect_type);
  return mrb_cp_transform_value(mrb, cpTransformBoneScale(*v0, *v1));
}

/*
 * Chipmunk2d::Transform.axial_scale(v0, v1, scale)
 * @param [Chipmunk2d::Vect] v0
 * @param [Chipmunk2d::Vect] v1
 * @param [Float] scale
 * @return [Chipmunk2d::Transform]
 */
static mrb_value
transform_s_axial_scale(mrb_state* mrb, mrb_value klass)
{
  cpVect* v0;
  cpVect* v1;
  mrb_float scale;
  mrb_get_args(mrb, "ddf", &v0, &mrb_cp_vect_type,
               &v1, &mrb_cp_vect_type,
               &scale);
  return mrb_cp_transform_value(mrb, cpTransformAxialScale(*v0, *v1, (cpFloat)scale));
}

MRB_CP_EXTERN void
mrb_cp_transform_init(mrb_state* mrb, struct RClass* cp_module)
{
  mrb_cp_transform_class = mrb_define_class_under(mrb, cp_module, "Transform", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_transform_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_transform_class, "initialize",    transform_initialize,    MRB_ARGS_REQ(6));
  mrb_define_method(mrb, mrb_cp_transform_class, "inverse",       transform_inverse,       MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_transform_class, "a",             transform_get_a,         MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_transform_class, "a=",            transform_set_a,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "b",             transform_get_b,         MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_transform_class, "b=",            transform_set_b,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "c",             transform_get_c,         MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_transform_class, "c=",            transform_set_c,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "d",             transform_get_d,         MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_transform_class, "d=",            transform_set_d,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "tx",            transform_get_tx,        MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_transform_class, "tx=",           transform_set_tx,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "ty",            transform_get_ty,        MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_transform_class, "ty=",           transform_set_ty,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "*",             transform_mult,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "point",         transform_point,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "vect",          transform_vect,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "bb",            transform_bb,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "rigid_inverse", transform_rigid_inverse, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_transform_class, "wrap",          transform_wrap,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_transform_class, "wrap_inverse",  transform_wrap_inverse,  MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_cp_transform_class, "new_transpose",  transform_s_new_transpose, MRB_ARGS_REQ(6));
  mrb_define_class_method(mrb, mrb_cp_transform_class, "translate",      transform_s_translate,     MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_cp_transform_class, "scale",          transform_s_scale,         MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, mrb_cp_transform_class, "rotate",         transform_s_rotate,        MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_cp_transform_class, "rigid",          transform_s_rigid,         MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_cp_transform_class, "ortho",          transform_s_ortho,         MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_cp_transform_class, "bone_scale",     transform_s_bone_scale,    MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, mrb_cp_transform_class, "axial_scale",    transform_s_axial_scale,   MRB_ARGS_REQ(3));
}
