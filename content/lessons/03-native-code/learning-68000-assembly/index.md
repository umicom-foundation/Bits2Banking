# Learning Motorola 68000 Assembly

Assembly language gives readable names to instructions a processor can carry out. In this introduction you will follow a calculation, read a memory diagram and trace a loop. A pencil and paper are enough for every exercise here.

Begin with [Introduction to Computers](../../../courses/computing-from-the-beginning/index.html) if files, programs or numbers stored in a computer are unfamiliar. The first lesson below introduces registers, bits and instruction notation before using them. You do not need to buy hardware or install an emulator.

## Read in this order

1. [Registers and a first calculation](01-registers-and-a-calculation.md): describe where a calculation keeps its values.
2. [Addresses and bytes in memory](02-addresses-and-memory.md): distinguish a location from the value stored there.
3. [Comparisons and a bounded loop](03-comparisons-and-loops.md): predict when repeated work stops.

These three lessons use the original MC68000 instruction set and GNU assembler notation. The examples are reading exercises, not complete boot programs. A future practical module will specify an assembler, an emulator, a memory map and a verified launch procedure together.

## Connect this subject to Umicom

The examples use the same arithmetic and loop ideas as the existing [Learning C](../../../courses/learning-c/index.html) laboratory. Follow the source links inside each lesson to compare a high-level instruction with smaller machine-level steps. The C examples are real Bits2Banking source files; the Assembly examples are teaching fragments and do not claim an existing Umicom Kernel 68000 port.

[Browser edition](../../../courses/learning-68000-assembly/index.html) · [All subjects](../../../start/course-series.md) · [Computer architecture](../../../courses/learning-computer-architecture/index.html)

Sammy Hegab · Umicom Foundation. Original teaching material: MIT. Linked processor documentation retains its own licence.

## Continue with a practical source study

You can understand a short 68000 routine by keeping a written record of each register. This lesson uses the idea of a bounded counter from the existing C repetition example, then expresses a small counter using 68000 instructions.

- [Draw registers before writing memory](04-draw-registers-before-writing-memory.md)
