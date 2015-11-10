#include <stdbool.h>

#include "../../lib/mpc/mpc.h"

bool node_is_type(mpc_ast_t* ast_node, char* type) {
  return (strstr(ast_node->tag, type)) ? 1 : 0;
}

char* operator(mpc_ast_t* ast_node) {
  /* The operator is always second child. */
  return ast_node->children[1]->contents;
}

mpc_ast_t* nth_child(mpc_ast_t* ast_node, int n) {
  return ast_node->children[n];
}

char* contents(mpc_ast_t* ast_node) {
  return ast_node->contents;
}
