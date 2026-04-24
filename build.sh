#!/usr/bin/env bash
# build.sh — B-Minor compiler build script (runs via WSL on Windows)
set -e
cd /mnt/d/compiler

echo "[1/3] Running bison..."
bison -d -o src/parser.tab.c src/parser.y

echo "[2/3] Running flex..."
flex -o src/lex.yy.c src/scanner.flex

echo "[3/3] Compiling..."
gcc -Wall -Wextra -g \
    src/parser.tab.c src/lex.yy.c \
    src/main.c src/ast.c src/typecheck.c \
    src/symbol.c src/resolve.c src/codegen.c \
    -o parser

echo "Build successful: ./parser"
