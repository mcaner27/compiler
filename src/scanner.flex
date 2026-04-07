%{
/*
 * CEN417 - B-Minor Scanner
 * Parser ile uyumlu sürüm
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"

extern FILE *yyin;
%}

/* Flex Options */
%option noyywrap
%option yylineno
%option nounput
%option noinput

/* Regex Definitions */
DIGIT      [0-9]
LETTER     [a-zA-Z]
ID         ({LETTER}|_)({LETTER}|{DIGIT}|_)*
ESCAPE     \\[nt0\\'"]
CHAR_BODY  ([^\\'\n]|{ESCAPE})
STR_BODY   ([^\\\"\n]|{ESCAPE})*

%%

[ \t\r\n]+                          { /* skip whitespace */ }
"//".*                              { /* skip single-line comment */ }
"/*"([^*]|(\*+[^*/]))*\*+"/"        { /* skip multi-line comment */ }

"/*"([^*]|(\*+[^*/]))*              {
                                        fprintf(stderr, "SCAN ERROR: Unterminated block comment at line %d\n", yylineno);
                                        return TOKEN_ERROR;
                                    }

"array"                             { return TOKEN_ARRAY; }
"boolean"                           { return TOKEN_BOOLEAN; }
"char"                              { return TOKEN_CHAR; }
"else"                              { return TOKEN_ELSE; }
"false"                             { return TOKEN_FALSE; }
"for"                               { return TOKEN_FOR; }
"function"                          { return TOKEN_FUNCTION; }
"if"                                { return TOKEN_IF; }
"integer"                           { return TOKEN_INTEGER; }
"print"                             { return TOKEN_PRINT; }
"return"                            { return TOKEN_RETURN; }
"string"                            { return TOKEN_STRING; }
"true"                              { return TOKEN_TRUE; }
"void"                              { return TOKEN_VOID; }
"while"                             { return TOKEN_WHILE; }

"++"                                { return TOKEN_INCREMENT; }
"--"                                { return TOKEN_DECREMENT; }
"=="                                { return TOKEN_EQUAL; }
"!="                                { return TOKEN_NOT_EQUAL; }
"<="                                { return TOKEN_LESS_EQUAL; }
">="                                { return TOKEN_GREATER_EQUAL; }
"&&"                                { return TOKEN_LOGICAL_AND; }
"||"                                { return TOKEN_LOGICAL_OR; }

"("                                 { return TOKEN_LPAREN; }
")"                                 { return TOKEN_RPAREN; }
"["                                 { return TOKEN_LBRACKET; }
"]"                                 { return TOKEN_RBRACKET; }
"{"                                 { return TOKEN_LBRACE; }
"}"                                 { return TOKEN_RBRACE; }
":"                                 { return TOKEN_COLON; }
";"                                 { return TOKEN_SEMICOLON; }
","                                 { return TOKEN_COMMA; }
"^"                                 { return TOKEN_EXPONENT; }
"*"                                 { return TOKEN_MULTIPLY; }
"/"                                 { return TOKEN_DIVIDE; }
"%"                                 { return TOKEN_MODULO; }
"+"                                 { return TOKEN_ADD; }
"-"                                 { return TOKEN_SUBTRACT; }
"<"                                 { return TOKEN_LESS_THAN; }
">"                                 { return TOKEN_GREATER_THAN; }
"!"                                 { return TOKEN_LOGICAL_NOT; }
"="                                 { return TOKEN_ASSIGN; }

{DIGIT}+                            { return TOKEN_INTEGER_LITERAL; }

\'{CHAR_BODY}\'                     { return TOKEN_CHARACTER_LITERAL; }
\'[^\']*\'                          {
                                        fprintf(stderr, "SCAN ERROR: Invalid character literal %s at line %d\n", yytext, yylineno);
                                        return TOKEN_ERROR;
                                    }

\"{STR_BODY}\"                      {
                                        if (yyleng > 258) {
                                            fprintf(stderr, "SCAN ERROR: String literal too long at line %d\n", yylineno);
                                            return TOKEN_ERROR;
                                        }
                                        return TOKEN_STRING_LITERAL;
                                    }

\"[^\"]*                            {
                                        fprintf(stderr, "SCAN ERROR: Unterminated string literal at line %d\n", yylineno);
                                        return TOKEN_ERROR;
                                    }

{ID}                                {
                                        if (yyleng > 256) {
                                            fprintf(stderr, "SCAN ERROR: Identifier too long (%s) at line %d\n", yytext, yylineno);
                                            return TOKEN_ERROR;
                                        }
                                        return TOKEN_IDENTIFIER;
                                    }

.                                   {
                                        fprintf(stderr, "SCAN ERROR: Unknown character '%s' at line %d\n", yytext, yylineno);
                                        return TOKEN_ERROR;
                                    }

%%