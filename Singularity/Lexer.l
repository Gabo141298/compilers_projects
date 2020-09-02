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