<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/01-signals-bits-and-circuits.md

PURPOSE:
Explain the lesson: Describe a circuit with signals.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Describe a circuit with signals

## Before you begin
You need a text editor and paper. No circuit board is required. A bit is a value with two possible binary states, written 0 and 1. In a physical circuit those values are represented by electrical ranges; in this lesson they are symbols that we can trace.

## What an HDL describes
HDL means hardware description language. VHDL is one such language. A signal names a connection. An input enters a component; an output leaves it. Several connections can respond to changes without waiting for a C-style loop to visit each one. A simulator calculates those responses.

Our first component chooses one of two input bits:
~~~text
A -----------+
             | selector ---- result
B -----------+
                 |
              choose_b
~~~
When choose_b is 0, result follows A. When it is 1, result follows B. This sentence is the specification: the promise our implementation must keep.

## Read the source
Open `labs/hardware/vhdl-foundations/select_bit.vhd` in your Bits2Banking checkout. The entity declares the component's ports. The architecture describes its behaviour. The names a and b are arbitrary; their direction and type give them meaning.

`std_logic` can also represent simulation states such as unknown X. An uninitialized or conflicting signal is useful evidence. It must not silently become a known binary value in our reasoning.

## Paper lab
1. Draw the selector and label all four connections.
2. Set A to 0 and B to 1.
3. Predict result with choose_b set to 0, then 1.
4. Change both A and B to 1. Predict both results again.
5. Explain why the selector does not need to remember its previous output.

Expected results are 0, 1, 1 and 1. This component is combinational: its current output is determined by its current inputs.

## Connect to Umicom
A processor chooses among inputs throughout its data path. In Umicom Kernel, software chooses operations and handles results; a circuit designer specifies hardware that carries out those operations. This course builds small components before attempting a processor.

## Check your understanding
Does a selector add A and B? No: it chooses one. If your drawing has no control connection, it cannot describe which input should be selected. Add that connection before writing code.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/select_bit.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](02-first-simulation.md)

