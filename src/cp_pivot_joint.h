#ifndef MRB_CP_PIVOT_JOINT_H
#define MRB_CP_PIVOT_JOINT_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_common.h"

MRB_CP_EXTERN void mrb_cp_pivot_joint_init(mrb_state* mrb, struct RClass* cp_module);

#endif
