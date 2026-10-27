# AI Research Frontiers — Lesson 05: Multimodal corpus extraction, lineage and lawful reuse

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Research foundations and practical systems comparisons

## What this topic investigates

A multimodal research corpus may include DOCX, PDF, HTML, C23 source, audio, video frames and structured financial documents. Extraction should preserve headings, code fences, tables, timestamps and source rights rather than converting everything to one untraceable string.

Distinguish a model architecture, an optimisation algorithm, an execution kernel and a dataset pipeline. Each operates at a different layer of the system and should be evaluated against its own fit-for-purpose baseline rather than combined into a single untestable claim.

## Worked example

A one-minute instructional video can yield audio/transcription segments and aligned frames. A training example should identify the source file/revision, time interval, rights and approved objective. It must not include confidential banking statements merely because an editor can open them.

## Practical research exercise

Compare two document-to-model paths: RAG that retrieves current authorised pages, and curated SFT that trains a model to answer in a particular style. Use separate training/validation/test splits by document/source. Apply secrets/PII scans and an independent licence review before any model training.

For a reproducible result, fix the model/dataset revision, precision, hardware, source permissions and measurement conditions. Report both the primary metric and at least one limitation. The existing Umicom Framework owns reusable C23 maths, model interfaces, provenance and approval services; an application must reuse them rather than fork an equivalent implementation.

## Self-assessment

**Question:** Why is a page number or video timestamp useful even after tokenisation?

<details><summary>Reveal the explanation</summary>

It supports source attribution, error investigation, rights review and recovery of the original context.

</details>

## Research starting points

- [Docling project: document extraction](https://github.com/docling-project/docling)
- [DataComp-LM — controlled data curation](https://arxiv.org/abs/2406.11794)

## Related courses

[Advanced native LLM research](../10-native-ai/389-govern-multimodal-training-data-before-distribution.md) · [Distributed Learning introduction](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
