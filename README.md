# B-Minor Compiler

A complete compiler implementation for the **B-Minor** programming language, built as part of the **CEN417 – Compiler Design** course.

The compiler translates B-Minor source code into **x86-64 assembly**, passing through lexical analysis, parsing, AST construction, name resolution, type checking, and code generation.

---

## Language Features

B-Minor supports:

- **Types:** `integer`, `boolean`, `char`, `string`, `void`
- **Variables:** global and local declarations with optional initializers
- **Functions:** definitions, prototypes, and calls with parameter passing
- **Arrays:** fixed-size array declarations and indexing
- **Control flow:** `if`, `if-else`, `for`, `while`
- **Operators:** `+ - * / % ^` (exponentiation), `== != < <= > >=`, `&& || !`, `= ++ --`
- **I/O:** `print` statement (supports integer, boolean, string, char)

### Example

```c
square: function integer (x: integer) = {
    return x ^ 2;
}

main: function integer () = {
    i: integer = 0;
    while (i < 5) {
        print square(i);
        i = i + 1;
    }
    return 0;
}
```

---

## Project Structure

```
compiler/
├── src/
│   ├── scanner.flex      # Lexical analyser (Flex)
│   ├── parser.y          # Grammar & AST builder (Bison)
│   ├── ast.h / ast.c     # Abstract Syntax Tree
│   ├── symbol.h / symbol.c   # Symbol table & scope management
│   ├── resolve.h / resolve.c # Name resolution
│   ├── typecheck.h / typecheck.c  # Type checker
│   ├── codegen.h / codegen.c      # x86-64 code generator
│   └── main.c            # Compiler driver
├── tests/                # B-Minor test programs
├── Makefile              # Build system (Linux / WSL)
├── build.sh              # Build script (Windows via WSL)
└── run_tests.sh          # Automated test suite
```

---

## Compilation Pipeline

```
B-Minor source
      │
      ▼
[Scanner – Flex]       → tokens
      │
      ▼
[Parser – Bison]       → Abstract Syntax Tree
      │
      ▼
[Name Resolution]      → Symbol table, scope checking
      │
      ▼
[Type Checker]         → Type safety validation
      │
      ▼
[Code Generator]       → x86-64 AT&T assembly (output.s)
```

---

## Building

### On Linux / WSL

```bash
make
```

Or step by step:

```bash
bash build.sh
```

### On Windows (PowerShell via WSL)

```powershell
wsl bash /mnt/d/compiler/build.sh
```

### Clean build artifacts

```bash
make clean
```

---

## Usage

```bash
./parser <source-file.bminor>
```

This prints the AST, pretty-printed source, resolve and type-check results, and writes assembly to `output.s`.

**Then link and run the generated assembly:**

```bash
gcc -no-pie -o myprogram output.s
./myprogram
```

### Example session

```
$ ./parser tests/test_valid.bminor

=== PRETTY PRINT OUTPUT ===
x: integer;
y: integer = 5;
main: function integer () = {
    print "hello\n", y;
    return 0;
}

=== RESOLVE ===
Name resolution successful. No resolve errors found.

=== TYPE CHECK ===
Type checking successful. No type errors found.

=== CODE GENERATION ===
Assembly written to output.s

$ gcc -no-pie -o prog output.s && ./prog
hello
5
```

---

## Automated Tests

Run the full test suite (34 tests covering B.1 – B.6):

```bash
bash run_tests.sh
```

On Windows:

```powershell
wsl bash /mnt/d/compiler/run_tests.sh
```

**Test coverage:**

| Phase | Tests |
|-------|-------|
| B.1 Scanner | Valid tokens, error recovery, corner cases |
| B.2 Parser | All grammar constructs, dangling-else, prototype, while |
| B.3 Pretty Printer | AST → re-parseable source output |
| B.4 Type Checker | All type rules, argument count/type checking |
| B.6 Code Generator | Runtime execution with correct results |

---

## Error Reporting

The compiler reports errors without stopping — it continues and collects all issues:

```
SCAN ERROR:    Unterminated string literal at line 5
PARSE ERROR:   syntax error
RESOLVE ERROR: Undefined identifier (foo)
TYPE ERROR:    Argument 1 type mismatch in call to 'square'.
```

---

## Technology Stack

| Tool | Purpose |
|------|---------|
| C | Implementation language |
| Flex | Lexical analyser generator |
| Bison | LALR(1) parser generator |
| GCC | Host compiler & assembler |
| x86-64 | Target architecture |
| System V AMD64 ABI | Calling convention for function calls |

---

## Authors

**Mehmet Caner Kahraman & Yağmur Keskin**  
CEN417 – Compiler Design, 2026
