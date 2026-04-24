#include <stdio.h>
#include "typecheck.h"
#include "symbol.h"

static int error_count = 0;

static void report_type_error(const char *msg)
{
    fprintf(stderr, "TYPE ERROR: %s\n", msg);
    error_count++;
}

static check_type ast_type_to_check_type(ASTNode *node)
{
    if (node == NULL) return CHECK_TYPE_UNKNOWN;

    switch (node->type_kind_val) {
        case TYPE_INTEGER: return CHECK_TYPE_INTEGER;
        case TYPE_BOOLEAN: return CHECK_TYPE_BOOLEAN;
        case TYPE_CHAR:    return CHECK_TYPE_CHAR;
        case TYPE_STRING:  return CHECK_TYPE_STRING;
        case TYPE_VOID:    return CHECK_TYPE_VOID;
        default:           return CHECK_TYPE_UNKNOWN;
    }
}

static check_type expr_type_with_scope(ASTNode *node, Scope *scope);

check_type expr_type(ASTNode *node)
{
    return expr_type_with_scope(node, NULL);
}

static check_type expr_type_with_scope(ASTNode *node, Scope *scope)
{
    if (node == NULL) return CHECK_TYPE_UNKNOWN;

    switch (node->expr_kind_val) {
        case EXPR_INTEGER_LITERAL:
            return CHECK_TYPE_INTEGER;

        case EXPR_STRING_LITERAL:
            return CHECK_TYPE_STRING;

        case EXPR_CHAR_LITERAL:
            return CHECK_TYPE_CHAR;

        case EXPR_BOOLEAN_LITERAL:
            return CHECK_TYPE_BOOLEAN;

        case EXPR_IDENTIFIER:
        {
            if (scope == NULL) return CHECK_TYPE_UNKNOWN;
            if (node->name == NULL) return CHECK_TYPE_UNKNOWN;

            ASTNode *decl = scope_lookup(scope, node->name);
            if (decl == NULL) return CHECK_TYPE_UNKNOWN;

            return ast_type_to_check_type(decl->left);
        }

        case EXPR_ADD:
        case EXPR_SUB:
        case EXPR_MUL:
        case EXPR_DIV:
        case EXPR_MOD:
        case EXPR_EXP:
        {
            check_type left = expr_type_with_scope(node->left, scope);
            check_type right = expr_type_with_scope(node->right, scope);

            if (left != CHECK_TYPE_INTEGER || right != CHECK_TYPE_INTEGER) {
                report_type_error("Arithmetic expressions require integer operands.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_INTEGER;
        }

        case EXPR_LT:
        case EXPR_LE:
        case EXPR_GT:
        case EXPR_GE:
        {
            check_type left = expr_type_with_scope(node->left, scope);
            check_type right = expr_type_with_scope(node->right, scope);

            if (left != CHECK_TYPE_INTEGER || right != CHECK_TYPE_INTEGER) {
                report_type_error("Comparison operators require integer operands.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_BOOLEAN;
        }

        case EXPR_EQ:
        case EXPR_NE:
        {
            check_type left = expr_type_with_scope(node->left, scope);
            check_type right = expr_type_with_scope(node->right, scope);

            if (left != right && left != CHECK_TYPE_UNKNOWN && right != CHECK_TYPE_UNKNOWN) {
                report_type_error("Equality operands must have the same type.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_BOOLEAN;
        }

        case EXPR_AND:
        case EXPR_OR:
        {
            check_type left = expr_type_with_scope(node->left, scope);
            check_type right = expr_type_with_scope(node->right, scope);

            if (left != CHECK_TYPE_BOOLEAN || right != CHECK_TYPE_BOOLEAN) {
                report_type_error("Logical operators require boolean operands.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_BOOLEAN;
        }

        case EXPR_NOT:
        {
            check_type left = expr_type_with_scope(node->left, scope);
            if (left != CHECK_TYPE_BOOLEAN && left != CHECK_TYPE_UNKNOWN) {
                report_type_error("Logical NOT requires a boolean operand.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_BOOLEAN;
        }

        case EXPR_NEG:
        {
            check_type left = expr_type_with_scope(node->left, scope);
            if (left != CHECK_TYPE_INTEGER && left != CHECK_TYPE_UNKNOWN) {
                report_type_error("Unary minus requires an integer operand.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_INTEGER;
        }

        case EXPR_ASSIGN:
        {
            check_type left = expr_type_with_scope(node->left, scope);
            check_type right = expr_type_with_scope(node->right, scope);

            if (left != CHECK_TYPE_UNKNOWN && right != CHECK_TYPE_UNKNOWN && left != right) {
                report_type_error("Assignment types do not match.");
                return CHECK_TYPE_ERROR;
            }
            return left;
        }

        case EXPR_CALL:
        {
            if (scope == NULL || node->name == NULL) return CHECK_TYPE_UNKNOWN;

            ASTNode *func_decl = scope_lookup(scope, node->name);
            if (func_decl == NULL || func_decl->type != NODE_FUNCTION) {
                return CHECK_TYPE_UNKNOWN;
            }

            /* Check argument types and count */
            ASTNode *param = (func_decl->left && func_decl->left->next)
                             ? func_decl->left->next : NULL;
            ASTNode *arg = node->left;
            int idx = 1;
            while (param != NULL && arg != NULL) {
                check_type p_type = ast_type_to_check_type(param->left);
                check_type a_type = expr_type_with_scope(arg, scope);
                if (p_type != CHECK_TYPE_UNKNOWN && a_type != CHECK_TYPE_UNKNOWN
                    && p_type != a_type) {
                    char msg[256];
                    snprintf(msg, sizeof(msg),
                             "Argument %d type mismatch in call to '%s'.",
                             idx, node->name);
                    report_type_error(msg);
                }
                param = param->next;
                arg   = arg->next;
                idx++;
            }
            if (param != NULL || arg != NULL) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                         "Wrong number of arguments in call to '%s'.",
                         node->name);
                report_type_error(msg);
            }

            return ast_type_to_check_type(func_decl->left);
        }

        case EXPR_INDEX:
        {
            expr_type_with_scope(node->left, scope);
            check_type idx_type = expr_type_with_scope(node->right, scope);

            if (idx_type != CHECK_TYPE_INTEGER && idx_type != CHECK_TYPE_UNKNOWN) {
                report_type_error("Array index must be integer.");
                return CHECK_TYPE_ERROR;
            }

            return CHECK_TYPE_UNKNOWN;
        }

        case EXPR_POST_INC:
        case EXPR_POST_DEC:
        {
            check_type left = expr_type_with_scope(node->left, scope);
            if (left != CHECK_TYPE_INTEGER && left != CHECK_TYPE_UNKNOWN) {
                report_type_error("Increment/decrement requires integer operand.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_INTEGER;
        }

        default:
            return CHECK_TYPE_UNKNOWN;
    }
}

static void typecheck_statement_with_scope(ASTNode *node, check_type expected_return_type, Scope *scope);



static void typecheck_statement_with_scope(ASTNode *node, check_type expected_return_type, Scope *scope)
{
    if (node == NULL) return;

    switch (node->stmt_kind_val) {
        case STMT_EXPR:
            expr_type_with_scope(node->left, scope);
            break;

        case STMT_RETURN:
        {
            if (node->left == NULL) {
                if (expected_return_type != CHECK_TYPE_VOID) {
                    report_type_error("Non-void function must return a value.");
                }
            } else {
                check_type actual = expr_type_with_scope(node->left, scope);
                if (expected_return_type != CHECK_TYPE_UNKNOWN &&
                    actual != CHECK_TYPE_UNKNOWN &&
                    actual != expected_return_type) {
                    report_type_error("Return type does not match function type.");
                }
            }
            break;
        }

        case STMT_PRINT:
        {
            ASTNode *temp = node->left;
            while (temp != NULL) {
                expr_type_with_scope(temp, scope);
                temp = temp->next;
            }
            break;
        }

        case STMT_IF:
        {
            check_type cond = expr_type_with_scope(node->left, scope);
            if (cond != CHECK_TYPE_BOOLEAN && cond != CHECK_TYPE_UNKNOWN) {
                report_type_error("If condition must be boolean.");
            }
            typecheck_statement_with_scope(node->right, expected_return_type, scope);
            break;
        }

        case STMT_WHILE:
        {
            check_type cond = expr_type_with_scope(node->left, scope);
            if (cond != CHECK_TYPE_BOOLEAN && cond != CHECK_TYPE_UNKNOWN) {
                report_type_error("While condition must be boolean.");
            }
            typecheck_statement_with_scope(node->right, expected_return_type, scope);
            break;
        }

        case STMT_IF_ELSE:
        {
            check_type cond = expr_type_with_scope(node->left, scope);
            if (cond != CHECK_TYPE_BOOLEAN && cond != CHECK_TYPE_UNKNOWN) {
                report_type_error("If-else condition must be boolean.");
            }
            typecheck_statement_with_scope(node->right, expected_return_type, scope);
            typecheck_statement_with_scope(node->third, expected_return_type, scope);
            break;
        }

        case STMT_FOR:
        {
            if (node->left) expr_type_with_scope(node->left, scope);
            if (node->right) {
                check_type cond = expr_type_with_scope(node->right, scope);
                if (cond != CHECK_TYPE_BOOLEAN && cond != CHECK_TYPE_UNKNOWN) {
                    report_type_error("For loop condition must be boolean.");
                }
            }
            if (node->third) expr_type_with_scope(node->third, scope);
            if (node->third && node->third->next) {
                typecheck_statement_with_scope(node->third->next, expected_return_type, scope);
            }
            break;
        }

        case STMT_BLOCK:
        {
            Scope *inner = scope_create(scope);
            ASTNode *temp = node->left;
            while (temp != NULL) {
                if (temp->type == NODE_STATEMENT) {
                    typecheck_statement_with_scope(temp, expected_return_type, inner);
                } else if (temp->type == NODE_DECLARATION) {
                    /* First check the initializer using the current inner scope */
                    check_type declared = ast_type_to_check_type(temp->left);
                    if (temp->right != NULL) {
                        check_type actual = expr_type_with_scope(temp->right, inner);
                        if (declared != CHECK_TYPE_UNKNOWN &&
                            actual != CHECK_TYPE_UNKNOWN &&
                            declared != actual) {
                            report_type_error("Declaration initializer type does not match declared type.");
                        }
                    }
                    /* Then bind the variable so subsequent statements can see it */
                    if (temp->name) {
                        scope_bind(inner, temp->name, temp);
                    }
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

static void typecheck_declaration_with_scope(ASTNode *node, Scope *scope)
{
    if (node == NULL) return;

    check_type declared = ast_type_to_check_type(node->left);

    if (node->right != NULL) {
        check_type actual = expr_type_with_scope(node->right, scope);

        if (declared != CHECK_TYPE_UNKNOWN &&
            actual != CHECK_TYPE_UNKNOWN &&
            declared != actual) {
            report_type_error("Declaration initializer type does not match declared type.");
        }
    }
}

static void typecheck_function_with_scope(ASTNode *node, Scope *scope)
{
    if (node == NULL) return;

    check_type return_type = ast_type_to_check_type(node->left);

    /* Create a function scope and bind parameters so the body can see them */
    Scope *fn_scope = scope_create(scope);

    ASTNode *params = NULL;
    if (node->left) {
        params = node->left->next;
    }
    while (params) {
        if (params->name) {
            scope_bind(fn_scope, params->name, params);
        }
        params = params->next;
    }

    if (node->right != NULL) {
        typecheck_statement_with_scope(node->right, return_type, fn_scope);
    }

    scope_destroy(fn_scope);
}

void typecheck_ast(ASTNode *node)
{
    typecheck_ast_with_scope(node, NULL);
}

void typecheck_ast_with_scope(ASTNode *node, Scope *scope)
{
    ASTNode *temp = node;

    while (temp != NULL) {
        switch (temp->type) {
            case NODE_DECLARATION:
                typecheck_declaration_with_scope(temp, scope);
                break;

            case NODE_FUNCTION:
                typecheck_function_with_scope(temp, scope);
                break;

            case NODE_STATEMENT:
                typecheck_statement_with_scope(temp, CHECK_TYPE_UNKNOWN, scope);
                break;

            default:
                break;
        }
        temp = temp->next;
    }
}

int typecheck_error_count(void)
{
    return error_count;
}