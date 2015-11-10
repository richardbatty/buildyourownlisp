#include <stdio.h>
#include <stdlib.h>

#include "../../lib/mpc/mpc.h"
#include "eval.h"
#include "parser.h"

char* interpret(char* input) {
  mpc_result_t r;
  char* result_string = malloc(100);
  if (parse(input, &r)) {
    long result = eval(r.output);
    snprintf(result_string, 100, "%ld", result);
    mpc_ast_delete(r.output);
  } else {
    result_string = mpc_err_string(r.error);
    mpc_err_delete(r.error);
  }
  return result_string;
}
