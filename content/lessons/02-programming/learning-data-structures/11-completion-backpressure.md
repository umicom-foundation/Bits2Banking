<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/11-completion-backpressure.md

PURPOSE:
Explain the lesson: Stop work when its completion cannot be delivered.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Stop work when its completion cannot be delivered

## Prepare
Use the work-dispatch README to configure the standalone host lab. Open TestCapacity in test_dispatch.c. Backpressure is a downstream stage telling an upstream stage to wait because it cannot accept more results.

## Fill the pipeline
Submit eight requests. There is enough work capacity to accept them all. Run with a budget of eight.

Only four requests execute because the completion queue holds four notices. The other four remain queued. This is intentional: producing a result with nowhere to record its completion could lose the result or leave ownership ambiguous.

Run reports OK and writes four to outRun because some progress occurred. A following Step returns BACKPRESSURE.

## Resume deliberately
Receive one receipt. This frees one completion slot and releases the corresponding work slot. Step may now execute one queued request. The completion queue becomes full again.

Track both capacities:
| Event | Queued work | Pending notices |
|---|---:|---:|
| Submit eight | 8 | 0 |
| Run budget eight | 4 | 4 |
| Receive one | 4 | 3 |
| Step once | 3 | 4 |

## Exercise
Continue the table until every request is delivered. Count total successful Steps and Receives. Both should equal eight.

## Diagnose a stall
When Run stops early, inspect the returned count and queue state before increasing its budget. A larger budget cannot create downstream capacity. The consumer must drain receipts. In a graphical application this reasoning also helps prevent a worker from flooding a UI event queue, although this lab uses synchronous calls and creates no threads.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/work-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-compose-a-work-pipeline.md) · [Next lesson](12-cancellation-is-a-result.md)

