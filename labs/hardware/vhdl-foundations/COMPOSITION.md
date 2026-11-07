# Connect a pulse detector to a counter

A component is a circuit with named inputs and outputs. Composition connects those ports without copying either component's implementation. Here, sampled_pulse detects a sampled low-to-high change. lesson_counter counts the resulting pulse. pulse_counter joins them.

Both components use the same clock. This lab accepts a signal already synchronous to that clock. A physical button needs a separately designed synchronizer and debounce policy; connecting one directly does not establish reliable hardware behavior.

## Set up and simulate

Install GHDL with VHDL-2008 support. Open PowerShell or Bash in this laboratory directory. These commands are identical in either terminal:

```text
ghdl -a --std=08 sampled_pulse.vhd lesson_counter.vhd pulse_counter.vhd tb_pulse_counter.vhd
ghdl -e --std=08 tb_pulse_counter
ghdl -r --std=08 tb_pulse_counter --assert-level=error --wave=pulse-counter.ghw
```

Analysis reads the declarations. Elaboration resolves the component instances. Running advances simulated time. The expected successful outcome is the report "Pulse counter checks passed" and normal termination. These are instructions and expected results, not evidence of execution.

## Trace the register boundary

After reset, use inputs 1, 1, 0, 1, 0. Inspect values just after each edge:

| Edge | Input | Detected pulse | Count |
| --- | --- | --- | --- |
| 1 | 1 | 1 | 0 |
| 2 | 1 | 0 | 1 |
| 3 | 0 | 0 | 1 |
| 4 | 1 | 1 | 1 |
| 5 | 0 | 0 | 2 |

At edge 1 the detector schedules a new pulse. The counter reads the old pulse at that edge. It therefore increments at edge 2. This one-edge latency follows from the two registers; changing the order of the instance declarations does not change it.

## Reset and capacity

The test uses a two-bit counter, whose largest value is binary 11, decimal 3. Further events retain 3. A reset edge clears both the counter and detector. It also discards a pending pulse. With input still high after reset is released, the detector observes a new rise from its reset state. The test explicitly checks this contract.

## Investigate a failing assertion

Keep the first failing edge, input, reset, pulse and count together. An expected count that is one edge early often indicates a misunderstanding of the register boundary. An unknown count before any reset edge is an initialization problem. A count that returns to zero at capacity violates saturation.

To extend the lab, change width to 3 and update the test to reach 7. Keep the latency and reset assertions as well as the new capacity cases. A larger width changes the range, not the sequencing contract.

