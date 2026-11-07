<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/11-detect-a-sampled-rising-edge.md

PURPOSE:
Explain the lesson: Detect a sampled rising edge.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Detect a sampled rising edge

A counter should sometimes count an event once even when an input stays high for several clock cycles. A rising edge means that the sampled value changed from 0 to 1. We can remember the previous sample and compare it with the next one.

## Setup recap

Open labs/hardware/vhdl-foundations. You need a text editor and GHDL with VHDL-2008 support for simulation. The paper exercise needs neither a board nor a compiler.

## 1. Read the ports

The entity sampled_pulse receives clk, reset and sampled_input. Its output pulse is a single std_logic signal. The input is assumed to be synchronous: it already follows the timing requirements of this clock. A real pushbutton does not automatically meet that assumption.

## 2. Trace the expression

The expression is `sampled_input and not previous`. It produces 1 only when the current sample is 1 and the remembered sample is 0.

| Current | Previous | Pulse |
| --- | --- | --- |
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

Inside the clocked process, both right-hand values describe the state before the edge. Assigning previous does not immediately change the value used by the pulse assignment.

## 3. Run the directed checks

In PowerShell or Bash, from the laboratory directory:

```text
ghdl -a --std=08 sampled_pulse.vhd tb_sampled_pulse.vhd
ghdl -e --std=08 tb_sampled_pulse
ghdl -r --std=08 tb_sampled_pulse --assert-level=error --wave=pulses.ghw
```

Read the testbench before running it. It checks held-high input, a second rise, reset and an unknown sample. A successful run should terminate normally after its completion report.

## Exercise and explanation

Write samples 0, 1, 1, 0, 1 on paper. After a reset, the corresponding pulses are 0, 1, 0, 0, 1. The third sample is held high and is not a new rise.

If a physical button produces several pulses, that may be contact bounce. This circuit does not debounce a button or synchronize an asynchronous input. Those are separate requirements to establish before a board exercise.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/sampled_pulse.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-check-reset-hold-and-saturation.md) · [Next lesson](12-connect-circuits-with-named-ports.md)

