<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/10-check-reset-hold-and-saturation.md

PURPOSE:
Explain the lesson: Check reset priority, holds and saturation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check reset priority, holds and saturation

## Test transitions, not only final values

A sequential circuit's result depends on its previous state and the sequence of clocked inputs. A useful test therefore checks transitions: reset to zero, enabled increments, disabled holds and behaviour at capacity.

The counter testbench instantiates two widths and drives the same control signals. Assertions compare each observation with a stated promise.

## Setup recap

Follow the [counter simulation guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/COUNTERS.md). Install GHDL and select VHDL-2008. Keep the design and testbench in the same practice directory. The commands analyze source, elaborate the testbench and run assertions.

## Understand the observation time

The testbench waits for a rising edge, then waits one nanosecond before checking outputs. This gives scheduled signal updates time to become visible. The extra interval is a testbench observation choice, not a required delay in the circuit.

~~~text
clock edge -> clocked process schedules count
                         |
                  signal update settles
                         |
                 test reads the outputs
~~~

Reading too early can compare the old value and produce a misleading failure.

## Lab

1. Run the original checks and read the report.
2. Find the case where reset and enable are both asserted.
3. Confirm that reset wins.
4. Find the interval between asserting reset and the next edge. The previous count must remain visible during that interval.
5. Find disabled holds at zero and one.
6. In a practice copy, replace the saturation guard with unconditional enabled increment. Expect the full-count check to fail, then restore the guard.

Save the failing assertion and waveform when making this deliberate experiment.

## Why two widths?

A design that accidentally assumes four bits might work with its default generic but fail with one bit. Instantiating widths one and three checks that the implementation follows its declared width. It does not prove every possible generic value.

## Exercise and explanation

Does reaching the stop-time without an error prove the test completed? No. A test could stop waiting before reaching its checks. Look for the explicit success report and the expected stop, as well as the process status.

## Extend the evidence

For a physical board, review synthesis reports, timing constraints, reset behaviour and electrical connections separately. A passing simulator does not establish the board pin mapping or the clock frequency. Keep those results attached to their actual hardware and source revision.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/tb_lesson_counter.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-count-clock-edges-with-a-generic.md)


[Next lesson: Detect a sampled rising edge](11-detect-a-sampled-rising-edge.md)
