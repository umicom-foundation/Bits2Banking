#!/usr/bin/env python3
"""
make_book.py

Combine a volume's chapters into one Markdown file and build an EPUB with Pandoc.

- Reads content/<volume>/volume.yml with fields:
    title:  "Volume Title"
    author: "Author or Project"
    cover:  "images/islam_bookcover.png"   # optional; can be omitted
    chapters:
      - introduction_to_islam.md
      - history_of_money.md
      - ...

- Writes:
    book/<volume>_combined.md
    book/<volume>.epub

Priority for cover image:
1) --cover CLI argument (if provided and exists)
2) 'cover' in volume.yml (if present and exists)
3) Auto-search under images/ with patterns:
   *<volume>*cover.*, *<volume>*bookcover.*, *bookcover.*, *cover.*

Optional:
--copy-cover  -> copy the chosen cover to bookcover/<volume>_cover.<ext> and use that path

"""

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Optional, List

import yaml


def run(cmd: List[str]) -> None:
    print("+", " ".join(cmd))
    subprocess.check_call(cmd)


def resolve_path(repo_root: Path, p: str) -> Path:
    """Resolve a path that may be absolute or relative to repo_root."""
    pp = Path(p)
    return pp if pp.is_absolute() else (repo_root / pp)


def pick_cover(repo_root: Path, volume: str, cli_cover: Optional[str], meta_cover: Optional[str]) -> Optional[Path]:
    """Choose a cover image path by priority, else search in images/."""
    # 1) CLI
    if cli_cover:
        p = resolve_path(repo_root, cli_cover)
        if p.exists():
            return p
        print(f"WARNING: --cover given but not found: {cli_cover}")

    # 2) volume.yml 'cover'
    if meta_cover:
        p = resolve_path(repo_root, meta_cover)
        if p.exists():
            return p
        print(f"WARNING: cover from volume.yml not found: {meta_cover}")

    # 3) auto-search in images/
    images_dir = repo_root / "images"
    if images_dir.exists():
        # Prefer names tied to the volume, then generic bookcover/cover names.
        patterns = [
            f"*{volume}*cover.*",
            f"*{volume}*bookcover.*",
            "*bookcover.*",
            "*cover.*",
        ]
        for pat in patterns:
            matches = sorted(images_dir.glob(pat))
            for m in matches:
                if m.is_file():
                    print(f"INFO: Auto-selected cover: {m}")
                    return m

    # None found
    print("INFO: No cover image selected (continuing without a cover).")
    return None


def main() -> None:
    parser = argparse.ArgumentParser(description="Build a volume EPUB from Markdown chapters.")
    parser.add_argument("--volume", required=True, help="Volume directory under content/, e.g. v001_islam_blueprint_for_life")
    parser.add_argument("--cover", help="Path to a PNG/JPG cover image (optional). If missing, will try volume.yml then auto-search images/")
    parser.add_argument("--copy-cover", action="store_true", help="Copy the chosen cover into bookcover/<volume>_cover.<ext> and use that copy")
    args = parser.parse_args()

    repo_root = Path(__file__).resolve().parents[1]
    content_dir = repo_root / "content" / args.volume
    volume_yaml = content_dir / "volume.yml"
    book_dir = repo_root / "book"
    book_dir.mkdir(exist_ok=True)

    if not volume_yaml.exists():
        print(f"ERROR: Missing metadata file: {volume_yaml}", file=sys.stderr)
        sys.exit(1)

    # Load volume metadata
    with volume_yaml.open("r", encoding="utf-8") as fh:
        meta = yaml.safe_load(fh)

    title = meta.get("title", args.volume)
    author = meta.get("author", "Bits2Banking")
    meta_cover = meta.get("cover")
    chapters = meta.get("chapters", [])
    if not chapters:
        print("ERROR: 'chapters' list is empty in volume.yml", file=sys.stderr)
        sys.exit(1)

    # Verify chapters exist and build combined markdown
    chapter_paths: List[Path] = []
    for fname in chapters:
        p = content_dir / fname
        if not p.exists():
            print(f"ERROR: Chapter not found: {p}", file=sys.stderr)
            sys.exit(1)
        chapter_paths.append(p)

    combined_md = book_dir / f"{args.volume}_combined.md"
    with combined_md.open("w", encoding="utf-8") as out:
        # YAML front matter for pandoc
        out.write("---\n")
        out.write(f'title: "{title}"\n')
        out.write(f'author: "{author}"\n')
        out.write("---\n\n")
        # Concatenate chapters in order
        for chap in chapter_paths:
            out.write(f"<!-- BEGIN {chap.name} -->\n\n")
            with chap.open("r", encoding="utf-8") as ch:
                out.write(ch.read().rstrip() + "\n")
            out.write(f"\n<!-- END {chap.name} -->\n\n")

    # Decide on cover image
    cover_path = pick_cover(repo_root, args.volume, args.cover, meta_cover)

    # If requested, copy the cover into bookcover/ for consistent outputs
    if cover_path and args.copy_cover:
        bookcover_dir = repo_root / "bookcover"
        bookcover_dir.mkdir(exist_ok=True)
        ext = cover_path.suffix.lower()
        dest = bookcover_dir / f"{args.volume}_cover{ext}"
        shutil.copyfile(cover_path, dest)
        cover_path = dest
        print(f"INFO: Copied cover to {cover_path}")

    # Build EPUB with Pandoc
    epub_out = book_dir / f"{args.volume}.epub"
    pandoc_cmd = [
        "pandoc",
        str(combined_md),
        "-o", str(epub_out),
        "--toc",
        "--standalone",
    ]
    if cover_path and cover_path.exists():
        pandoc_cmd.extend(["--epub-cover-image", str(cover_path)])

    try:
        run(pandoc_cmd)
        print(f"EPUB created: {epub_out}")
    except subprocess.CalledProcessError as e:
        print("ERROR: Pandoc failed to build the EPUB.", file=sys.stderr)
        sys.exit(e.returncode)


if __name__ == "__main__":
    main()
