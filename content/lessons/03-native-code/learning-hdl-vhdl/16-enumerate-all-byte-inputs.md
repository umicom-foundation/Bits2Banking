<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/16-enumerate-all-byte-inputs.md

PURPOSE:
Explain the lesson: Enumerate all byte inputs.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Enumerate all byte inputs

An eight-bit binary word has 256 possible values. This is small enough for a test bench to check every binary input.

## Prepare

Open tb_word_parity.vhd beside word_parity.vhd. The test bench creates input signals, connects the circuit and checks observations. It is simulation code, not the circuit intended for synthesis.

Use the commands in PARITY-AND-TIMING.md when ready to run.

## Read the input loop

The outer loop counts from zero through 255. to_unsigned converts the number into an eight-bit unsigned vector. std_logic_vector then gives it the signal type expected by the circuit.

The test computes an expected count of one bits using integer division and remainder. This differs from the circuit's XOR reduction, helping avoid a direct copy of the implementation.

## Observe after settling

After assigning word_in, the test waits one nanosecond. It then compares odd with the parity of the counted one bits.

The wait allows simulated signal updates to settle. It does not add a one-nanosecond delay component to the circuit.

## Exercise

Explain why checking only zero and 255 is insufficient: both have even parity. Add a short table showing one, two and three, whose expected outputs are one, one and zero.

The exhaustive loop already includes these values, but the table makes the expectation understandable.

## Interpret a result

A successful run checks all binary byte inputs for this model. It does not cover every std_logic value, physical timing or a synthesized board.

The test separately supplies an X input because binary enumeration cannot represent unknown simulation states. Keep these two coverage claims distinct in your notes.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/tb_word_parity.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](15-combine-bits-with-xor.md) · [Next lesson](17-keep-unknown-signals-visible.md)

