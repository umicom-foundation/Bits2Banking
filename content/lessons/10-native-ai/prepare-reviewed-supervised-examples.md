# Training Data Laboratory — Prepare Reviewed Supervised Examples

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Implementation owner:** native C23 Umicom Framework

## Learning objectives

Distinguish **source extraction**, **review**, **admission**, **example selection** and **model training**. Learn how to prepare prompt/completion pairs from source-linked text without placing private provenance inside a model-facing record or accidentally mixing training and evaluation content.

## 1. The model does not ingest a PDF or video directly

A native text language model learns from token sequences. A PDF, Word document, audio file or video is not automatically a trustworthy sequence of training text. Before producing examples, an approved extraction service must obtain the relevant text. Media extraction may involve subtitles, human transcripts, OCR or another specialist provider; each has different accuracy and rights limitations.

Umicom Framework already provides a Creative Workspace caption-track parser for supported SRT and WebVTT subsets, and a separate adapter converts reviewed caption cues into plain text. These are **not** speech recognition, video understanding or a general-purpose PDF extractor. A source without an appropriate reviewed transcription remains unready for text training.

## 2. Admit sources only through reviewed evidence

The existing `UmiAiTrainingSourceReview` contract identifies the text derivative, source medium, original and prepared SHA-256 digests, licence identifier, rights evidence and approval flags. Its admission policy rejects private and restricted visibility for this educational public-source training path, and rejects incomplete rights, training-use and personal-data reviews.

The companion `UmiAiTrainingSourceVerifyBytes` computes cryptographic digests over the **actual original bytes** and **actual prepared text**, compares them to the declared evidence, then calls the canonical admission policy. It cannot verify that a human reviewer was authorised or that a transcript is factually accurate. Those are procedural review obligations.

No source is approved merely because it resides under `dropzone` or because its extension is `.md` or `.txt`.

## 3. Source-level train/evaluation separation

If one audio recording has three transcript fragments, all three derive from the **same original asset**. The Framework assigns their partition using the original asset's digest, not the individual text chunks' digests. This prevents exact copies of that same source entering both training and evaluation partitions.

It does not automatically identify paraphrases, near-duplicate documents or a teacher's answer accidentally reproduced in a question. Human review and independent deduplication remain necessary.

## 4. Select two verifiable spans

A **supervised example** can contain one prompt and one expected completion. The new Framework API `UmiAiTrainingReviewedExampleJsonl` accepts two explicitly selected, nonoverlapping spans from a reviewed UTF-8 text derivative. It checks that the whole derivative is valid UTF-8 without NUL bytes, validates the text spans, verifies source approval and SHA-256 evidence, and then produces one JSON Lines record.

For example, a fictional, approved teaching derivative contains:

```text
Question: What is a vector?
Answer: An ordered list of numbers.
```

The prompt span contains `What is a vector?` and the completion span contains `An ordered list of numbers.`. The produced **model-facing** line is:

```json
{"prompt":"What is a vector?","completion":"An ordered list of numbers."}
```

The record is UTF-8, escaped as JSON and terminated by an LF. It includes **no source filename, personal correspondence, rights-evidence identifier or source digest**. Those belong in separately controlled evidence returned to the caller. The JSONL schema is a preparation format, not a claim that the existing decoder trainer already consumes that format.

## 5. A native Framework usage excerpt

```c
#include "umicom/ai/training/reviewed_examples.h"

/* review, originalBytes, derivativeBytes and their lengths are supplied
 * by an authorised source-review workflow, not fabricated by this code. */
UmiAiTrainingTextSpan question = {10U, 17U};
UmiAiTrainingTextSpan answer = {36U, 27U};
UmiAiTrainingReviewedExampleEvidence evidence = {0};
char record[512] = {0};
size_t recordLength = 0U;

UmiStatus status = UmiAiTrainingReviewedExampleJsonl(
    &review, originalBytes, originalLength,
    derivativeBytes, derivativeLength,
    question, answer, 20U,
    record, sizeof(record), &recordLength, &evidence);
```

The example's byte offsets apply **only** to the exact fictional derivative shown above. In real data, bytes and Unicode characters may not have one-to-one offsets: a multibyte character requires several UTF-8 bytes. Callers must derive and review offsets against the exact preserved byte sequence, not a visually similar normalised copy.

The API does **not** write `record` or `evidence` to a repository or disk. It reports the output byte length, a SHA-256 of the JSONL line, the original-source partition, and the selected text spans. The caller controls publication and private evidence storage separately. On rejection, all outputs remain unchanged.

## 6. Data quality beyond valid JSON

A model can learn fluent misinformation from perfectly valid JSON. Training-data review should therefore check the accuracy of each answer, uniqueness of the content, consistency of terminology, permission to use it for training, and whether a held-out test set provides a meaningful measure of generalisation.

For code examples, never execute untrusted training-source code as part of extraction. For financial documents, avoid real account numbers, credentials and customer information. For subtitles, verify timing, speaker identity and transcription accuracy; format conversion does not resolve errors already present in the transcript.

Fine-tuning for Umicom Studio, Trader, Bank or TMS must not grant a language model authority to release payments, execute trades, change risk controls or publish documents. Such actions need independent application permissions and human approval.

## 7. Practical questions and answers

1. **A source has a valid SHA-256 but no training-use approval. Admit it?** No. Integrity does not imply rights.
2. **A private chat is transcribed perfectly. Is it ready for public-model training?** No. Privacy, consent, classification and authorised purpose are independent requirements.
3. **Two clips originate from one recording. Can one be training and one evaluation?** Not under the original-asset partitioning rule; both share the same source assignment.
4. **Why keep lineage outside the JSONL example?** To keep model-facing text minimal and permit controlled, separately secured provenance records.
5. **Does JSONL preparation fine-tune a model?** No. Training also requires tokenisation, architecture-compatible loss, optimisation, evaluation and checkpoint management.

**Further study:** [Source verification](verify-reviewable-training-sources.md), [low-rank adaptation](train-a-frozen-projection-with-low-rank-adapters.md), [numerical evidence](../11-maths-for-ai/19-evidence-thresholds-and-uncertainty.md).
