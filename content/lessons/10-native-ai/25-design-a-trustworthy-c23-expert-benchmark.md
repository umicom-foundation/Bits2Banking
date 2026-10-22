# Lesson 25 — Design a Trustworthy C23 Expert Benchmark

**Level:** intermediate • **Estimated time:** 19 minutes • **Goal:** turn progress claims into verifiable evidence

## What does it mean to learn to write C23?

A small next-token model can learn that `return` often follows a condition and that semicolons appear frequently. It cannot yet be called a dependable C23 assistant, much less a banking software expert. **Predicting plausible source bytes is not the same as producing correct, secure, maintainable code.**

To evaluate a future specialised Umicom C Expert, we need different kinds of evidence.

## Build a staged evaluation ladder

| Evidence level | What it tells us | What it cannot prove |
|---|---|---|
| Held-out next-token cross-entropy | Predictive ability on withheld bytes | Whether generated functions work |
| Compile success | Whether a complete candidate passes a specified C23 compiler | Correct behaviour or safe memory ownership |
| Unit tests | Whether selected behaviours match expected examples | Absence of all defects |
| Sanitiser tests | Whether tested executions expose certain memory/undefined-behaviour defects | That every possible execution is safe |
| Design review | Whether APIs, ownership and domain rules are explicit | That the implementation is defect-free |
| Independent domain tests | Whether fictional accounting and payment invariants hold | Readiness for production financial use |

Each level answers a different question. A model might achieve excellent next-token statistics and still fail a simple test for integer overflow.

## Start with one verifiable fictional requirement

A model may be asked to implement an account transfer eligibility check in C23:

> Given available pence and a transfer amount, accept only when the amount is positive and does not exceed the available balance. Do not alter either input.

A reference implementation is small enough to review:

```c
#include <stdbool.h>
#include <stdint.h>

bool IsTransferAllowed(uint64_t availablePence, uint64_t amountPence)
{
    return amountPence > 0U && amountPence <= availablePence;
}
```

A useful evaluation suite should test zero amount, exact balance, insufficient balance and the largest supported integer values. If the task becomes a debit operation instead of a decision, it must additionally establish atomicity and checked arithmetic.

## Keep the benchmark genuinely held out

Do not put the exact required function, test assertions or benchmark solution into the training corpus. Otherwise a model could reproduce a memorised answer. Keep task descriptions, reference solutions and expected results independently versioned. Record compiler versions, build flags, test results and any execution restrictions.

A security-sensitive project must never run arbitrary generated executables inside a production banking system. Generated C23 source should be reviewed, built and tested in an appropriately isolated environment with explicit resource limits.

## A responsible measurement record

For each test prompt, record:

1. The immutable benchmark identifier and source revision.
2. Model/checkpoint fingerprint and training-data provenance.
3. Prompt, sampling configuration and produced source bytes.
4. Compiler configuration and diagnostics.
5. Automated test outcomes and known untested behaviour.
6. The reviewer decision, including whether the candidate was rejected.

Report numerator and denominator. “7 of 10 fictional transfer tests passed” is more informative than “the model understands banking”. Always label demonstrations as educational until wider qualification is complete.

## Your course project

Prepare a **benchmark plan**, not an executable service. Define five small original C23 exercises relevant to Umicom: a notes record, an account eligibility check, a payment status enum, a bounded message parser and a simple panel-state update. For each task write one clear requirement, at least three independent test cases, and the evidence needed for review.

<details><summary>Knowledge check: what about top-5 accuracy?</summary><p>Top-5 accuracy means the correct next token appeared among the five highest-scoring options. It is useful for studying the next-token predictor, but it does not measure whether an entire C23 function compiles, maintains memory ownership or satisfies financial invariants.</p></details>

## Where the learning journey goes next

You now have the language to discuss source provenance, tokenisation, causal windows, reproducible experiments, checkpoint recovery and trustworthy evaluation. The next stage is deeper work on training-data governance, scalable native compute and specialist task datasets. We should claim expertise only when independent benchmarks support it.

**Service to Many Leads to Greatness.**
