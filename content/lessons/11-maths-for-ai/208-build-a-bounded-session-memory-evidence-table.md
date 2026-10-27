# Mathematics for AI — Unit 208: Build a bounded session-memory evidence table

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Basic arithmetic and the preceding mathematics units.

## Learning objective

Combine budget estimates, active leases and rollover records.

## Step-by-step derivation

A useful evidence table lists configuration, checkpoint digest, `bytesPerSession`, budget, maximum sessions, active sessions, observed reserved bytes, peak reserved bytes, rejections, rollovers and independent process peak RSS. For the two-layer, four-position example, write rows for active sessions `0,1,2`: raw reservations are `0,512,1024`. The budget is 1,024 bytes, so an attempted third lease has no valid row. State whether numbers are calculated, observed from counters or measured from the operating system.

## Check your understanding

**Exercise:** Why must the table distinguish calculated reservation and measured RSS?

<details><summary>Show the worked solution</summary>

Because raw tensor payload excludes allocator overhead, model weights and operating-system memory behaviour.

</details>

## Native C23 connection

Use the Framework's existing checked `InferenceMemoryPlan`, `StackedKvStore` and `StackedKvPool` contracts. Arithmetic estimates do not themselves prove safe allocation, neural accuracy or measured latency.

## Continue learning

[Previous unit](207-separate-admission-time-from-generation-latency.md) · [Mathematics learning path](../../courses/maths-for-ai/kv-session-lifecycle-mathematics.html) · [Browser unit](../../courses/maths-for-ai/lessons/208-build-a-bounded-session-memory-evidence-table.html)

*Service to Many Leads to Greatness.*
