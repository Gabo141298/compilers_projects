%{

/*
 * Creado por Quantum Refraction
 */

#include "Parser.h"
#include "Lexer.h"

#include <iostream>

int yyerror(const char *msg) {
    std::cout << msg << std::endl;
    return 0;
}

%}

%output  "lib/Parser.c"
%defines "lib/Parser.h"

%union {
    char* var;
    char* string;
    long long intval;
    double floatval;
}

%token <var> IDENTIFIER
%token <intval> INTEGER
%token <floatval> FLOAT
%token <string> STRING

%token SET
%token TO
%token AS
%token LIST
%token MATRIX
%token BY
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
%token QUOTES_ERROR
%token HASH
%token OPEN_BRACKETS
%token CLOSE_BRACKETS
%token COMMA
%token IS
%token FALSE
%token TRUE
%token FROM



%%
%start input;
input: statement;

block: BEGIN_BLOCK body END_BLOCK;

body: statement | body;

// Falta function, data_structure, while_counting
statement: set | print | if_statement | while;

set : SET IDENTIFIER assignment;

read: READ TO IDENTIFIER;

assignment: TO numvalue | AS data_structure | pos_assignment;

print: PRINT value ; 

function: DEFINE FUNCTION IDENTIFIER block;

pos_assignment: OPEN_BRACKETS position CLOSE_BRACKETS TO value; 
position: intvalue | intvalue COMMA intvalue;

data_structure: LIST | MATRIX intvalue BY intvalue;

if_statement: {std::cout << "if" << std::endl;} IF condition block {std::cout << "fi" << std::endl;}; 

while: {std::cout << "while" << std::endl;} WHILE condition block {std::cout << "elihw" << std::endl;};

while_counting: WHILE IDENTIFIER COUNTING FROM intvalue TO intvalue block;

condition: comparison | {std::cout << "boolean" << std::endl;} boolean | {std::cout << "not" << std::endl;} NOT condition;

comparison: {std::cout << "comparison" << std::endl;} value comp_operator value;

comp_operator: {std::cout << "xor" << std::endl;} XOR | LEQ | GREATER | LESS | EQUALS | IS NOT; 

boolean: {std::cout << "true" << std::endl;} TRUE | {std::cout << "false" << std::endl;} FALSE;


numvalue: intvalue | FLOAT;
intvalue:  INTEGER  | IDENTIFIER;
value: numvalue | STRING;

%%
