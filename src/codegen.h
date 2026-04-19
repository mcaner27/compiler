#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

void codegen_program(ASTNode *root, const char *output_filename);

#endif
