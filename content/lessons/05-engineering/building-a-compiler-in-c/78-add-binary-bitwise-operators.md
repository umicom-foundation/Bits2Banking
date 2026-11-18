<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/78-add-binary-bitwise-operators.md

PURPOSE:
Teach eager bitwise semantics, signed representation and version-six consumer compatibility.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Add binary bitwise operators and preserve bytecode compatibility

[Course contents](index.md) · [Previous lesson](77-lower-signed-bitwise-complement.md)

A flag is a named bit in an integer. AND keeps bits present in both operands, OR keeps bits present in either, and XOR keeps bits present in exactly one. Umicom C supports signed 32-bit &, ^ and |, plus &=, ^= and |= on initialized local variables. This is a bounded language extension, not a complete C23 implementation.

## Work through one value

~~~c
int main(void)
{
    int flags = 63;
    flags &= 47;
    flags ^= 5;
    flags |= 0;
    return flags;
}
~~~

63 is binary 00111111 and 47 is 00101111. Their AND is 47. XOR with 5, binary 00000101, gives 42, binary 00101010. OR with zero keeps 42. A compound update loads the old local once, evaluates the right expression once, applies the operation, then stores the result. Assignment is still a statement: return flags &= 42; is rejected.

## Separate grouping from evaluation

From tighter to looser grouping, the relevant levels are equality, bitwise AND, bitwise XOR, bitwise OR, logical AND and logical OR. Thus 63 & 47 ^ 5 | 0 returns 42. However, 5 & 3 == 1 groups as 5 & (3 == 1), returning zero. Write (flags & mask) == mask when testing whether every mask bit is present. Operators at each level group from the left.

Both operands of a bitwise operation execute. The program return 0 & (1 / 0); fails at division. Logical 0 && (1 / 0) returns zero because its right side is skipped. This compiler evaluates the two bitwise operands from left to right; do not assume that this choice defines the evaluation order of arbitrary native C expressions in a different compiler.

## Represent signed endpoints explicitly

The runtime converts each signed input to uint32_t, giving its value modulo 2 to the power 32, then performs the operation on those unsigned values. Values at most INT32_MAX convert directly back; larger values are reduced by 4294967296 in int64_t before conversion. That final value is in the signed 32-bit range. This avoids relying on an out-of-range unsigned-to-signed conversion.

~~~c
uint32_t bits = (uint32_t)left ^ (uint32_t)right;
int64_t signed_value = bits <= INT32_MAX
    ? (int64_t)bits
    : (int64_t)bits - INT64_C(4294967296);
~~~

The snippet explains XOR; inspect bitwise_value in src/vm.c for all three operations. -1 & 42 is 42, -1 ^ 42 is -43, and -1 | 42 is -1. The minimum signed value XOR -1 is the maximum signed value. Bitwise operations cannot overflow this representation. Other operations in the same program can still fail.

## Extend bytecode without relabelling old programs

BITWISE_AND = 19, BITWISE_XOR = 20 and BITWISE_OR = 21 each have a zero reserved operand, consume two values and push one. A program using any of these records requires format 6. The existing eight-byte header and nine-byte records remain unchanged. Old arithmetic, comparison, local, branch and remainder programs keep formats 1 through 5 according to their minimum requirements.

The encoder must inspect the whole program before choosing its minimum format. Returning format 5 immediately when seeing a remainder would mislabel a later bitwise instruction. The decoder validates the complete graph and requires the canonical minimum version. Changing only the version byte is not a conversion. Unknown opcodes, nonzero reserved operands, stack underflow and mismatched versions are refused.

## Run source and saved bytecode

From a configured Umicom C checkout, use the existing build directory below. Adjust it if your build uses another directory. Compilation refuses to overwrite an existing output; use a fresh destination on later attempts.

~~~powershell
& ".\build\bin\umicom-c.exe" check .\examples\bitwise.uc
& ".\build\bin\umicom-c.exe" compile .\examples\bitwise.uc .\bitwise.umcb
& ".\build\bin\umicom-c.exe" run .\examples\bitwise.uc --max-steps 8
& ".\build\bin\umicom-c.exe" exec .\bitwise.umcb --max-steps 8
& ".\build\bin\umicom-c.exe" disassemble .\bitwise.umcb
& ".\build\bin\umicom-c.exe" trace-bytecode .\bitwise.umcb
& ".\build\bin\umicom-c.exe" profile
~~~

The expression example has eight instructions and returns 42. A budget of seven fails before RETURN and publishes no completed result. Its file starts with bytes 55 4d 43 42 06 00 08 00. The local-variable example above needs sixteen instructions, because loads and stores consume fuel. Source and saved-bytecode traces should agree, including source offsets.

## Check a linked consumer independently

UMC_FEATURE_BINARY_BITWISE is bit 65536 in both compiler and runtime profiles. The complete compiler feature mask is 130791, runtime features are 82331 and supported wire-version bits are 126. Query the component you actually link; a new header does not prove an installed DLL has the same capability. Source-only complement remains compiler bit 32768 and must not appear in a runtime-only feature mask.

The Kernel CVM uses independent literal format-6 bytes in programs/cvm/bitwise_checks.h. Host and RISC-V guest checks exercise AND, XOR, OR, fuel, signed endpoints, reserved operands and wrong versions. Framework preview delegates to the canonical compiler and runtime; its separate regression checks completed-result clearing after failure. A compiler or guest pass does not establish a Framework build or Studio UI pass.

## Diagnose an unexpected failure

1. For an unknown token, inspect the CLI profile and rebuild the intended executable; do not silently substitute another checkout.
2. For refused bytecode, inspect the header and disassembly with a compatible tool. Do not patch a version byte to bypass admission.
3. If a test formerly rejected 1 & 2, replace that obsolete refusal with a missing operand or unsupported shift and retain positive coverage. An obsolete unknown-opcode fixture must move beyond newly assigned values.
4. For a borrowed span ending after &, expect the missing right operand at the span end. Never read the next byte outside that span.
5. Shifts, unsigned declarations, pointers, address-taking and assignment expressions remain unsupported. ~= is not a C compound assignment.

## Exercises

1. Predict -1 ^ 42, (5 & 3) == 1 and 5 & 3 == 1; verify values and grouping.
2. Compare traces for 0 & (1 / 0) and 0 && (1 / 0). Identify the failing or skipped instruction.
3. Change the local example to flags &= ~16; flags ^= 5; and derive the complement instruction cost before running it.
4. Use literal bytes independent of the encoder to test valid format 6 and a nonzero reserved operand. Explain why encoder/decoder agreement alone is insufficient.
5. Inspect tests/test_bitwise.c for capacity, spans, fuel, endpoints and native comparison coverage. Add a boundary case with an explicit expected value rather than copying the implementation into the assertion.

[Next lesson](79-run-bytecode-in-bounded-slices.md)
