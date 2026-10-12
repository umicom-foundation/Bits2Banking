# Major Update 29 — Bounded Request Handoff and Deterministic Ownership

## Engineering scope

This is a **standalone C23 educational laboratory** that follows the real socket reactor and bounded admission lessons of Update 28. It does not change the existing HTTP server or Umicom Framework. A separate directory and CMake project avoid requiring unverified replacements of the user's current HTTP CMake files. The native queue demonstrates *handoff contracts*, not actual asynchronous thread execution.

## Ownership and lifecycle

The queue owns a copied payload of at most 96 bytes per request. A caller receives a `(slot, generation)` token. An acquiring consumer borrows a read-only pointer until completion/cancellation, then calls Release. Release wipes the bytes while retaining the generation to prevent late completions from hitting a new request in a reused slot. The producer cannot submit while the queue is quiescing. FIFO order is maintained on cancellation.

## Invariants

At all times queued entries are represented exactly once in the waiting ring. The queue active count equals ACTIVE entries and never exceeds the configured active limit. FREE entries are eligible for new submissions, while COMPLETE and CANCELLED entries must be released before reuse. The deterministic C23 test exercises 50,000 mutation steps, checking these invariants after each.

## Boundaries and future integration

There are no mutexes, threads, concurrent worker pools, socket handlers, C++ adapters, Python scripts, PowerShell scripts or database writes in this package. Updating the real network backend requires reviewing the latest repository and Framework interfaces, then implementing the appropriate dispatch and wakeup contracts in approved shared C23 code. This lab is not ready to be merged into a production reactor without those steps.

## Preservation and security

No existing source file is replaced. No legacy function or comment is deleted. The lab has fixed bounded payloads and no untrusted external resource access. Do not expose this demonstration as an Internet-facing service.
