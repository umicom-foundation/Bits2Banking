"""Regression checks for the course navigation and original-book links.

These tests read source files only. They do not install third-party packages,
launch the website server or alter the original source manuscripts.
"""
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class NativeBookCourseDocumentation(unittest.TestCase):
    def test_original_islam_volume_still_in_navigation(self):
        navigation = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
        self.assertIn("Volume 1 — Islam: Blueprint for Life", navigation)
        originals = (
            "introduction_to_islam.md",
            "history_of_money.md",
            "decline_of_sound_money.md",
            "modern_banking_and_finance.md",
            "technology_and_banking.md",
            "islamic_finance_and_future.md",
            "umicom_abs_coin.md",
            "governance_firewalls.md",
            "hall_of_shame_collaboration_and_betrayal.md",
            "recap.md",
        )
        for chapter in originals:
            self.assertIn(f"v001_islam_blueprint_for_life/{chapter}", navigation)

    def test_course_pages_are_available_and_linked(self):
        navigation = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
        for name in (
            "43-prepare-a-website-build-environment.md",
            "44-native-book-manuscripts.md",
            "45-run-external-build-tools-safely.md",
        ):
            self.assertTrue((ROOT / "content/lessons/05-engineering" / name).is_file())
            self.assertIn(name, navigation)
        for name in (
            "08-building-and-previewing-the-website.md",
            "09-assembling-a-markdown-book-in-c.md",
        ):
            self.assertTrue((ROOT / "content/videos/scripts" / name).is_file())
            self.assertIn(name, navigation)

    def test_umicom_branding_remains_configured(self):
        navigation = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
        self.assertIn("assets/branding/umicom-icon-on-dark.svg", navigation)
        self.assertIn("assets/branding/umicom.ico", navigation)
        self.assertIn("assets/stylesheets/umicom.css", navigation)


if __name__ == "__main__":
    unittest.main()
