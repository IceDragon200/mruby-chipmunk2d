#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_body.h"
#include "cp_arbiter.h"
#include "cp_constraint.h"
#include "cp_vect.h"
#include "cp_shape.h"
#include "cp_private.h"

static struct RClass *mrb_cp_body_class;

mrb_cp_body_user_data*
mrb_cp_body_user_data_new(mrb_state *mrb)
{
  mrb_cp_body_user_data *user_data =
    mrb_malloc(mrb, sizeof(mrb_cp_body_user_data));

  user_data->body = mrb_nil_value();
  user_data->space = mrb_nil_value();

  return user_data;
}

void
mrb_cp_body_user_data_free(mrb_state *mrb, mrb_cp_body_user_data *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}


void
mrb_cp_body_free(mrb_state *mrb, void *ptr)
{
  cpBody *body = ptr;
  mrb_cp_body_user_data *user_data;
  if (body) {
    user_data = cpBodyGetUserData(body);
    if (user_data) {
      mrb_cp_body_user_data_free(mrb, user_data);
    }
    cpBodyFree(body);
  }
}

struct mrb_data_type mrb_cp_body_type = { "Chipmunk2d::Body", mrb_cp_body_free };

void
mrb_cp_body_cleanup(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  body = (cpBody*)DATA_PTR(self);
  if (body) {
    mrb_cp_body_free(mrb, body);
  }
  DATA_PTR(self) = NULL;
}

static void
body_initialize_userdata(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  mrb_cp_body_user_data *user_data;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  user_data = mrb_cp_body_user_data_new(mrb);
  user_data->body = self;
  cpBodySetUserData(body, user_data);
}

/*
 * @return [Chipmunk2d::Body]
 */
mrb_value
mrb_cp_body_value(mrb_state *mrb, cpBody *body)
{
  mrb_value body_obj;
  mrb_value argv[2];
  argv[0] = mrb_float_value(mrb, 100.0);
  argv[1] = mrb_float_value(mrb, 1.0);
  body_obj = mrb_obj_new(mrb, mrb_cp_body_class, 2, argv);
  mrb_cp_body_cleanup(mrb, body_obj);
  mrb_data_init(body_obj, body, &mrb_cp_body_type);
  body_initialize_userdata(mrb, body_obj);
  return body_obj;
}

/*
 * Chipmunk2d::Body#initialize(mass, moment)
 * @param [Float] mass
 * @param [Float] moment
 * @return [self]
 */
static mrb_value
body_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float mass, moment;
  cpBody *body;
  mrb_get_args(mrb, "ff", &mass, &moment);
  mrb_cp_body_cleanup(mrb, self);
  body = cpBodyNew(mass, moment);
  mrb_data_init(self, body, &mrb_cp_body_type);
  body_initialize_userdata(mrb, self);
  return self;
}

/*
 * Chipmunk2d::Body#destroy
 * @return [self]
 */
static mrb_value
body_destroy(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodyDestroy(body);
  return self;
}

/*
 * Chipmunk2d::Body#activate
 * @return [self]
 */
static mrb_value
body_activate(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodyActivate(body);
  return self;
}

/*
 * @param [Chipmunk2d::Shape] filter
 */
static mrb_value
body_activate_static(mrb_state *mrb, mrb_value self)
{
  cpShape *filter;
  cpBody *body;
  mrb_get_args(mrb, "d", &filter, &mrb_cp_shape_type);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodyActivateStatic(body, filter);
  return self;
}

/*
 * Chipmunk2d::Body#sleep
 * @return [self]
 */
static mrb_value
body_sleep(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySleep(body);
  return self;
}

/*
 * Chipmunk2d::Body#sleep_with_group(group)
 * @param [Chipmunk2d::Body] group
 */
static mrb_value
body_sleep_with_group(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpBody *group;
  mrb_get_args(mrb, "d", &group, &mrb_cp_body_type);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySleepWithGroup(body, group);
  return self;
}

/*
 * Chipmunk2d::Body#sleeping?
 * @return [Boolean] is this body sleeping?
 */
static mrb_value
body_is_sleeping(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpBool sleeping;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  sleeping = cpBodyIsSleeping(body);
  return mrb_bool_value(sleeping);
}

/*
 * Chipmunk2d::Body#type
 * @return [Chipmunk2d::Body::TYPE_*]
 */
static mrb_value
body_get_type(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpBodyType body_type;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  body_type = cpBodyGetType(body);
  return mrb_fixnum_value(body_type);
}

/*
 * Chipmunk2d::Body#type=(body_type)
 * @param [Chipmunk2d::Body::TYPE_*] body_type
 */
static mrb_value
body_set_type(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  mrb_int body_type;
  mrb_get_args(mrb, "i", &body_type);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySetType(body, (cpBodyType)body_type);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Body#space
 * @return [Chipmunk2d::Space]
 */
static mrb_value
body_get_space(mrb_state *mrb, mrb_value self)
{
  mrb_sym space_sym;

  space_sym = mrb_intern_cstr(mrb, "space");
  return mrb_iv_get(mrb, self, space_sym);
}

/*
 * Chipmunk2d::Body#mass
 * @return [Float]
 */
static mrb_value
body_get_mass(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpFloat mass;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  mass = cpBodyGetMass(body);
  return mrb_float_value(mrb, mass);
}

/*
 * Chipmunk2d::Body#mass=(mass)
 * @param [Float] mass
 */
static mrb_value
body_set_mass(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  mrb_float mass;
  mrb_get_args(mrb, "f", &mass);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySetMass(body, mass);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Body#moment
 * @return [Float]
 */
static mrb_value
body_get_moment(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpFloat moment;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  moment = cpBodyGetMoment(body);
  return mrb_float_value(mrb, moment);
}

/*
 * Chipmunk2d::Body#moment=(moment)
 * @param [Float] moment
 */
static mrb_value
body_set_moment(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  mrb_float moment;
  mrb_get_args(mrb, "f", &moment);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySetMoment(body, moment);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Body#position
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
body_get_position(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect position;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  position = cpBodyGetPosition(body);
  return mrb_cp_vect_value(mrb, position);
}

/*
 * Chipmunk2d::Body#position=(position)
 * @param [Chipmunk2d::Vect] position
 */
static mrb_value
body_set_position(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect *position;
  mrb_get_args(mrb, "d", &position);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySetPosition(body, *position);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Body#center_of_gravity
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
body_get_center_of_gravity(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect center_of_gravity;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  center_of_gravity = cpBodyGetCenterOfGravity(body);
  return mrb_cp_vect_value(mrb, center_of_gravity);
}

/*
 * Chipmunk2d::Body#center_of_gravity=(center_of_gravity)
 * @param [Chipmunk2d::Vect] center_of_gravity
 */
static mrb_value
body_set_center_of_gravity(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect *center_of_gravity;
  mrb_get_args(mrb, "d", &center_of_gravity);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySetCenterOfGravity(body, *center_of_gravity);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Body#velocity
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
body_get_velocity(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect velocity;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  velocity = cpBodyGetVelocity(body);
  return mrb_cp_vect_value(mrb, velocity);
}

/*
 * Chipmunk2d::Body#velocity=(velocity)
 * @param [Chipmunk2d::Vect] velocity
 */
static mrb_value
body_set_velocity(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect *velocity;
  mrb_get_args(mrb, "d", &velocity);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySetVelocity(body, *velocity);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Body#force
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
body_get_force(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect force;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  force = cpBodyGetForce(body);
  return mrb_cp_vect_value(mrb, force);
}

/*
 * Chipmunk2d::Body#force=(force)
 * @param [Chipmunk2d::Vect] force
 */
static mrb_value
body_set_force(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect *force;
  mrb_get_args(mrb, "d", &force);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySetForce(body, *force);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Body#angle
 * @return [Float]
 */
static mrb_value
body_get_angle(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpFloat angle;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  angle = cpBodyGetAngle(body);
  return mrb_float_value(mrb, (mrb_float)angle);
}

/*
 * Chipmunk2d::Body#angle=(angle)
 * @param [Float] angle
 */
static mrb_value
body_set_angle(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  mrb_float angle;
  mrb_get_args(mrb, "f", &angle);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySetAngle(body, (cpFloat)angle);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Body#angular_velocity
 * @return [Float]
 */
static mrb_value
body_get_angular_velocity(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpFloat angular_velocity;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  angular_velocity = cpBodyGetAngularVelocity(body);
  return mrb_float_value(mrb, (mrb_float)angular_velocity);
}

/*
 * Chipmunk2d::Body#angular_velocity=(angular_velocity)
 * @param [Float] angular_velocity
 */
static mrb_value
body_set_angular_velocity(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  mrb_float angular_velocity;
  mrb_get_args(mrb, "f", &angular_velocity);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySetAngularVelocity(body, (cpFloat)angular_velocity);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Body#torque
 * @return [Float]
 */
static mrb_value
body_get_torque(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpFloat torque;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  torque = cpBodyGetTorque(body);
  return mrb_float_value(mrb, (mrb_float)torque);
}

/*
 * Chipmunk2d::Body#torque=(torque)
 * @param [Float] torque
 */
static mrb_value
body_set_torque(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  mrb_float torque;
  mrb_get_args(mrb, "f", &torque);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cpBodySetTorque(body, (cpFloat)torque);
  return mrb_nil_value();
}

/*
 * Chipmunk2d::Body#rotation(point)
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
body_get_rotation(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect rotation;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  rotation = cpBodyGetRotation(body);
  return mrb_cp_vect_value(mrb, rotation);
}

/*
 * Chipmunk2d::Body#local_to_world(point)
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
body_local_to_world(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect *point;
  cpVect world_point;
  mrb_get_args(mrb, "d", &point, &mrb_cp_vect_type);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  world_point = cpBodyLocalToWorld(body, *point);
  return mrb_cp_vect_value(mrb, world_point);
}

/*
 * Chipmunk2d::Body#world_to_local(point)
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
body_world_to_local(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpVect *point;
  cpVect local_point;
  mrb_get_args(mrb, "d", &point, &mrb_cp_vect_type);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  local_point = cpBodyWorldToLocal(body, *point);
  return mrb_cp_vect_value(mrb, local_point);
}

/*
 * Chipmunk2d::Body#kinetic_energy
 * @return [Float]
 */
static mrb_value
body_get_kinetic_energy(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  cpFloat kinetic_energy;
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  kinetic_energy = cpBodyKineticEnergy(body);
  return mrb_float_value(mrb, (mrb_float)kinetic_energy);
}

static void
body_each_shape_func(cpBody *body, cpShape *shape, void *data)
{
  struct mrb_cp_body_user_data *body_user_data;
  struct mrb_cp_shape_user_data *shape_user_data;
  struct mrb_cp_callback_data *cb_data;
  mrb_value argv[2];
  cb_data = data;
  body_user_data = cpBodyGetUserData(body);
  shape_user_data = cpShapeGetUserData(shape);
  argv[0] = body_user_data->body;
  argv[1] = shape_user_data->shape;
  mrb_yield_argv(cb_data->mrb, cb_data->blk, 2, argv);
}

/*
 * Chipmunk2d::Body#each_shape
 * @yield body, shape
 */
static mrb_value
body_each_shape(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  mrb_value blk;
  struct mrb_cp_callback_data cb_data;
  mrb_get_args(mrb, "&", &blk);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cb_data.mrb = mrb;
  cb_data.blk = blk;
  cpBodyEachShape(body, body_each_shape_func, &cb_data);
  return self;
}

static void
body_each_constraint_func(cpBody *body, cpConstraint *constraint, void *data)
{
  struct mrb_cp_body_user_data *body_user_data;
  struct mrb_cp_callback_data *cb_data;
  mrb_value argv[2];
  cb_data = data;
  body_user_data = cpBodyGetUserData(body);
  argv[0] = body_user_data->body;
  argv[1] = mrb_cp_constraint_get_mrb_obj(cb_data->mrb, constraint);
  mrb_yield_argv(cb_data->mrb, cb_data->blk, 2, argv);
}

/*
 * Chipmunk2d::Body#each_constraint
 * @yield body, constraint
 */
static mrb_value
body_each_constraint(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  struct mrb_cp_callback_data cb_data;
  mrb_value blk;
  mrb_get_args(mrb, "&", &blk);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cb_data.mrb = mrb;
  cb_data.blk = blk;
  cpBodyEachConstraint(body, body_each_constraint_func, &cb_data);
  return self;
}

static void
body_each_arbiter_func(cpBody *body, cpArbiter *arbiter, void *data)
{
  struct mrb_cp_body_user_data *body_user_data;
  struct mrb_cp_callback_data *cb_data;
  mrb_value argv[2];
  cb_data = data;
  body_user_data = cpBodyGetUserData(body);
  argv[0] = body_user_data->body;
  argv[1] = mrb_cp_arbiter_get_mrb_obj(cb_data->mrb, arbiter);
  mrb_yield_argv(cb_data->mrb, cb_data->blk, 2, argv);
}

/*
 * Chipmunk2d::Body#each_arbiter
 * @yield body, arbiter
 */
static mrb_value
body_each_arbiter(mrb_state *mrb, mrb_value self)
{
  cpBody *body;
  struct mrb_cp_callback_data cb_data;
  mrb_value blk;
  mrb_get_args(mrb, "&", &blk);
  body = mrb_data_get_ptr(mrb, self, &mrb_cp_body_type);
  cb_data.mrb = mrb;
  cb_data.blk = blk;
  cpBodyEachArbiter(body, body_each_arbiter_func, &cb_data);
  return self;
}

void
mrb_cp_body_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_body_class = mrb_define_class_under(mrb, cp_module, "Body", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_body_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_cp_body_class, "initialize",         body_initialize,            MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_body_class, "destroy",            body_destroy,               MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "activate",           body_activate,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "activate_static",    body_activate_static,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "sleep",              body_sleep,                 MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "sleep_with_group",   body_sleep_with_group,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "sleeping?",          body_is_sleeping,           MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "type",               body_get_type,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "type=",              body_set_type,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "space",              body_get_space,             MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "mass",               body_get_mass,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "mass=",              body_set_mass,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "moment",             body_get_moment,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "moment=",            body_set_moment,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "position",           body_get_position,          MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "position=",          body_set_position,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "center_of_gravity",  body_get_center_of_gravity, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "center_of_gravity=", body_set_center_of_gravity, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "velocity",           body_get_velocity,          MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "velocity=",          body_set_velocity,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "force",              body_get_force,             MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "force=",             body_set_force,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "angle",              body_get_angle,             MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "angle=",             body_set_angle,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "angular_velocity",   body_get_angular_velocity,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "angular_velocity=",  body_set_angular_velocity,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "torque",             body_get_torque,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "torque=",            body_set_torque,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "rotation",           body_get_rotation,          MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_body_class, "local_to_world",     body_local_to_world,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "world_to_local",     body_world_to_local,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "kinetic_energy",     body_get_kinetic_energy,    MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_cp_body_class, "each_shape",         body_each_shape,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "each_constraint",    body_each_constraint,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_body_class, "each_arbiter",       body_each_arbiter,          MRB_ARGS_REQ(1));

  mrb_define_const(mrb, mrb_cp_body_class, "TYPE_DYNAMIC",   mrb_fixnum_value(CP_BODY_TYPE_DYNAMIC));
  mrb_define_const(mrb, mrb_cp_body_class, "TYPE_KINEMATIC", mrb_fixnum_value(CP_BODY_TYPE_KINEMATIC));
  mrb_define_const(mrb, mrb_cp_body_class, "TYPE_STATIC",    mrb_fixnum_value(CP_BODY_TYPE_STATIC));
}
