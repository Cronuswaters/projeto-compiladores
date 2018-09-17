/**@<lextoparser.h>**/
#pragma once
extern int      lookahead;
extern char     lexeme[MAXIDLEN + 1];
extern FILE    *source;
int		lookahead;
void		match(int expected);
