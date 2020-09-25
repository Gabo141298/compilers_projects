%{     /* PARSER */

#include "parser.hh"
#include "scanner.hh"

#define yylex driver.scanner_->yylex
%}

%code requires
{
  #include <string>
  #include <iostream>
  #include "driver.hh"
  #include "location.hh"
  #include "position.hh"
}

%code provides
{
  namespace parse
  {
    // Forward declaration of the Driver class
    class Driver;

    inline void
    yyerror (const char* msg)
    {
      std::cerr << msg << std::endl;
    }
  }
}



%require "2.4"
%language "C++"
%locations
%defines
%debug
%define api.namespace {parse}
%define parser_class_name {Parser}
%parse-param {Driver &driver}
%lex-param {Driver &driver}
%error-verbose

%union
{
    std::string* var;
}

%token TOK_EOF 0

%token <var> IDENTIFIER INTEGER FLOAT STRING

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

body: statement | statement body;

// Falta data_structure, while_counting
statement: read | set | print | if_statement | while | while_counting |  function;

set : SET IDENTIFIER assignment;

read: READ TO IDENTIFIER;

assignment: TO numvalue | AS data_structure | pos_assignment;

print: PRINT value; 

function: DEFINE FUNCTION IDENTIFIER block | DEFINE FUNCTION IDENTIFIER WITH ARGUMENTS arguments block  ;

arguments: IDENTIFIER | IDENTIFIER COMMA arguments;

pos_assignment: OPEN_BRACKETS position CLOSE_BRACKETS TO value; 

position: intvalue | intvalue COMMA intvalue;

data_structure: LIST | MATRIX intvalue BY intvalue;

if_statement: IF condition block; 

while: WHILE condition block;

while_counting: WHILE IDENTIFIER COUNTING FROM intvalue TO intvalue block;

condition: comparison | {std::cout << "boolean" << std::endl;} boolean | {std::cout << "not" << std::endl;} NOT condition;

comparison: {std::cout << "comparison" << std::endl;} value comp_operator value;

comp_operator: {std::cout << "xor" << std::endl;} XOR | LEQ | GREATER | LESS | EQUALS | IS NOT; 

boolean: {std::cout << "true" << std::endl;} TRUE | {std::cout << "false" << std::endl;} FALSE;


numvalue: intvalue | FLOAT;
intvalue:  INTEGER  | IDENTIFIER;
value: numvalue | STRING;



%%

namespace parse
{
    void Parser::error(const location&, const std::string& m)
    {
        std::cerr << *driver.location_ << ": " << m << std::endl;
        driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
    }
}
