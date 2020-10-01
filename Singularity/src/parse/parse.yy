%{     /* PARSER */

#include "parser.hh"
#include "scanner.hh"

#define yylex driver.scanner_->yylex

SNode::Program* programBlock;
%}

%code requires
{
  #include <string>
  #include <iostream>
  #include "driver.hh"
  #include "location.hh"
  #include "position.hh"

  #include "node.h"
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
%define parser_class_name{Parser}
%parse-param {Driver &driver}
%lex-param {Driver &driver}
%define parse.error verbose

%union
{
    SNode::Node* node;
    SNode::Block* block;
    SNode::Body* body;
    SNode::Expression* expression;
    SNode::Statement* statement;
    SNode::Identifier* identifier;
    SNode::Program* program;
    SNode::Function* function;
    SNode::Value* value;
    SNode::DataStructure* dataStructure;
    SNode::Position* position;
    SNode::DataPositionAssignment* dataPosAssignment;
    std::string* var;
    SNode::ComparisonOperation compOper;
    SNode::BooleanOperation boolOper;
    SNode::VariableList* variableList;
    SNode::If* ifStatement;
    SNode::OtherwiseIf* otherwiseIf;
    SNode::Otherwise* otherwise;
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
%token MODULE
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

%type <program> program
%type <block> block
%type <body> body
%type <value> value boolean numvalue intvalue
%type <expression> assignment expression condition comparison func_call
%type <position> position 
%type <statement> statement set read print while while_counting answer 
%type <ifStatement> if_statement 
%type <otherwise> otherwise
%type <otherwiseIf> otherwiseIf
%type <dataStructure> data_structure
%type <dataPosAssignment> pos_assignment
%type <function> function
%type <compOper> comp_operator
%type <boolOper> boolean_operator
%type <variableList> arguments

%%
%start input;
input: program { programBlock = $1; } ;

program: function { $$ = new SNode::Program(); $$->functions.push_back($1); }
            | program function { $1->functions.push_back($2); }
            ;

block:  BEGIN_BLOCK
        body
        END_BLOCK { $$ = new SNode::Block(*$2); }
        ;

body:       statement { $$ = new SNode::Body(); $$->statements.push_back($<statement>1); }
            | body statement { $1->statements.push_back($<statement>2); }
            ;

statement: read { $$ = $1; }
            | set { $$ = $1; }
            | print { $$ = $1; }
            | if_statement { $$ = $1; }
            | while { $$ = $1; }
            | while_counting { $$ = $1; }
            | answer { $$ = $1; }
            | func_call { $$ = new SNode::ExpressionStatement(*$1); }
            ;

set : SET IDENTIFIER assignment 
            { $$ = new SNode::VariableAssignment(*(new SNode::Identifier(*$2)), $3); delete $2; }
            ;

read: READ TO IDENTIFIER { $$ = new SNode::Read(*$3); delete $3; };

assignment: TO expression { $$ = $2; } 
            | AS data_structure { $$ = $2; }
            | pos_assignment { $$ = $1; } 
            ;

print: PRINT expression { $$ = new SNode::Print(*$2); }; 

function: DEFINE FUNCTION IDENTIFIER block
            { $$ = new SNode::Function(*(new SNode::Identifier(*$3)), *$4); delete $3; }
            | DEFINE FUNCTION IDENTIFIER WITH ARGUMENTS arguments block
            { $$ = new SNode::Function(*(new SNode::Identifier(*$3)), *$6, *$7); delete $3; }
            ;

arguments: IDENTIFIER { $$ = new SNode::VariableList(); $$->push_back(new SNode::Identifier(*$1)); delete $1; }
            | arguments COMMA IDENTIFIER { $1->push_back(new SNode::Identifier(*$3)); delete $3; };

pos_assignment: OPEN_BRACKETS position CLOSE_BRACKETS TO expression
            { $$ = new SNode::DataPositionAssignment(*$2, *$5); }
            ; 

position: intvalue { $$ = new SNode::ListPosition(*$1); }
            | intvalue COMMA intvalue { $$ = new SNode::MatrixPosition(*$1, *$3); };

data_structure: LIST { $$ = new SNode::List(); }
            | MATRIX intvalue BY intvalue { $$ = new SNode::Matrix($2, $4); }
            ;

if_statement: IF condition block { $$ = new SNode::If(*$2, *$3); }
                | IF condition block otherwiseIf { $$ = new SNode::If(*$2, *$3, $4); }
                | IF condition block otherwise { $$ = new SNode::If(*$2, *$3, $4); }
                ;

otherwiseIf: OTHERWISE if_statement { $$ = new SNode::OtherwiseIf(*$2); } ;

otherwise: OTHERWISE block { $$ = new SNode::Otherwise(*$2); } ;

while: WHILE condition block { $$ = new SNode::While(*$2, *$3); };;

while_counting: WHILE IDENTIFIER COUNTING FROM expression TO expression block
                { $$ = new SNode::WhileCounting(*(new SNode::Identifier(*$2)), *$5, *$7, *$8); delete $2; };

condition: comparison { $$ = $1; }
            | IDENTIFIER { $$ = new SNode::Identifier(*$1); delete $1; }
            | boolean { $$ = $1; }
            | NOT condition { $$ = new SNode::NotOperator(*$2); }
            | condition boolean_operator condition
            { $$ = new SNode::BooleanOperator(*$1, $2, *$3); }
            ;

comparison: expression comp_operator expression
            { $$ = new SNode::ComparisonOperator(*$1, $2, *$3); }
            ;

comp_operator: LEQ { $$ = SNode::ComparisonOperation::leq; }
            | GEQ { $$ = SNode::ComparisonOperation::geq; }
            | GREATER { $$ = SNode::ComparisonOperation::greater; }
            | LESS { $$ = SNode::ComparisonOperation::less; }
            | EQUALS { $$ = SNode::ComparisonOperation::equals; }
            | IS NOT { $$ = SNode::ComparisonOperation::isNot; }
            | MODULE { $$ = SNode::ComparisonOperation::module; }
            ;

boolean_operator: XOR { $$ = SNode::BooleanOperation::bXor; }
            | OR { $$ = SNode::BooleanOperation::bOr; }
            | AND { $$ = SNode::BooleanOperation::bAnd; }
            ;

boolean: TRUE { $$ = new SNode::Boolean(true); }
            | FALSE { $$ = new SNode::Boolean(false); }
            ;

numvalue: intvalue { $$ = $1; }
            | FLOAT { $$ = new SNode::Double(atof($1->c_str())); delete $1; }
            ;

intvalue:  INTEGER { $$ = new SNode::Integer(atoll($1->c_str())); delete $1; }
            | IDENTIFIER { $$ = new SNode::Identifier(*$1); delete $1; }
            ;

value: numvalue { $$ = $1; }
            | STRING { $$ = new SNode::String(*$1); delete $1; }
            | boolean { $$ = $1; }
            ;

expression: IDENTIFIER OPEN_BRACKETS position CLOSE_BRACKETS {  $$ = new SNode::PositionAccess( *(new SNode::Identifier(*$1)), *$3); delete $1; }
            | value { $$ = $1; }
            | func_call
            | expression ADDITION expression { $$ = new SNode::ArithmeticOperator(*$1, SNode::Operation::addition, *$3); }
            | expression SUBSTRACTION expression { $$ = new SNode::ArithmeticOperator(*$1, SNode::Operation::substraction, *$3); }
            | expression MULTIPLICATION expression { $$ = new SNode::ArithmeticOperator(*$1, SNode::Operation::multiplication, *$3); }
            | expression DIVISION expression { $$ = new SNode::ArithmeticOperator(*$1, SNode::Operation::division, *$3); }
            | expression MODULE expression { $$ = new SNode::ArithmeticOperator(*$1, SNode::Operation::division, *$3);}
            ;

func_call: CALL IDENTIFIER { $$ = new SNode::FunctionCall(*(new SNode::Identifier(*$2))); delete $2; }
            | CALL IDENTIFIER WITH PARAMETERS OPEN_PARENTHESIS arguments CLOSE_PARENTHESIS
            { $$ = new SNode::FunctionCall(*(new SNode::Identifier(*$2)), *$6); delete $2; }
            ;

answer: ANSWER expression
        { $$ = new SNode::Answer(*$2); }
        ;

%%

namespace parse
{
    void Parser::error(const location&, const std::string& m)
    {
        std::cerr << *driver.location_ << ": " << m << std::endl;
        driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
    }
}
