# Chapter 312 — Recurring operations are evidence, not another scripting stack

**Bits to Banking · Native Engineering · Umicom Foundation**  
**Prerequisite:** System Administration Stage 8, especially Chapters 97–102; C23 structures and status codes.

## Engineering problem: scheduled does not mean completed

A system administrator wants a daily Notes health check, a weekly backup review, an alert route and a recorded service owner. The naive implementation creates a new local script for each task. That fragments configuration, error reporting, audit identity and security across several products. It also makes it difficult for Umicom Studio, Trader, Bank and OS to report the same operational facts. The Framework-first design asks a different question: *which existing Framework component owns the schedule, the process, the result and the review?*

Umicom Framework already contains services for task scheduling, observable execution, configuration, identity, and durable records. In this book's Update 45 we **do not introduce a new production scheduler**. The training laboratory uses one deterministic arithmetic function, `BtbOpsNextDue`, to explain when a later check would be due. There are **no worker threads, timers, PowerShell scripts or Python scripts** in the executable source.

## Two clocks, two responsibilities

**Wall time** is a date and time displayed to human readers. It depends on a timezone and system-clock discipline. It is appropriate for audit events with explicit timezone and source. **Elapsed/monotonic time** is used for measuring intervals such as a request timeout where a daylight-saving adjustment must not change the elapsed duration. In a real scheduler, avoid subtracting timestamps from different clock domains. The classroom model uses **simulated seconds in one declared clock domain** so every example is deterministic.

```c
/* Source: labs/native/operational-resilience/operations_review.h */
BtbOpsResult BtbOpsNextDue(uint64_t lastCompletedSeconds,
                           uint64_t intervalSeconds,
                           uint64_t *outNextSeconds);
```

The function rejects a zero interval, a missing output pointer and an addition that exceeds `UINT64_MAX`. It does not change the output on failure. For example, calling it with `lastCompletedSeconds=1200` and `intervalSeconds=300` yields `1500` logical seconds. This is only arithmetic, not proof that anything will execute at that time.

## Who owns what?

| Responsibility | Production owner | This teaching batch |
|---|---|---|
| Scheduling and timed callbacks | Existing Umicom Framework task/time services | Pure due-time arithmetic only |
| Process and service lifecycle | Umicom Framework process/lifecycle services | No OS access |
| Identity and authorisation | Framework security contracts and operating system | Fictional evidence flags |
| Durable audit | Framework audit/Data Server | Caller-owned values and printed summaries |
| Source-control observations | Framework VCS services | Fixed test revision text only |
| Operational review display | Thin product UI/Studio perspective | `btb-operations-demo` console |

The distinction is architectural, not cosmetic. A `REVIEWABLE` result returned by the teaching model does **not** authorise a deployment, launch an SSH session or prove that a backup can be restored. A real process must authenticate its caller and fetch verifiable evidence from authorised providers.

## Guided practice

Open `operations_review.h`, identify the request, evidence and decision structures, and describe who owns their storage. Build the laboratory from `labs/native/operational-resilience` following its README. Run the named `cadence` and `cadence-overflow` CTest cases and explain why arithmetic overflow must not silently become a small due time. Record the actual compiler and test results; do not write “passed” before running them.

## Review questions

**Why can't a Python or PowerShell script be the default shared Umicom scheduling engine?** It would duplicate Framework mechanisms and introduce inconsistent runtime, deployment and security policy. Native Framework contracts should be reused or extended in C23/Assembly after inspection and approval.

**Why must a missing scheduled check produce a missing result?** The absence of an observation cannot logically establish that the check succeeded.

**Next:** [Chapter 313 — Composing the existing C23 evidence libraries](313-compose-existing-evidence-for-operations-review.md).
