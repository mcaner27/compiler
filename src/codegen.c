#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

static FILE *out = NULL;
static int label_count = 0;

static int new_label(void)
{
    return label_count++;
}

static void gen_expr(ASTNode *node);
static void gen_stmt(ASTNode *node);
static void gen_function(ASTNode *node);

static void gen_expr(ASTNode *node)
{
    if (!node) return;

    switch (node->expr_kind_val) {
        case EXPR_INTEGER_LITERAL:
            fprintf(out, "    mov $%d, %%rax\n", node->int_value);
            break;

        case EXPR_BOOLEAN_LITERAL:
            fprintf(out, "    mov $%d, %%rax\n", node->int_value);
            break;

        case EXPR_ADD:
            gen_expr(node->left);
            fprintf(out, "    push %%rax\n");
            gen_expr(node->right);
            fprintf(out, "    mov %%rax, %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            fprintf(out, "    add %%rbx, %%rax\n");
            break;

        case EXPR_SUB:
            gen_expr(node->left);
            fprintf(out, "    push %%rax\n");
            gen_expr(node->right);
            fprintf(out, "    mov %%rax, %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            fprintf(out, "    sub %%rbx, %%rax\n");
            break;

        case EXPR_MUL:
            gen_expr(node->left);
            fprintf(out, "    push %%rax\n");
            gen_expr(node->right);
            fprintf(out, "    mov %%rax, %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            fprintf(out, "    imul %%rbx, %%rax\n");
            break;

        case EXPR_DIV:
            gen_expr(node->left);
            fprintf(out, "    push %%rax\n");
            gen_expr(node->right);
            fprintf(out, "    mov %%rax, %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            fprintf(out, "    cqo\n");
            fprintf(out, "    idiv %%rbx\n");
            break;

        case EXPR_LT:
            gen_expr(node->left);
            fprintf(out, "    push %%rax\n");
            gen_expr(node->right);
            fprintf(out, "    mov %%rax, %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            fprintf(out, "    cmp %%rbx, %%rax\n");
            fprintf(out, "    setl %%al\n");
            fprintf(out, "    movzb %%al, %%rax\n");
            break;

        case EXPR_LE:
            gen_expr(node->left);
            fprintf(out, "    push %%rax\n");
            gen_expr(node->right);
            fprintf(out, "    mov %%rax, %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            fprintf(out, "    cmp %%rbx, %%rax\n");
            fprintf(out, "    setle %%al\n");
            fprintf(out, "    movzb %%al, %%rax\n");
            break;

        case EXPR_GT:
            gen_expr(node->left);
            fprintf(out, "    push %%rax\n");
            gen_expr(node->right);
            fprintf(out, "    mov %%rax, %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            fprintf(out, "    cmp %%rbx, %%rax\n");
            fprintf(out, "    setg %%al\n");
            fprintf(out, "    movzb %%al, %%rax\n");
            break;

        case EXPR_GE:
            gen_expr(node->left);
            fprintf(out, "    push %%rax\n");
            gen_expr(node->right);
            fprintf(out, "    mov %%rax, %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            fprintf(out, "    cmp %%rbx, %%rax\n");
            fprintf(out, "    setge %%al\n");
            fprintf(out, "    movzb %%al, %%rax\n");
            break;

        case EXPR_EQ:
            gen_expr(node->left);
            fprintf(out, "    push %%rax\n");
            gen_expr(node->right);
            fprintf(out, "    mov %%rax, %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            fprintf(out, "    cmp %%rbx, %%rax\n");
            fprintf(out, "    sete %%al\n");
            fprintf(out, "    movzb %%al, %%rax\n");
            break;

        case EXPR_NE:
            gen_expr(node->left);
            fprintf(out, "    push %%rax\n");
            gen_expr(node->right);
            fprintf(out, "    mov %%rax, %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            fprintf(out, "    cmp %%rbx, %%rax\n");
            fprintf(out, "    setne %%al\n");
            fprintf(out, "    movzb %%al, %%rax\n");
            break;

        case EXPR_NEG:
            gen_expr(node->left);
            fprintf(out, "    neg %%rax\n");
            break;

        default:
            fprintf(out, "    # unsupported expression\n");
            fprintf(out, "    mov $0, %%rax\n");
            break;
    }
}

static void gen_stmt(ASTNode *node)
{
    if (!node) return;

    switch (node->stmt_kind_val) {
        case STMT_RETURN:
            if (node->left) {
                gen_expr(node->left);
            } else {
                fprintf(out, "    mov $0, %%rax\n");
            }
            fprintf(out, "    ret\n");
            break;

        case STMT_BLOCK:
        {
            ASTNode *temp = node->left;
            while (temp) {
                if (temp->type == NODE_STATEMENT) {
                    gen_stmt(temp);
                }
                temp = temp->next;
            }
            break;
        }

        case STMT_EXPR:
            gen_expr(node->left);
            break;

        case STMT_IF:
        {
            int false_label = new_label();

            gen_expr(node->left);
            fprintf(out, "    cmp $0, %%rax\n");
            fprintf(out, "    je .L%d\n", false_label);

            gen_stmt(node->right);

            fprintf(out, ".L%d:\n", false_label);
            break;
        }

        case STMT_IF_ELSE:
        {
            int else_label = new_label();
            int end_label = new_label();

            gen_expr(node->left);
            fprintf(out, "    cmp $0, %%rax\n");
            fprintf(out, "    je .L%d\n", else_label);

            gen_stmt(node->right);
            fprintf(out, "    jmp .L%d\n", end_label);

            fprintf(out, ".L%d:\n", else_label);
            gen_stmt(node->third);

            fprintf(out, ".L%d:\n", end_label);
            break;
        }

        default:
            fprintf(out, "    # unsupported statement\n");
            break;
    }
}

static void gen_function(ASTNode *node)
{
    if (!node) return;

    const char *fname = node->name ? node->name : "main";

    fprintf(out, ".globl %s\n", fname);
    fprintf(out, "%s:\n", fname);

    if (node->right) {
        gen_stmt(node->right);
    } else {
        fprintf(out, "    mov $0, %%rax\n");
        fprintf(out, "    ret\n");
    }

    fprintf(out, "\n");
}

void codegen_program(ASTNode *root, const char *output_filename)
{
    out = fopen(output_filename, "w");
    if (!out) {
        perror(output_filename);
        return;
    }

    label_count = 0;

    ASTNode *temp = root;
    while (temp) {
        if (temp->type == NODE_FUNCTION) {
            gen_function(temp);
        }
        temp = temp->next;
    }

    fclose(out);
    out = NULL;
}