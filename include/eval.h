#ifndef _EVAL_H
#define _EVAL_H
#include "base_lib.h"

enum
{
	LERR_DIV_ZERO,
	LERR_BAD_OP,
	LERR_BAD_NUM
};

enum
{
	LVAL_NUM,
	LVAL_ERR
};

typedef struct{
  int type;
  long num;
  int err;
} lval;

lval lval_num (long);
lval lval_err (int);
void lval_print (lval);
void lval_println (lval);
lval eval_op (lval, char*, lval);
lval eval (mpc_ast_t*);

#endif