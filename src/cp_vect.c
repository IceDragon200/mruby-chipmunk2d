#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_vect.h"

static struct RClass *mrb_cp_vect_class;

void
mrb_cp_vect_free(mrb_state *mrb, void *ptr)
{
  cpVect *mrb_cp_vect = ptr;

  if (mrb_cp_vect) {
    mrb_free(mrb, mrb_cp_vect);
  }
}

struct mrb_data_type mrb_cp_vect_type = { "Chipmunk2d::Vect", mrb_cp_vect_free };

mrb_value
mrb_cp_vect_value(mrb_state *mrb, cpVect vect)
{
  cpVect *vectp;
  mrb_value mrb_vect;
  mrb_value zero = mrb_float_value(mrb, 0.0);
  mrb_value argv[2] = { zero, zero };
  mrb_vect = mrb_obj_new(mrb, mrb_cp_vect_class, 2, argv);

  vectp = mrb_data_get_ptr(mrb, mrb_vect, &mrb_cp_vect_type);
  *vectp = vect;

  return mrb_vect;
}

static mrb_value
vect_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float x;
  mrb_float y;
  cpVect *vect;
  mrb_get_args(mrb, "ff", &x, &y);

  vect = (cpVect*)DATA_PTR(self);
  if (vect) {
    mrb_cp_vect_free(mrb, vect);
  }

  vect = mrb_malloc(mrb, sizeof(cpVect));
  *vect = cpv(x, y);

  mrb_data_init(self, vect, &mrb_cp_vect_type);

  return self;
}

static mrb_value
vect_get_x(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);
  return mrb_float_value(mrb, (mrb_float)vect->x);
}

static mrb_value
vect_set_x(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  mrb_float x;
  mrb_get_args(mrb, "f", &x);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);
  vect->x = (cpFloat)x;
  return mrb_nil_value();
}

static mrb_value
vect_get_y(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);
  return mrb_float_value(mrb, (mrb_float)vect->y);
}

static mrb_value
vect_set_y(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  mrb_float y;
  mrb_get_args(mrb, "f", &y);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);
  vect->y = (cpFloat)y;
  return mrb_nil_value();
}

static mrb_value
vect_is_equal(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  cpBool is_equal;
  mrb_get_args(mrb, "d", &other, &mrb_cp_vect_type);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);
  is_equal = cpveql(*vect, *other);
  return mrb_bool_value(is_equal);
}

static mrb_value
vect_add(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_vect_type);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvadd(*vect, *other));
}

static mrb_value
vect_sub(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_vect_type);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvsub(*vect, *other));
}

static mrb_value
vect_neg(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvneg(*vect));
}

static mrb_value
vect_mult(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  mrb_float num;
  mrb_get_args(mrb, "f", &num);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvmult(*vect, num));
}

static mrb_value
vect_dot(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_vect_type);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_float_value(mrb, cpvdot(*vect, *other));
}

static mrb_value
vect_cross(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_vect_type);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_float_value(mrb, cpvcross(*vect, *other));
}

static mrb_value
vect_perp(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvperp(*vect));
}

static mrb_value
vect_rperp(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvrperp(*vect));
}

static mrb_value
vect_project(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_vect_type);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvproject(*vect, *other));
}

static mrb_value
vect_to_angle(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_float_value(mrb, cpvtoangle(*vect));
}

static mrb_value
vect_rotate(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_vect_type);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvrotate(*vect, *other));
}

static mrb_value
vect_unrotate(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_vect_type);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvunrotate(*vect, *other));
}

static mrb_value
vect_length_sq(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_float_value(mrb, cpvlengthsq(*vect));
}

static mrb_value
vect_length(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_float_value(mrb, cpvlength(*vect));
}

static mrb_value
vect_lerp(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_float delta;
  mrb_get_args(mrb, "df", &other, &mrb_cp_vect_type, &delta);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvlerp(*vect, *other, (cpFloat)delta));
}

static mrb_value
vect_normalize(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvnormalize(*vect));
}

static mrb_value
vect_slerp(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_float delta;
  mrb_get_args(mrb, "df", &other, &mrb_cp_vect_type, &delta);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvslerp(*vect, *other, (cpFloat)delta));
}

static mrb_value
vect_slerp_const(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_float delta;
  mrb_get_args(mrb, "df", &other, &mrb_cp_vect_type, &delta);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvslerpconst(*vect, *other, (cpFloat)delta));
}

static mrb_value
vect_clamp(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  mrb_float len;
  mrb_get_args(mrb, "f", &len);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvclamp(*vect, (cpFloat)len));
}

static mrb_value
vect_lerp_const(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_float delta;
  mrb_get_args(mrb, "df", &other, &mrb_cp_vect_type, &delta);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_cp_vect_value(mrb, cpvlerpconst(*vect, *other, (cpFloat)delta));
}

static mrb_value
vect_dist(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_vect_type);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_float_value(mrb, cpvdist(*vect, *other));
}

static mrb_value
vect_dist_sq(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_get_args(mrb, "d", &other, &mrb_cp_vect_type);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_float_value(mrb, cpvdistsq(*vect, *other));
}

static mrb_value
vect_is_near(mrb_state *mrb, mrb_value self)
{
  cpVect *vect;
  cpVect *other;
  mrb_float dist;
  mrb_get_args(mrb, "df", &other, &mrb_cp_vect_type, &dist);
  vect = mrb_data_get_ptr(mrb, self, &mrb_cp_vect_type);

  return mrb_bool_value(cpvnear(*vect, *other, (cpFloat)dist));
}

static mrb_value
vect_s_for_angle(mrb_state *mrb, mrb_value klass)
{
  mrb_float angle;
  mrb_get_args(mrb, "f", &angle);
  return mrb_cp_vect_value(mrb, cpvforangle((cpFloat)angle));
}

void
mrb_cp_vect_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_vect_class = mrb_define_class_under(mrb, cp_module, "Vect", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_vect_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_cp_vect_class, "initialize",         vect_initialize,         MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_vect_class, "x",                  vect_get_x,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_vect_class, "x=",                 vect_set_x,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "y",                  vect_get_y,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_vect_class, "y=",                 vect_set_y,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "==",                 vect_is_equal,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "+",                  vect_add,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "-",                  vect_sub,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "@-",                 vect_neg,                MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_vect_class, "*",                  vect_mult,               MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "dot",                vect_dot,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "cross",              vect_cross,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "perp",               vect_perp,               MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_vect_class, "rperp",              vect_rperp,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_vect_class, "project",            vect_project,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "to_angle",           vect_to_angle,           MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_vect_class, "rotate",             vect_rotate,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "unrotate",           vect_unrotate,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "length_sq",          vect_length_sq,          MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_vect_class, "length",             vect_length,             MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_vect_class, "lerp",               vect_lerp,               MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_vect_class, "normalize",          vect_normalize,          MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_vect_class, "slerp",              vect_slerp,              MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_vect_class, "slerp_const",        vect_slerp_const,        MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_vect_class, "clamp",              vect_clamp,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "lerp_const",         vect_lerp_const,         MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_vect_class, "dist",               vect_dist,               MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "dist_sq",            vect_dist_sq,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_vect_class, "near?",              vect_is_near,            MRB_ARGS_REQ(2));

  mrb_define_class_method(mrb, mrb_cp_vect_class, "for_angle",    vect_s_for_angle,        MRB_ARGS_REQ(1));
}
