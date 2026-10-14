# Chapter 292 — Why a running service can still be blocked

**Bits to Banking · Native engineering and system administration · ISO C23**  
**Prerequisites:** [System Administration Chapters 35–36](../08-system-administration/35-monitor-metrics-logs-and-incident-timelines.md), [Chapter 45](../08-system-administration/45-recognise-service-health-versus-process-state.md), and Engineering Chapter 291.

## The problem we need to solve

Suppose the Umicom Notes classroom application has three parts: a document store, an application service and a presentation window. A user can see the window and find the service process in a list of running processes. Does that prove a document can be saved or read? No. The store may be unwritable, the service may be connected to the wrong directory or the requested document might fail validation. **A running process is an observation, not an authorisation to declare the whole service READY.**

A real operational system distinguishes *process lifecycle*, *liveness*, *readiness*, *business correctness*, and *release qualification*. Even when all required checks have passed, readiness is a snapshot for a particular service and observation time; it is not a guarantee that the next request cannot fail. Monitoring systems therefore retain evidence, update their decisions and identify degraded or blocked dependencies.

![Service dependency and readiness](../../assets/diagrams/sysadmin-service-dependency-readiness-update40.svg)

## Formal model

The previous `labs/native/sysadmin-evidence` laboratory (Update 39) owns the educational observation contract. Its `BtbAdminReview` holds copied checks with `checkId`, `captureId`, state and a bounded label. Its `BtbAdminReviewEvaluate` declares READY only when required checks are present, from the correct capture, and PASS. Optional adverse observations yield REVIEW; adverse required checks yield BLOCKED.

Major Update 40 deliberately **reuses that implementation**. It does not add another observation parser or write a production service-monitoring engine. The new laboratory composes several `BtbAdminReview` instances into a dependency graph. Each service has a stable ID, required-check mask and dependency mask. When a prerequisite is blocked, consumers cannot be marked READY by their own local checks alone.

| Situation | Store observation | Notes observation | Honest aggregate |
|---|---|---|---|
| Both required checks pass | PASS | PASS | READY |
| Store check fails | FAIL | PASS | BLOCKED |
| Store check not run | NOT RUN | PASS | BLOCKED |
| Store has optional warning | REVIEW | PASS | REVIEW |
| Store evidence was captured yesterday | STALE | PASS today | BLOCKED |

The aggregate decision does not change the actual host. It describes supplied fictional observations and their declared dependency relationships. An application that needs a real readiness check must consult the authoritative Umicom Framework service, not the education example.

## Source orientation

Open `labs/native/service-readiness/service_readiness.h`. The public contract contains `BtbServiceSpec`, `BtbServiceGraph` and `BtbServiceSummary`. The graph has at most eight **registered service records**. Service identifiers range from 1 to 32; bit N−1 identifies service N in a dependency mask. The distinction between count and identifier keeps the bounded graph compact while allowing sparse identifiers.

```c
const BtbServiceSpec storage = {
    1U,                    /* serviceId */
    0U,                    /* dependencyMask: no predecessor */
    UINT32_C(1),          /* check #1 is mandatory */
    "Notes document storage"
};
const BtbServiceSpec notes = {
    2U,
    UINT32_C(1),          /* depends on service #1 */
    UINT32_C(1),          /* own check #1 is mandatory */
    "Notes application"
};
```

The strings are display names, not authentication identities. No service ID or mask grants permission to restart a process or access a user's file. The model is immutable with respect to the underlying machine: it never calls Windows Service Control Manager, systemd, sockets or file APIs.

## Guided investigation

1. Read `BtbServiceGraphRegister`. Identify the checks performed before any record is appended.
2. Locate `EvaluateNode` in `service_readiness.c`. Find the point where prerequisite results are propagated.
3. Find `BtbAdminReviewEvaluate`. Explain why reusing this function matters for consistent readiness rules.
4. Run the demo, then the `inherited-block` CTest case. Read each test's expected decision before seeing the output.
5. Imagine a service that has a healthy application process but no current storage check. Write a two-sentence report that does **not** claim readiness.

## What could go wrong?

A naive implementation might initialise all checks to PASS, make an unknown prerequisite automatically succeed, or accept a previous capture's PASS after a service restart. All three are false positives. The C23 laboratory starts from a non-ready state, rejects references to unknown services, rejects cycles and requires explicit evidence for mandatory checks. Failure to evaluate produces an error rather than a partial green report.

**Source-preservation rule:** Do not copy `admin_evidence.c` into the new laboratory. The new CMake target links the existing Update 39 library. Production equivalents belong in Umicom Framework. The prior lesson and C23 code remain unchanged.

## Review questions

1. Why can a Running service be unready? *Because dependencies or required business actions may fail.*
2. What result is correct when an optional diagnostic reports WARNING? *REVIEW if all required checks pass.*
3. What happens when a required dependency has old evidence? *The dependent service must be BLOCKED until current requirements are verified.*
4. Does the laboratory restart or monitor real Umicom services? *No; it evaluates caller-supplied fictional observations only.*

**Next:** [Chapter 293 — Compose existing C23 observation services](293-compose-a-c23-service-readiness-graph.md).
