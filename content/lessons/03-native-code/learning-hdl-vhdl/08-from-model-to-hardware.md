<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/08-from-model-to-hardware.md

PURPOSE:
Explain the lesson: Plan the next step from simulation to hardware.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Plan the next step from simulation to hardware

## Before you begin
This chapter is a planning lab. You need the four supplied VHDL designs and their test results if you ran them. No board purchase or programming operation is required.

## Separate the stages
~~~text
specification -> source -> simulation -> synthesis -> implementation -> board checks
~~~
Simulation checks a model's behaviour. Synthesis converts an eligible description into a hardware structure. Implementation maps that structure to a chosen device and checks placement and timing. A physical board adds electrical connections and real clocks.

The testbench's `wait for 5 ns` is a simulation instruction. It is not an instruction to manufacture a clock on a board.

## Create a board plan
For a board you already have, record:
1. The exact device and board revision.
2. The supported toolchain and language features.
3. Clock frequency and which pin carries that clock.
4. Reset polarity and whether it is synchronized.
5. LED and button pin names, voltage requirements and active levels.
6. The board-specific constraints file and programming procedure.
7. How you will confirm the design is running before connecting external hardware.

Obtain these from that board's official documentation. An unverified pin number is not a useful exercise shortcut.

## Project exercise
Plan a button-controlled progress indicator. Reuse the register's enable/reset concepts. Write a specification for switch debounce before writing its circuit. A single press should cause one update even when an electrical contact bounces.

Compare the plan with Bits2Banking's `labs/native/activity-adapters/button.c`. That C example detects edges in already sampled logical input. It deliberately does not claim to debounce a physical switch.

## Connect the courses
Continue Introduction to RISC-V to study the processor interface used by Umicom Kernel. Then study RISC-V Assembly to trace software instructions. Designing a RISC-V processor is a later project requiring instruction decoding, memory, exceptions and a much larger verification plan.

## Review
A passing simulator run does not establish pin safety, clock timing or complete processor compatibility. Write down which claim each piece of evidence actually supports. That makes the next engineering step clear.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/lesson_register.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-waveforms-and-debugging.md)

[Continue: Count clock edges with a configurable width](09-count-clock-edges-with-a-generic.md)
