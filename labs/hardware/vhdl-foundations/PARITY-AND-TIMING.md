# Parity and request timing

These circuits extend the existing foundations lab. Read the VHDL course's signal and clock lessons first, or use the descriptions below as a recap.

A signal connects circuit behavior. A combinational circuit responds to its inputs without waiting for a clock. A clocked circuit changes stored state at selected clock edges.

## Prepare and simulate

Install GHDL with VHDL-2008 support. Open PowerShell or Bash in this directory. Run each command separately and stop on errors.

```text
ghdl -a --std=08 word_parity.vhd tb_word_parity.vhd
ghdl -e --std=08 tb_word_parity
ghdl -r --std=08 tb_word_parity --assert-level=error --vcd=parity.vcd
ghdl -a --std=08 request_timer.vhd tb_request_timer.vhd
ghdl -e --std=08 tb_request_timer
ghdl -r --std=08 tb_request_timer --assert-level=error --vcd=timer.vcd
```

Expected completion messages are word parity checks passed and request timer checks passed. A VCD file records signal changes for a waveform viewer. These simulations are authored and have not been executed for this delivery.

## Understand the contracts

word_parity produces one when the eight input bits contain an odd number of ones. An unknown X input propagates through XOR rather than silently becoming a binary answer.

request_timer accepts a one-clock start pulse while idle. After CYCLES subsequent rising edges it emits done for one clock and clears busy. Starts while busy are ignored; there is no hidden request queue. Reset cancels active work and suppresses completion.

The timer needs a reset edge before use. Inputs must already be synchronous to clk; this circuit does not synchronize a physical button.

## Inspect timing

For CYCLES = 3, acceptance occurs at edge A. Busy remains asserted after A + 1 and A + 2. Done is asserted after A + 3 and clears at the next edge. The test also pulses start while busy to detect accidental restart.

## Recover from a failure

Locate the first failing assertion. Inspect signals around that edge, including their values before the edge. The one-nanosecond wait in the test lets scheduled updates settle before observation; it is not hardware added to the design.

For a physical FPGA, clock constraints, pin assignments, reset circuitry and synthesis evidence are additional requirements. Simulation results alone do not qualify a board.

[GHDL documents simulation options and assertion handling](https://ghdl.github.io/ghdl/using/Simulation.html).
