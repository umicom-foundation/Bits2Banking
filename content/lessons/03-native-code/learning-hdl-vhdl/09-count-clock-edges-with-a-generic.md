<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/09-count-clock-edges-with-a-generic.md

PURPOSE:
Explain the lesson: Count clock edges with a configurable width.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Count clock edges with a configurable width

## A counter stores a number

A counter is a circuit that changes a stored value according to a clock and control inputs. This exercise counts enabled rising clock edges. It stops at its largest representable value instead of wrapping to zero.

A generic configures an entity when it is instantiated. The width generic selects how many bits store the count. One bit represents zero or one; three bits represent zero through seven.

## Setup recap

Install GHDL with VHDL-2008 support and check `ghdl --version`. Copy the two files named in the [counter lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/COUNTERS.md) into a practice directory. Its commands work in PowerShell and bash. This is a simulation exercise and requires no physical board.

## Read the interface

The inputs are clk, reset and enable. The outputs are count and full. The count type is unsigned from ieee.numeric_std, allowing arithmetic with an explicit bit width.

Inside the clocked process:

1. A rising edge starts the decision.
2. Asserted reset sets every count bit to zero.
3. Otherwise, asserted enable increments a count that is not full.
4. Every other case retains the stored value.

Reset is synchronous: it takes effect at the next active edge. Changing reset between edges does not immediately clear count.

## Lab

1. Analyze, elaborate and run the supplied simulation.
2. Find the three-bit and one-bit instances in the testbench.
3. Predict both counts after the first enabled edge.
4. Predict both counts after the second enabled edge.
5. Find the check after the three-bit count reaches seven.
6. Inspect counter.vcd with a waveform viewer and compare the count changes with clock edges.

The one-bit instance remains at one while the wider instance continues counting. They share a design, not stored state.

## Exercise and explanation

Why is saturation useful for a capacity indicator? Wrapping a full count to zero could make a full resource appear empty. Whether saturation is the correct policy depends on the circuit's contract; some counters intentionally wrap.

## Boundaries

The initial count is not usable until reset establishes it. A physical implementation also needs timing constraints and a plan for signals arriving from another clock domain. This lesson does not turn an unsynchronised physical switch into a safe clocked input.

A count is not a queue. A queue must store data and maintain ordering as well as track occupancy.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/lesson_counter.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-from-model-to-hardware.md) · [Next lesson](10-check-reset-hold-and-saturation.md)

