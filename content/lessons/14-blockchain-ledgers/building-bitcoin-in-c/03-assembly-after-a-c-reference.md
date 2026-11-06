# Assembly after a C reference

[Course contents](index.md) · [Previous: A bounded little-endian reader](02-a-bounded-little-endian-reader.md)

## Optimise only a defined operation

Assembly instructions are specific to a processor architecture and calling convention. A calling convention defines where arguments and results go and which registers a function must preserve. Write a correct C reference and expected results before substituting Assembly.

Consider this illustrative function that returns the first four bytes of a valid buffer as a little-endian number. The caller must already have validated the pointer and four-byte span. The snippet is GNU assembler AT&T syntax for the x86-64 System V ABI on Linux, not Windows x64 or RISC-V.

```asm
.text
.globl read_word_unchecked
.type read_word_unchecked, @function
read_word_unchecked:
    movl (%rdi), %eax
    ret
.size read_word_unchecked, .-read_word_unchecked
.section .note.GNU-stack,"",@progbits
```

In this ABI the first pointer argument arrives in rdi. movl loads 32 bits into eax, where a 32-bit result is returned. x86-64 stores this integer in little-endian order. The ret instruction returns to the caller. This function performs no length check; its name deliberately says unchecked. The [x86-64 psABI project](https://gitlab.com/x86-psABIs/x86-64-ABI) maintains the calling-convention specification.

## A comparison plan

1. Keep the bounded C reader from lesson 2 as the public interface.
2. Compare only after validation succeeds; never let an Assembly shortcut bypass the span check.
3. Prepare vectors with zero, high bits set and differing byte orders.
4. Compare C and Assembly results under the same architecture and ABI.
5. Measure a realistic workload before deciding the Assembly is worthwhile. A compiler may already emit the same load.

## Exercise

Why is pasting this function into a Windows build incorrect? Why should a faster hash implementation still be checked against known answers?

## Explained answer

Windows x64 normally passes the first pointer argument in a different register and uses different object-format conventions. Matching an architecture name is not enough. A fast hash that produces a wrong digest is incompatible; performance never replaces correctness. Framework should own reviewed optimisations and portable fallbacks so applications share the same behaviour.

The opening module stops at bounded parsing and an Assembly comparison design. It does not implement Bitcoin mining, signatures, networking or a spendable cryptocurrency.

## Continue learning

[Course contents](index.md) · [Previous: A bounded little-endian reader](02-a-bounded-little-endian-reader.md)

[Browser edition](../../../courses/building-bitcoin-in-c/lessons/03-assembly-after-a-c-reference.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.

[Primary reference](https://developer.bitcoin.org/reference/block_chain.html).
