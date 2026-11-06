# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/test_course_source_links.py
#
# PURPOSE:
#   Verify manuscript links survive local reading and website publication.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
import importlib.util
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('course_source_links', ROOT / 'hooks/course_source_links.py')
LINKS = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(LINKS)


class CoursePublicationLinks(unittest.TestCase):
    def setUp(self):
        self.folder = TemporaryDirectory()
        self.addCleanup(self.folder.cleanup)
        self.root = Path(self.folder.name)
        self.docs = self.root / 'content'
        self.site = self.root / 'site'
        self.source = self.docs / 'courses/learning-c/index.html'
        self.output = self.site / 'courses/learning-c/index.html'
        self.manuscript = self.docs / 'lessons/learning-c/index.md'
        self.page = self.site / 'lessons/learning-c/index.html'
        for p in (self.source, self.output, self.manuscript, self.page):
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text('content', encoding='utf-8')
        self.documents = {self.manuscript.resolve(): self.page}

    def rewrite(self, text):
        return LINKS.CourseLinks(text, self.source, self.output, self.documents).result()

    def test_known_manuscript_and_escaped_query(self):
        text = '<a class="read" href="../../lessons/learning-c/index.md?x=1&amp;y=2#exercise">Read</a>'
        self.assertEqual(self.rewrite(text), text.replace('index.md?', 'index.html?'))

    def test_source_examples_comments_and_external_links_remain(self):
        text = '''<!-- <a href="../../lessons/learning-c/index.md"> -->
<pre>&lt;a href="../../lessons/learning-c/index.md"&gt;</pre>
<script>const example = '<a href="../../lessons/learning-c/index.md">';</script>
<a href="https://example.com/index.md">External</a>
<a href="//example.com/index.md">External</a>
<a href="missing.md">Unresolved</a><a href="#exercise">Anchor</a>'''
        self.assertEqual(self.rewrite(text), text)

    def test_flat_destination_and_encoded_filename(self):
        source = self.docs / 'lessons/learning-c/two words.md'
        target = self.site / 'lessons/learning-c/two words.html'
        self.documents[source.resolve()] = target
        text = "<A data-href='leave.md' HREF='../../lessons/learning-c/two%20words.md'>Read</A>"
        self.assertEqual(self.rewrite(text), text.replace('two%20words.md', 'two%20words.html'))

    def test_href_text_inside_another_attribute_is_not_a_link(self):
        title = "title=\"Example href='../../lessons/learning-c/index.md'\""
        text = '<a ' + title + ' href="../../lessons/learning-c/index.md">Read</a>'
        expected = '<a ' + title + ' href="../../lessons/learning-c/index.html">Read</a>'
        self.assertEqual(self.rewrite(text), expected)

    def test_unquoted_href_is_preserved_as_unquoted(self):
        text = '<a href=../../lessons/learning-c/index.md>Read</a>'
        self.assertEqual(self.rewrite(text), text.replace('index.md', 'index.html'))

    def test_build_changes_output_only_and_is_repeatable(self):
        text = '<a href="../../lessons/learning-c/index.md">Read</a>'
        self.source.write_text(text, encoding='utf-8')
        self.output.write_text(text, encoding='utf-8')
        entries = [SimpleNamespace(src_uri='courses/learning-c/index.html',
            abs_src_path=str(self.source), abs_dest_path=str(self.output),
            is_documentation_page=lambda: False),
            SimpleNamespace(src_uri='lessons/learning-c/index.md',
            abs_src_path=str(self.manuscript), abs_dest_path=str(self.page),
            is_documentation_page=lambda: True)]
        config = {'site_dir': str(self.site), 'docs_dir': str(self.docs)}
        LINKS.on_files(entries, config)
        LINKS.on_post_build(config)
        once = self.output.read_bytes()
        LINKS.on_post_build(config)
        self.assertEqual(once, self.output.read_bytes())
        self.assertIn('index.html', self.output.read_text())
        self.assertEqual(text, self.source.read_text())

    def test_missing_generated_document_is_not_invented(self):
        self.page.unlink()
        text = '<a href="../../lessons/learning-c/index.md">Read</a>'
        self.output.write_text(text, encoding='utf-8')
        entry = SimpleNamespace(src_uri='lessons/learning-c/index.md',
            abs_src_path=str(self.manuscript), abs_dest_path=str(self.page),
            is_documentation_page=lambda: True)
        course = SimpleNamespace(src_uri='courses/learning-c/index.html',
            abs_src_path=str(self.source), abs_dest_path=str(self.output),
            is_documentation_page=lambda: False)
        LINKS.on_files([entry, course], {})
        LINKS.on_post_build({'site_dir': str(self.site), 'docs_dir': str(self.docs)})
        self.assertEqual(text, self.output.read_text())

    def test_source_output_overlap_is_rejected(self):
        with self.assertRaises(ValueError):
            LINKS.on_post_build({'site_dir': str(self.docs), 'docs_dir': str(self.docs)})


if __name__ == '__main__':
    unittest.main()
