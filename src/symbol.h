#ifndef SYMBOL_H
#define SYMBOL_H

#include "ast.h"

typedef struct Symbol {
    char *name;
    ASTNode *node;
    struct Symbol *next;
} Symbol;

typedef struct Scope {
    Symbol *symbols;
    struct Scope *parent;
} Scope;

Scope *scope_create(Scope *parent);
void scope_destroy(Scope *scope);

int scope_bind(Scope *scope, const char *name, ASTNode *node);
ASTNode *scope_lookup(Scope *scope, const char *name);
ASTNode *scope_lookup_current(Scope *scope, const char *name);

#endif
