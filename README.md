# Bits to Banking — Open Book Project
[![Ingest](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/ingest.yml/badge.svg?branch=main)](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/ingest.yml)
[![Build Volume 0](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/build-volume0.yml/badge.svg?branch=main)](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/build-volume0.yml)
[![Build](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/build-volume0.yml/badge.svg)](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/build-volume0.yml)
[![Lint](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/lint.yml/badge.svg)](https://github.com/umicom-foundation/Bits2Banking/actions/workflows/lint.yml)
[![Release](https://img.shields.io/github/v/release/umicom-foundation/Bits2Banking?display_name=tag&sort=semver)](https://github.com/umicom-foundation/Bits2Banking/releases/latest)
[![Docs](https://img.shields.io/badge/docs-online-blue)](https://umicom-foundation.github.io/Bits2Banking)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Learn computing from **bits → operating systems → programming → databases → networking → security → finance**, then into **Calypso/TMS** and real projects.  
We publish in small, printable **volumes** so beginners and adults can follow step by step.

---

## 🚀 Copy–Paste Cheatsheet

**Windows (PowerShell):**
```powershell
git clone https://github.com/umicom-foundation/Bits2Banking.git C:\Bits2Banking
cd C:\Bits2Banking
.build.ps1 install
.build.ps1 build
start .
olumes\Volume_00_Source_Control.docx
```

**macOS / Linux (Makefile):**
```bash
git clone https://github.com/umicom-foundation/Bits2Banking.git
cd Bits2Banking && make install && make build
xdg-open ./volumes/Volume_00_Source_Control.docx 2>/dev/null || open ./volumes/Volume_00_Source_Control.docx
```

---

## 📚 Project Docs

- [About](ABOUT.md) — Why this project exists and how it links education with humanitarian aid  
- [Roadmap](ROADMAP.md) — Planned volumes and future direction  
- [Support](SUPPORT.md) — Donation details (GBP, USD, EUR, AUD, CAD)  
- [Acknowledgements](ACKNOWLEDGEMENTS.md) — Families, volunteers, and supporters  
- [Contributing](.github/CONTRIBUTING.md) — Step-by-step guide for new contributors
- [Quick Upload via `raw_docs/`](docs/CONTRIBUTING_RAW_DOCS.md) — easiest path: upload `.md`/`.docx`/`.pdf` and let CI convert.  
- [Code of Conduct](.github/CODE_OF_CONDUCT.md) — Community rules and expectations  
- [Governance](GOVERNANCE.md) — How decisions are made  
- [Security Policy](.github/SECURITY.md) — How to report vulnerabilities  
- [Changelog](CHANGELOG.md) — Project history and notable changes

---

## Our Cause

This project is part of the **Umicom Foundation**’s mission: **open education with real-world impact**.  
We are committed to supporting **civilians in Gaza** who are suffering siege, starvation, and mass displacement. Through this project we aim to:  

- Provide **free educational resources** worldwide.  
- Channel project proceeds and donations into **relief and education** for those in crisis.  
- Stand in solidarity with Palestinians and all oppressed people by combining **knowledge sharing** with **direct humanitarian action**.  

---

## Founder

**Sammy Hegab** — software engineer, educator, and humanitarian.  

- 10+ years in the financial sector, working on Treasury Management Systems (**Calypso**, **Summit**, **Murex**).  
- Background in energy, fintech, and open-source advocacy (**RISC‑V**, **Linux**, free software).  
- Founder of the Umicom Foundation, which promotes **education, relief, and technology** projects.  

I started *Bits to Banking* to make computing and finance approachable for all learners, and to channel learning into **real help for people under siege and suffering**.

---

## Support & Donations

See **[SUPPORT.md](SUPPORT.md)** (GBP, USD, EUR, AUD, CAD). Your support funds **education** and **relief for Gaza**.

---

## What you’ll get (first run)

- A small **Volume 0** Word file you can open locally.  
- Two short chapters you can edit in Markdown.  
- A simple **“edit → build → pull request”** flow.  

---

## Quick Start — Windows (PowerShell)

> Requirements: **Python 3.11+** and **Git**  
> Download: <https://python.org> • <https://git-scm.com> • (Optional: [VS Code](https://code.visualstudio.com))

### 0) Get the project
```powershell
git clone https://github.com/umicom-foundation/Bits2Banking.git C:\Bits2Banking
cd C:\Bits2Banking
```

### 1) (Optional) Create a virtual environment
```powershell
python -m venv .venv
.\.venv\Scriptsctivate
python -m pip install --upgrade pip
```

### 2) Install dependencies
```powershell
# If requirements.txt exists, use it. Otherwise install python-docx only.
if (Test-Path .
equirements.txt) { pip install -r requirements.txt } else { pip install python-docx }
```

### 3) Build using the helper script
```powershell
# Uses scripts\make_volume0_from_md.py under the hood
.build.ps1 build
```

### 4) Open the result
```powershell
start .
olumes\Volume_00_Source_Control.docx
```

> Other handy commands: `.build.ps1 install` • `.build.ps1 docs` • `.build.ps1 lint` • `.build.ps1 clean`

---

## Quick Start — Any OS (Makefile)

> Requirements: **Python 3.11+**, **Git**, and **make** (Linux/macOS; on Windows use Git Bash/MSYS2).

```bash
# 0) Get the project
git clone https://github.com/umicom-foundation/Bits2Banking.git
cd Bits2Banking

# 1) Install deps (uses requirements.txt if present)
make install

# 2) Build Volume 0
make build

# 3) Open the output (macOS or Linux)
open ./volumes/Volume_00_Source_Control.docx 2>/dev/null || xdg-open ./volumes/Volume_00_Source_Control.docx
```

> Other handy commands: `make docs` • `make lint` • `make clean`

---

## Repository Layout

- `chapters/v00/` — Markdown chapters for Volume 0  
- `scripts/` — Python build scripts  
- `volumes/` — generated `.docx` (git-ignored)  
- `docs/` — website pages (MkDocs)  
- `images/`, `bookcover/` — artwork and assets  

---

## Contributing (Step-by-Step)

1. **Fork** the repo and create a branch (e.g., `feat/my-chapter`).  
2. Add/edit a file in `chapters/v00/` — start with a top-level heading:
   ```markdown
   # My Chapter Title
   A short introduction...
   ```
3. Build locally (pick one):  
   ```powershell
   .build.ps1 build
   ```
   ```bash
   make build
   ```
4. Open and review `volumes/Volume_00_Source_Control.docx`.  
5. Commit, push, and open a Pull Request.  
6. ✅ **CI will attach the built `.docx`** to your PR.  

---

## Troubleshooting

- **Markdown linter errors (MD040, MD024, etc.)**  
  Use code fences **with a language** (e.g., `text`, `powershell`). Duplicate headings are allowed across dates in the changelog.
- **Typos check fails on brand names**  
  We whitelist proper nouns in `.typos.toml`. Open a PR to add new ones.  
- **UTF‑8 BOM error / line endings**  
  We ship `.editorconfig` and `.gitattributes` to keep files UTF‑8 (no BOM) and LF (CRLF for `.ps1`). Ensure your editor follows them.  
- **Pages deployment 404**  
  Repo Settings → Pages → Source = **GitHub Actions**; ensure workflow has `pages: write`, `id-token: write` permissions.

---

## Acknowledgements

### Founding contributors
- **Sammy Hegab** (project lead, author, builder)  

### Supporters & community
- Families, friends, and volunteers of Umicom Foundation  
- All who stand with civilians in Gaza and support relief & education  

(If you’d like to be acknowledged as a supporter or partner, please open a PR or contact us.)  

---

## License

MIT — see [LICENSE](LICENSE).

**Project website:** <https://umicom-foundation.github.io/Bits2Banking>
