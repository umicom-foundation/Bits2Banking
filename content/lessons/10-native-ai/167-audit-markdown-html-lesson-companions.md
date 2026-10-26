# Lesson 167 — Audit the HTML Course Against Editable Markdown Lessons

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23, mathematics and accessible explanation

> **Learning objective:** Understand why the html and markdown trees represent two views of one curriculum and use the framework-owned audit to detect broken coverage.

## 1. Start with the engineering problem

Bits2Banking maintains editable manuscripts under `content/lessons` and learner-friendly pages under `content/courses`. Either tree can advance independently if an editor forgets to publish a companion. Rather than writing a new Python site script into the public repository, we can ask the native Framework to inspect both directories and report missing numbered pages and differently named companions.

Do not confuse three different outcomes: a calculation that is mathematically permitted, a program that is compiled, and a program that has passed an independent numerical qualification. An assumption used for planning can be valuable without yet being an implemented runtime feature.

## 2. Work through the calculation

If the LLM continuation includes ordinal numbers 95 through 168 inclusive, the expected count is `168−95+1 = 74`. A complete set has one numbered Markdown manuscript and one corresponding HTML lesson for each ordinal. The two basenames should share their numeric prefix and meaningful slug. Supplementary notes, images and special historical lesson suffixes remain separate; a simple pairing audit must not delete or renumber them.

The crucial questions are **which positions remain unchanged**, **which history each layer contains**, and **which observations the implementation has actually measured**. Record the assumptions before interpreting a counter or timing number.

## 3. Inspect the existing Framework boundary

```c
#include "umicom/education/course_companions.h"
UmiEducationCourseCompanionReport report = {0};
UmiStatus status = UmiEducationCourseCompanionsAudit(
    repositoryRoot, UMI_EDUCATION_COURSE_NATIVE_AI,
    95U, 168U, &report);
/* status==OK means the inspection ran; inspect the missing/mismatch
 * counts separately before approving publication. */
```

The C23 excerpt illustrates a **Framework-owned interface or validation scenario**. It is not a substitute for creating the surrounding model, verifying argument lifetimes and checking every return status. The compiled implementation belongs to `Umicom-Applications/framework`; this repository stores its educational explanation.

## 4. Qualification and review checklist

1. Check both new and original lesson directories; never equate a missing HTML file with permission to discard a Markdown manuscript.
2. Treat status code and report counts as different evidence: the filesystem scan can succeed while lessons remain missing.
3. A filename pairing does not prove that all examples are accurate or all links work; native site and editorial checks remain required.

### Why these checks matter

The native companion audit matches canonical numeric filenames and slugs. It is not a full HTML parser, YAML parser or copyright approval service; it performs no writes.

For financial applications, training quality and generated-code confidence must remain separate from authorised transaction processing. Educational AI output must not be executed, treated as a trusted trading signal, or used to bypass treasury controls.

## 5. Practice and reveal the worked answer

**Question:** What should happen if Unit 73 exists as Markdown but its HTML companion is missing?

<details>
<summary>Show the worked answer</summary>

The scan should complete and report one missing HTML companion. The Markdown source must be retained; the publication gap should be corrected without deleting or renaming it.

</details>

## 6. Connect to the next idea

Read [Mathematics for AI Unit 77 — Calculate Complete HTML and Markdown Course Coverage](../11-maths-for-ai/77-calculate-html-and-markdown-coverage.md) for a slower explanation of the numerical steps. Compare the original native Framework API declarations before reusing an example in an application. A successful educational build does not imply completed model validation.

[Previous: Lesson 166](166-measure-cache-memory-work-and-time-separately.md) · [Next: Lesson 168](168-integrate-html-course-navigation-without-data-loss.md)

*Service to Many Leads to Greatness.*
