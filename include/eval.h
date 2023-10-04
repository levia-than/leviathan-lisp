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
    LVAL_ERR,
	LVAL_NUM,
	LVAL_SYM,
    LVAL_SEXPR
};

typedef struct lval {
  int type;
  long num;
  /* Error and Symbol types have some string data */
  char* err;
  char* sym;
  /* Count and Pointer to a list of "lval*" */
  int count;
  struct lval** cell;
} lval;

lval* lval_num (long);
lval* lval_err (char*);
lval *lval_sym (char*);
lval *lval_sexpr (void);
void lval_print (lval);
void lval_println (lval);
lval* eval_op (lval, char*, lval);
lval* eval (mpc_ast_t*);
void lval_del (lval*);
#endif