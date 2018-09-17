/**@<main.c>**/
#include <stdio.h>
#include <stdlib.h>
#include <lexer.h>
#include <parser.h>

FILE           *source,
               *object;
extern float acc;
extern float *stack;
extern int stack_top;

int
main(void)
{
	
    source = stdin;
    object = stdout;

	stack = (float *)malloc(sizeof(float) + (MAXIDLEN + 1));
	stack_top = 0;
	acc = 0;

    lookahead = gettoken(source);

    expr();
    
    printf("%f\n",acc);

    exit(0);
}
