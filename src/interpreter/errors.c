#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

lisp_value lisp_value_num(long num) {
  lisp_value value;
  value.type = LISP_VALUE_NUM;
  value.num = num;
  return value;
}

lisp_value lisp_value_err(long num) {
  lisp_value value;
  value.type = LISP_VALUE_ERR;
  value.err = num;
  return value;
}

char* lisp_value_print(lisp_value value) {
  char* value_string = malloc(100);
  switch (value.type) {
    case LISP_VALUE_NUM:
      snprintf(value_string, 100, "%ld", value.num);
      break;

    case LISP_VALUE_ERR:
      if (value.err == LERR_DIV_ZERO) {
        value_string = "Error: Division by zero!";
      }
      if (value.err == LERR_BAD_OP) {
        value_string = "Error: Invalid Operator!";
      }
      if (value.err == LERR_BAD_NUM)  {
        value_string = "Error: Invalid Number!";
      }
      break;
  }
  return value_string;
}

void lisp_value_println(lisp_value value) {
  lisp_value_print(value); putchar('\n');
}
