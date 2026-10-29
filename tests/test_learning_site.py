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


# Retain the old assertion for review: it mixed unrelated course numbers.
if False:
    def test_all_lesson_numbers_exist():
        numbers = sorted(int(p.stem[:2]) for p in (ROOT / 'content' / 'lessons').glob('*/[0-9][0-9]-*.md'))
        assert len(numbers) >= 34
        assert numbers == list(range(1, len(numbers) + 1))

def test_all_lesson_numbers_exist():
    validator = load_validator()
    # Course-local numbering is independent of the foundational sequence.
    assert validator.lesson_number_errors(validator.numbered_lessons()) == []


def foundational_paths(count=34):
    return [Path(f'01-computers/{number:02d}-chapter.md')
            for number in range(1, count + 1)]


def test_independent_courses_can_restart_numbering():
    paths = foundational_paths() + [
        Path('learning-c/01-program.md'), Path('learning-python/01-program.md')]
    assert load_validator().lesson_number_errors(paths) == []


def test_three_digit_foundational_chapters_keep_their_full_number():
    assert load_validator().lesson_number_errors(foundational_paths(105)) == []


def test_missing_foundational_chapter_is_reported():
    paths = foundational_paths(35)
    paths.pop(10)
    assert any('expected 11, found 12' in error
               for error in load_validator().lesson_number_errors(paths))


def test_duplicate_number_within_one_course_is_reported():
    paths = foundational_paths() + [
        Path('learning-c/01-first.md'), Path('learning-c/001-duplicate.md')]
    assert any('learning-c: invalid or duplicate lesson 1' in error
               for error in load_validator().lesson_number_errors(paths))


def test_large_ordinal_does_not_allocate_a_dense_number_range():
    paths = foundational_paths() + [Path('01-computers/999999999999-last.md')]
    assert any('expected 35' in error
               for error in load_validator().lesson_number_errors(paths))


def test_numbered_discovery_includes_three_digits_and_excludes_indexes(tmp_path):
    folder = tmp_path / 'lessons' / '05-engineering'
    folder.mkdir(parents=True)
    for name in ('099-links.md', '100-compiler.md', 'index.md', 'appendix.md'):
        (folder / name).write_text('# Lesson\n', encoding='utf-8')
    assert [page.name for page in load_validator().numbered_lessons(tmp_path)] == [
        '099-links.md', '100-compiler.md']


def test_no_precompiled_java_in_labs():
    assert not list((ROOT / 'content' / 'labs').rglob('*.class'))


def test_source_file_ownership():
    assert (ROOT / 'content' / 'labs' / 'python-notes' / 'test_notes.py').is_file()
    assert (ROOT / 'content' / 'videos' / 'scripts' / '01-what-is-a-computer.md').is_file()
