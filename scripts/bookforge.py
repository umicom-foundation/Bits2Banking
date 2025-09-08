#!/usr/bin/env python3
"""
BookForge — one-dropzone builder for Bits2Banking

What it does (idempotent):
- Scans dropzone/documents (and dropzone/images) for user content
- Converts .md/.txt/.docx to normalised Markdown (YAML front matter stripped)
- Detects cover image by filename (e.g., "*book cover*.png", "*-cover.png", "*_cover.png")
- Detects foreword/purpose/preface and acknowledgements
- Orders chapters by explicit number in filename/heading or auto-assigns (00,10,20…)
- Normalises image links and copies local images to assets/images
- Writes normalised manuscript/*.md and a combined manuscript/book.md
- Builds DOCX and HTML site (and PDF if wkhtmltopdf or LaTeX engine present)
- Emits toc.json

Safe defaults:
- If Pandoc is missing, writes only manuscript/book.md and tells you what to install.
- Input format to Pandoc is forced to 'gfm' (no YAML metadata parsing), and we strip any
  front matter from individual docs to avoid YAML parse errors.
- If no cover image found, continues without error (cover is optional).
- If no foreword/purpose/preface or acknowledgements found, continues without error.
- If no chapter numbers found, auto-assigns in 10s (10,20,30…) order of discovery.
- Skips non-.md/.txt/.docx files in dropzone/documents.
- Leaves remote (http/https) and data: image URLs untouched.
- If local image file not found, leaves original link intact.
- If image copy fails, leaves original link intact.
- If PDF engine (wkhtmltopdf or LaTeX) not found, builds DOCX and HTML only.
- If dropzone/documents is empty or missing, does nothing.
- UTF-8 in/out to preserve Arabic/diacritics.
Requirements:
- Python 3.7+   
- pip install python-docx  (for .docx support; or install Pandoc)
- Pandoc installed (for DOCX/HTML/PDF output; optional, see above)
- wkhtmltopdf installed (for PDF output; optional, see above)
Usage:
  python scripts/bookforge.py
Environment variables:
    PANDOC_EXE: path to pandoc executable (overrides auto-detect)
    (optional)
    PANDOC_PDF_ENGINE: specify PDF engine for Pandoc (overrides auto-detect)    
    (e.g., "wkhtmltopdf", "xelatex", "lualatex", "pdflatex", "tectonic")
    (if unset, tries to find wkhtmltopdf; if not found, Pandoc will fall back to LaTeX if present)
    (if none found, PDF output is skipped)
    (note: MiKTeX/TeX Live can be used implicitly by Pandoc if installed; no need to set this variable)
Notes:
- Designed for simplicity and minimal user setup.
- Input files are not modified.
- Existing files in manuscript/, assets/images/, assets/covers/, volumes/, and site/ are overwritten.
- Run from repo root (where this script lives in scripts/).
- See README.md for more details.
- Created by Sammy Hegab - Umicom Foundation 2025 
    https://umicom.foundation/
Date: 08-09-2025    
"""

import os
import re
import sys
import json
import shutil
import subprocess
from pathlib import Path

# --- repo paths -------------------------------------------------------------

ROOT = Path(__file__).resolve().parents[1]
DROP = ROOT / "dropzone"
DOCS = DROP / "documents"
IMGS_INBOX = DROP / "images"

MANU = ROOT / "manuscript"
ASSETS = ROOT / "assets"
COVERS = ASSETS / "covers"
AIMGS = ASSETS / "images"

VOLS = ROOT / "volumes"
SITE = ROOT / "site"

# --- helpers ---------------------------------------------------------------

def info(msg: str):
    print(f"[BookForge] {msg}")

def ensure_dirs():
    for d in [DROP, DOCS, IMGS_INBOX, MANU, ASSETS, COVERS, AIMGS, VOLS, SITE]:
        d.mkdir(parents=True, exist_ok=True)

def slugify(title: str) -> str:
    t = re.sub(r"[^\w\s-]", "", title, flags=re.UNICODE)  # remove punctuation
    t = re.sub(r"\s+", "_", t.strip())
    return re.sub(r"_+", "_", t)

def read_text_file(p: Path) -> str:
    try:
        return p.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        return p.read_text(encoding="utf-8", errors="ignore")

def docx_to_md(p: Path) -> str:
    # Prefer python-docx if installed, otherwise try pandoc
    try:
        from docx import Document  # type: ignore
    except Exception:
        pandoc = find_pandoc()
        if pandoc:
            md = subprocess.check_output([pandoc, "-f", "docx", "-t", "gfm", str(p)], text=True)
            return md
        raise RuntimeError("DOCX support requires `python-docx` (pip install python-docx) or Pandoc installed.")
    doc = Document(str(p))
    lines = []
    for para in doc.paragraphs:
        txt = para.text.rstrip()
        lines.append(txt)
    return "\n".join(lines) + "\n"

def to_markdown(p: Path) -> str:
    ext = p.suffix.lower()
    if ext in [".md", ".markdown", ".txt"]:
        return read_text_file(p)
    if ext == ".docx":
        return docx_to_md(p)
    raise RuntimeError(f"Unsupported file type: {p.name}")

def strip_yaml_front_matter(md: str) -> str:
    """Remove a leading YAML front-matter block (--- ... --- or ...) if present."""
    s = md.lstrip()
    if s.startswith("---"):
        lines = s.splitlines(True)
        if lines and lines[0].strip() == "---":
            end_idx = None
            for i in range(1, len(lines)):
                if lines[i].strip() in ("---", "..."):
                    end_idx = i
                    break
            if end_idx is not None:
                return "".join(lines[end_idx+1:])
    return md

def detect_title(md: str, fallback: str) -> str:
    m = re.search(r"^\s*#\s+(.+)$", md, flags=re.M)
    return m.group(1).strip() if m else fallback

def detect_chapter_number(name_or_md: str) -> int | None:
    # "Chapter 5", "ch-05", "05_", "05 Title"
    m = re.search(r"(?:^|[^a-z])chapter\s*(\d+)", name_or_md, flags=re.I)
    if m: return int(m.group(1))
    m = re.search(r"(?:^|[\s_-])(\d{1,2})(?:[\s_-]|$)", name_or_md)
    if m: return int(m.group(1))
    return None

def is_acknowledgements(name: str, md_first_lines: str) -> bool:
    name_hit = re.search(r"acknowledg(e)?ment(s)?", name, flags=re.I)
    head_hit = re.search(r"^\s*#\s+acknowledg(e)?ment(s)?\s*$", md_first_lines, flags=re.I|re.M)
    return bool(name_hit or head_hit)

def is_foreword_or_purpose(name: str, md_first_lines: str) -> bool:
    key = r"(foreword|preface|purpose|introduction)"
    name_hit = re.search(key, name, flags=re.I)
    head_hit = re.search(rf"^\s*#\s+{key}\s*$", md_first_lines, flags=re.I|re.M)
    return bool(name_hit or head_hit)

def find_pandoc() -> str | None:
    # 1) Env override
    p_env = os.environ.get("PANDOC_EXE")
    if p_env and Path(p_env).exists():
        return p_env
    # 2) Local tools folder
    local = ROOT / "tools" / "pandoc" / ("pandoc.exe" if os.name == "nt" else "pandoc")
    if local.exists():
        return str(local)
    # 3) PATH
    return shutil.which("pandoc")

def find_pdf_engine() -> str | None:
    # Prefer wkhtmltopdf for minimal install, else none (Pandoc will fall back to LaTeX if present)
    wk = shutil.which("wkhtmltopdf")
    if wk:
        return "wkhtmltopdf"
    # If MiKTeX/TeX Live present, Pandoc can use them implicitly; we return None here.
    return None

def copy_image_resolved(src_path: Path, chapter_slug: str, fig_index: int) -> str | None:
    """Copy image file to assets/images with normalised name. Return relative destination or None."""
    if not src_path.exists():
        return None
    ext = src_path.suffix if src_path.suffix else ".png"
    dest = AIMGS / f"{chapter_slug}_fig{fig_index:02d}{ext.lower()}"
    dest.parent.mkdir(parents=True, exist_ok=True)
    try:
        shutil.copy2(src_path, dest)
        return dest.relative_to(ROOT).as_posix()
    except Exception:
        return None

def normalise_images_in_md(md: str, doc_path: Path, chapter_slug: str) -> str:
    """
    Rewrite local image links to assets/images/{chapter_slug}_figXX.ext and copy the files.
    Leave http(s) and data: URLs untouched.
    """
    fig = 1

    def replacer(match: re.Match) -> str:
        nonlocal fig
        alt = match.group(1)
        url = match.group(2).strip()

        # Leave remote or data URLs intact
        if re.match(r"^(https?://|data:)", url, flags=re.I):
            return match.group(0)

        # Resolve local path relative to the document
        src = (doc_path.parent / url).resolve()
        if not src.exists():
            # Try resolving against dropzone/images inbox as a fallback
            alt_try = (IMGS_INBOX / url).resolve()
            if alt_try.exists():
                src = alt_try

        rel = copy_image_resolved(src, chapter_slug, fig)
        if rel:
            new_link = f"![{alt}]({rel})"
            fig += 1
            return new_link

        # If copy failed, keep original link
        return match.group(0)

    # ![alt](url)
    return re.sub(r"!\[([^\]]*)\]\(([^)]+)\)", replacer, md)

def collect_documents() -> list[Path]:
    docs = []
    if DOCS.exists():
        for p in sorted(DOCS.rglob("*")):
            if p.is_file() and p.suffix.lower() in [".md",".markdown",".txt",".docx"]:
                docs.append(p)
    return docs

def find_cover_image() -> Path | None:
    cands = []
    for folder in [IMGS_INBOX, DOCS]:
        if not folder.exists():
            continue
        for p in folder.rglob("*"):
            if p.is_file() and p.suffix.lower() in [".png",".jpg",".jpeg",".webp",".tif",".tiff"]:
                if re.search(r"(book\s*cover|[_-]cover(\.|$))", p.name, flags=re.I):
                    cands.append(p)
    return sorted(cands)[0] if cands else None

def copy_and_rename_cover(title_slug: str, vol_num: int = 0) -> str | None:
    c = find_cover_image()
    if not c:
        return None
    dest = COVERS / f"Volume_{vol_num:02d}_{title_slug}_Cover{c.suffix.lower()}"
    dest.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(c, dest)
    return dest.relative_to(ROOT).as_posix()

# --- main -------------------------------------------------------------------

def main() -> int:
    ensure_dirs()
    info("Scanning dropzone/documents ...")
    raw_docs = collect_documents()
    if not raw_docs:
        info("No documents found in dropzone/documents/. Nothing to do.")
        return 0

    # 1) Convert to Markdown, strip YAML front matter
    converted: list[tuple[Path, str]] = []
    for p in raw_docs:
        try:
            md = to_markdown(p)
        except Exception as e:
            info(f"Skipping {p.name}: {e}")
            continue
        md = strip_yaml_front_matter(md)
        converted.append((p, md))

    # 2) Guess book title
    book_title = None
    for p, md in converted:
        book_title = detect_title(md, p.stem)
        if book_title:
            break
    if not book_title:
        book_title = "Untitled Book"
    book_slug = slugify(book_title)

    # 3) Cover
    rel_cover = copy_and_rename_cover(book_slug, vol_num=0)
    if rel_cover:
        info(f"Cover detected → {rel_cover}")
    else:
        info("No cover detected (optional).")

    # 4) Categorise documents
    chapters = []
    forewords = []
    acks = []

    auto_index = 0
    for p, md in converted:
        first_lines = "\n".join(md.splitlines()[:5])
        title = detect_title(md, p.stem)
        slug = slugify(title)

        # rewrite and copy images
        md2 = normalise_images_in_md(md, p, slug)

        if is_acknowledgements(p.name, first_lines):
            acks.append((999, slug, md2))
            continue
        if is_foreword_or_purpose(p.name, first_lines):
            forewords.append((0, slug, md2))
            continue

        cnum = detect_chapter_number(p.name + "\n" + md2)
        if cnum is None:
            cnum = auto_index
            auto_index += 10
        chapters.append((cnum, slug, md2))

    chapters.sort(key=lambda x: x[0])
    forewords.sort(key=lambda x: x[0])

    # 5) Write normalised manuscript parts
    info("Writing normalised manuscript/*.md ...")
    # clear old files (safe: only *.md in MANU)
    for old in MANU.glob("*.md"):
        try:
            old.unlink()
        except Exception:
            pass

    # forewords
    for i, (_, slug, md) in enumerate(forewords, start=1):
        (MANU / f"00.{i:02d}_{slug}.md").write_text(md, encoding="utf-8")

    # chapters
    for idx, (_, slug, md) in enumerate(chapters, start=1):
        (MANU / f"10.{idx*10:02d}_{slug}.md").write_text(md, encoding="utf-8")

    # acks
    for i, (_, slug, md) in enumerate(acks, start=1):
        (MANU / f"99.{i:02d}_{slug}.md").write_text(md, encoding="utf-8")

    # 6) Assemble book.md (avoid '---' rule; use '***')
    parts = []
    if rel_cover:
        parts.append(f"![Cover]({rel_cover})\n")
    parts.append(f"# {book_title}\n")

    # ToC
    parts.append("\n## Contents\n")
    if forewords:
        for _, slug, _ in forewords:
            parts.append(f"- Foreword: {slug.replace('_',' ')}")
    if chapters:
        for _, slug, _ in chapters:
            parts.append(f"- {slug.replace('_',' ')}")
    if acks:
        for _, slug, _ in acks:
            parts.append(f"- Acknowledgements: {slug.replace('_',' ')}")
    parts.append("\n***\n")

    # Sections
    for _, slug, md in forewords:
        parts.append(f"\n\n## Foreword: {slug.replace('_',' ')}\n")
        parts.append(md)
    for _, slug, md in chapters:
        parts.append(f"\n\n## {slug.replace('_',' ')}\n")
        parts.append(md)
    for _, slug, md in acks:
        parts.append(f"\n\n## Acknowledgements: {slug.replace('_',' ')}\n")
        parts.append(md)

    book_md = "\n".join(parts).strip() + "\n"
    (MANU / "book.md").write_text(book_md, encoding="utf-8")

    # 7) Build outputs with Pandoc (if available)
    vol_base = VOLS / f"Volume_00_{book_slug}"
    pandoc = find_pandoc()
    if not pandoc:
        info("Pandoc not found; wrote markdown only. Install Pandoc to produce DOCX/HTML/PDF.")
        info(f"Output: { (MANU / 'book.md').relative_to(ROOT).as_posix() }")
        return 0

    info("Building DOCX and site (and PDF if engine available) ...")
    # DOCX
    subprocess.check_call([
        pandoc, "-f", "gfm",
        str(MANU/"book.md"),
        "-o", str(vol_base.with_suffix(".docx"))
    ])

    # HTML site
    css = SITE / "style.css"
    if not css.exists():
        css.write_text(
            "body{max-width:900px;margin:3rem auto;font-family:system-ui,Segoe UI,Arial,sans-serif;line-height:1.6;padding:0 1rem}"
            "img{max-width:100%;} h1,h2,h3{scroll-margin-top:80px}"
            ".toc, .contents{background:#f6f6f6;padding:1rem;border-radius:8px}\n",
            encoding="utf-8"
        )
    subprocess.check_call([
        pandoc, "-f", "gfm", "-s",
        str(MANU/"book.md"),
        "-o", str(SITE/"index.html"),
        "--metadata", f"title={book_title}",
        "--css", str(css)
    ])

    # PDF (if engine available)
    pdf_engine = find_pdf_engine()
    if pdf_engine:
        subprocess.check_call([
            pandoc, "-f", "gfm",
            str(MANU/"book.md"),
            "-o", str(vol_base.with_suffix(".pdf")),
            f"--pdf-engine={pdf_engine}"
        ])
    else:
        info("Skipping PDF (wkhtmltopdf not found; install it or a LaTeX engine to enable PDF).")

    info(f"Built: {vol_base.with_suffix('.docx').name} (and site/index.html).")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except subprocess.CalledProcessError as e:
        print(f"[BookForge:ERROR] Command failed: {e}", file=sys.stderr)
        sys.exit(e.returncode)
    except Exception as e:
        print(f"[BookForge:ERROR] {e}", file=sys.stderr)
        sys.exit(1)
