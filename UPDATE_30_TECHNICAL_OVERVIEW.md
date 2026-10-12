# Major Update 30 — Technical overview and architecture decision

## Engineering motivation

Update 29 established a bounded request queue, generation tokens and quiescence in a deterministic single-owner teaching program. Update 30 continues the **same contract**, connecting accepted work to terminal notifications and receipt-driven storage release. It also substantially expands the Git/version-control curriculum to address the actual Umicom OS Framework-submodule failure patterns: detached HEAD, obsolete local main, non-fast-forward pushes, changes to tracked and untracked files, and careful stash comparison.

## New native integration adapter

```text
Mock request: CASH|GBP|ACCOUNT-A
           |
           v
BtbDispatchSubmit (requestId + generation + connectionId)
           |
           v
Existing BtbWorkQueue (8 owned copied requests)
           |         Single-owner BtbDispatchStep
           |         -> bounded diagnostic operation
           v
Existing BtbCompletionQueue (4 copied terminal notices)
           |
           v
BtbDispatchReceive (owned receipt; release original work slot)
```

The adapter does not add threading, polling a live socket, a financial calculation, or state persistence. Its primary value is in making cross-component identity and delivery responsibilities **executable and testable** without duplicating previously implemented queues.

### Contracts and invariants

| Contract | Enforced behaviour |
|---|---|
| Work admission | Request bytes are copied, 1–96 bytes, max eight retained entries. Invalid/rejected submissions do not modify caller's output. |
| Request identity | Monotonic nonzero `uint32_t` request ID and `slot + uint64_t generation`; exhaustion is rejected. |
| Processing | One synchronous `Step`; `Run` processes at most budget=8 and returns processed count. |
| Downstream backpressure | `Step` and queued cancellation refuse without changing request state when four terminal notices already exist. |
| Terminal state | Success or cancellation each produces exactly one completion notice. |
| Receipt | Owned value copy, then consumption of notice and release of work slot. |
| Quiescence | Refuses new submissions; admitted items may be processed or cancelled and delivered. |
| Drained | True only when no queued/active items, no completion notices, and no terminal entries awaiting release. |
| Consistency | `accepted = delivered + occupied`; `succeeded + cancelled = delivered + pending` plus token mappings and unique completion IDs. |

All state transitions occur in one execution context, so adjacent library calls can be treated as serial operations. **This design is not safe for concurrent callers**; its method of checking capacity before processing would need real synchronisation or reservation before any multithreaded implementation.

The `bytesTransferred` field comes from an earlier generic completion-queue lesson. Here it denotes bytes **consumed from the copied request payload** during the diagnostic Step. It does not mean network bytes sent, money transferred or an authenticated database write.

### Error model

The public adapter returns distinct statuses for invalid input, lack of work capacity, lack of notification capacity, empty queue, stale identity, already terminal, shutdown admission, exhausted request ID and invalid internal state. A code reviewer should verify errors are not collapsed into a single generic `false`: the caller needs to distinguish retryable backpressure from a permanently invalid request.

### No hidden redundancy

The new `CMakeLists.txt` references `../work-handoff/handoff.c` and `../completion-queue/queue.c`. It does **not** ship their sources as replacements or add application-local variants of Framework services. All examples remain confined to the educational repository. A production implementation would be required to use the current Framework task, event, command and lifecycle contracts, only extending Framework after inventory, design and owner approval.

### Limitations

- No concurrent socket work, epoll, IOCP, kqueue, worker pool, TLS or live service integration.
- No asynchronous cancellation of a worker currently executing; there is no overlap between `Step` and another public operation.
- No durable results, reliable distributed delivery or transactional outbox.
- No automated Git operations beyond clearly documented **interactive** commands; Git is the authoritative VCS rather than a new wrapper executable.
- FNV-1a digest demonstrates deterministic byte processing, **not** cryptographic validation or audit immutability.
- Unknown platform behaviours must be verified through Windows UCRT64 and integration acceptance, not inferred from Linux-only tests.

### Source-preservation boundaries

This update's ZIP contains **only additions**. It leaves previously implemented queue libraries, old chapters, MkDocs navigation and historical scripts unchanged. Navigation integration is an explicitly documented manual review operation, not an unreviewed YAML rewrite. Existing Umicom Foundation authorship, licensing, original research and the Islam manuscript navigation are preserved.
