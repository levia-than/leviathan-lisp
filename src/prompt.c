#include "prompt.h"
#include "mpc.h"
#include "eval.h"
#include "platform.h"

int main(int argc, char** argv){
	// Print Basic information about the Lisp REPL
  puts ("Leviathan's Lisp Version 0.0.1");
  puts ("Press Ctrl + c to Exit\n");

  // Initialize a bunch of Parsers
  mpc_parser_t *Number = mpc_new ("number");
  mpc_parser_t *Operator = mpc_new ("operator");
  mpc_parser_t *Expr = mpc_new ("expr");
  mpc_parser_t *Lispy = mpc_new ("lispy");

  mpca_lang (MPCA_LANG_DEFAULT, 
  "                                                       \
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