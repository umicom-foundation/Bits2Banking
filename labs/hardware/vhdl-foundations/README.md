# VHDL circuit laboratories

These original circuits accompany Learning HDL and VHDL. A hardware description specifies signals and their relationships; a testbench supplies inputs and checks results in simulated time.

## Prepare and run

Install GHDL and make `ghdl --version` available in PowerShell or Bash. From this directory:

~~~text
ghdl -a --std=08 select_bit.vhd select_bit_tb.vhd
ghdl -e --std=08 select_bit_tb
ghdl -r --std=08 select_bit_tb --assert-level=error
ghdl -a --std=08 add_nibble.vhd add_nibble_tb.vhd
ghdl -e --std=08 add_nibble_tb
ghdl -r --std=08 add_nibble_tb --assert-level=error
ghdl -a --std=08 lesson_register.vhd lesson_register_tb.vhd
ghdl -e --std=08 lesson_register_tb
ghdl -r --std=08 lesson_register_tb --assert-level=error
ghdl -a --std=08 lesson_buffer.vhd lesson_buffer_tb.vhd
ghdl -e --std=08 lesson_buffer_tb
ghdl -r --std=08 lesson_buffer_tb --assert-level=error
~~~

Run each command separately; stop on an error. `-a` analyses source, `-e` elaborates the selected design, and `-r` runs it. All stages use VHDL-2008. Each passing bench reports its checks passed and finishes. These are expected results to compare with your own run.

To inspect timing:

~~~text
ghdl -r --std=08 lesson_buffer_tb --assert-level=error --vcd=buffer.vcd
~~~

Open the trace in a waveform viewer. See [GHDL simulation and waveform guidance](https://ghdl.github.io/ghdl/quick_start/simulation/heartbeat/index.html). Testbench waits create simulated time; they are not an implementation of a physical oscillator.

## Source map and checks

- `select_bit`: chooses A or B; eight binary combinations and unknown selection.
- `add_nibble`: four-bit operands become a five-bit sum; all 256 pairs checked.
- `lesson_register`: synchronous reset, enabled capture and retained value.
- `lesson_buffer`: one stored word; ready/valid handshake, waiting, replacement, draining and reset.

Unknown control values are useful evidence in simulation. Do not hide them by assuming every signal starts at zero. The sequential designs require reset; the benches supply it.

## From simulation to a board

These examples have no FPGA part, pin constraints, clock constraint or board programmer configuration. They are not bitstreams. Before hardware use, choose a board and supported synthesis toolchain, identify its clock/reset/pin requirements, and perform timing and electrical checks. Never connect an arbitrary pin based only on this simulation.

