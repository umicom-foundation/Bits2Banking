# Prepare Documents and Media for Responsible LLM Training

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Implementation authority:** Umicom Framework

## Why data preparation is part of model engineering

A language model consumes sequences of token IDs. Books, PDFs, spreadsheets, audio recordings, video and images do not arrive in that form. They must be extracted or described, checked and converted into reviewed textual or multimodal training representations. A model that learns from a corrupted transcript, duplicated document or unauthorised source may give misleading results, leak personal information or violate content rights.

**Permission to view a document is not automatically permission to train on it.** A public URL or a copied file does not establish training rights. Keep private correspondence, confidential projects, personnel messages, credentials, personal records and internal AI agent instructions out of public educational repositories and public training datasets.

## A simple preparation pipeline

```text
Candidate source
  → Confirm origin, rights, permissions and privacy classification
  → Extract text or reviewed transcript/caption using an approved provider
  → Inspect completeness, encoding, layout, language and personal-data risk
  → Record original-asset digest and extracted-text digest
  → Human editorial approval for training use
  → Partition by ORIGINAL asset identity, before dividing into samples
  → Use Framework dataset manifest and tokenizer
  → Train on admitted sources; evaluate on independent held-out sources
```

The approval boundary precedes dataset construction. The current Framework supports byte tokenisation, trusted local dataset manifests and a native Transformer teaching model. Its Knowledge Centre already supplies provenance-preserving text chunking for retrieval. Model training and retrieval are distinct activities: indexed information is not thereby approved as training data.

## What to extract from each source type

| Source | Typical reviewed representation | Main quality risks |
| --- | --- | --- |
| Markdown or plain text | UTF-8 text with headings and source identity | Duplicate files, code blocks with credentials |
| PDF or DOCX | Extracted reading-order text and structural references | Missing tables, headers mixed into paragraphs, scanned pages |
| Source code | Exact licensed files with language, revision and repository identity | Private APIs, secrets, mixed licences |
| Audio | Timestamped speech transcript plus language and speaker boundaries when permitted | Transcription errors, speakers not consenting, omissions |
| Video | Reviewed speech transcript and selected captioned visual events | False visual descriptions, missing context, copyright |
| Image | Explicitly reviewed caption or a supported multimodal representation | Speculative captions, licensing and personal-information exposure |

For a **text-only decoder**, raw pixels or sound samples are not valid training text. A reviewed transcript or caption is a *derivative* of the original media. Building a native multimodal encoder, image processor or speech model is a separate engineering task and cannot be claimed by an admission manifest alone.

## Original identity and extracted-text identity

Suppose one permitted recording produces both a transcript and caption notes. They are two prepared text sources derived from the **same original asset**. Assigning their train/evaluation partitions independently could leak nearly identical material into both groups.

The Framework admission contract therefore stores two SHA-256 identifiers:

- `originalAssetSha256`: hash of the original source bytes, used to group derivatives into the same split.
- `preparedTextSha256`: hash of the exact reviewed text derivative, so different transcription revisions can be distinguished.

Both hashes must be calculated and verified using the Framework's existing cryptographic service before admission. An arbitrary digest written into a record is not proof that the content matches it. Near-duplicates from different original assets still require explicit detection and editorial review.

## Admit reviewed text to the native dataset manifest

`umicom/ai/training/source_admission.h` defines a C23 metadata gate. It rejects unapproved training use, restricted or private visibility, missing rights evidence, invalid digests or unsafe source-relative paths. Extracted document/media text also requires explicit review. The output is a small manifest record; the operation does not read private files or launch converters.

```c
#include "umicom/ai/training/source_admission.h"

/* Synthetic teaching identifiers: no personal or private records. */
const char original[] =
    "0000000000000000000000000000000000000000000000000000000000000000";
const char prepared[] =
    "0000000000000040000000000000000000000000000000000000000000000000";

UmiAiTrainingSourceReview review = {
    .relativeTextPath = "reviewed/example.txt",
    .originalAssetSha256 = original,
    .preparedTextSha256 = prepared,
    .licenceId = "CC-BY-4.0",
    .rightsEvidenceId = "licence-review",
    .medium = UMI_AI_TRAINING_SOURCE_DOCUMENT_TEXT,
    .visibility = UMI_AI_TRAINING_SOURCE_VISIBILITY_PUBLIC,
    .rightsReviewed = 1,
    .trainingUseApproved = 1,
    .personalDataReviewed = 1,
    .extractedTextReviewed = 1
};
UmiAiTrainingAdmittedSource accepted = {0};
UmiStatus status = UmiAiTrainingSourceAdmit(&review, 20U, &accepted);
```

The example's digests are **placeholders for an API demonstration**, not cryptographic evidence of any real file. A production caller must use actual verified source hashes and human-reviewed rights records. After admission, `UmiAiTrainingSourceManifestLine` produces either `train reviewed/example.txt` or `eval reviewed/example.txt`. The existing `UMICOM-AI-DATASET-1` parser remains the authority that loads the full, already-reviewed manifest and source files.

## Prevent leakage and unreliable training

A useful acceptance review asks four separate questions:

1. **Legal and privacy:** Does the proposed use have an appropriate right or licence? Has personal data been removed or lawfully handled, and is the review recorded?
2. **Technical fidelity:** Did extraction preserve reading order, equations, labels and meaningful timestamps? Are important sections missing?
3. **Evaluation isolation:** Were all versions of one original source assigned together? Are near-identical publications and quoted passages kept out of held-out evaluation?
4. **Operational integrity:** Does the content digest match the bytes we are actually tokenising? Can we reproduce the model run from its reviewed manifest and fixed settings?

Fine-tuning data, reinforcement-learning preferences and retrieval documents may have different permissions and purposes. Permission needs to be recorded for the actual intended use, not inferred from a file extension.

## What the implementation does not yet do

The admission layer does not decode DOCX/PDF, run speech recognition, detect faces, remove personal information automatically, calculate SHA-256 itself, transcribe video or train a model. These responsibilities belong to reusable Framework extractors, privacy/redaction services, existing hash utilities and established model-training APIs, with explicit tests. Do not present metadata admission as a completed multimodal ingestion system.

## Exercises

**1.** Why must two transcriptions of one recording share a train/evaluation split?  
**Answer:** They may repeat the same content. Keeping derivatives together reduces direct source leakage.

**2.** Can a public-domain declaration in a random file be trusted automatically?  
**Answer:** No. Provenance, permission and the authority of the declaration require review.

**3.** What is the difference between generating a Markdown transcript and training a model?  
**Answer:** Extraction creates source material; training changes neural parameters using approved token sequences and an optimiser.

**4.** Should internal development messages be copied into a public example dataset because they mention Umicom?  
**Answer:** No. Technical relevance does not override privacy or authorisation.

## Next steps in the learning path

Explore the [low-rank fine-tuning lesson](low-rank-adaptation-and-fine-tuning.md), the existing `dataset_manifest.h` and `byte_tokenizer.h` APIs, and the Knowledge Centre's provenance-aware `chunker.h`. Use only reviewed public or explicitly licensed synthetic teaching material for repository fixtures.
