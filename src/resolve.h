#ifndef RESOLVE_H
#define RESOLVE_H

#include "ast.h"
#include "symbol.h"

void resolve_ast(ASTNode *node);
Scope *resolve_and_return_scope(ASTNode *node);
int resolve_error_count(void);

#endif