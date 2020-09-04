%{

/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */

#include "Parser.h"
#include "Lexer.h"

#include <iostream>

int yyerror(const char *msg) {
    return 0;
}

%}

%output  "lib/Parser.c"
%defines "lib/Parser.h"

%union {
    char* var;
    long long intval;
    double floatval;
}

%token <var> IDENTIFIER
%token <intval> INTEGER
%token <floatval> FLOAT

%token SET
%token TO
%token AS
%token LIST
%token MATRIX
%token AT
%token READ
%token PRINT
%token IF
%token OTHERWISE
%token BEGIN_BLOCK
%token END_BLOCK
%token WHILE
%token COUNTING
%token DEFINE
%token FUNCTION
%token ANSWER
%token CALL
%token WITH
%token PARAMETERS
%token ARGUMENTS
%token NOT
%token AND
%token OR
%token XOR
%token ADDITION
%token SUBSTRACTION
%token MULTIPLICATION
%token DIVISION
%token EQUALS
%token GEQ
%token LEQ
%token GREATER
%token LESS
%token OPEN_PARENTHESIS
%token CLOSE_PARENTHESIS
%token STRING
%token QUOTES_ERROR
%token HASH

%%

input
    :
    ;

%%