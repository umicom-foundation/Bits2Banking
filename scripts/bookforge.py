#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
BookForge v3.1 — single-book builder for the Open Book project
- Created by: Umicom Foundation (https://umicom.foundation/)
- Date: 08-09-2025
- Description:
    Build exactly one book from a per-book drop-zone:
      dropzone/<book-slug>/{documents,images}
    Outputs:
      output/<book-slug>/manuscript/*.md (incl. book.md)
      output/<book-slug>/books/*.docx (and .pdf if engine present)
      output/<book-slug>/site/index.html (self-contained site)
    If --book-dir is omitted and exactly one book is present under dropzone/,
    it will auto-select that one. If multiple exist, it prints a list and exits.

CLI:
  python scripts/bookforge.py [--book-dir dropzone/<book-slug>]
  [--title "Display Title"] [--author "Name"] [--volume 0]
  [--no-docx] [--no-html] [--no-pdf] [--no-site-assets]
  [--dry-run] [--quiet]

Optional config (dropzone/<book-slug>/bookforge.json):
  { "title": "Title", "author": "Name", "volume": 0 }

Env:
  PANDOC_EXE, WKHTMLTOPDF_EXE, PANDOC_PDF_ENGINE
"""

import os, re, sys, json, shutil, argparse, subprocess
from pathlib import Path
from typing import Optional, Tuple, List

ROOT = Path(__file__).resolve().parents[1]
DROP = ROOT / "dropzone"

# Junk we ignore
IGNORE_RE = re.compile(
    r'(^|/)(~\$|\.#|#.*#|Thumbs\.db|\.DS_Store|\.AppleDouble|\.LSOverride|desktop\.ini|\.swp$|\.tmp$|\.bak$|\.partial$|\.crdownload$)',
    flags=re.I
)

def info(msg: str, quiet: bool = False):
    if not quiet:
        print(f"[BookForge] {msg}")

def slugify(s: str) -> str:
    s = re.sub(r"[^\w\s-]", "", s, flags=re.UNICODE)
    s = re.sub(r"\s+", "-", s.strip())
    return re.sub(r"-+", "-", s).strip("-").lower()

def read(p: Path) -> str:
    try:    return p.read_text(encoding="utf-8")
    except: return p.read_text(encoding="utf-8", errors="ignore")

def norm_eol(s: str) -> str:
    return s.replace("\r\n","\n").replace("\r","\n")

def add_lang_fences(md: str, default="text") -> str:
    return re.sub(r"(?m)^```[ \t]*\n", f"```{default}\n", md)

def find_pandoc() -> Optional[str]:
    p = os.environ.get("PANDOC_EXE")
    if p and Path(p).exists(): return p
    local = ROOT / "tools" / "pandoc" / ("pandoc.exe" if os.name=="nt" else "pandoc")
    if local.exists(): return str(local)
    return shutil.which("pandoc")

def find_pdf_engine() -> Optional[str]:
    env = os.environ.get("PANDOC_PDF_ENGINE")
    if env: return env
    wk = os.environ.get("WKHTMLTOPDF_EXE")
    if wk and Path(wk).exists(): return wk
    which = shutil.which("wkhtmltopdf")
    if which: return which
    for c in [Path(r"C:\Program Files\wkhtmltopdf\bin\wkhtmltopdf.exe"),
              Path(r"C:\Program Files (x86)\wkhtmltopdf\bin\wkhtmltopdf.exe")]:
        if c.exists(): return str(c)
    for latex in ("xelatex","pdflatex","lualatex"):
        if shutil.which(latex): return latex
    return None

def docx_to_md(p: Path) -> str:
    try:
        from docx import Document  # type: ignore
        doc = Document(str(p))
        lines = [(para.text or "").rstrip() for para in doc.paragraphs]
        return "\n".join(lines) + "\n"
    except Exception:
        pan = find_pandoc()
        if not pan:
            raise RuntimeError("DOCX support requires python-docx or Pandoc installed.")
        return subprocess.check_output([pan,"-f","docx","-t","gfm",str(p)], text=True)

def to_markdown(p: Path) -> str:
    ext = p.suffix.lower()
    if ext in (".md",".markdown",".txt"): return read(p)
    if ext == ".docx":                    return docx_to_md(p)
    raise RuntimeError(f"Unsupported file type: {p.name}")

def strip_yaml(md: str) -> str:
    s = md.lstrip()
    if s.startswith("---"):
        lines = s.splitlines(True)
        if lines and lines[0].strip()=="---":
            for i in range(1,len(lines)):
                if lines[i].strip() in ("---","..."):
                    return "".join(lines[i+1:])
    return md

def detect_title(md: str, fallback: str) -> str:
    m = re.search(r"^\s*#\s+(.+)$", md, flags=re.M)
    return m.group(1).strip() if m else fallback

def detect_ch_num(text: str) -> Optional[int]:
    m = re.search(r"(?:^|[^a-z])chapter\s*(\d+)", text, flags=re.I)
    if m: return int(m.group(1))
    m = re.search(r"^\s*(\d{1,2})[._-]", text)
    if m: return int(m.group(1))
    m = re.search(r"(?:^|[\s_-])(\d{1,2})(?:[\s_-]|$)", text)
    if m: return int(m.group(1))
    return None

def is_acks(name: str, first_lines: str) -> bool:
    # Match both US & UK spellings for the "acknowledg…nt(s)" section, avoiding a standalone token that the linter dislikes.
    patt = r"acknowledg(?:e)?m(?:e)?nt(?:s)?"
    return bool(
        re.search(patt, name, flags=re.I) or
        re.search(rf"^\s*#\s+{patt}\s*$", first_lines, flags=re.I|re.M)
    )

def is_frontmatter(name: str, first_lines: str) -> bool:
    key = r"(foreword|preface|purpose|introduction)"
    return bool(
        re.search(key, name, flags=re.I) or
        re.search(rf"^\s*#\s+{key}\s*$", first_lines, flags=re.I|re.M)
    )

def copy_image(src: Path, out_imgs: Path, chapter_slug: str, idx: int) -> Optional[str]:
    if not src.exists(): return None
    ext = (src.suffix or ".png").lower()
    dst = out_imgs / f"{chapter_slug}_fig{idx:02d}{ext}"
    dst.parent.mkdir(parents=True, exist_ok=True)
    try:
        shutil.copy2(src, dst)
        return dst
    except Exception:
        return None

def rewrite_images(md: str, doc_path: Path, out_imgs: Path, chapter_slug: str, repo_root: Path) -> str:
    n = 1
    def repl(m: re.Match) -> str:
        nonlocal n
        alt, url = m.group(1), m.group(2).strip()
        if re.match(r"^(https?://|data:)", url, flags=re.I): return m.group(0)
        src = (doc_path.parent / url).resolve()
        if not src.exists():
            inbox = (doc_path.parent.parent / "images" / url).resolve()  # try book images/
            if inbox.exists(): src = inbox
        dst = copy_image(src, out_imgs, chapter_slug, n)
        if dst:
            n += 1
            rel = dst.relative_to(repo_root).as_posix()
            return f"![{alt}]({rel})"
        return m.group(0)
    return re.sub(r"!\[([^\]]*)\]\(([^)]+)\)", repl, md)

def find_cover(images_dir: Path, docs_dir: Path) -> Optional[Path]:
    cands: List[Path] = []
    for folder in (images_dir, docs_dir):
        if not folder.exists(): continue
        for p in folder.rglob("*"):
            if not p.is_file(): continue
            if p.suffix.lower() not in (".png",".jpg",".jpeg",".webp",".tif",".tiff"): continue
            if re.search(r"(book\s*cover|[_-]cover(\.|$))", p.name, flags=re.I):
                cands.append(p)
    if not cands: return None
    try:
        from PIL import Image  # type: ignore
        scored = []
        for p in cands:
            try:
                with Image.open(str(p)) as im:
                    w,h = im.size
                    scored.append((w*h, p))
            except Exception:
                scored.append((p.stat().st_size, p))
        scored.sort(key=lambda t: (t[0], t[1].as_posix()))
        return scored[-1][1]
    except Exception:
        cands.sort(key=lambda p: (p.stat().st_size, p.as_posix()))
        return cands[-1]

def load_cfg(book_dir: Path) -> dict:
    cfg = {}
    cfg_path = book_dir / "bookforge.json"
    if cfg_path.exists():
        try:
            cfg = json.loads(cfg_path.read_text(encoding="utf-8"))
        except Exception as e:
            print(f"[BookForge:WARN] Could not parse {cfg_path}: {e}", file=sys.stderr)
    return cfg

def detect_books_under_dropzone() -> List[Path]:
    books: List[Path] = []
    if not DROP.exists(): return books
    for sub in sorted(DROP.iterdir()):
        if not sub.is_dir(): continue
        if (sub / "documents").exists():
            books.append(sub.resolve())
    return books

def main() -> int:
    ap = argparse.ArgumentParser(description="BookForge v3.1 — build one book (auto-detect single)")
    ap.add_argument("--book-dir", help="Path to the book drop-zone (dropzone/<book-slug>)")
    ap.add_argument("--title", help="Override display title")
    ap.add_argument("--author", help="Author name")
    ap.add_argument("--volume", type=int, default=None, help="Volume number (default 0)")
    ap.add_argument("--no-docx", action="store_true")
    ap.add_argument("--no-html", action="store_true")
    ap.add_argument("--no-pdf",  action="store_true")
    ap.add_argument("--no-site-assets", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--quiet",   action="store_true")
    args = ap.parse_args()

    # Resolve book directory (allow auto-detect if omitted)
    if args.book_dir:
        book_dir = Path(args.book_dir).resolve()
    else:
        candidates = detect_books_under_dropzone()
        if len(candidates) == 0:
            print("[BookForge] No books found under dropzone/. Create dropzone/<book>/documents first.", file=sys.stderr)
            return 2
        if len(candidates) > 1:
            print("[BookForge] Multiple books detected. Please specify one with --book-dir:", file=sys.stderr)
            for c in candidates:
                print(f"  - {c.relative_to(ROOT)}", file=sys.stderr)
            return 2
        book_dir = candidates[0]
        info(f"Auto-selected book: {book_dir.relative_to(ROOT)}", args.quiet)

    docs_dir = book_dir / "documents"
    imgs_dir = book_dir / "images"
    if not docs_dir.exists():
        info(f"Missing {docs_dir}; nothing to do.", args.quiet)
        return 0

    # derive slug from folder name
    book_slug = book_dir.name
    cfg = load_cfg(book_dir)
    title = args.title or cfg.get("title")
    author = args.author or cfg.get("author")
    volume = cfg.get("volume", 0) if args.volume is None else args.volume

    # collect inputs
    inputs: List[Path] = []
    for p in sorted(docs_dir.rglob("*")):
        if not p.is_file(): continue
        if IGNORE_RE.search(p.as_posix()) or p.name.startswith("."): continue
        if p.suffix.lower() in (".md",".markdown",".txt",".docx"):
            inputs.append(p)
    if not inputs:
        info("No documents found; nothing to do.", args.quiet)
        return 0

    # convert + normalise
    converted: List[Tuple[Path,str]] = []
    for p in inputs:
        try: md = to_markdown(p)
        except Exception as e:
            info(f"Skipping {p.name}: {e}", args.quiet); continue
        md = strip_yaml(md)
        md = norm_eol(md)
        md = add_lang_fences(md)
        converted.append((p, md))

    # title fallback from first heading
    if not title:
        for p,md in converted:
            t = detect_title(md, p.stem)
            if t:
                title = t
                break
    title = title or "Untitled Book"

    # outputs
    out_root = ROOT / "output" / book_slug
    out_manu = out_root / "manuscript"
    out_assets = out_root / "assets"
    out_covers = out_assets / "covers"
    out_imgs = out_assets / "images"
    out_books = out_root / "books"
    out_site  = out_root / "site"
    for d in (out_manu,out_assets,out_covers,out_imgs,out_books,out_site):
        d.mkdir(parents=True, exist_ok=True)

    # cover
    rel_cover = None
    cover = find_cover(imgs_dir, docs_dir)
    if cover:
        dst = out_covers / f"Volume_{volume:02d}_{slugify(title)}_cover{cover.suffix.lower()}"
        shutil.copy2(cover, dst)
        rel_cover = dst.relative_to(ROOT).as_posix()
        info(f"Cover → {rel_cover}", args.quiet)
    else:
        info("No cover detected (optional).", args.quiet)

    # categorise
    chapters = []; fronts = []; acks = []
    auto = 0
    for p, md in converted:
        first = "\n".join(md.splitlines()[:5])
        ch_title = detect_title(md, p.stem)
        ch_slug  = slugify(ch_title)
        md2 = rewrite_images(md, p, out_imgs, ch_slug, ROOT)
        if is_acks(p.name, first):
            acks.append((999, ch_slug, md2));  continue
        if is_frontmatter(p.name, first):
            fronts.append((0, ch_slug, md2));  continue
        n = detect_ch_num(p.name + "\n" + md2)
        if n is None: n, auto = auto, auto+10
        chapters.append((n, ch_slug, md2))

    chapters.sort(key=lambda x: x[0])
    fronts.sort(key=lambda x: x[0])

    # dry-run
    if args.dry_run:
        info(f"DRY RUN — {book_slug}: '{title}' (vol {volume})", args.quiet)
        def names(xs): return [s for _,s,_ in xs]
        if rel_cover: info(f"Cover: {rel_cover}", args.quiet)
        info(f"Front: {names(fronts)}", args.quiet)
        info(f"Chapters: {names(chapters)}", args.quiet)
        info(f"Acks: {names(acks)}", args.quiet)
        return 0

    # clear old manuscript
    for old in out_manu.glob("*.md"):
        try: old.unlink()
        except: pass

    # write parts
    for i,(_, s, md) in enumerate(fronts, start=1):
        (out_manu / f"00.{i:02d}_{s}.md").write_text(md, encoding="utf-8")
    for idx,(_, s, md) in enumerate(chapters, start=1):
        (out_manu / f"10.{idx*10:02d}_{s}.md").write_text(md, encoding="utf-8")
    for i,(_, s, md) in enumerate(acks, start=1):
        (out_manu / f"99.{i:02d}_{s}.md").write_text(md, encoding="utf-8")

    # assemble book.md
    parts = []
    if rel_cover: parts.append(f"![Cover]({rel_cover})\n")
    parts.append(f"# {title}\n")
    if (args.author or (book_dir/"bookforge.json").exists()):
        author = (args.author or json.loads((book_dir/"bookforge.json").read_text(encoding="utf-8")).get("author"))
        if author: parts.append(f"\n**{author}**\n")
    parts.append("\n## Contents\n")
    for _,s,_ in fronts:   parts.append(f"- Foreword: {s.replace('-',' ')}")
    for _,s,_ in chapters: parts.append(f"- {s.replace('-',' ')}")
    for _,s,_ in acks:     parts.append(f"- Acknowledgements: {s.replace('-',' ')}")
    parts.append("\n***\n")
    for _,s,md in fronts:   parts.append(f"\n\n## Foreword: {s.replace('-',' ')}\n"); parts.append(md)
    for _,s,md in chapters: parts.append(f"\n\n## {s.replace('-',' ')}\n");           parts.append(md)
    for _,s,md in acks:     parts.append(f"\n\n## Acknowledgements: {s.replace('-',' ')}\n"); parts.append(md)
    book_md = "\n".join(parts).strip() + "\n"
    (out_manu / "book.md").write_text(book_md, encoding="utf-8")

    # toc.json (per book)
    toc = {
        "slug": book_slug, "title": title, "volume": volume,
        "front": [s for _,s,_ in fronts],
        "chapters": [s for _,s,_ in chapters],
        "acknowledgements": [s for _,s,_ in acks],
        "output": f"output/{book_slug}/"
    }
    (out_root / "toc.json").write_text(json.dumps(toc, indent=2), encoding="utf-8")

    # build with Pandoc
    pan = find_pandoc()
    base = out_books / f"Volume_{volume:02d}_{slugify(title)}"
    if not pan:
        info("Pandoc not found; wrote markdown only.", args.quiet)
    else:
        rpath = os.pathsep.join([
            str(ROOT), str(book_dir), str(docs_dir),
            str(out_root), str(out_manu), str(out_assets)
        ])
        ref_docx = ROOT / "tools" / "pandoc" / "reference.docx"
        ref_args = ["--reference-doc", str(ref_docx)] if ref_docx.exists() else []

        # DOCX
        if not args.no_docx:
            subprocess.check_call([
                pan, "-f","gfm", str(out_manu/"book.md"),
                "-o", str(base.with_suffix(".docx")),
                "--resource-path", rpath,
                *ref_args
            ])

        # HTML site
        if not args.no_html:
            css = out_site / "style.css"
            if not css.exists():
                css.write_text(
                    "body{max-width:900px;margin:3rem auto;font-family:system-ui,Segoe UI,Arial,sans-serif;line-height:1.6;padding:0 1rem}"
                    "img{max-width:100%;} h1,h2,h3{scroll-margin-top:80px}"
                    ".toc,.contents{background:#f6f6f6;padding:1rem;border-radius:8px}\n",
                    encoding="utf-8"
                )
            subprocess.check_call([
                pan, "-f","gfm","-s",
                str(out_manu/"book.md"),
                "-o", str(out_site/"index.html"),
                "--metadata", f"title={title}",
                "--css", str(css),
                "--resource-path", rpath,
                "--toc","--toc-depth=3"
            ])
            if not args.no_site_assets:
                dest = out_site / "assets"
                if dest.exists(): shutil.rmtree(dest, ignore_errors=True)
                if out_assets.exists(): shutil.copytree(out_assets, dest)

        # PDF
        if not args.no_pdf:
            engine = find_pdf_engine()
            if engine:
                subprocess.check_call([
                    pan, "-f","gfm",
                    str(out_manu/"book.md"),
                    "-o", str(base.with_suffix(".pdf")),
                    "--pdf-engine", engine,
                    "--resource-path", rpath
                ])
            else:
                info("Skipping PDF (no wkhtmltopdf/LaTeX engine).", args.quiet)

    info(f"Built: output/{book_slug}/ (manuscript/books/site)", args.quiet)
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
