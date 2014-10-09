#ifndef MRB_CP_ROTARY_LIMIT_JOINT_H
#define MRB_CP_ROTARY_LIMIT_JOINT_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

void mrb_cp_rotary_limit_joint_free(mrb_state *mrb, void *ptr);

struct mrb_data_type mrb_cp_rotary_limit_joint_type;

void mrb_cp_rotary_limit_joint_init(mrb_state *mrb, struct RClass *cp_module);

#endif
