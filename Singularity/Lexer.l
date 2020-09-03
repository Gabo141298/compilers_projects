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
"set"			{
					printf("%s-%s\n", yytext, "SET");
					/* return SET; */
				}
"to"			{
					printf("%s-%s\n", yytext, "TO");
					/* return TO; */
				}
"as"			{
					printf("%s-%s\n", yytext, "AS");
					/* return AS; */
				}
"list"			{
					printf("%s-%s\n", yytext, "LIST");
					/* return LIST; */
				}
"matrix"		{
					printf("%s-%s\n", yytext, "MATRIX");
					/* return MATRIX; */
				}
"at"			{
					printf("%s-%s\n", yytext, "AT");
					/* return AT; */
				}
"read"			{
					printf("%s-%s\n", yytext, "READ");
					/* return READ; */
				}
"print"			{
					printf("%s-%s\n", yytext, "PRINT");
					/* return PRINT; */
				}
"if"			{
					printf("%s-%s\n", yytext, "IF");
					/* return IF; */
				}
"otherwise"		{
					printf("%s-%s\n", yytext, "OTHERWISE");
					/* return OTHERWISE; */
				}
"begin" 		{
					printf("%s-%s\n", yytext, "BEGIN_BLOCK");
					/* return BEGIN_BLOCK; */
				} 
"end" 			{
					printf("%s-%s\n", yytext, "END_BLOCK");
					/* return END_BLOCK; */
				}
"while" 		{
					printf("%s-%s\n", yytext, "WHILE");
					/* return WHILE; */
				}
"counting" 		{
					printf("%s-%s\n", yytext, "COUNTING");
					/* return COUNTING; */
				}
"define" 		{
					printf("%s-%s\n", yytext, "DEFINE");
					/* return DEFINE; */
				}
"function" 		{
					printf("%s-%s\n", yytext, "FUNCTION");
					/* return FUNCTION; */
				}
"answer" 		{
					printf("%s-%s\n", yytext, "ANSWER");
					/* return ANSWER; */
				}
"call" 			{
					printf("%s-%s\n", yytext, "CALL");
					/* return CALL; */
				}
"with"			{
					printf("%s-%s\n", yytext, "WITH");
					/* return WITH; */
				}
"parameters"	{
					printf("%s-%s\n", yytext, "PARAMETERS");
					/* return PARAMETERS; */
				}
"arguments"		{
					printf("%s-%s\n", yytext, "ARGUMENTS");
					/* return ARGUMENTS; */
				}
"not"			{
					printf("%s-%s\n", yytext, "NOT");
					/* return NOT; */
				}
"and"			{
					printf("%s-%s\n", yytext, "AND");
					/* return AND; */
				}
"or"			{
					printf("%s-%s\n", yytext, "OR");
					/* return OR; */
				}
"xor"			{
					printf("%s-%s\n", yytext, "XOR");
					/* return XOR; */
				}
"+"				{
					printf("%s-%s\n", yytext, "ADDITION");
					/* return ADDITION; */
				}
"-"				{
					printf("%s-%s\n", yytext, "SUBSTRACTION");
					/* return SUBSTRACTION; */
				}
"*"				{
					printf("%s-%s\n", yytext, "MULTIPLICATION");
					/* return MULTIPLICATION; */
				}
"/"				{
					printf("%s-%s\n", yytext, "DIVISION");
					/* return DIVISION; */
				}
"="				{
					printf("%s-%s\n", yytext, "EQUALS");
					/* return EQUALS; */
				}
">="			{
					printf("%s-%s\n", yytext, "GEQ");
					/* return GEQ; */
				}
"<="			{
					printf("%s-%s\n", yytext, "LEQ");
					/* return LEQ; */
				}
">"				{
					printf("%s-%s\n", yytext, "GREATER");
					/* return GREATER; */
				}
"greater than"	{
					printf("%s-%s\n", yytext, "GREATER");
					/* return GREATER; */
				}
"<"				{
					printf("%s-%s\n", yytext, "LESS");
					/* return LESS; */
				}
"less than"		{
					printf("%s-%s\n", yytext, "LESS");
					/* return LESS; */
				}
"("				{
					printf("%s-%s\n", yytext, "OPEN_PARENTHESIS");
					/* return OPEN_PARENTHESIS; */
				}
")"				{
					printf("%s-%s\n", yytext, "CLOSE_PARENTHESIS");
					/* return CLOSE_PARENTHESIS; */
				}
"\""			{
					printf("%s-%s\n", yytext, "QUOTES");
					/* return QUOTES; */
				}
"#"				{
					printf("%s-%s\n", yytext, "HASH");
					/* return HASH; */
				}
[a-zA-Z_][a-zA-Z0-9_]*	{
							printf("%s-%s\n", yytext, "IDENTIFIER");
							yylval.var = strdup(yytext);
							/* return IDENTIFIER; */
						}
[0-9]+\.[0-9]+	{
					printf("%s-%s\n", yytext, "FLOAT");
					yylval.floatval = strtod(yytext, NULL); 
					/* return FLOAT; */ 
				}
[0-9]+      	{
					printf("%s-%s\n", yytext, "INTEGER");
					yylval.intval = strtoll(yytext, NULL, 10); 
					/* return INTEGER; */
				}
.				{ continue; /* Ignore unexpected characters. */}

%%