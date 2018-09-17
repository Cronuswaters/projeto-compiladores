#include <stdlib.h>
#include <stdio.h>
#include <tokens.h>
#include <lexer.h>
#include <parser.h>

extern int      lookahead;
extern char     lexeme[MAXIDLEN + 1];
extern FILE    *source;

int             lookahead;

void
match(int expected)
{
    if (lookahead == expected) {
        lookahead = gettoken(source);
    } else {
        fprintf(stderr, "token mismatch... exiting\n");
        exit(-2);
    }
}

void
expr(void)
{
    int             oplus = lookahead;
    int             otimes = lookahead;

T_begin:

F_begin:

    switch (lookahead) {
    case ID:
        match(ID);
        break;
    case UINT:
        match(UINT);
        break;
    case FLTP:
        match(FLTP);
        break;
    default:
        match('('); expr(); match(')');
    }

    if (otimes == '*' || otimes == '/') {
        match(otimes);
        goto F_begin;
    }

    if (oplus == '+' || oplus == '-') {
            match(oplus);
            goto T_begin;            
    }
}
