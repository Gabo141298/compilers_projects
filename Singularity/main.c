#include "Parser.h"
#include "Lexer.h"

#include <cstdio>
#include <iostream>

extern int yyparse();
extern FILE *yyin;

int main(int argc, char** argv) {
    if(argc <= 1)
    {
        std::cerr << "File needed" << std::endl;
        return 1;
    }
    // open a file handle to a particular file:
    FILE *myfile = fopen(argv[1], "r");
    // make sure it's valid:
    if (!myfile) {
        std::cout << "Can't open file: " << argv[1] << std::endl;
        return -1;
    }
    // Set flex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    // Parse through the input:
    yyparse();
}