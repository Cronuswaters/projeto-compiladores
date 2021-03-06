/**@<vm.c>**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errcodes.h>
#include <vm.h>

double acc = 0;
double stack[MAXSTACKSIZE];
int sp = -1;
void execute_op(int op){
	switch(op){
		case '+':
			acc = stack[sp] + acc;
			break;
		case '-':
			acc = stack[sp] - acc;
			break;
		case '*':
			acc = stack[sp] * acc;
			break;
		case '/':
		    /** Checagem de divis�o por zero **/
			if(acc != 0) acc = stack[sp] / acc;
			else fprintf(stderr, "ERROR %d: Division by zero\n",ERR_DIVIDE_BY_ZERO);
			break;
		default:
		    /** Opera��o desconhecida **/
			fprintf(stderr, "Unknown operation\n");
			exit(ERR_UNKNOWN_OP);
	}
	sp--;
}

struct symtable{
    char symbol_name[NAMESIZE];
    double value;
} symbols[MAXSTACKSIZE];

int cur_symbol = -1;

void add_symbol(char *name){
    /**
        Function for adding/updating variable in symbol table

        Runs through symbol table to verify if the variable was already defined
        If it is found, then update the value (assuming new value is in accumulator)
        Otherwise:
        - Checks if cur_symbol is within symbol table bounds (ERR_SYMTABLE_OVERFLOW if not)
        - Increments cur_symbol (cur_symbol points to the last entry in table)
        - Copies name (from parameter) and value (from accumulator) into the new entry
    **/
    int i;
    int found = 0;
    for(i = 0; i < cur_symbol+1; i++){
        if(!strcmp(name, symbols[i].symbol_name)){
            found = 1;
            break;
        }
    }
    if(found) symbols[i].value = acc;
    else{
        if(cur_symbol < MAXSTACKSIZE){
            cur_symbol++;
            strcpy(symbols[cur_symbol].symbol_name, name);
            symbols[cur_symbol].value = acc;
        }
        else{
            fprintf(stderr, "ERROR: Symbol table overflow\n");
            exit(ERR_SYMTABLE_OVERFLOW);
        }
    }
}

void fetch_symbol(char *name){
    /**
        Function for fetching the value of a variable

        Runs through symbol table to find the desired variable (comparing with name, passed as parameter)
        If found:
        - Stacks current accumulator value (TODO: Implement checks against stack overflow
        - Copies the variable's value into accumulator
        - Otherwise, exit with an error message (ERR_VAR_UNDEFINED)
    **/
    int i;
    int found = 0;
    for(i = 0; i < cur_symbol+1; i++){
        if(!strcmp(name, symbols[i].symbol_name)){
            found = 1;
            break;
        }
    }
    if(found){
        stack[++sp] = acc;
        acc = symbols[i].value;
    } else{
        fprintf(stderr, "ERROR: Undefined variable %s\n", name);
        exit(ERR_VAR_UNDEFINED);
    }
}
