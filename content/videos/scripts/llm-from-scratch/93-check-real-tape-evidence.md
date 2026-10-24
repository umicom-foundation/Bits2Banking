# Video Script — Real evidence versus an unexecuted test

**Series:** Bits2Banking | **Author:** Sammy Hegab | **Format:** narrator + visual storyboard | **Recording status:** script only (no video produced)

## Intended audience
Newcomers from any background. Explain all mathematical symbols before displaying a full formula. Use clear UK English. Do not use childish greetings or irrelevant demonstrations.

## Script and on-screen direction
Opening [0:00–0:30] — Show a test explorer panel with three categories: not run, failed, passed. Narrator: “Green output alone is not proof that a neural training implementation is correct. Let us ask what was actually executed.”

Concept [0:30–2:20] — Draw two columns marked analytical gradient and independent numerical gradient. Use 0.0234 and 0.0231, subtract to obtain 0.0003. Explain the absolute-value signs and the tolerance of 0.0008 without assuming any prior calculus.

Application [2:20–4:00] — Present the three actual Umicom regressions: gradients, memory budget, rewind. Explain that a failed or missing test blocks acceptance, even if two passed. Demonstrate the new C23 evidence interpreter with visibly labelled “illustrative fixture” values. Do not present those values as real test results.

Review [4:00–5:00] — Ask viewers to distinguish running a test from interpreting its outcome. On-screen links: Maths Unit 19, LLM Lesson 93, source test file.

## Production notes
Use captions, high-contrast readable fonts, pauses after each numerical step and a static summary card. All examples use the same verified arithmetic as the companion HTML and Markdown lesson.
