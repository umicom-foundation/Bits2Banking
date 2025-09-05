# Contributing via `raw_docs/` (Quick Guide)

This project welcomes contributions from beginners and busy experts alike.
If you can upload a file, you can contribute. 🚀

---

## What to upload

- Chapters/sections as **.md**, **.docx**, or **.pdf**
- Optional cover image as: **`bookcover_<book_title>.png`** (PNG preferred, 1600–2400px wide)

> Tip: If you’re not sure about formatting, just upload the file. The bot will convert and normalize it.

---

## Where to put files

One folder **per volume** under `raw_docs/`:

```text
raw_docs/<volume-slug>/
├─ my-chapter.docx        # or .md / .pdf
├─ another-section.md
└─ bookcover_My_Title.png # optional
```

### Examples
```text
raw_docs/generalist-ai/intro.docx
raw_docs/starting-a-business/bookcover_Starting_Your_Own_Business.png
```

**Volume slug rules:** lowercase, use hyphens: `generalist-ai`, `starting-a-business`.

---

## What the bot (CI) does for you

When you push to `main`:

1. **Markdown passthrough**
   - Copies `.md` from `raw_docs/<slug>/` → `content/volumes/<slug>/`.
2. **DOCX → Markdown**
   - Converts `.docx` to `.md` (GitHub-Flavored Markdown).
   - Extracts embedded images to `content/volumes/<slug>/images/<basename>/`.
3. **PDF → DOCX → Markdown (best-effort)**
   - Converts text-based `.pdf` to `.docx`, then to `.md`.
   - Scanned PDFs produce images; text quality depends on the source.
4. **Auto-number new chapters**
   - Renames fresh files to `chNN-<slug>.md` (e.g., `ch01-introduction.md`), only for files processed this run. Existing files are untouched.
5. **Normalize Markdown**
   - Adds YAML front-matter (title, volume, status, dates).
   - Ensures a top-level `# Title`.
   - Fixes blank code fences to use `text` (satisfies markdownlint MD040).

### Output lives in:
```text
content/volumes/<volume-slug>/
```

---

## Naming tips (optional but helpful)

- File names: short, lowercase, hyphenated:
  `distributed-systems-overview.md`, `risk-management.docx`
- One top-level heading in `.md`:
```markdown
# My Chapter Title
```
- Code blocks:
```python
print("hello")
```
(Use `text` if you’re unsure.)

---

## Quick scaffolding (optional helpers)

### Windows (PowerShell):
```powershell
# From the repo root
.	ools
ew-volume.ps1 generalist-ai
```

### macOS/Linux (Bash):
```bash
# From the repo root
bash tools/new-volume.sh generalist-ai
```

These create:
```text
raw_docs/<slug>/
content/volumes/<slug>/images/
content/volumes/<slug>/ch00-<slug>.md (placeholder)
```

---

## Submitting work

- If you can edit the repo, **commit directly to `main`** under `raw_docs/<slug>/`.
- Otherwise, fork → branch → PR (the classic way).

That’s it. The bot will mirror/convert your files and you (the maintainer) review final content under `content/volumes/<slug>/`.
