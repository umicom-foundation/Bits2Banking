# Connect two buffered stages

A pipeline passes work through several stages. This exercise composes two copies of `lesson_buffer`; each stores one byte. The new design does not reproduce the buffer's storage logic.

## Prepare

Install GHDL with VHDL-2008 support. Open PowerShell or Bash in this directory. A simulator evaluates the circuit in modelled time. It does not program a physical board.

Run each command separately and stop on errors:

```text
ghdl -a --std=08 lesson_buffer.vhd buffer_pipeline.vhd buffer_pipeline_tb.vhd buffer_pipeline_reset_tb.vhd
ghdl -e --std=08 buffer_pipeline_tb
ghdl -r --std=08 buffer_pipeline_tb --assert-level=error --vcd=pipeline.vcd
ghdl -e --std=08 buffer_pipeline_reset_tb
ghdl -r --std=08 buffer_pipeline_reset_tb --assert-level=error
```

Expected: the scoreboard bench reports that its checks passed after 64 accepted words arrive in order; the reset bench reports that both stages were cleared. These are expected outcomes, not a record of an executed run.

## Draw the connections

```text
producer --word,valid--> first --word,valid--> second --word,valid--> consumer
producer <--ready------ first <--ready------ second <--ready------ consumer
```

A transfer occurs at a rising edge when both ready and valid are one. The producer retains a pending word until that edge. A consumer's readiness describes capacity, not whether a word exists.

With no stalls, a word first enters stage one and reaches stage two at the next edge. Once filled, the pipeline can accept and deliver one word per edge. Latency and throughput are different measurements.

## Compare with software

The native work-dispatch lab also separates admission, stored work and completion. Its queue uses ordinary C operations rather than clocked hardware. Compare ownership and capacity rules without assuming their timing models are identical.

## Recovery

An assertion gives the first violated condition. Inspect the named signal in the waveform around that edge. If elaboration cannot find `lesson_buffer`, analyse it first using the same standard and working directory. Synthesis, clock constraints and board pin assignment remain separate work.
