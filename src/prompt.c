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
void add_history(char * unused){}

// For Linux/Mac platform
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv){
	// Print Basic information about the Lisp REPL
  puts ("Leviathan's Lisp Version 0.0.1");
  puts ("Press Ctrl + c to Exit\n");

  // Main loop
  while(1){
		// Output the prompt
      char* input = readline("lisp #");
      add_history (input);
			
		// Back print the result.
      printf ("%s", input);
      free (input);
    }
  return 0;
}