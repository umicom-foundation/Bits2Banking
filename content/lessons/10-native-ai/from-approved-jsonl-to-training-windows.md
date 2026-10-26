# From Approved JSONL to Response-Only Training Windows

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning outcome

Prepare *already reviewed* prompt/completion examples for the existing Umicom native decoder without writing a second tokenizer, JSON converter or training engine. Understand why validating every source and partition **before** allocating an admitted dataset matters.

## Begin with one fictional example

Imagine a training demonstration containing the question `Q` and completion `A`. The Framework's reviewed-example service emits a single-line JSONL representation:

```json
{"prompt":"Q","completion":"A"}
```

The example is deliberately fictional. Its exact bytes must be bound to separately reviewed source evidence. The JSONL file alone does not prove authorship, permission to use the text for training, privacy review, or isolation from a held-out evaluation set.

The existing `UmiAiTrainingReviewedExampleJsonl` service establishes the canonical byte representation for one approved example. `UmiAiTrainingReviewedCorpusAudit` checks the ordered collection's SHA-256 evidence, duplicate records and whether descendants of the same original source remain in one partition.

Only after that audit passes does the new **`UmiAiTrainingSupervisedDatasetCreate`** accept the complete collection and turn each JSONL record into fixed-length token windows.

## Read the training alignment

The canonical byte vocabulary reserves IDs 0–3 for PAD, BOS, EOS and UNK. The reversible byte tokenizer maps the byte value `b` to token ID `b + 4`.

For prompt `Q` and answer `A`, a conceptual stream is:

`[BOS, Q, A, EOS]`.

At each input position the target is the next token. The loss mask selects the response byte and EOS, **not** the prompt or right-padding. If the context length is eight, unused positions receive PAD and a zero mask. No loss term is silently created for padding.

The underlying `UmiAiTrainingSupervisedByteWindowBuild` service performs the actual token layout. If the complete example cannot fit within the decoder's context, creation fails. Shortening an approved answer without editorial review could change what the model is taught.

## Framework C23 interface

```c
#include "umicom/ai/training/supervised_dataset.h"

/* Each record and evidence entry is already produced by the Framework's
 * reviewed-source services. This is an excerpt, not a full program. */
UmiAiTrainingSupervisedDataset *dataset = NULL;
UmiStatus status = UmiAiTrainingSupervisedDatasetCreate(
    records, recordLengths, evidence, recordCount, 8U, &dataset);
if (status == UMI_STATUS_OK) {
    UmiAiTrainingSupervisedDatasetInfo info = {0};
    status = UmiAiTrainingSupervisedDatasetInspect(dataset, &info);
    UmiAiTrainingSupervisedDatasetDestroy(dataset);
}
```

The dataset owns copies of *token IDs and masks*, not the original JSONL text. It exposes copies of individual windows, never mutable pointers into internal storage. Once created, its contents are immutable.

## Why the JSON parser is deliberately narrow

The source producer emits `prompt` then `completion`, with a fixed set of canonical escapes. The reader accepts precisely that format rather than claiming to parse arbitrary JSON. It refuses unknown properties, reordered fields, malformed escapes, extra JSONL records and missing delimiters. This reduces ambiguity in training data pipelines; another input format needs its own reviewed adapter, not a permissive shortcut.

## Exercises

1. In `[BOS,Q,A,EOS]`, which targets are supervised? **The response `A` and EOS.**
2. Why check the whole dataset before building the first window? **A late source-group leak must invalidate the collection, not leave a partly admitted dataset.**
3. Is a content digest sufficient to prove the author permitted training? **No; rights and approval are separate evidence.**
4. Why preserve source grouping? **Two excerpts of one original document must not appear on opposite sides of an evaluation split.**

Continue with [auditing source-level splits](audit-supervised-learning-datasets.md) and [Mathematics Unit 25](../11-maths-for-ai/25-loss-masks-and-next-token-alignment.md).
