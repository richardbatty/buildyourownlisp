#include "../../lib/mpc/mpc.h"
#include "ast.h"
#include "errors.h"

/* Use operator string to see which operation to perform */
lisp_value calculate(lisp_value x, char* op, lisp_value y) {
  if (x.type == LISP_VALUE_ERR) { return x; }
  if (y.type == LISP_VALUE_ERR) { return y; }

  if (strcmp(op, "+") == 0) { return lisp_value_num(x.num + y.num); }
  if (strcmp(op, "-") == 0) { return lisp_value_num(x.num - y.num); }
  if (strcmp(op, "*") == 0) { return lisp_value_num(x.num * y.num); }
  if (strcmp(op, "/") == 0) {
    return y.num == 0
      ? lisp_value_err(LERR_DIV_ZERO)
      : lisp_value_num(x.num / y.num);
    }
  if (strcmp(op, "%") == 0) { return lisp_value_num(x.num % y.num); }
  if (strcmp(op, "^") == 0) { return lisp_value_num(pow(x.num, y.num)); }
  if (strcmp(op, "min") == 0) { return lisp_value_num(fmin(x.num, y.num)); }
  if (strcmp(op, "max.num") == 0) { return lisp_value_num(fmax(x.num, y.num)); }
  return lisp_value_err(LERR_BAD_OP);
}

lisp_value calculate_unary(char* op, lisp_value x) {
  if (strcmp(op, "-") == 0) { return lisp_value_num(- x.num); }
  return lisp_value_err(LERR_BAD_OP);
}

lisp_value eval(mpc_ast_t* ast_node) {

  /* If tagged as number return it directly. */
  if (node_is_type(ast_node, "number")) {
    errno = 0;
    long x = strtol(contents(ast_node), NULL, 10);
    return errno != ERANGE ? lisp_value_num(x) : lisp_value_err(LERR_BAD_NUM);
  }

  char* op = operator(ast_node);

  /* TODO: Create an array of operands to manipulate rather than
  the awkward off-by-one ast node once I know more about pointers */
  /* We store the third child in `result` */
  lisp_value result = eval(nth_child(ast_node, 2));

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
