/**@<parser.c>**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tokens.h>
#include <lexer.h>
#include <lextoparser.h>
#include <errcodes.h>
#include <parser.h>

#define TRUE 1
#define FALSE 0

char name[MAXIDLEN +1];

void mybc(void){
    /**/lookahead = gettoken(source);/**/
	mybc_start:
    cmd_start:
    if(is_FIRST_expr()){
        expr();
    }
    if(cmdsep()) goto cmd_start;
    if(!cmd_quit()) goto mybc_start;
}

void fact(void){
	switch (lookahead) {
		case ID:
		    /** ID [ = expr ] **/
		    match(ID);
		    if(lookahead == '='){
		        match('='); expr();
		    }
		    break;
		case UINT:
        case FLTP:
            match(lookahead);
		    break;
		default:
		    /** ( expr ) **/
		    match('('); expr(); match(')');
		}
}

void
expr(void)
{
    int oplus = 0;
    int otimes = 0;

    /** abstracts ['+''-'] **/
    oplus = lookahead;
    if(oplus == '+' || oplus == '-'){
        match(oplus);
    }

T_begin:

F_begin:
    fact();

    oplus = lookahead;
    otimes = lookahead;

    if(otimes == '*' || otimes == '/'){
        match(otimes);
        goto F_begin;
    }

    if(oplus == '+' || oplus == '-'){
        match(oplus);
        goto T_begin;
    }
}

/**
    FIRST(expr) -> num | id | (expr)
**/
int is_FIRST_expr(){
    return ((lookahead == UINT) || (lookahead == FLTP) || (lookahead == ID)
            || (lookahead == '(') || (lookahead == '-') || (lookahead == '+'));
}

int cmd_quit(){
	return lookahead == QUIT;
}

/**
    cmdsep -> ; | '\n'
**/
int cmdsep(){
    if((lookahead == ';') || (lookahead == '\n')){
        match(lookahead);
        return TRUE;
    } else return FALSE;
}
