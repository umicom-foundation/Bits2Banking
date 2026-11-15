<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/73-lower-checked-compound-assignments.md

PURPOSE:
Lower checked compound assignments

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Lower checked compound assignments

## Goal

Extend a small language without duplicating its runtime. This lesson adds four compound-assignment statements to Umicom C: +=, -=, *= and /=. You will follow a token into the parser, compare the emitted operations with an ordinary assignment, and prove both successful updates and refusals. Read the earlier local-variable and conditional-expression lessons first. The implementation remains a bounded integer language, not a general C23 compiler.

## Start with an existing local

~~~c
int main(void)
{
    int balance = 40;
    balance += 2;
    return balance;
}
~~~

This program returns 42. balance must already be initialized before the update. A declaration such as int balance += 2; is invalid. Keeping declaration and update separate avoids reading a value that has never been stored. The compiler looks up the name in its per-call symbol table, and emitted instructions carry a slot number rather than a pointer into the source text. These educational integers do not constitute production financial money types or accounting logic.

## Recognize one adjacent token

In umicom-c/src/lexer.c, an arithmetic character looks ahead by one byte only when that byte lies inside the supplied source span. An adjacent equals sign forms the compound token. Spaces or comments may surround the complete token, but x + = 2 and x +/**/= 2 are two tokens and fail. A final plus at the end of a non-terminated span must not cause an out-of-bounds read. Slash comments are recognized before ordinary token classification, so a real /= operator must remain distinct from // and /*.

The four token kinds are private compiler details. Appending them does not change the public instruction encoding. Preserve ordinary arithmetic tokenization: a program that previously used x = x + 2 must still compile. Test longest-match behavior and truncated spans separately; a test on a normal NUL-terminated string cannot demonstrate the whole borrowed-span contract.

## Reuse checked operations

~~~text
PUSH 40
STORE_LOCAL 0
LOAD_LOCAL 0
PUSH 2
ADD
STORE_LOCAL 0
LOAD_LOCAL 0
RETURN
~~~

The compiler loads the old value, parses the whole right expression, emits the corresponding arithmetic operation and stores the result. x *= 2 + 3 therefore multiplies by five. x += x * 2 reads the old x in the right expression. The left side here is only a local integer name, with no address side effects. A future array subscript, pointer dereference or function call would need its own evaluation rules; blindly duplicating such an expression would be wrong.

The update arithmetic uses the existing signed-overflow and division checks in the VM. There is no second calculator inside the parser and no new runtime opcode. A program using locals alone remains format 3. A conditional or logical expression on the right uses existing forward branches and selects format 4. A compiler-only feature bit, UMC_FEATURE_COMPOUND_ASSIGNMENTS with value 2048, identifies the new grammar. The runtime must not claim it parses that syntax.

## Follow failures before publication

Change the initializer to 2147483647 and add one. The source is syntactically valid, but execution fails at ADD. The assignment store has not executed and the caller's completed-result object stays unchanged. Umicom C deliberately refuses signed overflow; do not execute the overflowing expression in a native-C oracle, where signed overflow has undefined behavior. The trace can retain completed steps plus the failed attempt without pretending the program completed.

A right expression can fail before the update arithmetic. For example, x *= 1 / 0 fails even if x is zero. Multiplication does not skip its right side. In contrast, x += 0 && 1 / 0 uses logical short-circuiting within the right expression and adds zero. Both expressions still have to parse and satisfy structural validation. The API does not expose partially updated local slots across calls.

## Build and inspect the example

From the Umicom C checkout, use a C23 host compiler and Ninja. Each build cache must belong to one source checkout. Run commands separately and stop on errors. The supplied example multiplies six by seven and needs eight instructions including RETURN.

~~~powershell
cmake -S . -B build -G Ninja -DUMICOM_C_BUILD_TESTS=ON
cmake --build build
.\build\bin\umicom-c.exe profile
.\build\bin\umicom-c.exe check .\examples\compound_assignment.uc
.\build\bin\umicom-c.exe run .\examples\compound_assignment.uc --max-steps 8
.\build\bin\umicom-c.exe trace .\examples\compound_assignment.uc
.\build\bin\umicom-c.exe compile .\examples\compound_assignment.uc .\compound-assignment.umcb
.\build\bin\umicom-c.exe disassemble .\compound-assignment.umcb
.\build\bin\umicom-c.exe exec .\compound-assignment.umcb --max-steps 8
~~~

Expect result 42, eight executed instructions and format 3. Choose a new output filename; compilation refuses to replace an existing artifact. Retry the run with a seven-step budget: RETURN cannot execute, so no completed result should appear. If the profile lacks bit 2048 or check rejects *=, confirm the executable path and rebuild the intended compiler. A new source checkout does not update an old installed binary.

## Design independent regression evidence

tests/test_compound_assignment.c compares 1,425 small updates with native C, avoiding division by zero and overflow in the oracle. Separate fault cases deliberately trigger Umicom's defined arithmetic errors. A literal format-3 byte vector checks numeric opcodes, operands and source offsets without deriving expectations from the compiler being tested. Enumerate offsets from the exact fixture text; a mistaken expected offset is a test defect, not evidence that the parser should move an operator.

The capacity fixture contains one declaration, 63 updates and one return: two initializer records, four per update and two final records make 256. Adding the 64th update must fail with a published instruction count of zero. The old value also occupies a stack position while the right expression runs, so stack and parser-depth limits continue to apply. A source-byte bound, an instruction bound, runtime fuel and a wall-clock timeout protect different resources.

~~~powershell
ctest --test-dir build -R "umicom.c.(compound-assignment|cli-compound-assignment|profile|cli-profile)" --output-on-failure --no-tests=error
ctest --test-dir build --output-on-failure --no-tests=error
~~~

## Exercise and scope

1. Predict x after int x=7; x+=x*2; and then confirm 21 by tracing the loads and store.
2. Reject int x+=1;, return x+=1;, x%=2; and x + = 2;. Explain why each is outside this grammar.
3. Compare the operations for x*=7; and x=x*7;. Their computation agrees, while operator source locations can differ.
4. Record the tested compiler source, toolchain and results. Qualify Framework consumers and Kernel guests separately; hosted tests do not establish GUI or SDK execution.

Read the implementation and tests alongside umicom-c/docs/compound-assignments.md. These statements add no loops, pointers, floating-point values, assignment expressions or arbitrary source-language translation. Extending a shared runtime carefully means naming its supported boundary and testing that boundary, not claiming compatibility from a familiar spelling.

[Course contents](index.md) · [Previous lesson](72-bound-recursive-expression-parsing.md) · [Next lesson](74-lower-braced-conditional-statements.md)
