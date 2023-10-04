#include <stdio.h>
#include <stdlib.h>

#include "prompt.h"
#include "mpc.h"

// For Windows platform
#ifdef _WIN32
#include <string.h>
// Buffer for User input.
static char input[USER_INPUT_BUFFER];

char *readline(char* prompt){
  fputs (prompt, stdout);
  fgets (buffer, USER_INPUT_BUFFER, stdin);
  char *cpy = malloc (stdlen(buffer) + 1);
  strcpy (cpy, buffer);
  cpy (strlen(cpy) - 1) = '\0';
  return cpy;
}
void add_history (char *unused){}

// For Linux/Mac platform
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

/* Create a new number type lval */
lval lval_num(long x) {
  lval v;
  v.type = LVAL_NUM;
  v.num = x;
  return v;
}

/* Create a new error type lval */
lval lval_err(int x) {
  lval v;
  v.type = LVAL_ERR;
  v.err = x;
  return v;
}


/* Print an "lval" */
void lval_print(lval v) {
  switch (v.type) {
    /* In the case the type is a number print it */
    /* Then 'break' out of the switch. */
    case LVAL_NUM: printf("%li", v.num); break;

    /* In the case the type is an error */
    case LVAL_ERR:
      /* Check what type of error it is and print it */
      if (v.err == LERR_DIV_ZERO) {
        printf("Error: Division By Zero!");
      }
      if (v.err == LERR_BAD_OP)   {
        printf("Error: Invalid Operator!");
      }
      if (v.err == LERR_BAD_NUM)  {
        printf("Error: Invalid Number!");
      }
    break;
  }
}

/* Print an "lval" followed by a newline */
void lval_println(lval v) { lval_print(v); putchar('\n'); }


/* Now change to lval, because we will treat the err as val to. */
lval eval_op(lval x, char* op, lval y) {

  /* If either value is an error return it */
  if (x.type == LVAL_ERR) { return x; }
  if (y.type == LVAL_ERR) { return y; }

  /* Otherwise do maths on the number values */
  if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
  if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
  if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
  if (strcmp(op, "/") == 0) {
    /* If second operand is zero return error */
    return y.num == 0 
      ? lval_err(LERR_DIV_ZERO) 
      : lval_num(x.num / y.num);
  }

  return lval_err(LERR_BAD_OP);
}

lval eval (mpc_ast_t *t)
{
  // Check Current AST Node if it's a number.
  if (strstr (t->tag, "number"))
    {
      // check if the number conversion works fine.
      errno = 0;
      long x = strtol (t->contents, NULL, 10);
      return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
    }
  /* The operator is always second child! */
  char *op = t->children[1]->contents;
  lval x = eval (t->children[2]);

  int i = 3;
  while(strstr(t->children[i]->tag, "expr")){
      x = eval_op (x, op, eval (t->children[i]));
      i++;
    }
  return x;
}

int main(int argc, char** argv){
	// Print Basic information about the Lisp REPL
  puts ("Leviathan's Lisp Version 0.0.1");
  puts ("Press Ctrl + c to Exit\n");

  // Initialize a bunch of Parsers
  mpc_parser_t *Number = mpc_new ("number");
  mpc_parser_t *Operator = mpc_new ("operator");
  mpc_parser_t *Expr = mpc_new ("expr");
  mpc_parser_t *Lispy = mpc_new ("lispy");

  mpca_lang (MPCA_LANG_DEFAULT, "                                       \
    number      :/-?[0-9]+/ ;                             \
    operator    :'+' | '-' | '*' | '/' ;                  \
    expr        :<number> | '(' <operator> <expr>+ ')' ;  \
    lispy       :/^/ <operator> <expr>+  /$/ ;            \
  ",
    Number, Operator, Expr, Lispy);

  // Main loop
  while(1){
		// Output the prompt
      char* input = readline("lisp #");
      add_history (input);
		// Try to parse the user Input.
      mpc_result_t r;
      if(mpc_parse("<stdin>", input, Lispy, &r)){
          mpc_ast_print (r.output);
          lval result = eval (r.output);
          lval_println (result);
          mpc_ast_delete (r.output);
        }
      else
        {
          mpc_err_print (r.error);
          mpc_err_delete (r.error);
        }
    // Free the input Buffer
      free (input);
    }
    
  mpc_cleanup (4, Number, Operator, Expr, Lispy);
  return 0;
}