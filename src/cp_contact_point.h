#ifndef MRB_CP_CONTACT_POINT_H
#define MRB_CP_CONTACT_POINT_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

mrb_value mrb_cp_contact_point_set_value(mrb_state *mrb, cpContactPointSet *points);

void mrb_cp_contact_point_init(mrb_state *mrb, struct RClass *cp_module);

#endif
