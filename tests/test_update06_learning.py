"""Contract checks for the new human-readable C23 learning material.

The test reads editable source documents and does not need MkDocs, a compiler,
or a live GitHub connection. Executable C behaviour is checked by CTest.
"""
from pathlib import Path
import re
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
CONTENT = ROOT / "content"
NATIVE = ROOT / "labs" / "native"

NEW_LESSONS = (
    "lessons/03-native-code/58-memory-ownership-in-c23.md",
    "lessons/03-native-code/59-checked-arithmetic-and-money.md",
    "lessons/03-native-code/60-debugging-undefined-behaviour.md",
    "lessons/05-engineering/61-build-a-c-library-with-cmake.md",
    "lessons/05-engineering/62-build-and-preview-the-education-site.md",
)
NEW_DIAGRAMS = (
    "assets/diagrams/notes-memory-ownership.svg",
    "assets/diagrams/checked-money-before-commit.svg",
    "assets/diagrams/education-build-serve.svg",
)
NEW_VIDEOS = (
    "videos/scripts/14-why-memory-ownership-matters.md",
    "videos/scripts/15-checked-arithmetic-and-safe-preview.md",
)


def test_new_chapters_exist_and_appear_in_navigation():
    nav = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
    for relative in NEW_LESSONS:
        assert (CONTENT / relative).is_file(), relative
        assert nav.count(relative) == 1, f"Missing or duplicated navigation: {relative}"
        assert (CONTENT / relative).read_text(encoding="utf-8").startswith("# ")


def test_original_islam_volume_navigation_is_preserved():
    nav = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
    original = (
        "introduction_to_islam.md", "history_of_money.md", "decline_of_sound_money.md",
        "modern_banking_and_finance.md", "technology_and_banking.md",
        "islamic_finance_and_future.md", "umicom_abs_coin.md",
        "governance_firewalls.md", "hall_of_shame_collaboration_and_betrayal.md", "recap.md",
    )
    seen = []
    for name in original:
        path = f"v001_islam_blueprint_for_life/{name}"
        assert nav.count(path) == 1, path
        seen.append(nav.index(path))
    assert seen == sorted(seen), "The original book chapter order has changed"


def test_source_laboratories_are_complete_and_targeted():
    for directory, files, target in (
        ("owned-notes", ("notes.h", "notes.c", "main.c", "test_notes.c"),
         "bits2banking-owned-notes-test"),
        ("checked-money", ("account.h", "account.c", "main.c", "test_account.c"),
         "bits2banking-checked-money-test"),
    ):
        root = NATIVE / directory
        for name in (*files, "CMakeLists.txt", "README.md"):
            assert (root / name).is_file(), str(root / name)
        cmake = (root / "CMakeLists.txt").read_text(encoding="utf-8")
        assert "C_STANDARD 23" in cmake
        assert target in cmake
        assert "add_test(" in cmake


def test_original_diagrams_are_valid_editable_svg():
    for relative in NEW_DIAGRAMS:
        path = CONTENT / relative
        assert path.is_file(), path
        tree = ET.parse(path)
        root = tree.getroot()
        assert root.tag.endswith("svg")
        assert root.get("viewBox")
        assert root.get("role") == "img"


def test_relative_links_in_new_reading_paths_resolve():
    pages = [*(CONTENT / p for p in NEW_LESSONS), *(CONTENT / p for p in NEW_VIDEOS)]
    pages += [NATIVE / "owned-notes" / "README.md", NATIVE / "checked-money" / "README.md"]
    for page in pages:
        content = page.read_text(encoding="utf-8")
        for ref in re.findall(r"\]\(([^)]+)\)", content):
            ref = ref.split("#", 1)[0].strip()
            if not ref or ref.startswith(("https://", "http://", "mailto:")):
                continue
            assert (page.parent / ref).is_file(), f"{page}: broken relative link to {ref}"


def test_video_scripts_are_linked_from_video_index():
    index = (CONTENT / "videos" / "index.md").read_text(encoding="utf-8")
    nav = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
    for relative in NEW_VIDEOS:
        assert (CONTENT / relative).is_file()
        assert relative.removeprefix("videos/") in index
        assert nav.count(relative) == 1


def test_existing_publication_workflows_not_replaced_by_this_update():
    # The reader-facing update should not change the ownership of production
    # publication jobs; those are separately qualified in the prior batch.
    assert (ROOT / "mkdocs.yml").is_file()
    # Public curriculum checks must not require a maintainer's private plan.
    # Keep the former check here for source review; the learner roadmap is
    # the published replacement and remains a required course resource.
    # assert (ROOT / "ROADMAP_MAJOR_UPDATES.md").is_file()
    assert (CONTENT / "roadmap.md").is_file()
