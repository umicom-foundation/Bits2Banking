# Audit Supervised Training Data Before Any Model Update

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## The difference between text that exists and text we may train on

A PDF, source file, video transcript or web archive may be technically readable without being licensed for model training. A SHA-256 checksum describes byte identity; it is not copyright ownership, privacy clearance or permission to create a derived training dataset. These questions require explicit review.

Umicom separates three jobs: **extracting** approved text from a source, **admitting** reviewed derivatives using the Framework source-admission contracts, and **training** from a verified snapshot. The learning repository contains explanatory material, not private corpora or production ingestion logic.

## The source-group problem

Suppose one synthetic classroom document contains three paragraphs. We produce three prompt/completion examples from different paragraphs. If two enter training and the third enters evaluation, a model may appear good at held-out performance because it has seen highly related passages from the same source. The evaluation is no longer independent.

The Framework's existing `UmiAiTrainingSourceAdmit` assigns a split based on the **original asset digest**. `UmiAiTrainingReviewedCorpusAudit` detects exact duplicate JSONL, identical prepared content in opposing splits and conflicts between derivatives of one source. It does **not** detect every near-duplicate, paraphrase or hidden copy. A human and additional similarity checks are still needed for large real datasets.

## Four acceptance gates

1. **Rights:** document the legal basis and explicit training-use decision; reject materials where training rights are uncertain.
2. **Privacy:** exclude passwords, API keys, personal records, account statements, internal conversation transcripts and material subject to restrictions. Keep approved provenance evidence separate from model-facing text.
3. **Integrity:** verify the SHA-256 of both source bytes and prepared derivative bytes. A changed file is a different candidate, not an automatically updated approved source.
4. **Partition:** prevent the original source and its extracts from leaking across train and evaluation. Maintain separate test material for final independent model assessment.

## The new dataset boundary

`UmiAiTrainingSupervisedDatasetCreate` invokes the full reviewed-corpus audit **before** parsing any record into tokens. `DatasetInspect` returns example counts and the collection's deterministic ordered digest. `DatasetGet` copies a bounded window and its mask. No file paths, prompts or media bytes are printed by these methods.

A report can state that four fictional examples were admitted from four distinct original sources, with two in training and two held out. It **must not** treat those counts as proof of compliance with all possible legal or privacy obligations.

## An exercise in risk identification

A developer downloads a public webpage, runs automatic transcript extraction and adds every paragraph to training. Which gates are missing? The webpage being visible does not prove training-use permission; extraction may be inaccurate; personal information may appear; related paragraphs may leak into evaluation; and a hash without a trusted provenance chain proves no publisher identity.

**Worked answer:** start by obtaining source and rights evidence, reviewing the exact extracted text and redacting/removing disallowed content, computing digests, selecting whole-source partitions and auditing the complete approved collection. Reject or hold back uncertain inputs rather than treating automation as authorisation.

See [the prepared training-window lesson](from-approved-jsonl-to-training-windows.md) and [Framework source provenance principles](knowledge-catalogues-and-source-provenance.md).
