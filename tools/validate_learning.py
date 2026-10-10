"""Check learning chapter links, diagram references and course navigation."""
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
CONTENT = ROOT / 'content'
LINK_RE = re.compile(r'(?<!!)\[[^\]]+\]\(([^)]+)\)|!\[[^\]]*\]\(([^)]+)\)')


def collect_errors():
    errors = []
    chapters = sorted((CONTENT / 'lessons').glob('*/[0-9][0-9]-*.md'))
    diagrams = sorted((CONTENT / 'assets' / 'diagrams').glob('*.svg'))
    if len(chapters) != 34:
        errors.append(f'Expected 34 numbered lessons; found {len(chapters)}')
    if len(diagrams) != 17:
        errors.append(f'Expected 17 diagrams; found {len(diagrams)}')
    if list(CONTENT.rglob('*.class')):
        errors.append('Compiled Java class files should not be committed as lesson source')
    for page in CONTENT.rglob('*.md'):
        source = page.read_text(encoding='utf-8')
        if not re.search(r'^#\s+\S+', source, flags=re.MULTILINE):
            errors.append(f'{page.relative_to(ROOT)} lacks a top-level title')
        # Strip code fences, as code examples can contain strings resembling links.
        text = re.sub(r'(?ms)^```.*?^```[ \t]*$', '', source)
        for match in LINK_RE.finditer(text):
            link = (match.group(1) or match.group(2)).split('#', 1)[0].strip()
            if not link or link.startswith(('https://', 'http://', 'mailto:', '#', 'data:')):
                continue
            local = (page.parent / link).resolve()
            try:
                local.relative_to(CONTENT.resolve())
            except ValueError:
                errors.append(f'{page.relative_to(ROOT)}: link leaves content root: {link}')
                continue
            if not local.exists():
                errors.append(f'{page.relative_to(ROOT)}: missing link target: {link}')
    config = (ROOT / 'mkdocs.yml').read_text(encoding='utf-8')
    # The fixed structure writes a nav mapping where leaf file paths are .md.
    for nav_target in re.findall(r':\s+([\w./-]+\.md)\s*$', config, re.MULTILINE):
        if not (CONTENT / nav_target).is_file():
            errors.append(f'mkdocs.yml: nav target missing: {nav_target}')
    return errors


def main():
    errors = collect_errors()
    if errors:
        for err in errors:
            print('ERROR:', err)
        return 1
    print('Learning content validated: 34 lessons, 17 diagrams, local links and MkDocs navigation.')
    return 0


if __name__ == '__main__':
    sys.exit(main())
