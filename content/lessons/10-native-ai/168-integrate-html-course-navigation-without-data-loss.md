# Lesson 168 — Integrate Course Home Navigation Without Losing Source Material

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23, mathematics and accessible explanation

> **Learning objective:** Review complete, source-preserving homepage updates and distinguish staged files from modifications to the original repository.

## 1. Start with the engineering problem

Long course maps contain historical design, links, branding and author credits. A rewrite that keeps only the latest lessons may silently destroy those assets. An educational site needs discoverable continuation navigation, but it also needs a reversible, auditable publishing workflow. The Framework therefore composes a small accessible link into the existing complete HTML and stages the resulting full document for comparison.

Do not confuse three different outcomes: a calculation that is mathematically permitted, a program that is compiled, and a program that has passed an independent numerical qualification. An assumption used for planning can be valuable without yet being an implemented runtime feature.

## 2. Work through the calculation

Open the original `content/courses/llm-from-scratch/index.html` containing Lessons 1–68. The longer continuation catalogue at `advanced-lessons.html` provides later pages through Lesson 168. The native composer locates the original `<main>` opening tag, inserts one labelled continuation link, and copies all other original bytes in order. If that exact link is already present, a repeat call returns the same page rather than adding a second banner.

The crucial questions are **which positions remain unchanged**, **which history each layer contains**, and **which observations the implementation has actually measured**. Record the assumptions before interpreting a counter or timing number.

## 3. Inspect the existing Framework boundary

```c
#include "umicom/education/course_home_link.h"
/* original and result are independently owned buffers. */
UmiStatus status = UmiEducationCourseHomeLinkCompose(
    original, originalLength, "advanced-lessons.html",
    "Continue the complete native LLM course",
    result, resultCapacity, &resultLength);
/* Review the FULL staged HTML file before replacing a published page. */
```

The C23 excerpt illustrates a **Framework-owned interface or validation scenario**. It is not a substitute for creating the surrounding model, verifying argument lifetimes and checking every return status. The compiled implementation belongs to `Umicom-Applications/framework`; this repository stores its educational explanation.

## 4. Qualification and review checklist

1. Run the native staging executable with an explicit output folder; it refuses to overwrite existing staged documents.
2. Compare the generated full `index.html`, `course-map.html` and maths `index.html` against their original sources using Beyond Compare.
3. Check branding, original links and author credit remain in the same order; a successful local staging run is not a public-site publication.

### Why these checks matter

The composer accepts reviewed local HTML documents; it does not sanitise arbitrary remote HTML. The tool does not automatically replace the original, run MkDocs or commit any Git repository.

For financial applications, training quality and generated-code confidence must remain separate from authorised transaction processing. Educational AI output must not be executed, treated as a trusted trading signal, or used to bypass treasury controls.

## 5. Practice and reveal the worked answer

**Question:** Why stage a complete HTML document rather than rewriting the original course home immediately?

<details>
<summary>Show the worked answer</summary>

Staging preserves the original as the source of truth for review. A contributor can compare the complete proposed document, verify that only one navigation element was added and decide whether to merge it.

</details>

## 6. Connect to the next idea

Read [Mathematics for AI Unit 78 — Calculate Source-Preserving HTML Output Capacity](../11-maths-for-ai/78-calculate-source-preserving-html-output-capacity.md) for a slower explanation of the numerical steps. Compare the original native Framework API declarations before reusing an example in an application. A successful educational build does not imply completed model validation.

[Previous: Lesson 167](167-audit-markdown-html-lesson-companions.md) · [Return to the native AI lesson index](index.md)

*Service to Many Leads to Greatness.*
