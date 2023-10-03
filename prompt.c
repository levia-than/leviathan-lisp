#include <stdio.h>
#include <stdlib.h>

#include "prompt.h"
// Buffer for User input.
static char input[USER_INPUT_BUFFER];

int main(int argc, char** argv){
	// Print Basic information about the Lisp REPL
  puts ("Leviathan's Lisp Version 0.0.1");
  puts ("Press Ctrl + c to Exit\n");

  // Main loop
  while(1){
		// Output the prompt
      fputs ("lisp #", stdout);
		// Read a line of user input into ouer buffer.
      fgets (input, 2048, stdin);
		// Back print the result.
      printf ("%s", input);
    }
  return 0;
}