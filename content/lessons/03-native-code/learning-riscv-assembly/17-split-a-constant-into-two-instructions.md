<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/17-split-a-constant-into-two-instructions.md

PURPOSE:
  Teach a beginner to split a constant into two instructions using object-only exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Split a constant into two instructions

[Previous lesson](16-check-assembly-with-a-c-oracle.md) · [Course contents](index.md) · [Next lesson](18-record-an-absolute-symbol-address.md) · [HTML edition](../../../courses/learning-riscv-assembly/lessons/17-split-a-constant-into-two-instructions.html)

When a number takes more bits than one instruction can carry, build it in parts. In RV64, `lui` puts an upper field into bits 31 through 12, fills the lower bits with zero and extends bit 31 to the rest of the register. `addi` adds a signed 12-bit number. Its input can be any integer from −2048 to 2047.

## Split a known value on paper

Build `0x1234fabc`. The bottom 12 bits have the pattern `0xabc`, which represents 2748 when you read it as an unsigned number. As a 12-bit signed number that pattern means 2748 minus 4096, or −1348. Increase the upper field from `0x1234f` to `0x12350`. The signed lower part subtracts the excess.

| Step | Register value |
| --- | --- |
| `lui a0, 0x12350` | `0x12350000` |
| `addi a0, a0, -1348` | `0x1234fabc` |

Save this as `constant.s`.

~~~asm
.text
.globl seed_value
seed_value:
    lui a0, 0x12350
    addi a0, a0, -1348
    li a1, 0x1234fabc
    lui a2, 0x80000
    ret
~~~

Use the cross assembler and object inspector from the earlier object-file lesson.

~~~text
clang --target=riscv64-unknown-elf -march=rv64i -mabi=lp64 -mno-relax -c constant.s -o constant.o
llvm-objdump -dr -M no-aliases constant.o
~~~

Look for two instructions writing `a0`. This assembler also expands `li a1, 0x1234fabc` into two instructions. `li` is a shorthand that lets the assembler choose the real instructions. The inspector may print −1348 as `-0x544`. For the `a2` line, write down the full register width. The sign extension yields `0xffffffff80000000`.

The section displays instructions stored in an object. This exercise uses a paper trace and an object inspector to check the encoding. It needs no RISC-V device.

## Check the arithmetic in C

Save the companion as `arithmetic.c`. It asks a hosted C23 compiler to check both integer equalities before producing any program.

~~~c
#include <stdint.h>

static_assert(INT64_C(0x12350000) - INT64_C(1348) == INT64_C(0x1234fabc));
static_assert(INT64_C(0xabc) - INT64_C(0x1000) == -INT64_C(1348));
~~~

Run `gcc -std=c23 -Werror -fsyntax-only arithmetic.c`. Change 1348 in the first assertion to 1347 to see how one wrong unit changes the result. Restore 1348 and check the code again.

[RISC-V RV64I instruction reference](https://docs.riscv.org/reference/isa/unpriv/rv64.html)
