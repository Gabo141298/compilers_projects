%{

/*
 * Lexer.l file
 * To generate the lexical analyzer run: "flex Lexer.l"
 */

#include "Parser.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

%}

%option outfile="Lexer.c" header-file="Lexer.h"

%option noyywrap

%%

[ \r\n\t]* 		{ continue; /* Skip blanks. */ }
"set"			{return SET;}
"to"			{return TO;}
"as"			{return AS;}
"list"			{return LIST;}
"matrix"		{return MATRIX;}
"at"			{return AT;}
"read"			{return READ;}
"print"			{return PRINT;}
"if"			{return IF;}
"otherwise"		{return OTHERWISE;}
"begin" 		{return BEGIN_BLOCK;} 
"end" 			{return END_BLOCK;}
"while" 		{return WHILE;}
"counting" 		{return COUNTING;}
"define" 		{return DEFINE;}
"function" 		{return FUNCTION;}
"answer" 		{return ANSWER;}
"call" 			{return CALL;}
"with"			{return WITH;}
"parameters"	{ return PARAMETERS; }
"arguments"		{ return ARGUMENTS; }
"not"			{ return NOT; }
"and"			{ return AND; }
"or"			{ return OR; }
"xor"			{ return XOR; }
"+"				{ return ADDITION; }
"-"				{ return SUBSTRACTION; }
"*"				{ return MULTIPLICATION; }
"/"				{ return DIVISION; }
"="				{ return EQUALS; }
">="			{ return GEQ; }
"<="			{ return LEQ; }
">"				{ return GREATER; }
"greater than"	{ return GREATER; }
"<"				{ return LESS; }
"less than"		{ return LESS; }
"("				{ return OPEN_PARENTHESIS; }
")"				{ return CLOSE_PARENTHESIS; }
"\""			{ return QUOTES; }
"#"				{ return HASH; }
[a-zA-Z][a-zA-Z0-9]*	{
							yylval.var = strdup(yytext);
							return IDENTIFIER;
						}
[0-9]+      	{
					yylval.intval = strtoll(yytext, NULL, 10); 
					return INTEGER;
				}
[0-9]+\.[0-9]+	{
					yylval.floatval = strtod(yytext, NULL); 
					return FLOAT; 
				}
.				{ continue; /* Ignore unexpected characters. */}

%%