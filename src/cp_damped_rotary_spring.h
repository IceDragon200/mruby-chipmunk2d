#ifndef MRB_CP_DAMPED_ROTARY_SPRING_H
#define MRB_CP_DAMPED_ROTARY_SPRING_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_common.h"

MRB_CP_EXTERN struct mrb_data_type mrb_cp_damped_rotary_spring_type;

MRB_CP_EXTERN void mrb_cp_damped_rotary_spring_init(mrb_state* mrb, struct RClass* cp_module);

#endif
