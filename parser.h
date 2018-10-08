/***@<parser.h>***/
#pragma once

extern int      lookahead;
extern FILE    *source;
extern char		lexeme[];

void		mybc(void);
void		fact(void);
void		expr(void);
/*
float		acc;
float	       *stack;
int		stack_top;
*/
