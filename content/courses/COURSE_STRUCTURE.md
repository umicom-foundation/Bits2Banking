# Umicom Bits2Banking — Course directory convention

**Owner:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT.

The parent `content/courses/` holds independently navigable learning courses.
`index.html` is the learner-facing catalogue. `assets/umicom-learning.css` is
shared by all HTML courses, while each course may own explanatory diagrams.

Active:
- `llm-from-scratch/` — 42 interconnected HTML pages and twelve SVG diagrams.

Future courses should adopt stable descriptive paths such as:
- `programming-fundamentals/`
- `c23-programming/`
- `cpp-programming/`
- `assembly-programming/`
- `blockchain/`
- `umicom-framework/`
- `treasury-management/`
- `calypso-development/`

Do not create empty directories or pages for unpublished courses.

## Preservation and ownership

Do not delete or rename the original Markdown lessons under
`content/lessons/`. The Framework remains the authority for native training
mathematics and runnable C23 examples. The visual course contains no alternate
model runtime. All official branding lives in `content/assets/branding/` and
is copied byte-for-byte from `Umicom-Applications/framework/resources/brand/`.
No downloaded fonts, tracking scripts or external frameworks are required.

Before publishing, merge this directory, ensure the approved official SVGs
are installed, check all relative links and inspect the result in a browser.
`mkdocs.yml` and the production publishing workflow are intentionally left
unchanged until the combined site navigation can be reviewed without risking
existing books and published lessons.

## Current course inventory — additive clarification

The older "42 interconnected HTML pages" description above records the initial
course release, not the current page count. At the reviewed revision, the
repository contains 94 numbered LLM HTML lessons and 20 Mathematics for AI
HTML units. The active course folders are `llm-from-scratch/` and
`maths-for-ai/`.

- **Canonical written lessons:** `content/lessons/<subject>/*.md`
- **Browser course:** `content/courses/<course>/lessons/*.html` plus its
  existing assets, style and course navigation.
- **Video production:** `content/videos/scripts/<course>/*.md`
- **Source relations and inventory:** `knowledge/`; administrative metadata
  is allowed, but no copied article text or unrestricted training corpus.

The complete 94-lesson browser catalogue is
[`llm-from-scratch/all-lessons.html`](llm-from-scratch/all-lessons.html).
Course index and map pages are preserved pending a separate full-file review.
