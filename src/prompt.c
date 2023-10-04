#include "prompt.h"
#include "mpc.h"
#include "eval.h"

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