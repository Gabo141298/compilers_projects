# Makefile

FILES	= lib/Lexer.cpp lib/Parser.cpp main.cpp
CC	= g++
CFLAGS	= -g -ansi 

singularity: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o singularity

lib/Lexer.cpp: Lexer.l
	flex Lexer.l

lib/Parser.cpp: Parser.y lib/Lexer.cpp
	bison -d Parser.y -Wconflicts-sr

clean:
	rm -rf *.o *~ lib/*.h lib/*.cpp singularity
