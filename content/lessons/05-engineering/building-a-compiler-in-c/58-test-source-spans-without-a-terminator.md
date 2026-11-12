<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/58-test-source-spans-without-a-terminator.md

PURPOSE:
Test source spans without a terminator

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Test source spans without a terminator

## Before you begin
Read the compiler's public umc_compile contract and the spans test in tests/test_integer_literals.c. You need to distinguish a C string from a byte span before writing parser tests or native library adapters.

## A pointer does not describe the whole input
A C string ends at a NUL byte. A span supplies a pointer and an explicit length. Umicom C accepts source spans, so a caller may provide an array with no terminator. Calling strlen on that array would violate its contract.

The test constructs such an array deliberately:

~~~c
const char fixture[] = "int main(void){return 0x2a+0b10;}";
char raw[sizeof fixture - 1U];
memcpy(raw, fixture, sizeof raw);
~~~

The fixture includes a NUL because it is initialized from a string literal. The raw array has room only for the payload, and memcpy copies exactly those payload bytes. sizeof raw is the admitted length. No string operation is applied to raw.

An earlier spelling directly initialized the short array from a string literal. GCC's strict unterminated-string-initialization warning rejects that form. The original is retained in a disabled review block. The active explicit copy preserves the non-string test while keeping warnings enabled. Do not disable warnings or add an unnoticed terminator merely to make this fixture compile.

## Every prefix is a different input
The loop compiles every proper prefix of the complete program. Each is incomplete and must fail with count zero. The reported byte offset must stay within the supplied length. The complete non-NUL span must compile and evaluate to 44.

1. Find the prefix that ends after the initial zero of 0x2a.
2. Find the prefix that ends after x.
3. Explain why the second input must not borrow a digit from storage beyond its admitted length.
4. Find the prefix that contains the complete expression but no closing brace.
5. Explain why a nonzero partial instruction buffer is not permission to execute after failure.

The compiler may write partial instructions, but it publishes count zero on refusal. That count and the returned status are the handoff contract.

## Exercise the maximum admitted source
The second fixture fills a source buffer with a hexadecimal token containing many leading zeroes. It ends with 1 and the required punctuation. The total span is exactly UMC_SOURCE_LIMIT, and the result is still one. A declared length one byte larger must fail before reading the short allocation.

The test also inserts an embedded zero byte and expects a syntax error at that byte. A span parser must not silently treat an embedded NUL as the end of an otherwise valid source file.

~~~powershell
cmake --build build --parallel 4
ctest --test-dir build -R "umicom.c.integer-literals.spans" --output-on-failure --no-tests=error
~~~

Stop after a failed build; an old test binary does not validate newly edited source. The fixture is compiled with strict warnings as errors on GNU and Clang toolchains. Read the actual test result, including failures or skipped execution, rather than treating registration as a pass.

## Limits of this evidence
These cases exercise length admission, truncation, output-count publication and exact-size storage. A passing finite corpus is not a proof that every possible input is memory safe. Sanitizers, guard-page fixtures and fuzzing can provide additional independent evidence on suitable hosts. Keep those claims separate unless those checks have actually run.

[Course contents](index.md) · [Previous lesson](57-separate-source-spelling-from-wire-format.md) · [Next lesson](59-separate-instruction-fuel-from-wall-clock-time.md)
