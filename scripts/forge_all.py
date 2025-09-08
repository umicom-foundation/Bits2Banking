#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Forge All v1.0 — multi-book orchestrator
- Created by: Umicom Foundation
- Date: 08-09-2025
- Description:
    Detect per-book drop-zones under dropzone/* and build each one by
    invoking scripts/bookforge.py. Optionally build only those that changed
    since a given Git commit. Also generates a catalog site at:
        output/site/index.html
    that links to each book's site at output/<slug>/site/.

CLI:
  python scripts/forge_all.py               # build all books
  python scripts/forge_all.py --changed-only BASE_SHA
"""

import os, sys, subprocess, json, shutil
from pathlib import Path
from typing import List, Set

ROOT = Path(__file__).resolve().parents[1]
DROP = ROOT / "dropzone"
OUT  = ROOT / "output"

def run(cmd: list[str]) -> int:
    return subprocess.call(cmd)

def list_books() -> List[Path]:
    books = []
    if DROP.exists():
        for p in sorted(DROP.iterdir()):
            if p.is_dir() and (p/"documents").exists():
                books.append(p)
    return books

def changed_books(base_sha: str) -> Set[str]:
    # Use git to find changed paths and map to top-level book dirs under dropzone/
    try:
        out = subprocess.check_output(["git","diff","--name-only", f"{base_sha}..HEAD"], text=True)
        paths = [l.strip() for l in out.splitlines() if l.strip()]
    except Exception:
        return set()
    slugs: Set[str] = set()
    for p in paths:
        if not p.startswith("dropzone/"): continue
        parts = p.split("/")
        if len(parts) >= 3:
            slugs.add(parts[1])  # dropzone/<slug>/...
    return slugs

def catalog(books: List[Path]):
    site_root = OUT / "site"
    site_root.mkdir(parents=True, exist_ok=True)
    # Copy each per-book site to catalog subtree: output/site/<slug>/
    for b in books:
        slug = b.name
        src = OUT / slug / "site"
        dst = site_root / slug
        if dst.exists(): shutil.rmtree(dst, ignore_errors=True)
        if src.exists(): shutil.copytree(src, dst)

    # Write index.html
    items = []
    for b in books:
        slug = b.name
        toc = OUT / slug / "toc.json"
        title = slug
        if toc.exists():
            try:
                meta = json.loads(toc.read_text(encoding="utf-8"))
                title = meta.get("title", slug)
            except Exception:
                pass
        items.append(f'<li><a href="{slug}/index.html">{title}</a></li>')
    html = f"""<!doctype html><meta charset="utf-8">
<title>Open Book — Catalog</title>
<style>body{{max-width:900px;margin:2rem auto;font-family:system-ui,Segoe UI,Arial,sans-serif;line-height:1.6;padding:0 1rem}}</style>
<h1>Open Book — Catalog</h1>
<p>Browse generated books:</p>
<ul>
{''.join(items) if items else '<li>(no books yet)</li>'}
</ul>
"""
    (site_root/"index.html").write_text(html, encoding="utf-8")

def main(argv: List[str]) -> int:
    changed_only = False
    base = None
    if len(argv) >= 2 and argv[1] == "--changed-only":
        changed_only = True
        base = argv[2] if len(argv) >= 3 else None
    books = list_books()
    if changed_only and base:
        slugs = changed_books(base)
        books = [b for b in books if b.name in slugs]
    if not books:
        print("[ForgeAll] No books to build.")
        catalog([])  # still produce an empty catalog
        return 0

    print(f"[ForgeAll] Building {len(books)} book(s): " + ", ".join(b.name for b in books))
    for b in books:
        rc = run([sys.executable, str(ROOT/"scripts"/"bookforge.py"), "--book-dir", str(b)])
        if rc != 0:
            print(f"[ForgeAll] ERROR building {b.name} (rc={rc})")
            return rc

    catalog(books)
    print("[ForgeAll] Catalog updated at output/site/index.html")
    return 0

if __name__ == "__main__":
    sys.exit(main(sys.argv))

