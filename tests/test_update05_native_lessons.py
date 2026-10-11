"""Bits to Banking: check the new native-systems lessons without network access.

These checks verify the source navigation and file layout, not compiled C code;
CMake/CTest performs the executable checks separately.
"""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
CONTENT = ROOT / "content"
NEW_LESSONS = [
    "lessons/03-native-code/53-call-assembly-from-c.md",
    "lessons/01-computers/54-from-first-instruction-to-kernel.md",
    "lessons/03-native-code/55-write-a-safe-binary-record-in-c.md",
    "lessons/05-engineering/56-test-windows-process-paths.md",
    "lessons/05-engineering/57-examine-object-files-and-linkers.md",
]
VIDEOS = [
    "videos/scripts/12-calling-c-from-assembly.md",
    "videos/scripts/13-binary-records-and-safer-c.md",
]


class LearningUpdate05(unittest.TestCase):
    def test_new_chapters_are_available_in_mkdocs(self):
        configuration = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
        for path in NEW_LESSONS + VIDEOS:
            with self.subTest(path=path):
                self.assertTrue((CONTENT / path).is_file())
                self.assertIn(path, configuration)

    def test_preserve_original_islam_chapter_navigation(self):
        configuration = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
        original = [
            "introduction_to_islam", "history_of_money", "decline_of_sound_money",
            "modern_banking_and_finance", "technology_and_banking",
            "islamic_finance_and_future", "umicom_abs_coin", "governance_firewalls",
            "hall_of_shame_collaboration_and_betrayal", "recap",
        ]
        for name in original:
            with self.subTest(name=name):
                self.assertIn("v001_islam_blueprint_for_life/" + name + ".md", configuration)

    def test_diagram_and_local_links_exist(self):
        pattern = re.compile(r'!?\[[^\]]*\]\(([^)#]+)(?:#[^)]*)?\)')
        for name in NEW_LESSONS + VIDEOS:
            page = CONTENT / name
            body = page.read_text(encoding="utf-8")
            self.assertIn("# ", body)
            for link in pattern.findall(body):
                if "://" in link or link.startswith("mailto:"):
                    continue  # External references are checked separately in publication QA.
                destination = (page.parent / link).resolve()
                with self.subTest(page=name, link=link):
                    self.assertTrue(destination.is_file(), str(destination))

    def test_indexes_link_to_new_chapters(self):
        path_map = {
            "lessons/01-computers/index.md": ["54-from-first-instruction-to-kernel.md"],
            "lessons/03-native-code/index.md": [
                "53-call-assembly-from-c.md", "55-write-a-safe-binary-record-in-c.md"],
            "lessons/05-engineering/index.md": [
                "56-test-windows-process-paths.md", "57-examine-object-files-and-linkers.md"],
            "videos/index.md": [
                "12-calling-c-from-assembly.md", "13-binary-records-and-safer-c.md"],
        }
        for location, entries in path_map.items():
            text = (CONTENT / location).read_text(encoding="utf-8")
            for entry in entries:
                with self.subTest(location=location, entry=entry):
                    self.assertIn(entry, text)

    def test_lab_sources_and_cmake_are_present(self):
        for lab, files in {
            "assembly-functions": [
                "CMakeLists.txt", "main.c", "add_x86_64.S", "add_riscv64.S", "README.md"],
            "binary-payment-records": [
                "CMakeLists.txt", "record.h", "record.c", "main.c", "test_record.c", "README.md"],
        }.items():
            for file in files:
                with self.subTest(lab=lab, file=file):
                    self.assertTrue((ROOT / "labs/native" / lab / file).is_file())

    def test_course_diagrams_have_accessibility_text(self):
        for name in [
            "assembly-call-registers.svg", "payment-wire-format.svg",
            "windows-process-boundary.svg",
        ]:
            p = CONTENT / "assets/diagrams" / name
            svg = p.read_text(encoding="utf-8")
            self.assertIn("<title", svg)
            self.assertIn("<desc", svg)
            self.assertIn('role="img"', svg)


if __name__ == "__main__":
    unittest.main()
