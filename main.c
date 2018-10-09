/**@<main.c>**/
#include <stdio.h>
#include <stdlib.h>
#include <lexer.h>
#include <parser.h>
#include <vm.h>

FILE           *source,
               *object;

int
main(int argc, char *argv[])
{

	//source = fopen("test.mybc", "r");
	source = stdin;
    object = stdout;

/*	stack = (float *)malloc(sizeof(float) + (MAXIDLEN + 1));
	stack_top = 0;
	acc = 0;*/

//    lookahead = gettoken(source);

    mybc();

    exit(0);
}
