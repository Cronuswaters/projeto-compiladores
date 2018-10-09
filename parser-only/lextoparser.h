/**@<lextoparser.h>**/
#pragma once
extern int      lookahead;
extern FILE    *source;
int		lookahead;
void		match(int expected);
