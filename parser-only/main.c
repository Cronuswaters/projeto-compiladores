/**@<main.c>**/
#include <stdio.h>
#include <stdlib.h>
#include <lexer.h>
#include <parser.h>

FILE           *source,
               *object;

int
main(int argc, char *argv[])
{
	source = stdin;
    object = stdout;

    mybc();

    exit(0);
}
