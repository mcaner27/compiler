#include <stdio.h>
#include "resolve.h"
#include "symbol.h"

static int error_count = 0;

static void resolve_error(const char *msg, const char *name)
{
    if (name) {
        fprintf(stderr, "RESOLVE ERROR: %s (%s)\n", msg, name);
    } else {
        fprintf(stderr, "RESOLVE ERROR: %s\n", msg);
    }
    error_count++;
}

static void resolve_expr(ASTNode *node, Scope *scope);
static void resolve_stmt(ASTNode *node, Scope *scope);
static void resolve_decl(ASTNode *node, Scope *scope);

static void resolve_expr(ASTNode *node, Scope *scope)
{
    if (!node) return;

    switch (node->expr_kind_val) {
        case EXPR_IDENTIFIER:
            if (node->name && scope_lookup(scope, node->name) == NULL) {
                resolve_error("Undefined identifier", node->name);
            }
            break;

        case EXPR_CALL:
            if (node->name && scope_lookup(scope, node->name) == NULL) {
                resolve_error("Call to undefined function", node->name);
            }
            resolve_expr(node->left, scope);
            break;

        default:
            resolve_expr(node->left, scope);
            resolve_expr(node->right, scope);
            resolve_expr(node->third, scope);
            break;
    }

    resolve_expr(node->next, scope);
}

static void resolve_stmt(ASTNode *node, Scope *scope)
{
    if (!node) return;

    switch (node->stmt_kind_val) {
        case STMT_EXPR:
        case STMT_RETURN:
        case STMT_PRINT:
            resolve_expr(node->left, scope);
            break;

        case STMT_IF:
            resolve_expr(node->left, scope);
            resolve_stmt(node->right, scope);
            break;

        case STMT_IF_ELSE:
            resolve_expr(node->left, scope);
            resolve_stmt(node->right, scope);
            resolve_stmt(node->third, scope);
            break;

        case STMT_FOR:
            resolve_expr(node->left, scope);
            resolve_expr(node->right, scope);
            resolve_expr(node->third, scope);
            if (node->third && node->third->next) {
                resolve_stmt(node->third->next, scope);
            }
            break;

        case STMT_BLOCK:
        {
            Scope *inner = scope_create(scope);
            ASTNode *temp = node->left;

            while (temp) {
                if (temp->type == NODE_DECLARATION) {
                    resolve_decl(temp, inner);
                } else if (temp->type == NODE_STATEMENT) {
                    resolve_stmt(temp, inner);
                }
                temp = temp->next;
            }

            scope_destroy(inner);
            break;
        }

        default:
            break;
    }
}

static void resolve_decl(ASTNode *node, Scope *scope)
{
    if (!node) return;

    if (node->name) {
        if (!scope_bind(scope, node->name, node)) {
            resolve_error("Duplicate declaration in same scope", node->name);
        }
    }

    resolve_expr(node->right, scope);
}

static void resolve_function(ASTNode *node, Scope *scope)
{
    if (!node) return;

    if (node->name) {
        if (!scope_bind(scope, node->name, node)) {
            resolve_error("Duplicate function declaration", node->name);
        }
    }

    Scope *fn_scope = scope_create(scope);

    ASTNode *params = NULL;
    if (node->left) {
        params = node->left->next;
    }

    while (params) {
        if (params->name) {
            if (!scope_bind(fn_scope, params->name, params)) {
                resolve_error("Duplicate parameter name", params->name);
            }
        }
        params = params->next;
    }

    if (node->right) {
        resolve_stmt(node->right, fn_scope);
    }

    scope_destroy(fn_scope);
}

void resolve_ast(ASTNode *node)
{
    Scope *global = scope_create(NULL);
    ASTNode *temp = node;

    while (temp) {
        if (temp->type == NODE_DECLARATION) {
            resolve_decl(temp, global);
        } else if (temp->type == NODE_FUNCTION) {
            resolve_function(temp, global);
        }
        temp = temp->next;
    }

    scope_destroy(global);
}

int resolve_error_count(void)
{
    return error_count;
}
