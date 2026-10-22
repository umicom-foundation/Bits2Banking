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
