#!/bin/bash
cd /mnt/d/compiler
PASS=0; FAIL=0

check_exit() {
    local name="$1"
    local expected="$2"
    local got="$3"
    if [ "$got" = "$expected" ]; then
        echo "PASS [$name] exit=$got"
        PASS=$((PASS+1))
    else
        echo "FAIL [$name] expected=$expected got=$got"
        FAIL=$((FAIL+1))
    fi
}

run_test() {
    local name="$1"
    local src="$2"
    local expected_exit="$3"
    ./parser "$src" > /dev/null 2>&1
    gcc -no-pie -o /tmp/bm_test output.s 2>/dev/null
    /tmp/bm_test
    check_exit "$name" "$expected_exit" "$?"
}

# --- Compile-only tests ---
typecheck_test() {
    local name="$1"
    local src="$2"
    local expect_ok="$3"   # "ok" or "err"
    result=$(./parser "$src" 2>&1)
    has_err=$(echo "$result" | grep -c "TYPE ERROR\|RESOLVE ERROR\|PARSE ERROR")
    if [ "$expect_ok" = "ok" ] && [ "$has_err" -eq 0 ]; then
        echo "PASS [$name]"
        PASS=$((PASS+1))
    elif [ "$expect_ok" = "err" ] && [ "$has_err" -gt 0 ]; then
        echo "PASS [$name] (errors detected: $has_err)"
        PASS=$((PASS+1))
    else
        echo "FAIL [$name] expect=$expect_ok has_err=$has_err"
        echo "$result" | grep -E "ERROR|failed" | head -3
        FAIL=$((FAIL+1))
    fi
}

echo "=== RUNTIME TESTS ==="

run_test "return_literal"    tests/test_codegen1.bminor   5
run_test "return_add"        tests/test_codegen2.bminor   5

cat > /tmp/t_arith.bminor << 'E'
main: function integer () = {
    x: integer = 10; y: integer = 3;
    z: integer = x + y * 2 - 4 / 2;
    return z;
}
E
run_test "arithmetic"  /tmp/t_arith.bminor  14

cat > /tmp/t_while.bminor << 'E'
main: function integer () = {
    i: integer = 0;
    while (i < 5) { i = i + 1; }
    return i;
}
E
run_test "while_loop"  /tmp/t_while.bminor  5

cat > /tmp/t_for.bminor << 'E'
main: function integer () = {
    i: integer; sum: integer = 0;
    for (i = 0; i < 5; i++) { sum = sum + i; }
    return sum;
}
E
run_test "for_loop"  /tmp/t_for.bminor  10

cat > /tmp/t_if.bminor << 'E'
main: function integer () = {
    x: integer = 7;
    if (x > 5) { return 1; }
    return 0;
}
E
run_test "if_true"   /tmp/t_if.bminor   1

cat > /tmp/t_ifelse.bminor << 'E'
main: function integer () = {
    x: integer = 3;
    if (x > 5) { return 99; } else { return 1; }
    return 0;
}
E
run_test "if_else"   /tmp/t_ifelse.bminor   1

cat > /tmp/t_call.bminor << 'E'
square: function integer (x: integer) = { return x ^ 2; }
main: function integer () = { return square(5); }
E
run_test "func_call_exp"  /tmp/t_call.bminor  25

cat > /tmp/t_mod.bminor << 'E'
main: function integer () = { return 17 % 5; }
E
run_test "modulo"  /tmp/t_mod.bminor  2

cat > /tmp/t_print.bminor << 'E'
main: function integer () = {
    x: integer = 42;
    print x;
    return 0;
}
E
./parser /tmp/t_print.bminor > /dev/null 2>&1
gcc -no-pie -o /tmp/t_print output.s 2>/dev/null
OUT=$(/tmp/t_print)
if [ "$OUT" = "42" ]; then echo "PASS [print_integer]"; PASS=$((PASS+1))
else echo "FAIL [print_integer] got='$OUT'"; FAIL=$((FAIL+1)); fi

echo ""
echo "=== SEMANTIC TESTS ==="
typecheck_test "valid_prog"         tests/test_valid.bminor        ok
typecheck_test "type_errors"        tests/test_type_error.bminor   err
typecheck_test "resolve_errors"     tests/test_resolve_error.bminor err
typecheck_test "boolean_expr"       tests/test_boolean_expr.bminor ok
typecheck_test "prototype"          tests/test_prototype.bminor    ok

cat > /tmp/t_argcheck.bminor << 'E'
square: function integer (x: integer) = { return x ^ 2; }
main: function integer () = { return square(true); }
E
typecheck_test "arg_type_check"  /tmp/t_argcheck.bminor  err

cat > /tmp/t_while_sem.bminor << 'E'
main: function integer () = {
    i: integer = 0;
    while (i < 10) { i = i + 1; }
    return i;
}
E
typecheck_test "while_typecheck"  /tmp/t_while_sem.bminor  ok

echo ""
echo "=== SUMMARY: PASS=$PASS FAIL=$FAIL ==="
