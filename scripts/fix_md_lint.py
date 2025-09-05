#!/usr/bin/env python3
"""
fix_md_lint.py

Auto-fixes common markdownlint issues across the repo:

- MD028: no-blanks-blockquote
  Turns a blank line *between two quoted lines* into a quoted blank line,
  preserving the quote nesting depth where possible.

- MD009: no-trailing-spaces
  Removes a single trailing space; normalizes 2+ trailing spaces to exactly 2
  (to preserve intentional soft line breaks).

- MD010: no-hard-tabs
  Replaces tab characters with 4 spaces (outside code fences by default).

- MD036: no-emphasis-as-heading
  If a line consists solely of emphasized text like "*Examples*" or "_Windows (PowerShell)_",
  convert it to a real heading "### Examples" (outside code fences).

- MD025: single-title/single-h1
  Keeps the first top-level "# " heading; demotes any later "# " headings to "## ".

Skips: volumes/**, book/**, site/**, .github/ISSUE_TEMPLATE/**, and PULL_REQUEST_TEMPLATE.md
Avoids touching lines inside fenced code blocks for MD028/MD036/MD025 and MD009.
MD010 (tabs) is applied outside fences; change APPLY_TABS_IN_FENCES to True if you want everywhere.

Run:
  python3 scripts/fix_md_lint.py   (Linux/macOS)
  py scripts\\fix_md_lint.py       (Windows)
"""

from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]

# --- Configuration ---
APPLY_TABS_IN_FENCES = False     # Set True to replace tabs even inside fenced code blocks
TAB_REPLACEMENT = " " * 4        # 4 spaces per tab

def should_skip(p: Path) -> bool:
    rel = p.relative_to(ROOT).as_posix()
    if rel.startswith("volumes/"): return True
    if rel.startswith("book/"): return True
    if rel.startswith("site/"): return True
    if rel.startswith(".github/ISSUE_TEMPLATE/"): return True
    if p.name == "PULL_REQUEST_TEMPLATE.md": return True
    return False

# Fenced code blocks: ``` or ~~~ with 3+ markers
FENCE_RE = re.compile(r"^\s*(`{3,}|~{3,})")
# Blockquote line: one or more '>' possibly with a trailing space
BQ_LINE_RE = re.compile(r"^\s*(>+\s?)")
# Trailing spaces/tabs
TRAIL_SPACES_RE = re.compile(r"[ \t]+$")

# Heading patterns
H1_RE = re.compile(r"^(#)\s+(.*?)(\s#+\s*)?$")  # "# Title" (ignore trailing hashes)
# Emphasis-only line: *Text*, **Text**, _Text_, __Text__ (standalone line)
EMPH_AS_HEADING_RE = re.compile(
    r"""^\s*                # leading space
        (?:
          \*{1,3}([^\*\_].*?)\*{1,3}   # *text* or **text** or ***text***
          |
          _{1,3}([^_\*].*?)_{1,3}       # _text_ or __text__ or ___text___
        )\s*$""",
    re.VERBOSE
)

def is_fence(line: str) -> bool:
    return FENCE_RE.match(line) is not None

def is_blockquote(line: str) -> bool:
    return BQ_LINE_RE.match(line) is not None

def bq_prefix(line: str) -> str:
    m = BQ_LINE_RE.match(line)
    return m.group(1) if m else ""

def fix_md028(lines):
    """Fix blank lines *inside* blockquotes by inserting a quoted blank line."""
    out = []
    in_fence = False
    changed = False
    for i, line in enumerate(lines):
        if is_fence(line):
            in_fence = not in_fence
            out.append(line)
            continue

        if not in_fence and line.strip() == "":
            prev = out[-1] if out else ""
            nxt  = lines[i+1] if i+1 < len(lines) else ""
            if is_blockquote(prev) and is_blockquote(nxt):
                # choose a prefix (prefer previous); fallback to next; else single '>'
                pref_prev = bq_prefix(prev).strip()
                pref_next = bq_prefix(nxt).strip()
                pref = pref_prev or pref_next or ">"
                # Normalize to just '>' repeated (strip spaces), e.g., ">>"
                pref = ">" * pref.count(">")
                if not pref:
                    pref = ">"
                out.append(pref)
                changed = True
                continue

        out.append(line)
    return out, changed

def fix_md009(lines):
    """Normalize trailing spaces."""
    out = []
    in_fence = False
    changed = False
    for line in lines:
        if is_fence(line):
            in_fence = not in_fence
            out.append(line)
            continue
        m = TRAIL_SPACES_RE.search(line)
        if not in_fence and m:
            trail = m.group(0)
            if len(trail) == 1:
                line = line[:m.start()]
                changed = True
            elif len(trail) >= 2:
                line = line[:m.start()] + "  "
                changed = True
        out.append(line)
    return out, changed

def fix_md010_tabs(lines):
    """Replace tabs with spaces (optionally skip fenced blocks)."""
    out = []
    in_fence = False
    changed = False
    for line in lines:
        if is_fence(line):
            in_fence = not in_fence
            out.append(line)
            continue
        if ("\t" in line) and (APPLY_TABS_IN_FENCES or not in_fence):
            out.append(line.replace("\t", TAB_REPLACEMENT))
            changed = True
        else:
            out.append(line)
    return out, changed

def fix_md036_emphasis_as_heading(lines):
    """Convert lines that are only emphasis into '### Heading'."""
    out = []
    in_fence = False
    changed = False
    for line in lines:
        if is_fence(line):
            in_fence = not in_fence
            out.append(line)
            continue

        if not in_fence:
            # Avoid list markers or quotes acting as headings
            if not line.lstrip().startswith(("-", "* ", "+", ">", "1.", "2.", "3.", "`")):
                m = EMPH_AS_HEADING_RE.match(line)
                if m:
                    inner = m.group(1) or m.group(2) or ""
                    inner = inner.strip()
                    if inner:
                        out.append(f"### {inner}")
                        changed = True
                        continue
        out.append(line)
    return out, changed

def fix_md025_single_h1(lines):
    """Demote any additional '# ' headings to '## ' after the first one."""
    out = []
    in_fence = False
    changed = False
    seen_h1 = False
    for line in lines:
        if is_fence(line):
            in_fence = not in_fence
            out.append(line)
            continue

        if not in_fence:
            m = H1_RE.match(line)
            if m:
                if not seen_h1:
                    seen_h1 = True
                    out.append(line)  # keep the first H1
                    continue
                # Demote subsequent H1 to H2
                title = m.group(2).strip()
                out.append(f"## {title}")
                changed = True
                continue
        out.append(line)
    return out, changed

def fix_file(p: Path) -> bool:
    # Read strict UTF-8 to preserve Arabic and avoid silent data loss
    txt = p.read_text(encoding="utf-8")
    lines = txt.splitlines(keepends=False)

    changed_any = False

    # Order matters a bit; do blockquote and tabs/spacing before headings
    lines, ch = fix_md028(lines);               changed_any |= ch
    lines, ch = fix_md009(lines);               changed_any |= ch
    lines, ch = fix_md010_tabs(lines);          changed_any |= ch
    lines, ch = fix_md036_emphasis_as_heading(lines); changed_any |= ch
    lines, ch = fix_md025_single_h1(lines);     changed_any |= ch

    if changed_any:
        p.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return changed_any

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
