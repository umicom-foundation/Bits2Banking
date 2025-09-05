---
title: "Introduction — How This Open Book Works"
volume: "volume-0"
status: draft
source: "raw_docs/volume-0/volume0-introduction.md"
## tags: ["contributing", "guide"]

# Introduction — How This Open Book Works

Welcome to the **Bits to Banking — Open Book Project**.  
This chapter explains, in plain language, how the repository is organized and how anyone can contribute—by simply uploading a file.

---

## Big picture

- You (or any contributor) put files in **`raw_docs/<volume-slug>/`**.
- The **Ingest bot** (GitHub Actions) mirrors or converts them into **`content/volumes/<volume-slug>/`**.
- The output is normalized Markdown (front-matter, title, code fence languages, etc.) and ready to review/publish.

---

## Folder layout

```text
raw_docs/                 # Drop-zone for uploads (md, docx, pdf), one folder per volume
content/volumes/          # Bot-populated Markdown output (auto-numbered chapters)
chapters/                 # (Legacy/authoring) Existing Volume 0 authoring
docs/                     # Website pages (MkDocs)
.github/                  # CI workflows, issue templates, policies
tools/                    # Helper scripts for scaffolding volumes
```

---

## Contribute in 3 minutes

1. **Pick a volume slug** (lowercase, hyphens): e.g., `volume-0`, `introduction-to-islam`, `bits-to-banking`  
2. **Upload your file(s)** into `raw_docs/<slug>/` as **`.md`**, **`.docx`**, or **`.pdf`**.  
   - Optional cover image: **`bookcover_<book_title>.png`** (or `.jpg`)  
3. **Commit to `main`** (or open a PR).  
4. Bot converts/copies into `content/volumes/<slug>/` and auto-numbers new chapters: `ch01-…`, `ch02-…`

### Examples
```text
raw_docs/volume-0/intro.md
raw_docs/introduction-to-islam/history.docx
raw_docs/bits-to-banking/bookcover_Bits_to_Banking.png
```

---

## What the bot does (exactly)

1. **Markdown passthrough**  
   Copies `.md` to `content/volumes/<slug>/` (and lists them for auto-numbering).
2. **DOCX → Markdown**  
   Uses Pandoc to produce GitHub-Flavored Markdown; extracts embedded images to `content/volumes/<slug>/images/<basename>/`.
3. **PDF → DOCX → Markdown (best-effort)**  
   Converts text-based PDFs via LibreOffice → DOCX → Markdown. Scanned/image-only PDFs become images and may need manual edits.
4. **Book cover standardization**  
   Files named `bookcover_<book_title>.(png|jpg|jpeg)` are saved as `content/volumes/<slug>/images/cover.png`.
5. **Auto-numbering (new files only)**  
   Fresh files from this run are renamed to `chNN-<slug>.md` to keep chapters ordered. Existing files are not renamed.
6. **Normalization**  
   Adds YAML front-matter if missing (title, volume, status, dates), ensures a top-level `# Title`, and fixes bare code fences to `text`.

### Guards & hygiene
- Skips junk/temp files (e.g., `~$docx`, `.tmp`, `.DS_Store`, `Thumbs.db`).
- Warns (does not fail) on uppercase or spaces in filenames—use **lowercase-hyphenated** names.
- Skips very large files with a **warning** (Markdown >2MB, DOCX >20MB, PDF >40MB, images >10MB).

---

## File conventions (quick rules)

- **Filenames:** `lowercase-hyphenated.md` (e.g., `risk-management.md`)  
- **One H1 per chapter:**  
  ```markdown
  # My Chapter Title
  ```
- **Code fences** specify a language:  
  ```python
  print("hello")
  ```
  Use `text` if unsure.

---

## Start a new volume (optional helpers)

### Windows (PowerShell)
```powershell
# From the repo root
.    ools
ew-volume.ps1 introduction-to-islam
```

### macOS/Linux (Bash)
```bash
# From the repo root
bash tools/new-volume.sh introduction-to-islam
```

This creates:
```text
raw_docs/<slug>/
content/volumes/<slug>/images/
content/volumes/<slug>/ch00-<slug>.md (placeholder)
```

---

## Maintainer review flow (what happens after the bot)

1. You push to `main` (or open a PR).  
2. The bot writes normalized Markdown into `content/volumes/<slug>/`.  
3. Maintainer reviews and curates the chapters.  
4. Docs site/build pipelines pick up the content for publishing.

---

## Troubleshooting

- **Nothing happened**: Make sure you committed into `raw_docs/<slug>/` and the file isn’t too large. Check Actions → *Ingest* logs.  
- **Weird formatting**: For DOCX/PDF conversions, open the produced `.md` in `content/volumes/<slug>/` and adjust manually.  
- **Filename warnings**: Rename to lowercase-hyphenated; commit again.  
- **Cover image not found**: Ensure filename starts with `bookcover_` and is `.png`/`.jpg` in the same `raw_docs/<slug>/` folder.

---

## Suggested volumes

- **Volume 0:** `volume-0` — project introduction (this file).
- **Volume 1:** `introduction-to-islam` — foundations, history, core concepts.
- **Volume 2:** `bits-to-banking` — computing → OS → programming → security → finance.

Happy writing! ✨
