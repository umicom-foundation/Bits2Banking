<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-hdl-vhdl/24-read-a-transfer-at-the-clock-edge.md

PURPOSE:
Explain the lesson: Decide exactly when a transfer happens.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Decide exactly when a transfer happens

## Prepare
Read the pipeline testbench beside PIPELINES.md. A clock edge is the instant at which the sequential circuits sample their inputs. Between edges, combinational outputs can settle without accepting a new byte.

The transfer rule is:
```text
accepted at this rising edge = valid is one AND ready is one
```
Neither signal alone is an acknowledgement.

## Work through a table
| Valid | Ready | Meaning at the edge |
|---|---|---|
| 0 | 0 | No word offered and no capacity advertised |
| 0 | 1 | Capacity exists, but nothing transfers |
| 1 | 0 | A word waits |
| 1 | 1 | One word transfers |

A waiting producer must keep the pending word and valid signal stable until acceptance. Our bench derives input_word from sent, and increments sent only after an accepting handshake.

## Lab
Temporarily sketch a consumer that keeps ready low for three edges. Write the producer's byte beneath each edge. All three entries must show the same byte. At the first accepting edge, the producer may advance to the next byte afterwards.

## Observe before and after
The testbench snapshots the handshake before the rising edge. After that edge, output_word may already describe the next stored byte. Comparing that new value with the old transfer would report a false failure.

## Troubleshoot
A mismatch that is always one word ahead often indicates that the test observes the wrong side of the edge. Check observation timing before modifying the circuit. The supplied bench waits for settling after changing inputs, then samples the handshake and finally advances the clock.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/hardware/vhdl-foundations/buffer_pipeline_tb.vhd). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](23-compose-a-buffered-pipeline.md) · [Next lesson](25-capacity-and-backpressure.md)

