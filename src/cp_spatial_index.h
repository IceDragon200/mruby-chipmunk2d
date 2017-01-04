#ifndef MRB_CP_SPATIAL_INDEX_H
#define MRB_CP_SPATIAL_INDEX_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_common.h"

MRB_CP_EXTERN const struct mrb_data_type mrb_cp_spatial_index_type;
MRB_CP_EXTERN void mrb_cp_spatial_index_init(mrb_state* mrb, struct RClass* cp_module);

#endif
