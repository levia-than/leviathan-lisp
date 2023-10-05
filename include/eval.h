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
  LVAL_FUN,
  LVAL_SEXPR,
  LVAL_QEXPR
};

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

typedef lval *(*lbuiltin) (lenv *, lval *);

typedef struct lval {
  int type;
  long num;
  /* Error and Symbol types have some string data */
  char* err;
  char* sym;

  /* As soon as we add general symbol in the lang,
     we need add a function pointer for buildin func.*/
  /* Count and Pointer to a list of "lval*" */
  lbuiltin fun;
  int count;
  struct lval** cell;
} lval;

struct lenv{
  int count;
  char **syms;
  lval **vals;
};

lval* lval_num (long);
lval* lval_err (char*);
lval *lval_sym (char*);
lval *lval_sexpr (void);
lval *lval_qexpr (void);
lval *lval_fun (lbuiltin);

void lval_expr_print (lval *, char, char);
void lval_print (lval *);
void lval_println (lval*);

void lval_del (lval *);
lval *lval_add (lval*, lval *);
lval *lval_pop (lval *, int);
lval *lval_take (lval *, int);
lval *lval_copy (lval *);

lval *lval_read_num (mpc_ast_t *);
lval *lval_read (mpc_ast_t *);

void lval_del (lval *);

lenv *lenv_new (void);
void lenv_del (lenv *e);
lval *lenv_get (lenv *, lval *);
void lenv_put (lenv *, lval *, lval *);

lval *lval_eval (lenv *, lval *);
#endif