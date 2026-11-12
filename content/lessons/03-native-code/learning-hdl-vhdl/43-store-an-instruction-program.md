<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/43-store-an-instruction-program.md

PURPOSE:
Store an instruction program

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Store an instruction program

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


## What a memory address means

An address selects one location in a memory. Our address has four binary digits, called bits. Four bits represent sixteen combinations, from 0000 to 1111, so this memory has locations 0 through 15. Each location holds eight bits. A memory word is the collection of bits returned by one address; it is eight bits in this design, not a universal size for every computer.

Open learning_program.vhd. The entity declares its interface: address is an input and instruction is an output. The architecture describes how that interface behaves. program_words is an array type whose indices are the integers 0 through 15. Each array element is a std_logic_vector with eight positions. A constant named program supplies the contents.

## Read the table

1. Find 0 => x"13". The arrow associates location 0 with hexadecimal 13.
2. Find 1 => x"31". Location 1 holds the subtract instruction.
3. Find 4 => x"F0". This location stops execution.
4. Find others => x"60". Every location not listed receives an invalid operation.

Read-only means the design supplies no write input. Changing the source and rebuilding changes the simulated memory contents. It does not mean a program can write a new instruction while this simulation is running.

## Follow the lookup

The process(all) block reacts whenever a signal it reads changes. For a resolved address, to_integer converts the unsigned bits into an array index. program(index) selects the word, and the signal assignment schedules that word on instruction. There is no clock in this memory: its output follows the address after the simulator processes signal updates.

The CPU, by contrast, changes state at a clock edge. This separation matters: selecting an instruction and executing it are different operations. Draw address → program table → instruction → CPU, then draw the CPU's next address back to the table.

## Exercise

Write the words for addresses 0, 3, 4 and 15 without running the program. They are 13, 41, F0 and 60. Explain why 15 returns an invalid operation rather than silently executing a no-operation instruction. If an unexpected jump reaches unused memory, stopping with a fault is easier to diagnose than continuing through unspecified behaviour.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/rtl/learning_program.vhd)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/rtl/learning_program.vhd).

## Continue learning

[Course contents](../../../courses/learning-hdl-vhdl/index.html) · [Next: Encode a countdown program](44-encode-a-countdown-program.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](42-review-cpu-evidence-and-next-steps.md)


[Manuscript course contents](index.md)
