#ifndef MRB_CP_POLY_SHAPE_H
#define MRB_CP_POLY_SHAPE_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <chipmunk/chipmunk.h>

void mrb_cp_poly_shape_free(mrb_state *mrb, void *ptr);
void mrb_cp_poly_shape_init(mrb_state *mrb, struct RClass *cp_module);

#endif
