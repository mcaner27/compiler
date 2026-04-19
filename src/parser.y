%code requires {
    #include "ast.h"
}

%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex(void);
void yyerror(const char *s);

ASTNode *root;
%}

%union {
    ASTNode *node;
    char *text;
    int number;
}

%token TOKEN_ARRAY TOKEN_BOOLEAN TOKEN_CHAR TOKEN_ELSE TOKEN_FALSE
%token TOKEN_FOR TOKEN_FUNCTION TOKEN_IF TOKEN_INTEGER TOKEN_PRINT
%token TOKEN_RETURN TOKEN_STRING TOKEN_TRUE TOKEN_VOID TOKEN_WHILE

%token <text> TOKEN_IDENTIFIER
%token <number> TOKEN_INTEGER_LITERAL
%token <text> TOKEN_STRING_LITERAL
%token <text> TOKEN_CHARACTER_LITERAL

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

%type <node> program
%type <node> declaration_list declaration function_decl
%type <node> param_list_opt param_list param
%type <node> type return_type
%type <node> block stmt_list statement
%type <node> expr_opt print_list array_initializer
%type <node> expr_list_opt expr_list
%type <node> expr
%type <node> argument_list_opt argument_list

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
        {
            root = $1;
            $$ = $1;
        }
    ;

declaration_list
    : declaration_list declaration
        {
            if ($1 == NULL) {
                $$ = $2;
            } else {
                ASTNode *temp = $1;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = $2;
                $$ = $1;
            }
        }
    | /* empty */
        {
            $$ = NULL;
        }
    ;

declaration
    : TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SEMICOLON
        {
            $$ = create_node(NODE_DECLARATION);
            $$->name = $1;
            $$->left = $3;
        }
    | TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expr TOKEN_SEMICOLON
        {
            $$ = create_node(NODE_DECLARATION);
            $$->name = $1;
            $$->left = $3;
            $$->right = $5;
        }
    | TOKEN_IDENTIFIER TOKEN_COLON TOKEN_ARRAY TOKEN_LBRACKET expr TOKEN_RBRACKET type TOKEN_SEMICOLON
        {
            $$ = create_node(NODE_DECLARATION);
            $$->name = $1;
            $$->left = $5;
            $$->right = $7;
        }
    | TOKEN_IDENTIFIER TOKEN_COLON TOKEN_ARRAY TOKEN_LBRACKET expr TOKEN_RBRACKET type TOKEN_ASSIGN array_initializer TOKEN_SEMICOLON
        {
            $$ = create_node(NODE_DECLARATION);
            $$->name = $1;
            $$->left = $5;
            $$->right = $9;
        }
    | function_decl
        {
            $$ = $1;
        }
    ;

function_decl
    : TOKEN_IDENTIFIER TOKEN_COLON TOKEN_FUNCTION return_type TOKEN_LPAREN param_list_opt TOKEN_RPAREN TOKEN_ASSIGN block
        {
            $$ = create_node(NODE_FUNCTION);
            $$->name = $1;
            $$->left = $4;
            $$->right = $9;

            if ($6 != NULL && $4 != NULL) {
                $4->next = $6;
            }
        }
    ;

return_type
    : type
        {
            $$ = $1;
        }
    | TOKEN_VOID
        {
            $$ = create_node(NODE_TYPE);
            $$->type_kind_val = TYPE_VOID;
        }
    ;

param_list_opt
    : param_list
        {
            $$ = $1;
        }
    | /* empty */
        {
            $$ = NULL;
        }
    ;

param_list
    : param
        {
            $$ = $1;
        }
    | param_list TOKEN_COMMA param
        {
            if ($1 == NULL) {
                $$ = $3;
            } else {
                ASTNode *temp = $1;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = $3;
                $$ = $1;
            }
        }
    ;

param
    : TOKEN_IDENTIFIER TOKEN_COLON type
        {
            $$ = create_node(NODE_DECLARATION);
            $$->name = $1;
            $$->left = $3;
        }
    | TOKEN_IDENTIFIER TOKEN_COLON TOKEN_ARRAY TOKEN_LBRACKET TOKEN_RBRACKET type
        {
            $$ = create_node(NODE_DECLARATION);
            $$->name = $1;
            $$->left = $6;
        }
    ;

type
    : TOKEN_INTEGER
        {
            $$ = create_node(NODE_TYPE);
            $$->type_kind_val = TYPE_INTEGER;
        }
    | TOKEN_BOOLEAN
        {
            $$ = create_node(NODE_TYPE);
            $$->type_kind_val = TYPE_BOOLEAN;
        }
    | TOKEN_CHAR
        {
            $$ = create_node(NODE_TYPE);
            $$->type_kind_val = TYPE_CHAR;
        }
    | TOKEN_STRING
        {
            $$ = create_node(NODE_TYPE);
            $$->type_kind_val = TYPE_STRING;
        }
    ;

block
    : TOKEN_LBRACE stmt_list TOKEN_RBRACE
        {
            $$ = create_node(NODE_STATEMENT);
            $$->stmt_kind_val = STMT_BLOCK;
            $$->left = $2;
        }
    ;

stmt_list
    : stmt_list statement
        {
            if ($1 == NULL) {
                $$ = $2;
            } else {
                ASTNode *temp = $1;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = $2;
                $$ = $1;
            }
        }
    | /* empty */
        {
            $$ = NULL;
        }
    ;

statement
    : expr TOKEN_SEMICOLON
        {
            $$ = create_node(NODE_STATEMENT);
            $$->stmt_kind_val = STMT_EXPR;
            $$->left = $1;
        }
    | TOKEN_RETURN expr TOKEN_SEMICOLON
        {
            $$ = create_node(NODE_STATEMENT);
            $$->stmt_kind_val = STMT_RETURN;
            $$->left = $2;
        }
    | TOKEN_RETURN TOKEN_SEMICOLON
        {
            $$ = create_node(NODE_STATEMENT);
            $$->stmt_kind_val = STMT_RETURN;
        }
    | TOKEN_PRINT print_list TOKEN_SEMICOLON
        {
            $$ = create_node(NODE_STATEMENT);
            $$->stmt_kind_val = STMT_PRINT;
            $$->left = $2;
        }
    | block
        {
            $$ = $1;
        }
    | TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN statement %prec LOWER_THAN_ELSE
        {
            $$ = create_node(NODE_STATEMENT);
            $$->stmt_kind_val = STMT_IF;
            $$->left = $3;
            $$->right = $5;
        }
    | TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN statement TOKEN_ELSE statement
        {
            $$ = create_node(NODE_STATEMENT);
            $$->stmt_kind_val = STMT_IF_ELSE;
            $$->left = $3;
            $$->right = $5;
            $$->third = $7;
        }
    | TOKEN_FOR TOKEN_LPAREN expr_opt TOKEN_SEMICOLON expr_opt TOKEN_SEMICOLON expr_opt TOKEN_RPAREN statement
        {
            $$ = create_node(NODE_STATEMENT);
            $$->stmt_kind_val = STMT_FOR;
            $$->left = $3;
            $$->right = $5;
            $$->third = $7;

            if ($7 != NULL) {
                $7->next = $9;
            } else if ($5 != NULL) {
                $5->next = $9;
            } else if ($3 != NULL) {
                $3->next = $9;
            } else {
                $$->third = $9;
            }
        }
    | declaration
        {
            $$ = $1;
        }
    ;

expr_opt
    : expr
        {
            $$ = $1;
        }
    | /* empty */
        {
            $$ = NULL;
        }
    ;

print_list
    : expr
        {
            $$ = $1;
        }
    | print_list TOKEN_COMMA expr
        {
            if ($1 == NULL) {
                $$ = $3;
            } else {
                ASTNode *temp = $1;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = $3;
                $$ = $1;
            }
        }
    ;

array_initializer
    : TOKEN_LBRACE expr_list_opt TOKEN_RBRACE
        {
            $$ = $2;
        }
    ;

expr_list_opt
    : expr_list
        {
            $$ = $1;
        }
    | /* empty */
        {
            $$ = NULL;
        }
    ;

expr_list
    : expr
        {
            $$ = $1;
        }
    | expr_list TOKEN_COMMA expr
        {
            if ($1 == NULL) {
                $$ = $3;
            } else {
                ASTNode *temp = $1;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = $3;
                $$ = $1;
            }
        }
    ;

expr
    : TOKEN_IDENTIFIER
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_IDENTIFIER;
            $$->name = $1;
        }
    | TOKEN_INTEGER_LITERAL
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_INTEGER_LITERAL;
            $$->int_value = $1;
        }
    | TOKEN_STRING_LITERAL
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_STRING_LITERAL;
            $$->string_value = $1;
        }
    | TOKEN_CHARACTER_LITERAL
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_CHAR_LITERAL;
            $$->string_value = $1;
        }
    | TOKEN_TRUE
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_BOOLEAN_LITERAL;
            $$->int_value = 1;
        }
    | TOKEN_FALSE
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_BOOLEAN_LITERAL;
            $$->int_value = 0;
        }
    | TOKEN_LPAREN expr TOKEN_RPAREN
        {
            $$ = $2;
        }
    | expr TOKEN_ADD expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_ADD;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_SUBTRACT expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_SUB;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_MULTIPLY expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_MUL;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_DIVIDE expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_DIV;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_MODULO expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_MOD;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_EXPONENT expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_EXP;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_LESS_THAN expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_LT;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_LESS_EQUAL expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_LE;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_GREATER_THAN expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_GT;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_GREATER_EQUAL expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_GE;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_EQUAL expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_EQ;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_NOT_EQUAL expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_NE;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_LOGICAL_AND expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_AND;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_LOGICAL_OR expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_OR;
            $$->left = $1;
            $$->right = $3;
        }
    | TOKEN_LOGICAL_NOT expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_NOT;
            $$->left = $2;
        }
    | TOKEN_SUBTRACT expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_NEG;
            $$->left = $2;
        }
    | expr TOKEN_ASSIGN expr
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_ASSIGN;
            $$->left = $1;
            $$->right = $3;
        }
    | expr TOKEN_LBRACKET expr TOKEN_RBRACKET
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_INDEX;
            $$->left = $1;
            $$->right = $3;
        }
    | TOKEN_IDENTIFIER TOKEN_LPAREN argument_list_opt TOKEN_RPAREN
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_CALL;
            $$->name = $1;
            $$->left = $3;
        }
    | expr TOKEN_INCREMENT
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_POST_INC;
            $$->left = $1;
        }
    | expr TOKEN_DECREMENT
        {
            $$ = create_node(NODE_EXPRESSION);
            $$->expr_kind_val = EXPR_POST_DEC;
            $$->left = $1;
        }
    ;

argument_list_opt
    : argument_list
        {
            $$ = $1;
        }
    | /* empty */
        {
            $$ = NULL;
        }
    ;

argument_list
    : expr
        {
            $$ = $1;
        }
    | argument_list TOKEN_COMMA expr
        {
            if ($1 == NULL) {
                $$ = $3;
            } else {
                ASTNode *temp = $1;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = $3;
                $$ = $1;
            }
        }
    ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "PARSE ERROR: %s\n", s);
}