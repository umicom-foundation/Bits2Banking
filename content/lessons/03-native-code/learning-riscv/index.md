# Introduction to RISC-V

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## Registers, memory and control flow

Start with values and addresses, then trace branches, calls and returns.

1. [Registers, memory and instructions](01-registers-and-memory.md)
1. [Why programs ask the Kernel for help](02-programs-and-privileges.md)
1. [Trace a short sequence of register changes](03-binary-and-instruction-traces.md)
1. [Read bytes and words at memory addresses](04-addresses-and-memory-width.md)
1. [Trace a loop and prove where it stops](05-branches-and-counted-loops.md)
1. [Follow a function call and its saved return address](06-call-return-and-stack.md)

## Instruction contracts and arithmetic

Read width and signedness explicitly while following small arithmetic and bit algorithms.

1. [Read an instruction contract](07-read-an-instruction-contract.md)
1. [Distinguish register width and data width](08-distinguish-register-width-and-data-width.md)
1. [Understand signed and unsigned order](09-understand-signed-and-unsigned-order.md)
1. [Understand fixed-width arithmetic wrap](10-understand-word-arithmetic-wrap.md)
1. [Explain bit rotation](11-explain-bit-rotation.md)
1. [Use parity as a small bit algorithm](12-use-parity-as-a-small-bit-algorithm.md)

## Project: virtual-address translation

Split an address, walk three modeled tables, check permissions and preserve rejected results.

1. [Split an address into a page and an offset](13-split-an-address-into-page-and-offset.md)
1. [Extract three page-table indices](14-extract-three-page-table-indices.md)
1. [Follow a three-level page walk](15-follow-a-three-level-page-walk.md)
1. [Check canonical virtual addresses](16-check-canonical-virtual-addresses.md)
1. [Model read, write and execute permissions](17-model-read-write-and-execute-permissions.md)
1. [Construct a mapping before publishing it](18-construct-a-mapping-before-publishing-it.md)
1. [Preserve an output after translation fails](19-preserve-an-output-after-translation-fails.md)
1. [Plan evidence for an address translator](20-plan-page-walker-evidence.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

# Introduction to RISC-V

 Start with the first lesson. A register is a small processor storage location; an instruction tells the processor which operation to perform. These reading exercises need only a text editor and paper. Practical execution requires a matching toolchain and machine or emulator.

## First lessons

1. [Registers, memory and instructions](01-registers-and-memory.md)
1. [Why programs ask the Kernel for help](02-programs-and-privileges.md)

## Continue with practical labs

1. [Trace a short sequence of register changes](03-binary-and-instruction-traces.md)
1. [Read bytes and words at memory addresses](04-addresses-and-memory-width.md)
1. [Trace a loop and prove where it stops](05-branches-and-counted-loops.md)
1. [Follow a function call and its saved return address](06-call-return-and-stack.md)


- [Read an instruction contract](07-read-an-instruction-contract.md)

- [Distinguish register width and data width](08-distinguish-register-width-and-data-width.md)

- [Understand signed and unsigned order](09-understand-signed-and-unsigned-order.md)

- [Understand fixed-width arithmetic wrap](10-understand-word-arithmetic-wrap.md)

- [Explain bit rotation](11-explain-bit-rotation.md)

- [Use parity as a small bit algorithm](12-use-parity-as-a-small-bit-algorithm.md)

- [Split an address into a page and an offset](13-split-an-address-into-page-and-offset.md)

- [Extract three page-table indices](14-extract-three-page-table-indices.md)

- [Follow a three-level page walk](15-follow-a-three-level-page-walk.md)

- [Check canonical virtual addresses](16-check-canonical-virtual-addresses.md)

- [Model read, write and execute permissions](17-model-read-write-and-execute-permissions.md)

- [Construct a mapping before publishing it](18-construct-a-mapping-before-publishing-it.md)

- [Preserve an output after translation fails](19-preserve-an-output-after-translation-fails.md)

- [Plan evidence for an address translator](20-plan-page-walker-evidence.md)

</details>
