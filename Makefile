CC     = gcc
FLEX   = flex
BISON  = bison
CFLAGS = -Wall -Wextra -g

all: parser

parser: src/parser.tab.c src/lex.yy.c src/main.c src/ast.c \
        src/typecheck.c src/symbol.c src/resolve.c src/codegen.c
	$(CC) $(CFLAGS) $^ -o $@

src/parser.tab.c src/parser.tab.h: src/parser.y
	$(BISON) -d -o src/parser.tab.c src/parser.y

src/lex.yy.c: src/scanner.flex src/parser.tab.h
	$(FLEX) -o src/lex.yy.c src/scanner.flex

test: parser
	bash run_all_tests.sh

clean:
	rm -f src/parser.tab.c src/parser.tab.h src/lex.yy.c parser output.s

.PHONY: all test clean