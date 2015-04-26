#ifndef MRB_CP_POINT_QUERY_INFO_H
#define MRB_CP_POINT_QUERY_INFO_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

void mrb_cp_point_query_info_free(mrb_state *mrb, void *ptr);
extern const struct mrb_data_type mrb_cp_point_query_info_type;
void mrb_cp_point_query_info_init(mrb_state *mrb, struct RClass *cp_module);
mrb_value mrb_cp_point_query_info_value(mrb_state *mrb, cpPointQueryInfo point_query_info);

#endif
