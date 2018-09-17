/**@<vm.c>**/
#include <errcodes.h>
#include <vm.h>

double acc = 0;
double stack[MAXSTACKSIZE];
int sp = -1;

void execute_op(int op){
	// salvar o estado do acumulador na pilha
	// ... or not
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
			acc = stack[sp] / acc;
			break;
		default:
			fprintf(stderr, "Unknown operation");
			exit(ERR_UNKNOWN_OP);
	}
	sp--;
}
