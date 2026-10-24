# Bits2Banking — HTML course catalogue and knowledge inventory batch

**Repository:** `umicom-foundation/Bits2Banking`  
**Reviewed source:** `d8e176c51a2aef9be65cd26e41b5904f07dd8cae`  
**Maintainer:** Sammy Hegab · Umicom Foundation  
**Implementation and documentation:** native C23 validation, Markdown, HTML, JSON

## What is delivered

- `content/courses/llm-from-scratch/all-lessons.html` presents the complete
  **94** existing LLM HTML lesson links in six readable sections.
- `knowledge/inventories/course-html-pages.tsv` inventories **94 LLM** pages and
  **20 Mathematics** HTML pages from the reviewed Git tree.
- `tests/content_integrity/` provides read-only *test-only* C23 structural
  validation of inventory order, presence, path safety and migrated lessons.
- Existing complete course and knowledge README files gain append-only
  explanations of the new resources; legacy text is preserved.
- New supplementary Markdown teaching and narrated video material describe
  source provenance and the separation of retrieval versus training rights.

## Deliberate preservation constraints

- `content/courses/llm-from-scratch/index.html` and `course-map.html` are **not
  overwritten**; the original pages still list only 1–68. The new catalogue
  makes 1–94 directly accessible now without compromising those originals.
  A later authorised full-file navigation update should integrate it directly.
- `content/courses/maths-for-ai/index.html` already covers all 20 units and
  remains unchanged.
- Original HTML lesson bodies, the Framework and every video script are unchanged.
- All original duplicate Markdown paths were already removed in the preceding
  cleanup commit, so **this release requires no deletions**.
- Inventory membership is not semantic accuracy, verified provenance, RAG
  ingestion, legal rights or training permission.

## Acceptance workflow

1. Compare this ZIP with the local repository in Beyond Compare. Merge **new
   and modified files only**; never synchronise deletions from sparse archives.
2. Build `tests/content_integrity/` using GCC/Clang C23 with CMake and Ninja.
3. Run CTest for the real repository paths; the test reads local files only.
4. Confirm browser catalogue links and the existing 20-unit mathematics index.
5. Commit and push the Bits2Banking repository to `main`. No Framework or
   Applications commits are required.

## Next milestones

1. Additive full-file update of LLM HTML `index.html` and `course-map.html`.
2. Review and prepare full, unabridged Markdown counterparts for older
   HTML-only lessons; don't invent or discard authored material.
3. Extend content IDs and editorial review metadata across all lesson types.
4. Build a Framework-owned native ingestion adapter and consent-controlled
   dataset export gate, with tests against denied/unassessed sources.
