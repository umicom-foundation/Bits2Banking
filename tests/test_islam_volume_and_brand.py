"""Verify historic authored content and canonical Framework branding are published."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONTENT = ROOT / "content"
VOLUME = CONTENT / "v001_islam_blueprint_for_life"


def test_original_chapters_present():
    from sys import path as sys_path
    sys_path.insert(0, str(ROOT / "tools"))
    from prepare_learning_site import CHAPTERS
    for name in CHAPTERS:
        published = VOLUME / name
        original = ROOT / "dropzone" / "documents" / "islam_blueprint_for_life" / name
        assert published.is_file() and original.is_file(), name
        assert published.read_text(encoding="utf-8-sig").strip(), name


def test_book_illustrations_present():
    images = CONTENT / "assets" / "books" / "islam"
    assert (images / "islam_bookcover.png").is_file()
    assert (images / "Diagram_Tech_in_Banking.png").is_file()
    assert (images / "Diagram_Umicom_ABS_Coin.png").is_file()


def test_website_brand_uses_framework_artwork():
    brand = CONTENT / "assets" / "branding"
    icon = brand / "umicom.ico"
    assert icon.is_file()
    assert icon.read_bytes()[:4] == b"\x00\x00\x01\x00"
    assert (brand / "umicom-icon-on-dark.svg").is_file()
    assert (brand / "umicom-logo.png").is_file()


def test_restored_navigation():
    conf = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
    assert 'Volume 1 — Islam: Blueprint for Life' in conf
    assert 'v001_islam_blueprint_for_life/introduction_to_islam.md' in conf
    assert 'assets/branding/umicom.ico' in conf
    assert 'assets/stylesheets/umicom.css' in conf
