/**@<vm.h>**/
#pragma once
#define MAXSTACKSIZE 1024
#define NAMESIZE 32

extern double acc;
extern double stack[MAXSTACKSIZE];
extern int sp;

void execute_op(int op);
void add_symbol(char *name);
void fetch_symbol(char *name);
