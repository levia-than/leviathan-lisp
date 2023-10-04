#ifndef _PROMPT_H
#define _PROMPT_H

#define USER_INPUT_BUFFER 2048

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
#endif