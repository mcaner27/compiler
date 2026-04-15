#include <stdio.h>
#include "typecheck.h"

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
        case TYPE_CHAR: return CHECK_TYPE_CHAR;
        case TYPE_STRING: return CHECK_TYPE_STRING;
        case TYPE_VOID: return CHECK_TYPE_VOID;
        default: return CHECK_TYPE_UNKNOWN;
    }
}

check_type expr_type(ASTNode *node)
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
            return CHECK_TYPE_UNKNOWN;

        case EXPR_ADD:
        case EXPR_SUB:
        case EXPR_MUL:
        case EXPR_DIV:
        case EXPR_MOD:
        case EXPR_EXP:
        {
            check_type left = expr_type(node->left);
            check_type right = expr_type(node->right);

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
            check_type left = expr_type(node->left);
            check_type right = expr_type(node->right);

            if (left != CHECK_TYPE_INTEGER || right != CHECK_TYPE_INTEGER) {
                report_type_error("Comparison operators require integer operands.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_BOOLEAN;
        }

        case EXPR_EQ:
        case EXPR_NE:
        {
            check_type left = expr_type(node->left);
            check_type right = expr_type(node->right);

            if (left != right) {
                report_type_error("Equality operands must have the same type.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_BOOLEAN;
        }

        case EXPR_AND:
        case EXPR_OR:
        {
            check_type left = expr_type(node->left);
            check_type right = expr_type(node->right);

            if (left != CHECK_TYPE_BOOLEAN || right != CHECK_TYPE_BOOLEAN) {
                report_type_error("Logical operators require boolean operands.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_BOOLEAN;
        }

        case EXPR_NOT:
        {
            check_type left = expr_type(node->left);
            if (left != CHECK_TYPE_BOOLEAN) {
                report_type_error("Logical NOT requires a boolean operand.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_BOOLEAN;
        }

        case EXPR_NEG:
        {
            check_type left = expr_type(node->left);
            if (left != CHECK_TYPE_INTEGER) {
                report_type_error("Unary minus requires an integer operand.");
                return CHECK_TYPE_ERROR;
            }
            return CHECK_TYPE_INTEGER;
        }

        case EXPR_ASSIGN:
        {
            check_type left = expr_type(node->left);
            check_type right = expr_type(node->right);

            if (left != CHECK_TYPE_UNKNOWN && right != CHECK_TYPE_UNKNOWN && left != right) {
                report_type_error("Assignment types do not match.");
                return CHECK_TYPE_ERROR;
            }
            return left;
        }

        case EXPR_CALL:
            return CHECK_TYPE_UNKNOWN;

        case EXPR_INDEX:
            return CHECK_TYPE_UNKNOWN;

        case EXPR_POST_INC:
        case EXPR_POST_DEC:
        {
            check_type left = expr_type(node->left);
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

static void typecheck_statement(ASTNode *node, check_type expected_return_type)
{
    if (node == NULL) return;

    switch (node->stmt_kind_val) {
        case STMT_EXPR:
            expr_type(node->left);
            break;

        case STMT_RETURN:
        {
            if (node->left == NULL) {
                if (expected_return_type != CHECK_TYPE_VOID) {
                    report_type_error("Non-void function must return a value.");
                }
            } else {
                check_type actual = expr_type(node->left);
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
                expr_type(temp);
                temp = temp->next;
            }
            break;
        }

        case STMT_IF:
        {
            check_type cond = expr_type(node->left);
            if (cond != CHECK_TYPE_BOOLEAN && cond != CHECK_TYPE_UNKNOWN) {
                report_type_error("If condition must be boolean.");
            }
            typecheck_statement(node->right, expected_return_type);
            break;
        }

        case STMT_IF_ELSE:
        {
            check_type cond = expr_type(node->left);
            if (cond != CHECK_TYPE_BOOLEAN && cond != CHECK_TYPE_UNKNOWN) {
                report_type_error("If-else condition must be boolean.");
            }
            typecheck_statement(node->right, expected_return_type);
            typecheck_statement(node->third, expected_return_type);
            break;
        }

        case STMT_FOR:
        {
            if (node->left) expr_type(node->left);
            if (node->right) {
                check_type cond = expr_type(node->right);
                if (cond != CHECK_TYPE_BOOLEAN && cond != CHECK_TYPE_UNKNOWN) {
                    report_type_error("For loop condition must be boolean.");
                }
            }
            if (node->third) expr_type(node->third);
            if (node->third && node->third->next) {
                typecheck_statement(node->third->next, expected_return_type);
            }
            break;
        }

        case STMT_BLOCK:
        {
            ASTNode *temp = node->left;
            while (temp != NULL) {
                if (temp->type == NODE_STATEMENT) {
                    typecheck_statement(temp, expected_return_type);
                }
                temp = temp->next;
            }
            break;
        }

        default:
            break;
    }
}

static void typecheck_declaration(ASTNode *node)
{
    if (node == NULL) return;

    check_type declared = ast_type_to_check_type(node->left);

    if (node->right != NULL) {
        check_type actual = expr_type(node->right);

        if (declared != CHECK_TYPE_UNKNOWN &&
            actual != CHECK_TYPE_UNKNOWN &&
            declared != actual) {
            report_type_error("Declaration initializer type does not match declared type.");
        }
    }
}

static void typecheck_function(ASTNode *node)
{
    if (node == NULL) return;

    check_type return_type = ast_type_to_check_type(node->left);

    if (node->right != NULL) {
        typecheck_statement(node->right, return_type);
    }
}

void typecheck_ast(ASTNode *node)
{
    ASTNode *temp = node;

    while (temp != NULL) {
        switch (temp->type) {
            case NODE_DECLARATION:
                typecheck_declaration(temp);
                break;

            case NODE_FUNCTION:
                typecheck_function(temp);
                break;

            case NODE_STATEMENT:
                typecheck_statement(temp, CHECK_TYPE_UNKNOWN);
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