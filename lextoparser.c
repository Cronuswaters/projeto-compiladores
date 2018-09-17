/**@<lextoparser.c>**/

#include <stdio.h>
#include <stdlib.h>
#include <lexer.h>
#include <errcodes.h>
#include <lextoparser.h>

int lookahead;

void match(int expected){
	if(lookahead == expected){
		lookahead = gettoken(source);
	} else{
		fprintf(stder, "token mismatch. Exiting...");
		exit(ERR_TOKEN_MISMATCH);
	}
}
