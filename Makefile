CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Wall -g

all: parser

parser: src/parser.tab.c src/lex.yy.c src/main.c src/ast.c src/typecheck.c src/symbol.c src/resolve.c src/codegen.c
	$(CC) $(CFLAGS) src/parser.tab.c src/lex.yy.c src/main.c src/ast.c src/typecheck.c src/symbol.c src/resolve.c src/codegen.c -o parser

src/parser.tab.c src/parser.tab.h: src/parser.y
	$(BISON) -d -o src/parser.tab.c src/parser.y

src/lex.yy.c: src/scanner.flex src/parser.tab.h
	$(FLEX) -o src/lex.yy.c src/scanner.flex

clean:
	rm -f src/parser.tab.c src/parser.tab.h src/lex.yy.c parser output.s