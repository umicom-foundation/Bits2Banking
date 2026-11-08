<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/44-encode-a-countdown-program.md

PURPOSE:
Encode a countdown program

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Encode a countdown program

A CPU is a circuit that changes its internal state according to instructions. This module connects the existing teaching CPU to a stored sequence of instructions. Each lesson explains the terms it uses and follows a real source file from the Framework project template.

## Prepare the laboratory

A terminal is a window in which you type commands. An editor changes text files. GHDL interprets VHDL hardware descriptions; CMake prepares build instructions; Ninja performs the requested build steps; CTest runs the checks recorded by CMake. Install these tools and verify that ghdl --version, cmake --version and ninja --version each identify a program. A missing-command message means the installation or PATH search list needs attention.

Open a terminal in the Bits2Banking checkout. In PowerShell, enter Set-Location "C:\umicom\Umicom-Bits2Banking\labs\hardware\vhdl-cpu". In Bash, enter cd /path/to/Umicom-Bits2Banking/labs/hardware/vhdl-cpu, using your checkout path. Then run the following commands one at a time, stopping after any failure:

```text
cmake --preset simulation
cmake --build --preset simulation
ctest --preset simulation -R "^cpu[.]program$"
```

The preset is a named set of settings in CMakePresets.json. A successful program check prints Stored program checks passed. An assertion failure describes a behaviour that differs from the specification; a missing executable usually means the build did not finish. No physical board is required. This laboratory simulates a small teaching CPU. For the complete language introduction, explore [Learning HDL and VHDL](../index.html).


## Turn operations into bytes

Hexadecimal is a way to write binary values compactly. One hexadecimal digit represents four bits. In this teaching instruction set, the first digit chooses an operation and the second supplies a small number or address. The CPU's accumulator is an eight-bit register: a stored value used by arithmetic instructions. The program counter is a four-bit register selecting the next instruction.

The program is deliberately small enough to explain completely. LOAD 3 writes three into the accumulator. SUBTRACT 1 reduces it by one. JUMP-IF-ZERO 4 selects address 4 only when the accumulator is zero. JUMP 1 selects address 1 unconditionally. HALT stops execution until reset.

## Translate the program

1. LOAD uses operation 1. Combining it with operand 3 produces hexadecimal 13.
2. SUBTRACT uses operation 3. Operand 1 produces 31.
3. JUMP-IF-ZERO uses operation 5. Destination 4 produces 54.
4. JUMP uses operation 4. Destination 1 produces 41.
5. HALT uses operation F. Its unused operand is written as zero, producing F0.

This is a machine-code listing for the teaching CPU. It is not an assembly program accepted by a RISC-V assembler. A future assembler would translate readable names into these bytes while checking operand ranges.

## Trace the loop

After LOAD, the accumulator is three. SUBTRACT makes it two, so the conditional jump falls through to address 3. The unconditional jump returns to the subtract instruction. On the third subtraction the value becomes zero. The conditional jump then chooses address 4, and HALT stops the machine.

The conditional jump examines the value before its clock edge. It does not subtract again. This distinction prevents a common hand-tracing error in which a learner counts a branch as an arithmetic operation.

## Exercise

Replace only LOAD 3 with LOAD 2 on a separate learning copy. Write the expected addresses and accumulator values before changing the testbench. The program should require seven executed instructions to halt: LOAD, SUBTRACT, conditional branch, unconditional branch, SUBTRACT, conditional branch and HALT. The existing ten-step trace should fail until the specification is deliberately updated. Restore the supplied word to continue the original laboratory.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/rtl/learning_program.vhd)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/rtl/learning_program.vhd).

## Continue learning

[Course contents](../../../courses/learning-hdl-vhdl/index.html) · [Previous: Store an instruction program](43-store-an-instruction-program.md) · [Next: Connect CPU and memory](45-connect-cpu-and-memory.md)
