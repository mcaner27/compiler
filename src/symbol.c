#include <stdlib.h>
#include <string.h>
#include "symbol.h"

Scope *scope_create(Scope *parent)
{
    Scope *scope = malloc(sizeof(Scope));
    scope->symbols = NULL;
    scope->parent = parent;
    return scope;
}

void scope_destroy(Scope *scope)
{
    if (!scope) return;

    Symbol *s = scope->symbols;
    while (s) {
        Symbol *next = s->next;
        free(s);
        s = next;
    }

    free(scope);
}

ASTNode *scope_lookup_current(Scope *scope, const char *name)
{
    if (!scope || !name) return NULL;

    Symbol *s = scope->symbols;
    while (s) {
        if (strcmp(s->name, name) == 0) {
            return s->node;
        }
        s = s->next;
    }

    return NULL;
}

ASTNode *scope_lookup(Scope *scope, const char *name)
{
    Scope *cur = scope;

    while (cur) {
        ASTNode *found = scope_lookup_current(cur, name);
        if (found) return found;
        cur = cur->parent;
    }

    return NULL;
}

int scope_bind(Scope *scope, const char *name, ASTNode *node)
{
    if (!scope || !name) return 0;

    if (scope_lookup_current(scope, name) != NULL) {
        return 0;
    }

    Symbol *s = malloc(sizeof(Symbol));
    s->name = (char *)name;
    s->node = node;
    s->next = scope->symbols;
    scope->symbols = s;

    return 1;
}
