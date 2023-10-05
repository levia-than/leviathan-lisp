#ifndef _BUILDIN_OP
#define _BUILDIN_OP

#include "base_lib.h"
#include "eval.h"
lval *builtin (lenv *, lval *, char *);
lval *builtin_eval (lenv *, lval *);
lval *builtin_load (lenv *, lval *);
void lenv_add_builtins (lenv *);
#endif