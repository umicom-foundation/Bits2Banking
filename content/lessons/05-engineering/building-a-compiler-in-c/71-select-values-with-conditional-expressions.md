<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/71-select-values-with-conditional-expressions.md

PURPOSE:
Select values with conditional expressions

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Select values with conditional expressions

## Goal

Add value selection to the expression language using the already qualified forward-branch runtime. You should understand the logical operators and join checks from the preceding lessons. No new VM operation is needed for this feature.

## Choose a fallback value

~~~c
int main(void) {
    int divisor = 0;
    return divisor != 0 ? 42 / divisor : 7;
}
~~~

The condition is zero, so the fallback seven is selected. Division is not attempted. Change divisor to six: the result is still seven, but this time division executes. Equal results do not prove that two programs have identical traces, source positions or instruction costs.

Unlike && and ||, the conditional operator preserves the selected integer. The expression 1 ? -9 : 42 returns minus nine. It does not convert the selected value into true or false.

## Parse the lowest expression level

The conditional level sits below logical OR. Read logical_or and expression in src/compiler.c. The parser first consumes a complete logical-OR expression as the condition. If the next token is ?, it parses the middle expression, requires :, and parses the final expression.

The final arm recursively parses another conditional. This gives right associativity: a ? b : c ? d : e means a ? b : (c ? d : e). The middle arm may also contain a nested conditional. For example, 1 ? 0 ? 7 : 8 : 9 returns eight. Parentheses are useful even when grouping is already defined.

## Lower values into compatible paths

After the condition, emit JUMP_IF_ZERO. The true arm leaves its integer on the stack and JUMP skips the false arm. The false arm also leaves one integer. The existing graph validator checks equal stack depth at their join. The compiler does not insert the zero-comparison normalization used by logical AND and OR.

Both arms must parse, so an undeclared name in an unselected arm is still an error. Both arms must be structurally valid bytecode. Only arithmetic on the chosen arm executes. Format 4, runtime feature mask 411 and wire mask 30 are unchanged; the compiler adds conditional feature bit 1024.

## Inspect and qualify

After building the intended Umicom C checkout, run these commands separately:

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe check .\examples\conditional_value.uc
.\build\windows-ucrt64-debug\bin\umicom-c.exe trace .\examples\conditional_value.uc --max-steps 8
ctest --test-dir .\build\windows-ucrt64-debug -R "umicom[.]c[.](conditional[.]|cli-conditional)" --output-on-failure --no-tests=error
~~~

Expect 12 compiled records, eight executed instructions and value seven for the supplied example. A seven-instruction budget exhausts at RETURN. The source tests cover selected faults, skipped faults, integer extremes, grouping, locals and incomplete punctuation. The CLI test separately checks source/wire agreement and existing-output preservation.

## Exercise and recovery

Compare 1 ? 0 : 1 ? 7 : 8 with (1 ? 0 : 1) ? 7 : 8. Predict both results before executing them: the first returns zero, the second eight. Explain which condition is used in each case.

If ? is rejected, inspect the linked compiler's conditional feature bit and select a current build. If a selected division fails, change the program's guard rather than suppressing the error. This profile does not add conditional statements, comma expressions, assignments inside expressions, omitted middle arms or pointer conversions.

[Course contents](index.md) · [Previous lesson](70-compare-logical-programs-with-native-c.md) · [Next lesson](72-bound-recursive-expression-parsing.md)
