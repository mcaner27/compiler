#!/bin/bash
# =============================================================
# CEN417 B-Minor Compiler — Automated Test Suite
# Kullanim: bash run_tests.sh
# =============================================================

COMPILER="./parser"
PASS=0
FAIL=0
RED='\033[0;31m'
GRN='\033[0;32m'
YLW='\033[1;33m'
NC='\033[0m'

pass() { echo -e "${GRN}[PASS]${NC} $1"; PASS=$((PASS+1)); }
fail() { echo -e "${RED}[FAIL]${NC} $1"; FAIL=$((FAIL+1)); }
header() { echo -e "\n${YLW}=== $1 ===${NC}"; }

# --- Derlenecek binary var mi? ---
if [ ! -f "$COMPILER" ]; then
    echo "Compiler bulunamadi. Once build edin: bash build.sh"
    exit 1
fi

# ============================================================
# B.1 SCANNER TESTLERİ — geçerli ve hatalı token'lar
# ============================================================
header "B.1 SCANNER TESTS"

scanner_test() {
    local name="$1" src="$2" expect="$3"  # expect: ok / scan_error
    result=$($COMPILER "$src" 2>&1)
    has_scan=$(echo "$result" | grep -c "SCAN ERROR")
    if [ "$expect" = "ok" ] && [ "$has_scan" -eq 0 ]; then
        pass "$name"
    elif [ "$expect" = "scan_error" ] && [ "$has_scan" -gt 0 ]; then
        pass "$name (scan errors detected)"
    else
        fail "$name (expected=$expect scan_errors=$has_scan)"
    fi
}

scanner_test "valid_tokens"         tests/test_valid.bminor        ok
scanner_test "scanner_corner_cases" tests/test_scanner.bminor      scan_error

# ============================================================
# B.2 PARSER TESTLERİ — sözdizimi doğruluğu
# ============================================================
header "B.2 PARSER TESTS"

parse_test() {
    local name="$1" src="$2" expect="$3"  # expect: ok / error
    result=$($COMPILER "$src" 2>&1)
    has_parse=$(echo "$result" | grep -c "PARSE ERROR\|Parsing failed")
    if [ "$expect" = "ok" ] && [ "$has_parse" -eq 0 ]; then
        pass "$name"
    elif [ "$expect" = "error" ] && [ "$has_parse" -gt 0 ]; then
        pass "$name (parse error detected)"
    else
        fail "$name"
    fi
}

parse_test "global_declarations"   tests/test_valid.bminor       ok
parse_test "function_definition"   tests/test_codegen1.bminor    ok
parse_test "arithmetic_expr"       tests/test_arithmetic.bminor  ok
parse_test "for_loop"              tests/test_for_loop.bminor    ok

# while loop
cat > /tmp/p_while.bminor << 'E'
main: function integer () = {
    i: integer = 0;
    while (i < 5) { i = i + 1; }
    return i;
}
E
parse_test "while_loop"  /tmp/p_while.bminor  ok

# function prototype (B-Minor A6.3)
parse_test "func_prototype"  tests/test_prototype.bminor  ok

# if-else (dangling-else)
parse_test "if_else"         tests/test_nested_if.bminor  ok

# ============================================================
# B.3 PRETTY PRINTER TESTLERİ
# ============================================================
header "B.3 PRETTY PRINTER TESTS"

pretty_test() {
    local name="$1" src="$2"
    result=$($COMPILER "$src" 2>&1)
    if echo "$result" | grep -q "PRETTY PRINT OUTPUT"; then
        pass "$name"
    else
        fail "$name"
    fi
}

pretty_test "pretty_basic"    tests/test_valid.bminor
pretty_test "pretty_function" tests/test_function_call.bminor
pretty_test "pretty_for"      tests/test_for_loop.bminor

# ============================================================
# B.4 TYPE CHECKER TESTLERİ
# ============================================================
header "B.4 TYPE CHECKER TESTS"

type_test() {
    local name="$1" src="$2" expect="$3"  # ok / type_error
    result=$($COMPILER "$src" 2>&1)
    has_err=$(echo "$result" | grep -c "TYPE ERROR")
    if [ "$expect" = "ok" ] && [ "$has_err" -eq 0 ]; then
        pass "$name"
    elif [ "$expect" = "type_error" ] && [ "$has_err" -gt 0 ]; then
        pass "$name (type errors detected: $has_err)"
    else
        fail "$name (expected=$expect type_errors=$has_err)"
        echo "$result" | grep "TYPE ERROR" | head -3 | sed 's/^/    /'
    fi
}

type_test "integer_arithmetic"    tests/test_arithmetic.bminor  ok
type_test "boolean_expressions"   tests/test_boolean_expr.bminor ok
type_test "comparison_ops"        tests/test_comparison.bminor   ok
type_test "logical_ops"           tests/test_logical.bminor      ok
type_test "type_errors_detected"  tests/test_type_error.bminor   type_error
type_test "resolve_errors"        tests/test_resolve_error.bminor ok  # resolve hatası, type değil

# arguman tip kontrolü
cat > /tmp/t_argcheck.bminor << 'E'
square: function integer (x: integer) = { return x ^ 2; }
main: function integer () = { return square(true); }
E
type_test "arg_type_mismatch"  /tmp/t_argcheck.bminor  type_error

# wrong arg count
cat > /tmp/t_argcount.bminor << 'E'
add: function integer (a: integer, b: integer) = { return a + b; }
main: function integer () = { return add(1); }
E
type_test "arg_count_mismatch"  /tmp/t_argcount.bminor  type_error

# ============================================================
# B.6 CODE GENERATOR TESTLERİ — üretilen assembly çalışıyor mu?
# ============================================================
header "B.6 CODE GENERATOR TESTS"

codegen_test() {
    local name="$1" src="$2" expected_exit="$3"
    $COMPILER "$src" > /dev/null 2>&1
    gcc -no-pie -o /tmp/bm_cg_test output.s 2>/dev/null
    /tmp/bm_cg_test
    got=$?
    if [ "$got" -eq "$expected_exit" ]; then
        pass "$name (exit=$got)"
    else
        fail "$name (expected exit=$expected_exit got=$got)"
    fi
}

print_test() {
    local name="$1" src="$2" expected_out="$3"
    $COMPILER "$src" > /dev/null 2>&1
    gcc -no-pie -o /tmp/bm_print_test output.s 2>/dev/null
    got=$(/tmp/bm_print_test 2>/dev/null)
    if [ "$got" = "$expected_out" ]; then
        pass "$name (output='$got')"
    else
        fail "$name (expected='$expected_out' got='$got')"
    fi
}

codegen_test "return_literal"    tests/test_codegen1.bminor   5
codegen_test "return_add_2_3"    tests/test_codegen2.bminor   5

cat > /tmp/cg_arith.bminor << 'E'
main: function integer () = {
    x: integer = 10; y: integer = 3;
    z: integer = x + y * 2 - 4 / 2;
    return z;
}
E
codegen_test "arithmetic_result"  /tmp/cg_arith.bminor  14

cat > /tmp/cg_mod.bminor << 'E'
main: function integer () = { return 17 % 5; }
E
codegen_test "modulo"  /tmp/cg_mod.bminor  2

cat > /tmp/cg_exp.bminor << 'E'
main: function integer () = { return 2 ^ 7; }
E
codegen_test "exponentiation_2^7"  /tmp/cg_exp.bminor  128
# 1024 mod 256 = 0, so let's use 3^3=27
cat > /tmp/cg_exp2.bminor << 'E'
main: function integer () = { return 3 ^ 3; }
E
codegen_test "exponentiation_3^3"  /tmp/cg_exp2.bminor  27

cat > /tmp/cg_if.bminor << 'E'
main: function integer () = {
    x: integer = 7;
    if (x > 5) { return 1; }
    return 0;
}
E
codegen_test "if_true_branch"   /tmp/cg_if.bminor  1

cat > /tmp/cg_ifelse.bminor << 'E'
main: function integer () = {
    x: integer = 3;
    if (x > 5) { return 99; } else { return 1; }
    return 0;
}
E
codegen_test "if_else_false_branch"  /tmp/cg_ifelse.bminor  1

cat > /tmp/cg_for.bminor << 'E'
main: function integer () = {
    i: integer; sum: integer = 0;
    for (i = 0; i < 5; i++) { sum = sum + i; }
    return sum;
}
E
codegen_test "for_loop_sum"  /tmp/cg_for.bminor  10

cat > /tmp/cg_while.bminor << 'E'
main: function integer () = {
    i: integer = 0;
    while (i < 5) { i = i + 1; }
    return i;
}
E
codegen_test "while_loop"  /tmp/cg_while.bminor  5

cat > /tmp/cg_call.bminor << 'E'
square: function integer (x: integer) = { return x ^ 2; }
main: function integer () = { return square(5); }
E
codegen_test "function_call_square_5"  /tmp/cg_call.bminor  25

cat > /tmp/cg_print_int.bminor << 'E'
main: function integer () = { print 42; return 0; }
E
print_test "print_integer"  /tmp/cg_print_int.bminor  "42"

cat > /tmp/cg_print_str.bminor << 'E'
main: function integer () = { print "merhaba"; return 0; }
E
print_test "print_string"  /tmp/cg_print_str.bminor  "merhaba"

cat > /tmp/cg_global.bminor << 'E'
counter: integer = 10;
main: function integer () = { return counter + 5; }
E
codegen_test "global_variable"  /tmp/cg_global.bminor  15

# ============================================================
# ÖZET
# ============================================================
echo ""
echo "============================================"
echo -e "  TOPLAM:  ${GRN}PASS=$PASS${NC}  ${RED}FAIL=$FAIL${NC}"
echo "============================================"
if [ "$FAIL" -eq 0 ]; then
    echo -e "${GRN}Tum testler gecti!${NC}"
    exit 0
else
    exit 1
fi
