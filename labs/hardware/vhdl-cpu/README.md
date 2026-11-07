# Learning CPU

This VHDL project models an eight-bit accumulator CPU. It is a teaching design with sixteen instruction addresses. It is not a processor implementing RISC-V and does not boot Umicom Kernel.

Install CMake, Ninja and GHDL, then open a terminal in this folder. Run each command separately and stop if it fails.

```text
cmake --preset simulation
cmake --build --preset simulation
ctest --preset simulation
cmake --build build/simulation --target simulate
```

In Studio, create this template, select its simulation configure/build/test preset, and use Configure, Build and Test. Simulation is a test/custom build target; the ordinary native Run command expects a native executable and is not the GHDL launcher.

If GHDL is installed outside PATH, configure with -DGHDL_EXECUTABLE= followed immediately by the complete executable path. Quote paths containing spaces. A missing compiler stops configuration. Build before testing after source edits. The test checks reset, load/add/subtract, branches, pause, wraparound, halt and an invalid opcode. A successful run prints CPU checks passed. A failed assertion exits unsuccessfully.

The instruction's high four bits select its operation and the low four bits contain an immediate value or address. Opcodes 0, 1, 2, 3, 4, 5 and F mean NOP, LOAD, ADD, SUBTRACT, JUMP, JUMP-IF-ZERO and HALT. Other opcodes latch a fault. Arithmetic wraps modulo 256; addresses wrap modulo 16. Reset clears the fault and halt state.

The simulate target records build/simulation/ghdl-work/cpu.ghw for a compatible waveform viewer. Simulation does not establish device timing, synthesis suitability or electrical correctness.

Read the Learning HDL and VHDL course in Bits2Banking to extend this model with a program memory and a trace.

## Execute a stored program

The project also contains a read-only program memory. Open rtl/learning_program.vhd:
address 0 loads 3; address 1 subtracts 1; address 2 jumps to address 4 when the
accumulator is zero; address 3 returns to address 1; address 4 halts. Unused
addresses contain the invalid instruction 60 (hexadecimal).

rtl/learning_system.vhd connects the CPU and memory. Its outputs expose the
current instruction, address and accumulator for inspection. The testbench
tests/tb_learning_system.vhd compares every enabled step against a written
expected trace. It also checks a pause, a stable halt and a reset while disabled.

After configuring and building with the commands above, run:

```text
ctest --preset simulation -R "^cpu[.]program$"
cmake --build build/simulation --target simulate_program
```

A passing simulation reports Stored program checks passed. The custom target
writes build/simulation/ghdl-program/program.ghw. The program and individual
instruction simulations use separate work libraries so their builds can run
concurrently. Change a ROM word, build again and examine a failed trace before
changing its expected values. A testbench expectation is a specification, not
a value to update merely to make a failure disappear.

This is a small simulated CPU, not a hardware installation image. It does not
provide an instruction set compatible with Umicom Kernel. Physical devices
need a separate synthesis, timing and board-integration workflow.
