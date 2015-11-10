#include "../../lib/mpc/mpc.h"

mpc_parser_t* Number;
mpc_parser_t* Operator;
mpc_parser_t* Expr;
mpc_parser_t* Lispy;

int parse(char* input, mpc_result_t *r) {

  /* Create some parsers */
  Number = mpc_new("number");
  Operator = mpc_new("operator");
  Expr = mpc_new("expr");
  Lispy = mpc_new("lispy");

  /* Define them with the following language */
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number   : /-?[0-9]+.?/ ;                           \
      operator : '+' | '-' | '*' | '/' | '%' | '^' | /min/ | /max/ ;      \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      lispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
    Number, Operator, Expr, Lispy);

  return mpc_parse("<stdin>", input, Lispy, r);
}

/* Undefine and delete our parsers */
void parser_cleanup() {
  mpc_cleanup(4, Number, Operator, Expr, Lispy);
}
