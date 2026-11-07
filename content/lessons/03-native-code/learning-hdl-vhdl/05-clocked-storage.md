<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/05-clocked-storage.md

PURPOSE:
Explain the lesson: Store a value at a clock edge.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Store a value at a clock edge

## Setup recap
Open `lesson_register.vhd` and its testbench in the VHDL foundations lab. Use GHDL with VHDL-2008 for simulation. A register is storage that holds a value; a clock supplies the events at which this example can change it.

## Describe the rule first
At a rising clock edge, reset clears the stored word. Otherwise, enable permits a new word to be captured. With neither condition active, the previous word remains.

~~~text
clock edge -> reset? yes -> store zero
                 |
                 no
                 v
              enabled? yes -> store input
                 |
                 no -> keep previous value
~~~

## Read the process
~~~vhdl
if rising_edge(clk) then
    if reset = '1' then
        stored_word <= (others => '0');
    elsif enable = '1' then
        stored_word <= input_word;
    end if;
end if;
~~~
The reset has priority because it is checked first. Here reset is synchronous: asserting it between edges does not immediately clear the register. This choice is part of the interface contract.

## Run and observe
~~~text
ghdl -a --std=08 lesson_register.vhd lesson_register_tb.vhd
ghdl -e --std=08 lesson_register_tb
ghdl -r --std=08 lesson_register_tb --assert-level=error --vcd=register.vcd
~~~
Expected checks cover reset priority, enabled capture, disabled retention and the timing of reset. Open the VCD file in a waveform viewer if available.

## Lab
1. Find the testbench's 5 ns half-period. Calculate the full period.
2. Predict the stored value after the first two rising edges.
3. Explain why the bench waits briefly after an edge before checking.
4. Change the input while enable is zero. Confirm that the output retains its value.
5. Add another retained-value observation in a practice copy.

## Connection to a processor
Registers let a processor keep intermediate values across operations. The RISC-V course studies the visible register interface used by software. This eight-bit teaching circuit is not a complete RISC-V register file.

## Recovery
Do not assume a stored output starts at zero before reset. If a waveform starts with U or X, first check whether the testbench has supplied the specified reset edge.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/lesson_register.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-width-and-arithmetic.md) · [Next lesson](06-ready-valid-transfers.md)

