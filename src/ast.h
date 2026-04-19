#ifndef AST_H
#define AST_H

typedef enum {
    NODE_PROGRAM,
    NODE_DECLARATION,
    NODE_FUNCTION,
    NODE_STATEMENT,
    NODE_EXPRESSION,
    NODE_TYPE
} node_type;

typedef enum {
    TYPE_NONE,
    TYPE_INTEGER,
    TYPE_BOOLEAN,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_VOID
} type_kind;

typedef enum {
    STMT_NONE,
    STMT_RETURN,
    STMT_PRINT,
    STMT_IF,
    STMT_IF_ELSE,
    STMT_FOR,
    STMT_BLOCK,
    STMT_EXPR
} stmt_kind;

typedef enum {
    EXPR_NONE,
    EXPR_IDENTIFIER,
    EXPR_INTEGER_LITERAL,
    EXPR_STRING_LITERAL,
    EXPR_CHAR_LITERAL,
    EXPR_BOOLEAN_LITERAL,
    EXPR_ADD,
    EXPR_SUB,
    EXPR_MUL,
    EXPR_DIV,
    EXPR_MOD,
    EXPR_EXP,
    EXPR_LT,
    EXPR_LE,
    EXPR_GT,
    EXPR_GE,
    EXPR_EQ,
    EXPR_NE,
    EXPR_AND,
    EXPR_OR,
    EXPR_NOT,
    EXPR_ASSIGN,
    EXPR_CALL,
    EXPR_INDEX,
    EXPR_POST_INC,
    EXPR_POST_DEC,
    EXPR_NEG
} expr_kind;

typedef struct ASTNode {
    node_type type;
    type_kind type_kind_val;
    stmt_kind stmt_kind_val;
    expr_kind expr_kind_val;

    char *name;
    char *string_value;
    int int_value;

    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *third;
    struct ASTNode *next;
} ASTNode;

ASTNode *create_node(node_type type);
void print_ast(ASTNode *node, int level);
void print_pretty(ASTNode *node, int indent);

#endif