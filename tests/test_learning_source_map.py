"""-----------------------------------------------------------------------------
Umicom Bits2Banking
File: tests/test_learning_source_map.py

PURPOSE:
    Guard lesson identity, course order and code preservation across source media.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
---------------------------------------------------------------------------"""

from html.parser import HTMLParser
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class CodeExamples(HTMLParser):
    """Decode HTML entities while retaining the complete text inside pre blocks."""

    def __init__(self):
        super().__init__(convert_charrefs=True)
        self.examples = []
        self.current = None

    def handle_starttag(self, tag, attrs):
        if tag == "pre":
            self.current = []

    def handle_data(self, text):
        if self.current is not None:
            self.current.append(text)

    def handle_endtag(self, tag):
        if tag == "pre" and self.current is not None:
            self.examples.append("".join(self.current).strip("\n"))
            self.current = None


class LearningSourceMapTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.media = json.loads((ROOT / "knowledge/registries/lesson-media.json").read_text(encoding="utf-8"))
        cls.curriculum = json.loads((ROOT / "knowledge/registries/curriculum.json").read_text(encoding="utf-8"))

    def source(self, relative):
        candidate = (ROOT / relative).resolve()
        self.assertTrue(candidate.is_relative_to(ROOT), relative)
        self.assertTrue(candidate.is_file(), relative)
        return candidate

    def test_every_pair_resolves_and_shared_manuscripts_have_explicit_aliases(self):
        entries = self.media["lessons"]
        by_html = {entry["html"]: entry for entry in entries}
        self.assertEqual(len(by_html), len(entries), "A browser address must have one identity")
        manuscripts = {}
        for entry in entries:
            with self.subTest(html=entry["html"]):
                self.source(entry["html"])
                self.source(entry["markdown"])
                manuscripts.setdefault(entry["markdown"], []).append(entry)
                if "aliasOf" in entry:
                    canonical = by_html[entry["aliasOf"]]
                    self.assertNotIn("aliasOf", canonical, "Aliases must resolve directly")
                    self.assertEqual(entry["markdown"], canonical["markdown"])
        for manuscript, group in manuscripts.items():
            with self.subTest(manuscript=manuscript):
                self.assertEqual(sum("aliasOf" not in entry for entry in group), 1)

    def test_converted_examples_preserve_c_includes_and_other_code(self):
        for entry in self.media["lessons"]:
            if entry["relationship"] != "converted-from-html":
                continue
            with self.subTest(html=entry["html"]):
                parser = CodeExamples()
                parser.feed(self.source(entry["html"]).read_text(encoding="utf-8-sig"))
                markdown = self.source(entry["markdown"]).read_text(encoding="utf-8-sig")
                for example in parser.examples:
                    if example:
                        self.assertIn(example, markdown, "Review both source formats when changing an example")

    def test_curriculum_has_one_subject_for_every_registered_course(self):
        courses = [course for subject in self.curriculum["subjects"] for course in subject["courses"]]
        ids = [course["id"] for course in courses]
        self.assertEqual(len(ids), len(set(ids)))
        self.assertEqual(set(ids), {entry["course"] for entry in self.media["lessons"]})
        for course in courses:
            self.source(course["source"].split("#", 1)[0])
        stages = self.curriculum["stages"]
        self.assertEqual([stage["order"] for stage in stages], list(range(1, len(stages) + 1)))
        for stage in stages:
            self.source(stage["source"].split("#", 1)[0])
            self.assertTrue(stage["readiness"].strip())

    def test_introductory_course_modules_preserve_one_reading_order(self):
        pairs = {entry["html"]: entry["markdown"] for entry in self.media["lessons"]}
        for course in ("learning-c", "umicom-development"):
            with self.subTest(course=course):
                directory = ROOT / "content/courses" / course
                metadata = json.loads((directory / "course.json").read_text(encoding="utf-8"))
                lesson_paths = [lesson["path"] for lesson in metadata["lessons"]]
                module_paths = [item for module in metadata["modules"] for item in module["lessons"]]
                self.assertEqual(lesson_paths, module_paths)
                self.assertEqual(len(module_paths), len(set(module_paths)))
                for lesson in metadata["lessons"]:
                    html = (directory / lesson["path"]).relative_to(ROOT).as_posix()
                    manuscript = (directory / lesson["manuscript"]).resolve()
                    self.assertEqual(manuscript, self.source(pairs[html]))


if __name__ == "__main__":
    unittest.main()
