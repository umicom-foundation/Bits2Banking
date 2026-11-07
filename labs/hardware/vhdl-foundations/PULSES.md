# From a sampled level to a pulse

The existing counter increments on every enabled clock edge. A button held high for ten clock edges would therefore count ten times. `sampled_pulse.vhd` remembers the previous sampled level and outputs a one-cycle pulse for a low-to-high change.

This component expects an input already synchronous to its clock. It does not synchronize an external pin, remove mechanical bounce or prove electrical timing. A real board needs those boundaries designed and reviewed separately.

## Simulate

Install GHDL with VHDL-2008 support. From this directory use:

~~~text
ghdl -a --std=08 sampled_pulse.vhd tb_sampled_pulse.vhd
ghdl -e --std=08 tb_sampled_pulse
ghdl -r --std=08 tb_sampled_pulse --assert-level=error --wave=pulse.ghw
~~~

Expected final note: `Sampled pulse checks passed`. These commands are supplied for execution; no simulation result is claimed here. The process waits one nanosecond after each edge so signal assignments have settled before assertions.

## Trace first

For input samples 0, 1, 1, 0, 1 after reset, predict output pulses 0, 1, 0, 0, 1. Signal assignments in the clocked process schedule updates; assigning `previous` does not make the new value available to the preceding expression during that same process activation.

Reset sets history to zero. Consequently, an input still high on the first edge after reset generates a pulse. That is an explicit design choice tested by the bench. A different requirement, such as requiring a release after reset, needs a different state machine and cases.

## Extend the experiment

Connect `pulse` to the enable input of `lesson_counter` in a separate top-level entity. Both processes run at the same clock edge, so the counter observes the prior pulse value. Predict this one-edge delay before simulation. Never use a combinational pulse as a new clock merely to remove that delay.

