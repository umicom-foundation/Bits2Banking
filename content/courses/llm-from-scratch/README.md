# Build an LLM from Scratch — Umicom Bits2Banking

**Owner:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT.

Open `content/courses/llm-from-scratch/index.html` in your browser.
The 42 original authored HTML pages and twelve course-owned educational SVGs
are preserved with their relative navigation updated for the new location.

Official logo artwork is **not recreated or modified**. The masthead uses the
canonical `content/assets/branding/umicom-icon-on-dark.svg` and typesets
`umicom` in the Framework's documented system font stack. The favicon is the
canonical `umicom-icon.svg`. Use the unchanged approved masters from
`Umicom-Applications/framework/resources/brand/` to populate the shared
Bits2Banking branding directory if necessary.

`content/courses/assets/umicom-learning.css` is the course-shared stylesheet;
new courses should reuse it instead of maintaining parallel style systems.
`assets/diagrams/` remains local to this course: those are teaching diagrams,
not logos. No external CSS, JavaScript, images or fonts are required.

The original Markdown chapters remain untouched at `content/lessons/10-native-ai/`.
Do not delete them when migrating. The HTML is a learner-friendly presentation
of the existing curriculum, not another native model implementation.


## New guided C23 specialist learning path

Lessons 20–25 explain source byte tokenisation, next-token windows, file-level
evaluation, reviewed training plans, checkpoint evidence and trustworthy
programming benchmarks. The six Markdown sources are under
`content/lessons/10-native-ai/` and the linked HTML pages are under
`content/courses/llm-from-scratch/lessons/`. The browser course does not
execute code; learners use the existing Framework-native tools when their
local security environment has been reviewed.

The course's `assets/` are self-contained, including an officially derived
Umicom vector mark. Framework remains the authoritative logo and learning
runtime owner. See `../assets/branding/README.md`.

## Complete catalogue and current source inventory (24 October 2026)

The original 42-page design history above is preserved. The current reviewed
Git tree contains **94 numbered LLM HTML lessons**. Start at
[the complete Lesson 1–94 catalogue](all-lessons.html) for the entire reading
path; the original [course home](index.html) and [course map](course-map.html)
currently expose only Lessons 1–68 and are kept byte-for-byte unchanged in
this additive release. Their full navigation integration remains a separate,
source-preserving follow-up; the new catalogue closes the immediate discovery
gap without shortening either original document.

The machine-readable pathname inventory is
`knowledge/inventories/course-html-pages.tsv` at the repository root. It is a
path listing, **not** a claim that the listed pages have reviewed Markdown
manuscripts, or that any material is authorised for AI training.

The four relocated Markdown lessons (LLM 93–94; mathematics 19–20) are already
committed under `content/lessons/` and the four old copies have been removed.
This batch does **not** recreate old files, rename any lesson, or change their
HTML content. A test-only native C23 inventory validator is available under
`tests/content_integrity/`.
