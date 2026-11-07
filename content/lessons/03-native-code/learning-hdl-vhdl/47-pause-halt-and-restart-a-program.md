<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/47-pause-halt-and-restart-a-program.md

PURPOSE:
Pause, halt and restart a program

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Pause, halt and restart a program

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


## Three controls with different jobs

Enable permits execution at a clock edge. Reset returns the CPU to its initial state. HALT is an instruction that latches a stopped state inside the CPU. These controls have different meanings even though each can temporarily prevent the program counter from advancing.

The test pauses immediately after LOAD 3. At that point address is 1, accumulator is 3 and the memory presents instruction 31. Setting enable to zero leaves these values unchanged through the next rising edge. Restoring enable allows execution to continue at the next edge.

## Follow the halt checks

1. Locate the final trace entry. The halt instruction leaves address at 4 and accumulator at zero.
2. Read the following edge call. It deliberately adds another clock edge after the program has stopped.
3. The assertion requires halted to remain one and fault to remain zero.
4. The test then asserts reset while enable is zero.
5. Reset must clear halted, fault and the registers despite execution being disabled.

This order verifies the CPU's control priority. A halted machine must still be recoverable through reset. A disabled machine must still respond to reset. The implementation expresses that priority by checking reset before the enabled-execution branch.

## Restart is observable behaviour

After reset, the test keeps enable low for another edge and checks that the initial state is stable. It then enables execution and expects LOAD 3 to run again. Checking only cleared registers would miss a defect where the machine resets but can never resume.

In larger systems, reset may have timing requirements and may cross clock domains. This synchronous teaching design examines reset at a rising edge. A physical reset switch needs additional electrical and timing design; a simulation input is not a complete board-level reset circuit.

## Exercise

Make a table with four rows: paused, running, halted and reset. For each row, predict whether the next clock can change address or accumulator. Then explain why merely changing enable cannot resume a halted program. The stopped flag is stored inside the CPU and is cleared by reset, not by enable.

## Read the source

[Open the example source](../../../../labs/hardware/vhdl-cpu/tests/tb_learning_system.vhd).

## Continue learning

[Course contents](../../../courses/learning-hdl-vhdl/index.html) · [Previous: Check a program trace](46-check-a-program-trace.md) · [Next: Handle unresolved addresses](48-handle-unresolved-addresses.md)
