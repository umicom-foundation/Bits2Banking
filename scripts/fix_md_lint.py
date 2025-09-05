#!/usr/bin/env python3
"""
fix_md_lint.py

Repairs two markdownlint issues across the repo:

- MD028: no-blanks-blockquote
  Converts a blank line that sits *inside* a blockquote into a quoted blank line,
  preserving the same '>' nesting prefix (e.g., '>' or '>> ').

- MD009: no-trailing-spaces
  Removes trailing spaces if exactly 1; normalizes 2+ trailing spaces to exactly 2
  (to keep intentional soft line breaks).

Skips: volumes/**, book/**, site/**, .github/ISSUE_TEMPLATE/**, and PULL_REQUEST_TEMPLATE.md
Avoids touching lines inside fenced code blocks (``` or ~~~, any length >= 3).
"""

from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]

def should_skip(p: Path) -> bool:
    rel = p.relative_to(ROOT).as_posix()
    if rel.startswith("volumes/"): return True
    if rel.startswith("book/"): return True
    if rel.startswith("site/"): return True
    if rel.startswith(".github/ISSUE_TEMPLATE/"): return True
    if p.name == "PULL_REQUEST_TEMPLATE.md": return True
    return False

# Fence: start/end of fenced code blocks (```... or ~~~...), any length >=3
fence_re = re.compile(r"^\s*(`{3,}|~{3,})")
# A line that begins with one or more '>' (with optional spaces after) is a blockquote
blockquote_line_re = re.compile(r"^\s*(>+\s?)")
# Any trailing spaces/tabs
trail_spaces_re = re.compile(r"[ \t]+$")

def is_blockquote(line: str) -> bool:
    return blockquote_line_re.match(line) is not None

def quote_prefix(line: str) -> str:
    """
    Return the exact leading quote prefix ('>', '>>', '   > ' etc.) from a blockquote line.
    If not a blockquote, returns empty string.
    """
    m = blockquote_line_re.match(line)
    return m.group(1) if m else ""

def fix_file(p: Path) -> bool:
    # Read as strict UTF-8 (no 'ignore') to avoid silently losing non-ascii content
    text = p.read_text(encoding="utf-8")
    lines = text.splitlines(keepends=False)

    changed = False
    in_fence = False

    # --- Pass 1: MD028 (blank lines inside blockquotes)
    out = []
    for i, line in enumerate(lines):
        # Toggle fence state when a fence line is seen
        if fence_re.match(line):
            in_fence = not in_fence
            out.append(line)
            continue

        if not in_fence and line.strip() == "":
            prev = out[-1] if out else ""
            nxt  = lines[i+1] if i+1 < len(lines) else ""
            if is_blockquote(prev) and is_blockquote(nxt):
                # Insert a quoted blank line with *the same prefix depth* as prev
                pref = quote_prefix(prev)
                # Normalize to just the quote markers and a single space (if any space was there)
                # e.g., "> " or ">> "
                pref = pref.rstrip() + (" " if pref.strip() else "")
                out.append(pref.rstrip("> ").replace(" ", "") + ("" if pref.strip() == ">" else pref))
                # The above line ensures at least '>' and preserves multiple '>' if present.
                # Simpler (and usually sufficient) alternative:
                # out.append(pref.strip() if pref.strip() else ">")
                # But we’ll use a cleaner approach below instead:
                out.pop()  # remove the experimental append
                pref_clean = quote_prefix(prev)
                if not pref_clean:
                    pref_clean = ">"
                # If prev was '>> ' then we want '>>' (with optional space); both are valid.
                out.append(pref_clean.strip())
                changed = True
                continue

        out.append(line)

    lines = out
    out = []
    in_fence = False

    # --- Pass 2: MD009 (trailing spaces)
    for line in lines:
        if fence_re.match(line):
            in_fence = not in_fence
            out.append(line)
            continue

        if not in_fence:
            m = trail_spaces_re.search(line)
            if m:
                trail = m.group(0)
                if len(trail) == 1:
                    # remove single trailing space
                    line = line[:m.start()]
                    changed = True
                elif len(trail) >= 2:
                    # normalize to exactly two spaces (intentional soft break)
                    line = line[:m.start()] + "  "
                    changed = True

        out.append(line)

    if changed:
        # Write back with a single trailing newline, UTF-8
        Path(p).write_text("\n".join(out) + "\n", encoding="utf-8")
    return changed

def main() -> int:
    md_files = [p for p in ROOT.rglob("*.md") if not should_skip(p)]
    touched = 0
    for p in md_files:
        if fix_file(p):
            print(f"Fixed: {p.relative_to(ROOT)}")
            touched += 1
    print(f"Done. Files modified: {touched}")
    return 0

if __name__ == "__main__":
    sys.exit(main())
