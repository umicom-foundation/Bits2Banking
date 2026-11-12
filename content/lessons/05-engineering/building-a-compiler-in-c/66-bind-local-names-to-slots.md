<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/66-bind-local-names-to-slots.md

PURPOSE:
Bind local names to integer slots

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Bind local names to integer slots

## Goal and prerequisites

Extend the expression compiler into a small statement language. You should already understand token offsets, expression precedence and the difference between compilation and execution. Use the implemented local profile in the Umicom C source tree; this lesson does not claim full C23 support.

## Follow a declaration

~~~c
int main(void) {
    int base = 6;
    int result = base * 7;
    base = 9;
    return result;
}
~~~

Predict the answer before running it. result stores 42 when its initializer executes; assigning 9 to base does not recompute result. These are integer values, not spreadsheet formulas.

1. Open src/lexer.c. A name begins with an ASCII letter or underscore. Later characters may also be digits. The token carries an offset and length, allowing comparison without allocating a copied string.
2. Open src/compiler.c and find the active find_local function. It compares both length and bytes against earlier declarations. base and baseline must remain different names; Base differs from base.
3. Follow local_statement. It checks whether the name already exists before compiling an initializer. A new declaration is entered only after its expression and semicolon are accepted.
4. Follow the identifier arm in unary. It resolves a name and emits LOAD_LOCAL with the numeric slot. Source locations remain diagnostic offsets; no source pointer enters bytecode.
5. Follow assignment. It resolves an existing slot, compiles the right side, then emits STORE_LOCAL. It does not add a symbol or yield an expression value.

This ordering explains why int value=value; is rejected. The new variable cannot read itself before initialization. An earlier variable remains visible in a later initializer. The single function body has one flat scope; there is no shadowing block.

## Run and inspect

Save the example as slots.uc in your Umicom C checkout after following its build guide.

~~~powershell
.\build\bin\umicom-c.exe check .\slots.uc
.\build\bin\umicom-c.exe run .\slots.uc
.\build\bin\umicom-c.exe trace .\slots.uc
~~~

Expect result 42. Trace the store into result and the later store into base. Explain why the returned copy still holds 42. The trace exposes the operand stack, not a complete variable inspector.

## Make the boundaries fail

Change return result to return missing. Expect a syntax error at the undeclared name and no executable instruction count. Try declaring base twice, omit an initializer, or use return base=9. Each violates a different part of the statement contract. Restore valid source after each experiment; do not execute partially emitted instructions.

The limits are independent: 63 bytes per identifier, 32 declared locals, 256 instructions and 64 stack values. Reassigning one variable consumes instructions without consuming another local slot. The tests generate 32 distinct declarations and a rejected 33rd; they also exhaust instruction storage with assignments to one name.

## Exercise and review

Add two similarly named variables and verify that changing one does not change the other. Write down the expected declaration-order slots before reading disassembly. Then run:

~~~powershell
ctest --test-dir build -R "umicom.c.locals.source" --output-on-failure --no-tests=error
~~~

Read tests/test_local_source.c. Its expected values, rejected forms and boundary cases are the specification checks. Passing compilation alone does not establish arithmetic success, portable wire compatibility or the Kernel consumer's execution.


[Course contents](index.md) · [Previous lesson](65-test-buffered-report-failures.md) · [Next lesson](67-prove-local-initialization-before-execution.md)
