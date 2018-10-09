/**@<lexer.c>::**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <tokens.h>
#include <lexer.h>

char            lexeme[MAXIDLEN + 1];

void
skipspaces(FILE *tape)
{
    int  head;
    while ( (head = getc(tape)) == ' ');
    ungetc(head, tape);
}

int isQUIT(FILE *tape){
    int i = 0;
    int token = 0;
    int breakloop = 0;
    while(breakloop == 0){
        lexeme[i] = getc(tape);
        if(lexeme[i] == ' ' || lexeme[i] == '\n' || lexeme[i] == ';' || lexeme[i] == 0){
            breakloop = 1;
        }else i++;
    }
    ungetc(lexeme[i], tape);
    lexeme[i] = 0;
    strcpy(lexeme, strupr(lexeme));
    if(!strcmp(lexeme, "EXIT")) token = QUIT;
    else if(!strcmp(lexeme, "QUIT")) token = QUIT;
    else if(!strcmp(lexeme, "BYE")) token = QUIT;
    else if(!strcmp(lexeme, "LOGOUT")) token = QUIT;
    else{
        i--;
        for(; i >= 0; i--) ungetc(lexeme[i], tape);
    }
    return token;
}

int isID(FILE *tape)
{
    int i = 0;

    if( isalpha( lexeme[i]=getc(tape) ) ) {
        i++;
        while( isalnum( lexeme[i]=getc(tape) ) ) i++;
        ungetc(lexeme[i], tape);
        lexeme[i] = 0;
        return ID;
    }

    ungetc(lexeme[i], tape);
    return 0;
}

/** EE = [eE] ['+''-']? FRAC

    FRAC = [0-9]+

    **/
int
chk_EE(FILE *tape, int i0)
{
    /** using lexeme[i] as a subtape to easy possible backtracking **/
    int             i = i0;
    if (toupper(lexeme[i] = getc(tape)) == 'E') {
        i++;

        /** abstracts ['+''-'] **/
        if ((lexeme[i] = getc(tape)) == '+' || lexeme[i] == '-') {
            i++;
        } else {
            ungetc(lexeme[i], tape);
			lexeme[i] = 0;
        }

        /** abstracts [0-9]+ **/
        if (isdigit(lexeme[i] = getc(tape))) {
            i++;
            while (isdigit(lexeme[i] = getc(tape)))
                i++;
            ungetc(lexeme[i], tape);
            lexeme[i] = 0;
            return i;
        } else {
            /** reaching out this line means this is NAN **/
            for (; i >= i0; i--) {
                ungetc(lexeme[i], tape);
            }
            return i0;
        }
    }

    /** at this point, not even ana EE-prefix was found **/
    ungetc(lexeme[i], tape);
    return i0;

}

int
isNUM(FILE *tape)
{
    int i;
    lexeme[i = 0] = getc(tape);
    int             token = 0;
    /** integer part **/
    if (isdigit(lexeme[i])) {
        token = UINT;
        if (lexeme[i] == '0') {
            ;
        } else {
            while (isdigit(lexeme[++i] = getc(tape)));
            ungetc(lexeme[i], tape);
        }

    }  /** Pequena alteração **/
      else{
        ungetc(lexeme[i],tape);
      }

    if ((lexeme[i] = getc(tape)) == '.') {
		i++;
        if (token == UINT) {
            token = FLTP;

        } else {
            if (isdigit(lexeme[i] = getc(tape))) {
                token = FLTP;
            } else {
                /** NAN **/
                ungetc(lexeme[i], tape);
                ungetc('.', tape);
                return token;
            }
        }
        while (isdigit(lexeme[i] = getc(tape))) i++;
        ungetc(lexeme[i], tape);
		lexeme[i] = 0;
    } else{
		ungetc(lexeme[i], tape);
		lexeme[i] = 0;
	}
    if (token == 0) {
        /** this is not a number **/
        return 0;
    }

    /** at this point we got a number, either UINT or FLTP **/
    /** check scientific notation: **/
    i = chk_EE(tape, i);
    return token;
}

int
gettoken(FILE *tape)
{
    int             token;
    skipspaces(tape);
    if(token = isQUIT(tape))
        return token;
    if (token = isID(tape))
        return token;
    if (token = isNUM(tape))
        return token;


    return token = getc(tape);
}
