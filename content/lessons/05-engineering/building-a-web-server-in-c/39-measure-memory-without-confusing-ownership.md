<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/39-measure-memory-without-confusing-ownership.md

PURPOSE:
Measure memory without confusing ownership

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Measure memory without confusing ownership

[Course contents](index.md)
An optimization claim needs a defined measurement. Removing a payload copy can be demonstrated by inspecting allocation sizes and pointer identity. A process-wide memory measurement answers a different question. It includes libraries, stacks, allocator caches and other activity, so it may not fall immediately when one response is destroyed.


## 1. Define the question first

For the transfer API, ask whether it allocates another payload-sized buffer. For a server workload, ask for peak resident memory across a fixed number of requests and concurrency level. Resident memory means pages currently occupying physical RAM for the process. Neither question is answered by the executable's file size.


## 2. Use an independent allocation check

The transfer regression compiles the production body implementation with test allocation hooks. It starts with a known 4096-byte payload, transfers it, and checks that the body points to those same bytes. The metadata allocation must be smaller than the payload. The test is deliberately local: it makes no claim about the filesystem cache, sockets or process peak.


## 3. Keep input and load constant

1. Choose one fixed asset, record its byte length and digest, and keep the file unchanged.
2. Use the same binary configuration and request count for each comparison.
3. Start with one active request, then repeat with a chosen concurrent count.
4. Record the observation tool, operating system, allocator, warm-up behavior and peak metric.
5. Compare successful responses and cleanup outcomes as well as memory numbers.

A digest is a compact fingerprint of file contents. It helps confirm that two experiments used the same input. It does not prove that the program was correct. Likewise a lower memory peak does not excuse missing bytes or a failed request.


## 4. Estimate before measuring

~~~text
old overlapping payloads: approximately 2 * file_bytes * active_requests
transferred payloads:      approximately 1 * file_bytes * active_requests

Add metadata, headers, stacks, sockets and allocator overhead separately.
~~~

These formulas describe only a simple static-file path where each request owns its own payload. They are not a general memory model for streaming, compression, shared caches or zero-copy operating-system APIs. The present transfer API still reads the complete bounded file into memory; it is not a streaming-file implementation.


## 5. Record uncertainty honestly

If resident memory remains high after responses finish, inspect outstanding owners and allocator behavior before declaring a leak. Allocators may retain freed pages for reuse. Conversely, a stable graph during a short test does not prove that a slow leak is absent. Repeat a defined workload and use allocation or sanitizer evidence when available.

Exercise: write two separate statements for an engineering report. One can say that the transfer regression found no second 4096-byte payload allocation. The other should report measured peak process memory only if that experiment was actually run. Do not merge those statements into an unsupported claim that all application memory problems are fixed.


[Previous lesson](38-release-response-bodies-on-every-exit.md) · [Next lesson](40-encode-a-fastcgi-request-with-bounded-bytes.md)
