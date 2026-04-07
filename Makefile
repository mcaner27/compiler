# B-Minor Compiler - Makefile
# Currently compiling only the Scanner phase.

CC = gcc
FLEX = flex
CFLAGS = -Wall -g

# Main target executed when 'make' is called
all: scanner

# Rule to compile the scanner tool
scanner: src/scanner.flex
	$(FLEX) -o src/scanner.c src/scanner.flex
	$(CC) $(CFLAGS) src/scanner.c -o scanner

# Rule to clean compiled files when 'make clean' is called
clean:
	rm -f src/scanner.c scanner