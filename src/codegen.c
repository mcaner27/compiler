/*
 * codegen.c — x86-64 AT&T assembly code generator for B-Minor
 * Calling convention: System V AMD64 ABI
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symbol.h"
#include "ast.h"

/* ── output file ─────────────────────────────────────────── */
static FILE *out = NULL;
static int label_count = 0;
static int new_label(void) { return label_count++; }

/* ── string literal table ────────────────────────────────── */
#define MAX_STR 1024
static char *str_tab[MAX_STR];
static int   str_cnt = 0;

static int add_str(const char *s)
{
    for (int i = 0; i < str_cnt; i++)
        if (strcmp(str_tab[i], s) == 0) return i;
    if (str_cnt < MAX_STR) { str_tab[str_cnt] = strdup(s); return str_cnt++; }
    return 0;
}

/* ── argument registers (System V AMD64) ─────────────────── */
static const char *argregs[] = {"%rdi","%rsi","%rdx","%rcx","%r8","%r9"};

/* ── forward declarations ────────────────────────────────── */
static void gen_expr(ASTNode *node, Scope *scope);
static void gen_stmt(ASTNode *node, Scope *scope);

/* ── simple type inference for print ────────────────────── */
static type_kind expr_type_kind(ASTNode *n, Scope *sc)
{
    if (!n) return TYPE_NONE;
    switch (n->expr_kind_val) {
        case EXPR_INTEGER_LITERAL: return TYPE_INTEGER;
        case EXPR_BOOLEAN_LITERAL: return TYPE_BOOLEAN;
        case EXPR_STRING_LITERAL:  return TYPE_STRING;
        case EXPR_CHAR_LITERAL:    return TYPE_CHAR;
        case EXPR_ADD: case EXPR_SUB: case EXPR_MUL: case EXPR_DIV:
        case EXPR_MOD: case EXPR_EXP: case EXPR_NEG:
        case EXPR_POST_INC: case EXPR_POST_DEC:
            return TYPE_INTEGER;
        case EXPR_LT: case EXPR_LE: case EXPR_GT: case EXPR_GE:
        case EXPR_EQ: case EXPR_NE: case EXPR_AND: case EXPR_OR:
        case EXPR_NOT:
            return TYPE_BOOLEAN;
        case EXPR_IDENTIFIER:
            if (sc && n->name) {
                ASTNode *d = scope_lookup(sc, n->name);
                if (d && d->left) return d->left->type_kind_val;
            }
            return TYPE_NONE;
        case EXPR_ASSIGN:
            return expr_type_kind(n->left, sc);
        case EXPR_CALL:
            if (sc && n->name) {
                ASTNode *d = scope_lookup(sc, n->name);
                if (d && d->type == NODE_FUNCTION && d->left)
                    return d->left->type_kind_val;
            }
            return TYPE_NONE;
        default: return TYPE_NONE;
    }
}

/* ── local-variable slot counting ───────────────────────── */
static int count_locals(ASTNode *blk)
{
    int c = 0;
    for (ASTNode *t = blk; t; t = t->next) {
        if (t->type == NODE_DECLARATION) {
            c++;
        } else if (t->type == NODE_STATEMENT) {
            /* recurse into any nested block/body */
            if (t->stmt_kind_val == STMT_BLOCK && t->left)
                c += count_locals(t->left);
            if (t->right && t->right->type == NODE_STATEMENT)
                c += count_locals(t->right->left ? t->right->left : NULL);
            if (t->third && t->third->type == NODE_STATEMENT)
                c += count_locals(t->third->left ? t->third->left : NULL);
        }
    }
    return c;
}

static void assign_slots(ASTNode *blk, int *ctr)
{
    for (ASTNode *t = blk; t; t = t->next) {
        if (t->type == NODE_DECLARATION) {
            t->local_slot = (*ctr)++;
        } else if (t->type == NODE_STATEMENT) {
            if (t->stmt_kind_val == STMT_BLOCK && t->left)
                assign_slots(t->left, ctr);
            /* recurse into right/third bodies */
            if (t->right && t->right->type == NODE_STATEMENT && t->right->left)
                assign_slots(t->right->left, ctr);
            if (t->third && t->third->type == NODE_STATEMENT && t->third->left)
                assign_slots(t->third->left, ctr);
        }
    }
}

/* ── get stack offset for a local decl node ─────────────── */
static int local_offset(ASTNode *decl)
{
    return -(decl->local_slot + 1) * 8;
}

/* ── emit string/format literals to .rodata ─────────────── */
static void emit_rodata(void)
{
    /* Suppress "executable stack" linker warning */
    fprintf(out, ".section .note.GNU-stack,\"\",@progbits\n\n");
    fprintf(out, ".section .rodata\n");
    /* format strings always needed */
    fprintf(out, "__fmt_int:\n    .string \"%%lld\"\n");
    fprintf(out, "__fmt_char:\n    .string \"%%c\"\n");
    fprintf(out, "__str_true:\n    .string \"true\"\n");
    fprintf(out, "__str_false:\n    .string \"false\"\n");
    for (int i = 0; i < str_cnt; i++)
        fprintf(out, ".Lstr%d:\n    .string %s\n", i, str_tab[i]);
    fprintf(out, "\n");
}

/* ── emit global var .data section ──────────────────────── */
static void emit_data(ASTNode *root)
{
    int has = 0;
    for (ASTNode *t = root; t; t = t->next)
        if (t->type == NODE_DECLARATION && t->name) { has = 1; break; }
    if (!has) return;

    fprintf(out, ".data\n");
    for (ASTNode *t = root; t; t = t->next) {
        if (t->type != NODE_DECLARATION || !t->name) continue;
        t->is_global = 1;
        fprintf(out, ".globl %s\n%s:\n", t->name, t->name);
        if (t->right && t->right->expr_kind_val == EXPR_INTEGER_LITERAL)
            fprintf(out, "    .quad %d\n", t->right->int_value);
        else if (t->right && t->right->expr_kind_val == EXPR_BOOLEAN_LITERAL)
            fprintf(out, "    .quad %d\n", t->right->int_value);
        else
            fprintf(out, "    .quad 0\n");
    }
    fprintf(out, "\n");
}

/* ── emit integer-power helper __bm_pow ─────────────────── */
static void emit_pow_helper(void)
{
    fprintf(out,
        "__bm_pow:\n"
        "    push %%rbp\n    mov %%rsp, %%rbp\n"
        "    mov $1, %%rax\n"          /* result = 1 */
        "    cmp $0, %%rsi\n    jle .Lpow_done\n"
        ".Lpow_loop:\n"
        "    imul %%rdi, %%rax\n"
        "    dec %%rsi\n"
        "    jnz .Lpow_loop\n"
        ".Lpow_done:\n"
        "    leave\n    ret\n\n");
}

/* ── collect string literals from whole AST ─────────────── */
static void collect_strings(ASTNode *n)
{
    if (!n) return;
    if (n->expr_kind_val == EXPR_STRING_LITERAL && n->string_value)
        add_str(n->string_value);
    collect_strings(n->left);
    collect_strings(n->right);
    collect_strings(n->third);
    collect_strings(n->next);
}

/* ── expression codegen ──────────────────────────────────── */
static void gen_expr(ASTNode *node, Scope *scope)
{
    if (!node) return;

    switch (node->expr_kind_val) {

    case EXPR_INTEGER_LITERAL:
        fprintf(out, "    movq $%d, %%rax\n", node->int_value);
        break;

    case EXPR_BOOLEAN_LITERAL:
        fprintf(out, "    movq $%d, %%rax\n", node->int_value ? 1 : 0);
        break;

    case EXPR_CHAR_LITERAL: {
        int cv = 0;
        const char *s = node->string_value;
        if (s && s[1] == '\\') {
            switch (s[2]) {
                case 'n':  cv = '\n'; break;
                case '0':  cv = 0;    break;
                case '\\': cv = '\\'; break;
                case '\'': cv = '\''; break;
                default:   cv = s[2]; break;
            }
        } else if (s) {
            cv = (unsigned char)s[1];
        }
        fprintf(out, "    movq $%d, %%rax\n", cv);
        break;
    }

    case EXPR_STRING_LITERAL: {
        int idx = add_str(node->string_value);
        fprintf(out, "    leaq .Lstr%d(%%rip), %%rax\n", idx);
        break;
    }

    case EXPR_IDENTIFIER: {
        if (!node->name || !scope) { fprintf(out, "    movq $0, %%rax\n"); break; }
        ASTNode *d = scope_lookup(scope, node->name);
        if (!d) { fprintf(out, "    movq $0, %%rax\n    # undef %s\n", node->name); break; }
        if (d->is_global)
            fprintf(out, "    movq %s(%%rip), %%rax\n", d->name);
        else
            fprintf(out, "    movq %d(%%rbp), %%rax\n", local_offset(d));
        break;
    }

    /* arithmetic */
#define BINOP(OP) \
    gen_expr(node->left, scope); \
    fprintf(out, "    pushq %%rax\n"); \
    gen_expr(node->right, scope); \
    fprintf(out, "    movq %%rax, %%rbx\n"); \
    fprintf(out, "    popq %%rax\n"); \
    fprintf(out, "    " OP " %%rbx, %%rax\n"); break

    case EXPR_ADD: BINOP("addq");
    case EXPR_SUB: BINOP("subq");
    case EXPR_MUL: BINOP("imulq");

    case EXPR_DIV:
        gen_expr(node->left, scope);
        fprintf(out, "    pushq %%rax\n");
        gen_expr(node->right, scope);
        fprintf(out, "    movq %%rax, %%rbx\n");
        fprintf(out, "    popq %%rax\n");
        fprintf(out, "    cqo\n    idivq %%rbx\n");
        break;

    case EXPR_MOD:
        gen_expr(node->left, scope);
        fprintf(out, "    pushq %%rax\n");
        gen_expr(node->right, scope);
        fprintf(out, "    movq %%rax, %%rbx\n");
        fprintf(out, "    popq %%rax\n");
        fprintf(out, "    cqo\n    idivq %%rbx\n");
        fprintf(out, "    movq %%rdx, %%rax\n");
        break;

    case EXPR_EXP:
        gen_expr(node->left, scope);
        fprintf(out, "    pushq %%rax\n");
        gen_expr(node->right, scope);
        fprintf(out, "    movq %%rax, %%rsi\n");
        fprintf(out, "    popq %%rdi\n");
        fprintf(out, "    callq __bm_pow\n");
        break;

    case EXPR_NEG:
        gen_expr(node->left, scope);
        fprintf(out, "    negq %%rax\n");
        break;

    /* comparison */
#define CMPOP(SET) \
    gen_expr(node->left, scope); \
    fprintf(out, "    pushq %%rax\n"); \
    gen_expr(node->right, scope); \
    fprintf(out, "    movq %%rax, %%rbx\n"); \
    fprintf(out, "    popq %%rax\n"); \
    fprintf(out, "    cmpq %%rbx, %%rax\n"); \
    fprintf(out, "    " SET " %%al\n"); \
    fprintf(out, "    movzbq %%al, %%rax\n"); break

    case EXPR_LT: CMPOP("setl");
    case EXPR_LE: CMPOP("setle");
    case EXPR_GT: CMPOP("setg");
    case EXPR_GE: CMPOP("setge");
    case EXPR_EQ: CMPOP("sete");
    case EXPR_NE: CMPOP("setne");

    /* logical */
    case EXPR_AND: BINOP("andq");
    case EXPR_OR:  BINOP("orq");

    case EXPR_NOT:
        gen_expr(node->left, scope);
        fprintf(out, "    cmpq $0, %%rax\n");
        fprintf(out, "    sete %%al\n");
        fprintf(out, "    movzbq %%al, %%rax\n");
        break;

    /* assignment */
    case EXPR_ASSIGN: {
        if (!node->left || node->left->expr_kind_val != EXPR_IDENTIFIER
            || !node->left->name || !scope) break;
        ASTNode *d = scope_lookup(scope, node->left->name);
        if (!d) break;
        gen_expr(node->right, scope);
        if (d->is_global)
            fprintf(out, "    movq %%rax, %s(%%rip)\n", d->name);
        else
            fprintf(out, "    movq %%rax, %d(%%rbp)\n", local_offset(d));
        break;
    }

    /* post-increment / post-decrement with writeback */
    case EXPR_POST_INC:
    case EXPR_POST_DEC: {
        int is_inc = (node->expr_kind_val == EXPR_POST_INC);
        if (node->left && node->left->expr_kind_val == EXPR_IDENTIFIER
            && node->left->name && scope) {
            ASTNode *d = scope_lookup(scope, node->left->name);
            if (d) {
                if (d->is_global) {
                    fprintf(out, "    movq %s(%%rip), %%rax\n", d->name);
                    fprintf(out, "    movq %%rax, %%rbx\n");
                    fprintf(out, "    %s %%rbx\n", is_inc ? "incq" : "decq");
                    fprintf(out, "    movq %%rbx, %s(%%rip)\n", d->name);
                } else {
                    fprintf(out, "    movq %d(%%rbp), %%rax\n", local_offset(d));
                    fprintf(out, "    movq %%rax, %%rbx\n");
                    fprintf(out, "    %s %%rbx\n", is_inc ? "incq" : "decq");
                    fprintf(out, "    movq %%rbx, %d(%%rbp)\n", local_offset(d));
                }
                break;
            }
        }
        gen_expr(node->left, scope);
        fprintf(out, "    %s %%rax\n", is_inc ? "incq" : "decq");
        break;
    }

    /* array index */
    case EXPR_INDEX:
        gen_expr(node->left, scope);
        fprintf(out, "    # array index: result in rax (address), not fully implemented\n");
        break;

    /* function call — System V AMD64 ABI */
    case EXPR_CALL: {
        if (!node->name) break;
        /* count args */
        int nargs = 0;
        for (ASTNode *a = node->left; a; a = a->next) nargs++;
        /* evaluate each arg and push onto stack */
        for (ASTNode *a = node->left; a; a = a->next) {
            gen_expr(a, scope);
            fprintf(out, "    pushq %%rax\n");
        }
        /* pop into registers in reverse order */
        int reg_args = nargs < 6 ? nargs : 6;
        for (int i = reg_args - 1; i >= 0; i--)
            fprintf(out, "    popq %s\n", argregs[i]);
        /* extra args beyond 6 stay on stack (already in right order) */
        fprintf(out, "    movq $0, %%rax\n");   /* rax=0: no SSE args */
        fprintf(out, "    callq %s\n", node->name);
        /* clean up any stack args */
        if (nargs > 6)
            fprintf(out, "    addq $%d, %%rsp\n", (nargs - 6) * 8);
        break;
    }

    default:
        fprintf(out, "    movq $0, %%rax\n    # unsupported expr\n");
        break;
    }
}

/* ── statement codegen ───────────────────────────────────── */
static void gen_stmt(ASTNode *node, Scope *scope)
{
    if (!node) return;

    switch (node->stmt_kind_val) {

    case STMT_EXPR:
        gen_expr(node->left, scope);
        break;

    case STMT_RETURN:
        if (node->left) gen_expr(node->left, scope);
        else            fprintf(out, "    movq $0, %%rax\n");
        fprintf(out, "    leave\n    ret\n");
        break;

    case STMT_BLOCK: {
        /* First pass: bind all declarations in this block to scope */
        for (ASTNode *t = node->left; t; t = t->next) {
            if (t->type == NODE_DECLARATION && t->name && t->local_slot >= 0)
                scope_bind(scope, t->name, t);
        }
        /* Second pass: emit code */
        for (ASTNode *t = node->left; t; t = t->next) {
            if (t->type == NODE_DECLARATION) {
                if (t->right) {
                    gen_expr(t->right, scope);
                    fprintf(out, "    movq %%rax, %d(%%rbp)\n", local_offset(t));
                }
            } else if (t->type == NODE_STATEMENT) {
                gen_stmt(t, scope);
            }
        }
        break;
    }

    case STMT_IF: {
        int lf = new_label();
        gen_expr(node->left, scope);
        fprintf(out, "    cmpq $0, %%rax\n    je .L%d\n", lf);
        gen_stmt(node->right, scope);
        fprintf(out, ".L%d:\n", lf);
        break;
    }

    case STMT_IF_ELSE: {
        int lelse = new_label(), lend = new_label();
        gen_expr(node->left, scope);
        fprintf(out, "    cmpq $0, %%rax\n    je .L%d\n", lelse);
        gen_stmt(node->right, scope);
        fprintf(out, "    jmp .L%d\n.L%d:\n", lend, lelse);
        gen_stmt(node->third, scope);
        fprintf(out, ".L%d:\n", lend);
        break;
    }

    case STMT_FOR: {
        int lstart = new_label(), lend = new_label();
        if (node->left)  gen_expr(node->left, scope);
        fprintf(out, ".L%d:\n", lstart);
        if (node->right) {
            gen_expr(node->right, scope);
            fprintf(out, "    cmpq $0, %%rax\n    je .L%d\n", lend);
        }
        if (node->third && node->third->next)
            gen_stmt(node->third->next, scope);
        if (node->third)  gen_expr(node->third, scope);
        fprintf(out, "    jmp .L%d\n.L%d:\n", lstart, lend);
        break;
    }

    case STMT_WHILE: {
        int lstart = new_label(), lend = new_label();
        fprintf(out, ".L%d:\n", lstart);
        gen_expr(node->left, scope);
        fprintf(out, "    cmpq $0, %%rax\n    je .L%d\n", lend);
        gen_stmt(node->right, scope);
        fprintf(out, "    jmp .L%d\n.L%d:\n", lstart, lend);
        break;
    }

    case STMT_PRINT: {
        for (ASTNode *t = node->left; t; t = t->next) {
            type_kind tk = expr_type_kind(t, scope);
            gen_expr(t, scope);
            switch (tk) {
            case TYPE_INTEGER:
                fprintf(out, "    movq %%rax, %%rsi\n");
                fprintf(out, "    leaq __fmt_int(%%rip), %%rdi\n");
                fprintf(out, "    movq $0, %%rax\n");
                fprintf(out, "    callq printf\n");
                break;
            case TYPE_BOOLEAN: {
                int lt = new_label(), ld = new_label();
                fprintf(out, "    cmpq $0, %%rax\n    jne .L%d\n", lt);
                fprintf(out, "    leaq __str_false(%%rip), %%rdi\n");
                fprintf(out, "    jmp .L%d\n.L%d:\n", ld, lt);
                fprintf(out, "    leaq __str_true(%%rip), %%rdi\n");
                fprintf(out, ".L%d:\n", ld);
                fprintf(out, "    movq $0, %%rax\n    callq printf\n");
                break;
            }
            case TYPE_STRING:
                fprintf(out, "    movq %%rax, %%rdi\n");
                fprintf(out, "    movq $0, %%rax\n");
                fprintf(out, "    callq printf\n");
                break;
            case TYPE_CHAR:
                fprintf(out, "    movq %%rax, %%rdi\n");
                fprintf(out, "    callq putchar\n");
                break;
            default:
                fprintf(out, "    movq %%rax, %%rsi\n");
                fprintf(out, "    leaq __fmt_int(%%rip), %%rdi\n");
                fprintf(out, "    movq $0, %%rax\n");
                fprintf(out, "    callq printf\n");
                break;
            }
        }
        break;
    }

    default:
        fprintf(out, "    # unsupported statement\n");
        break;
    }
}

/* ── function codegen ────────────────────────────────────── */
static void gen_function(ASTNode *node, Scope *global)
{
    if (!node || !node->right) return;  /* skip prototypes */

    const char *fname = node->name ? node->name : "main";

    fprintf(out, ".globl %s\n%s:\n", fname, fname);
    fprintf(out, "    pushq %%rbp\n    movq %%rsp, %%rbp\n");

    /* Create function scope, bind params */
    Scope *fn_scope = scope_create(global);

    /* Bind parameters — they are passed in registers; store onto shadow area */
    ASTNode *params = (node->left && node->left->next) ? node->left->next : NULL;
    {
        /* count params for shadow allocation */
        int nparams = 0;
        for (ASTNode *p = params; p; p = p->next) nparams++;

        /* Count locals (excluding params) */
        int nlocals = 0;
        if (node->right->stmt_kind_val == STMT_BLOCK)
            nlocals = count_locals(node->right->left);

        int total = nparams + nlocals;
        if (total > 0)
            fprintf(out, "    subq $%d, %%rsp\n", total * 8);

        /* Assign slots to params */
        int slot = 0;
        for (ASTNode *p = params; p; p = p->next, slot++) {
            p->local_slot = slot;
            int reg_idx = slot < 6 ? slot : -1;
            if (reg_idx >= 0)
                fprintf(out, "    movq %s, %d(%%rbp)\n",
                        argregs[reg_idx], local_offset(p));
            if (p->name) scope_bind(fn_scope, p->name, p);
        }

        /* Assign slots to locals */
        if (node->right->stmt_kind_val == STMT_BLOCK)
            assign_slots(node->right->left, &slot);
    }

    gen_stmt(node->right, fn_scope);

    /* Default return if function falls off end */
    fprintf(out, "    movq $0, %%rax\n    leave\n    ret\n\n");

    scope_destroy(fn_scope);
}

/* ── top-level entry point ───────────────────────────────── */
void codegen_program(ASTNode *root, const char *outfile)
{
    out = fopen(outfile, "w");
    if (!out) { perror(outfile); return; }

    label_count = 0;
    str_cnt = 0;

    /* Collect all string literals first */
    collect_strings(root);

    /* .rodata — strings & format strings */
    emit_rodata();

    /* .data — global variables */
    emit_data(root);

    /* .text */
    fprintf(out, ".text\n\n");
    emit_pow_helper();

    /* Build global scope */
    Scope *global = scope_create(NULL);
    for (ASTNode *t = root; t; t = t->next) {
        if (t->name) scope_bind(global, t->name, t);
    }

    /* Generate functions */
    for (ASTNode *t = root; t; t = t->next) {
        if (t->type == NODE_FUNCTION)
            gen_function(t, global);
    }

    scope_destroy(global);

    /* free string table */
    for (int i = 0; i < str_cnt; i++) free(str_tab[i]);
    str_cnt = 0;

    fclose(out);
    out = NULL;
}