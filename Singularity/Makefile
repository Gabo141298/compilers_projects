# Makefile

FILES	= Lexer.c Parser.c main.c
CC	= g++
CFLAGS	= -g -ansi

singularity: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o singularity

Lexer.c: Lexer.l
	flex Lexer.l

Parser.c: Parser.y Lexer.c
	bison Parser.y

clean:
	rm -f *.o *~ Lexer.c Lexer.h Parser.c Parser.h singularity
