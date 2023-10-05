#ifndef _ASSERT_MACRO_H
#define _ASSERT_MACRO_H

#define LASSERT(args, cond, fmt, ...) \
  if (!(cond)) { \
    lval* err = lval_err(fmt, ##__VA_ARGS__); \
    lval_del(args); \
    return err; \
  }

#define LASSERT_TYPE(name, args, pos, in_type)                                   \
  LASSERT (args, (args->cell[pos]->type == in_type),\
  "Function '%s' passed incorrect type for argument %d. ",\
  "Got %s, Expected %s.", name, pos, \
  ltype_name(args->cell[pos]->type), ltype_name(in_type))

#define LASSERT_NUM(name, args, num) \
  LASSERT(args, (args->count == num),\
  "Function 'head' passed too many arguments. ",\
  "Got %i, Expected %i.", args->count, num)

#endif