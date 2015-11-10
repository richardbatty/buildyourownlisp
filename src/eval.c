#include "../lib/mpc/mpc.h"
#include "ast.h"

/* Use operator string to see which operation to perform */
long calculate(long x, char* op, long y) {
  if (strcmp(op, "+") == 0) { return x + y; }
  if (strcmp(op, "-") == 0) { return x - y; }
  if (strcmp(op, "*") == 0) { return x * y; }
  if (strcmp(op, "/") == 0) { return x / y; }
  if (strcmp(op, "%") == 0) { return x % y; }
  if (strcmp(op, "^") == 0) { return pow(x, y); }
  if (strcmp(op, "min") == 0) { return fmin(x, y); }
  if (strcmp(op, "max") == 0) { return fmax(x, y); }
  return 0;
}

long calculate_unary(char* op, long x) {
  if (strcmp(op, "-") == 0) { return - x; }
  return 0;
}

long eval(mpc_ast_t* ast_node) {

  /* If tagged as number return it directly. */
  if (node_is_type(ast_node, "number")) {
    return atoi(contents(ast_node));
  }

  char* op = operator(ast_node);

  /* TODO: Create an array of operands to manipulate rather than
  the awkward off-by-one ast node once I know more about pointers */
  /* We store the third child in `result` */
  long result = eval(nth_child(ast_node, 2));

  if (!node_is_type(nth_child(ast_node, 3), "expr")) {
    result = calculate_unary(op, result);
  }

  /* Iterate the remaining children and combining. */
  int i = 3;
  while (node_is_type(nth_child(ast_node, i), "expr")) {
    result = calculate(result,
                       op,
                       eval(nth_child(ast_node, i)));
    i++;
  }

  return result;
}
