#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

ASTNode *create_node(node_type type)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;

    node->type_kind_val = TYPE_NONE;
    node->stmt_kind_val = STMT_NONE;
    node->expr_kind_val = EXPR_NONE;

    node->name = NULL;
    node->string_value = NULL;
    node->int_value = 0;

    node->left = NULL;
    node->right = NULL;
    node->third = NULL;
    node->next = NULL;

    return node;
}
static void print_indent(int level)
{
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
}

static const char *node_type_to_string(node_type type)
{
    switch (type) {
        case NODE_PROGRAM: return "PROGRAM";
        case NODE_DECLARATION: return "DECLARATION";
        case NODE_FUNCTION: return "FUNCTION";
        case NODE_STATEMENT: return "STATEMENT";
        case NODE_EXPRESSION: return "EXPRESSION";
        case NODE_TYPE: return "TYPE";
        default: return "UNKNOWN";
    }
}

void print_ast(ASTNode *node, int level)
{
    while (node != NULL) {
        print_indent(level);
        printf("%s\n", node_type_to_string(node->type));

        if (node->left != NULL) {
            print_indent(level);
            printf("LEFT:\n");
            print_ast(node->left, level + 1);
        }

        if (node->right != NULL) {
            print_indent(level);
            printf("RIGHT:\n");
            print_ast(node->right, level + 1);
        }

        if (node->third != NULL) {
            print_indent(level);
            printf("THIRD:\n");
            print_ast(node->third, level + 1);
        }

        node = node->next;

        if (node != NULL) {
            print_indent(level);
            printf("NEXT:\n");
        }
    }
}

static void print_type_node(ASTNode *node)
{
    if (node == NULL) {
        printf("unknown");
        return;
    }

    /* Şimdilik parser type node'larında detay tutulmuyor */
    printf("type");
}

static void print_expr(ASTNode *node);

static void print_expr_list(ASTNode *node)
{
    ASTNode *temp = node;
    while (temp != NULL) {
        print_expr(temp);
        if (temp->next != NULL) {
            printf(", ");
        }
        temp = temp->next;
    }
}

static void print_expr(ASTNode *node)
{
    if (node == NULL) {
        return;
    }

    switch (node->expr_kind_val) {
        case EXPR_IDENTIFIER:
            if (node->name != NULL) printf("%s", node->name);
            else printf("id");
            break;

        case EXPR_INTEGER_LITERAL:
            printf("%d", node->int_value);
            break;

        case EXPR_STRING_LITERAL:
            if (node->string_value != NULL) printf("\"%s\"", node->string_value);
            else printf("\"string\"");
            break;

        case EXPR_BOOLEAN_LITERAL:
            printf("%s", node->int_value ? "true" : "false");
            break;

        case EXPR_ADD:
            print_expr(node->left);
            printf(" + ");
            print_expr(node->right);
            break;

        case EXPR_SUB:
            print_expr(node->left);
            printf(" - ");
            print_expr(node->right);
            break;

        case EXPR_MUL:
            print_expr(node->left);
            printf(" * ");
            print_expr(node->right);
            break;

        case EXPR_DIV:
            print_expr(node->left);
            printf(" / ");
            print_expr(node->right);
            break;

        case EXPR_MOD:
            print_expr(node->left);
            printf(" %% ");
            print_expr(node->right);
            break;

        case EXPR_EXP:
            print_expr(node->left);
            printf(" ^ ");
            print_expr(node->right);
            break;

        case EXPR_LT:
            print_expr(node->left);
            printf(" < ");
            print_expr(node->right);
            break;

        case EXPR_LE:
            print_expr(node->left);
            printf(" <= ");
            print_expr(node->right);
            break;

        case EXPR_GT:
            print_expr(node->left);
            printf(" > ");
            print_expr(node->right);
            break;

        case EXPR_GE:
            print_expr(node->left);
            printf(" >= ");
            print_expr(node->right);
            break;

        case EXPR_EQ:
            print_expr(node->left);
            printf(" == ");
            print_expr(node->right);
            break;

        case EXPR_NE:
            print_expr(node->left);
            printf(" != ");
            print_expr(node->right);
            break;

        case EXPR_AND:
            print_expr(node->left);
            printf(" && ");
            print_expr(node->right);
            break;

        case EXPR_OR:
            print_expr(node->left);
            printf(" || ");
            print_expr(node->right);
            break;

        case EXPR_NOT:
            printf("!");
            print_expr(node->left);
            break;

        case EXPR_NEG:
            printf("-");
            print_expr(node->left);
            break;

        case EXPR_ASSIGN:
            print_expr(node->left);
            printf(" = ");
            print_expr(node->right);
            break;

        case EXPR_INDEX:
            print_expr(node->left);
            printf("[");
            print_expr(node->right);
            printf("]");
            break;

        case EXPR_CALL:
            if (node->name != NULL) printf("%s", node->name);
            else printf("func");
            printf("(");
            print_expr_list(node->left);
            printf(")");
            break;

        case EXPR_POST_INC:
            print_expr(node->left);
            printf("++");
            break;

        case EXPR_POST_DEC:
            print_expr(node->left);
            printf("--");
            break;

        default:
            printf("expr");
            break;
    }
}

static void print_statement(ASTNode *node, int indent);

static void print_block(ASTNode *node, int indent)
{
    printf("{\n");

    ASTNode *stmt = node;
    while (stmt != NULL) {
        print_statement(stmt, indent + 1);
        stmt = stmt->next;
    }

    print_indent(indent);
    printf("}\n");
}

static void print_declaration(ASTNode *node, int indent)
{
    print_indent(indent);

    if (node->name != NULL) printf("%s", node->name);
    else printf("var");

    printf(": ");

    if (node->left != NULL) {
        print_type_node(node->left);
    } else {
        printf("type");
    }

    if (node->right != NULL) {
        printf(" = ");
        print_expr(node->right);
    }

    printf(";\n");
}

static void print_function(ASTNode *node, int indent)
{
    print_indent(indent);

    if (node->name != NULL) printf("%s", node->name);
    else printf("func");

    printf(": function ");

    if (node->left != NULL) {
        print_type_node(node->left);
    } else {
        printf("type");
    }

    printf(" () = ");

    if (node->right != NULL && node->right->stmt_kind_val == STMT_BLOCK) {
        print_block(node->right->left, indent);
    } else {
        printf("{ }\n");
    }
}

static void print_statement(ASTNode *node, int indent)
{
    if (node == NULL) return;

    switch (node->stmt_kind_val) {
        case STMT_EXPR:
            print_indent(indent);
            print_expr(node->left);
            printf(";\n");
            break;

        case STMT_RETURN:
            print_indent(indent);
            printf("return");
            if (node->left != NULL) {
                printf(" ");
                print_expr(node->left);
            }
            printf(";\n");
            break;

        case STMT_PRINT:
            print_indent(indent);
            printf("print ");
            print_expr_list(node->left);
            printf(";\n");
            break;

        case STMT_BLOCK:
            print_indent(indent);
            print_block(node->left, indent);
            break;

        case STMT_IF:
            print_indent(indent);
            printf("if (");
            print_expr(node->left);
            printf(") ");
            if (node->right != NULL && node->right->stmt_kind_val == STMT_BLOCK) {
                print_block(node->right->left, indent);
            } else {
                printf("\n");
                print_statement(node->right, indent + 1);
            }
            break;

        case STMT_IF_ELSE:
            print_indent(indent);
            printf("if (");
            print_expr(node->left);
            printf(") ");
            if (node->right != NULL && node->right->stmt_kind_val == STMT_BLOCK) {
                print_block(node->right->left, indent);
            } else {
                printf("\n");
                print_statement(node->right, indent + 1);
            }

            print_indent(indent);
            printf("else ");
            if (node->third != NULL && node->third->stmt_kind_val == STMT_BLOCK) {
                print_block(node->third->left, indent);
            } else {
                printf("\n");
                print_statement(node->third, indent + 1);
            }
            break;

        case STMT_FOR:
            print_indent(indent);
            printf("for (");
            if (node->left != NULL) print_expr(node->left);
            printf("; ");
            if (node->right != NULL) print_expr(node->right);
            printf("; ");
            if (node->third != NULL) print_expr(node->third);
            printf(") ");

            if (node->third != NULL && node->third->next != NULL &&
                node->third->next->stmt_kind_val == STMT_BLOCK) {
                print_block(node->third->next->left, indent);
            } else if (node->third != NULL && node->third->next != NULL) {
                printf("\n");
                print_statement(node->third->next, indent + 1);
            } else {
                printf("{ }\n");
            }
            break;

        default:
            print_indent(indent);
            printf("/* unknown statement */\n");
            break;
    }
}

void print_pretty(ASTNode *node, int indent)
{
    ASTNode *temp = node;

    while (temp != NULL) {
        switch (temp->type) {
            case NODE_DECLARATION:
                print_declaration(temp, indent);
                break;

            case NODE_FUNCTION:
                print_function(temp, indent);
                break;

            case NODE_STATEMENT:
                print_statement(temp, indent);
                break;

            default:
                print_indent(indent);
                printf("/* unsupported node */\n");
                break;
        }

        temp = temp->next;
    }
}