/**@<parser.c>**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tokens.h>
#include <lexer.h>
#include <lextoparser.h>
#include <errcodes.h>
#include <vm.h>
#include <parser.h>

#define TRUE 1
#define FALSE 0

char name[MAXIDLEN +1];

void mybc(void){
    /**/lookahead = gettoken(source);/**/
	mybc_start:
    cmd_start:
    if(is_FIRST_expr()){
        acc = 1;
        expr();
        printf("%lg\n",acc);
    }
    if(cmdsep()) goto cmd_start;
    if(!cmd_quit()) goto mybc_start;
}

void fact(void){
	switch (lookahead) {
		case ID:
		    /** ID [ = expr ] **/
		    strcpy(name, lexeme);
		    match(ID);
		    if(lookahead == '='){
		        match('='); expr();

		        add_symbol(name);

		    }
		    else fetch_symbol(name);
		    break;
		case UINT:
        case FLTP:
            acc = atof(lexeme);
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
    int		op_times = 0, op_plus = 0;
	int				isneg = 0;
    int             oplus = 0;
    int             otimes = 0;

    /** abstracts ['+''-'] **/
    oplus = lookahead;
    if (oplus == '+' || oplus == '-') {
    		isneg = (oplus == '-'); /* flag 1 up */
            match(oplus);
    }

T_begin:

F_begin:
    fact();
    /* flag 1 check */
    if(isneg){
    	acc *= -1;
    	isneg = 0;
	}

	// Cosmetic change to match diagram
	/* Flag 3 check */
	if(op_plus){
		execute_op(oplus);
		op_plus = 0;
	}

	/* Flag 2 check */
	if(op_times){
		execute_op(otimes);
		op_times = 0;
	}

    oplus  = lookahead;
    otimes = lookahead;


    if (otimes == '*' || otimes == '/') { // This raises flag 2
        /** Check for stack overflow **/
        if(sp >= MAXSTACKSIZE){
            fprintf(stderr, "ERROR: Stack Overflow\n");
            exit(ERR_STACK_OVERFLOW);
        }
    	stack[++sp] = acc;
        match(otimes);
       	op_times = otimes;
        goto F_begin;
    }

    else if (oplus == '+' || oplus == '-') { // This raises flag 3
        /** Check for stack overflow **/
        if(sp >= MAXSTACKSIZE){
            fprintf(stderr, "ERROR: Stack Overflow\n");
            exit(ERR_STACK_OVERFLOW);
        }
    	stack[++sp] = acc;
        match(oplus);
        op_plus = oplus;
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
