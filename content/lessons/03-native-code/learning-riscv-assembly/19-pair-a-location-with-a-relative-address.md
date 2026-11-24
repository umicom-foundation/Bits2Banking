<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/19-pair-a-location-with-a-relative-address.md

PURPOSE:
  Teach a beginner to pair a location with a relative address using object-only exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Pair a location with a relative address

[Previous lesson](18-record-an-absolute-symbol-address.md) · [Course contents](index.md) · [Next lesson](20-find-a-linker-relaxation-hint.md) · [HTML edition](../../../courses/learning-riscv-assembly/lessons/19-pair-a-location-with-a-relative-address.html)

A PC-relative address starts from the location of the instruction and adds the distance to the target. The **program counter** tells the processor which instruction it is using. The instruction `auipc` adds a shifted upper field to its own address. A following `addi` supplies the lower part.

## Mark the instruction that owns the pair

Save this as `relative.s`. The upper relocation names the data. The lower relocation points to the label immediately before the `auipc` so the linker can find the corresponding upper relocation.

~~~asm
.text
.globl relative_seed_address
relative_seed_address:
.Lcourse_anchor:
    auipc a0, %pcrel_hi(course_seed)
    addi a0, a0, %pcrel_lo(.Lcourse_anchor)
    ret

.data
.globl course_seed
course_seed:
    .word 23
~~~

~~~text
clang --target=riscv64-unknown-elf -march=rv64i -mabi=lp64 -mno-relax -c relative.s -o relative.o
llvm-objdump -dr -M no-aliases relative.o
~~~

| Object entry | Expected reference |
| --- | --- |
| Offset 0, `R_RISCV_PCREL_HI20` | `course_seed` |
| Offset 4, `R_RISCV_PCREL_LO12_I` | `.Lcourse_anchor` |

Imagine the instruction starts at address `0x1000` and the linked data starts at `0x2240`. The difference is `0x1240`. The upper contribution is `0x1000`, and the lower contribution is `0x240`. Add both contributions to the instruction's address to obtain `0x2240`. Moving both by the same amount keeps that difference.

If a linker reports a missing upper relocation, compare the label in `%pcrel_lo` with the label at the `auipc`. The linker needs the start of this particular pair. Reading `llvm-objdump -dr` before linking makes the association visible. Firmware and loaded executables need separate qualification.

[RISC-V ELF PC-relative symbol addresses](https://docs.riscv.org/reference/abi/riscv-elf-object-files.html)
