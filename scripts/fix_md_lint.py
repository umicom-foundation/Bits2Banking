#!/usr/bin/env python3
"""
fix_md_lint.py

Auto-fixes common markdownlint issues across the repo:

- MD028: no-blanks-blockquote
  Turns a blank line *between two quoted lines* into a quoted blank line,
  preserving quote nesting depth where possible.

- MD009: no-trailing-spaces
  Removes a single trailing space; normalizes 2+ trailing spaces to exactly 2
  (to preserve intentional soft line breaks).

- MD010: no-hard-tabs
  Replaces tab characters with 4 spaces (now **including** inside fences).

- MD036: no-emphasis-as-heading
  If a line consists solely of emphasized text like "*Examples*" or "_Windows (PowerShell)_",
  convert it to a real heading "### Examples" (outside fences).

- MD025: single-title/single-h1
  Keeps the first top-level "# " heading; demotes any later "# " headings to "## ".

- MD026: no-trailing-punctuation in headings
  Strips trailing punctuation (.:;!?), while preserving any anchor like " {#id}".

- MD001: heading-increment
  Prevents jumps (e.g., H2 → H4). If a heading level increases by > 1,
  it’s reduced to previous_level + 1.

Skips: volumes/**, book/**, site/**, .github/ISSUE_TEMPLATE/**, and PULL_REQUEST_TEMPLATE.md

Notes:
- All fixes avoid changing content inside fenced code blocks *except* MD010 (tabs),
  which now also fixes tabs inside fences to satisfy CI.
- Files are read/written as UTF-8 to preserve Arabic text and diacritics.
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

# Fenced code blocks: ``` or ~~~ with 3+ markers
FENCE_RE = re.compile(r"^\s*(`{3,}|~{3,})")
# Blockquote line: one or more '>' possibly with a trailing space
BQ_LINE_RE = re.compile(r"^\s*(>+\s?)")
# Trailing spaces/tabs
TRAIL_SPACES_RE = re.compile(r"[ \t]+$")

# Heading patterns
# Captures: hashes, space, title, optional space, optional trailing hashes
HEAD_RE = re.compile(r"^(\s{0,3}#{1,6})(\s+)(.*?)(\s*)(#+\s*)?$")
# Emphasis-only line: *Text*, **Text**, _Text_, __Text__, etc.
EMPH_AS_HEADING_RE = re.compile(
    r"""^\s*
        (?:
          \*{1,3}([^\*\_].*?)\*{1,3}
          |
          _{1,3}([^_\*].*?)_{1,3}
        )\s*$""",
    re.VERBOSE
)

TAB_REPLACEMENT = " " * 4  # 4 spaces per tab

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
                pref_prev = bq_prefix(prev).strip()
                pref_next = bq_prefix(nxt).strip()
                pref = pref_prev or pref_next or ">"
                # normalize to '>' repeated (strip spaces)
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
    """Replace tabs with spaces **including inside fences** to satisfy MD010."""
    out = []
    changed = False
    for line in lines:
        if "\t" in line:
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
            if not line.lstrip().startswith(("-", "* ", "+", ">", "1.", "2.", "3.", "`")):
                m = EMPH_AS_HEADING_RE.match(line)
                if m:
                    inner = (m.group(1) or m.group(2) or "").strip()
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
            m = HEAD_RE.match(line)
            if m:
                hashes, sp, title, sp2, trailing = m.groups()
                level = len(hashes.strip())
                if level == 1:
                    if not seen_h1:
                        seen_h1 = True
                        out.append(f"{hashes}{sp}{title.strip()}")
                        continue
                    # demote to H2
                    out.append(f"## {title.strip()}")
                    changed = True
                    continue
        out.append(line)
    return out, changed

def strip_heading_trailing_punct(title: str):
    """
    Remove trailing punctuation (.:;!?) before any anchor like {#id}.
    Preserve anchor if present.
    """
    # separate optional anchor
    anchor = ""
    m = re.match(r"^(.*?)(\s*\{[^}]+\})\s*$", title)
    if m:
        core = m.group(1).rstrip()
        anchor = m.group(2)
    else:
        core = title.rstrip()

    new_core = re.sub(r"[ \t]*[.:;!?]+$", "", core)
    changed = (new_core != core)
    return (new_core + (f" {anchor}" if anchor else "")).strip(), changed

def fix_md026_heading_punct(lines):
    """Strip trailing punctuation from headings (outside fences)."""
    out = []
    in_fence = False
    changed = False
    for line in lines:
        if is_fence(line):
            in_fence = not in_fence
            out.append(line)
            continue

        m = HEAD_RE.match(line) if not in_fence else None
        if m:
            hashes, sp, title, sp2, trailing = m.groups()
            new_title, ch = strip_heading_trailing_punct(title)
            if ch:
                out.append(f"{hashes}{sp}{new_title}")
                changed = True
                continue
        out.append(line)
    return out, changed

def fix_md001_heading_increment(lines):
    """
    Prevent heading level jumps: if we go up by >1 (e.g., H2 -> H4),
    demote to last_level + 1. (Outside fences.)
    """
    out = []
    in_fence = False
    changed = False
    last_level = None
    for line in lines:
        if is_fence(line):
            in_fence = not in_fence
            out.append(line)
            continue

        m = HEAD_RE.match(line) if not in_fence else None
        if m:
            hashes, sp, title, sp2, trailing = m.groups()
            level = len(hashes.strip())
            if last_level is None:
                last_level = level
                out.append(f"{hashes}{sp}{title.strip()}")
                continue
            if level > last_level + 1:
                level = last_level + 1
                out.append(f"{'#' * level} {title.strip()}")
                changed = True
                last_level = level
                continue
            last_level = level
        out.append(line)
    return out, changed

def fix_file(p: Path) -> bool:
    # Read strict UTF-8 to preserve Arabic and avoid data loss
    txt = p.read_text(encoding="utf-8")
    lines = txt.splitlines(keepends=False)

    changed_any = False

    # Order matters:
    lines, ch = fix_md028(lines);                      changed_any |= ch
    lines, ch = fix_md009(lines);                      changed_any |= ch
    lines, ch = fix_md010_tabs(lines);                 changed_any |= ch
    lines, ch = fix_md036_emphasis_as_heading(lines);  changed_any |= ch
    lines, ch = fix_md025_single_h1(lines);            changed_any |= ch
    lines, ch = fix_md026_heading_punct(lines);        changed_any |= ch
    lines, ch = fix_md001_heading_increment(lines);    changed_any |= ch

    if changed_any:
        Path(p).write_text("\n".join(lines) + "\n", encoding="utf-8")
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
