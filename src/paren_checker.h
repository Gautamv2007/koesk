#ifndef PAREN_CHECKER_H
#define PAREN_CHECKER_H

#include <stdio.h>

void push(char c);
char pop();
char peek();
void check_paren(FILE *file);

#endif

