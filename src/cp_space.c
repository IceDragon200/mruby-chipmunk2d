#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_space.h"
#include "cp_body.h"
#include "cp_bb.h"
#include "cp_constraint.h"
#include "cp_contact_point.h"
#include "cp_shape.h"
#include "cp_shape_filter.h"
#include "cp_segment_query_info.h"
#include "cp_point_query_info.h"
#include "cp_vect.h"
#include "cp_private.h"

static struct RClass* mrb_cp_space_class;
static struct RClass* mrb_cp_post_step_callback_class;

MRB_CP_EXTERN mrb_cp_space_user_data*
mrb_cp_space_user_data_new(mrb_state* mrb)
{
  mrb_cp_space_user_data* user_data =
    (mrb_cp_space_user_data*)mrb_malloc(mrb, sizeof(mrb_cp_space_user_data));
  user_data->space = mrb_nil_value();
  return user_data;
}

MRB_CP_EXTERN void
mrb_cp_space_user_data_free(mrb_state* mrb, mrb_cp_space_user_data* ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

static void
mrb_cp_space_free(mrb_state* mrb, void* ptr)
{
  cpSpace* space = (cpSpace*)ptr;

  if (space) {
    cpSpaceFree(space);
  }
}

static void
post_step_callback_free(mrb_state* mrb, void* ptr)
{
  struct mrb_cp_callback_data* cb_data = (struct mrb_cp_callback_data*)ptr;

  if (cb_data) {
    mrb_free(mrb, cb_data);
  }
}

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_space_type = { "cpSpace", mrb_cp_space_free };
static const struct mrb_data_type post_step_callback_type = { "cpPostStepFunc", post_step_callback_free };

static mrb_value
mrb_cp_collision_handler_value(mrb_state* mrb, cpCollisionHandler* handler)
{
  /* (IceDragon) TODO */
  return mrb_nil_value();
}

/*
 * @return [Chipmunk2d::Space::PostStepCallback]
 */
static mrb_value
mrb_cp_post_step_callback_value(mrb_state* mrb, struct mrb_cp_callback_data* cb_data)
{
  mrb_value result;
  result = mrb_obj_new(mrb, mrb_cp_post_step_callback_class, 0, NULL);
  mrb_data_init(result, cb_data, &post_step_callback_type);
  mrb_iv_set(mrb, result, mrb_intern_lit(mrb, "callback"), cb_data->blk);
  return result;
}

/*
 * Chipmunk2d::Space#initialize
 * @return [self]
 */
static mrb_value
space_initialize(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_cp_space_user_data* user_data;
  space = (cpSpace*)DATA_PTR(self);

  if (space) {
    mrb_cp_space_free(mrb, space);
  }

  space = cpSpaceNew();
  user_data = mrb_cp_space_user_data_new(mrb);
  user_data->space = self;
  cpSpaceSetUserData(space, user_data);
  mrb_data_init(self, space, &mrb_cp_space_type);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "shapes"), mrb_ary_new(mrb));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "bodies"), mrb_ary_new(mrb));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "constraints"), mrb_ary_new(mrb));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "post_step_callbacks"), mrb_ary_new(mrb));
  return self;
}

/*
 * Chipmunk2d::Space#iterations
 * @return [Integer]
 */
static mrb_value
space_get_iterations(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_int iterations;
  space = mrb_cp_get_space_ptr(mrb, self);
  iterations = (mrb_int)cpSpaceGetIterations(space);
  return mrb_fixnum_value(iterations);
}

/*
 * Chipmunk2d::Space#iterations=(iterations)
 * @param [Integer] iterations
 */
static mrb_value
space_set_iterations(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_int iterations;
  mrb_get_args(mrb, "i", &iterations);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceSetIterations(space, iterations);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#gravity
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
space_get_gravity(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpVect gravity;
  space = mrb_cp_get_space_ptr(mrb, self);
  gravity = cpSpaceGetGravity(space);
  return mrb_cp_vect_value(mrb, gravity);
}

/*
 * Chipmunk2d::Space#gravity=(gravity)
 * @param [Chipmunk2d::Vect] gravity
 */
static mrb_value
space_set_gravity(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpVect* gravity;
  mrb_get_args(mrb, "d", &gravity, &mrb_cp_vect_type);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceSetGravity(space, *gravity);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#damping
 * @return [Float]
 */
static mrb_value
space_get_damping(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float damping;
  space = mrb_cp_get_space_ptr(mrb, self);
  damping = (mrb_float)cpSpaceGetDamping(space);
  return mrb_float_value(mrb, damping);
}

/*
 * Chipmunk2d::Space#damping=(damping)
 * @param [Float] damping
 */
static mrb_value
space_set_damping(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float damping;
  mrb_get_args(mrb, "f", &damping);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceSetDamping(space, (cpFloat)damping);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#idle_speed_threshold
 * @return [Float]
 */
static mrb_value
space_get_idle_speed_threshold(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float idle_speed_threshold;
  space = mrb_cp_get_space_ptr(mrb, self);
  idle_speed_threshold = (mrb_float)cpSpaceGetIdleSpeedThreshold(space);
  return mrb_float_value(mrb, idle_speed_threshold);
}

/*
 * Chipmunk2d::Space#idle_speed_threshold=(idle_speed_threshold)
 * @param [Float] idle_speed_threshold
 */
static mrb_value
space_set_idle_speed_threshold(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float idle_speed_threshold;
  mrb_get_args(mrb, "f", &idle_speed_threshold);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceSetIdleSpeedThreshold(space, (cpFloat)idle_speed_threshold);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#sleep_time_threshold
 * @return [Float]
 */
static mrb_value
space_get_sleep_time_threshold(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float sleep_time_threshold;
  space = mrb_cp_get_space_ptr(mrb, self);
  sleep_time_threshold = (mrb_float)cpSpaceGetSleepTimeThreshold(space);
  return mrb_float_value(mrb, sleep_time_threshold);
}

/*
 * Chipmunk2d::Space#sleep_time_threshold=(sleep_time_threshold)
 * @param [Float] sleep_time_threshold
 */
static mrb_value
space_set_sleep_time_threshold(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float sleep_time_threshold;
  mrb_get_args(mrb, "f", &sleep_time_threshold);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceSetSleepTimeThreshold(space, (cpFloat)sleep_time_threshold);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#collision_slop
 * @return [Float]
 */
static mrb_value
space_get_collision_slop(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float collision_slop;
  space = mrb_cp_get_space_ptr(mrb, self);
  collision_slop = (mrb_float)cpSpaceGetCollisionSlop(space);
  return mrb_float_value(mrb, collision_slop);
}

/*
 * Chipmunk2d::Space#collision_slop=(collision_slop)
 * @param [Float] collision_slop
 */
static mrb_value
space_set_collision_slop(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float collision_slop;
  mrb_get_args(mrb, "f", &collision_slop);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceSetCollisionSlop(space, (cpFloat)collision_slop);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#collision_bias
 * @return [Float]
 */
static mrb_value
space_get_collision_bias(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float collision_bias;
  space = mrb_cp_get_space_ptr(mrb, self);
  collision_bias = (mrb_float)cpSpaceGetSleepTimeThreshold(space);
  return mrb_float_value(mrb, collision_bias);
}

/*
 * Chipmunk2d::Space#collision_bias=(collision_bias)
 * @param [Float] collision_bias
 */
static mrb_value
space_set_collision_bias(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float collision_bias;
  mrb_get_args(mrb, "f", &collision_bias);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceSetCollisionBias(space, (cpFloat)collision_bias);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#collision_persistence
 * @return [Integer]
 */
static mrb_value
space_get_collision_persistence(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_int collision_persistence;
  space = mrb_cp_get_space_ptr(mrb, self);
  collision_persistence = (mrb_int)cpSpaceGetCollisionPersistence(space);
  return mrb_fixnum_value(collision_persistence);
}

/*
 * Chipmunk2d::Space#collision_persistence=(collision_persistence)
 * @param [Integer] collision_persistence
 */
static mrb_value
space_set_collision_persistence(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_int collision_persistence;
  mrb_get_args(mrb, "i", &collision_persistence);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceSetCollisionPersistence(space, (cpTimestamp)collision_persistence);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#static_body
 * @return [Chipmunk2d::Body]
 * @nyi
 */
static mrb_value
space_get_static_body(mrb_state* mrb, mrb_value self)
{
  //cpSpace *space;
  //mrb_value body;
  //body = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "static_body"));
  //if (mrb_nil_p(body)) {
  //  space = mrb_cp_get_space_ptr(mrb, self);
  //  body = mrb_cp_body_value(mrb, cpSpaceGetStaticBody(space));
  //  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "static_body"), body);
  //}
  //return body;
  /* IceDragon (TODO) creating the static body is a bit dangerous with mruby's GC */
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#current_time_step
 * @return [Float]
 */
static mrb_value
space_get_current_time_step(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float current_time_step;
  space = mrb_cp_get_space_ptr(mrb, self);
  current_time_step = (mrb_float)cpSpaceGetCurrentTimeStep(space);
  return mrb_float_value(mrb, current_time_step);
}

/*
 * Chipmunk2d::Space#locked?
 * @return [Boolean]
 */
static mrb_value
space_is_locked(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  space = mrb_cp_get_space_ptr(mrb, self);
  return mrb_bool_value(cpSpaceIsLocked(space));
}

/*
 * Chipmunk2d::Space#add_default_collision_handler
 * @return [Chipmunk2d::CollisionHandler]
 */
static mrb_value
space_add_default_collision_handler(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpCollisionHandler* collision_handler;
  space = mrb_cp_get_space_ptr(mrb, self);
  collision_handler = cpSpaceAddDefaultCollisionHandler(space);
  return mrb_cp_collision_handler_value(mrb, collision_handler);
}

/*
 * Chipmunk2d::Space#add_collision_handler(a, b)
 * @param [Integer] a
 * @param [Integer] b
 * @return [Chipmunk2d::CollisionHandler]
 */
static mrb_value
space_add_collision_handler(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpCollisionHandler* collision_handler;
  mrb_int a;
  mrb_int b;
  mrb_get_args(mrb, "ii", &a, &b);
  space = mrb_cp_get_space_ptr(mrb, self);
  collision_handler = cpSpaceAddCollisionHandler(space, a, b);
  return mrb_cp_collision_handler_value(mrb, collision_handler);
}

/*
 * Chipmunk2d::Space#add_wildcard_handler(type)
 * @param [Integer] type
 * @return [Chipmunk2d::CollisionHandler]
 */
static mrb_value
space_add_wildcard_handler(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpCollisionHandler* collision_handler;
  mrb_int type;
  mrb_get_args(mrb, "i", &type);
  space = mrb_cp_get_space_ptr(mrb, self);
  collision_handler = cpSpaceAddWildcardHandler(space, type);
  return mrb_cp_collision_handler_value(mrb, collision_handler);
}

/*
 * Chipmunk2d::Space#add_shape(shape)
 * @param [Chipmunk2d::Shape] shape
 * @return [Chipmunk2d::Shape]
 */
static mrb_value
space_add_shape(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpShape* shape;
  mrb_cp_shape_user_data* user_data;
  mrb_value shape_obj;
  mrb_value shapes;
  mrb_get_args(mrb, "o", &shape_obj);
  shape = mrb_cp_get_shape_ptr(mrb, shape_obj);
  space = mrb_cp_get_space_ptr(mrb, self);
  user_data = (mrb_cp_shape_user_data*)cpShapeGetUserData(shape);
  user_data->space = self;
  mrb_iv_set(mrb, shape_obj, mrb_intern_lit(mrb, "space"), self);
  shapes = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "shapes"));
  mrb_ary_push(mrb, shapes, shape_obj);
  cpSpaceAddShape(space, shape);
  return shape_obj;
}

/*
 * Chipmunk2d::Space#add_body(body)
 * @param [Chipmunk2d::Body] body
 * @return [Chipmunk2d::Body]
 */
static mrb_value
space_add_body(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpBody* body;
  mrb_cp_body_user_data* user_data;
  mrb_value body_obj;
  mrb_value bodies;
  mrb_get_args(mrb, "o", &body_obj);
  body = mrb_cp_get_body_ptr(mrb, body_obj);
  space = mrb_cp_get_space_ptr(mrb, self);
  user_data = (mrb_cp_body_user_data*)cpBodyGetUserData(body);
  user_data->space = self;
  mrb_iv_set(mrb, body_obj, mrb_intern_lit(mrb, "space"), self);
  bodies = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "bodies"));
  mrb_ary_push(mrb, bodies, body_obj);
  cpSpaceAddBody(space, body);
  return body_obj;
}

/*
 * Chipmunk2d::Space#add_constraint(constraint)
 * @param [Chipmunk2d::Constraint] constraint
 * @return [Chipmunk2d::Constraint]
 */
static mrb_value
space_add_constraint(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpConstraint* constraint;
  mrb_cp_constraint_user_data* user_data;
  mrb_value constraint_obj;
  mrb_value constraints;
  mrb_get_args(mrb, "o", &constraint_obj);
  constraint = mrb_cp_get_constraint_ptr(mrb, constraint_obj);
  space = mrb_cp_get_space_ptr(mrb, self);
  user_data = (mrb_cp_constraint_user_data*)cpConstraintGetUserData(constraint);
  user_data->space = self;
  mrb_iv_set(mrb, constraint_obj, mrb_intern_lit(mrb, "space"), self);
  constraints = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "constraints"));
  mrb_ary_push(mrb, constraints, constraint_obj);
  cpSpaceAddConstraint(space, constraint);
  return constraint_obj;
}

/*
 * Chipmunk2d::Space#remove_shape(shape)
 * @param [Chipmunk2d::Shape] shape
 * @return [Chipmunk2d::Shape]
 */
static mrb_value
space_remove_shape(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpShape* shape;
  mrb_cp_shape_user_data* user_data;
  mrb_value shapes;
  mrb_value shape_obj;
  mrb_get_args(mrb, "o", &shape_obj);
  shape = mrb_cp_get_shape_ptr(mrb, shape_obj);
  space = mrb_cp_get_space_ptr(mrb, self);
  user_data = (mrb_cp_shape_user_data*)cpShapeGetUserData(shape);
  user_data->space = mrb_nil_value();
  mrb_iv_set(mrb, shape_obj, mrb_intern_lit(mrb, "space"), mrb_nil_value());
  cpSpaceRemoveShape(space, shape);
  shapes = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "shapes"));
  mrb_cp_ary_delete(mrb, shapes, shape_obj);
  return shape_obj;
}

/*
 * Chipmunk2d::Space#remove_body(body)
 * @param [Chipmunk2d::Body] body
 * @return [Chipmunk2d::Body]
 */
static mrb_value
space_remove_body(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpBody* body;
  mrb_cp_body_user_data* user_data;
  mrb_value bodies;
  mrb_value body_obj;
  mrb_get_args(mrb, "o", &body_obj);
  body = mrb_cp_get_body_ptr(mrb, body_obj);
  space = mrb_cp_get_space_ptr(mrb, self);
  user_data = (mrb_cp_body_user_data*)cpBodyGetUserData(body);
  user_data->space = mrb_nil_value();
  mrb_iv_set(mrb, body_obj, mrb_intern_lit(mrb, "space"), mrb_nil_value());
  cpSpaceRemoveBody(space, body);
  bodies = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "bodies"));
  mrb_cp_ary_delete(mrb, bodies, body_obj);
  return body_obj;
}

/*
 * Chipmunk2d::Space#remove_constraint(constraint)
 * @param [Chipmunk2d::Constraint] constraint
 * @return [Chipmunk2d::Constraint]
 */
static mrb_value
space_remove_constraint(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpConstraint* constraint;
  mrb_cp_constraint_user_data* user_data;
  mrb_value constraints;
  mrb_value constraint_obj;
  mrb_get_args(mrb, "o", &constraint_obj);
  constraint = mrb_cp_get_constraint_ptr(mrb, constraint_obj);
  space = mrb_cp_get_space_ptr(mrb, self);
  user_data = (mrb_cp_constraint_user_data*)cpConstraintGetUserData(constraint);
  user_data->space = mrb_nil_value();
  mrb_iv_set(mrb, constraint_obj, mrb_intern_lit(mrb, "space"), mrb_nil_value());
  cpSpaceRemoveConstraint(space, constraint);
  constraints = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "constraints"));
  mrb_cp_ary_delete(mrb, constraints, constraint_obj);
  return constraint_obj;
}

/*
 * Chipmunk2d::Space#contains_shape?(shape)
 * @param [Chipmunk2d::Shape] shape
 * @return [Boolean]
 */
static mrb_value
space_contains_shape(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpShape* shape;
  cpBool contains_shape;
  mrb_get_args(mrb, "d", &shape, &mrb_cp_shape_type);
  space = mrb_cp_get_space_ptr(mrb, self);
  contains_shape = cpSpaceContainsShape(space, shape);
  return mrb_bool_value(contains_shape);
}

/*
 * Chipmunk2d::Space#contains_body?(body)
 * @param [Chipmunk2d::Body] body
 * @return [Boolean]
 */
static mrb_value
space_contains_body(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpBody* body;
  cpBool contains_body;
  mrb_get_args(mrb, "d", &body, &mrb_cp_body_type);
  space = mrb_cp_get_space_ptr(mrb, self);
  contains_body = cpSpaceContainsBody(space, body);
  return mrb_bool_value(contains_body);
}

/*
 * Chipmunk2d::Space#contains_constraint?(constraint)
 * @param [Chipmunk2d::Constraint] constraint
 * @return [Boolean]
 */
static mrb_value
space_contains_constraint(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpConstraint* constraint;
  cpBool contains_constraint;
  mrb_get_args(mrb, "d", &constraint, &mrb_cp_constraint_type);
  space = mrb_cp_get_space_ptr(mrb, self);
  contains_constraint = cpSpaceContainsConstraint(space, constraint);
  return mrb_bool_value(contains_constraint);
}

/*
 * @yield [Chipmunk2d::Space]
 */
static void
space_post_step_func(cpSpace* space, void* key, void* data)
{
  struct mrb_cp_callback_data* cb_data;
  mrb_cp_space_user_data* user_data;
  cb_data = (struct mrb_cp_callback_data*)data;
  user_data = (mrb_cp_space_user_data*)cpSpaceGetUserData(space);
  mrb_yield(cb_data->mrb, cb_data->blk, user_data->space);
}

/*
 * Chipmunk2d::Space#add_post_step_callback(key, &block)
 * @param [Symbol] key
 * @return [nil]
 */
static mrb_value
space_add_post_step_callback(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_value blk;
  mrb_value pscb;
  mrb_sym key;
  struct mrb_cp_callback_data* cb_data;
  mrb_get_args(mrb, "n&", &key, &blk);
  space = mrb_cp_get_space_ptr(mrb, self);
  cb_data = (struct mrb_cp_callback_data*)mrb_malloc(mrb, sizeof(struct mrb_cp_callback_data));
  cb_data->mrb = mrb;
  cb_data->blk = blk;
  pscb = mrb_cp_post_step_callback_value(mrb, cb_data);
  mrb_ary_push(mrb, mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "post_step_callbacks")), pscb);
  cpSpaceAddPostStepCallback(space, space_post_step_func, (void*)(uintptr_t)key, cb_data);
  return mrb_nil_value();
}

/*
 * @yield [Chipmunk2d::Shape] shape,
 *        [Chipmunk2d::Vect] point,
 *        [Float] distance,
 *        [Chipmunk2d::Vect] gradient
 */
static void
space_point_query_func(cpShape* shape, cpVect point, cpFloat distance, cpVect gradient, void* data)
{
  mrb_cp_shape_user_data* user_data;
  mrb_value ary[4];
  struct mrb_cp_callback_data* cb_data;
  cb_data = (struct mrb_cp_callback_data*)data;
  user_data = (mrb_cp_shape_user_data*)cpShapeGetUserData(shape);
  ary[0] = user_data->shape;
  ary[1] = mrb_cp_vect_value(cb_data->mrb, point);
  ary[2] = mrb_float_value(cb_data->mrb, distance);
  ary[3] = mrb_cp_vect_value(cb_data->mrb, gradient);
  mrb_yield_argv(cb_data->mrb, cb_data->blk, 4, ary);
}

/*
 * Chipmunk2d::Shape#point_query(point, max_distance, filter, &blk)
 * @param [Chipmunk2d::Vect] point
 * @param [Float] max_distance
 * @param [Chipmunk2d::ShapeFilter] filter
 * @yield [Chipmunk2d::Shape] shape,
 *        [Chipmunk2d::Vect] point,
 *        [Float] distance,
 *        [Chipmunk2d::Vect] gradient
 * @return [nil]
 */
static mrb_value
space_point_query(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpVect* point;
  cpShapeFilter* filter;
  struct mrb_cp_callback_data cb_data;
  mrb_value blk;
  mrb_float max_distance;
  mrb_get_args(mrb, "dfd&",
               &point, &mrb_cp_vect_type,
               &max_distance,
               &filter, &mrb_cp_shape_filter_type,
               &blk);
  space = mrb_cp_get_space_ptr(mrb, self);
  cb_data.mrb = mrb;
  cb_data.blk = blk;
  cpSpacePointQuery(space, *point, max_distance, *filter, space_point_query_func, &cb_data);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Shape#point_query_nearest(point, max_distance, filter, out)
 * @param [Chipmunk2d::Vect] point
 * @param [Float] max_distance
 * @param [Chipmunk2d::ShapeFilter] filter
 * @param [Chipmunk2d::PointQueryInfo] out
 * @return [Chipmunk2d::Shape]
 */
static mrb_value
space_point_query_nearest(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpShape* shape;
  cpVect* point;
  cpShapeFilter* filter;
  cpPointQueryInfo* out;
  mrb_cp_shape_user_data* user_data;
  mrb_float max_distance;
  mrb_get_args(mrb, "dfdd",
               &point, &mrb_cp_vect_type,
               &max_distance,
               &filter, &mrb_cp_shape_filter_type,
               &out, &mrb_cp_point_query_info_type);
  space = mrb_cp_get_space_ptr(mrb, self);
  shape = cpSpacePointQueryNearest(space, *point, max_distance, *filter, out);

  if (shape) {
    user_data = (mrb_cp_shape_user_data*)cpShapeGetUserData(shape);

    if (user_data) {
      return user_data->shape;
    }
  }

  return mrb_nil_value();
}

static void
space_segment_query_func(cpShape* shape, cpVect point, cpVect normal, cpFloat alpha, void* data)
{
  mrb_cp_shape_user_data* user_data;
  mrb_value ary[4];
  struct mrb_cp_callback_data* cb_data;
  cb_data = (struct mrb_cp_callback_data*)data;
  user_data = (mrb_cp_shape_user_data*)cpShapeGetUserData(shape);
  ary[0] = user_data->shape;
  ary[1] = mrb_cp_vect_value(cb_data->mrb, point);
  ary[2] = mrb_cp_vect_value(cb_data->mrb, normal);
  ary[3] = mrb_float_value(cb_data->mrb, alpha);
  mrb_yield_argv(cb_data->mrb, cb_data->blk, 4, ary);
}

static mrb_value
space_segment_query(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpVect* start;
  cpVect* end;
  cpShapeFilter* filter;
  struct mrb_cp_callback_data cb_data;
  mrb_float radius;
  mrb_value blk;
  mrb_get_args(mrb, "ddfd&",
               &start, &mrb_cp_vect_type,
               &end, &mrb_cp_vect_type,
               &radius,
               &filter, &mrb_cp_shape_filter_type,
               &blk);
  space = mrb_cp_get_space_ptr(mrb, self);
  cb_data.mrb = mrb;
  cb_data.blk = blk;
  cpSpaceSegmentQuery(space, *start, *end, (cpFloat)radius, *filter, space_segment_query_func, &cb_data);
  return mrb_nil_value();
}

static mrb_value
space_segment_query_first(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpShape* shape;
  cpVect* start;
  cpVect* end;
  cpShapeFilter* filter;
  cpSegmentQueryInfo* out;
  mrb_cp_shape_user_data* user_data;
  mrb_float radius;
  mrb_get_args(mrb, "ddfdd",
               &start, &mrb_cp_vect_type,
               &end, &mrb_cp_vect_type,
               &radius,
               &filter, &mrb_cp_shape_filter_type,
               &out, &mrb_cp_segment_query_info_type);
  space = mrb_cp_get_space_ptr(mrb, self);
  shape = cpSpaceSegmentQueryFirst(space, *start, *end, (cpFloat)radius, *filter, out);

  if (shape) {
    user_data = (mrb_cp_shape_user_data*)cpShapeGetUserData(shape);

    if (user_data) {
      return user_data->shape;
    }
  }

  return mrb_nil_value();
}

/*
 * @yield [Chipmunk2d::Shape] shape
 */
static void
space_bb_query_func(cpShape* shape, void* data)
{
  mrb_cp_shape_user_data* user_data;
  struct mrb_cp_callback_data* cb_data;
  cb_data = (struct mrb_cp_callback_data*)data;
  user_data = (mrb_cp_shape_user_data*)cpShapeGetUserData(shape);
  mrb_yield(cb_data->mrb, cb_data->blk, user_data->shape);
}

/*
 * Chipmunk2d::Shape#bb_query(bb, filter, &blk)
 */
static mrb_value
space_bb_query(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpBB* bb;
  cpShapeFilter* filter;
  struct mrb_cp_callback_data cb_data;
  mrb_value blk;
  mrb_get_args(mrb, "dd&", &bb, &mrb_cp_bb_type,
               &filter, &mrb_cp_shape_filter_type, &blk);
  space = mrb_cp_get_space_ptr(mrb, self);
  cb_data.mrb = mrb;
  cb_data.blk = blk;
  cpSpaceBBQuery(space, *bb, *filter, space_bb_query_func, &cb_data);
  return mrb_nil_value();
}

/*
 * @yield [Chipmunk2d::Shape] shape
 *        [Chipmunk2d::ContactPointSet] points
 */
static void
space_shape_query_func(cpShape* shape, cpContactPointSet* points, void* data)
{
  mrb_cp_shape_user_data* user_data;
  struct mrb_cp_callback_data* cb_data;
  mrb_value argdata[2];
  mrb_int argc;
  cb_data = (struct mrb_cp_callback_data*)data;
  user_data = (mrb_cp_shape_user_data*)cpShapeGetUserData(shape);
  argc = 1;
  argdata[0] = user_data->shape;

  if (points) {
    argc = 2;
    argdata[1] = mrb_cp_contact_point_set_value(cb_data->mrb, points);
  }

  mrb_yield_argv(cb_data->mrb, cb_data->blk, argc, argdata);
}

/*
 * @overload Chipmunk2d::Space#shape_query(shape)
 * @overload Chipmunk2d::Space#shape_query(shape, &block)
 *   @yield [Chipmunk2d::Shape] shape,
 *          [Chipmunk2d::ContactPointSet] points
 */
static mrb_value
space_shape_query(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpShape* shape;
  cpBool result;
  struct mrb_cp_callback_data cb_data;
  mrb_value blk = mrb_nil_value();
  mrb_get_args(mrb, "d|&", &shape, &mrb_cp_shape_type, &blk);
  space = mrb_cp_get_space_ptr(mrb, self);

  if (mrb_nil_p(blk)) {
    result = cpSpaceShapeQuery(space, shape, NULL, NULL);
  } else {
    cb_data.mrb = mrb;
    cb_data.blk = blk;
    result = cpSpaceShapeQuery(space, shape, space_shape_query_func, &cb_data);
  }

  return mrb_bool_value(result);
}

/*
 * @yield [Chipmunk2d::Body]
 */
static void
space_each_body_func(cpBody* body, void* data)
{
  mrb_cp_body_user_data* user_data;
  struct mrb_cp_callback_data* cb_data;
  cb_data = (struct mrb_cp_callback_data*)data;
  user_data = (mrb_cp_body_user_data*)cpBodyGetUserData(body);
  mrb_yield(cb_data->mrb, cb_data->blk, user_data->body);
}

/*
 * Chipmunk2d::Space#each_body
 * @yield [Chipmunk2d::Body]
 * @return [nil]
 */
static mrb_value
space_each_body(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_value blk;
  struct mrb_cp_callback_data cb_data;
  mrb_get_args(mrb, "&", &blk);
  space = mrb_cp_get_space_ptr(mrb, self);
  cb_data.mrb = mrb;
  cb_data.blk = blk;
  cpSpaceEachBody(space, space_each_body_func, &cb_data);
  return mrb_nil_value();
}

/*
 * @yield [Chipmunk2d::Shape]
 */
static void
space_each_shape_func(cpShape* shape, void* data)
{
  mrb_cp_shape_user_data* user_data;
  struct mrb_cp_callback_data* cb_data;
  cb_data = (struct mrb_cp_callback_data*)data;
  user_data = (mrb_cp_shape_user_data*)cpShapeGetUserData(shape);
  mrb_yield(cb_data->mrb, cb_data->blk, user_data->shape);
}

/*
 * Chipmunk2d::Space#each_shape
 * @yield [Chipmunk2d::Shape]
 * @return [nil]
 */
static mrb_value
space_each_shape(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_value blk;
  struct mrb_cp_callback_data cb_data;
  mrb_get_args(mrb, "&", &blk);
  space = mrb_cp_get_space_ptr(mrb, self);
  cb_data.mrb = mrb;
  cb_data.blk = blk;
  cpSpaceEachShape(space, space_each_shape_func, &cb_data);
  return mrb_nil_value();
}

/*
 * @yield [Chipmunk2d::Constraint]
 */
static void
space_each_constraint_func(cpConstraint* constraint, void* data)
{
  mrb_cp_constraint_user_data* user_data;
  struct mrb_cp_callback_data* cb_data;
  cb_data = (struct mrb_cp_callback_data*)data;
  user_data = (mrb_cp_constraint_user_data*)cpConstraintGetUserData(constraint);
  mrb_yield(cb_data->mrb, cb_data->blk, user_data->constraint);
}

/*
 * Chipmunk2d::Space#each_constraint
 * @yield [Chipmunk2d::Constraint]
 * @return [nil]
 */
static mrb_value
space_each_constraint(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_value blk;
  struct mrb_cp_callback_data cb_data;
  mrb_get_args(mrb, "&", &blk);
  space = mrb_cp_get_space_ptr(mrb, self);
  cb_data.mrb = mrb;
  cb_data.blk = blk;
  cpSpaceEachConstraint(space, space_each_constraint_func, &cb_data);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#reindex_static
 */
static mrb_value
space_reindex_static(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceReindexStatic(space);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#reindex_shape(shape)
 * @param [Chipmunk2d::Shape] shape
 */
static mrb_value
space_reindex_shape(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpShape* shape;
  mrb_get_args(mrb, "d", &shape, &mrb_cp_shape_type);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceReindexShape(space, shape);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#reindex_shapes_for_body(body)
 * @param [Chipmunk2d::Body] body
 */
static mrb_value
space_reindex_shapes_for_body(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  cpBody* body;
  mrb_get_args(mrb, "d", &body, &mrb_cp_body_type);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceReindexShapesForBody(space, body);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#use_spatial_hash(dim, count)
 * @param [Float] dim
 * @param [Integer] count
 */
static mrb_value
space_use_spatial_hash(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float dim;
  mrb_int count;
  mrb_get_args(mrb, "fi", &dim, &count);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceUseSpatialHash(space, (cpFloat)dim, (int)count);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Space#step(delta)
 * @param [Float] delta
 */
static mrb_value
space_step(mrb_state* mrb, mrb_value self)
{
  cpSpace* space;
  mrb_float delta;
  mrb_get_args(mrb, "f", &delta);
  space = mrb_cp_get_space_ptr(mrb, self);
  cpSpaceStep(space, (cpFloat)delta);
  return mrb_nil_value();
}

/* @!class Chipmunk2d::Space
 */
MRB_CP_EXTERN void
mrb_cp_space_init(mrb_state* mrb, struct RClass* cp_module)
{
  mrb_cp_space_class = mrb_define_class_under(mrb, cp_module, "Space", mrb->object_class);
  mrb_cp_post_step_callback_class = mrb_define_class_under(mrb, mrb_cp_space_class, "PostStepCallback", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_space_class, MRB_TT_DATA);
  MRB_SET_INSTANCE_TT(mrb_cp_post_step_callback_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_space_class, "initialize",                    space_initialize,                    MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "iterations",                    space_get_iterations,                MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "iterations=",                   space_set_iterations,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "gravity",                       space_get_gravity,                   MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "gravity=",                      space_set_gravity,                   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "damping",                       space_get_damping,                   MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "damping=",                      space_set_damping,                   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "idle_speed_threshold",          space_get_idle_speed_threshold,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "idle_speed_threshold=",         space_set_idle_speed_threshold,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "sleep_time_threshold",          space_get_sleep_time_threshold,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "sleep_time_threshold=",         space_set_sleep_time_threshold,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "collision_slop",                space_get_collision_slop,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "collision_slop=",               space_set_collision_slop,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "collision_bias",                space_get_collision_bias,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "collision_bias=",               space_set_collision_bias,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "collision_persistence",         space_get_collision_persistence,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "collision_persistence=",        space_set_collision_persistence,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "static_body",                   space_get_static_body,               MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "current_time_step",             space_get_current_time_step,         MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "locked?",                       space_is_locked,                     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "add_default_collision_handler", space_add_default_collision_handler, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_space_class, "add_collision_handler",         space_add_collision_handler,         MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_space_class, "add_wildcard_handler",          space_add_wildcard_handler,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "add_shape",                     space_add_shape,                     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "add_body",                      space_add_body,                      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "add_constraint",                space_add_constraint,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "remove_shape",                  space_remove_shape,                  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "remove_body",                   space_remove_body,                   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "remove_constraint",             space_remove_constraint,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "contains_shape?",               space_contains_shape,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "contains_body?",                space_contains_body,                 MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "contains_constraint?",          space_contains_constraint,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "add_post_step_callback",        space_add_post_step_callback,        MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb_cp_space_class, "point_query",                   space_point_query,                   MRB_ARGS_REQ(3) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb_cp_space_class, "point_query_nearest",           space_point_query_nearest,           MRB_ARGS_REQ(4));
  mrb_define_method(mrb, mrb_cp_space_class, "segment_query",                 space_segment_query,                 MRB_ARGS_REQ(4) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb_cp_space_class, "segment_query_first",           space_segment_query_first,           MRB_ARGS_REQ(5));
  mrb_define_method(mrb, mrb_cp_space_class, "bb_query",                      space_bb_query,                      MRB_ARGS_REQ(2) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb_cp_space_class, "shape_query",                   space_shape_query,                   MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb_cp_space_class, "each_body",                     space_each_body,                     MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb_cp_space_class, "each_shape",                    space_each_shape,                    MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb_cp_space_class, "each_constraint",               space_each_constraint,               MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb_cp_space_class, "reindex_static",                space_reindex_static,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "reindex_shape",                 space_reindex_shape,                 MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "reindex_shapes_for_body",       space_reindex_shapes_for_body,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_space_class, "use_spatial_hash",              space_use_spatial_hash,              MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_space_class, "step",                          space_step,                          MRB_ARGS_REQ(1));
}
