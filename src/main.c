#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "typecheck.h"
#include "resolve.h"
#include "codegen.h"

extern FILE *yyin;
int yyparse(void);
extern ASTNode *root;

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./parser <input-file>\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror(argv[1]);
        return 1;
    }

    if (yyparse() == 0) {
        printf("Parsing successful.\n");
        printf("root address: %p\n", (void*)root);

        if (root != NULL) {
            printf("AST created successfully.\n");

            printf("\n=== AST OUTPUT ===\n");
            print_ast(root, 0);

            printf("\n=== PRETTY PRINT OUTPUT ===\n");
            print_pretty(root, 0);

            printf("\n=== RESOLVE ===\n");
            resolve_ast(root);
            if (resolve_error_count() == 0) {
                printf("Name resolution successful. No resolve errors found.\n");
            } else {
                printf("Name resolution finished with %d error(s).\n", resolve_error_count());
            }

            printf("\n=== TYPE CHECK ===\n");
            typecheck_ast(root);
            if (typecheck_error_count() == 0) {
                printf("Type checking successful. No type errors found.\n");
            } else {
                printf("Type checking finished with %d error(s).\n", typecheck_error_count());
            }

            if (resolve_error_count() == 0 && typecheck_error_count() == 0) {
                printf("\n=== CODE GENERATION ===\n");
                codegen_program(root, "output.s");
                printf("Assembly written to output.s\n");
            }
        }
    } else {
        printf("Parsing failed.\n");
    }

    fclose(yyin);
    return 0;
}