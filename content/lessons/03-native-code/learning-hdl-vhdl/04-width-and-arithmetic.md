<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/04-width-and-arithmetic.md

PURPOSE:
Explain the lesson: Keep the carry when adding binary values.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep the carry when adding binary values

## Before you begin
A binary digit is a bit. Four bits are sometimes called a nibble. They represent unsigned values from 0 to 15. Install GHDL for the executable lab, or trace the calculations on paper.

## Count the required bits
The largest sum of two four-bit unsigned values is 15 + 15 = 30. Four bits cannot represent 30; five bits can.
~~~text
  01111   15
+ 01111   15
-------
  11110   30
~~~
The extra bit is part of the result. Assigning a narrow calculation to a wide destination is too late if the calculation already lost information.

## Read the implementation
~~~vhdl
total <= resize(a, total'length) + resize(b, total'length);
~~~
`numeric_std` supplies unsigned arithmetic. `resize` extends each operand before addition. `total'length` asks for the output width, here five. The apostrophe introduces an attribute; it is not a text quotation.

## Run the exhaustive check
From `labs/hardware/vhdl-foundations`:
~~~text
ghdl -a --std=08 add_nibble.vhd add_nibble_tb.vhd
ghdl -e --std=08 add_nibble_tb
ghdl -r --std=08 add_nibble_tb --assert-level=error
~~~
The bench checks 16 × 16 input pairs. It compares the circuit result with integer addition. Expected final output includes `adder checks passed`.

## Lab
1. Calculate 0 + 0, 7 + 8, 8 + 8 and 15 + 15.
2. Convert each result to five bits.
3. Find `to_unsigned` and `to_integer` in the bench and explain their directions.
4. In a practice copy, reduce the result width and observe the failure.
5. Restore the design and rerun.

## Connect to C and Framework
Integer widths matter at software boundaries too. The activity adapter checks negative C inputs before converting them to unsigned values. Both examples establish the valid range before performing an operation; they do not rely on an output variable to repair an earlier mistake.

## Troubleshooting
A type error between `std_logic_vector` and `unsigned` is a request to make interpretation explicit. Use the appropriate conversion rather than adding unrelated arithmetic packages until the error disappears.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/add_nibble.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-truth-tables-and-selection.md) · [Next lesson](05-clocked-storage.md)

