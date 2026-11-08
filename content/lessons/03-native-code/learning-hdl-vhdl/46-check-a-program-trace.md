<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/46-check-a-program-trace.md

PURPOSE:
Check a program trace

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Check a program trace

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


## Specify every step

A trace records values in order. A test oracle is an independent statement of the result a test should observe. This testbench uses two arrays as its oracle: expected_pc and expected_acc. Their entries describe the state after each enabled instruction, not before it.

The address sequence is 1, 2, 3, 1, 2, 3, 1, 2, 4, 4. The accumulator sequence is 3, 2, 2, 2, 1, 1, 1, 0, 0, 0. The last repeated address is intentional: HALT leaves the program counter pointing at the halt instruction.

## Follow the test process

1. The clock starts at zero and toggles every five nanoseconds. A rising edge occurs when it changes from zero to one.
2. The edge procedure waits for a rising edge and then one nanosecond for signal updates to settle.
3. Reset is initially asserted. The first observation expects address zero, accumulator zero and the LOAD instruction.
4. Reset is released. A loop executes one edge for each expected trace entry.
5. Assertions compare the address and accumulator with the corresponding entries and require fault to remain clear.

An assertion checks a condition. severity failure tells the simulator that a false condition must stop this check unsuccessfully. The CMake test command also sets --assert-level=error, so error-level assertions cannot silently pass.

## Avoid copying the implementation into the oracle

The expected arrays were derived from the written instruction specification. Reimplementing the CPU decoder inside the testbench risks reproducing the same mistake twice. A fixed trace is intentionally simple: a reviewer can work through ten rows without trusting another execution engine.

The trace does not prove every possible program is correct. Individual instruction tests cover arithmetic boundaries and invalid operations separately. These two kinds of evidence complement each other.

## Exercise

On paper, place columns for executed address, instruction, next address and next accumulator. Fill all ten rows. Compare the last two columns with the arrays only after completing your calculation. If a simulation fails, record the first differing row and investigate that transition before examining later consequences.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/tests/tb_learning_system.vhd)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/tests/tb_learning_system.vhd).

## Continue learning

[Course contents](../../../courses/learning-hdl-vhdl/index.html) · [Previous: Connect CPU and memory](45-connect-cpu-and-memory.md) · [Next: Pause, halt and restart a program](47-pause-halt-and-restart-a-program.md)
