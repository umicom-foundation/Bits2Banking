"""Validate the new educational workshops and retained foundational material."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONTENT = ROOT / "content"


def test_original_islam_volume_navigation_remains_accessible():
    nav = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
    assert "Volume 1 — Islam: Blueprint for Life" in nav
    for chapter in ("introduction_to_islam.md", "history_of_money.md",
                    "islamic_finance_and_future.md", "recap.md"):
        assert f"v001_islam_blueprint_for_life/{chapter}" in nav
        assert (CONTENT / "v001_islam_blueprint_for_life" / chapter).is_file()


def test_native_learning_sections_have_source_and_navigation():
    nav = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
    pages = (
        "lessons/03-native-code/35-assembly-and-processor-contracts.md",
        "lessons/03-native-code/36-safer-c-programming.md",
        "lessons/05-engineering/37-cmake-and-build-systems.md",
        "lessons/05-engineering/38-package-managers-and-c-libraries.md",
        "lessons/05-engineering/39-build-a-c-web-server.md",
        "lessons/06-umicom/40-boot-umicom-kernel.md",
        "lessons/05-engineering/41-other-compiled-languages.md",
        "lessons/05-engineering/42-http-and-assembly.md",
        "umicom/native-education-tools.md",
        "roadmap.md",
    )
    for page in pages:
        assert page in nav
        assert (CONTENT / page).is_file()
    assert (ROOT / "ROADMAP_MAJOR_UPDATES.md").is_file()


def test_native_examples_are_source_only_and_bounded():
    notes = ROOT / "labs/native/safe-notes"
    scanner = ROOT / "labs/native/http-header-scanner"
    for p in (notes, scanner):
        assert (p / "CMakeLists.txt").is_file()
        assert not list(p.rglob("*.exe"))
        assert not list(p.rglob("*.o"))
        assert not list(p.rglob("*.obj"))
    assert "count - 1U" in (scanner / "scanner.c").read_text()
    assert (scanner / "scan_x86_64.S").is_file()
    assert (scanner / "scan_riscv64.S").is_file()
    assert "BITS_HTTP_ENABLE_ASSEMBLY" in (scanner / "CMakeLists.txt").read_text()


def test_native_video_scripts_are_navigable():
    nav = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
    for number in ("05-build-a-web-server-in-c", "06-from-assembly-to-umicom-kernel",
                   "07-http-scanner-assembly"):
        path = f"videos/scripts/{number}.md"
        assert path in nav
        assert (CONTENT / path).is_file()
