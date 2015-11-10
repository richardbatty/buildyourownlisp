#ifndef PARSE_H_
#define PARSE_H_
#include "../../lib/mpc/mpc.h"
int parse(char* input, mpc_result_t *r);
#endif

#ifndef PARSER_CLEANUP_H_
#define PARSER_CLEANUP_H_
#include "../../lib/mpc/mpc.h"
int parser_cleanup();
#endif
