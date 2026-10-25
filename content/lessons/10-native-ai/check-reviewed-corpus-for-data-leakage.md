# Native AI laboratory — Check a reviewed dataset for exact leakage

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation owner:** Umicom Framework (C23)

## Learning objectives

Explain the difference between a training and evaluation partition, verify the exact JSONL bytes of approved examples, reject repeated records and prevent one original document from appearing in both partitions.

## 1. Why a train/evaluation split matters

Training adjusts model weights. Evaluation measures performance on material withheld from the adjustment. If identical examples appear in both partitions, evaluation can overstate generalisation. If one original recording produces several transcripts or caption fragments, those derivatives must remain together in one partition; otherwise almost identical source content can leak between the groups.

The Framework's existing `UmiAiTrainingSourceVerifyBytes` validates caller-declared SHA-256 against actual original and prepared bytes after explicit human approval. `UmiAiTrainingReviewedExampleJsonl` then produces source-bound prompt/completion records and separately retained provenance. The new `UmiAiTrainingReviewedCorpusAudit` checks the **collection** of those records before they are admitted to a learning experiment.

## 2. What is checked

| Check | Why it matters |
| --- | --- |
| The JSONL bytes match their evidence SHA-256 | Detects changed text after review |
| Every JSONL record is complete and bounded | Prevents hidden suffixes and concatenated lines |
| No exact duplicate record occurs | Prevents trivial memorisation inflating counts |
| Every original asset stays in one partition | Keeps a document and its derivatives together |
| Identical prepared content does not straddle partitions | Catches exact derivative reuse |
| Both train and evaluation contain examples | Prevents a misleading evaluation with no held-out data |

The audit publishes counts and a deterministic ordered digest, **not** the underlying prompt text, personal names, source filenames or original media bytes.

## 3. Minimal C23 call

```c
#include "umicom/ai/training/reviewed_corpus.h"

/* records, lengths and evidence were produced and verified by Framework. */
UmiAiTrainingReviewedCorpusReport report = {0};
UmiStatus status = UmiAiTrainingReviewedCorpusAudit(
    records, lengths, evidence, recordCount, &report);

if (status == UMI_STATUS_OK) {
    /* Both splits exist, exact bytes agree, and no exact leakage was found. */
}
```

`records` is an array of pointers to JSONL byte sequences, `lengths` is an array of their byte counts, and `evidence` contains the corresponding provenance records. This code does not open files or train any model.

## 4. An important limit: identical is not merely similar

Two different sentences can convey the same answer. A transcript and its edited summary can preserve many phrases despite having different SHA-256 values. Exact checks cannot detect all such **near-duplicates**. Similarly, approving a file's checksum does not prove that its training rights are valid. Human editorial, privacy, licensing and near-duplicate review remain separate requirements.

The audit cannot create editorial permission by itself; it must only consume evidence from previously approved source-verification calls.

## 5. Exercises and answer

**Scenario:** A recorded interview has two approved transcripts; one transcript is in training and the other in evaluation. The original recording's SHA-256 is the same in both provenance records. Should the audit accept the collection?

**Answer:** no. The original media identity groups both derived texts. The split is invalid even if the two transcripts have different wording and different prepared-text digests.

**Scenario:** Training and evaluation records are different byte strings but paraphrases of the same answer. Would exact SHA-256 duplicate checking detect them? **Answer:** not necessarily. Additional semantic near-duplicate review is needed.

**Takeaway:** provenance and dataset partitioning are part of experimental correctness, not optional publishing metadata.

[Related lesson: reviewed examples](prepare-reviewed-supervised-examples.md) · [Native adapter lesson](train-a-frozen-decoder-logit-adapter.md)
