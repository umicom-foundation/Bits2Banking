<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/50-investigate-a-program-failure.md

PURPOSE:
Investigate a program failure

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Investigate a program failure

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


## Start with the first disagreement

A failing simulation is evidence that an observed transition differs from the test's expectation. Possible causes include an incorrect instruction word, a wiring mistake, a CPU defect, a stale build or a wrong test expectation. Do not choose a cause merely because it is familiar.

Use the program trace to localize the failure. If the first LOAD result is correct but the first subtraction is wrong, investigate the instruction at address 1 and the arithmetic transition. If the accumulator is correct but the next address is wrong, inspect branch selection and the program-counter output.

## Capture a bounded run

1. Build the project so the simulation matches the current sources.
2. Run the cpu.program test and save its first assertion message.
3. Run the simulate_program target when a waveform will help.
4. Open program.ghw with a compatible waveform viewer.
5. Add clock, reset, enable, address, instruction, accumulator, halted and fault to the display.
6. Locate the rising edge immediately before the disagreement and compare its input instruction with the next stable outputs.

The one-nanosecond observation delay in the testbench is a simulation convenience. It gives scheduled updates time to settle. It does not assert that the physical processor would meet a one-nanosecond timing budget.

## Protect the meaning of a pass

A separate deadline process fails after two microseconds if normal completion never occurs. CTest also applies a wall-clock timeout, protecting against a stalled simulator. These limits measure different things: simulated circuit time and elapsed host time.

Do not replace a failing assertion with a successful early exit. Do not extend a timeout without understanding why the workload needs more time. Do not change expected trace values until the written instruction specification justifies them.

## Exercise and extension

Create a separate project copy, alter the branch destination from 4 to 3, and predict the first differing trace entry. The third subtraction reaches zero, but the conditional branch now selects address 3 instead of 4. Investigate that mismatch and restore the original word. Keep a short public engineering note describing the symptom, cause, correction and regression check. The same method applies when a Framework-generated project fails inside Studio.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/tests/tb_learning_system.vhd)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/tests/tb_learning_system.vhd).

## Continue learning

[Course contents](../../../courses/learning-hdl-vhdl/index.html) · [Previous: Build separate simulation libraries](49-build-separate-simulation-libraries.md)
