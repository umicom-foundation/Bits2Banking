# Training-data admission policy — Umicom Bits2Banking

**Owner:** Umicom Foundation · **Status:** proposed operational gate · **Author:** Sammy Hegab.

## Distinguish three purposes

1. **Reading/publishing:** a course page is presented to a student.
2. **RAG/retrieval:** approved text is indexed as attributable evidence for a question.
3. **Model training:** authorised material is used to alter learned model parameters.

These are separate grants. A public GitHub file, permissive repository badge or
successful HTML build does not, without appropriate rights review, establish
that every document or embedded contribution may be used for training.

## A source is not training-eligible until all requirements are met

- Attribute the creator and preserve the original source URI and exact revision.
- Identify copyright, licence and contribution conditions, including images,
  embedded data, generated material and quoted third-party text.
- Review source sensitivity. Remove secrets, credentials, personal records and
  any confidential/proprietary financial or customer information.
- Obtain and record explicit approval for the intended use. The state
  `not_assessed` or `pending_review` means **do not export**.
- Record immutable digest and, where available, original-source signatures.
- Deduplicate near-identical documents and divide by original source rather
  than by adjacent windows. Reserve validation and test material from training.
- Record dataset revision, exact file list and partition, rights review,
  extraction/normalisation process, and evaluation evidence.
- Re-check new revisions; approval of one revision is not automatic approval
  of every edited descendant.

## Existing Framework reuse

`Umicom Framework/include/umicom/knowledge/` and corresponding C23 sources
already provide collections, sources, chunking, ingestion, retrieval and
citations. Training has a separate `ai/training/dataset_manifest.h`.
A reviewed adapter should link these services without duplicating their logic
inside an education repository.

Existing native training manifests are limited teaching contracts and should
not be treated as a scalable unbounded ingestion engine. Keep public data
separate from internal/private sources. This batch supplies only an inventory
and schema; it does **not** ingest documents or train models.

## Review decision

A training dataset export must explicitly return a negative result when any
source has an unreviewed or denied training permission, missing provenance,
misclassified privacy, unsupported licence, or ambiguous evaluation split.
Decisions must be auditable without storing restricted original content in
public repositories. Human editorial approval is required for AI-authored
lessons or video scripts before publication.
