"""Check learning chapter links, diagram references and course navigation."""
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
CONTENT = ROOT / 'content'
LINK_RE = re.compile(r'(?<!!)\[[^\]]+\]\(([^)]+)\)|!\[[^\]]*\]\(([^)]+)\)')


def numbered_lessons(content=CONTENT):
    """Read the complete ordinal; independent courses may restart at lesson one."""
    return sorted(page for page in (content / 'lessons').glob('*/*.md')
                  if re.match(r'^[0-9]+-', page.name))


def lesson_number_errors(chapters):
    """The seven foundational sections share one sequence; other courses own theirs."""
    groups = {}
    for page in chapters:
        number = int(re.match(r'^([0-9]+)-', page.name).group(1))
        section = page.parent.name
        namespace = 'foundation' if re.match(r'^0[1-7]-', section) else section
        groups.setdefault(namespace, {}).setdefault(number, []).append(page)
    errors = []
    for namespace, numbers in sorted(groups.items()):
        for number, pages in sorted(numbers.items()):
            if number < 1 or len(pages) != 1:
                errors.append(f'{namespace}: invalid or duplicate lesson {number}: '
                              + ', '.join(str(page) for page in pages))
    foundation = groups.get('foundation', {})
    if len(foundation) < 34:
        errors.append(f'Expected at least 34 foundational lessons; found {len(foundation)}')
    # Compare sorted neighbours instead of allocating an array up to a pathname's
    # number. A malformed, extremely large ordinal must not exhaust the checker.
    for expected, actual in enumerate(sorted(foundation), start=1):
        if actual != expected:
            errors.append(f'Foundational lesson sequence: expected {expected}, found {actual}')
            break
    return errors


def collect_errors():
    errors = []
    # Retained for review: the former global two-digit sequence mixed
    # independent courses and omitted lesson 100 onward. Scoped ordinals below
    # preserve duplicate and missing-chapter detection without that assumption.
    if False:
        chapters = sorted((CONTENT / 'lessons').glob('*/[0-9][0-9]-*.md'))
        diagrams = sorted((CONTENT / 'assets' / 'diagrams').glob('*.svg'))
        if len(chapters) < 34:
            errors.append(f'Expected at least 34 numbered lessons; found {len(chapters)}')
        numbers = sorted(int(page.stem[:2]) for page in chapters)
        if numbers and numbers != list(range(1, len(numbers) + 1)):
            errors.append('Lesson numbers must be unique and continuous from 1')
    chapters = numbered_lessons()
    diagrams = sorted((CONTENT / "assets" / "diagrams").glob("*.svg"))
    errors.extend(lesson_number_errors(chapters))
    if len(diagrams) < 17:
        errors.append(f'Expected at least 17 diagrams; found {len(diagrams)}')
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
    print('Learning content validated: numbered lessons, 17 diagrams, local links and MkDocs navigation.')
    return 0


if __name__ == '__main__':
    sys.exit(main())
