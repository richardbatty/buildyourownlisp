#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>

#include "interpreter/interpreter.h"

int main(int argc, char** argv) {
  puts("Lispy Version 0.0.0.0.1");
  puts("From http://buildyourownlisp.com/");
  puts("Press Ctrl+c to Exit\n");

  while(1) {
    char* input = readline("battylisp> ");
    add_history(input);
    puts(interpret(input));
    free(input);
  }

  return 0;
}
