<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/17-keep-unknown-signals-visible.md

PURPOSE:
Explain the lesson: Keep unknown signals visible.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep unknown signals visible

Simulation can represent a signal whose value is not known. This helps expose missing initialization, conflicting drivers or incomplete assumptions.

## Prepare

Read the final stimulus in tb_word_parity.vhd. It assigns 0000000X to word_in and expects odd to become X.

X is a std_logic value used to represent an unknown result. It is not a third stable voltage that this lesson asks you to generate on a board.

## Trace uncertainty

The seven known zero bits do not affect parity. The remaining bit could be zero or one, so the parity cannot be determined.

XOR preserves that uncertainty. Replacing unknown inputs with zero would produce a confident answer without sufficient information.

## Exercise

Write the two possible binary replacements for X. Compute their parity separately. Since the answers differ, a single known output is unjustified.

Now consider two unknown bits. Do not assume they are equal merely because both are displayed as X; each represents missing knowledge.

## Use the diagnostic

If a waveform shows X unexpectedly, inspect initialization, reset, driver ownership and input timing. Find the earliest unknown rather than only the final incorrect output.

For a clocked circuit, verify that the intended reset edge actually occurred before observations began.

## Connect to application debugging

An absent field, uninitialized variable or unknown network outcome should also remain distinguishable from a valid zero or a successful operation. The representation differs, but the reasoning principle is similar.

The test's X check is a simulation expectation. Physical-device qualification still requires electrical and timing analysis; an X-free simulation is not proof of a reliable board.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/tb_word_parity.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](16-enumerate-all-byte-inputs.md) · [Next lesson](18-count-latency-from-acceptance.md)

