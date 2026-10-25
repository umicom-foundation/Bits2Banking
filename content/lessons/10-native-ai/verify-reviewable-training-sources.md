# Native AI — Verify Reviewed Documents and Media Before Training

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** [Review and prepare documents and media](review-and-prepare-documents-media-for-training.md).

## Learning objectives

Separate an original document or recording from its derived training text; explain why a human-reviewed source needs verified content digests as well as rights approval; apply Framework-owned admission controls; and prevent accidental inclusion of private material in a public dataset.

## 1. Original asset, reviewed derivative and permission

A training pipeline has three separate subjects:

1. **Original asset:** a Markdown manuscript, a document, an authorised recording or image.
2. **Prepared derivative:** vetted UTF-8 text, such as an extracted chapter or reviewed caption transcript.
3. **Permission evidence:** a recorded decision that this specific material may be used for the stated training purpose.

A valid transcript is not automatically licensed for model training. A rights-approved text file may still contain personal information that has not been cleared. A cryptographic digest proves neither permission nor semantic correctness. These controls are complementary rather than interchangeable.

## 2. Never confuse a declared digest with verified bytes

The Framework admission contract accepts textual SHA-256 fingerprints from a reviewed record. But a caller can type any 64-character hexadecimal string. The correct next step is to hash the **actual bytes** through the shared Framework SHA-256 service and compare them to the declared fingerprints.

`UmiAiTrainingSourceVerifyBytes` composes two pre-existing owners:

- `UmiAiTrainingSourceAdmit` decides whether the rights, public/private visibility, personal-data review and extracted-text review permit this source.
- `UmiSha256Buffer` computes the actual digest of the original asset and its prepared text.

The combined operation returns an admitted source only after both gates pass. It does not create another dataset loader, document parser, transcription engine or cryptographic implementation inside Bits2Banking.

## 3. Work through one synthetic source

Suppose a freely licensed, fictional educational recording has a reviewed transcript:

`"Explain two training gradients.\n"`

The recording bytes and reviewed text are kept in separate, controlled input buffers. Compute their hashes using the Framework's canonical SHA-256 implementation. Attach the actual reviewed licence/evidence identifiers and set review flags only after a responsible person has completed those checks.

```c
#include "umicom/base/sha256.h"
#include "umicom/ai/training/source_evidence.h"

char originalHash[UMI_SHA256_HEX_CAPACITY] = {0};
char preparedHash[UMI_SHA256_HEX_CAPACITY] = {0};

/* originalBytes and preparedText are approved, caller-owned buffers. */
UmiStatus status = UmiSha256Buffer(
    originalBytes, originalLength, originalHash);
if (status == UMI_STATUS_OK)
    status = UmiSha256Buffer(
        preparedText, preparedLength, preparedHash);

/* A reviewer must have explicitly authorised the rights and content fields.
 * Filling hashes alone does not satisfy review or establish ownership. */
UmiAiTrainingSourceReview review = {
    .relativeTextPath = "approved/example-transcript.txt",
    .originalAssetSha256 = originalHash,
    .preparedTextSha256 = preparedHash,
    .licenceId = "CC0-1.0",
    .rightsEvidenceId = "reviewed-example",
    .medium = UMI_AI_TRAINING_SOURCE_VIDEO_TRANSCRIPT,
    .visibility = UMI_AI_TRAINING_SOURCE_VISIBILITY_PUBLIC,
    .rightsReviewed = 1,
    .trainingUseApproved = 1,
    .personalDataReviewed = 1,
    .extractedTextReviewed = 1
};

UmiAiTrainingAdmittedSource admitted = {0};
if (status == UMI_STATUS_OK)
    status = UmiAiTrainingSourceVerifyBytes(
        &review, originalBytes, originalLength,
        preparedText, preparedLength, 20U, &admitted);
```

All names here are **synthetic teaching examples**. Do not set approval flags for actual material until the decisions and evidence really exist. A source marked private or not approved for training must be refused even if its SHA-256 is correct.

## 4. Avoid leakage across train and evaluation sets

The Framework's existing admission rule chooses the training/evaluation partition from the **original asset fingerprint**, not from each prepared text chunk. This helps keep identical originals together: two caption extracts of the same source should not appear on opposite sides of an evaluation split.

This does **not** detect all near-duplicates, excerpts, translated copies, shared topics or covert repetition. Before model evaluation, review source families, duplicate chapters and derived documents together, then inspect whether held-out material genuinely tests new behaviour.

The current native dataset-manifest loader remains bounded and requires its own safety assumptions about trusted local filesystem inputs. The admission decision does not magically sandbox arbitrary paths or independently prove a licence.

## 5. What about audio, video, images, PDF and DOCX?

The Framework already has a shared Creative Workspace caption service that parses a documented subset of SRT and WebVTT. The existing `caption_text` adapter produces **text from already-reviewed captions**, not audio speech recognition. A future approved speech-to-text provider must have its own explicit provenance, confidence, human verification and privacy rules.

Likewise, PDF/DOCX extraction should reuse Framework document adapters and distinguish source text from OCR guesses, tables, images, sidebars and page order. Image captions must not be treated as authoritative facts merely because a model produced them.

Private manuscripts, personal communications, confidential financial files, account credentials, confidential operational records and unpublished research must not be copied to public learning repositories or automatically used for training.

## 6. Verify the gates

The Framework-focused CTest `framework.ai.adaptation.source_evidence` tests approved synthetic inputs, changed prepared bytes, incorrect digests, rejected private visibility, missing review flags and failure-atomic outputs. The result is a **content-integrity and admission gate**, not a universal personal-data detector, digital-rights investigator or near-duplicate classifier.

## Practise and check

**A.** The transcript bytes change, but their recorded SHA-256 does not. What should happen?  
**Answer.** Verification refuses admission because the computed digest no longer matches the reviewed derivative identity.

**B.** A recording has valid hashes but no training-use permission. Is it eligible?  
**Answer.** No. Integrity does not confer rights or bypass the source-admission gate.

**C.** Why should two derivatives of one recording remain in the same dataset partition?  
**Answer.** Otherwise closely related text may leak from training into evaluation and overstate model generalisation.

**Key lesson:** Training starts only after authorised review, actual-byte verification and a defensible evaluation split. The original source stays under its rightful owner's control.
