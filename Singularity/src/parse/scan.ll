%{                                                            /* -*- C++ -*- */

#include "parser.hh"
#include "scanner.hh"
#include "driver.hh"

/*  Defines some macros to update locations */


#define STEP()                                      \
  do {                                              \
    driver.location_->step ();                      \
  } while (0)

#define COL(Col)				                    \
  driver.location_->columns (Col)

#define LINE(Line)				                    \
  do{						                        \
    driver.location_->lines (Line);		            \
 } while (0)

#define YY_USER_ACTION				                \
  COL(yyleng);


typedef parse::Parser::token token;
typedef parse::Parser::token_type token_type;

#define SAVE_TOKEN yylval->var = new std::string(yytext, yyleng)

#define yyterminate() return token::TOK_EOF

%}

%option debug
%option c++
%option noyywrap
%option never-interactive
%option yylineno
%option nounput
%option batch
%option prefix="parse"

/*
%option stack
*/

%%
[ \r\n\t]*      { continue; /* Skip blanks. */ }
"set"           {
                    /*printf("%s-%s\n", yytext, "SET");*/
                    return token::SET;
                }
"to"            {
                    /*printf("%s-%s\n", yytext, "TO");*/
                    return token::TO;
                }
"as"            {
                    /* printf("%s-%s\n", yytext, "AS"); */
                    return token::AS;
                }
"list"          {
                    /* printf("%s-%s\n", yytext, "LIST"); */
                    return token::LIST;
                }
"matrix of size"        {
                    /* printf("%s-%s\n", yytext, "MATRIX"); */
                    return token::MATRIX;
                }
"by"            {
                    /* printf("%s-%s\n", yytext, "BY"); */
                    return token::BY;
                }
"at"            {
                    /* printf("%s-%s\n", yytext, "AT"); */
                    return token::AT;
                }
"read"          {
                    /* printf("%s-%s\n", yytext, "READ"); */
                    return token::READ;
                }
"print"         {
                    /* printf("%s-%s\n", yytext, "PRINT"); */
                    return token::PRINT;
                }
"if"            {
                    /* printf("%s-%s\n", yytext, "IF"); */
                    return token::IF;
                }
"otherwise"     {
                    /* printf("%s-%s\n", yytext, "OTHERWISE"); */
                    return token::OTHERWISE;
                }
"begin"         {
                    /* printf("%s-%s\n", yytext, "BEGIN_BLOCK"); */
                    return token::BEGIN_BLOCK;
                } 
"end"           {
                    /* printf("%s-%s\n", yytext, "END_BLOCK"); */
                    return token::END_BLOCK;
                }
"while"         {
                    /* printf("%s-%s\n", yytext, "WHILE"); */
                    return token::WHILE;
                }
"counting"      {
                    /* printf("%s-%s\n", yytext, "COUNTING"); */
                    return token::COUNTING;
                }
"define"        {
                    /* printf("%s-%s\n", yytext, "DEFINE"); */
                    return token::DEFINE;
                }
"function"      {
                    /* printf("%s-%s\n", yytext, "FUNCTION"); */
                    return token::FUNCTION;
                }
"answer"        {
                    /* printf("%s-%s\n", yytext, "ANSWER"); */
                    return token::ANSWER;
                }
"call"          {
                    /* printf("%s-%s\n", yytext, "CALL"); */
                    return token::CALL;
                }
"with"          {
                    /* printf("%s-%s\n", yytext, "WITH"); */
                    return token::WITH;
                }
"parameters"    {
                    /* printf("%s-%s\n", yytext, "PARAMETERS"); */
                    return token::PARAMETERS;
                }
"arguments"     {
                    /* printf("%s-%s\n", yytext, "ARGUMENTS"); */
                    return token::ARGUMENTS;
                }
"is"            {
                    /* printf("%s-%s\n", yytext, "IS"); */
                    return token::IS;
                }
"not"           {
                    /* printf("%s-%s\n", yytext, "NOT"); */
                    return token::NOT;
                }
"from"          {
                    /* printf("%s-%s\n", yytext, "FROM"); */
                    return token::FROM;
                }
"and"           {
                    /* printf("%s-%s\n", yytext, "AND"); */
                    return token::AND;
                }
"or"            {
                    /* printf("%s-%s\n", yytext, "OR"); */
                    return token::OR;
                }
"xor"           {
                    /* printf("%s-%s\n", yytext, "XOR"); */
                    return token::XOR;
                }
"false"         {
                    /* printf("%s-%s\n", yytext, "FALSE"); */
                    return token::FALSE;

                }
"true"          {
                    /* printf("%s-%s\n", yytext, "TRUE"); */
                    return token::TRUE;

                }
"+"             {
                    /* printf("%s-%s\n", yytext, "ADDITION"); */
                    return token::ADDITION;
                }
"-"             {
                    /* printf("%s-%s\n", yytext, "SUBSTRACTION"); */
                    return token::SUBSTRACTION;
                }
"*"             {
                    /* printf("%s-%s\n", yytext, "MULTIPLICATION"); */
                    return token::MULTIPLICATION;
                }
"/"             {
                    /* printf("%s-%s\n", yytext, "DIVISION"); */
                    return token::DIVISION;
                }
"="             {
                    /* printf("%s-%s\n", yytext, "EQUALS"); */
                    return token::EQUALS;
                }
">="            {
                    /* printf("%s-%s\n", yytext, "GEQ"); */
                    return token::GEQ;
                }
"<="            {
                    /* printf("%s-%s\n", yytext, "LEQ"); */
                    return token::LEQ;
                }
">"             {
                    /* printf("%s-%s\n", yytext, "GREATER"); */
                    return token::GREATER;
                }
"%"             {
                    /* printf("%s-%s\n", yytext, "MODULE"); */
                    return token::MODULE;
                }        
"greater than"  {
                    /* printf("%s-%s\n", yytext, "GREATER"); */
                    return token::GREATER;
                }
"<"             {
                    /* printf("%s-%s\n", yytext, "LESS"); */
                    return token::LESS;
                }
"less than"     {
                    /* printf("%s-%s\n", yytext, "LESS"); */
                    return token::LESS;
                }
"("             {
                    /* printf("%s-%s\n", yytext, "OPEN_PARENTHESIS"); */
                    return token::OPEN_PARENTHESIS;
                }
")"             {
                    /* printf("%s-%s\n", yytext, "CLOSE_PARENTHESIS"); */
                    return token::CLOSE_PARENTHESIS;
                }

"(at)? ["       {
                    /* printf("%s-%s\n", yytext, "OPEN_BRACKETS"); */
                    return token::OPEN_BRACKETS;
                }
"]"             {
                    /* printf("%s-%s\n", yytext, "CLOSE_BRACKETS"); */
                    return token::CLOSE_BRACKETS;
                }
","             {
                    /* printf("%s-%s\n", yytext, "COMMA"); */
                    return token::COMMA;
                }

["][^"]*["]     {
                    /* printf("%s-%s\n", yytext, "STRING"); */
                    SAVE_TOKEN;
                    return token::STRING;
                }
"\""            {
                    /* printf("%s-%s\n", yytext, "QUOTES_ERROR"); */
                    return token::QUOTES_ERROR;
                }
"#"             {
                    /* printf("%s-%s\n", yytext, "HASH"); */
                    return token::HASH;
                }
[a-zA-Z_][a-zA-Z0-9_]*  {
                            /*printf("%s-%s\n", yytext, "IDENTIFIER");*/
                            SAVE_TOKEN;
                            return token::IDENTIFIER;
                        }
[0-9]+\.[0-9]+  {
                    /* printf("%s-%s\n", yytext, "FLOAT"); */
                    SAVE_TOKEN; 
                    return token::FLOAT; 
                }
[0-9]+          {
                    /* printf("%s-%s\n", yytext, "INTEGER"); */
                    SAVE_TOKEN;
                    return token::INTEGER;
                }
.               { continue; /* Ignore unexpected characters. */}

%%


/*

   CUSTOM C++ CODE

*/

namespace parse
{

    Scanner::Scanner()
    : parseFlexLexer()
    {
    }

    Scanner::~Scanner()
    {
    }

    void Scanner::set_debug(bool b)
    {
        yy_flex_debug = b;
    }
}

#ifdef yylex
# undef yylex
#endif

int parseFlexLexer::yylex()
{
  std::cerr << "call parsepitFlexLexer::yylex()!" << std::endl;
  return 0;
}
