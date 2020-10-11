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
    SNode::Operation arithOper;
    SNode::VariableList* variableList;
    SNode::If* ifStatement;
    SNode::ExpressionList* expressionList;
    SNode::RightSideArithExpr* rsArithExpr;
    SNode::RightSideCompExpr* rsCompExpr;
    SNode::RightSideBoolExpr* rsBoolExpr;
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

%type <program> program
%type <block> block
%type <body> body
%type <value> value boolean intvalue
%type <expression> assignment expression condition func_call bool_cond
%type <position> position 
%type <statement> statement read print while while_counting answer if_statement otherwise
%type <variableAssignment> set
%type <ifStatement> if_condition
%type <dataStructure> data_structure
%type <dataPosAssignment> pos_assignment
%type <function> function
%type <compOper> comp_operator
%type <boolOper> boolean_operator
%type <variableList> arguments
%type <expressionList> parameters
%type <arithOper> arith_oper
%type <rsArithExpr> expression2
%type <rsCompExpr> comparison
%type <rsBoolExpr> bool_cond2

%%
%start input;
input: program { programBlock = $1; } ;

program: %empty { $$ = new SNode::Program(); }
            | program function { $1->functions.push_back($2); }
            | program set { $1->globals.push_back($2); }
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
            | if_condition { $$ = $1; }
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

parameters: expression { $$ = new SNode::ExpressionList(); $$->push_back($1); }
            | parameters COMMA expression { $1->push_back($3);  };

pos_assignment: OPEN_BRACKETS position CLOSE_BRACKETS TO expression
            { $$ = new SNode::DataPositionAssignment(*$2, *$5); }
            ; 

position: expression { $$ = new SNode::ListPosition(*$1); }
            | expression COMMA expression { $$ = new SNode::MatrixPosition(*$1, *$3); };

data_structure: LIST { $$ = new SNode::List(); }
            | MATRIX intvalue BY intvalue { $$ = new SNode::Matrix($2, $4); }
            ;

if_condition: IF bool_cond block if_statement { $$ = new SNode::If(*$2, *$3, $4); }
                ;

if_statement: %empty { $$ = nullptr; }
                | OTHERWISE otherwise { $$ = $2; }
                ;

otherwise: if_condition { $$ = new SNode::OtherwiseIf(*$1); }
            | block { $$ = new SNode::Otherwise(*$1); } 
            ;

while: WHILE bool_cond block { $$ = new SNode::While(*$2, *$3); };;

while_counting: WHILE IDENTIFIER COUNTING FROM expression TO expression block
                { $$ = new SNode::WhileCounting(*(new SNode::Identifier(*$2)), *$5, *$7, *$8); delete $2; };

bool_cond: condition bool_cond2 {
                if($2)
                {
                    $$ = new SNode::BooleanOperator(*$1, $2->op, $2->exp);
                    delete $2;
                }
                else
                {
                    $$ = $1;
                }
            }
            | NOT bool_cond { $$ = new SNode::NotOperator(*$2); }
            | OPEN_PARENTHESIS bool_cond CLOSE_PARENTHESIS bool_cond2 { 
                if($4)
                {
                    $$ = new SNode::BooleanOperator(*$2, $4->op, $4->exp);
                    delete $4;
                }
                else
                {
                    $$ = $2;
                }
            }
            ;

bool_cond2: boolean_operator bool_cond { $$ = new SNode::RightSideBoolExpr($1, *$2); }
            | %empty { $$ = nullptr; }
            ;

condition: expression comparison { $$ = new SNode::ComparisonOperator(*$1, $2->op, $2->exp); delete $2; }
            | IDENTIFIER { $$ = new SNode::Identifier(*$1); delete $1; }
            | boolean { $$ = $1; }
            ;

comparison: comp_operator expression
            { $$ = new SNode::RightSideCompExpr($1, *$2); }
            ;

comp_operator: LEQ { $$ = SNode::ComparisonOperation::leq; }
            | GEQ { $$ = SNode::ComparisonOperation::geq; }
            | GREATER { $$ = SNode::ComparisonOperation::greater; }
            | LESS { $$ = SNode::ComparisonOperation::less; }
            | EQUALS { $$ = SNode::ComparisonOperation::equals; }
            | IS NOT { $$ = SNode::ComparisonOperation::isNot; }
            ;

boolean_operator: XOR { $$ = SNode::BooleanOperation::bXor; }
            | OR { $$ = SNode::BooleanOperation::bOr; }
            | AND { $$ = SNode::BooleanOperation::bAnd; }
            ;

boolean: TRUE { $$ = new SNode::Boolean(true); }
            | FALSE { $$ = new SNode::Boolean(false); }
            ;

intvalue:  INTEGER { $$ = new SNode::Integer(atoll($1->c_str())); delete $1; }
            | IDENTIFIER { $$ = new SNode::Identifier(*$1); delete $1; }
            ;

value:      FLOAT { $$ = new SNode::Double(atof($1->c_str())); delete $1; }
            | INTEGER { $$ = new SNode::Integer(atoll($1->c_str())); delete $1; }
            | IDENTIFIER { $$ = new SNode::Identifier(*$1); delete $1; }
            | STRING { $$ = new SNode::String(*$1); delete $1; }
            | boolean { $$ = $1; }
            ;

expression: IDENTIFIER OPEN_BRACKETS position CLOSE_BRACKETS {  $$ = new SNode::PositionAccess( *(new SNode::Identifier(*$1)), *$3); delete $1; }
            | value expression2 { 
                if($2) 
                {
                    $$ = new SNode::ArithmeticOperator(*$1, $2->op, $2->exp);
                    delete $2;
                }
                else
                {
                    $$ = $1;
                }
            }
            | func_call
            ;

expression2: %empty { $$ = nullptr; }
            | arith_oper expression { $$ = new SNode::RightSideArithExpr($1, *$2); }
            ;

arith_oper: ADDITION { $$ = SNode::Operation::addition; }
            | SUBSTRACTION { $$ = SNode::Operation::substraction; }
            | MULTIPLICATION { $$ = SNode::Operation::multiplication; }
            | DIVISION { $$ = SNode::Operation::division; }
            | MODULO { $$ = SNode::Operation::modulo; }
            ;

func_call: CALL IDENTIFIER { $$ = new SNode::FunctionCall(*(new SNode::Identifier(*$2))); delete $2; }
            | CALL IDENTIFIER WITH PARAMETERS OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS
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
