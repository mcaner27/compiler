#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "ast.h"

typedef enum {
    CHECK_TYPE_UNKNOWN,
    CHECK_TYPE_INTEGER,
    CHECK_TYPE_BOOLEAN,
    CHECK_TYPE_CHAR,
    CHECK_TYPE_STRING,
    CHECK_TYPE_VOID,
    CHECK_TYPE_ERROR
} check_type;

check_type expr_type(ASTNode *node);
void typecheck_ast(ASTNode *node);
int typecheck_error_count(void);

#endif