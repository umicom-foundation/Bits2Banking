# Clocked counters and bit width

This simulation adds a saturating counter to the digital-circuit exercises. A three-bit instance counts from zero to seven. A one-bit instance counts from zero to one. Both use the same entity with a different width generic.

## Prepare and run

Install GHDL with VHDL-2008 support. Check `ghdl --version`. In an empty practice directory copy lesson_counter.vhd and tb_lesson_counter.vhd, then run these commands in PowerShell or bash:

~~~text
ghdl -a --std=08 lesson_counter.vhd tb_lesson_counter.vhd
ghdl -e --std=08 tb_lesson_counter
ghdl -r --std=08 tb_lesson_counter --assert-level=error --stop-time=1us --vcd=counter.vcd
~~~

Expected result is the Counter checks passed report with no failing assertion. The stop-time is a guard against an accidentally unfinished simulation, not evidence that assertions ran. Inspect the report as well as the process status.

## What the checks establish

- An active clock edge with reset asserted initializes the count.
- Reset has priority when enable is also asserted.
- Enable increments until the largest representable value.
- A full count holds instead of wrapping to zero.
- A disabled count holds both zero and a nonzero value.
- Two widths follow the same contract independently.

The full output reflects the stored count. Synchronous reset does not clear it until the active edge. Inputs must obey the clock-domain and timing requirements of a physical implementation; this simulation does not solve switch bounce, metastability or electrical constraints.

Use the existing ready/valid buffer lab when exploring data transfer. A count alone is not a queue and contains no stored messages.

