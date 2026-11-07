# Request timer worksheet

Complete the remaining column before looking at the implementation.

| Edge | reset | start | remaining after edge | busy after edge | done after edge |
| --- | --- | --- | --- | --- | --- |
| Reset | 1 | 0 | 0 | 0 | 0 |
| A | 0 | 1 | 3 | 1 | 0 |
| A + 1 | 0 | 0 | 2 | 1 | 0 |
| A + 2 | 0 | 1 | 1 | 1 | 0 |
| A + 3 | 0 | 0 | 0 | 0 | 1 |
| A + 4 | 0 | 0 | 0 | 0 | 0 |

The pulse at A + 2 does not restart the countdown. The service contract accepts requests only while idle.

Repeat with reset asserted at A + 2. Completion must never appear for the cancelled request. Repeat with CYCLES = 1: the accepted request completes on the next rising edge, not the acceptance edge.

A held-high start is not a single pulse. After returning idle, a later edge can accept it as another request. Draw this scenario and decide whether the caller should create pulses or whether a different handshake interface is needed.

Compare this circuit with lesson_buffer.vhd. The buffer advertises readiness and retains data until accepted. A timer that silently queued requests would have a different interface, storage requirement and test plan.

For the parity circuit, make a table of values 0, 1, 2, 3, 127, 128 and 255. Write the number of one bits and expected odd output. Add 0000000X as an explicitly unknown simulation case.
