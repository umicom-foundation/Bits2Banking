# Lesson 160 — Verify the browser course and editable lessons together

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation language:** C23

## Learning objectives

Understand the encoding and ownership invariant, follow a concrete example, identify the reusable Framework service and explain a safe failure outcome.

## 1. The engineering problem

A growing educational repository should not force readers to guess where the latest material lives. In Bits2Banking, the HTML course is under `content/courses/llm-from-scratch/`, while editable educational source lives under `content/lessons/10-native-ai/`. Those are different representations of one curriculum, not competing runtime implementations.

A contributor should inspect the relative path of every new HTML lesson, preserve the original Lesson 1–94 pages, keep previous and next links consistent, and ensure examples remain inert. Browser pages must not silently execute code snippets or train a model on documents simply because a lesson contains a command example.

The continuation catalogue collects Lessons 95–160 and links each HTML companion to its Markdown source. Mathematics has a parallel continuation for Units 21–70. Existing course homes, diagrams and brand artwork remain unmodified.

## 2. Use the existing Framework boundaries

A native Framework API, `UmiEducationCourseCatalogueRender`, validates ordered lesson numbers and relative HTML links, escapes HTML-sensitive titles and writes a complete accessible navigation page. That reusable functionality belongs in Framework rather than another app-specific script.

The presence of a catalogue does not prove every destination exists. An additional site link check and human editorial review remain necessary. Verify the course in a browser and run the Framework education tests separately; successful HTML rendering is not evidence that native LLM mathematical tests passed.

## Practice

**Question:** What is the difference between an HTML-renderer test and a native Transformer numerical test?

<details><summary>Reveal the worked answer</summary>

The former checks safe educational navigation and markup. The latter must execute the actual mathematical model and verify shapes, logits, gradients and lifetime contracts.

</details>

## Continue

Return to [tokenisation and context planning](155-plan-tokenisation-before-model-scaling.md), or use [Mathematics Unit 69](../11-maths-for-ai/69-utf8-byte-sequences-and-character-counts.md) for the byte-level arithmetic. Code examples are educational and not automatically executed.

*Service to Many Leads to Greatness.*
