# Trace a pipeline before simulating it

Use `buffer_pipeline.vhd` and the two supplied testbenches. Begin with reset asserted for one rising edge. This establishes empty storage; uninitialised signals are not usable data.

## Exercise 1: a stopped consumer

1. Keep output-ready zero.
2. Present byte 17 with input-valid one.
3. At the first accepting edge, replace the input byte with 34.
4. Wait for a second accepting edge.
5. Keep input-valid one and present byte 51.

Predict the state. The first two words occupy the pipeline. Input-ready becomes zero. Byte 51 remains the producer's responsibility until capacity is available.

## Exercise 2: simultaneous movement

Set output-ready to one while the pipeline is full. At the next rising edge, 17 can leave, 34 can move forward and 51 can enter. Draw the state immediately before and after the edge; do not treat the three movements as three separate clock ticks.

## Exercise 3: a scoreboard

A scoreboard is a reference list of inputs that were actually accepted. Add a word only when input-valid and input-ready are one at the edge. Remove the oldest word only on an output handshake.

The difference between accepted and delivered words must remain between zero and two. Equal final counts alone cannot detect reordering: compare each delivered value with the oldest expected value.

## Exercise 4: reset

Fill both stages, then assert reset before another edge. This implementation immediately suppresses advertised transfers, but clears stored state at the next rising edge. After reset, send 51 again and verify that neither earlier word returns.

## Explain your findings

Record the expected trace, actual trace and source revision. If a check fails, keep the failing waveform before changing the design. A successful simulation covers the supplied stimulus; it does not establish physical timing closure or electrical correctness.
