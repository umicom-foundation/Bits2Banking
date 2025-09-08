#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Repo Migration Helper v1.0 — multi-book cleanup to per-book drop zones
- Created by: Umicom Foundation (https://umicom.foundation/)
- Date: 08-09-2025
- Description:
    Scans legacy folders (book/, bookcover/, chapters/, images/, raw_docs/, content/**, etc.)
    and proposes a plan to migrate files into per-book drop-zones:

        dropzone/<book-slug>/documents
        dropzone/<book-slug>/images

    By default, runs in PLAN mode (no changes). Pass --apply to execute the plan.
    Safe move with collision-proof renaming. Optionally archives legacy folders.

Usage:
    python scripts/migrate_repo.py                # plan only
    python scripts/migrate_repo.py --apply        # perform moves
    python scripts/migrate_repo.py --apply --archive-legacy

Notes:
    - Idempotent: re-running after a partial move is safe.
    - Does not touch output/ or .github/
    - Does not modify file contents; BookForge will normalise on build.
"""

import os, re, sys, json, shutil, argparse
from pathlib import Path
from typing import Dict, List, Tuple, Optional

ROOT = Path(__file__).resolve().parents[1]
DROP = ROOT / "dropzone"
ARCH = ROOT / "archive" / "legacy"

# File type sets
DOC_EXTS  = {".md", ".markdown", ".txt", ".docx"}
IMG_EXTS  = {".png", ".jpg", ".jpeg", ".webp", ".tif", ".tiff", ".gif"}

# Ignore junk
IGNORE_RE = re.compile(
    r'(^|/)(~\$|\.#|#.*#|Thumbs\.db|\.DS_Store|\.AppleDouble|\.LSOverride|desktop\.ini|\.swp$|\.tmp$|\.bak$|\.partial$|\.crdownload$)',
    flags=re.I
)

def info(msg: str):  print(f"[Migrate] {msg}")
def warn(msg: str):  print(f"[Migrate:WARN] {msg}")
def err (msg: str):  print(f"[Migrate:ERROR] {msg}", file=sys.stderr)

def slugify(s: str) -> str:
    s = re.sub(r"[^\w\s-]", "", s, flags=re.UNICODE)
    s = re.sub(r"\s+", "-", s.strip())
    return re.sub(r"-+", "-", s).strip("-").lower()

def list_files(base: Path) -> List[Path]:
    out: List[Path] = []
    if not base.exists():
        return out
    for p in base.rglob("*"):
        if not p.is_file(): continue
        rel = p.relative_to(ROOT).as_posix()
        if IGNORE_RE.search(rel) or p.name.startswith("."): continue
        out.append(p)
    return out

def is_text(p: Path) -> bool: return p.suffix.lower() in DOC_EXTS
def is_image(p: Path) -> bool: return p.suffix.lower() in IMG_EXTS

def detect_books_from_content(content_dir: Path) -> Dict[str, List[Path]]:
    """
    content/<name>/... → book slug from <name>
    """
    books: Dict[str, List[Path]] = {}
    if not content_dir.exists(): return books
    for sub in sorted(p for p in content_dir.iterdir() if p.is_dir()):
        slug = slugify(sub.name)
        files = list_files(sub)
        if files:
            books.setdefault(slug, []).extend(files)
    return books

def detect_bits_to_banking_default(repo_root: Path) -> List[Path]:
    """
    If chapters/ or book*/images or root images exist, assume Bits-to-Banking unless overridden.
    """
    candidates: List[Path] = []
    for d in ("chapters", "book", "bookcover", "book_cover", "images", "raw_docs", "raw docs"):
        p = repo_root / d
        if p.exists():
            candidates.extend(list_files(p))
    return candidates

def existing_dropzone_books(drop_dir: Path) -> Dict[str, List[Path]]:
    """
    Already-migrated books under dropzone/ (we won't move these).
    """
    found: Dict[str, List[Path]] = {}
    if not drop_dir.exists(): return found
    for sub in sorted(drop_dir.iterdir()):
        if not sub.is_dir(): continue
        slug = sub.name
        # Recognise a book if it has documents/ or images/
        docs = sub / "documents"
        imgs = sub / "images"
        if docs.exists() or imgs.exists():
            found[slug] = list_files(sub)
    return found

def group_files_into_books() -> Tuple[Dict[str, Dict[str, List[Path]]], List[Path]]:
    """
    Returns:
      plan = {slug: {"docs":[...], "images":[...], "other":[...]}}
      leftovers = [unassigned paths]
    """
    plan: Dict[str, Dict[str, List[Path]]] = {}
    leftovers: List[Path] = []

    # 1) Explicit books under content/*
    content_books = detect_books_from_content(ROOT / "content")
    for slug, files in content_books.items():
        for f in files:
            bucket = "images" if is_image(f) else ("docs" if is_text(f) else "other")
            plan.setdefault(slug, {"docs":[], "images":[], "other":[]})[bucket].append(f)

    # 2) Default legacy buckets → bits-to-banking (overridable later if needed)
    b2b_slug = "bits-to-banking"
    for f in detect_bits_to_banking_default(ROOT):
        # If file already assigned via content/*, skip
        already = any(f in plan[s][k] for s in plan for k in ("docs","images","other"))
        if already: continue
        bucket = "images" if is_image(f) else ("docs" if is_text(f) else "other")
        plan.setdefault(b2b_slug, {"docs":[], "images":[], "other":[]})[bucket].append(f)

    # 3) Anything else at root we can heuristically slot?
    #    If a top-level folder has many text files, treat it as a book.
    for sub in sorted(p for p in ROOT.iterdir()
                      if p.is_dir() and p.name not in {
                          "dropzone","output","archive",".git",".github","tools","scripts",
                          "content","volumes","docs","book","bookcover","book_cover","chapters",
                          "images","raw_docs","raw docs"
                      }):
        files = list_files(sub)
        text_count = sum(1 for x in files if is_text(x))
        if text_count >= 3:
            slug = slugify(sub.name)
            for f in files:
                bucket = "images" if is_image(f) else ("docs" if is_text(f) else "other")
                plan.setdefault(slug, {"docs":[], "images":[], "other":[]})[bucket].append(f)
        else:
            leftovers.extend(files)

    # 4) Exclude any already under dropzone/* (migrated)
    dz_existing = existing_dropzone_books(DROP)
    dz_paths = {p for files in dz_existing.values() for p in files}
    for slug in list(plan.keys()):
        for k in ("docs","images","other"):
            plan[slug][k] = [p for p in plan[slug][k] if p not in dz_paths]

    # 5) Collect leftovers not matched above, excluding output & infra
    infra = ("dropzone","output","archive",".git",".github","tools","scripts")
    for p in ROOT.rglob("*"):
        if not p.is_file(): continue
        if IGNORE_RE.search(p.as_posix()): continue
