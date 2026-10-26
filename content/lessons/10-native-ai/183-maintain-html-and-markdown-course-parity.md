# Lesson 183 — Maintain HTML And Markdown Course Parity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Preserve both forms of the course and make new lessons discoverable.

## 1. The engineering question

Under `content/lessons/10-native-ai/`, Markdown remains the editable manuscript. Under `content/courses/llm-from-scratch/lessons/`, the corresponding HTML is the browser edition. New entries belong in the continuation catalogue and lesson index, without discarding the original HTML pages or diagrams.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

A broken relative link makes a lesson inaccessible even when its HTML file exists. A complete review checks that every new numbered Markdown path has exactly one matching HTML companion, that both indexes point to the right filename, and that prev/next navigation resolves.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

Use the existing Framework `UmiEducationCourseCompanionsAudit` and the native HTML catalogue/navigation components. Editing the curriculum is not a reason to introduce another publishing engine inside Bits2Banking.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** Why would replacing a 29 KB historic course homepage with a three-line “new course” page be a destructive change?

<details><summary>Reveal the worked answer</summary>

The replacement would discard the old navigation, brand marks, historical content and links. A source-preserving merge adds discovery while retaining the original complete page.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/90-design-independent-regression-evidence.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/183-maintain-html-and-markdown-course-parity.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
