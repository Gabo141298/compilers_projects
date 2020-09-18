%{

/*
 * Creado por Quantum Refraction
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

input
    :
    ;

block: BEGIN_BLOCK body END_BLOCK;

body: statement | body

// Poner todas las demás cosas que puede ser un statement
statement: set

set : SET IDENTIFIER assignment;

read: READ TO IDENTIFIER

assignment: TO numvalue | AS data_structure | pos_assignment;

print: PRINT value 

function: DEFINE FUNCTION IDENTIFIER block;

pos_assignment: OPEN_BRACKETS position CLOSE_BRACKETS TO value; 
position: intvalue | intvalue COMMA intvalue;

data_structure: LIST | MATRIX intvalue BY intvalue;

if_statement: IF condition block; 

while: WHILE condition block;

while_counting: WHILE IDENTIFIER COUNTING FROM intvalue TO intvalue block;

condition: comparison | boolean | NOT condition;

comparison: value comp_operator value;

comp_operator: XOR | LEQ | GREATER | LESS | EQUALS | IS NOT; 

boolean: TRUE | FALSE;

intvalue: INTEGER | IDENTIFIER;
numvalue: intvalue | FLOAT
value: numvalue | STRING;

%%
