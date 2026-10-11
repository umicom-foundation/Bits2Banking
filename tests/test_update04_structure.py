"""Review the added publications and preserve the original book navigation."""
from pathlib import Path
import unittest
import yaml

ROOT = Path(__file__).resolve().parents[1]


class PublishingStructureTest(unittest.TestCase):
    def test_all_new_chapters_and_video_are_in_nav(self):
        text = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
        paths = [
            "lessons/01-computers/49-how-memory-access-reaches-the-cpu.md",
            "lessons/05-engineering/50-publish-learning-and-books-together.md",
            "lessons/05-engineering/51-verify-publication-in-c23.md",
            "lessons/05-engineering/52-one-github-pages-deployment.md",
            "videos/scripts/11-publish-and-verify-the-learning-site.md",
        ]
        for relative in paths:
            with self.subTest(relative=relative):
                self.assertIn(relative, text)
                self.assertTrue((ROOT / "content" / relative).is_file())

    def test_historic_volume_navigation_retained(self):
        text = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
        for chapter in (
            "introduction_to_islam", "history_of_money", "decline_of_sound_money",
            "modern_banking_and_finance", "technology_and_banking",
            "islamic_finance_and_future", "umicom_abs_coin",
            "governance_firewalls", "hall_of_shame_collaboration_and_betrayal", "recap",
        ):
            self.assertIn(f"v001_islam_blueprint_for_life/{chapter}.md", text)

    def test_only_unified_workflow_deploys(self):
        folder = ROOT / ".github/workflows"
        for name in ("books-build.yml", "dropzone-build.yml"):
            workflow = yaml.load((folder / name).read_text(), Loader=yaml.BaseLoader)
            self.assertEqual(workflow["jobs"]["deploy"]["if"], "false")
            self.assertIn("build", workflow["jobs"])
        publisher = yaml.load((folder / "learning-pages.yml").read_text(), Loader=yaml.BaseLoader)
        self.assertIn("deploy", publisher["jobs"])
        self.assertNotEqual(publisher["jobs"]["deploy"]["if"], "false")
        self.assertIn("pull_request", publisher["on"])


if __name__ == "__main__":
    unittest.main()
