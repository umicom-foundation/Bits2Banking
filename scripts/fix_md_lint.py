#!/usr/bin/env python3
"""
fix_md_lint.py

Auto-fixes common markdownlint issues across the repo:

- MD028: no-blanks-blockquote
- MD009: no-trailing-spaces
- MD010: no-hard-tabs (tabs -> 4 spaces, even inside code fences)
- MD036: no-emphasis-as-heading  (*Text* -> ### Text)
- MD025: single H1 (handles both ATX '# ' and Setext '===='/'----')
- MD026: no-trailing-punctuation in headings
- MD001: heading-increment (avoid H2 -> H4 jumps)

Skips: volumes/**, book/**, site/**, .github/ISSUE_TEMPLATE/**, and PULL_REQUEST_TEMPLATE.md

UTF-8 in/out to preserve Arabic/diacritics.
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

FENCE_RE = re.compile(r"^\s*(`{3,}|~{3,})")
BQ_LINE_RE = re.compile(r"^\s*(>+\s?)")
TRAIL_SPACES_RE = re.compile(r"[ \t]+$")
HEAD_RE = re.compile(r"^(\s{0,3}#{1,6})(\s+)(.*?)(\s*)(#+\s*)?$")
EMPH_AS_HEADING_RE = re.compile(
    r"""^\s*(?:\*{1,3}([^\*\_].*?)\*{1,3}|_{1,3}([^_\*].*?)_{1,3})\s*$""",
    re.VERBOSE
)

TAB_REPLACEMENT = " " * 4

def is_fence(line: str) -> bool:
    return FENCE_RE.match(line) is not None

def is_blockquote(line: str) -> bool:
    return BQ_LINE_RE.match(line) is not None

def bq_prefix(line: str) -> str:
    m = BQ_LINE_RE.match(line)
    return m.group(1) if m else ""

def fix_md028(lines):
    out, in_fence, changed = [], False, False
    for i, line in enumerate(lines):
        if is_fence(line):
            in_fence = not in_fence
            out.append(line); continue
        if not in_fence and line.strip() == "":
            prev = out[-1] if out else ""
            nxt  = lines[i+1] if i+1 < len(lines) else ""
            if is_blockquote(prev) and is_blockquote(nxt):
                pref_prev = bq_prefix(prev).strip()
                pref_next = bq_prefix(nxt).strip()
                pref = pref_prev or pref_next or ">"
                pref = ">" * max(1, pref.count(">"))
                out.append(pref); changed = True; continue
        out.append(line)
    return out, changed

def fix_md009(lines):
    out, in_fence, changed = [], False, False
    for line in lines:
        if is_fence(line):
            in_fence = not in_fence
            out.append(line); continue
        m = TRAIL_SPACES_RE.search(line)
        if not in_fence and m:
            trail = m.group(0)
            line = line[:m.start()] + ("  " if len(trail) >= 2 else "")
            changed = True
        out.append(line)
    return out, changed

def fix_md010_tabs(lines):
    out, changed = [], False
    for line in lines:
        if "\t" in line:
            out.append(line.replace("\t", TAB_REPLACEMENT)); changed = True
        else:
            out.append(line)
    return out, changed

def fix_md036_emphasis_as_heading(lines):
    out, in_fence, changed = [], False, False
    for line in lines:
        if is_fence(line):
            in_fence = not in_fence
            out.append(line); continue
        if not in_fence:
            m = EMPH_AS_HEADING_RE.match(line)
            if m:
                inner = (m.group(1) or m.group(2) or "").strip()
                if inner:
                    out.append(f"### {inner}"); changed = True; continue
        out.append(line)
    return out, changed

def strip_heading_trailing_punct(title: str):
    anchor = ""
    m = re.match(r"^(.*?)(\s*\{[^}]+\})\s*$", title)
    if m:
        core, anchor = m.group(1).rstrip(), m.group(2)
    else:
        core = title.rstrip()
    new_core = re.sub(r"[ \t]*[.:;!?]+$", "", core)
    return (new_core + (f" {anchor}" if anchor else "")).strip(), (new_core != core)

def fix_md026_heading_punct(lines):
    out, in_fence, changed = [], False, False
    for line in lines:
        if is_fence(line):
            in_fence = not in_fence
            out.append(line); continue
        m = HEAD_RE.match(line) if not in_fence else None
        if m:
            hashes, sp, title, sp2, trailing = m.groups()
            new_title, ch = strip_heading_trailing_punct(title)
            if ch:
                out.append(f"{hashes}{sp}{new_title}"); changed = True; continue
        out.append(line)
    return out, changed

def fix_md025_single_h1(lines):
    """
    Ensure only first H1 remains H1.
    - Converts Setext H1/H2 (====/----) to ATX (#/##).
    - Demotes additional H1s (ATX or Setext) to H2.
    """
    out, in_fence, changed, seen_h1 = [], False, False, False
    i = 0
    while i < len(lines):
        line = lines[i]

        if is_fence(line):
            in_fence = not in_fence
            out.append(line); i += 1; continue

        if not in_fence:
            # ATX headings
            m = HEAD_RE.match(line)
            if m:
                hashes, sp, title, _, _ = m.groups()
                level = len(hashes.strip())
                title = title.strip()
                if level == 1:
                    if seen_h1:
                        out.append(f"## {title}"); changed = True
                    else:
                        out.append(f"# {title}"); seen_h1 = True
                else:
                    out.append(f"{'#'*level} {title}")
                i += 1
                continue

            # Setext detection: current line text + next line all '=' or '-'
            if i + 1 < len(lines):
                title_line = line.rstrip()
                underline = lines[i+1].strip()
                if title_line and re.fullmatch(r"=+", underline):  # Setext H1
                    if seen_h1:
                        out.append(f"## {title_line.strip()}")  # demote to H2
                    else:
                        out.append(f"# {title_line.strip()}"); seen_h1 = True
                    changed = True
                    i += 2
                    continue
                if title_line and re.fullmatch(r"-+", underline):  # Setext H2
                    out.append(f"## {title_line.strip()}"); changed = True
                    i += 2
                    continue

        # default
        out.append(line); i += 1

    return out, changed

def fix_md001_heading_increment(lines):
    out, in_fence, changed = [], False, False
    last_level = None
    for line in lines:
        if is_fence(line):
            in_fence = not in_fence
            out.append(line); continue
        m = HEAD_RE.match(line) if not in_fence else None
        if m:
            hashes, sp, title, _, _ = m.groups()
            level = len(hashes.strip())
            title = title.strip()
            if last_level is None:
                last_level = level
                out.append(f"{'#'*level} {title}")
            else:
                if level > last_level + 1:
                    level = last_level + 1
                    changed = True
                out.append(f"{'#'*level} {title}")
                last_level = level
            continue
        out.append(line)
    return out, changed

def fix_file(p: Path) -> bool:
    txt = p.read_text(encoding="utf-8")
    lines = txt.splitlines(keepends=False)
    changed_any = False

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
            print(f"Fixed: {p.relative_to(ROOT)}"); touched += 1
    print(f"Done. Files modified: {touched}")
    return 0

if __name__ == "__main__":
    sys.exit(main())
