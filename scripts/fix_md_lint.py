#!/usr/bin/env python3
"""
fix_md_lint.py

Repairs two markdownlint issues across the repo:
- MD028: no-blanks-blockquote  -> converts a blank line between two quoted lines into a '>' line
- MD009: no-trailing-spaces    -> removes trailing spaces (keeps exactly 2 if already 2+)

Skips: volumes/**, book/**, site/**, .github/ISSUE_TEMPLATE/** and PULL_REQUEST_TEMPLATE.md
Avoids touching lines inside fenced code blocks (``` or ~~~).
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

fence_re = re.compile(r"^\s*(```|~~~)")
blockquote_re = re.compile(r"^\s*>")
trail_spaces_re = re.compile(r"[ \t]+$")

def fix_file(p: Path) -> bool:
    text = p.read_text(encoding="utf-8", errors="ignore")
    lines = text.splitlines(keepends=False)

    changed = False
    in_fence = False

    # First pass: fix MD028 (blank lines between two blockquote lines)
    out = []
    for i, line in enumerate(lines):
        # Toggle code fence state on lines that begin with ``` or ~~~
        if fence_re.match(line):
            in_fence = not in_fence
            out.append(line)
            continue

        if not in_fence and line.strip() == "":
            prev = out[-1] if out else ""
            nxt = lines[i+1] if i+1 < len(lines) else ""
            if blockquote_re.match(prev or "") and blockquote_re.match(nxt or ""):
                # Turn blank line into a quoted blank line to satisfy MD028
                out.append(">")
                changed = True
                continue

        out.append(line)

    lines = out
    out = []
    in_fence = False

    # Second pass: fix MD009 (trailing spaces)
    for line in lines:
        if fence_re.match(line):
            in_fence = not in_fence
            out.append(line)
            continue

        if not in_fence:
            m = trail_spaces_re.search(line)
            if m:
                # count trailing spaces/tabs
                trail = m.group(0)
                if len(trail) == 1:
                    # drop single trailing space
                    line = line[:m.start()]
                    changed = True
                elif len(trail) >= 2:
                    # normalize 2+ trailing spaces to exactly 2 (or, if you prefer, strip all)
                    line = line[:m.start()] + "  "
                    changed = True

        out.append(line)

    if changed:
        p.write_text("\n".join(out) + "\n", encoding="utf-8")
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

