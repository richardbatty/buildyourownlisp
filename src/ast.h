#include <stdbool.h>

#include "../lib/mpc/mpc.h"

#ifndef NODE_IS_TYPE_H_
#define NODE_IS_TYPE_H_
bool node_is_type(mpc_ast_t* ast_node, char* type);
#endif

#ifndef OPERATOR_H_
#define OPERATOR_H_
char* operator(mpc_ast_t* ast_node);
#endif

#ifndef NTH_CHILD_H_
#define NTH_CHILD_H_
mpc_ast_t* nth_child(mpc_ast_t* ast_node, int n);
#endif

#ifndef CONTENTS_H_
#define CONTENTS_H_
char* contents(mpc_ast_t* ast_node);
#endif
