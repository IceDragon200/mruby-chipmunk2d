#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_shape.h"
#include "cp_shape_filter.h"
#include "cp_bb.h"
#include "cp_body.h"
#include "cp_transform.h"
#include "cp_contact_point.h"
#include "cp_point_query_info.h"
#include "cp_segment_query_info.h"
#include "cp_vect.h"
#include "cp_private.h"

static struct RClass* mrb_cp_shape_class;
static struct RClass* mrb_cp_circle_shape_class;
static struct RClass* mrb_cp_segment_shape_class;

MRB_CP_EXTERN mrb_cp_shape_user_data*
mrb_cp_shape_user_data_new(mrb_state* mrb)
{
  mrb_cp_shape_user_data* user_data =
    (mrb_cp_shape_user_data*)mrb_malloc(mrb, sizeof(mrb_cp_shape_user_data));
  user_data->shape = mrb_nil_value();
  user_data->space = mrb_nil_value();
  return user_data;
}

MRB_CP_EXTERN void
mrb_cp_shape_user_data_free(mrb_state* mrb, mrb_cp_shape_user_data* ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

MRB_CP_EXTERN void
mrb_cp_shape_free(mrb_state* mrb, void* ptr)
{
  cpShape* mrb_cp_shape = (cpShape*)ptr;

  if (mrb_cp_shape) {
    cpShapeFree(mrb_cp_shape);
  }
}

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_shape_type = { "cpShape", mrb_cp_shape_free };

MRB_CP_EXTERN struct RClass*
mrb_cp_get_shape_class()
{
  return mrb_cp_shape_class;
}

MRB_CP_EXTERN void
mrb_cp_shape_cleanup(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  shape = (cpShape*)DATA_PTR(self);

  if (shape) {
    mrb_cp_shape_free(mrb, shape);
  }
}

MRB_CP_EXTERN void
mrb_cp_shape_init_bind(mrb_state* mrb, mrb_value self, cpShape* shape)
{
  mrb_cp_shape_user_data* user_data;
  user_data = mrb_cp_shape_user_data_new(mrb);
  user_data->shape = self;
  cpShapeSetUserData(shape, user_data);
  mrb_data_init(self, shape, &mrb_cp_shape_type);
}

MRB_CP_EXTERN mrb_value
mrb_cp_shape_get_mrb_obj(mrb_state* mrb, const cpShape* shape)
{
  mrb_cp_shape_user_data* user_data;
  user_data = (mrb_cp_shape_user_data*)cpShapeGetUserData(shape);
  return user_data->shape;
}

static mrb_value
shape_initialize(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_RUNTIME_ERROR, "You may not create a `Shape` Object.");
  return self;
}

static mrb_value
shape_cache_bb(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  return mrb_cp_bb_value(mrb, cpShapeCacheBB(shape));
}

static mrb_value
shape_update(mrb_state* mrb, mrb_value self)
{
  cpShape*      shape;
  cpTransform*  transform;
  mrb_get_args(mrb, "d", &transform, &mrb_cp_transform_type);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  return mrb_cp_bb_value(mrb, cpShapeUpdate(shape, *transform));
}

static mrb_value
shape_point_query(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpVect* p;
  cpPointQueryInfo* out;
  cpFloat point_query;
  mrb_get_args(mrb, "dd", &p, &mrb_cp_vect_type,
               &out, &mrb_cp_point_query_info_type);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  point_query = cpShapePointQuery(shape, *p, out);
  return mrb_float_value(mrb, point_query);
}

static mrb_value
shape_segment_query(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpVect* a;
  cpVect* b;
  cpSegmentQueryInfo* info;
  cpBool segment_query;
  mrb_float radius;
  mrb_get_args(mrb, "ddfd", &a, &mrb_cp_vect_type,
               &b, &mrb_cp_vect_type,
               &radius,
               &info, &mrb_cp_segment_query_info_type);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  segment_query = cpShapeSegmentQuery(shape, *a, *b, (cpFloat)radius, info);
  return mrb_float_value(mrb, segment_query);
}

/*
 * @return [Chipmunk2d::ContactPointSet]
 */
static mrb_value
shape_collide(mrb_state* mrb, mrb_value self)
{
  cpShape* a;
  cpShape* b;
  cpContactPointSet contact_point_set;
  mrb_get_args(mrb, "d", &b, &mrb_cp_shape_type);
  a = mrb_cp_get_shape_ptr(mrb, self);
  contact_point_set = cpShapesCollide(a, b);
  return mrb_cp_contact_point_set_value(mrb, &contact_point_set);
}

/*
 * @return [Chipmunk2d::Space, nil]
 */
static mrb_value
shape_get_space(mrb_state* mrb, mrb_value self)
{
  mrb_sym space_sym;
  space_sym = mrb_intern_lit(mrb, "space");
  return mrb_iv_get(mrb, self, space_sym);
}

static mrb_value
shape_get_body(mrb_state* mrb, mrb_value self)
{
  mrb_sym body_sym;
  body_sym = mrb_intern_lit(mrb, "body");
  return mrb_iv_get(mrb, self, body_sym);
}

static mrb_value
shape_set_body(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpBody* body;
  mrb_value body_obj;
  mrb_sym body_sym;
  mrb_get_args(mrb, "d", &body, &mrb_cp_body_type);
  mrb_get_args(mrb, "o", &body_obj);
  body_sym = mrb_intern_lit(mrb, "body");
  shape = mrb_cp_get_shape_ptr(mrb, self);
  cpShapeSetBody(shape, body);
  mrb_iv_set(mrb, self, body_sym, body_obj);
  return mrb_nil_value();
}

static mrb_value
shape_get_mass(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpFloat mass;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  mass = cpShapeGetMass(shape);
  return mrb_float_value(mrb, (mrb_float)mass);
}

static mrb_value
shape_set_mass(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  mrb_float mass;
  mrb_get_args(mrb, "f", &mass);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  cpShapeSetMass(shape, (cpFloat)mass);
  return mrb_nil_value();
}

static mrb_value
shape_get_density(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpFloat density;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  density = cpShapeGetDensity(shape);
  return mrb_float_value(mrb, (mrb_float)density);
}

static mrb_value
shape_set_density(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  mrb_float density;
  mrb_get_args(mrb, "f", &density);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  cpShapeSetDensity(shape, (cpFloat)density);
  return mrb_nil_value();
}

static mrb_value
shape_get_moment(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpFloat moment;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  moment = cpShapeGetMoment(shape);
  return mrb_float_value(mrb, (mrb_float)moment);
}

static mrb_value
shape_get_area(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpFloat area;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  area = cpShapeGetArea(shape);
  return mrb_float_value(mrb, (mrb_float)area);
}

static mrb_value
shape_get_center_of_gravity(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpVect center_of_gravity;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  center_of_gravity = cpShapeGetCenterOfGravity(shape);
  return mrb_cp_vect_value(mrb, center_of_gravity);
}

static mrb_value
shape_get_bb(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpBB bb;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  bb = cpShapeGetBB(shape);
  return mrb_cp_bb_value(mrb, bb);
}

static mrb_value
shape_get_sensor(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpBool sensor;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  sensor = cpShapeGetSensor(shape);
  return mrb_bool_value((mrb_bool)sensor);
}

static mrb_value
shape_set_sensor(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  mrb_bool sensor;
  mrb_get_args(mrb, "b", &sensor);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  cpShapeSetSensor(shape, (cpBool)sensor);
  return mrb_nil_value();
}

static mrb_value
shape_get_elasticity(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpFloat elasticity;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  elasticity = cpShapeGetElasticity(shape);
  return mrb_float_value(mrb, (mrb_float)elasticity);
}

static mrb_value
shape_set_elasticity(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  mrb_float elasticity;
  mrb_get_args(mrb, "f", &elasticity);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  cpShapeSetElasticity(shape, (cpFloat)elasticity);
  return mrb_nil_value();
}

static mrb_value
shape_get_friction(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpFloat friction;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  friction = cpShapeGetFriction(shape);
  return mrb_float_value(mrb, (mrb_float)friction);
}

static mrb_value
shape_set_friction(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  mrb_float friction;
  mrb_get_args(mrb, "f", &friction);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  cpShapeSetFriction(shape, (cpFloat)friction);
  return mrb_nil_value();
}

static mrb_value
shape_get_surface_velocity(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpVect surface_velocity;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  surface_velocity = cpShapeGetSurfaceVelocity(shape);
  return mrb_cp_vect_value(mrb, surface_velocity);
}

static mrb_value
shape_set_surface_velocity(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpVect* surface_velocity;
  mrb_get_args(mrb, "d", &surface_velocity, &mrb_cp_vect_type);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  cpShapeSetSurfaceVelocity(shape, *surface_velocity);
  return mrb_nil_value();
}

static mrb_value
shape_get_collision_type(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpCollisionType collision_type;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  collision_type = cpShapeGetCollisionType(shape);
  return mrb_fixnum_value(collision_type);
}

static mrb_value
shape_set_collision_type(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  mrb_int collision_type;
  mrb_get_args(mrb, "i", &collision_type);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  cpShapeSetCollisionType(shape, (cpCollisionType)collision_type);
  return mrb_nil_value();
}

static mrb_value
shape_get_filter(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpShapeFilter filter;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  filter = cpShapeGetFilter(shape);
  return mrb_cp_shape_filter_value(mrb, filter);
}

static mrb_value
shape_set_filter(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpShapeFilter* filter;
  mrb_get_args(mrb, "d", &filter, &mrb_cp_shape_filter_type);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  cpShapeSetFilter(shape, *filter);
  return mrb_nil_value();
}

/*
 * @return [Chipmunk2d::ContactPointSet]
 */
static mrb_value
shape_s_collide(mrb_state* mrb, mrb_value self)
{
  cpShape* a;
  cpShape* b;
  cpContactPointSet contact_point_set;
  mrb_get_args(mrb, "dd", &a, &mrb_cp_shape_type,
               &b, &mrb_cp_shape_type);
  contact_point_set = cpShapesCollide(a, b);
  return mrb_cp_contact_point_set_value(mrb, &contact_point_set);
}

/*
 * @param [Chipmunk2d::Body] body
 * @param [Float] radius
 * @param [Chipmunk2d::Vect] offset
 * @return [self]
 */
static mrb_value
circle_shape_initialize(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpBody* body;
  cpVect* offset;
  mrb_float radius;
  mrb_value body_obj;
  mrb_sym body_sym;
  mrb_cp_shape_cleanup(mrb, self);
  mrb_get_args(mrb, "ofd", &body_obj,
               &radius,
               &offset, &mrb_cp_vect_type);
  body = mrb_cp_get_body_ptr(mrb, body_obj);
  shape = cpCircleShapeNew(body, (cpFloat)radius, *offset);
  body_sym = mrb_intern_lit(mrb, "body");
  mrb_cp_shape_init_bind(mrb, self, shape);
  mrb_iv_set(mrb, self, body_sym, body_obj);
  return self;
}

static mrb_value
circle_shape_get_offset(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpVect offset;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  offset = cpCircleShapeGetOffset(shape);
  return mrb_cp_vect_value(mrb, offset);
}

static mrb_value
circle_shape_get_radius(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpFloat radius;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  radius = cpCircleShapeGetRadius(shape);
  return mrb_float_value(mrb, (mrb_float)radius);
}

/*
 * Chipmunk2d::SegmentShape#initialize(body, a, b, radius)
 * @param [Chipmunk2d::Body] body
 * @param [Chipmunk2d::Vect] a
 * @param [Chipmunk2d::Vect] b
 * @param [Float] radius
 * @return [self]
 */
static mrb_value
segment_shape_initialize(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpBody* body;
  cpVect* a;
  cpVect* b;
  mrb_float radius;
  mrb_value body_obj;
  mrb_sym body_sym;
  mrb_cp_shape_cleanup(mrb, self);
  mrb_get_args(mrb, "oddf", &body_obj,
               &a, &mrb_cp_vect_type,
               &b, &mrb_cp_vect_type,
               &radius);
  body = mrb_cp_get_body_ptr(mrb, body_obj);
  body_sym = mrb_intern_lit(mrb, "body");
  shape = cpSegmentShapeNew(body, *a, *b, (cpFloat)radius);
  mrb_cp_shape_init_bind(mrb, self, shape);
  mrb_iv_set(mrb, self, body_sym, body_obj);
  return self;
}

static mrb_value
segment_shape_set_neighbors(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpVect* prev;
  cpVect* next;
  mrb_get_args(mrb, "dd", &prev, &mrb_cp_vect_type,
               &next, &mrb_cp_vect_type);
  shape = mrb_cp_get_shape_ptr(mrb, self);
  cpSegmentShapeSetNeighbors(shape, *prev, *next);
  return mrb_nil_value();
}

static mrb_value
segment_shape_get_a(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpVect a;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  a = cpSegmentShapeGetA(shape);
  return mrb_cp_vect_value(mrb, a);
}

static mrb_value
segment_shape_get_b(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpVect b;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  b = cpSegmentShapeGetB(shape);
  return mrb_cp_vect_value(mrb, b);
}

static mrb_value
segment_shape_get_normal(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpVect normal;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  normal = cpSegmentShapeGetNormal(shape);
  return mrb_cp_vect_value(mrb, normal);
}

static mrb_value
segment_shape_get_radius(mrb_state* mrb, mrb_value self)
{
  cpShape* shape;
  cpFloat radius;
  shape = mrb_cp_get_shape_ptr(mrb, self);
  radius = cpSegmentShapeGetRadius(shape);
  return mrb_float_value(mrb, (mrb_float)radius);
}

/* @!class Shape
 * @abstract
 */
MRB_CP_EXTERN void
mrb_cp_shape_init(mrb_state* mrb, struct RClass* cp_module)
{
  mrb_cp_shape_class = mrb_define_class_under(mrb, cp_module, "Shape", mrb->object_class);
  mrb_cp_circle_shape_class = mrb_define_class_under(mrb, cp_module, "CircleShape", mrb_cp_shape_class);
  mrb_cp_segment_shape_class = mrb_define_class_under(mrb, cp_module, "SegmentShape", mrb_cp_shape_class);
  MRB_SET_INSTANCE_TT(mrb_cp_shape_class, MRB_TT_DATA);
  MRB_SET_INSTANCE_TT(mrb_cp_circle_shape_class, MRB_TT_DATA);
  MRB_SET_INSTANCE_TT(mrb_cp_segment_shape_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_shape_class, "initialize",        shape_initialize,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "cache_bb",          shape_cache_bb,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "update",            shape_update,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_class, "point_query",       shape_point_query,           MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_shape_class, "segment_query",     shape_segment_query,         MRB_ARGS_REQ(4));
  mrb_define_method(mrb, mrb_cp_shape_class, "collide",           shape_collide,               MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_class, "space",             shape_get_space,             MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "body",              shape_get_body,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "body=",             shape_set_body,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_class, "mass",              shape_get_mass,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "mass=",             shape_set_mass,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_class, "density",           shape_get_density,           MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "density=",          shape_set_density,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_class, "moment",            shape_get_moment,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "area",              shape_get_area,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "center_of_gravity", shape_get_center_of_gravity, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "bb",                shape_get_bb,                MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "sensor",            shape_get_sensor,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "sensor=",           shape_set_sensor,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_class, "elasticity",        shape_get_elasticity,        MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "elasticity=",       shape_set_elasticity,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_class, "friction",          shape_get_friction,          MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "friction=",         shape_set_friction,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_class, "surface_velocity",  shape_get_surface_velocity,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "surface_velocity=", shape_set_surface_velocity,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_class, "collision_type",    shape_get_collision_type,    MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "collision_type=",   shape_set_collision_type,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_shape_class, "filter",            shape_get_filter,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_shape_class, "filter=",           shape_set_filter,            MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_cp_shape_class, "collide",     shape_s_collide,             MRB_ARGS_REQ(2));
  /* CircleShape */
  mrb_define_method(mrb, mrb_cp_circle_shape_class, "initialize", circle_shape_initialize,     MRB_ARGS_REQ(3));
  mrb_define_method(mrb, mrb_cp_circle_shape_class, "offset",     circle_shape_get_offset,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_circle_shape_class, "radius",     circle_shape_get_radius,     MRB_ARGS_NONE());
  /* SegmentShape */
  mrb_define_method(mrb, mrb_cp_segment_shape_class, "initialize",     segment_shape_initialize,     MRB_ARGS_REQ(4));
  mrb_define_method(mrb, mrb_cp_segment_shape_class, "set_neighbors",  segment_shape_set_neighbors,  MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_segment_shape_class, "a",              segment_shape_get_a,          MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_segment_shape_class, "b",              segment_shape_get_b,          MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_segment_shape_class, "normal",         segment_shape_get_normal,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_segment_shape_class, "radius",         segment_shape_get_radius,     MRB_ARGS_NONE());
}
