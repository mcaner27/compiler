/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/parser.y"

    #include "ast.h"

#line 53 "src/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_ARRAY = 258,             /* TOKEN_ARRAY  */
    TOKEN_BOOLEAN = 259,           /* TOKEN_BOOLEAN  */
    TOKEN_CHAR = 260,              /* TOKEN_CHAR  */
    TOKEN_ELSE = 261,              /* TOKEN_ELSE  */
    TOKEN_FALSE = 262,             /* TOKEN_FALSE  */
    TOKEN_FOR = 263,               /* TOKEN_FOR  */
    TOKEN_FUNCTION = 264,          /* TOKEN_FUNCTION  */
    TOKEN_IF = 265,                /* TOKEN_IF  */
    TOKEN_INTEGER = 266,           /* TOKEN_INTEGER  */
    TOKEN_PRINT = 267,             /* TOKEN_PRINT  */
    TOKEN_RETURN = 268,            /* TOKEN_RETURN  */
    TOKEN_STRING = 269,            /* TOKEN_STRING  */
    TOKEN_TRUE = 270,              /* TOKEN_TRUE  */
    TOKEN_VOID = 271,              /* TOKEN_VOID  */
    TOKEN_WHILE = 272,             /* TOKEN_WHILE  */
    TOKEN_IDENTIFIER = 273,        /* TOKEN_IDENTIFIER  */
    TOKEN_INTEGER_LITERAL = 274,   /* TOKEN_INTEGER_LITERAL  */
    TOKEN_STRING_LITERAL = 275,    /* TOKEN_STRING_LITERAL  */
    TOKEN_CHARACTER_LITERAL = 276, /* TOKEN_CHARACTER_LITERAL  */
    TOKEN_LPAREN = 277,            /* TOKEN_LPAREN  */
    TOKEN_RPAREN = 278,            /* TOKEN_RPAREN  */
    TOKEN_LBRACKET = 279,          /* TOKEN_LBRACKET  */
    TOKEN_RBRACKET = 280,          /* TOKEN_RBRACKET  */
    TOKEN_LBRACE = 281,            /* TOKEN_LBRACE  */
    TOKEN_RBRACE = 282,            /* TOKEN_RBRACE  */
    TOKEN_COLON = 283,             /* TOKEN_COLON  */
    TOKEN_SEMICOLON = 284,         /* TOKEN_SEMICOLON  */
    TOKEN_COMMA = 285,             /* TOKEN_COMMA  */
    TOKEN_INCREMENT = 286,         /* TOKEN_INCREMENT  */
    TOKEN_DECREMENT = 287,         /* TOKEN_DECREMENT  */
    TOKEN_EXPONENT = 288,          /* TOKEN_EXPONENT  */
    TOKEN_MULTIPLY = 289,          /* TOKEN_MULTIPLY  */
    TOKEN_DIVIDE = 290,            /* TOKEN_DIVIDE  */
    TOKEN_MODULO = 291,            /* TOKEN_MODULO  */
    TOKEN_ADD = 292,               /* TOKEN_ADD  */
    TOKEN_SUBTRACT = 293,          /* TOKEN_SUBTRACT  */
    TOKEN_LESS_THAN = 294,         /* TOKEN_LESS_THAN  */
    TOKEN_LESS_EQUAL = 295,        /* TOKEN_LESS_EQUAL  */
    TOKEN_GREATER_THAN = 296,      /* TOKEN_GREATER_THAN  */
    TOKEN_GREATER_EQUAL = 297,     /* TOKEN_GREATER_EQUAL  */
    TOKEN_EQUAL = 298,             /* TOKEN_EQUAL  */
    TOKEN_NOT_EQUAL = 299,         /* TOKEN_NOT_EQUAL  */
    TOKEN_LOGICAL_AND = 300,       /* TOKEN_LOGICAL_AND  */
    TOKEN_LOGICAL_OR = 301,        /* TOKEN_LOGICAL_OR  */
    TOKEN_LOGICAL_NOT = 302,       /* TOKEN_LOGICAL_NOT  */
    TOKEN_ASSIGN = 303,            /* TOKEN_ASSIGN  */
    TOKEN_ERROR = 304,             /* TOKEN_ERROR  */
    LOWER_THAN_ELSE = 305          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "src/parser.y"

    ASTNode *node;
    char *text;
    int number;

#line 126 "src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
