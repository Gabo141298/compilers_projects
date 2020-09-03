# Makefile

FILES	= lib/Lexer.c lib/Parser.c main.c
CC	= g++
CFLAGS	= -g -ansi

singularity: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o singularity

lib/Lexer.c: Lexer.l
	flex Lexer.l

lib/Parser.c: Parser.y lib/Lexer.c
	bison Parser.y

clean:
	rm -f *.o *~ lib/Lexer.c lib/Lexer.h lib/Parser.c lib/Parser.h singularity
