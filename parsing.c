#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib/mpc/mpc.h"

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add_history function */
void add_history(char* unused) {}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#endif

/* Use operator string to see which operation to perform */
long calculate(long x, char* op, long y) {
  if (strcmp(op, "+") == 0) { return x + y; }
  if (strcmp(op, "-") == 0) { return x - y; }
  if (strcmp(op, "*") == 0) { return x * y; }
  if (strcmp(op, "/") == 0) { return x / y; }
  return 0;
}

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

long eval(mpc_ast_t* ast_node) {

  /* If tagged as number return it directly. */
  if (node_is_type(ast_node, "number")) {
    return atoi(contents(ast_node));
  }

  char* op = operator(ast_node);

  /* We store the third child in `result` */
  long result = eval(nth_child(ast_node, 2));

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

int main(int argc, char** argv) {

  /* Create some parsers */
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  /* Define them with the following language */
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number   : /-?[0-9]+.?/ ;                           \
      operator : '+' | '-' | '*' | '/' | '%' ;            \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      lispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
    Number, Operator, Expr, Lispy);

  puts("Lispy Version 0.0.0.0.1");
  puts("From http://buildyourownlisp.com/");
  puts("Press Ctrl+c to Exit\n");

  while(1) {
    char* input = readline("battylisp> ");

    add_history(input);
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
    free(input);
  }

  /* Undefine and delete our parsers */
  mpc_cleanup(4, Number, Operator, Expr, Lispy);

  return 0;
}
