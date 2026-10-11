"""Regression coverage for real malformed YAML, original chapters, and nav paths."""
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
SCRIPT = ROOT / 'tools' / 'check_mkdocs_config.py'
CONFIG = ROOT / 'mkdocs.yml'


def run(config: Path, *args: str) -> subprocess.CompletedProcess[str]:
    return subprocess.run([sys.executable, str(SCRIPT), '--config', str(config), *args],
                          capture_output=True, text=True, timeout=15, check=False)


def test_complete_restored_navigation_is_valid_yaml():
    result = run(CONFIG, '--syntax-only')
    assert result.returncode == 0, result.stderr


def test_corrupted_sibling_indentation_reports_line_numbers(tmp_path: Path):
    # This deliberately recreates the style of reported error near lines 65-78.
    text = CONFIG.read_text(encoding='utf-8')
    bad = text.replace('  - "Computer fundamentals":', '    - "Computer fundamentals":', 1)
    assert bad != text
    config = tmp_path / 'mkdocs.yml'
    config.write_text(bad, encoding='utf-8')
    result = run(config, '--syntax-only')
    assert result.returncode == 2
    assert 'Line ' in result.stderr
    assert 'Computer fundamentals' in result.stderr


def test_missing_selected_page_refuses_success(tmp_path: Path):
    config = tmp_path / 'mkdocs.yml'
    config.write_text(CONFIG.read_text(encoding='utf-8'), encoding='utf-8')
    (tmp_path / 'content').mkdir()
    result = run(config)
    assert result.returncode == 3
    assert 'missing page' in result.stderr.lower()


def test_duplicate_nav_entry_refuses_success(tmp_path: Path):
    text = CONFIG.read_text(encoding='utf-8')
    duplicate = '  - Again: index.md\n'
    config = tmp_path / 'mkdocs.yml'
    config.write_text(text.replace('nav:\n', 'nav:\n' + duplicate, 1), encoding='utf-8')
    (tmp_path / 'content').mkdir()
    result = run(config)
    assert result.returncode == 3
    assert 'more than once' in result.stderr


def test_ten_legacy_islam_chapters_are_preserved():
    import yaml
    doc = yaml.safe_load(CONFIG.read_text(encoding='utf-8'))
    section = [entry['Volume 1 — Islam: Blueprint for Life'] for entry in doc['nav']
               if isinstance(entry, dict) and 'Volume 1 — Islam: Blueprint for Life' in entry]
    assert len(section) == 1
    paths = [next(iter(page.values())) for page in section[0]]
    from importlib.util import spec_from_file_location, module_from_spec
    spec = spec_from_file_location('mkdocs_check07', SCRIPT)
    module = module_from_spec(spec)
    assert spec is not None and spec.loader is not None
    spec.loader.exec_module(module)
    original = [path.rsplit('/', 1)[-1] for path in paths
                if path.rsplit('/', 1)[-1] in module.ORIGINAL_ISLAM_CHAPTERS]
    assert tuple(original) == module.ORIGINAL_ISLAM_CHAPTERS


def test_lesson_07_pages_appear_once_in_navigation():
    cfg = CONFIG.read_text(encoding='utf-8')
    for p in (
        'lessons/05-engineering/63-repair-a-mkdocs-configuration.md',
        'lessons/03-native-code/64-test-allocation-failures.md',
        'lessons/03-native-code/65-parse-bounded-http-bytes.md',
        'lessons/05-engineering/66-fuzz-bytes-and-check-contracts.md',
    ):
        assert cfg.count(p) == 1
        assert (ROOT / 'content' / p).is_file()
