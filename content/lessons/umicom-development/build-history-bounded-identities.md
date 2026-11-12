<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/build-history-bounded-identities.md

PURPOSE:
Retry with new identities and bounded retained history

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Retry with new identities and bounded retained history

## Separate identity from position

An operation ID identifies an admitted attempt. A history index identifies a position in the currently retained ring. Those values are not interchangeable. With capacity two, three attempts produce IDs 1, 2 and 3, but only IDs 2 and 3 remain. Index zero now refers to ID 2. An interface that stores a ring index as permanent identity could later open the wrong attempt after another completion.



## Observe the rolling scenario

| After attempt | Retained IDs | Oldest index |
| --- | --- | --- |
| 1 | 1 | 0 points to ID 1 |
| 2 | 1, 2 | 0 points to ID 1 |
| 3 | 2, 3 | 0 points to ID 2 |



All three attempts in this laboratory fail for the same missing Run program. Retrying does not overwrite the earlier failure or reuse its ID. The ring removes only the oldest retained record when capacity is full. This makes the capacity policy visible without claiming that omitted records succeeded, disappeared from a durable log or were never attempted.



## Share the identity allocator

~~~c
config.history = history;
umi_build_runner_create(&config, &first);
umi_build_runner_create(&config, &second);
/* Check both creation statuses before using either runner. */
~~~



The shared scenario creates both runners before either performs work. Each runner initially has a local next-ID field, but a configured history is the authoritative allocator. The first call reserves ID 1 and the second runner reserves ID 2. This is why assigning IDs independently inside each client would be wrong. The laboratory performs these calls sequentially; it does not claim to qualify simultaneous access from multiple threads.



## Respect exhaustion and clearing

The identity API uses zero as an exhaustion signal rather than wrapping a 64-bit ID back to one. A refused reservation cannot be appended as an invented operation. Clearing retained records also does not authorise reusing old IDs. The Framework regression fixture exercises exhaustion; this small public client keeps to ordinary IDs and does not modify private allocator state.



## Exercise: model a history viewer

- Run rolling and shared through the owner procedure and compare retained IDs.
- Sketch a viewer that copies records before presenting them instead of holding mutable ring indices.
- Explain how a completed result can be evicted while its operation identity remains meaningful in an external log.
- Describe what the viewer should display when a retained record cannot be read.



For a coherent multi-record review while producers are active, inspect UmiBuildHistoryCopyRecent. It copies the newest retained records under one history lock and reports omitted retained records. Repeated count and at calls are sufficient for this single-threaded laboratory, but may observe different ring generations in a concurrent viewer. The method selected for observation must match the producer lifetime.



## Recover without erasing evidence

Investigate the failing profile and submit a new attempt after correcting it. Do not clear history as a way to make the latest error disappear. For exhausted identities, use a reviewed new owner lifecycle and preserve the previous evidence. Native presentation, concurrent producers and persistent logging each need their own qualification; a sequential ring exercise proves none of those automatically.



## Source and practice

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Build-history laboratory and owner commands](../../../labs/native/framework-build-history/README.md) · [HTML edition](../../courses/umicom-development/lessons/build-history-bounded-identities.html)
-->
[Build-history laboratory and owner commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-build-history/README.md) · [HTML edition](../../courses/umicom-development/lessons/build-history-bounded-identities.html)

[Previous lesson](build-history-copy-and-lifetime.md) · [Next lesson](build-history-layered-qualification.md) · [Course index](index.md)
