#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_bb.h"
#include "cp_vect.h"

static struct RClass *mrb_cp_bb_class;

void
mrb_cp_bb_free(mrb_state *mrb, void *ptr)
{
  cpBB *mrb_cp_bb = ptr;

  if (mrb_cp_bb) {
    mrb_free(mrb, mrb_cp_bb);
  }
}

const struct mrb_data_type mrb_cp_bb_type = { "cpBB", mrb_cp_bb_free };

/*
 * @return [Chipmunk2d::BB]
 */
mrb_value
mrb_cp_bb_value(mrb_state *mrb, cpBB bb)
{
  cpBB *result_bb;
  mrb_value result;
  mrb_value zero = mrb_float_value(mrb, 0.0);
  mrb_value argv[4] = { zero, zero, zero, zero };
  result = mrb_obj_new(mrb, mrb_cp_bb_class, 4, argv);
  result_bb = mrb_data_get_ptr(mrb, result, &mrb_cp_bb_type);
  *result_bb = bb;
  return result;
}

/* Chipmunk2d::BB#initialize(l, b, r, t)
 * @param [Float] l  left
 * @param [Float] b  bottom
 * @param [Float] r  right
 * @param [Float] t  top
 */
static mrb_value
bb_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float l;
  mrb_float b;
  mrb_float r;
  mrb_float t;
  cpBB *bb;
  mrb_get_args(mrb, "ffff", &l, &b, &r, &t);
  bb = (cpBB*)DATA_PTR(self);
  if (bb) {
    mrb_cp_bb_free(mrb, bb);
  }
  bb = mrb_malloc(mrb, sizeof(cpBB));
  *bb = cpBBNew(l, b, r, t);
  mrb_data_init(self, bb, &mrb_cp_bb_type);
  return self;
}

/* Chipmunk2d::BB#initialize_copy(org)
 * @param [Chipmunk2d::BB] org  original bb
 */
static mrb_value
bb_initialize_copy(mrb_state *mrb, mrb_value self)
{
  cpBB *self_bb;
  cpBB *org_bb;
  mrb_get_args(mrb, "d", &org_bb, &mrb_cp_bb_type);
  self_bb = (cpBB*)DATA_PTR(self);
  if (self_bb) {
    mrb_cp_bb_free(mrb, self_bb);
  }
  self_bb = mrb_malloc(mrb, sizeof(cpBB));
  *self_bb = *org_bb;
  mrb_data_init(self, self_bb, &mrb_cp_bb_type);
  return self;
}

/* Chipmunk2d::BB#l
 * @return [Float]
 */
static mrb_value
bb_get_l(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  return mrb_float_value(mrb, (mrb_float)bb->l);
}

/* Chipmunk2d::BB#l=(l)
 * @param [Float] l
 */
static mrb_value
bb_set_l(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  mrb_float l;
  mrb_get_args(mrb, "f", &l);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  bb->l = (cpFloat)l;
  return mrb_nil_value();
}

/* Chipmunk2d::BB#b
 * @return [Float]
 */
static mrb_value
bb_get_b(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  return mrb_float_value(mrb, (mrb_float)bb->b);
}

/* Chipmunk2d::BB#b=(b)
 * @param [Float] b
 */
static mrb_value
bb_set_b(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  mrb_float b;
  mrb_get_args(mrb, "f", &b);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  bb->b = (cpFloat)b;
  return mrb_nil_value();
}

/* Chipmunk2d::BB#r
 * @return [Float]
 */
static mrb_value
bb_get_r(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  return mrb_float_value(mrb, (mrb_float)bb->r);
}

/* Chipmunk2d::BB#r=(r)
 * @param [Float] r
 */
static mrb_value
bb_set_r(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  mrb_float r;
  mrb_get_args(mrb, "f", &r);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  bb->r = (cpFloat)r;
  return mrb_nil_value();
}

/* Chipmunk2d::BB#t
 * @return [Float]
 */
static mrb_value
bb_get_t(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  return mrb_float_value(mrb, (mrb_float)bb->t);
}

/* Chipmunk2d::BB#t=(t)
 * @param [Float] t
 */
static mrb_value
bb_set_t(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  mrb_float t;
  mrb_get_args(mrb, "f", &t);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  bb->t = (cpFloat)t;
  return mrb_nil_value();
}

/* Chipmunk2d::BB#intersects?(other)
 * @param [Chipmunk2d::BB] other
 * @return [Boolean]
 */
static mrb_value
bb_intersects(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpBB *bb2;
  mrb_get_args(mrb, "d", &bb2, &mrb_cp_bb_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  return mrb_bool_value(cpBBIntersects(*bb, *bb2));
}

/* Chipmunk2d::BB#contains_bb?(other)
 * @param [Chipmunk2d::BB] other
 * @return [Boolean]
 */
static mrb_value
bb_contains_bb(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpBB *bb2;
  mrb_get_args(mrb, "d", &bb2, &mrb_cp_bb_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  return mrb_bool_value(cpBBContainsBB(*bb, *bb2));
}

/* Chipmunk2d::BB#contains_vect?(vect)
 * @param [Chipmunk2d::Vect] vect
 * @return [Boolean]
 */
static mrb_value
bb_contains_vect(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpVect *vect;
  mrb_get_args(mrb, "d", &vect, &mrb_cp_vect_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  return mrb_bool_value(cpBBContainsVect(*bb, *vect));
}

/* Chipmunk2d::BB#merge(other)
 * @param [Chipmunk2d::BB] other
 * @return [Chipmunk2d::BB]
 */
static mrb_value
bb_merge(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpBB *bb2;
  cpBB *bb_result;
  mrb_value result;
  mrb_value zero = mrb_float_value(mrb, 0.0);
  mrb_value result_argv[4] = { zero, zero, zero, zero };
  mrb_get_args(mrb, "d", &bb2, &mrb_cp_bb_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  result = mrb_obj_new(mrb, mrb_cp_bb_class, 4, result_argv);
  bb_result = mrb_data_get_ptr(mrb, result, &mrb_cp_bb_type);
  *bb_result = cpBBMerge(*bb, *bb2);
  return result;
}

/* Chipmunk2d::BB#expand(other)
 * @param [Chipmunk2d::Vect] other
 * @return [Chipmunk2d::BB]
 */
static mrb_value
bb_expand(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpVect *vect;
  cpBB *bb_result;
  mrb_value result;
  mrb_value zero = mrb_float_value(mrb, 0.0);
  mrb_value result_argv[4] = { zero, zero, zero, zero };
  mrb_get_args(mrb, "d", &vect, &mrb_cp_vect_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  result = mrb_obj_new(mrb, mrb_cp_bb_class, 4, result_argv);
  bb_result = mrb_data_get_ptr(mrb, result, &mrb_cp_bb_type);
  *bb_result = cpBBExpand(*bb, *vect);
  return result;
}

/* Chipmunk2d::BB#center
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
bb_center(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpVect center_vect;
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  center_vect = cpBBCenter(*bb);
  return mrb_cp_vect_value(mrb, center_vect);
}

/* Chipmunk2d::BB#area
 * @return [Float]
 */
static mrb_value
bb_area(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpFloat area;
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  area = cpBBArea(*bb);
  return mrb_float_value(mrb, area);
}


/* Chipmunk2d::BB#merged_area(other)
 * @param [Chipmunk2d::BB] other
 * @return [Float]
 */
static mrb_value
bb_merged_area(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpBB *bb2;
  cpFloat merged_area;
  mrb_get_args(mrb, "d", &bb2, &mrb_cp_bb_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  merged_area = cpBBMergedArea(*bb, *bb2);
  return mrb_float_value(mrb, merged_area);
}

/* Chipmunk2d::BB#segment_query(v1, v2)
 * @param [Chipmunk2d::Vect] v1
 * @param [Chipmunk2d::Vect] v2
 * @return [Float]
 */
static mrb_value
bb_segment_query(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpVect *vect1;
  cpVect *vect2;
  cpFloat segment_query;
  mrb_get_args(mrb, "dd", &vect1, &mrb_cp_vect_type,
                          &vect2, &mrb_cp_vect_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  segment_query = cpBBSegmentQuery(*bb, *vect1, *vect2);
  return mrb_float_value(mrb, segment_query);
}

/* Chipmunk2d::BB#intersects_segment?(v1, v2)
 * @param [Chipmunk2d::Vect] v1
 * @param [Chipmunk2d::Vect] v2
 * @return [Float]
 */
static mrb_value
bb_intersects_segment(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpVect *vect1;
  cpVect *vect2;
  cpFloat intersects_segment;
  mrb_get_args(mrb, "dd", &vect1, &mrb_cp_vect_type,
                          &vect2, &mrb_cp_vect_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  intersects_segment = cpBBIntersectsSegment(*bb, *vect1, *vect2);
  return mrb_bool_value(intersects_segment);
}

/* Chipmunk2d::BB#clamp_vect(vect)
 * @param [Chipmunk2d::Vect] vect
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
bb_clamp_vect(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpVect *vect;
  cpVect clamp_vect;
  mrb_get_args(mrb, "d", &vect, &mrb_cp_vect_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  clamp_vect = cpBBClampVect(*bb, *vect);
  return mrb_cp_vect_value(mrb, clamp_vect);
}

/* Chipmunk2d::BB#wrap_vect(vect)
 * @param [Chipmunk2d::Vect] vect
 * @return [Chipmunk2d::Vect]
 */
static mrb_value
bb_wrap_vect(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpVect *vect;
  cpVect wrap_vect;
  mrb_get_args(mrb, "d", &vect, &mrb_cp_vect_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  wrap_vect = cpBBWrapVect(*bb, *vect);
  return mrb_cp_vect_value(mrb, wrap_vect);
}

/* Chipmunk2d::BB#offset(vect)
 * @param [Chipmunk2d::Vect] vect
 * @return [Chipmunk2d::BB]
 */
static mrb_value
bb_offset(mrb_state *mrb, mrb_value self)
{
  cpBB *bb;
  cpVect *vect;
  cpBB *bb_result;
  mrb_value result;
  mrb_value zero = mrb_float_value(mrb, 0.0);
  mrb_value result_argv[4] = { zero, zero, zero, zero };
  mrb_get_args(mrb, "d", &vect, &mrb_cp_vect_type);
  bb = mrb_data_get_ptr(mrb, self, &mrb_cp_bb_type);
  result = mrb_obj_new(mrb, mrb_cp_bb_class, 4, result_argv);
  bb_result = mrb_data_get_ptr(mrb, result, &mrb_cp_bb_type);
  *bb_result = cpBBOffset(*bb, *vect);
  return result;
}

void
mrb_cp_bb_init(mrb_state *mrb, struct RClass *cp_module)
{
  mrb_cp_bb_class = mrb_define_class_under(mrb, cp_module, "BB", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_cp_bb_class, MRB_TT_DATA);
  /* */
  mrb_define_method(mrb, mrb_cp_bb_class, "initialize",          bb_initialize,         MRB_ARGS_REQ(4));
  mrb_define_method(mrb, mrb_cp_bb_class, "initialize_copy",     bb_initialize_copy,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "l",                   bb_get_l,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_bb_class, "l=",                  bb_set_l,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "b",                   bb_get_b,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_bb_class, "b=",                  bb_set_b,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "r",                   bb_get_r,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_bb_class, "r=",                  bb_set_r,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "t",                   bb_get_t,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_bb_class, "t=",                  bb_set_t,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "intersects?",         bb_intersects,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "contains_bb?",        bb_contains_bb,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "contains_vect?",      bb_contains_vect,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "merge",               bb_merge,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "expand",              bb_expand,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "center",              bb_center,             MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_bb_class, "area",                bb_area,               MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_cp_bb_class, "merged_area",         bb_merged_area,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "segment_query",       bb_segment_query,      MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_bb_class, "intersects_segment?", bb_intersects_segment, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_cp_bb_class, "clamp_vect",          bb_clamp_vect,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "wrap_vect",           bb_wrap_vect,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_cp_bb_class, "offset",              bb_offset,             MRB_ARGS_REQ(1));
}
