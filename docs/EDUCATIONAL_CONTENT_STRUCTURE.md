# Bits2Banking Educational Content Structure

**Owner:** Sammy Hegab · Umicom Foundation · **Status:** active directory policy.

## Directory owners

| Directory | Content | Allowed formats |
| --- | --- | --- |
| `content/lessons/<subject>/` | Editable primary teaching manuscripts, chapter indexes | Markdown (`.md`) |
| `content/courses/<course>/` | Complete published HTML course, navigation, illustrations, styles | HTML, CSS, SVG, course-level README/metadata |
| `content/videos/scripts/<course>/` | Narration, on-screen instructions, filmed examples | Markdown (`.md`) |
| `knowledge/registries/` | Stable IDs, relationships and rights-review status | Machine-readable metadata; no copied private text |
| `dropzone/` | Original contributor materials and reviewed incoming manuscripts | Original formats retained |
| `output/` | Generated deliverables | Not authoritative sources |

### Migration exception

The existing course-level README and roadmap Markdown files are **administrative metadata** and are not teaching manuscripts. Existing historical HTML course catalogues are retained. The previous four lesson manuscripts inside `content/courses/` are copied and corrected under `content/lessons/` before the user explicitly deletes their old tracked paths.

**Do not shorten or overwrite historical HTML-only lessons.** LLM lessons 63–92 and mathematics units 1–18 still require a *full-content* Markdown equivalence review. This release migrates the four known misplaced Markdown sources only.

## Stable links and future authoring

An educational concept receives one stable ID. A primary Markdown manuscript, interactive course HTML, visual diagrams and separately adapted video script may have different text but must all reference the same concept and original evidence. Any generated lessons require approval before publication. No training permissions are inferred from open visibility.

## Validation rules

- No lesson article written in Markdown should remain under `content/courses/*/lessons/` after the approved four-path deletion.
- New HTML lessons remain in `content/courses` and original scripts remain under `content/videos/scripts`.
- Every moved Markdown link must resolve to a real local file.
- Main LLM index and course map must list approved lessons 1–94.
- Mathematics index must list 1–20, with honest disclosure of HTML-only units.
- Commit migration only after verifying expected Git moves and no accidental deletion outside the approved source list.
