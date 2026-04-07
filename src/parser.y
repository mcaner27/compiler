%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token TOKEN_ARRAY TOKEN_BOOLEAN TOKEN_CHAR TOKEN_ELSE TOKEN_FALSE
%token TOKEN_FOR TOKEN_FUNCTION TOKEN_IF TOKEN_INTEGER TOKEN_PRINT
%token TOKEN_RETURN TOKEN_STRING TOKEN_TRUE TOKEN_VOID TOKEN_WHILE

%token TOKEN_IDENTIFIER
%token TOKEN_INTEGER_LITERAL
%token TOKEN_STRING_LITERAL
%token TOKEN_CHARACTER_LITERAL

%token TOKEN_LPAREN TOKEN_RPAREN
%token TOKEN_LBRACKET TOKEN_RBRACKET
%token TOKEN_LBRACE TOKEN_RBRACE
%token TOKEN_COLON TOKEN_SEMICOLON TOKEN_COMMA

%token TOKEN_INCREMENT TOKEN_DECREMENT
%token TOKEN_EXPONENT
%token TOKEN_MULTIPLY TOKEN_DIVIDE TOKEN_MODULO
%token TOKEN_ADD TOKEN_SUBTRACT
%token TOKEN_LESS_THAN TOKEN_LESS_EQUAL
%token TOKEN_GREATER_THAN TOKEN_GREATER_EQUAL
%token TOKEN_EQUAL TOKEN_NOT_EQUAL
%token TOKEN_LOGICAL_AND TOKEN_LOGICAL_OR
%token TOKEN_LOGICAL_NOT
%token TOKEN_ASSIGN
%token TOKEN_ERROR

%right TOKEN_ASSIGN
%left TOKEN_LOGICAL_OR
%left TOKEN_LOGICAL_AND
%left TOKEN_EQUAL TOKEN_NOT_EQUAL
%left TOKEN_LESS_THAN TOKEN_LESS_EQUAL TOKEN_GREATER_THAN TOKEN_GREATER_EQUAL
%left TOKEN_ADD TOKEN_SUBTRACT
%left TOKEN_MULTIPLY TOKEN_DIVIDE TOKEN_MODULO
%right TOKEN_EXPONENT
%right TOKEN_LOGICAL_NOT
%nonassoc LOWER_THAN_ELSE
%nonassoc TOKEN_ELSE

%%

program
    : declaration_list
    ;

declaration_list
    : declaration_list declaration
    | /* empty */
    ;

declaration
    : TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SEMICOLON
    | TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expr TOKEN_SEMICOLON
    | TOKEN_IDENTIFIER TOKEN_COLON TOKEN_ARRAY TOKEN_LBRACKET expr TOKEN_RBRACKET type TOKEN_SEMICOLON
    | TOKEN_IDENTIFIER TOKEN_COLON TOKEN_ARRAY TOKEN_LBRACKET expr TOKEN_RBRACKET type TOKEN_ASSIGN array_initializer TOKEN_SEMICOLON
    | function_decl
    ;

function_decl
    : TOKEN_IDENTIFIER TOKEN_COLON TOKEN_FUNCTION return_type TOKEN_LPAREN param_list_opt TOKEN_RPAREN TOKEN_ASSIGN block
    ;

return_type
    : type
    | TOKEN_VOID
    ;

param_list_opt
    : param_list
    | /* empty */
    ;

param_list
    : param
    | param_list TOKEN_COMMA param
    ;

param
    : TOKEN_IDENTIFIER TOKEN_COLON type
    | TOKEN_IDENTIFIER TOKEN_COLON TOKEN_ARRAY TOKEN_LBRACKET TOKEN_RBRACKET type
    ;

type
    : TOKEN_INTEGER
    | TOKEN_BOOLEAN
    | TOKEN_CHAR
    | TOKEN_STRING
    ;

block
    : TOKEN_LBRACE stmt_list TOKEN_RBRACE
    ;

stmt_list
    : stmt_list statement
    | /* empty */
    ;

statement
    : expr TOKEN_SEMICOLON
    | TOKEN_RETURN expr TOKEN_SEMICOLON
    | TOKEN_RETURN TOKEN_SEMICOLON
    | TOKEN_PRINT print_list TOKEN_SEMICOLON
    | block
    | TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN statement %prec LOWER_THAN_ELSE
    | TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN statement TOKEN_ELSE statement
    | TOKEN_FOR TOKEN_LPAREN expr_opt TOKEN_SEMICOLON expr_opt TOKEN_SEMICOLON expr_opt TOKEN_RPAREN statement
    | declaration
    ;

expr_opt
    : expr
    | /* empty */
    ;

print_list
    : expr
    | print_list TOKEN_COMMA expr
    ;

array_initializer
    : TOKEN_LBRACE expr_list_opt TOKEN_RBRACE
    ;

expr_list_opt
    : expr_list
    | /* empty */
    ;

expr_list
    : expr
    | expr_list TOKEN_COMMA expr
    ;

expr
    : TOKEN_IDENTIFIER
    | TOKEN_INTEGER_LITERAL
    | TOKEN_STRING_LITERAL
    | TOKEN_CHARACTER_LITERAL
    | TOKEN_TRUE
    | TOKEN_FALSE
    | TOKEN_LPAREN expr TOKEN_RPAREN
    | expr TOKEN_ADD expr
    | expr TOKEN_SUBTRACT expr
    | expr TOKEN_MULTIPLY expr
    | expr TOKEN_DIVIDE expr
    | expr TOKEN_MODULO expr
    | expr TOKEN_EXPONENT expr
    | expr TOKEN_LESS_THAN expr
    | expr TOKEN_LESS_EQUAL expr
    | expr TOKEN_GREATER_THAN expr
    | expr TOKEN_GREATER_EQUAL expr
    | expr TOKEN_EQUAL expr
    | expr TOKEN_NOT_EQUAL expr
    | expr TOKEN_LOGICAL_AND expr
    | expr TOKEN_LOGICAL_OR expr
    | TOKEN_LOGICAL_NOT expr
    | TOKEN_SUBTRACT expr
    | expr TOKEN_ASSIGN expr
    | expr TOKEN_LBRACKET expr TOKEN_RBRACKET
    | TOKEN_IDENTIFIER TOKEN_LPAREN argument_list_opt TOKEN_RPAREN
    | expr TOKEN_INCREMENT
    | expr TOKEN_DECREMENT
    ;

argument_list_opt
    : argument_list
    | /* empty */
    ;

argument_list
    : expr
    | argument_list TOKEN_COMMA expr
    ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "PARSE ERROR: %s\n", s);
}