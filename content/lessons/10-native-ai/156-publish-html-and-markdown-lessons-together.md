# Lesson 156 — Keep Markdown manuscripts and the browser course consistent

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Native C23 and AI engineering.

## Learning objectives

Understand the core engineering invariant, work through a bounded example, identify what Umicom Framework already implements and distinguish verified facts from proposed improvements.

## 1. The idea from first principles

Bits2Banking has two complementary educational forms. The editable Markdown manuscript is kept under `content/lessons/10-native-ai/`. The browser-friendly course is under `content/courses/llm-from-scratch/lessons/`. A new learner may start from the course home and choose an illustrated HTML lesson; a contributor may edit the corresponding Markdown manuscript and preserve its source references.

Never replace a reviewed Markdown manuscript merely to publish an HTML companion. A static HTML page must also keep code fences escaped, links relative to the course folder and expandable worked answers keyboard accessible. The browser must not execute training commands simply because a lesson prints a code example.

This pathway deliberately extends the existing course while preserving its earlier 94 HTML lessons, original diagrams, course home and course map. New lesson pages carry local forward/back links and an additional continuation catalogue; no existing brand artwork is changed.

## 2. Connect the lesson to Umicom Framework

The Framework's native `UmiEducationCourseCatalogueRender` validates an ordered set of reviewed titles and relative HTML paths, escapes sensitive characters and emits a deterministic, accessible catalogue document. Actual lesson manuscripts and the published HTML remain Bits2Banking-owned content.

This is an additive education capability: it does not replace the existing `umicom-education` site verification, MkDocs process or original course navigation. Source-to-HTML fidelity should be reviewed by comparing headings, worked calculations, links and practical exercises.

## 3. Practice

**Question:** Why is a successful HTML file render not sufficient evidence that every lesson link works?

<details><summary>Reveal the worked answer</summary>

Rendering proves that markup can be produced, but a separate link/inventory check must verify that the referenced HTML files exist at the relative paths used by the site.

</details>

## Further reading

Review [the multi-layer inference lesson](148-build-and-qualify-native-stacked-inference.md), [the introduction to the stacked decoder](121-build-a-real-multi-layer-transformer.md) and [the mathematics companion](../11-maths-for-ai/stacked-inference-mathematics.md).

*All numerical examples are educational; no model-generated source or financial transaction is executed. Service to Many Leads to Greatness.*
