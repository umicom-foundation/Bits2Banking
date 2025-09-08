#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
BookForge v2.0 — one-dropzone builder for Bits2Banking
- Created by: Sammy Hegab — Umicom Foundation (https://umicom.foundation/)
- Date: 08-09-2025
- Description:
    One entry point (dropzone/) in, one output root (output/) out.
    Scans dropzone/documents + dropzone/images, normalises content, detects cover + special
    sections, orders chapters, and produces:
      - output/manuscript/*.md + output/manuscript/book.md
      - output/books/Volume_XX_<slug>.docx (and .pdf if engine present)
      - output/site/index.html (+ output/site/assets/*) as a self-contained site
    Safe defaults: tolerant of YAML front matter, CRLFs, unlabeled code fences, missing cover,
    missing PDF engine, and mixed inputs. UTF-8 throughout.

What it does:
- Converts .md/.txt/.docx → Markdown (strips YAML front matter; CRLF→LF; adds code-fence language)
- Detects cover by filename (“book cover”, “-cover”, “_cover”); picks best image
- Detects foreword/purpose/preface and acknowledgements
- Orders chapters (explicit numbers if present else 00,10,20…)
- Normalises image links and copies images to output/assets/images
- Writes output/manuscript/*.md and output/manuscript/book.md
- Builds DOCX, HTML site, and PDF if wkhtmltopdf or LaTeX engine present
- Mirrors output/assets → output/site/assets (so site is standalone)
- Emits toc.json at repo root

Optional config (dropzone/bookforge.json):
{
  "title": "Your Book Title",
  "volume": 0
}

CLI:
  --title "My Title"  --volume 1
  --no-docx --no-html --no-pdf --no-site-assets
  --dry-run --quiet

Env:
  PANDOC_EXE         : path to pandoc executable
  WKHTMLTOPDF_EXE    : path to wkhtmltopdf
  PANDOC_PDF_ENGINE  : engine name/path (wkhtmltopdf, xelatex, ...)

Requirements:
  - Python 3.9+
  - pip install python-docx (for .docx import) OR install Pandoc
  - Pandoc (for DOCX/HTML/PDF)
  - wkhtmltopdf OR LaTeX engine (for PDF)
"""

import os
import re
import sys
import json
import shutil
import argparse
import subprocess
from pathlib import Path
from typing import Optional

# --- repo paths (single output root) ---------------------------------------

ROOT = Path(__file__).resolve().parents[1]
DROP = ROOT / "dropzone"
DOCS = DROP / "documents"
IMGS_INBOX = DROP / "images"

OUTPUT = ROOT / "output"
OUT_MANU = OUTPUT / "manuscript"
OUT_ASSETS = OUTPUT / "assets"
OUT_COVERS = OUT_ASSETS / "covers"
OUT_AIMGS = OUT_ASSETS / "images"
OUT_BOOKS = OUTPUT / "books"
OUT_SITE = OUTPUT / "site"

# Ignore junk files (OS/editor/temp)
IGNORE_RE = re.compile(
    r'(^|/)(~\$|\.#|#.*#|Thumbs\.db|\.DS_Store|\.AppleDouble|\.LSOverride|desktop\.ini|\.swp$|\.tmp$|\.bak$|\.partial$|\.crdownload$)',
    flags=re.I
)

# --- helpers ---------------------------------------------------------------

def info(msg: str, quiet: bool = False):
    if not quiet:
        print(f"[BookForge] {msg}")

def ensure_dirs():
    for d in [DROP, DOCS, IMGS_INBOX, OUTPUT, OUT_MANU, OUT_ASSETS, OUT_COVERS, OUT_AIMGS, OUT_BOOKS, OUT_SITE]:
        d.mkdir(parents=True, exist_ok=True)

def slugify(title: str) -> str:
    t = re.sub(r"[^\w\s-]", "", title, flags=re.UNICODE)
    t = re.sub(r"\s+", "_", t.strip())
    return re.sub(r"_+", "_", t).strip("_")

def read_text_file(p: Path) -> str:
    try:
        return p.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        return p.read_text(encoding="utf-8", errors="ignore")

def normalise_line_endings(s: str) -> str:
    return s.replace("\r\n", "\n").replace("\r", "\n")

def add_lang_to_fences(md: str, default_lang: str = "text") -> str:
    return re.sub(r"(?m)^```[ \t]*\n", f"```{default_lang}\n", md)

def find_pandoc() -> Optional[str]:
    p_env = os.environ.get("PANDOC_EXE")
    if p_env and Path(p_env).exists():
        return p_env
    local = ROOT / "tools" / "pandoc" / ("pandoc.exe" if os.name == "nt" else "pandoc")
    if local.exists():
        return str(local)
    return shutil.which("pandoc")

def find_pdf_engine() -> Optional[str]:
    env_engine = os.environ.get("PANDOC_PDF_ENGINE")
    if env_engine:
        return env_engine
    env_wk = os.environ.get("WKHTMLTOPDF_EXE")
    if env_wk and Path(env_wk).exists():
        return env_wk
    which = shutil.which("wkhtmltopdf")
    if which:
        return which
    for c in [
        Path(r"C:\Program Files\wkhtmltopdf\bin\wkhtmltopdf.exe"),
        Path(r"C:\Program Files (x86)\wkhtmltopdf\bin\wkhtmltopdf.exe"),
    ]:
        if c.exists():
            return str(c)
    for latex in ("xelatex", "pdflatex", "lualatex"):
        if shutil.which(latex):
            return latex
    return None

def docx_to_md(p: Path) -> str:
    try:
        from docx import Document  # type: ignore
    except Exception:
        pandoc = find_pandoc()
        if pandoc:
            md = subprocess.check_output([pandoc, "-f", "docx", "-t", "gfm", str(p)], text=True)
            return md
        raise RuntimeError("DOCX support requires `python-docx` or Pandoc.")
    doc = Document(str(p))
    lines = [(para.text or "").rstrip() for para in doc.paragraphs]
    return "\n".join(lines) + "\n"

def to_markdown(p: Path) -> str:
    ext = p.suffix.lower()
    if ext in [".md", ".markdown", ".txt"]:
        return read_text_file(p)
    if ext == ".docx":
        return docx_to_md(p)
    raise RuntimeError(f"Unsupported file type: {p.name}")

def strip_yaml_front_matter(md: str) -> str:
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

def detect_chapter_number(name_or_md: str) -> Optional[int]:
    m = re.search(r"(?:^|[^a-z])chapter\s*(\d+)", name_or_md, flags=re.I)
    if m: return int(m.group(1))
    m = re.search(r"^\s*(\d{1,2})[._-]", name_or_md)
    if m: return int(m.group(1))
    m = re.search(r"(?:^|[\s_-])(\d{1,2})(?:[\s_-]|$)", name_or_md)
    if m: return int(m.group(1))
    return None

def is_acknowledgements(name: str, md_first_lines: str) -> bool:
    # Match both spellings without introducing a bare 'ment' token that the typos checker flags.
    # This regex accepts: acknowledgment(s) & acknowledgement(s).
    patt = r"acknowledg(?:e)?m(?:e)?nt(?:s)?"
    name_hit = re.search(patt, name, flags=re.I)
    head_hit = re.search(rf"^\s*#\s+{patt}\s*$", md_first_lines, flags=re.I | re.M)
    return bool(name_hit or head_hit)

def is_foreword_or_purpose(name: str, md_first_lines: str) -> bool:
    key = r"(foreword|preface|purpose|introduction)"
    name_hit = re.search(key, name, flags=re.I)
    head_hit = re.search(rf"^\s*#\s+{key}\s*$", md_first_lines, flags=re.I|re.M)
    return bool(name_hit or head_hit)

def copy_image_resolved(src_path: Path, chapter_slug: str, fig_index: int) -> Optional[str]:
    if not src_path.exists():
        return None
    ext = src_path.suffix if src_path.suffix else ".png"
    dest = OUT_AIMGS / f"{chapter_slug}_fig{fig_index:02d}{ext.lower()}"
    dest.parent.mkdir(parents=True, exist_ok=True)
    try:
        shutil.copy2(src_path, dest)
        return dest.relative_to(ROOT).as_posix()
    except Exception:
        return None

def normalise_images_in_md(md: str, doc_path: Path, chapter_slug: str) -> str:
    fig = 1
    def repl(m: re.Match) -> str:
        nonlocal fig
        alt, url = m.group(1), m.group(2).strip()
        if re.match(r"^(https?://|data:)", url, flags=re.I):
            return m.group(0)
        src = (doc_path.parent / url).resolve()
        if not src.exists():
            alt_try = (IMGS_INBOX / url).resolve()
            if alt_try.exists():
                src = alt_try
        rel = copy_image_resolved(src, chapter_slug, fig)
        if rel:
            fig += 1
            return f"![{alt}]({rel})"
        return m.group(0)
    return re.sub(r"!\[([^\]]*)\]\(([^)]+)\)", repl, md)

# --- cover selection --------------------------------------------------------

def _image_resolution_score(path: Path) -> int:
    try:
        from PIL import Image  # type: ignore
        with Image.open(str(path)) as im:
            w, h = im.size
            return int(w) * int(h)
    except Exception:
        try:
            return path.stat().st_size
        except Exception:
            return 0

def find_cover_candidates() -> list[Path]:
    cands: list[Path] = []
    for folder in [IMGS_INBOX, DOCS]:
        if not folder.exists(): 
            continue
        for p in folder.rglob("*"):
            if not p.is_file():
                continue
            if p.suffix.lower() not in [".png",".jpg",".jpeg",".webp",".tif",".tiff"]:
                continue
            if re.search(r"(book\s*cover|[_-]cover(\.|$))", p.name, flags=re.I):
                cands.append(p)
    return cands

def select_best_cover(cands: list[Path]) -> Optional[Path]:
    if not cands:
        return None
    scored = sorted((( _image_resolution_score(p), p) for p in cands ), key=lambda t: (t[0], t[1].as_posix()))
    return scored[-1][1] if scored else None

def copy_and_rename_cover(title_slug: str, vol_num: int = 0) -> Optional[str]:
    best = select_best_cover(find_cover_candidates())
    if not best:
        return None
    dest = OUT_COVERS / f"Volume_{vol_num:02d}_{title_slug}_Cover{best.suffix.lower()}"
    dest.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(best, dest)
    return dest.relative_to(ROOT).as_posix()

# --- site asset mirroring ---------------------------------------------------

def mirror_assets_to_site(quiet: bool = False):
    """Make site self-contained by mirroring output/assets/ → output/site/assets/."""
    dest = OUT_SITE / "assets"
    if dest.exists():
        shutil.rmtree(dest, ignore_errors=True)
    if OUT_ASSETS.exists():
        shutil.copytree(OUT_ASSETS, dest)
        info("Mirrored output/assets → output/site/assets.", quiet)

# --- load config ------------------------------------------------------------

def load_config():
    cfg = {}
    cfg_path = DROP / "bookforge.json"
    if cfg_path.exists():
        try:
            cfg = json.loads(cfg_path.read_text(encoding="utf-8"))
        except Exception as e:
            print(f"[BookForge:WARN] Could not parse {cfg_path}: {e}", file=sys.stderr)
    return cfg

# --- main -------------------------------------------------------------------

def main() -> int:
    ap = argparse.ArgumentParser(description="BookForge — one-dropzone → one-output builder")
    ap.add_argument("--title", help="Override book title")
    ap.add_argument("--volume", type=int, default=None, help="Volume number (default 0)")
    ap.add_argument("--no-docx", action="store_true", help="Skip DOCX output")
    ap.add_argument("--no-html", action="store_true", help="Skip HTML site output")
    ap.add_argument("--no-pdf",  action="store_true", help="Skip PDF output")
    ap.add_argument("--no-site-assets", action="store_true", help="Do not mirror output/assets into output/site/assets")
    ap.add_argument("--dry-run", action="store_true", help="Parse & plan only; do not write outputs")
    ap.add_argument("--quiet",   action="store_true", help="Reduce console output")
    args = ap.parse_args()

    ensure_dirs()

    cfg = load_config()
    cfg_title = cfg.get("title")
    cfg_volume = cfg.get("volume", 0)

    info("Scanning dropzone/documents ...", args.quiet)
    raw_docs: list[Path] = []
    if DOCS.exists():
        for p in sorted(DOCS.rglob("*")):
            if not p.is_file():
                continue
            rel = p.relative_to(DOCS).as_posix()
            if IGNORE_RE.search(rel) or p.name.startswith("."):
                continue
            if p.suffix.lower() in [".md",".markdown",".txt",".docx"]:
                raw_docs.append(p)

    if not raw_docs:
        info("No documents found in dropzone/documents/. Nothing to do.", args.quiet)
        return 0

    # Convert → Markdown; strip YAML; normalise; fix fences
    converted: list[tuple[Path, str]] = []
    for p in raw_docs:
        try:
            md = to_markdown(p)
        except Exception as e:
            info(f"Skipping {p.name}: {e}", args.quiet)
            continue
        md = strip_yaml_front_matter(md)
        md = normalise_line_endings(md)
        md = add_lang_to_fences(md, default_lang="text")
        converted.append((p, md))

    # Title & volume
    book_title = args.title or cfg_title
    if not book_title:
        for p, md in converted:
            book_title = detect_title(md, p.stem)
            if book_title:
                break
    book_title = book_title or "Untitled Book"
    volume = cfg_volume if args.volume is None else args.volume
    book_slug = slugify(book_title)

    # Cover
    rel_cover = copy_and_rename_cover(book_slug, vol_num=volume)
    if rel_cover:
        info(f"Cover detected → {rel_cover}", args.quiet)
    else:
        info("No cover detected (optional).", args.quiet)

    # Categorise
    chapters = []
    forewords = []
    acks = []
    auto_index = 0
    for p, md in converted:
        first_lines = "\n".join(md.splitlines()[:5])
        title = detect_title(md, p.stem)
        slug = slugify(title)
        md2 = normalise_images_in_md(md, p, slug)
        if is_acknowledgements(p.name, first_lines):
            acks.append((999, slug, md2));  continue
        if is_foreword_or_purpose(p.name, first_lines):
            forewords.append((0, slug, md2));  continue
        cnum = detect_chapter_number(p.name + "\n" + md2)
        if cnum is None:
            cnum = auto_index;  auto_index += 10
        chapters.append((cnum, slug, md2))

    chapters.sort(key=lambda x: x[0])
    forewords.sort(key=lambda x: x[0])

    # Dry-run preview
    if args.dry_run:
        info(f"DRY RUN — Title: '{book_title}', Volume: {volume}", args.quiet)
        if rel_cover:
            info(f"DRY RUN — Cover: {rel_cover}", args.quiet)
        def names(lst): return [s for _, s, _ in lst]
        info(f"DRY RUN — Forewords: {names(forewords)}", args.quiet)
        info(f"DRY RUN — Chapters: {names(chapters)}", args.quiet)
        info(f"DRY RUN — Acknowledgements: {names(acks)}", args.quiet)
        return 0

    # Clear and write output/manuscript parts
    info("Writing normalised output/manuscript/*.md ...", args.quiet)
    for old in OUT_MANU.glob("*.md"):
        try: old.unlink()
        except Exception: pass

    for i, (_, slug, md) in enumerate(forewords, start=1):
        (OUT_MANU / f"00.{i:02d}_{slug}.md").write_text(md, encoding="utf-8")
    for idx, (_, slug, md) in enumerate(chapters, start=1):
        (OUT_MANU / f"10.{idx*10:02d}_{slug}.md").write_text(md, encoding="utf-8")
    for i, (_, slug, md) in enumerate(acks, start=1):
        (OUT_MANU / f"99.{i:02d}_{slug}.md").write_text(md, encoding="utf-8")

    # Assemble book.md (avoid '---', use '***')
    parts = []
    if rel_cover:
        parts.append(f"![Cover]({rel_cover})\n")
    parts.append(f"# {book_title}\n")
    parts.append("\n## Contents\n")
    for _, slug, _ in forewords:
        parts.append(f"- Foreword: {slug.replace('_',' ')}")
    for _, slug, _ in chapters:
        parts.append(f"- {slug.replace('_',' ')}")
    for _, slug, _ in acks:
        parts.append(f"- Acknowledgements: {slug.replace('_',' ')}")
    parts.append("\n***\n")
    for _, slug, md in forewords:
        parts.append(f"\n\n## Foreword: {slug.replace('_',' ')}\n");  parts.append(md)
    for _, slug, md in chapters:
        parts.append(f"\n\n## {slug.replace('_',' ')}\n");           parts.append(md)
    for _, slug, md in acks:
        parts.append(f"\n\n## Acknowledgements: {slug.replace('_',' ')}\n");  parts.append(md)
    book_md = "\n".join(parts).strip() + "\n"
    (OUT_MANU / "book.md").write_text(book_md, encoding="utf-8")

    # Emit toc.json at repo root
    toc = {
        "title": book_title,
        "volume": volume,
        "foreword": [s for _, s, _ in forewords],
        "chapters": [s for _, s, _ in chapters],
        "acknowledgements": [s for _, s, _ in acks],
        "output": "output/"
    }
    (ROOT / "toc.json").write_text(json.dumps(toc, indent=2), encoding="utf-8")

    # Build with Pandoc (if available)
    pandoc = find_pandoc()
    vol_base = OUT_BOOKS / f"Volume_{volume:02d}_{book_slug}"
    if not pandoc:
        info("Pandoc not found; wrote markdown only. Install Pandoc to produce DOCX/HTML/PDF.", args.quiet)
        info(f"Output: {(OUT_MANU/'book.md').relative_to(ROOT).as_posix()}", args.quiet)
        return 0

    # resource-path so images resolve
    resource_path = os.pathsep.join([
        str(ROOT),
        str(DROP),
        str(DOCS),
        str(OUT_ASSETS),
        str(OUT_AIMGS),
        str(OUT_COVERS),
        str(OUT_SITE)
    ])

    # Optional reference DOCX template
    ref_docx = ROOT / "tools" / "pandoc" / "reference.docx"
    ref_args = ["--reference-doc", str(ref_docx)] if ref_docx.exists() else []

    info("Building outputs ...", args.quiet)

    # DOCX
    if not args.no_docx:
        subprocess.check_call([
            pandoc, "-f", "gfm", str(OUT_MANU/"book.md"),
            "-o", str(vol_base.with_suffix(".docx")),
            "--resource-path", resource_path,
            *ref_args
        ])

    # HTML site → output/site/index.html
    if not args.no_html:
        css = OUT_SITE / "style.css"
        if not css.exists():
            css.write_text(
                "body{max-width:900px;margin:3rem auto;font-family:system-ui,Segoe UI,Arial,sans-serif;line-height:1.6;padding:0 1rem}"
                "img{max-width:100%;} h1,h2,h3{scroll-margin-top:80px}"
                ".toc,.contents{background:#f6f6f6;padding:1rem;border-radius:8px}\n",
                encoding="utf-8"
            )
        subprocess.check_call([
            pandoc, "-f", "gfm", "-s",
            str(OUT_MANU/"book.md"),
            "-o", str(OUT_SITE/"index.html"),
            "--metadata", f"title={book_title}",
            "--css", str(css),
            "--resource-path", resource_path,
            "--toc", "--toc-depth=3"
        ])
        # Make site self-contained
        if not args.no_site_assets:
            mirror_assets_to_site(args.quiet)

    # PDF → output/books/*.pdf
    if not args.no_pdf:
        engine = find_pdf_engine()
        if engine:
            subprocess.check_call([
                pandoc, "-f", "gfm",
                str(OUT_MANU/"book.md"),
                "-o", str(vol_base.with_suffix(".pdf")),
                "--pdf-engine", engine,
                "--resource-path", resource_path
            ])
        else:
            info("Skipping PDF (wkhtmltopdf or LaTeX engine not found).", args.quiet)

    info(f"Built in output/: books/, site/, manuscript/ (plus HTML/PDF if enabled).", args.quiet)
    return 0

# --- entry ------------------------------------------------------------------

if __name__ == "__main__":
    try:
        sys.exit(main())
    except subprocess.CalledProcessError as e:
        print(f"[BookForge:ERROR] Command failed: {e}", file=sys.stderr)
        sys.exit(e.returncode)
    except Exception as e:
        print(f"[BookForge:ERROR] {e}", file=sys.stderr)
        sys.exit(1)
# --- end --------------------------------------------------------------------