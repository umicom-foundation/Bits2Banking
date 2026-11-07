<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/15-combine-bits-with-xor.md

PURPOSE:
Explain the lesson: Combine bits with XOR.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Combine bits with XOR

XOR compares two bits and produces one when they differ. Repeating XOR across a word can tell us whether it contains an odd number of one bits.

## Prepare

Open word_parity.vhd. The input word_in has eight positions, numbered seven down to zero. The output odd is a single std_logic signal.

The lab's PARITY-AND-TIMING.md explains how to install the required simulator and run this example. You can complete the first trace on paper.

## Follow the temporary value

Inside process(all), folded begins at zero. The loop visits every position in word_in'range. Each bit is combined with folded using XOR.

For input 00000101, the two one bits toggle the temporary value twice. It returns to zero, indicating even parity.

The process assigns folded to odd after the loop.

## Distinguish variables and signals

folded is a process variable. Its assignment uses := and the next loop iteration sees the updated value immediately.

odd is a signal. Its assignment uses <= and schedules an update. This difference explains why the loop can accumulate a result in a variable before publishing one signal value.

## Exercise

Trace 00000111, writing folded after each bit. Expect one because there are three one bits.

Then change the input on paper to all zeroes. The initial assignment to folded is essential: it makes each evaluation start independently instead of retaining the previous computation.

## Relate to software

The RISC-V sequences lab computes the same parity property with a loop over register bits. Both examples help explain the operation, but synthesis determines the hardware structure produced from this VHDL.

Parity is a small integrity check. It does not authenticate a message or locate an error.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/word_parity.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](14-reset-a-pending-event.md) · [Next lesson](16-enumerate-all-byte-inputs.md)

