<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/48-handle-unresolved-addresses.md

PURPOSE:
Handle unresolved addresses

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Handle unresolved addresses

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


## A simulation signal can be unknown

Hardware simulation represents more than binary zero and one. An unresolved or unknown value helps reveal a signal that has not yet received a meaningful drive. The standard logic type includes values such as U for uninitialized and X for unknown. These are diagnostic states in a simulation, not additional machine instructions.

An unsigned vector still uses standard logic elements. Converting an unresolved address directly to an integer can produce warnings and a value that conceals the original problem. The ROM checks is_x(std_logic_vector(address)) before calling to_integer. The conversion to std_logic_vector supplies the type expected by that check; it does not repair the bits.

## Choose an explicit result

When the address is unresolved, the memory emits hexadecimal 60. The CPU treats its high digit 6 as an invalid operation. Unused but resolved addresses also contain 60. These cases therefore lead to a visible stop and fault if executed, instead of selecting a plausible valid instruction accidentally.

This is a teaching fault policy, not a claim that physical hardware detects every electrical fault. Synthesis and board behaviour require separate analysis. The simulation rule is useful because its effect is explicit and testable.

## Read the independent memory probe

1. Open tb_learning_system.vhd and find probe_address.
2. Its initial value fills every position with X.
3. A separate memory instance named probe receives this address.
4. After signal updates settle, the test requires the invalid word.
5. The test then selects resolved address 15 and requires the same invalid word for an unused location.

The probe does not drive the CPU's program counter. It examines the ROM interface independently, while the main system executes its valid program.

## Exercise

Explain the difference between an unknown address and an unused address. The first lacks a resolved numeric selection; the second is a valid number whose table entry is deliberately invalid. Keep both checks when modifying memory contents. If a future program legitimately occupies address 15, update the unused-address test to a documented unused location rather than removing the test entirely.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/rtl/learning_program.vhd)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/rtl/learning_program.vhd).

## Continue learning

[Course contents](../../../courses/learning-hdl-vhdl/index.html) · [Previous: Pause, halt and restart a program](47-pause-halt-and-restart-a-program.md) · [Next: Build separate simulation libraries](49-build-separate-simulation-libraries.md)


[Manuscript course contents](index.md)
