"""Structural checks for the published educational content."""
import importlib.util
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SCRIPT = ROOT / 'tools' / 'validate_learning.py'


def load_validator():
    spec = importlib.util.spec_from_file_location('validate_learning', SCRIPT)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def test_lesson_links_and_navigation():
    assert load_validator().collect_errors() == []


def test_all_lesson_numbers_exist():
    numbers = sorted(int(p.stem[:2]) for p in (ROOT / 'content' / 'lessons').glob('*/[0-9][0-9]-*.md'))
    assert numbers == list(range(1, 35))


def test_no_precompiled_java_in_labs():
    assert not list((ROOT / 'content' / 'labs').rglob('*.class'))


def test_source_file_ownership():
    assert (ROOT / 'content' / 'labs' / 'python-notes' / 'test_notes.py').is_file()
    assert (ROOT / 'content' / 'videos' / 'scripts' / '01-what-is-a-computer.md').is_file()
