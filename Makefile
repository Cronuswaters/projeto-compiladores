#!/usr/bin/make -f

# Makefile for assisted compiling of the MyBC project

# mybc => lexer.o main.o parser.o

CFLAGS=-g -I.

mybc: lexer.o main.o parser.o vm.o lextoparser.o
	$(CC) $^ -o $@

clean:
	$(RM) *.o

mostlyclean: clean
	$(RM) *~
