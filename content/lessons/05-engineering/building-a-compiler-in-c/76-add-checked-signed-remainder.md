<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/76-add-checked-signed-remainder.md

PURPOSE:
Add checked signed remainder without breaking bytecode

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Add checked signed remainder without breaking bytecode

Remainder answers how much is left after integer division. It is useful for grouping counters, selecting a bucket or checking whether an integer is divisible by another. Adding the percent operator to a language requires more than recognizing one character: source precedence, arithmetic failures, bytecode identities, capability queries and independent consumers must agree. This lesson follows the native Umicom C implementation and its shared Kernel runtime.

## 1. Predict signed results

Umicom C uses signed 32-bit integers and division that truncates toward zero. Its remainder follows that division: 7 % 3 is 1, -7 % 3 is -1, 7 % -3 is 1, and -7 % -3 is -1. A nonzero result has the sign of the left operand. This differs from a mathematical modulo operation that always chooses a nonnegative result. State which meaning your application requires before choosing the operation.

~~~c
int main(void)
{
    int value = 137;
    value %= 95;
    return value;
}
~~~

The example returns 42. The initializer stores 137, the compound assignment reads that old value once and computes its remainder with 95, then the final return reads the updated local. The resulting program contains eight records and requires eight units of instruction fuel. Remainder assignment remains a statement: it cannot appear inside another expression or declare a new local.

## 2. Admit tokens and preserve precedence

The lexer recognizes a percent character and optionally one immediately adjacent equals character. Its lookahead stays inside the caller-provided source span, which need not end in a NUL byte. A space or comment between the two characters does not form a compound assignment. Thus value %= 3 is accepted, while value % = 3 is rejected. Neither source form enables floating-point, unsigned or array operations.

The parser places remainder beside multiplication and division. Operators in this group associate to the left: 20 % 6 / 2 means (20 % 6) / 2, producing 1. Addition binds less tightly, so 2 + 7 % 3 * 4 produces 6. Parentheses can override this grouping. Each source operand is emitted once; the runtime consumes the two resulting stack values.

## 3. Guard native arithmetic before using it

~~~c
if (right == 0 || (left == INT32_MIN && right == -1)) {
    status = UMC_ARITHMETIC_ERROR;
} else {
    value = left % right;
}
~~~

A zero divisor is invalid. The minimum signed value paired with minus one is also rejected before the host remainder expression executes. The matching division quotient cannot fit in the signed type, even though the mathematical remainder would be zero. Evaluating the native operator first and checking afterward is too late. Both checks live in the shared runtime, so ordinary execution, tracing and freestanding Kernel execution use one contract.

On a failed remainder operation the runtime preserves the caller’s previous completed result. The trace can still describe the failed attempt: its opcode is remainder, its source location identifies the percent operator, and its two operands remain on the stack. The assignment store after that operation does not execute. An editor adapter should clear its own displayed completion before presenting the new failure.

## 4. Keep instruction identity stable

Remainder is appended as opcode 18. Earlier opcode numbers remain unchanged. A separate operation is necessary because a naive expansion of a % b into a - (a / b) * b can evaluate source operands more than once and complicate checked temporary storage. One runtime record gives it an explicit two-input, one-output stack contract and one unit of fuel. It is counted as arithmetic by program inspection.

Whole-program validation still happens before execution. A remainder instruction requires two available operands and a zero reserved operand field. Invalid stack shapes, malformed operands or impossible source offsets are rejected even when the execution budget is zero. Forward-branch validation still checks all structural paths, including an unselected branch containing remainder. Runtime arithmetic faults occur only on the selected path.

## 5. Select the highest required wire profile

Portable bytecode uses a versioned header and fixed nine-byte records. Remainder requires format 5. Arithmetic-only programs still use format 1; comparisons require at least 2, locals at least 3 and forward branches at least 4. The encoder selects the highest requirement anywhere in the complete program. It must continue scanning after seeing a branch, because a later remainder can require a newer profile.

The decoder checks the full program and then requires the canonical minimum version. A remainder program labelled format 4 is refused. An old division-only program unnecessarily labelled format 5 is also refused. This rule keeps one representation for an admitted program and prevents a new operation from being presented to an older consumer under an old header. Updating a source file does not update an already installed executable.

~~~text
55 4d 43 42 05 00 04 00
01 07 00 00 00 0a 00 00 00
01 03 00 00 00 14 00 00 00
12 00 00 00 00 1e 00 00 00
07 00 00 00 00 28 00 00 00
~~~

This independent fixture encodes PUSH 7, PUSH 3, REMAINDER and RETURN, with source offsets 10, 20, 30 and 40. The hexadecimal opcode 12 is decimal 18. It executes to 1 in four steps. A literal byte fixture checks the encoder and decoder against an external expectation rather than merely checking that two implementations agree with each other.

## 6. Query the linked implementation

UMC_FEATURE_REMAINDER is bit 16384 in both compiler and runtime capability reports. The complete compiler mask is currently 65255, the runtime mask is 16795, and the supported wire-version mask is 62, meaning bits 1 through 5. Applications should test the individual remainder bit and format-5 bit rather than freeze a whole-mask comparison. Compiler-only features such as else-if spelling remain absent from the runtime report.

A declaration in a new header does not prove an old linked library supports the operation. The runtime-only regression links no parser, executes a fixed remainder program and checks its wire profile. The compiler regression compiles and executes a source update. An independent installed consumer must still identify and test the particular libraries it actually links.

## 7. Exercise the native CLI

~~~powershell
.\build\bin\umicom-c.exe profile
.\build\bin\umicom-c.exe check examples\remainder.uc
.\build\bin\umicom-c.exe run examples\remainder.uc --max-steps 8
.\build\bin\umicom-c.exe compile examples\remainder.uc remainder.umcb
.\build\bin\umicom-c.exe exec remainder.umcb --max-steps 8
.\build\bin\umicom-c.exe disassemble remainder.umcb
~~~

Use the executable from your actual build directory and a new output filename. Expect result 42 and eight executed instructions. Lower the budget to seven to observe exhaustion at RETURN without a completed result. Compare source and bytecode traces, then try a zero divisor and the minimum-value/minus-one pair. Source check can accept structurally valid arithmetic that later fails during execution; these are distinct phases.

## 8. Keep capacity failures precise

Compiler instruction storage and encoded byte storage have different refusal contracts. When the compiler cannot emit another instruction, it reports UMC_PROGRAM_TOO_LARGE and leaves the published instruction count at zero. When the encoder cannot fit the complete byte representation, it reports UMC_BUFFER_TOO_SMALL and leaves the published byte count at zero. A regression should assert the status belonging to the operation it actually called, instead of guessing from similarly named limits.

## 9. Qualify consumers in separate layers

The Kernel guest includes independent format-5 bytes and delegates arithmetic to the canonical Umicom C runtime. New selectors cover positive and negative results, zero and minimum-value failures, an incorrect wire version, fuel exhaustion and a malformed reserved operand. The same entry runs in a host envelope and in real RISC-V user mode at O0 and O2. The guest helper header belongs in the source receipt so changing it invalidates earlier image evidence.

Host tests do not prove privilege transitions or Kernel frame cleanup. Guest checks do not prove Studio’s UI result ownership. The Framework preview fixture separately checks successful remainder and clearing an earlier result after arithmetic or fuel failure. Keep authored tests, registered tests, executed tests, skips and installed-consumer evidence separate.

## Exercise

Write a program that distinguishes even and odd integers with value % 2, including negative inputs. Add a guarded divisor that avoids zero through a conditional expression. Predict every result before running it. Then move the remainder into the later arm of a conditional and inspect the bytecode version: the encoder must still select format 5 even when that arm is not executed. Finally compare a small corpus against ordinary native C, excluding its undefined divisor pairs.

[Course contents](index.md) · [Previous lesson](75-lower-ordered-else-if-chains.md)

<!-- Previous complete compiler mask before unary complement: 32487. -->

[Next lesson: Lower signed bitwise complement through checked arithmetic](77-lower-signed-bitwise-complement.md)
