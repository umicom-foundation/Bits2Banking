<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/21-distinguish-a-pulse-from-a-level.md

PURPOSE:
Explain the lesson: Distinguish a pulse from a level.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish a pulse from a level

A level describes a signal's current value. A pulse describes a temporary assertion over a limited interval. A receiver may react differently to each.

## Prepare

Read the start and done contracts in PARITY-AND-TIMING.md. The caller supplies a one-clock start pulse while idle. The timer produces a one-clock done pulse when work finishes.

Use a timing diagram with vertical marks for clock edges.

## Follow completion

On the completion edge, done becomes one. At the next edge the normal path first schedules done to zero. Unless another completion occurs, it stays zero.

The test checks this clearing behavior after the first request.

## Hold start high on paper

Imagine start stays one from acceptance through completion and beyond. While busy, it is ignored. At a later idle edge, the still-high start is accepted again.

The receiver cannot infer whether the caller intended one long press or another request.

## Exercise

Draw start held high for ten clock edges with CYCLES = 3. Mark every accepted request and completion. Then redraw using one-clock pulses only.

Compare the results before changing any code.

## Choose a protocol

For a single event, an edge detector may be appropriate. For data transfer, ready and valid signals can express acceptance. For work that must never be lost, buffering and backpressure may be required.

The earlier lesson_buffer circuit demonstrates a one-word ready/valid transfer. Reuse its documented contract when that behavior is needed rather than assuming the timer already queues work.

The lesson is about synchronous signals. A physical input additionally needs electrical, synchronization and debounce decisions.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/request_timer.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](20-cancel-work-with-reset.md) · [Next lesson](22-read-waveforms-as-evidence.md)

