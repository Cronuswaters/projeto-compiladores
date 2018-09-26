/**@<lexer.h>**/
#pragma once
#define MAXIDLEN 63

int             gettoken(FILE *tape);

extern char lexeme[];
