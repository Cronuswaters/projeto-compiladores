/**@<parser.c>**/
// TODO: Implement checks against stack overflow
#include <stdlib.h>
#include <stdio.h>
#include <tokens.h>
#include <lexer.h>
#include <lextoparser.h>
#include <errcodes.h>
#include <vm.h>
#include <parser.h>

// Lots of untested code below
// char name[MAXIDLEN +1];

void mybc(void){
    /**/lookahead = gettoken(source);/**/
	expr();
}

void fact(void){
	switch (lookahead) {
		case ID:
		    /** ID [ = expr ] **/
		    match(ID);
		    /*
		    strcpy(name, lexeme);
		    */
		    if(lookahead == '='){
		        match('='); expr();
		        /* Untested code
		        add_symbol(name);
		        */
		    }/* Untested code, remove else following this block when testing
		    else fetch_symbol(name);
		    */
		     else ;
		    break;
		case UINT:
        case FLTP:
            acc = atof(lexeme);
            match(lookahead);
		    break;
		default:
		    match('('); expr(); match(')');
		}
}
int		op_times, op_plus;


/* Non-working functions
void acc_add(){
	if(acc != 0){
		stack[stack_top] = acc;
		stack_top++;
	}
	acc = (float)atof(lexeme);
}

void negate(){
	acc *= -1;
	op_negate = 0;
}

void times(){
	if(op_times == '*') acc = stack[stack_top] * acc;
	else acc = stack[stack_top] / acc;
	stack_top--;
	op_times = 0;
}
*/

/*void plus(){
	if(op_plus == '+') acc = stack[stack_top] + acc;
	else acc = stack[stack_top] - acc;
	stack_top--;
	op_plus = 0;
}*/

void
expr(void)
{
	int				isneg = 0;
    int             oplus = 0;
    int             otimes = 0;

    /*int             oplus = lookahead;
    int             otimes = lookahead;*/

    /** abstracts ['+''-'] **/
    if (oplus == '+' || oplus == '-') {
    		isneg = (oplus == '-'); /* flag 1 up */
            match(oplus);
            //if(oplus == '-') op_negate = 1;
            //printf("oper %c",oplus);
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

    /*acc_add();
    if(op_negate) negate();
    if(op_times) times();*/

    oplus  = lookahead;
    otimes = lookahead;


    if (otimes == '*' || otimes == '/') { // This raises flag 2
    	/* untested code
    	stack[++sp] = acc;
    	*/
    	++sp;
    	stack[sp] = acc;
        match(otimes);
       	op_times = otimes;
        goto F_begin;
    }

    //if(op_plus) plus();

    else if (oplus == '+' || oplus == '-') { // This raises flag 3
    	/* untested code
    	stack[++sp] = acc;
    	*/
    	++sp;
    	stack[sp] = acc;
        match(oplus);
        op_plus = oplus;
        goto T_begin;
    }


}
