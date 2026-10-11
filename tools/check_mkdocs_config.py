#!/usr/bin/env python3
"""Validate the human-authored Bits2Banking MkDocs navigation.

MkDocs remains the renderer. This tool performs an early, non-mutating check
of YAML syntax, navigation ownership and the source pages selected for build.
It does not build a site, rewrite a file or attempt to install dependencies.
"""
from __future__ import annotations

import argparse
from pathlib import Path
import sys

ORIGINAL_ISLAM_CHAPTERS = (
    'introduction_to_islam.md',
    'history_of_money.md',
    'decline_of_sound_money.md',
    'modern_banking_and_finance.md',
    'technology_and_banking.md',
    'islamic_finance_and_future.md',
    'umicom_abs_coin.md',
    'governance_firewalls.md',
    'hall_of_shame_collaboration_and_betrayal.md',
    'recap.md',
)


def _issue(message: str) -> None:
    print(f'[FAIL] {message}', file=sys.stderr)


def _yaml_error(path: Path, original_text: str, failure: Exception) -> int:
    _issue(f'YAML parsing failed in {path}')
    mark = getattr(failure, 'problem_mark', None)
    if mark is None:
        print(f'  {failure}', file=sys.stderr)
        return 2
    line_number = mark.line + 1
    print(f'  Line {line_number}, column {mark.column + 1}: '
          f'{getattr(failure, "problem", "invalid YAML")}', file=sys.stderr)
    lines = original_text.splitlines()
    for index in range(max(0, mark.line - 4), min(len(lines), mark.line + 4)):
        indicator = '>>' if index == mark.line else '  '
        print(f'{indicator} {index + 1:4} | {lines[index]}', file=sys.stderr)
    print('  Check the indentation of neighbouring nav: list items. '
          'Siblings must use the same number of leading spaces; do not use tabs.',
          file=sys.stderr)
    return 2


def _pages(nav: object) -> tuple[list[tuple[str, str]], list[str]]:
    """Return (display title, page path) while checking MkDocs nav shapes."""
    found: list[tuple[str, str]] = []
    problems: list[str] = []

    def visit(node: object, trail: str) -> None:
        if not isinstance(node, list):
            problems.append(f'{trail} must be a YAML list')
            return
        for entry in node:
            if not isinstance(entry, dict) or len(entry) != 1:
                problems.append(f'{trail} has an item that is not one labelled page or group')
                continue
            label, value = next(iter(entry.items()))
            if not isinstance(label, str) or not label.strip():
                problems.append(f'{trail} has an empty or non-text navigation label')
                continue
            if isinstance(value, list):
                visit(value, f'{trail} / {label}')
            elif isinstance(value, str) and value.strip():
                found.append((label, value))
            else:
                problems.append(f'{trail} / {label} must be a file path or nested list')

    visit(nav, 'nav')
    return found, problems


def check(configuration: Path, syntax_only: bool = False) -> int:
    try:
        raw = configuration.read_text(encoding='utf-8-sig')
    except OSError as exc:
        _issue(f'Cannot read {configuration}: {exc}')
        return 2
    if '\t' in raw:
        _issue(f'{configuration} contains a tab. Use spaces for YAML indentation.')
        return 2
    try:
        import yaml
    except ImportError:
        _issue('PyYAML is missing from the active Python environment. '
               'Install the existing requirements-docs.txt into the website .venv.')
        return 2
    # YAML normally accepts repeated mapping keys and silently keeps the last
    # value. Refuse that behaviour so a merge cannot hide previous chapters.
    class NoDuplicateKeysLoader(yaml.SafeLoader):
        pass

    def UniqueMapping(loader: object, node: object) -> dict:
        mapping = {}
        for key_node, value_node in node.value:
            key = loader.construct_object(key_node, deep=True)
            if key in mapping:
                raise yaml.constructor.ConstructorError(
                    'YAML navigation', node.start_mark,
                    f'duplicate mapping key {key!r}', key_node.start_mark)
            mapping[key] = loader.construct_object(value_node, deep=True)
        return mapping

    NoDuplicateKeysLoader.add_constructor(
        yaml.resolver.BaseResolver.DEFAULT_MAPPING_TAG, UniqueMapping)
    try:
        document = yaml.load(raw, Loader=NoDuplicateKeysLoader)
    except yaml.YAMLError as exc:
        return _yaml_error(configuration, raw, exc)
    if not isinstance(document, dict):
        _issue('MkDocs configuration must be a YAML mapping.')
        return 3
    if syntax_only:
        print(f'[OK] YAML syntax: {configuration}')
        return 0

    root = configuration.parent.resolve()
    if document.get('docs_dir') != 'content' or document.get('site_dir') != 'site':
        _issue('This project expects docs_dir: content and site_dir: site.')
        return 3
    contents = root / 'content'
    pages, errors = _pages(document.get('nav'))
    selected: set[str] = set()
    missing: list[str] = []
    original_order: list[str] = []
    prefix = 'v001_islam_blueprint_for_life/'
    for label, value in pages:
        if value.startswith(('https://', 'http://')):
            continue
        path = value.split('#', 1)[0]
        if not path.endswith('.md'):
            errors.append(f'{label}: only Markdown pages are expected in this nav: {value}')
            continue
        normalised = (contents / path).resolve()
        if not normalised.is_relative_to(contents.resolve()):
            errors.append(f'{label}: navigation path escapes content/: {path}')
            continue
        if path in selected:
            errors.append(f'{label}: page is in the navigation more than once: {path}')
        selected.add(path)
        if not normalised.is_file():
            missing.append(path)
        if path.startswith(prefix) and path.removeprefix(prefix) in ORIGINAL_ISLAM_CHAPTERS:
            original_order.append(path.removeprefix(prefix))
    if tuple(original_order) != ORIGINAL_ISLAM_CHAPTERS:
        errors.append('The original ten Islam: Blueprint for Life chapters are '
                      'missing, duplicated or no longer in their original order.')
    if errors or missing:
        for error in errors[:25]:
            _issue(error)
        for path in missing[:25]:
            _issue(f'Navigation points to a missing page: content/{path}')
        if len(errors) > 25 or len(missing) > 25:
            _issue('Additional issues were omitted; correct the first errors and retry.')
        if missing:
            print('  Ensure earlier batches are merged, then run the existing '
                  'site preparation tool to copy original books and branding:',
                  file=sys.stderr)
            print('    python tools/prepare_learning_site.py', file=sys.stderr)
        return 3
    print(f'[OK] MkDocs configuration: {len(pages)} navigation pages; '
          f'{len(original_order)} original Islam chapters in order.')
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description='Check MkDocs YAML and educational pages without modifying them.')
    parser.add_argument('--config', type=Path, default=Path(__file__).resolve().parents[1] / 'mkdocs.yml')
    parser.add_argument('--syntax-only', action='store_true', help='Check YAML syntax without requiring prepared book pages.')
    options = parser.parse_args(argv)
    return check(options.config.resolve(), options.syntax_only)


if __name__ == '__main__':
    sys.exit(main())
