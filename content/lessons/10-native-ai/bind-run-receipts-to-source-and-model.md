# Bind Fine-Tuning Evidence to the Exact Source and Frozen Model

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Why an experiment needs an identity

A report saying “loss fell from 4.3 to 4.1” is insufficient. Which approved sources did it use? Which frozen model checkpoint? Was the answer-only objective preserved? How many successful SGD steps were performed? A reproducible experiment must distinguish these observations from a generic performance claim.

The Framework's supervised experiment report records the **ordered approved dataset SHA-256**, **frozen decoder checkpoint SHA-256**, training policy, completed steps, baseline and final held-out metrics and an in-memory epoch trace. It does not log prompts, document names or private messages.

## Portable records are not native C structures

Serialising `sizeof(myStruct)` bytes is unsafe when different compilers insert padding or use different field layouts. The Framework's `UmiAiTrainingSupervisedReceiptEncode` explicitly writes a **208-byte little-endian record**, with a fixed magic, format revision, integer counters, IEEE-754 metric bits, two 32-byte SHA-256 identities and a trailing 32-byte SHA-256 checksum.

The original model and dataset are *not* inside this record. It is deliberately a compact evidence receipt.

## Inspect the native API

```c
#include "umicom/ai/training/supervised_receipt.h"

uint8_t encoded[UMI_AI_SUPERVISED_RECEIPT_BYTES] = {0};
size_t used = 0U;
UmiStatus status = UmiAiTrainingSupervisedReceiptEncode(
    &runReport, encoded, sizeof(encoded), &used);

UmiAiTrainingSupervisedReceiptInfo opened = {0};
if (status == UMI_STATUS_OK)
    status = UmiAiTrainingSupervisedReceiptDecode(encoded, used, &opened);
if (status == UMI_STATUS_OK)
    status = UmiAiTrainingSupervisedReceiptVerifyLive(
        &opened, dataset, adapter);
```

`VerifyLive` compares dataset identity, frozen decoder checkpoint identity and the **current adapter step count**. It does not compare the adapter's actual trainable tensors. For that reason, the receipt is *not* an adapter checkpoint and cannot recover model weights after a crash.

## Integrity versus authenticity

A checksum detects changes when compared against a separately trusted expected digest. Someone who can rewrite an unsigned receipt can calculate a new checksum. A valid SHA-256 trailer therefore **does not establish who signed or approved the experiment**.

To promote an AI model for Umicom Studio or another application, a separate verified publisher signature, permission review, model checkpoint identity and model-quality gate are required. The training receipt supplies an input to that review; it does not authorise deployment.

## A worked source-change example

Imagine two model runs use the same initial checkpoint, seed and hyperparameters, but one reviewed answer was corrected before the second run. The complete ordered JSONL digest changes. The same fine-tuning receipt cannot validly describe both experiments; `VerifyLive` must reject the mismatched collection.

A second scenario uses the same source bytes but trains two more adapter steps. The original receipt's final step count no longer matches the live adapter. Both observations must be explicit rather than quietly treating results as interchangeable.

## Practice

1. Why include both corpus and model hashes? **Either one can change independently.**
2. Is a receipt's checksum a digital signature? **No.**
3. Can an intact receipt restore weights? **No; it stores aggregate evidence, not tensors or optimizer moments.**
4. Why is an exact record length important? **Trailing or missing bytes could change parsing meaning and undermine compatibility.**

Continue with [resume and failure limitations](understand-training-failures-and-resume-limits.md) and [Mathematics Unit 32](../11-maths-for-ai/32-integer-bounds-and-evidence-identities.md).
