#ifndef MRB_CP_POINT_QUERY_INFO_H
#define MRB_CP_POINT_QUERY_INFO_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>
#include "cp_common.h"

MRB_CP_EXTERN  const struct mrb_data_type mrb_cp_point_query_info_type;

static inline cpPointQueryInfo*
mrb_cp_get_point_query_info_ptr(mrb_state* mrb, mrb_value value)
{
  return (cpPointQueryInfo*)mrb_data_get_ptr(mrb, value, &mrb_cp_point_query_info_type);
}

MRB_CP_EXTERN void mrb_cp_point_query_info_init(mrb_state* mrb, struct RClass* cp_module);
MRB_CP_EXTERN mrb_value mrb_cp_point_query_info_value(mrb_state* mrb, cpPointQueryInfo point_query_info);

#endif
