<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/70-compare-logical-programs-with-native-c.md

PURPOSE:
Compare logical programs with native C

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Compare logical programs with native C

## Goal

Use an independent implementation as an oracle without assuming that every C program belongs to the smaller Umicom C language. Here the host C compiler and the interpreter evaluate the same defined integer program bodies.

## Keep one input body

Read tests/test_logical_native.c. An X-macro list associates a fixture name with a function body. One expansion compiles a native function. Another stringizes that body into an int main(void) source string for Umicom C. This avoids manually maintaining two expressions that can drift apart.

~~~c
#define ONE(X) \
    X(guard, { int divisor=0; return divisor!=0 && 42/divisor>1; })
#define NATIVE(name, body) static int native_##name(void) body
ONE(NATIVE)
~~~

The actual test list contains several bodies and a table of native function pointers. The interpreter compiles each string, executes it with the full structural count as a sufficient budget, and compares the integer result with the native function.

## Restrict the common language

Use initialized int locals, signed values that fit both implementations, comparisons, parentheses and logical operators. Do not use Umicom C's decimal-leading-zero rule to predict native C octal behavior. Avoid unsupported functions, pointers, assignments inside expressions and host-specific integer assumptions.

An evaluated division by zero or signed overflow has undefined behavior in native C. It cannot serve as a portable expected-error oracle. Guarded expressions are suitable only when the guard actually prevents the invalid operation. Test Umicom C's defined arithmetic error statuses separately in its source/runtime tests.

## Run and interpret

~~~powershell
ctest --test-dir .\build\windows-ucrt64-debug -R "umicom[.]c[.]logical[.]logical_native[.]native" --output-on-failure --no-tests=error
~~~

Expect one registered test containing multiple independent program bodies. A pass supports those exact bodies with that host toolchain. It is not proof of all possible inputs, full C23 compatibility or correctness on another architecture.

## Diagnose a disagreement

1. Identify the fixture name and exact source string.
2. Confirm that both executions remain in their defined shared subset.
3. Inspect the emitted bytecode and trace to locate the first unexpected path or value.
4. Check precedence, logical normalization and branch target patching separately.
5. Add a small fixed expected-value regression once the cause is understood.

If both implementations use the same incorrect helper, agreement can hide a defect. Keep the native function independent of VM instructions and compiler routines. Likewise, encoder-decoder roundtrips do not replace literal wire fixtures.

## Exercise

Add a defined fixture with two local assignments followed by a nested logical expression. Predict its value by hand, then compare the native and interpreted results. Add a separate Umicom C-only fault test whose right operand must execute. Explain why that failing program must not be called as a native C oracle.

[Course contents](index.md) · [Previous lesson](69-validate-joins-on-all-forward-paths.md) · [Next lesson](71-select-values-with-conditional-expressions.md)
