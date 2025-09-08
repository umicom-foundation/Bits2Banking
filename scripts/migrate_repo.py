#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Repo Migration Helper v1.1 — multi-book cleanup to per-book drop zones
- Created by: Umicom Foundation (https://umicom.foundation/)
- Date: 2025-09-09
- Description:
    Scans legacy folders (book/, bookcover/, chapters/, images/, raw_docs/, content/**,
    and old dropzone/documents) and proposes a plan to migrate files into per-book drop-zones:

        dropzone/<book-slug>/{documents,images}

    PLAN first (no changes). Use --apply to move with collision-safe renaming.
    Optionally --archive-legacy to move empty legacy folders into archive/legacy/.

Usage:
    python scripts/migrate_repo.py
    python scripts/migrate_repo.py --apply
    python scripts/migrate_repo.py --apply --archive-legacy
"""

import os, re, sys, json, shutil, argparse
from pathlib import Path
from typing import Dict, List, Tuple, Optional

ROOT = Path(__file__).resolve().parents[1]
DROP = ROOT / "dropzone"
ARCH = ROOT / "archive" / "legacy"

DOC_EXTS = {".md", ".markdown", ".txt", ".docx"}
IMG_EXTS = {".png", ".jpg", ".jpeg", ".webp", ".tif", ".tiff", ".gif"}

IGNORE_RE = re.compile(
    r'(^|/)(~\$|\.#|#.*#|Thumbs\.db|\.DS_Store|\.AppleDouble|\.LSOverride|desktop\.ini|\.swp$|\.tmp$|\.bak$|\.partial$|\.crdownload$)',
    flags=re.I
)

PROJECT_DOCS = {
    "README.md","CONTRIBUTING.md","CODE_OF_CONDUCT.md","SECURITY.md","SUPPORT.md",
    "ROADMAP.md","CHANGELOG.md","RELEASE.md","GOVERNANCE.md","mkdocs.yml"
}

def info(m): print(f"[Migrate] {m}")
def slugify(s: str) -> str:
    s = re.sub(r"[^\w\s-]", "", s, flags=re.UNICODE)
    s = re.sub(r"\s+", "-", s.strip())
    return re.sub(r"-+", "-", s).strip("-").lower()

def list_files(base: Path) -> List[Path]:
    out: List[Path] = []
    if not base.exists(): return out
    for p in base.rglob("*"):
        if p.is_file() and not IGNORE_RE.search(p.as_posix()) and not p.name.startswith("."):
            out.append(p)
    return out

def is_text(p: Path) -> bool: return p.suffix.lower() in DOC_EXTS
def is_image(p: Path) -> bool: return p.suffix.lower() in IMG_EXTS

def detect_books_from_content(content_dir: Path) -> Dict[str, List[Path]]:
    books: Dict[str, List[Path]] = {}
    if not content_dir.exists(): return books
    for sub in sorted(p for p in content_dir.iterdir() if p.is_dir()):
        slug = slugify(sub.name)
        files = list_files(sub)
        if files:
            books.setdefault(slug, []).extend(files)
    return books

def detect_legacy_default(repo_root: Path) -> List[Path]:
    candidates: List[Path] = []
    for d in ("chapters","book","bookcover","book_cover","images","raw_docs","raw docs","dropzone/documents"):
        p = repo_root / d
        if p.exists():
            candidates.extend(list_files(p))
    return candidates

def existing_dropzone_books(drop_dir: Path) -> Dict[str, List[Path]]:
    found = {}
    if not drop_dir.exists(): return found
    for sub in sorted(drop_dir.iterdir()):
        if not sub.is_dir(): continue
        if (sub/"documents").exists():
            found[sub.name] = list_files(sub)
    return found

def group_files_into_books() -> Tuple[Dict[str, Dict[str, List[Path]]], List[Path]]:
    plan: Dict[str, Dict[str, List[Path]]] = {}
    leftovers: List[Path] = []

    # 1) content/* → book by folder name
    for slug, files in detect_books_from_content(ROOT / "content").items():
        for f in files:
            bucket = "images" if is_image(f) else ("docs" if is_text(f) else "other")
            plan.setdefault(slug, {"docs":[], "images":[], "other":[]})[bucket].append(f)

    # 2) legacy locations → default to 'bits-to-banking'
    default_slug = "bits-to-banking"
    for f in detect_legacy_default(ROOT):
        # skip top-level project docs
        if f.name in PROJECT_DOCS and f.parent == ROOT: 
            continue
        # don't reassign if already planned
        already = any(f in plan[s][k] for s in plan for k in ("docs","images","other"))
        if already: continue
        bucket = "images" if is_image(f) else ("docs" if is_text(f) else "other")
        plan.setdefault(default_slug, {"docs":[], "images":[], "other":[]})[bucket].append(f)

    # 3) exclude files already inside proper dropzone/<book>/*
    dz_existing = existing_dropzone_books(DROP)
    dz_paths = {p for files in dz_existing.values() for p in files}
    for slug in list(plan.keys()):
        for k in ("docs","images","other"):
            plan[slug][k] = [p for p in plan[slug][k] if p not in dz_paths]

    # 4) leftovers not matched (ignore infra)
    infra = {"dropzone","output","archive",".git",".github","tools","scripts",".venv","venv","env"}
    for p in ROOT.rglob("*"):
        if not p.is_file(): continue
        if IGNORE_RE.search(p.as_posix()): continue
        if p.name in PROJECT_DOCS and p.parent == ROOT: continue
        top = p.relative_to(ROOT).parts[0]
        if top in infra: continue
        already = any(p in plan[s][k] for s in plan for k in ("docs","images","other"))
        if not already:
            leftovers.append(p)

    return plan, leftovers

def ensure_dropzone(slug: str) -> Tuple[Path, Path]:
    book_dir = DROP / slug
    docs_dir = book_dir / "documents"
    imgs_dir = book_dir / "images"
    docs_dir.mkdir(parents=True, exist_ok=True)
    imgs_dir.mkdir(parents=True, exist_ok=True)
    return docs_dir, imgs_dir

def safe_move(src: Path, dest_dir: Path) -> Path:
    dest_dir.mkdir(parents=True, exist_ok=True)
    candidate = dest_dir / src.name
    if not candidate.exists():
        shutil.move(str(src), str(candidate))
        return candidate
    stem, ext = candidate.stem, candidate.suffix
    i = 1
    while True:
        alt = dest_dir / f"{stem}_{i}{ext}"
        if not alt.exists():
            shutil.move(str(src), str(alt))
            return alt
        i += 1

def archive_empty_legacy():
    ARCH.mkdir(parents=True, exist_ok=True)
    legacy_roots = [
        ROOT/"book", ROOT/"bookcover", ROOT/"book_cover",
        ROOT/"chapters", ROOT/"images", ROOT/"raw_docs", ROOT/"raw docs",
        ROOT/"content", ROOT/"dropzone"/"documents"
    ]
    for d in legacy_roots:
        if d.exists():
            # move dir if empty (or only empty subdirs)
            empty = True
            for _ in d.rglob("*"):
                empty = False
                break
            if empty:
                dest = ARCH / d.name
                if dest.exists(): shutil.rmtree(dest, ignore_errors=True)
                shutil.move(str(d), str(dest))
                info(f"Archived empty legacy folder → {dest.relative_to(ROOT)}")

def main():
    ap = argparse.ArgumentParser(description="Migrate legacy repo content into per-book drop zones")
    ap.add_argument("--apply", action="store_true", help="Perform the moves (default is plan only)")
    ap.add_argument("--archive-legacy", action="store_true", help="After apply, archive empty legacy folders")
    args = ap.parse_args()

    plan, leftovers = group_files_into_books()

    # Show plan
    print("\n=== MIGRATION PLAN (dry-run) ===")
    for slug in sorted(plan.keys()):
        docs = plan[slug]["docs"]; imgs = plan[slug]["images"]; oth = plan[slug]["other"]
        print(f"\nBook: {slug}  →  dropzone/{slug}/{{documents,images}}")
        if docs:
            print(f"  docs ({len(docs)}):")
            for p in docs[:10]: print(f"    - {p.relative_to(ROOT)}")
            if len(docs) > 10: print(f"    ... +{len(docs)-10} more")
        if imgs:
            print(f"  images ({len(imgs)}):")
            for p in imgs[:10]: print(f"    - {p.relative_to(ROOT)}")
            if len(imgs) > 10: print(f"    ... +{len(imgs)-10} more")
        if oth:
            print(f"  other ({len(oth)}):")
            for p in oth[:5]: print(f"    - {p.relative_to(ROOT)}")
            if len(oth) > 5: print(f"    ... +{len(oth)-5} more")

    if leftovers:
        print(f"\nUnassigned leftovers ({len(leftovers)}):")
        for p in leftovers[:15]: print(f"  - {p.relative_to(ROOT)}")
        if len(leftovers) > 15: print(f"  ... +{len(leftovers)-15} more")

    # Write plan file
    (ROOT/"migration_plan.json").write_text(
        json.dumps({
            "books": {
                slug: {
                    "docs":   [str(p.relative_to(ROOT)) for p in plan[slug]["docs"]],
                    "images": [str(p.relative_to(ROOT)) for p in plan[slug]["images"]],
                    "other":  [str(p.relative_to(ROOT)) for p in plan[slug]["other"]],
                } for slug in sorted(plan.keys())
            },
            "leftovers": [str(p.relative_to(ROOT)) for p in leftovers]
        }, indent=2),
        encoding="utf-8"
    )
    print("\nPlan written to migration_plan.json")

    if not args.apply:
        print("\nRun again with --apply to perform moves.")
        return 0

    # Apply
    print("\n=== APPLYING MIGRATION ===")
    moved = 0
    for slug in sorted(plan.keys()):
        docs_dir, imgs_dir = ensure_dropzone(slug)
        for p in plan[slug]["docs"]:
            dst = safe_move(p, docs_dir); moved += 1
            print(f"  DOC  {p.relative_to(ROOT)}  →  {dst.relative_to(ROOT)}")
        for p in plan[slug]["images"]:
            dst = safe_move(p, imgs_dir); moved += 1
            print(f"  IMG  {p.relative_to(ROOT)}  →  {dst.relative_to(ROOT)}")
        # 'other' left untouched (templates/scripts/etc.)

    print(f"\nDone. Moved {moved} files into dropzone/*.")

    if args.archive_legacy:
        archive_empty_legacy()

    print("\nNext:")
    print("  - Inspect dropzone/<book>/documents and images.")
    print("  - Build locally:  python scripts/forge_all.py")
    print("  - Commit and push to trigger CI.")
    return 0

if __name__ == "__main__":
    sys.exit(main())
