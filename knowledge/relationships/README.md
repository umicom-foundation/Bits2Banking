# Bits2Banking educational representation relationships

**Owner:** Umicom Foundation · **Author:** Sammy Hegab · **Status:** pending human review.

This directory holds metadata about relationships among existing canonical
Markdown, learner-facing HTML, video scripts and source evidence. It does not
hold duplicated manuscript text, training corpora or a second Knowledge Centre.

## Batch 03 relationship inventory

`lesson-source-coverage.tsv` is produced locally by the native C23 staging
utility at `tools/course_navigation_stage.c`. The generated table enumerates
all 94 numbered Native LLM HTML lessons and 20 Mathematics for AI HTML units,
using the already-reviewed path inventory at
`knowledge/inventories/course-html-pages.tsv`.

The table records whether a matching canonical Markdown pathname exists in the
*actual local checkout*. A present pathname is **not** a verified content
relationship, approved source, evidence of authorship, legal rights review or
training-data permission. A missing Markdown pathname is left blank; the
existing HTML lesson is not discarded or reconstructed by guessing.

The special-case published LLM Lesson 61 HTML slug is longer than its existing
Markdown slug; the reader and validator account for that known difference.

In the upstream revision reviewed for this batch, 66/114 numbered HTML lessons
had a canonical Markdown counterpart by lesson number; 48 were HTML-only.
The HTML-only LLM lessons were 63–92 and Mathematics units were 1–18.
Those gaps require a separate editorial recovery effort using the original
source material. Counts may differ in your local checkout; inspect the generated
register and never automatically backfill manuscript text from HTML.

### Editorial admission rules

All records are marked `human_review_required` and
`training_permission=not_assessed`. Before promoting an educational relation
from a pathname candidate to an approved record, establish the original author,
licence, exact source revision, trustworthy provenance and editorial equivalence.
AI training permissions require separate explicit decisions under
`knowledge/governance/training-data-admission.md`.

The Framework-owned Knowledge Centre and native training manifest remain the
implementation authorities. This TSV is proposed metadata for a future
Framework ingestion adapter, not an independent ingestion implementation.
