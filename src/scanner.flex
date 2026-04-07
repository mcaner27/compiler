%{
/*
 * CEN417 - B-Minor Scanner
 * Reads a source file and produces a listing of each token, 
 * annotated with token kind and location. 
 * Includes error recovery and escape sequence handling.
 */

#include <stdio.h>
#include <string.h>

/* Token Enumerations */
typedef enum {
    TOKEN_EOF = 0,
    /* Keywords */
    TOKEN_ARRAY, TOKEN_BOOLEAN, TOKEN_CHAR, TOKEN_ELSE, TOKEN_FALSE,
    TOKEN_FOR, TOKEN_FUNCTION, TOKEN_IF, TOKEN_INTEGER, TOKEN_PRINT,
    TOKEN_RETURN, TOKEN_STRING, TOKEN_TRUE, TOKEN_VOID, TOKEN_WHILE,
    /* Identifiers and Literals */
    TOKEN_IDENTIFIER, TOKEN_INTEGER_LITERAL, TOKEN_STRING_LITERAL, TOKEN_CHARACTER_LITERAL,
    /* Symbols and Operators */
    TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_LBRACKET, TOKEN_RBRACKET, TOKEN_LBRACE, TOKEN_RBRACE,
    TOKEN_COLON, TOKEN_SEMICOLON, TOKEN_COMMA, TOKEN_INCREMENT, TOKEN_DECREMENT,
    TOKEN_EXPONENT, TOKEN_MULTIPLY, TOKEN_DIVIDE, TOKEN_MODULO, TOKEN_ADD, TOKEN_SUBTRACT,
    TOKEN_LESS_THAN, TOKEN_LESS_EQUAL, TOKEN_GREATER_THAN, TOKEN_GREATER_EQUAL,
    TOKEN_EQUAL, TOKEN_NOT_EQUAL, TOKEN_LOGICAL_AND, TOKEN_LOGICAL_OR, TOKEN_LOGICAL_NOT, TOKEN_ASSIGN,
    /* Error state for recovery */
    TOKEN_ERROR
} token_t;

/* Helper function to get token names for printing */
const char* get_token_name(token_t t) {
    switch(t) {
        case TOKEN_ARRAY: return "ARRAY"; case TOKEN_BOOLEAN: return "BOOLEAN";
        case TOKEN_CHAR: return "CHAR"; case TOKEN_ELSE: return "ELSE";
        case TOKEN_FALSE: return "FALSE"; case TOKEN_FOR: return "FOR";
        case TOKEN_FUNCTION: return "FUNCTION"; case TOKEN_IF: return "IF";
        case TOKEN_INTEGER: return "INTEGER"; case TOKEN_PRINT: return "PRINT";
        case TOKEN_RETURN: return "RETURN"; case TOKEN_STRING: return "STRING";
        case TOKEN_TRUE: return "TRUE"; case TOKEN_VOID: return "VOID";
        case TOKEN_WHILE: return "WHILE"; case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_INTEGER_LITERAL: return "INTEGER_LITERAL";
        case TOKEN_STRING_LITERAL: return "STRING_LITERAL";
        case TOKEN_CHARACTER_LITERAL: return "CHARACTER_LITERAL";
        case TOKEN_ERROR: return "SCANNER_ERROR";
        default: return "OPERATOR/SYMBOL";
    }
}
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

/* Regex for handling valid strings and chars with escape sequences */
ESCAPE     \\[nt0\\'"]
CHAR_BODY  ([^\\'\n]|{ESCAPE})
STR_BODY   ([^\\"\n]|{ESCAPE})*

%%

[ \t\r\n]+              { /* Skip whitespaces */ }
"//".* { /* Skip C++ style single-line comments */ }
"/*"([^*]|(\*+[^*/]))*\*+"/" { /* Skip C style multi-line comments */ }

"/*"([^*]|(\*+[^*/]))* { 
    fprintf(stderr, "SCAN ERROR: Unterminated block comment starting at line %d\n", yylineno); 
    return TOKEN_ERROR; 
}

"array"     { return TOKEN_ARRAY; }
"boolean"   { return TOKEN_BOOLEAN; }
"char"      { return TOKEN_CHAR; }
"else"      { return TOKEN_ELSE; }
"false"     { return TOKEN_FALSE; }
"for"       { return TOKEN_FOR; }
"function"  { return TOKEN_FUNCTION; }
"if"        { return TOKEN_IF; }
"integer"   { return TOKEN_INTEGER; }
"print"     { return TOKEN_PRINT; }
"return"    { return TOKEN_RETURN; }
"string"    { return TOKEN_STRING; }
"true"      { return TOKEN_TRUE; }
"void"      { return TOKEN_VOID; }
"while"     { return TOKEN_WHILE; }

"++"        { return TOKEN_INCREMENT; }
"--"        { return TOKEN_DECREMENT; }
"=="        { return TOKEN_EQUAL; }
"!="        { return TOKEN_NOT_EQUAL; }
"<="        { return TOKEN_LESS_EQUAL; }
">="        { return TOKEN_GREATER_EQUAL; }
"&&"        { return TOKEN_LOGICAL_AND; }
"||"        { return TOKEN_LOGICAL_OR; }

"("         { return TOKEN_LPAREN; }
")"         { return TOKEN_RPAREN; }
"["         { return TOKEN_LBRACKET; }
"]"         { return TOKEN_RBRACKET; }
"{"         { return TOKEN_LBRACE; }
"}"         { return TOKEN_RBRACE; }
":"         { return TOKEN_COLON; }
";"         { return TOKEN_SEMICOLON; }
","         { return TOKEN_COMMA; }
"^"         { return TOKEN_EXPONENT; }
"*"         { return TOKEN_MULTIPLY; }
"/"         { return TOKEN_DIVIDE; }
"%"         { return TOKEN_MODULO; }
"+"         { return TOKEN_ADD; }
"-"         { return TOKEN_SUBTRACT; }
"<"         { return TOKEN_LESS_THAN; }
">"         { return TOKEN_GREATER_THAN; }
"!"         { return TOKEN_LOGICAL_NOT; }
"="         { return TOKEN_ASSIGN; }

{DIGIT}+    { return TOKEN_INTEGER_LITERAL; }

\'{CHAR_BODY}\' { return TOKEN_CHARACTER_LITERAL; }
\'[^\']*\'      { 
    fprintf(stderr, "SCAN ERROR: Invalid character literal '%s' at line %d\n", yytext, yylineno); 
    return TOKEN_ERROR; 
}

\"{STR_BODY}\" {
    if(yyleng > 256) {
        fprintf(stderr, "SCAN ERROR: String literal exceeds 256 characters at line %d\n", yylineno);
        return TOKEN_ERROR;
    }
    return TOKEN_STRING_LITERAL; 
}
\"[^\"]* { 
    fprintf(stderr, "SCAN ERROR: Unterminated string literal starting at line %d\n", yylineno); 
    return TOKEN_ERROR; 
}

{ID} { 
    if(yyleng > 256) {
        fprintf(stderr, "SCAN ERROR: Identifier '%s' exceeds 256 characters at line %d\n", yytext, yylineno);
        return TOKEN_ERROR;
    }
    return TOKEN_IDENTIFIER; 
}

. { 
    fprintf(stderr, "SCAN ERROR: Unknown character '%s' at line %d\n", yytext, yylineno); 
    return TOKEN_ERROR; 
}

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: ./scanner <source_file>\n");
        return 1;
    }
    
    token_t token;
    
    printf("--- B-MINOR SCANNER OUTPUT ---\n");
    printf("%-20s %-10s %s\n", "TOKEN KIND", "LINE", "LEXEME/TEXT");
    printf("--------------------------------------------------\n");

    while ((token = yylex())) {
        if (token != TOKEN_ERROR) {
            printf("%-20s %-10d %s\n", get_token_name(token), yylineno, yytext);
        }
    }
    
    printf("--------------------------------------------------\n");
    printf("Scan complete.\n");
    return 0;
}