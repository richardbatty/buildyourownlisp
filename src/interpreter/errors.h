#include <stdio.h>
#include <stdlib.h>

#include "interpreter.h"

typedef struct {
  int type;
  long num;
  int err;
} lisp_value;

/* Enumeration of possible lisp_value types */
enum { LISP_VALUE_NUM, LISP_VALUE_ERR };

/* Enumeration of possible error types */
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

#ifndef LISP_VALUE_NUM_H_
#define LISP_VALUE_NUM_H_
lisp_value lisp_value_num(long num);
#endif

#ifndef LISP_VALUE_ERR_H_
#define LISP_VALUE_ERR_H_
lisp_value lisp_value_err(long num);
#endif

#ifndef LISP_VALUE_PRINT_H_
#define LISP_VALUE_PRINT_H_
char* lisp_value_print(lisp_value value);
#endif

#ifndef LISP_VALUE_PRINTLN_H_
#define LISP_VALUE_PRINTLN_H_
void lisp_value_println(lisp_value value);
#endif
