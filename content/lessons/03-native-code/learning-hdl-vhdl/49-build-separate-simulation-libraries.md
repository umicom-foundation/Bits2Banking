<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/49-build-separate-simulation-libraries.md

PURPOSE:
Build separate simulation libraries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Build separate simulation libraries

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


## Understand the intermediate files

GHDL analysis records design units in a work library. A design unit is an entity, architecture or related declaration understood by the tool. The work library is not the source directory: it is an intermediate database that later elaboration and simulation use.

The instruction test and stored-program test are independent build targets. If they wrote the same work database concurrently, one build could interfere with the other's analysis. The CMake project therefore uses ghdl-work for instruction checks and ghdl-program for the composed program. Both directories are inside the build tree.

## Follow the dependency chain

1. program_sources lists the CPU first, then program memory, then the system that instantiates them, and finally its testbench.
2. The analysis command reads this ordered list.
3. Elaboration selects tb_learning_system as the top-level design.
4. Only after successful commands does CMake touch analysis.stamp.
5. DEPENDS names every source and the GHDL executable, so a changed input makes the target out of date.

A stamp is a file used to record successful completion of a build step. Creating it before analysis succeeded would be misleading. The ALL keyword makes program_analysis part of the normal build, so a learner does not need to guess which hardware target to request.

## Separate building from testing

CTest runs the previously prepared simulation. It does not automatically repair an outdated analysis database. Build after editing a ROM word and before testing. The simulate_program target has an explicit dependency on program_analysis and also requests a waveform file.

VERBATIM asks CMake to preserve individual command arguments through the build tool. Quoted paths keep a folder such as CPU designs together. It does not validate an arbitrary shell command; this project supplies known tool arguments directly.

## Exercise

Find the four source paths and both work directories. Change one comment in the program source, then inspect the next owner-run build output. The source timestamp can still trigger analysis even though the circuit behaviour is unchanged. Record actual evidence rather than assuming a no-work result. See the [GHDL command reference](https://ghdl.github.io/ghdl/using/InvokingGHDL.html) for tool-specific analysis and simulation options.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/CMakeLists.txt)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-cpu/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-hdl-vhdl/index.html) · [Previous: Handle unresolved addresses](48-handle-unresolved-addresses.md) · [Next: Investigate a program failure](50-investigate-a-program-failure.md)
