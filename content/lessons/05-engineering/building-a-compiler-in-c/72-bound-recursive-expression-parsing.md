<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/72-bound-recursive-expression-parsing.md

PURPOSE:
Bound recursive expression parsing

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Bound recursive expression parsing

## Goal

Keep parser recursion bounded when a new operator recursively invokes the expression parser. A finite source buffer alone does not guarantee acceptable call-stack use. The depth bound, instruction bound and runtime execution budget protect different resources.

## Find the recursive edges

The unary parser already increases depth for another unary operator or a parenthesized expression. Conditional parsing adds two more recursive edges: the true arm and the false arm. Both call expression with depth + 1. The next unary entry rejects depth at or beyond UMC_PARSE_DEPTH_LIMIT before consuming another operand.

Passing the old depth to either arm would let nested conditionals bypass the established bound. Applying a separate unrelated counter could also let mixed parentheses, unary operators and conditionals exceed the intended shared allowance. Follow one depth parameter through the complete parser call chain.

## Distinguish resource limits

| Bound | Resource protected | Observable refusal |
| --- | --- | --- |
| Source bytes | Borrowed input span | Source-too-large status |
| Parse depth | Recursive parser calls | Depth-limit status |
| Program capacity | Emitted instruction slots | Program-too-large status |
| Execution fuel | Instructions on the selected path | Fuel-exhausted status |

A valid source program can reach one limit before another. Do not assume a test exercises recursion merely because its source looks deeply nested. Count the instructions emitted before the deepest operand is reached.

## Construct both nesting directions

Read bounds in tests/test_conditional.c. One generated source repeatedly prefixes 1? and appends :0 arms after the final seven. The other repeatedly prefixes 0?0: before the final seven. These exercise recursive middle and final arms separately.

With 63 conditional levels, the full program contains 254 records and remains within the 256-record capacity. Both forms return seven. With a 64th level, the parser must report the depth limit and publish count zero. The test uses an explicit byte length; a trailing zero is not part of the input contract.

## Preserve publication rules

The output buffer may contain partial instructions after a failed compile, but count must remain zero. A caller must never execute that partial buffer. A later successful compile can reuse storage only after checking the new status and count. This is different from claiming that a failed compile leaves every output byte untouched.

The same source test group also checks a capacity one record below the required count and a borrowed span ending after :. Those failures should not be misreported as a successful empty program.

## Qualify the exact boundary

~~~powershell
ctest --test-dir .\build\windows-ucrt64-debug -R "^umicom[.]c[.]conditional[.]bounds$" --output-on-failure --no-tests=error
~~~

A pass covers the selected host compiler and the concrete generated forms. It does not measure every possible native call-stack frame or prove unlimited nesting is safe. Keep the production depth limit in place even on a machine with more memory.

## Read exact wire fixtures carefully

The neighboring wire-trace case uses the exact text int main(void){return 0?7:42;}. Its condition begins at byte 22, ? at 23, true value at 24 and false value at 26. The space after return occupies byte 21. Enumerate the literal independently before freezing golden bytes; changing a compiler to satisfy an incorrectly counted fixture would create a product defect.

## Exercise and recovery

Wrap a conditional in several pairs of parentheses and add unary negation inside one arm. Trace how the shared depth changes and predict which operand reaches the limit first. Keep a separate instruction count. If a test reports program capacity before depth, redesign the fixture to reach its intended boundary; do not weaken either guard.

[Course contents](index.md) · [Previous lesson](71-select-values-with-conditional-expressions.md)
