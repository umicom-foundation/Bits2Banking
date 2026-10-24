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
