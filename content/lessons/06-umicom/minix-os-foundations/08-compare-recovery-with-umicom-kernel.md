# Compare MINIX recovery with Umicom Kernel

## Compare invariants, not names

Both systems invite questions about service lifetime: who owns resources, when may a replacement run, and what happens to in-flight work? Their implementations and ABIs remain independent.

MINIX's [live-update guide](https://wiki.minix3.org/doku.php?id=developersguide:liveupdate) describes RS-coordinated quiescence, state transfer and rollback. Its details and limitations require a matching system version. Umicom's managed-service controller currently provides its own readiness, health and replacement policy; a restart path is not evidence of MINIX-style live update.

## Build a comparison worksheet

For each system, answer these questions from identified source:

1. How is a live instance identified?
2. What makes it ready for dependents?
3. Who revokes access after failure?
4. Which resources remain owned during cleanup?
5. What state must be transferred or reconstructed?
6. What evidence distinguishes recovery success from a retry still in progress?

Do not fill unknown answers with a familiar API from the other system.

## Worked scenario

A service is replaced while another component still refers to a buffer it owned. Copying the visible service name does not repair the stale memory relationship. The recovery design must account for outstanding references, grants or handles before declaring the replacement usable.

In Umicom, study dependency revocation and collection before readmission. In MINIX, study the selected service's quiescence and grant behaviour. The similar problem does not imply identical solutions.

## Exercise and answer

A demonstration prints “restarted” after a new process begins. What remains unproven? Answer: readiness, resource cleanup, outstanding request outcomes, restored state and the client's ability to use the new instance.

## Capstone

Produce a source map, a read-window boundary test report, a guest build record and an explicit list of unexecuted checks. If you only performed source reading, label the work accordingly. Keep MINIX source attribution and licences; the original Umicom teaching driver does not relicense the operating system.

The next course stage can add a stateful service after the read-only boundary is qualified. This introductory module does not claim a complete MINIX course, a new operating system or hardware validation.

[Course contents](index.md)
