#ifndef EVAL_H_
#define EVAL_H_
#include "../../lib/mpc/mpc.h"
#include "errors.h"
lisp_value eval(mpc_ast_t* ast_node);
#endif
