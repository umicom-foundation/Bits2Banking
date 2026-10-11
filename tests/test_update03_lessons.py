"""Check the reader-facing navigation added with the native renderer repair."""
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
CONTENT = ROOT / "content"
NAVIGATION = ROOT / "mkdocs.yml"


class LearningUpdate03(unittest.TestCase):
    def test_new_lessons_are_available_from_navigation(self):
        navigation = NAVIGATION.read_text(encoding="utf-8")
        for name in (
            "46-diagnose-a-failing-build-tool.md",
            "47-test-child-processes-with-ctest.md",
            "48-validate-a-book-before-publishing.md",
        ):
            lesson = CONTENT / "lessons" / "05-engineering" / name
            self.assertTrue(lesson.is_file(), name)
            self.assertIn(f"lessons/05-engineering/{name}", navigation)
            self.assertIn("## 1.", lesson.read_text(encoding="utf-8"))

    def test_video_has_related_lesson_and_navigation(self):
        navigation = NAVIGATION.read_text(encoding="utf-8")
        video = CONTENT / "videos/scripts/10-find-and-fix-a-build-boundary.md"
        self.assertTrue(video.is_file())
        self.assertIn("scripts/10-find-and-fix-a-build-boundary.md", navigation)
        text = video.read_text(encoding="utf-8")
        self.assertIn("**Narration**", text)
        self.assertIn("**On screen", text)
        self.assertIn("46-diagnose-a-failing-build-tool.md", text)

    def test_original_islam_chapter_navigation_is_retained(self):
        navigation = NAVIGATION.read_text(encoding="utf-8")
        names = (
            "introduction_to_islam.md", "history_of_money.md",
            "decline_of_sound_money.md", "modern_banking_and_finance.md",
            "technology_and_banking.md", "islamic_finance_and_future.md",
            "umicom_abs_coin.md", "governance_firewalls.md",
            "hall_of_shame_collaboration_and_betrayal.md", "recap.md",
        )
        for name in names:
            self.assertIn(f"v001_islam_blueprint_for_life/{name}", navigation)


if __name__ == "__main__":
    unittest.main()
