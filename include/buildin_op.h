#ifndef _BUILDIN_OP
#define _BUILDIN_OP

#include "base_lib.h"
#include "eval.h"
lval *builtin (lenv *, lval *, char *);
void lenv_add_builtins (lenv *);
#endif