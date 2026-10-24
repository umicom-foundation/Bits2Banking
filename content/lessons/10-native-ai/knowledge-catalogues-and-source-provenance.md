# Supplementary study: Knowledge catalogues, source provenance and AI-training permissions

**Bits2Banking · Native AI**  
**Author:** Sammy Hegab · Umicom Foundation  
**Format:** Markdown teaching note (not a new numbered LLM lesson)

## Why we need this

Suppose Umicom LLM needs to answer a developer's question about a Data Server.
We should be able to identify the Framework documentation and code revision
supporting the answer. Separately, if we later train an AI model using source
material, we must know the right to use each document for that purpose.

One published article can have three connected representations: its editable
Markdown manuscript, its HTML course presentation and the separately authored
video narration. These are **not** necessarily byte-for-byte copies.

## Source, representation and derived draft

- **Source:** an independently identifiable original document, including
  author, licence, revision, origin and classification.
- **Representation:** a presentation of material, such as an HTML lesson.
- **Derivative:** a proposed adaptation, such as a video script or simplified
  example; identify its parents and require review before publishing.

A catalogue describes relationships; it must not silently replace source
content or declare training permissions. A path inventory only says that a
file is expected at that location.

## A worked example

Source `btb:llm:093` has a Markdown manuscript under
`content/lessons/10-native-ai/`, a browser lesson under
`content/courses/llm-from-scratch/` and a separate video script under
`content/videos/scripts/llm-from-scratch/`.

A reader can study the material without requesting a training run. If the
source's `training_permission` is `not_assessed`, a dataset exporter must not
include it, even if the source is available on the public website.

## Three different validation questions

1. **Structural:** Is every expected HTML lesson file present? An inventory
   and read-only C23 file validator can check this.
2. **Educational:** Does the Markdown text accurately and fully explain the
   HTML article? This requires editorial comparison, not just file existence.
3. **Legal/governance:** Is model training allowed? This requires review and
   explicit authorisation, independently of Markdown or HTML link validity.

## Practical exercise

Open [the complete LLM HTML catalogue](../../courses/llm-from-scratch/all-lessons.html)
and follow Lesson 93. Find its Markdown lesson and video script, then inspect
[`knowledge/registries/education-links.json`](../../../knowledge/registries/education-links.json)
from the repository root. State which fields prove a **link**, which prove
**authors' attribution**, and which are still **unreviewed decisions**.

## Follow-up

The Framework's native Knowledge Centre is the proposed long-term owner of
source indexing and retrieval. The education repository owns curated teaching
material and editorial decisions, not a replacement indexing runtime.
