<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/02-first-simulation.md

PURPOSE:
Explain the lesson: Run a self-checking VHDL simulation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Run a self-checking VHDL simulation

## Prepare the tools
Install GHDL for your operating system and open PowerShell or Bash. Run `ghdl --version`. If the command is missing, add the installed tool directory to your terminal's PATH or open the terminal provided by its installation. You also need a text editor and the Bits2Banking checkout.

Move to the lab directory:
~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\hardware\vhdl-foundations"
~~~
On Bash, use `cd /path/to/Umicom-Bits2Banking/labs/hardware/vhdl-foundations`, substituting the actual checkout path.

## Three separate steps
~~~text
ghdl -a --std=08 select_bit.vhd select_bit_tb.vhd
ghdl -e --std=08 select_bit_tb
ghdl -r --std=08 select_bit_tb --assert-level=error
~~~
Run one command at a time and stop on failure. Analysis reads and checks source. Elaboration connects the selected design. Running advances the simulation. `--std=08` selects the same language version at every stage.

A testbench is a separate design that drives inputs and checks outputs. The supplied bench tests all eight binary combinations, then an unknown control. A correct run reports `selector checks passed` and terminates. This is the result you should look for in your own run.

## Read an assertion
~~~vhdl
assert result_bit = values(ai)
    report "A selection failed" severity failure;
~~~
The expression is a condition we expect to be true. If it is false, the simulator reports why the check failed. A passing run is stronger evidence than a screenshot of one output.

## Investigate deliberately
In a separate practice copy, exchange the A and B assignments in the selector. Analyse both files again and rerun the bench. It should fail. Restore your practice copy and repeat. A check that never detects this change is not checking selection properly.

## Recovery
If the simulator cannot find the entity, verify the current directory and run analysis before elaboration. If `std.env` is unavailable, check that all commands use VHDL-2008. Do not remove assertions to make the run finish.

## Extend the exercise
Write down the exact input combination from the first failure. Explain why equal A and B values cannot reveal a swapped selector. This is the same testing principle used when Umicom validates two branches that happen to return equal results for some inputs.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/select_bit_tb.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](01-signals-bits-and-circuits.md) · [Next lesson](03-truth-tables-and-selection.md)

