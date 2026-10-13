# Major Update 37 — Validation report (observed results)

**Scope:** additive Bits2Banking absolute beginner course, new user-provided teaching screenshot, diagrams and standalone C23 Notes laboratory. No Umicom Framework, Kernel, OS or Applications code is changed or tested by this batch.

## Native toolchain validation

| Check | Observed result | Qualification boundary |
|---|---|---|
| GCC 14.2.0 compile, C23 required, strict `-Wall -Wextra -Wpedantic -Wconversion -Wshadow` | **Passed**, 0 compiler diagnostics in build output | Linux GNU host; not Windows UCRT64 |
| GCC 14.2.0 standalone CTest | **8/8 passed** | Seven independent cases plus demonstration |
| Clang 17 C23 with `-fsanitize=address,undefined` | **Compiled** | Sanitizer instrumentation for this Linux toolchain |
| Clang 17 AddressSanitizer/UBSan CTest | **8/8 passed** | No reported sanitizer failures; does not prove platform-wide memory safety |
| `btb-contributor-notes-demo` | **Ran successfully** | Printed two in-memory Notes records, no persistence |
| Optional installed Framework SDK consumer | **Not run** | Compatible SDK installation is required; no SDK build qualified here |
| Windows MSYS2 UCRT64 build | **Not run** | Must be checked on a Windows machine with its exact GCC/CMake/Ninja versions |
| Complete existing MkDocs website build | **Not run** | Requires reviewed manual navigation merge and pre-existing MkDocs environment |
| GitHub Pages live publication | **Not verified** | Requires post-push Actions and site checks |

## Native case detail

CTest names: `bits2banking.contributor_notes.add`, `.update`, `.too-long`, `.capacity`, `.missing`, `.invalid`, `.ownership`, `.demo`.

The negative tests exercise empty/missing input, oversized text, full storage, missing records, and copied payload ownership. `BtbNotesAdd` rejects oversized/full input without updating the caller-owned store or its output identifier. Notes are bounded by eight records and 95 characters plus the terminating NUL. All operations are single-threaded; they do not claim concurrency or persistence.

## Content review

- Markdown chapter numbering continues from **264** through **283** (20 new numbered lessons; 16 foundation lessons plus four optional advanced chapters).
- Five video scripts continue sequentially from **90** through **94**.
- Five SVG diagrams are well-formed XML and were rendered during authoring. A learner-provided Windows 11 search screenshot is included unchanged under `content/assets/screenshots`. The shareable offline HTML edition was inspected: it embeds **20 numbered lessons, five inline SVG diagrams, the screenshot, responsive styles and no JavaScript**.
- The course uses one new landing page and one quick-reference page, and retains the previously established `content/lessons/05-engineering` and `content/videos/scripts` locations.
- All new relative Markdown image/page links were checked against the package tree; none were unresolved. Links to existing historical lessons are described as source paths rather than unverified new package assets.
- The MkDocs navigation fragment has been syntax-checked separately; it is **not** a complete replacement for the historical `mkdocs.yml`.
- New executable source uses **C23** only; there are **zero `.py` and `.ps1` implementation files**. PowerShell appears only as interactive commands inside Markdown.
- No batch operation performs live Git modifications, credential management, system administration or network calls.

## Teaching quality gates

Commands were reviewed to distinguish PowerShell 7, Windows PowerShell 5.1, Windows Terminal, MSYS2 UCRT64 and Linux Bash. Git and GitHub operations are separated; the beginner local repo is deliberately placed under `$HOME` and is independent of Umicom production repositories. `git add -A`, `git push`, `gh repo create`, Winget installation and the `repo lock` staging operation each have an explicit permission or safety boundary. Negative outcomes are not misrepresented as success.

**Remaining acceptance:** Windows build/CTest; merge reviewed navigation, run `mkdocs build --strict`, check the new screenshot and diagrams on the actual site; optionally compile the installed Framework SDK example; finally verify any GitHub-hosted deployment. No unperformed check is claimed as passed.
