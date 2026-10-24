# Umicom Bits2Banking Knowledge Catalogue — Initial Source Relations

**Owner:** Umicom Foundation · **Author:** Sammy Hegab.

This directory contains **references and governance metadata**, not duplicate articles, model checkpoints, training datasets or a second retrieval engine. Reusable indexing and RAG functionality already exists in **Umicom Framework** under `include/umicom/knowledge/` and `src/knowledge/`.

`registries/education-links.json` is an initial four-record human-reviewed migration register. Stable content IDs link canonical Markdown manuscripts to HTML presentations and video scripts. Its `training_permission: not_assessed` setting is intentional: public publication alone does not confer authority to use material for model training.

## Future controlled ingestion

1. Register original source, revision, author and licence.
2. Verify permissions, data classification, privacy and intended use.
3. Ingest through the existing Framework Knowledge Centre with source citations.
4. Review generated teaching adaptations before publishing any new output.
5. Export a separate, explicitly approved and split training dataset **only after** completing a documented rights and governance review.

This release does **not** ingest files, generate text, re-train a model or change production Framework code. None of the existing source material is deleted by the ZIP.

## Supplementary HTML pathname inventory

[`inventories/course-html-pages.tsv`](inventories/course-html-pages.tsv) lists
all 94 existing LLM and 20 Mathematics HTML pages in a machine-readable format.
It is only a location/coverage inventory. It does not override the stable-ID
relations in `registries/education-links.json` and does not imply publication,
provenance approval, editorial equivalence or AI-training permission.

`schemas/source-record.schema.json` is a proposed metadata contract for
individual original sources, including collection, licence, permission,
classification, provenance and review state. A schema describing fields is
not a cryptographic authenticity check; do not auto-admit a record for
training because it is parseable JSON. Review requirements are documented in
`governance/training-data-admission.md`.
