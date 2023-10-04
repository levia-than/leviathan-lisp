#ifndef _PLATFORM_H
#define _PLATFORM_H

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

#endif