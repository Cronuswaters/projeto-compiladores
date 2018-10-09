/***@<parser.h>***/
#pragma once

extern int      lookahead;
extern FILE    *source;
extern char		lexeme[];

void		mybc(void);
void		fact(void);
void		expr(void);

int         is_FIRST_expr(void);
int         cmdsep(void);
int         cmd_quit(void);
