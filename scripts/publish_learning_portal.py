#!/usr/bin/env python3
"""Place existing BookForge websites and downloads beside the MkDocs learning site.

The editable books and lessons are never changed. BookForge and MkDocs remain
independent generators; this command composes only their generated outputs.
"""
from __future__ import annotations

import argparse
from html import escape
from pathlib import Path
import shutil
import sys

ROOT = Path(__file__).resolve().parents[1]
FORMATS = frozenset({".pdf", ".docx", ".epub"})


def fail(message: str) -> None:
    raise ValueError(message)


def validate_tree(root: Path) -> None:
    if not root.is_dir() or root.is_symlink():
        fail(f"Not an ordinary directory: {root}")
    for path in root.rglob("*"):
        if path.is_symlink():
            fail(f"Linked input is not included in the publication: {path}")
        if not (path.is_dir() or path.is_file()):
            fail(f"Unsupported input: {path}")
        if any(part in {".", ".."} for part in path.relative_to(root).parts):
            fail(f"Ambiguous input path: {path}")


def publication_paths(repository: Path) -> tuple[Path, Path, Path]:
    return repository / "site", repository / "output" / "site", repository / "output"


def copy_downloads(generated: Path, target: Path) -> int:
    downloads = target / "downloads"
    downloads.mkdir(parents=True, exist_ok=True)
    links = []
    for volume in sorted(generated.iterdir()):
        if volume.name == "site" or not volume.is_dir():
            continue
        if volume.is_symlink() or volume.name.startswith("."):
            fail(f"Unsafe generated book directory: {volume}")
        folder = volume / "books"
        if not folder.exists():
            continue
        validate_tree(folder)
        for source in sorted(folder.iterdir()):
            if not source.is_file() or source.suffix.lower() not in FORMATS:
                continue
            relative = Path(volume.name) / source.name
            destination = downloads / relative
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(source, destination, follow_symlinks=False)
            links.append(f'<li><a href="{escape(relative.as_posix(), quote=True)}">'
                         f'{escape(volume.name)} — {escape(source.name)}</a></li>')
    page = ('<!doctype html><html lang="en-GB"><meta charset="utf-8">'
            '<meta name="viewport" content="width=device-width,initial-scale=1">'
            '<title>Bits to Banking — book downloads</title>'
            '<main><h1>Book downloads</h1><p><a href="../">Book catalogue</a> · '
            '<a href="../../../">Learning website</a></p>'
            '<ul>' + (''.join(links) if links else '<li>No book downloads in this build.</li>') +
            '</ul></main></html>')
    (downloads / "index.html").write_text(page, encoding="utf-8")
    return len(links)


def assemble(repository: Path, refresh: bool = False) -> None:
    website, book_site, generated = publication_paths(repository)
    if not (website / "index.html").is_file():
        fail("MkDocs output missing: build the learning site before composing publication")
    if not (book_site / "index.html").is_file():
        fail("BookForge catalogue missing: build original books with scripts/forge_all.py")
    validate_tree(book_site)
    archive = website / "archive"
    archive.mkdir(parents=True, exist_ok=True)
    destination = archive / "books"
    staged = archive / ".books-staged"
    if staged.exists() or staged.is_symlink():
        fail(f"Previous staged output requires manual inspection: {staged}")
    if destination.exists() and not refresh:
        fail(f"Book archive already exists: {destination}; review it before --refresh")
    if destination.is_symlink():
        fail(f"Refusing to overwrite a linked archive: {destination}")
    try:
        shutil.copytree(book_site, staged, symlinks=True)
        copied = copy_downloads(generated, staged)
        if not (staged / "index.html").is_file() or not (staged / "downloads" / "index.html").is_file():
            fail("The staged archive is incomplete")
        if destination.exists():
            # --refresh applies ONLY to previously generated site/archive/books.
            # Original book sources, BookForge output and MkDocs source are untouched.
            validate_tree(destination)
            shutil.rmtree(destination)
        staged.rename(destination)
        print(f"[OK] Historic book catalogue: {destination / 'index.html'}")
        print(f"[OK] Downloadable books: {copied}")
    except Exception:
        if staged.exists() and not staged.is_symlink():
            shutil.rmtree(staged)
        raise


def verify(repository: Path) -> None:
    website, book_site, _ = publication_paths(repository)
    page = website / "index.html"
    archive = website / "archive" / "books"
    checks = [page, book_site / "index.html", archive / "index.html",
              archive / "downloads" / "index.html"]
    for path in checks:
        if not path.is_file() or path.is_symlink():
            fail(f"Expected publication page missing or linked: {path}")
    validate_tree(archive)
    print("[OK] Learning home, original book catalogue, downloads page and archived files")


def main(arguments: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("assemble", "verify"))
    parser.add_argument("--repo", type=Path, default=ROOT)
    parser.add_argument("--refresh", action="store_true")
    args = parser.parse_args(arguments)
    if args.command == "verify" and args.refresh:
        parser.error("--refresh is not applicable to read-only verification")
    repo = args.repo.resolve()
    try:
        if not (repo / "mkdocs.yml").is_file():
            fail(f"Not a Bits2Banking checkout: {repo}")
        if args.command == "assemble":
            assemble(repo, refresh=args.refresh)
        else:
            verify(repo)
    except (OSError, ValueError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
