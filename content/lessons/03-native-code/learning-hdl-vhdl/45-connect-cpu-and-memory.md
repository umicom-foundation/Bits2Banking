<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/45-connect-cpu-and-memory.md

PURPOSE:
Connect CPU and memory

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Connect CPU and memory

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


## Describe a connected circuit

A component interface describes which signals enter and leave a circuit. Composition connects existing components into a larger circuit. learning_system has clock, reset and enable inputs. Its outputs expose the address, accumulator, instruction, halted flag and fault flag. These outputs make the internal activity visible to the testbench.

Two internal signals connect the components. pc holds the CPU's selected address. word holds the instruction returned by memory. The declaration signal pc : unsigned(3 downto 0) gives pc four numbered positions. word uses std_logic_vector because its bits encode an instruction rather than a single number used directly for arithmetic.

## Read each connection

1. memory : entity work.learning_program creates an instance named memory from the analyzed learning_program entity.
2. port map associates its address input with pc and its instruction output with word.
3. cpu : entity work.learning_cpu creates the existing CPU instance.
4. Its instruction input receives word. Its address output drives pc.
5. Concurrent assignments expose pc and word at the system boundary.

The names before the association arrows belong to the component's ports. Names after the arrows belong to the surrounding architecture. Named associations help reviewers notice a swapped signal. A matching type and width are necessary, but type correctness alone cannot prove the wires connect the intended functions.

## Why the design has no second execution engine

learning_system does not decode instructions or calculate arithmetic. Those behaviours remain in learning_cpu. The ROM does not change registers; it selects a word. Keeping these responsibilities separate allows the same CPU to be tested with either a controlled instruction input or an actual program.

VHDL concurrent statements describe circuits operating together. They are not a list of C function calls executed from top to bottom. After a clock edge changes pc, the memory reacts and presents the next word. The testbench waits for these scheduled updates before inspecting them.

## Exercise

Draw three boxes: testbench, CPU and program memory. Label every arrow with its signal name and direction. Mark the clock arrow only where it is consumed. Then identify which component must change to add a different stored program. The ROM contents change; the CPU interface and instruction decoder can remain the same.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/rtl/learning_system.vhd)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/rtl/learning_system.vhd).

## Continue learning

[Course contents](../../../courses/learning-hdl-vhdl/index.html) · [Previous: Encode a countdown program](44-encode-a-countdown-program.md) · [Next: Check a program trace](46-check-a-program-trace.md)
