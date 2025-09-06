#!/usr/bin/env python3
"""
Fix common markdownlint issues:
- MD028: blank line inside blockquote  (> line ... [blank] ... > line)
- MD009: trailing spaces at end of lines

It walks the repo, skipping volumes/, book/, site/, and .github/ISSUE_TEMPLATE/,
and skips .github/PULL_REQUEST_TEMPLATE.md (same as your CI).
"""

from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]

EXCLUDE_DIRS = {
    str(ROOT / "volumes"),
    str(ROOT / "book"),
    str(ROOT / "site"),
    str(ROOT / ".github" / "ISSUE_TEMPLATE"),
}

SKIP_FILES = {
    str(ROOT / ".github" / "PULL_REQUEST_TEMPLATE.md"),
}

MD_GLOB = "**/*.md"

# Regex to turn a blank line BETWEEN two blockquote lines into a blockquote
# Example: "> a\n\n> b" ==> "> a\n>\n> b"
RE_MD028 = re.compile(r"(?m)^(>.*)\n[ \t]*\n(?=>)", re.UNICODE)

# Regex to strip trailing spaces/tabs (MD009)
RE_TRAILING = re.compile(r"[ \t]+$", re.MULTILINE)


def should_skip(p: Path) -> bool:
    sp = str(p)
    if sp in SKIP_FILES:
        return True
    for ex in EXCLUDE_DIRS:
        if sp.startswith(ex + "/") or sp.startswith(ex + "\\"):
            return True
    return False


def fix_file(p: Path) -> int:
    """
    Returns number of changes performed in file p.
    """
    try:
        text = p.read_text(encoding="utf-8", errors="strict")
    except Exception as e:
        print(f"!! Could not read {p}: {e}", file=sys.stderr)
        return 0

    orig = text

    # MD028: repeatedly apply until no more changes
    while True:
        new_text = RE_MD028.sub(r"\1\n>", text)
        if new_text == text:
            break
        text = new_text

    # MD009: strip trailing spaces/tabs
    text = RE_TRAILING.sub("", text)

    if text != orig:
        try:
            # Write back as UTF-8, preserve LF newlines
            p.write_text(text, encoding="utf-8", errors="strict", newline="\n")
        except Exception as e:
            print(f"!! Could not write {p}: {e}", file=sys.stderr)
            return 0
        return 1
    return 0


def main():
    changed = 0
    scanned = 0
    for p in ROOT.glob(MD_GLOB):
        if not p.is_file():
            continue
        if should_skip(p):
            continue
        scanned += 1
        changed += fix_file(p)

    print(f"Scanned {scanned} Markdown file(s); fixed {changed} file(s).")
    if changed == 0:
        print("No changes needed or already clean.")


if __name__ == "__main__":
    main()

