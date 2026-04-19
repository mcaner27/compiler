#ifndef RESOLVE_H
#define RESOLVE_H

#include "ast.h"

void resolve_ast(ASTNode *node);
int resolve_error_count(void);

#endif
