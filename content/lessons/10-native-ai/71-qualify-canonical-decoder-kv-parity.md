# Lesson 71 — Qualify KV-Cache Reuse Against the Canonical Decoder

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Existing Umicom Framework C23 decoder and KV-cache APIs  
**Illustrated companion:** [Lesson 71](../../courses/llm-from-scratch/lessons/71-qualify-canonical-decoder-kv-parity.html)

## Learning objectives

Explain why two schedules of one cache kernel are not independent references, compare every logit against the canonical decoder, identify the positional invariants needed for reuse and interpret numerical-tolerance evidence without making performance claims.

## 1. Why the previous comparison was not enough

In [Lesson 70](70-test-prefix-reuse-with-real-decoder.md), a cache was cleared and rebuilt for each growing prefix, then compared with one long-lived cache receiving incremental appends. This demonstrates that the two **schedules** produce matching logits, but both paths use `UmiAiTrainingKvCache` and can share the same numerical defect.

The independent reference in this lesson is `UmiAiTrainingDecoderLogits`. It evaluates the original decoder using the canonical training-tape implementation. No extra decoder, tokenizer or attention kernel is introduced into Bits2Banking.

Comparing only the token selected by `argmax` is weak evidence: two different logit vectors can select the same token while assigning different probabilities to others. Compare **every vocabulary logit** under a predeclared tolerance.

## 2. One sequence, two representations

For a context length of eight, start with tokens `A B C D E F G H` at learned positions `0..7`. The KV cache can prefill `A` and append `B` through `H` without relocating earlier tokens. The canonical decoder independently processes the complete eight-token sequence. Both should produce matching logits for the last token.

| Check | Cache path | Independent decoder path |
|---|---|---|
| Input | Prefill A; append B–H | Process A–H as one complete context |
| Position of A | 0 | 0 |
| Position of H | 7 | 7 |
| Result | Final cached logit vector | Canonical last-row logit vector |
| Work counter | Eight computed token rows | A separate full-context evaluation |

The current Framework qualification tolerance is an **absolute logit difference no greater than `0.00004`**. This is a numerical acceptance criterion for the current C23 implementation, not an assertion that every future CPU or GPU backend will match bit-for-bit.

## 3. Call the existing Framework qualification service

```c
#include "umicom/ai/training/kv_position_qualification.h"

/* The caller has already created and owns an eight-position decoder. */
size_t contextIds[8] = {109U, 114U, 120U, 36U,
                        112U, 118U, 121U, 45U};
UmiAiTrainingKvPositionQualification report = {0};
UmiStatus status = UmiAiTrainingKvPositionQualify(
    model, contextIds, 8U, 37U, &report);

if (status == UMI_STATUS_OK) {
    /* Only a completed independent qualification publishes the report. */
    size_t checked = report.comparedLogits;
    uint64_t rows = report.computedRowsBeforeRollover;
    (void)checked;
    (void)rows;
}
```

The last argument `37U` represents an additional token that will force the first context rollover. The service qualifies **two states**, before and after eviction; Lesson 72 explains the second one.

For vocabulary size `260`, two full-vector comparisons examine `260 × 2 = 520` logit values. A successful report also checks that no non-finite values escaped validation and that observed cache work matches the qualified transition.

## 4. Read-only operation and failure safety

The caller retains the model's lifetime and serialises all decoder operations. The qualification must not train the model, update parameters or write a checkpoint. A failure leaves the caller's report unchanged. The associated regression records the canonical decoder checkpoint before and after qualification to check immutability.

Exact checkpoint bytes and numerical logits prove **different things**. Byte equality supports the claim that the test did not modify that checkpoint representation. Logit tolerance supports the claim that two computations agree for the tested states. Neither one by itself establishes model quality on unseen text.

## 5. Run the native Framework tests

From PowerShell, after building the Framework's existing prefix-work learning target:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
ctest --test-dir '.\build\windows-ucrt64-native-llm-prefix-debug' `
    -R '^framework\.ai\.training\.kv_position_' `
    --output-on-failure --no-tests=error
```

A CTest entry marked `Not Run` does not establish numerical failure or success; it means the test executable was not run. Build the named targets and inspect the first error before interpreting results.

## Practise and check

**A.** Why is comparing both schedules of the KV-cache kernel insufficient?  
**Answer.** Both can reproduce the same implementation defect. An independent canonical decoder is required for stronger numerical evidence.

**B.** With vocabulary size `260` and two full-context comparisons, how many logits are checked?  
**Answer.** `520`.

**C.** If a cached logit is `0.50003` and its canonical counterpart is `0.50000`, does it pass absolute tolerance `0.00004`?  
**Answer.** Yes: difference `0.00003` is less than `0.00004`, provided both values are finite.

**Next:** [Lesson 72 — Learned-position rollover](72-test-learned-position-rollover.md). The Framework remains the sole owner of the implementation.
