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
import json
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import unittest
from unittest.mock import patch

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

    def test_post_build_shares_source_resolution_only_during_one_build(self):
        # Adjacent sources share the source target even when their output
        # pages have different navigation depth.
        second_source = self.source.with_name('detail.html')
        second_output = self.output.parent / 'detail/index.html'
        second_output.parent.mkdir()
        text = '<a href="../../lessons/learning-c/index.md?x=5#check">Read</a>'
        self.source.write_text(text, encoding='utf-8')
        second_source.write_text(text, encoding='utf-8')
        entries = [
            SimpleNamespace(src_uri='courses/learning-c/index.html',
                abs_src_path=str(self.source), abs_dest_path=str(self.output),
                is_documentation_page=lambda: False),
            SimpleNamespace(src_uri='courses/learning-c/detail.html',
                abs_src_path=str(second_source), abs_dest_path=str(second_output),
                is_documentation_page=lambda: False),
            SimpleNamespace(src_uri='lessons/learning-c/index.md',
                abs_src_path=str(self.manuscript), abs_dest_path=str(self.page),
                is_documentation_page=lambda: True),
        ]
        config = {'site_dir': str(self.site), 'docs_dir': str(self.docs)}
        LINKS.on_files(entries, config)
        with patch.object(LINKS, 'publication_reference_target',
                          wraps=LINKS.publication_reference_target) as resolve:
            for builds in (1, 2):
                self.output.write_text(text, encoding='utf-8')
                second_output.write_text(text, encoding='utf-8')
                LINKS.on_post_build(config)
                self.assertEqual(builds, resolve.call_count)
                self.assertEqual(text.replace('index.md?', 'index.html?'),
                                 self.output.read_text(encoding='utf-8'))
                self.assertEqual(text.replace('index.md?', 'index.html?').replace(
                    '../../lessons', '../../../lessons'), second_output.read_text(encoding='utf-8'))
        self.assertEqual(text, second_source.read_text(encoding='utf-8'))


    def test_repository_source_uses_public_url_with_encoded_name(self):
        target = self.root / 'labs/native/two words.c'
        target.parent.mkdir(parents=True)
        target.write_text('source', encoding='utf-8')
        context = LINKS.repository_context(
            {'repo_url': 'https://github.com/umicom-foundation/Bits2Banking.git'}, self.docs)
        original = '<a href="../../../labs/native/two%20words.c?x=1&amp;y=2#L3">Read</a>'
        result = LINKS.CourseLinks(original, self.source, self.output,
                                   self.documents, context).result()
        self.assertEqual(result, '<a href="https://github.com/umicom-foundation/'
            'Bits2Banking/blob/main/labs/native/two%20words.c?x=1&amp;y=2#L3">Read</a>')

    def test_pack_guide_and_manifest_have_public_routes(self):
        folder = self.root / 'learning-packs'
        folder.mkdir()
        for name in ('index.html', 'course.json'):
            (folder / name).write_text('resource', encoding='utf-8')
        context = LINKS.repository_context(
            {'repo_url': 'https://github.com/umicom-foundation/Bits2Banking/'}, self.docs)
        original = '<a href="../../../learning-packs/index.html">Guide</a>' + (
            '<a href="../../../learning-packs/course.json">Manifest</a>')
        result = LINKS.CourseLinks(original, self.source, self.output,
                                   self.documents, context).result()
        self.assertIn('/blob/main/learning-packs/index.html', result)
        self.assertIn('/blob/main/learning-packs/course.json', result)
        self.assertNotIn('href="../', result)

    def test_unknown_missing_and_hidden_files_are_not_exposed(self):
        for name in ('_local/private.md', 'notes/plan.md', 'labs/.hidden/code.c'):
            target = self.root / name
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text('private', encoding='utf-8')
        context = LINKS.repository_context(
            {'repo_url': 'https://github.com/umicom-foundation/Bits2Banking'}, self.docs)
        original = ''.join('<a href="../../../' + name + '">Read</a>' for name in
            ('_local/private.md', 'notes/plan.md', 'labs/.hidden/code.c', 'labs/missing.c'))
        self.assertEqual(original, LINKS.CourseLinks(original, self.source,
            self.output, self.documents, context).result())

    def test_local_source_routes_remain_without_publication_context(self):
        target = self.root / 'labs/native/main.c'
        target.parent.mkdir(parents=True)
        target.write_text('source', encoding='utf-8')
        original = '<a href="../../../labs/native/main.c">Local source</a>'
        self.assertEqual(original, self.rewrite(original))

    def test_repository_identity_is_not_guessed(self):
        for value in ('http://github.com/owner/repo',
                      'https://example.com/owner/repo',
                      'https://github.com/owner/repo?token=value',
                      'https://github.com/owner/repo#branch',
                      'https://github.com/owner/repo/tree/main',
                      'https://github.com/../repo',
                      'https://user@github.com/owner/repo'):
            with self.subTest(value=value):
                self.assertIsNone(LINKS.repository_context({'repo_url': value}, self.docs))

    def test_repository_fallback_changes_generated_html_only(self):
        folder = self.root / 'learning-packs'
        folder.mkdir()
        (folder / 'index.html').write_text('guide', encoding='utf-8')
        original = '<a href="../../../learning-packs/index.html">Offline setup</a>'
        self.source.write_text(original, encoding='utf-8')
        self.output.write_text(original, encoding='utf-8')
        entry = SimpleNamespace(src_uri='courses/learning-c/index.html',
            abs_src_path=str(self.source), abs_dest_path=str(self.output),
            is_documentation_page=lambda: False)
        config = {'site_dir': str(self.site), 'docs_dir': str(self.docs),
            'repo_url': 'https://github.com/umicom-foundation/Bits2Banking'}
        LINKS.on_files([entry], config)
        LINKS.on_post_build(config)
        once = self.output.read_bytes()
        LINKS.on_post_build(config)
        self.assertEqual(once, self.output.read_bytes())
        self.assertIn('/blob/main/learning-packs/index.html', self.output.read_text())
        self.assertEqual(original, self.source.read_text())

    def test_public_folder_symlink_cannot_expose_a_neighbour(self):
        with TemporaryDirectory() as other:
            target = Path(other) / 'private.c'
            target.write_text('private', encoding='utf-8')
            link = self.root / 'labs/native/link.c'
            link.parent.mkdir(parents=True)
            try:
                link.symlink_to(target)
            except OSError:
                self.skipTest('Host does not permit this symlink fixture')
            context = LINKS.repository_context(
                {'repo_url': 'https://github.com/umicom-foundation/Bits2Banking'}, self.docs)
            original = '<a href="../../../labs/native/link.c">Read</a>'
            self.assertEqual(original, LINKS.CourseLinks(original, self.source,
                self.output, self.documents, context).result())

    def test_source_output_overlap_is_rejected(self):
        with self.assertRaises(ValueError):
            LINKS.on_post_build({'site_dir': str(self.docs), 'docs_dir': str(self.docs)})

    def test_rendered_markdown_resolves_only_public_file_links(self):
        lab = self.root / 'labs/native/journal/README.md'
        lab.parent.mkdir(parents=True)
        lab.write_text('journal fixture', encoding='utf-8')
        note = self.root / 'docs/notes.md'
        note.parent.mkdir(exist_ok=True)
        note.write_text('working note', encoding='utf-8')
        expected = 'https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/journal/README.md'
        original = ('<a href="../../../labs/native/journal/README.md">Lab</a> '
                    '<a href="../../../docs/notes.md">Other</a> '
                    '<a href="../introduction/">Introduction</a>')
        self.page.write_text(original, encoding='utf-8')
        LINKS.on_files([SimpleNamespace(src_uri='lessons/learning-c/index.md',
            abs_src_path=str(self.manuscript), abs_dest_path=str(self.page),
            is_documentation_page=lambda: True)], {})
        LINKS.on_post_build({'site_dir': str(self.site), 'docs_dir': str(self.docs),
            'repo_url': 'https://github.com/umicom-foundation/Bits2Banking'})
        self.assertEqual(self.page.read_text(encoding='utf-8'),
                         original.replace('../../../labs/native/journal/README.md', expected))


    def test_native_payload_is_not_rewritten_by_source_link_publication(self):
        original = '<a href="../../lessons/learning-c/index.md">Manuscript</a>'
        self.output.write_text(original, encoding='utf-8')
        manifest = self.output.parent / 'learning-pack.json'
        manifest.write_text(json.dumps({'schema': 'umicom.learning.pack',
            'resources': [{'path': 'index.html'}]}), encoding='utf-8')
        before = manifest.read_bytes()
        entries = [SimpleNamespace(src_uri='courses/learning-c/index.html',
            abs_src_path=str(self.source), abs_dest_path=str(self.output),
            is_documentation_page=lambda: False),
            SimpleNamespace(src_uri='lessons/learning-c/index.md',
            abs_src_path=str(self.manuscript), abs_dest_path=str(self.page),
            is_documentation_page=lambda: True)]
        LINKS.on_files(entries, {})
        LINKS.on_post_build({'site_dir': str(self.site), 'docs_dir': str(self.docs)})
        self.assertEqual(original, self.output.read_text())
        self.assertEqual(before, manifest.read_bytes())

    def test_pack_admission_finishes_before_any_course_write(self):
        original = '<a href="../../lessons/learning-c/index.md">Manuscript</a>'
        self.output.write_text(original, encoding='utf-8')
        invalid = self.site / 'zz-invalid/learning-pack.json'
        invalid.parent.mkdir()
        invalid.write_text(json.dumps({'schema': 'umicom.learning.pack',
            'resources': [{'path': '../outside.html'}]}), encoding='utf-8')
        LINKS.on_files([SimpleNamespace(src_uri='courses/learning-c/index.html',
            abs_src_path=str(self.source), abs_dest_path=str(self.output),
            is_documentation_page=lambda: False)], {})
        with self.assertRaisesRegex(ValueError, 'escapes'):
            LINKS.on_post_build({'site_dir': str(self.site), 'docs_dir': str(self.docs)})
        self.assertEqual(original, self.output.read_text())

    def test_native_pack_resource_shape_and_paths_are_checked(self):
        manifest = self.output.parent / 'learning-pack.json'
        invalid_entries = [None, {}, [None], [{}], [{'path': None}], [{'path': 1}],
            [{'path': ''}], [{'path': '.'}], [{'path': '/absolute.html'}],
            [{'path': 'C:/absolute.html'}], [{'path': '../outside.html'}],
            [{'path': 'nested/../index.html'}], [{'path': 'nested//index.html'}],
            [{'path': 'nested\\index.html'}], [{'path': 'nul\x00name.html'}]]
        for entries in invalid_entries:
            with self.subTest(entries=entries):
                manifest.write_text(json.dumps({'schema': 'umicom.learning.pack',
                    'resources': entries}), encoding='utf-8')
                with self.assertRaises(ValueError):
                    LINKS.native_pack_resources(self.site)

    def test_native_pack_requires_present_files_and_allows_empty_pack(self):
        manifest = self.output.parent / 'learning-pack.json'
        manifest.write_text(json.dumps({'schema': 'umicom.learning.pack',
            'resources': [{'path': 'missing.html'}]}), encoding='utf-8')
        with self.assertRaisesRegex(ValueError, 'Missing'):
            LINKS.native_pack_resources(self.site)
        manifest.write_text(json.dumps({'schema': 'umicom.learning.pack',
            'resources': []}), encoding='utf-8')
        self.assertEqual(set(), LINKS.native_pack_resources(self.site))

    def test_unrelated_manifest_does_not_claim_native_ownership(self):
        manifest = self.output.parent / 'learning-pack.json'
        manifest.write_text(json.dumps({'schema': 'example.catalogue',
            'resources': [{'path': 'index.html'}]}), encoding='utf-8')
        self.assertEqual(set(), LINKS.native_pack_resources(self.site))

    def test_linked_native_payload_is_rejected_even_inside_pack(self):
        linked = self.output.parent / 'linked.html'
        try:
            linked.symlink_to(self.output)
        except (OSError, NotImplementedError):
            self.skipTest('Host cannot create a symbolic-link fixture')
        manifest = self.output.parent / 'learning-pack.json'
        manifest.write_text(json.dumps({'schema': 'umicom.learning.pack',
            'resources': [{'path': 'linked.html'}]}), encoding='utf-8')
        with self.assertRaisesRegex(ValueError, 'Linked'):
            LINKS.native_pack_resources(self.site)



    def strict_site_config(self):
        from mkdocs.config import load_config

        hook = ROOT / 'hooks/course_source_links.py'
        config_file = self.root / 'mkdocs.yml'
        config_file.write_text(
            'site_name: Publication Link Test\n'
            'docs_dir: content\n'
            'site_dir: site\n'
            'theme: mkdocs\n'
            'repo_url: https://github.com/umicom-foundation/Bits2Banking\n'
            f'hooks: [{json.dumps(hook.as_posix())}]\n',
            encoding='utf-8')
        return load_config(config_file=str(config_file), strict=True)

    @unittest.skipUnless(importlib.util.find_spec('mkdocs'), 'MkDocs documentation dependencies')
    def test_strict_build_resolves_reviewed_markdown_source_links(self):
        from mkdocs.commands.build import build

        # These files are public repository sources beyond MkDocs' docs_dir.
        for name in ('labs/native/two words.c', 'learning-packs/course.json',
                     'knowledge/registries/lesson-media.json'):
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text('resource', encoding='utf-8')
        source = self.docs / 'review/index.md'
        source.parent.mkdir()
        original = (
            '# Review\n\n'
            '[A local page](../lessons/learning-c/index.md)\n\n'
            '[A lab](../../labs/native/two%20words.c?x=1&y=2#L3)\n\n'
            '[A pack][pack]\n\n'
            '[The registry](../../knowledge/registries/lesson-media.json)\n\n'
            '[External](https://example.com/main.c)\n\n'
            '<a href="../../labs/native/two%20words.c">An HTML link</a>\n\n'
            '` [An example](../../labs/native/two%20words.c)`\n\n'
            '[pack]: ../../learning-packs/course.json\n'
        )
        source.write_text(original, encoding='utf-8')
        build(self.strict_site_config())
        output = (self.site / 'review/index.html').read_text(encoding='utf-8')
        repo = 'https://github.com/umicom-foundation/Bits2Banking/blob/main/'
        self.assertIn('href="../lessons/learning-c/"', output)
        self.assertIn(f'href="{repo}labs/native/two%20words.c?x=1&amp;y=2#L3"', output)
        self.assertIn(f'href="{repo}learning-packs/course.json"', output)
        self.assertIn(f'href="{repo}knowledge/registries/lesson-media.json"', output)
        self.assertIn(f'href="{repo}labs/native/two%20words.c"', output)
        self.assertIn('href="https://example.com/main.c"', output)
        self.assertIn('<code>[An example](../../labs/native/two%20words.c)</code>', output)
        self.assertEqual(source.read_text(encoding='utf-8'), original)

    @unittest.skipUnless(importlib.util.find_spec('mkdocs'), 'MkDocs documentation dependencies')
    def test_strict_build_still_rejects_unreviewed_and_missing_links(self):
        from mkdocs.commands.build import build
        from mkdocs.exceptions import Abort

        target = self.root / 'knowledge/registries/unreviewed.json'
        target.parent.mkdir(parents=True)
        target.write_text('unreviewed', encoding='utf-8')
        source = self.docs / 'review/index.md'
        source.parent.mkdir()
        source.write_text(
            '# Review\n\n'
            '[Unreviewed](../../knowledge/registries/unreviewed.json)\n\n'
            '[Missing approved category](../../labs/native/not-present.c)\n\n'
            '[Broken site route](missing.md)\n',
            encoding='utf-8')
        with self.assertLogs('mkdocs', level='WARNING') as found:
            with self.assertRaises(Abort):
                build(self.strict_site_config())
        for link in ('../../knowledge/registries/unreviewed.json',
                     '../../labs/native/not-present.c', 'missing.md'):
            self.assertTrue(any(f"contains a link '{link}'" in msg for msg in found.output),
                            found.output)


if __name__ == '__main__':
    unittest.main()
