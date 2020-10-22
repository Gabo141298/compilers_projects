%{     /* PARSER */

#include "parser.hh"
#include "scanner.hh"

#define yylex driver.scanner_->yylex

SNode::Program* programBlock;
SymbolTable symbolTable;
%}

%code requires
{
  #include <string>
  #include <iostream>
  #include "driver.hh"
  #include "location.hh"
  #include "position.hh"

  #include "../node/node_headers.hh"
  #include "symbol_table.hh"
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
    SNode::VariableList* variableList;
    SNode::If* ifStatement;
    SNode::ExpressionList* expressionList;
    SNode::VariableAssignment* variableAssignment;
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
%token MODULO
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

%left AND OR XOR
%left EQUALS GEQ LEQ GREATER LESS IS NOT
%left ADDITION SUBSTRACTION
%left MULTIPLICATION DIVISION MODULO

%type <program> program
%type <block> block body
%type <value> value boolean intvalue
%type <expression> assignment expression func_call term
%type <position> position 
%type <statement> statement read print while while_counting answer if_statement otherwise
%type <variableAssignment> set
%type <ifStatement> if_condition
%type <dataStructure> data_structure
%type <dataPosAssignment> data_pos_set
%type <function> function
%type <variableList> arguments
%type <expressionList> parameters

%%
%start input;
input: program { programBlock = $1; } ;

program: %empty { $$ = new SNode::Program(); }
            | program function { 
                $1->functions.push_back($2); 
                symbolTable.insertToCurrentSubtable($2->id.name, Datatype::FUNCTION, $2->arguments.size());
            }
            | program set {
                $1->globals.push_back($2); 
                symbolTable.insertToCurrentSubtable($2->id.name, $2->assignmentExpr->getExpressionType());
            }
            ;

block:  BEGIN_BLOCK body END_BLOCK { $$ = $2; }
        ;

body:       statement { $$ = new SNode::Block(); $$->statements.push_back($<statement>1); }
            | body statement { $1->statements.push_back($<statement>2); }
            ;

statement: read { $$ = $1; }
            | set { $$ = $1; }
            | data_pos_set { $$ = $1; }
            | print { $$ = $1; }
            | if_condition { $$ = $1; }
            | while { $$ = $1; }
            | while_counting { $$ = $1; }
            | answer { $$ = $1; }
            | func_call { $$ = new SNode::ExpressionStatement(*$1); }
            ;

set : SET IDENTIFIER assignment 
        { $$ = new SNode::VariableAssignment(*(new SNode::Identifier(*$2, symbolTable)), $3); delete $2; }
        ;

data_pos_set: SET IDENTIFIER OPEN_BRACKETS position CLOSE_BRACKETS TO expression
                { $$ = new SNode::DataPositionAssignment(*(new SNode::Identifier(*$2,symbolTable)), *$4, *$7); delete $2; }
                ;

read: READ TO IDENTIFIER { $$ = new SNode::Read(*new SNode::Identifier(*$3, symbolTable)); delete $3; };

assignment: TO expression { $$ = $2; } 
            | AS data_structure { $$ = $2; }
            ;

print: PRINT expression { $$ = new SNode::Print(*$2); }; 

function: DEFINE FUNCTION IDENTIFIER block
            { $$ = new SNode::Function(*(new SNode::Identifier(*$3,symbolTable)), *$4); delete $3; }
            | DEFINE FUNCTION IDENTIFIER WITH ARGUMENTS arguments block
            { $$ = new SNode::Function(*(new SNode::Identifier(*$3,symbolTable)), *$6, *$7); delete $3; }
            ;

arguments: IDENTIFIER { $$ = new SNode::VariableList(); $$->push_back(new SNode::Identifier(*$1,symbolTable)); delete $1; }
            | arguments COMMA IDENTIFIER { $1->push_back(new SNode::Identifier(*$3,symbolTable)); delete $3; };

parameters: expression { $$ = new SNode::ExpressionList(); $$->push_back($1); }
            | parameters COMMA expression { $1->push_back($3);  };

position: expression { $$ = new SNode::ListPosition(*$1); }
            | expression COMMA expression { $$ = new SNode::MatrixPosition(*$1, *$3); };

data_structure: LIST { $$ = new SNode::List(); }
            | MATRIX intvalue BY intvalue { $$ = new SNode::Matrix($2, $4); }
            ;

if_condition: IF expression block if_statement { $$ = new SNode::If(*$2, *$3, $4); }
                ;

if_statement: %empty { $$ = nullptr; }
                | OTHERWISE otherwise { $$ = $2; }
                ;

otherwise: if_condition { $$ = new SNode::OtherwiseIf(*$1); }
            | block { $$ = new SNode::Otherwise(*$1); } 
            ;

while: WHILE expression block { $$ = new SNode::While(*$2, *$3); };;

while_counting: WHILE IDENTIFIER COUNTING FROM expression TO expression block
                { $$ = new SNode::WhileCounting(*(new SNode::Identifier(*$2,symbolTable)), *$5, *$7, *$8); delete $2; };

boolean: TRUE { $$ = new SNode::Boolean(true); }
            | FALSE { $$ = new SNode::Boolean(false); }
            ;

intvalue:  INTEGER { $$ = new SNode::Integer(atoll($1->c_str())); delete $1; }
            | IDENTIFIER { $$ = new SNode::Identifier(*$1,symbolTable); delete $1; }
            ;

value:      FLOAT { $$ = new SNode::Double(atof($1->c_str())); delete $1; }
            | INTEGER { $$ = new SNode::Integer(atoll($1->c_str())); delete $1; }
            | IDENTIFIER { $$ = new SNode::Identifier(*$1,symbolTable); delete $1; }
            | STRING { $$ = new SNode::String(*$1); delete $1; }
            | boolean { $$ = $1; }
            ;

term:       value { $$ = $1; }
            | func_call { $$ = $1; }
            | OPEN_PARENTHESIS expression CLOSE_PARENTHESIS { $$ = $2; }
            | IDENTIFIER OPEN_BRACKETS position CLOSE_BRACKETS { $$ = new SNode::PositionAccess( *(new SNode::Identifier(*$1,symbolTable)), *$3); delete $1; }
            | NOT OPEN_PARENTHESIS expression CLOSE_PARENTHESIS { $$ = new SNode::NotOperation(*$3); }
            ;

expression: term { $$ = $1; }
            | expression ADDITION expression { $$ = SNode::createOperation(*$1, SNode::ArithmeticOperator::addition, *$3); }
            | expression SUBSTRACTION expression { $$ = SNode::createOperation(*$1, SNode::ArithmeticOperator::substraction, *$3); }
            | expression MULTIPLICATION expression { $$ = SNode::createOperation(*$1, SNode::ArithmeticOperator::multiplication, *$3); }
            | expression DIVISION expression { $$ = SNode::createOperation(*$1, SNode::ArithmeticOperator::division, *$3); }
            | expression MODULO expression { $$ = SNode::createOperation(*$1, SNode::ArithmeticOperator::modulo, *$3); }
            | expression LEQ expression { $$ = SNode::createOperation(*$1, SNode::ComparisonOperator::leq, *$3); }
            | expression GEQ expression { $$ = SNode::createOperation(*$1, SNode::ComparisonOperator::geq, *$3); }
            | expression GREATER expression { $$ = SNode::createOperation(*$1, SNode::ComparisonOperator::greater, *$3); }
            | expression LESS expression { $$ = SNode::createOperation(*$1, SNode::ComparisonOperator::less, *$3); }
            | expression EQUALS expression { $$ = SNode::createOperation(*$1, SNode::ComparisonOperator::equals, *$3); }
            | expression IS NOT expression { $$ = SNode::createOperation(*$1, SNode::ComparisonOperator::isNot, *$4); }
            | expression XOR expression { $$ = SNode::createOperation(*$1, SNode::BooleanOperator::bXor, *$3); }
            | expression OR expression { $$ = SNode::createOperation(*$1, SNode::BooleanOperator::bOr, *$3); }
            | expression AND expression { $$ = SNode::createOperation(*$1, SNode::BooleanOperator::bAnd, *$3); }
            ;

func_call: CALL IDENTIFIER { $$ = new SNode::FunctionCall(*(new SNode::Identifier(*$2,symbolTable)), symbolTable); delete $2; }
            | CALL IDENTIFIER WITH PARAMETERS OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS
            { $$ = new SNode::FunctionCall(*(new SNode::Identifier(*$2,symbolTable)), symbolTable, *$6); delete $2; }
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
