#ifndef MRB_CP_PRIVATE_H
#define MRB_CP_PRIVATE_H

#include <mruby.h>
#include <mruby/value.h>
#include <chipmunk/chipmunk.h>

/* Since its difficult to keep track of the Chipmunk objects, its an idea
 * to keep the object hitchhiking on the Chipmunk object through its userdata.
 */
struct mrb_cp_callback_data {
  mrb_state *mrb;
  mrb_value blk;
};

static inline mrb_value
mrb_cp_ary_delete(mrb_state *mrb, mrb_value ary, mrb_value obj)
{
  return mrb_funcall(mrb, ary, "delete", 1, obj);
}

/* This is a hack, and may break at any given time */
static inline int
mrb_cp_argc(mrb_state *mrb)
{
  return mrb->c->ci->argc;
}
#endif
