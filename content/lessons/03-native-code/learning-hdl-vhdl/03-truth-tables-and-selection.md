<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/03-truth-tables-and-selection.md

PURPOSE:
Explain the lesson: Turn a truth table into a selector.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Turn a truth table into a selector

## Setup recap
Open the VHDL foundations lab in an editor. For simulation install GHDL and use the three selector commands from the previous chapter. You can complete the table exercise with paper only.

## Enumerate the possibilities
A truth table lists every allowed input combination and its expected output. Three binary inputs have eight combinations because 2 × 2 × 2 = 8.
~~~text
A B choose_b | result
0 0    0    |   0
0 0    1    |   0
0 1    0    |   0
0 1    1    |   1
1 0    0    |   1
1 0    1    |   0
1 1    0    |   1
1 1    1    |   1
~~~
The output column is derived from the specification, not copied from the implementation.

## Read the complete assignment
~~~vhdl
with choose_b select
    result_bit <= a when '0',
                  b when '1',
                  'X' when others;
~~~
`<=` schedules a signal assignment. The alternatives cover every control value. The final alternative makes an unknown selection visible in simulation.

## Follow the bench
Open `select_bit_tb.vhd`. Two loops choose A and B. Inside the loops the bench checks both selection values. The `wait for 1 ns` gives the scheduled changes time to propagate before observation. The design itself has no delay expression; the wait belongs to the testbench.

## Practical task
1. Add a column to your paper table stating which input is selected.
2. Locate the corresponding assertion for each row.
3. Run the selector bench.
4. Save the tool version, command and result in your practice notebook.
5. Write a ninth case for choose_b = X and explain why it is outside the binary truth table.

## A useful design habit
Give every combinational output a defined assignment for every intended input path. In a process, an omitted assignment can imply storage. Storage is appropriate for a register, but accidental storage changes the circuit.

## Review
If A changes while choose_b selects B, result should continue to follow B. This independence is a useful additional check. Think of it when testing Umicom interfaces: changing an unrelated field should not unexpectedly change the selected result.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/select_bit.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](02-first-simulation.md) · [Next lesson](04-width-and-arithmetic.md)

