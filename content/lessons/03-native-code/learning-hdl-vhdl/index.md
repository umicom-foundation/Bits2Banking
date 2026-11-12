# Learning HDL and VHDL

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## Signals and combinational circuits

Describe bits, select a value and preserve a carry before adding clocked state.

1. [Describe a circuit with signals](01-signals-bits-and-circuits.md)
1. [Run a self-checking VHDL simulation](02-first-simulation.md)
1. [Turn a truth table into a selector](03-truth-tables-and-selection.md)
1. [Keep the carry when adding binary values](04-width-and-arithmetic.md)

## Clocked storage and observation

Use a clock, ready/valid transfers, assertions and waveforms to explain one small circuit.

1. [Store a value at a clock edge](05-clocked-storage.md)
1. [Move a word with ready and valid signals](06-ready-valid-transfers.md)
1. [Use assertions and waveforms to locate a circuit error](07-waveforms-and-debugging.md)
1. [Plan the next step from simulation to hardware](08-from-model-to-hardware.md)

## Counters and sampled events

Connect a configurable counter to a sampled edge detector, then account for reset and latency.

1. [Count clock edges with a configurable width](09-count-clock-edges-with-a-generic.md)
1. [Check reset priority, holds and saturation](10-check-reset-hold-and-saturation.md)
1. [Detect a sampled rising edge](11-detect-a-sampled-rising-edge.md)
1. [Connect circuits with named ports](12-connect-circuits-with-named-ports.md)
1. [Explain one clock of latency](13-explain-one-clock-of-latency.md)
1. [Reset a pending event](14-reset-a-pending-event.md)

## A complete request and response

Use parity to study accepted work, busy time, completion pulses and reset.

1. [Combine bits with XOR](15-combine-bits-with-xor.md)
1. [Enumerate all byte inputs](16-enumerate-all-byte-inputs.md)
1. [Keep unknown signals visible](17-keep-unknown-signals-visible.md)
1. [Count latency from request acceptance](18-count-latency-from-acceptance.md)
1. [Specify what happens to a request while busy](19-specify-busy-time-request-policy.md)
1. [Cancel pending work with reset](20-cancel-work-with-reset.md)
1. [Distinguish a pulse from a level](21-distinguish-a-pulse-from-a-level.md)
1. [Read waveforms as evidence](22-read-waveforms-as-evidence.md)

## Project: a buffered pipeline

Compose two existing buffers and check ordering, backpressure, bounded progress and reset.

1. [Compose existing circuits into a pipeline](23-compose-a-buffered-pipeline.md)
1. [Decide exactly when a transfer happens](24-read-a-transfer-at-the-clock-edge.md)
1. [Follow backpressure through two stages](25-capacity-and-backpressure.md)
1. [Measure latency and throughput separately](26-latency-and-throughput.md)
1. [Check every delivered word with a scoreboard](27-build-an-independent-scoreboard.md)
1. [Make a stalled simulation finish with evidence](28-bound-a-simulation.md)
1. [Reset every stage of a composed system](29-reset-a-composed-system.md)
1. [Review a circuit before moving to a device](30-review-a-hardware-boundary.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

# Learning HDL and VHDL

Describe small digital circuits, simulate their behaviour, and check the results before considering a physical board.

## Start here

Reading and paper exercises need no installation. Simulation labs use GHDL with VHDL-2008 support. Each chapter repeats its required commands.

## Lesson sequence

1. [Describe a circuit with signals](01-signals-bits-and-circuits.md)
1. [Run a self-checking VHDL simulation](02-first-simulation.md)
1. [Turn a truth table into a selector](03-truth-tables-and-selection.md)
1. [Keep the carry when adding binary values](04-width-and-arithmetic.md)
1. [Store a value at a clock edge](05-clocked-storage.md)
1. [Move a word with ready and valid signals](06-ready-valid-transfers.md)
1. [Use assertions and waveforms to locate a circuit error](07-waveforms-and-debugging.md)
1. [Plan the next step from simulation to hardware](08-from-model-to-hardware.md)
9. [Count clock edges with a configurable width](09-count-clock-edges-with-a-generic.md)
10. [Check reset priority, holds and saturation](10-check-reset-hold-and-saturation.md)
- [Detect a sampled rising edge](11-detect-a-sampled-rising-edge.md)
- [Connect circuits with named ports](12-connect-circuits-with-named-ports.md)
- [Explain one clock of latency](13-explain-one-clock-of-latency.md)
- [Reset a pending event](14-reset-a-pending-event.md)

## Continue learning

[Learning C](../../learning-c/index.md) introduces functions, values and checks. [Learning Umicom Framework](../../umicom-development/index.md) connects those ideas to shared application services. Each example is a bounded teaching project; the source does not establish device or production qualification.


- [Combine bits with XOR](15-combine-bits-with-xor.md)

- [Enumerate all byte inputs](16-enumerate-all-byte-inputs.md)

- [Keep unknown signals visible](17-keep-unknown-signals-visible.md)

- [Count latency from request acceptance](18-count-latency-from-acceptance.md)

- [Specify what happens to a request while busy](19-specify-busy-time-request-policy.md)

- [Cancel pending work with reset](20-cancel-work-with-reset.md)

- [Distinguish a pulse from a level](21-distinguish-a-pulse-from-a-level.md)

- [Read waveforms as evidence](22-read-waveforms-as-evidence.md)

- [Compose existing circuits into a pipeline](23-compose-a-buffered-pipeline.md)

- [Decide exactly when a transfer happens](24-read-a-transfer-at-the-clock-edge.md)

- [Follow backpressure through two stages](25-capacity-and-backpressure.md)

- [Measure latency and throughput separately](26-latency-and-throughput.md)

- [Check every delivered word with a scoreboard](27-build-an-independent-scoreboard.md)

- [Make a stalled simulation finish with evidence](28-bound-a-simulation.md)

- [Reset every stage of a composed system](29-reset-a-composed-system.md)

- [Review a circuit before moving to a device](30-review-a-hardware-boundary.md)

</details>


## Project: an instruction-driven CPU

Create the Framework VHDL project, trace its instruction set and qualify its simulation.

1. [Create a CPU simulation project in Studio](31-create-a-cpu-project.md)
1. [Read the inputs, outputs and stored state](32-read-ports-and-state.md)
1. [Decode operation codes and operands](33-decode-an-instruction.md)
1. [Explain wraparound in fixed-width arithmetic](34-check-fixed-width-arithmetic.md)
1. [Follow jumps and conditional branches](35-follow-branches.md)
1. [Control pause, halt and reset](36-control-pause-halt-reset.md)
1. [Make invalid instructions visible](37-stop-on-invalid-operations.md)
1. [Drive a clocked circuit from a testbench](38-write-a-clocked-testbench.md)
1. [Choose expected results independently](39-build-an-independent-cpu-oracle.md)
1. [Distinguish successful completion from a timeout](40-bound-a-cpu-simulation.md)
1. [Understand the analysis and simulation build graph](41-understand-the-vhdl-build-graph.md)
1. [Review CPU evidence and plan the next extension](42-review-cpu-evidence-and-next-steps.md)


## Project: a CPU with program memory

Connect read-only instruction memory, follow a countdown program and inspect bounded simulation evidence without changing the CPU instruction engine.

1. [Store an instruction program](43-store-an-instruction-program.md)
1. [Encode a countdown program](44-encode-a-countdown-program.md)
1. [Connect CPU and memory](45-connect-cpu-and-memory.md)
1. [Check a program trace](46-check-a-program-trace.md)
1. [Pause, halt and restart a program](47-pause-halt-and-restart-a-program.md)
1. [Handle unresolved addresses](48-handle-unresolved-addresses.md)
1. [Build separate simulation libraries](49-build-separate-simulation-libraries.md)
1. [Investigate a program failure](50-investigate-a-program-failure.md)
