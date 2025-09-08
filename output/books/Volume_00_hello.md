![Cover](assets/covers/Volume_00_hello_Cover.png)

# hello


## Contents

- [hello](#hello)
- [Introduction How This Open Book Works](#introduction_how_this_open_book_works)
- [ch00 prelude](#ch00_prelude)
- [Introduction to Islam Purpose Sources and Scope](#introduction_to_islam_purpose_sources_and_scope)
- [ch01 git GitHub basics](#ch01_git_github_basics)
- [Bits to Banking What You Will Learn](#bits_to_banking_what_you_will_learn)
- [README](#readme)

---



## hello
<a name='hello'></a>

﻿# Hello from raw_docs



## Introduction How This Open Book Works
<a name='introduction_how_this_open_book_works'></a>

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



## ch00 prelude
<a name='ch00_prelude'></a>

﻿# Prelude — Recap & Setup (placeholder)

> This chapter has moved to the new content system.
> For current content, see: `content/v001_islam_blueprint_for_life/`.



## Introduction to Islam Purpose Sources and Scope
<a name='introduction_to_islam_purpose_sources_and_scope'></a>

---
title: "Introduction to Islam — Purpose, Sources, and Scope"
volume: "introduction-to-islam"
status: draft
source: "raw_docs/introduction-to-islam/volume1-introduction.md"
## tags: ["introduction", "history", "glossary"]

# Introduction to Islam — Purpose, Sources, and Scope

This chapter sets expectations for the volume and offers a gentle, respectful overview of Islam for newcomers.  
It explains *what* we will cover, *how* we will approach it, and *how you can contribute* to improve clarity and accuracy.

---

## Who this is for

- Curious readers with **no prior background**.
- Educators, parents, and learners looking for **clear definitions** and **primary-source pointers**.
- Contributors who want to help with **editing, translation notes, or adding references**.

> We aim for **accuracy**, **neutrality**, and **respect** for diverse Muslim communities and scholarly traditions.

---

## What this volume covers

- A beginner-friendly **overview of Islam**: key beliefs and practices.
- Concise context for **history**, **sources**, and **schools of thought**.
- Clear definitions for common terms and a short **glossary**.
- Signposts to primary sources and widely used translations.

This is **not** a replacement for scholarly study; it is an introduction that points to deeper resources.

---

## How to use this volume

- Read sequentially or dip into sections you need.  
- Use the **glossary** when you encounter new terms.  
- Follow the **Further Reading** notes at the end of chapters.

If you notice unclear phrasing or missing context, please contribute a correction (see **Contributing** below).

---

## Sources and methodology (at a glance)

- **Primary sources**: the Qur'an and the Sunnah (the teachings and practices attributed to the Prophet Muhammad, recorded in hadith literature).  
- **Secondary sources**: classical and modern scholarship, commentaries (tafsir), legal theory (usul al‑fiqh), and history.  
- When citing English translations, we note that **word choices vary**; contributors may suggest improvements and add references.  
- We avoid sectarian polemics; where scholarly views diverge, we **describe multiple perspectives** clearly.

---

## Key terms at a glance

- **Allah** — Arabic for God; used by Arabic‑speaking Muslims and non‑Muslims alike.  
- **Qur'an** — central scripture of Islam.  
- **Sunnah** — the prophetic example; teachings/practices reported in hadith.  
- **Hadith** — reports about what the Prophet said, did, or approved; collected with chains of transmission.  
- **Sharia** — the broad path or way; ethical‑legal framework derived from sources.  
- **Fiqh** — jurisprudence; the human understanding and application of the law.  
- **Ummah** — the global community of Muslims.  
- **Mosque (Masjid)** — place of worship.  
- **Five Pillars** — declaration of faith, prayer, almsgiving, fasting in Ramadan, and pilgrimage (Hajj).

> These brief definitions are for orientation; later chapters expand them with sources and examples.

---

## Suggested outline for this volume

- **ch01 — Orientation:** What this book covers and how to read it.  
- **ch02 — The Qur'an:** Structure, themes, translations, recitation.  
- **ch03 — The Sunnah and Hadith:** Collections, authentication, usage.  
- **ch04 — Core Beliefs:** God, prophethood, revelation, afterlife.  
- **ch05 — Practices:** Prayer, charity, fasting, pilgrimage.  
- **ch06 — Ethics and Law:** Sharia, fiqh, objectives (maqasid), diversity of opinion.  
- **ch07 — History (very brief):** Early community, spread, languages, scholarship.  
- **ch08 — Contemporary topics:** Community life, education, and common questions.  
- **ch09 — Glossary & study tips:** How to keep learning.  
- **ch10 — Further reading:** Translations, introductions, beginner courses.

This outline is a **starting point**; contributors can suggest reordering or new sections.

---

## Contributing (for this volume)

1. Create or use the folder:  
   ```text
   raw_docs/introduction-to-islam/
   ```
2. Add your chapter as **.md**, **.docx**, or **.pdf**.  
   - Optional cover image named like: `bookcover_Introduction_to_Islam.png`  
3. Commit to **main** (or open a PR). The **Ingest** bot will:
   - Convert or copy to `content/volumes/introduction-to-islam/`
   - Auto‑number new chapters (`ch01‑...`, `ch02‑...`)
   - Normalize Markdown (front‑matter, title, code fences)

If your file is very large (PDF > 40MB, DOCX > 20MB, MD > 2MB), the bot will **skip it** and print a warning in the Action logs.

---

## A short glossary (starter)

- **Aqidah** — creed or beliefs.  
- **Tafsir** — exegesis/commentary on the Qur'an.  
- **Madhhab** — legal school (e.g., Hanafi, Maliki, Shafi'i, Hanbali).  
- **Imam** — leader of prayer; also used for senior scholars in history.  
- **Maqasid al‑Sharia** — higher objectives of the law (e.g., protection of faith, life, intellect, family, property).

---

### Next

Propose a **chapter you want to write** (e.g., “The Qur'an: an overview”) and add it under `raw_docs/introduction-to-islam/`.  
We’ll grow this volume together with clear, sourced, respectful chapters.



## ch01 git GitHub basics
<a name='ch01_git_github_basics'></a>

﻿# Git & GitHub Basics (placeholder)

> This chapter has moved to the new content system.
> For current content, see: `content/v001_islam_blueprint_for_life/`.



## Bits to Banking What You Will Learn
<a name='bits_to_banking_what_you_will_learn'></a>

---
title: "Bits to Banking — What You Will Learn"
volume: "bits-to-banking"
status: draft
source: "raw_docs/bits-to-banking/volume2-introduction.md"
## tags: ["overview", "computing", "finance"]

# Bits to Banking — What You Will Learn

This volume is a hands-on pathway from **computing fundamentals** (bits, binary, operating systems) to **software development**, **databases**, **networking & security**, and finally **finance systems** and **Treasury/Trading** concepts used in the real world.

---

## Who this is for

- Beginners who want a clear, practical route from zero to building useful things.  
- Engineers from other fields who want a **finance-tech** overview.  
- Contributors who can add examples, diagrams, labs, or case studies.

---

## Learning outcomes

By the end you will be able to:

- Explain how data becomes meaning: **bits → bytes → files → processes**.  
- Use the command line and write small programs to automate tasks.  
- Model and query data in **relational databases**.  
- Understand core **networking** and **security** ideas.  
- Read and discuss **banking/treasury** workflows with the right vocabulary.  

---

## Suggested outline

- **ch01 — Bits & Binary:** Representation, integers, text, endianness.  
- **ch02 — Operating Systems primer:** Processes, memory, filesystems, permissions.  
- **ch03 — Programming basics:** Variables, control flow, functions, modules, tests.  
- **ch04 — Data modeling & SQL:** Tables, keys, normalization, joins, transactions.  
- **ch05 — Networking:** TCP/IP, HTTP, tools, client–server mini-labs.  
- **ch06 — Security essentials:** Hashing, crypto at a high level, auth, threat basics.  
- **ch07 — Finance foundations:** Money flows, accounts, ledgers, payments rails.  
- **ch08 — Market data & pricing:** Instruments, quotes, risk-at-a-glance.  
- **ch09 — Treasury systems overview:** Positions, cash, risk, settlement; where **Calypso/TMS** fits.  
- **ch10 — Mini projects:** ETL a CSV into a DB; simple pricing/reporting script; mock “ops” day.

This outline will evolve with contributions and reviewer feedback.

---

## Contributing to this volume

1. Create or use the folder:
   ```text
   raw_docs/bits-to-banking/
   ```
2. Add chapters as **.md**, **.docx**, or **.pdf**.  
   - Optional cover image: `bookcover_Bits_to_Banking.png`  
3. Commit to **main** (or open a PR). The **Ingest** bot will:
   - Convert/copy to `content/volumes/bits-to-banking/`
   - Auto-number new chapters (`ch01-...`)
   - Normalize Markdown (front-matter, title, code fences)

If your file is very large (PDF > 40MB, DOCX > 20MB, MD > 2MB), it will be **skipped** with a warning in the Action logs.

---

## Getting hands-on (starter tasks)

- Reproduce a binary-to-decimal conversion with a short script.  
- Write a CLI that reads a CSV and prints summary stats.  
- Spin up a local database and run three non-trivial joins.  
- Use a packet capture tool to observe a simple HTTP request.  
- Sketch a money movement from account A → B and identify risks.

We’ll refine these into end-to-end labs as the volume grows.

---

## Next steps

Pick a chapter (e.g., **Bits & Binary**) and start drafting under `raw_docs/bits-to-banking/`.  
Include small, runnable examples and short exercises.



## README
<a name='readme'></a>

﻿# raw_docs (drop zone)

Put uploads here. Accepted formats (for now): **.md**, **.docx**, **.pdf**
Optional cover image: `bookcover_<book_title>.png`

Recommended structure (we’ll wire automation next step):
- `raw_docs/<volume-slug>/your_chapter.docx`
- `raw_docs/<volume-slug>/bookcover_<book_title>.png`

Examples:
- `raw_docs/generalist-ai/intro.docx`
- `raw_docs/starting-a-business/bookcover_Starting_Your_Own_Business.png`
