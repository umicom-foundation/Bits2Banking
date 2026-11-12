# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/test_umicom_branding.py
#
# PURPOSE:
#   Verify generated branding uses approved local assets without changing lessons or native packs.
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

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('umicom_branding', ROOT / 'hooks/umicom_branding.py')
BRAND = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(BRAND)
LINK_SPEC = importlib.util.spec_from_file_location(
    'course_source_links', ROOT / 'hooks/course_source_links.py')
LINKS = importlib.util.module_from_spec(LINK_SPEC)
LINK_SPEC.loader.exec_module(LINKS)


class LearningBranding(unittest.TestCase):
    def setUp(self):
        self.temp = TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.docs, self.site = self.root / 'content', self.root / 'site'
        self.page = self.site / 'courses/learning-c/lessons/one.html'
        self.page.parent.mkdir(parents=True)
        self.source = self.docs / 'courses/learning-c/lessons/one.html'
        self.source.parent.mkdir(parents=True)
        self.text = '<!doctype html><html><head><title>Lesson</title></head><body><header><strong>Learning C</strong></header><main><h1>One</h1></main></body></html>'
        self.source.write_text(self.text, encoding='utf-8')
        self.page.write_text(self.text, encoding='utf-8')
        for root in (self.docs, self.site):
            for name in (*BRAND._ASSETS, 'umicom-brand.css'):
                target = root / 'assets/branding' / name
                target.parent.mkdir(parents=True, exist_ok=True)
                target.write_bytes(('fixture for ' + name).encode())
        self.config = {'site_dir': str(self.site), 'docs_dir': str(self.docs)}

    def render(self, text=None, adaptive=False):
        return BRAND.BrandPage(self.text if text is None else text, self.page, self.site, adaptive).result()

    def test_nested_paths_keep_original_heading_and_body(self):
        output = self.render()
        self.assertIn('../../../assets/branding/umicom.ico', output)
        self.assertIn('../../../assets/branding/umicom-wordmark.svg', output)
        self.assertIn('<strong>Learning C</strong>', output)
        self.assertIn('<main><h1>One</h1></main>', output)
        self.assertEqual(1, output.count('class="umicom-brand-mark"'))

    def test_repeated_publication_does_not_duplicate_markup(self):
        once = self.render()
        self.assertEqual(once, self.render(once))

    def test_comments_scripts_and_escaped_examples_are_not_artwork(self):
        example = '<!-- <img src="umicom-logo.svg"> --><script>const sample = \'<img src="umicom-logo.svg">\';</script><pre>&lt;img src="umicom-logo.svg"&gt;</pre>'
        output = self.render(self.text.replace('<h1>One</h1>', example))
        self.assertIn(example, output)
        self.assertEqual(1, output.count('class="umicom-brand-mark"'))

    def test_correct_legacy_reference_preserves_other_attributes(self):
        logo = '<IMG title="Example src=\'other.svg\'" src=../../wrong/umicom-logo-on-dark.svg alt="Umicom" width="160">'
        output = self.render(self.text.replace('<strong>Learning C</strong>', logo))
        self.assertIn('src="../../../assets/branding/umicom-wordmark-on-dark.svg"', output)
        self.assertIn('title="Example src=\'other.svg\'"', output)
        self.assertIn('alt="Umicom" width="160"', output)
        self.assertNotIn('class="umicom-brand-mark"', output)

    def test_existing_icon_is_enough_for_a_native_style_header(self):
        text = self.text.replace('<strong>Learning C</strong>', '<img src="../../../assets/branding/umicom-icon.svg" alt="Umicom"> Learning C')
        self.assertNotIn('class="umicom-brand-mark"', self.render(text))

    def test_dark_header_uses_dark_variant_even_with_adaptive_page(self):
        output = self.render(self.text.replace('<header>', '<header class="site">'), True)
        self.assertIn('src="../../../assets/branding/umicom-wordmark-on-dark.svg"', output)
        self.assertNotIn('<source media=', output)

    def test_adaptive_page_includes_both_artwork_variants(self):
        output = self.render(adaptive=True)
        self.assertIn('<source media="(prefers-color-scheme: dark)"', output)
        self.assertIn('umicom-wordmark-on-dark.svg', output)
        self.assertIn('umicom-wordmark.svg', output)

    def test_main_can_host_mark_when_no_header_exists(self):
        output = self.render(self.text.replace('<header><strong>Learning C</strong></header>', ''))
        self.assertIn('<main><picture', output)
        self.assertEqual(1, output.count('<main>'))

    def test_fragment_is_unchanged(self):
        text = '<p>Embedded example</p><img src="umicom-logo.svg">'
        self.assertEqual(text, self.render(text))

    def test_output_changes_source_does_not_and_second_build_is_stable(self):
        BRAND.on_post_build(self.config)
        first = self.page.read_bytes()
        BRAND.on_post_build(self.config)
        self.assertEqual(first, self.page.read_bytes())
        self.assertEqual(self.text, self.source.read_text())
        self.assertIn(b'umicom-wordmark.svg', first)

    def test_missing_or_different_asset_refuses_before_page_write(self):
        asset = self.site / 'assets/branding/umicom.ico'
        asset.write_bytes(b'different')
        with self.assertRaisesRegex(ValueError, 'differs'):
            BRAND.on_post_build(self.config)
        self.assertEqual(self.text, self.page.read_text())
        asset.unlink()
        with self.assertRaisesRegex(ValueError, 'Missing'):
            BRAND.on_post_build(self.config)
        self.assertEqual(self.text, self.page.read_text())

    def test_overlapping_source_output_is_refused(self):
        with self.assertRaisesRegex(ValueError, 'separate'):
            BRAND.on_post_build({'site_dir': str(self.docs), 'docs_dir': str(self.docs)})

    def test_native_pack_payload_identity_is_preserved(self):
        manifest = self.page.parent / 'learning-pack.json'
        metadata = {'schema': 'umicom.learning.pack', 'resources': [{'path': 'one.html'}]}
        manifest.write_text(json.dumps(metadata), encoding='utf-8')
        before = manifest.read_bytes()
        BRAND.on_post_build(self.config)
        self.assertEqual(self.text, self.page.read_text())
        self.assertEqual(before, manifest.read_bytes())

    def test_native_pack_cannot_escape_its_root(self):
        manifest = self.page.parent / 'learning-pack.json'
        manifest.write_text(json.dumps({'schema': 'umicom.learning.pack', 'resources': [{'path': '../outside.html'}]}))
        with self.assertRaisesRegex(ValueError, 'escapes'):
            BRAND.on_post_build(self.config)
        self.assertEqual(self.text, self.page.read_text())

    def test_theme_detection_reads_only_local_published_stylesheets(self):
        sheet = self.site / 'course.css'
        sheet.write_text('@media(prefers-color-scheme:dark){body{color:white}}')
        text = '<link rel="stylesheet" href="../../../course.css">'
        self.assertTrue(BRAND.uses_adaptive_theme(text, self.page, self.site))
        self.assertFalse(BRAND.uses_adaptive_theme('<link rel="stylesheet" href="https://example.com/course.css">', self.page, self.site))


    def test_link_then_brand_pipeline_preserves_native_payload_and_manifest(self):
        # A browser edition may change, but the native payload and manifest are
        # one content identity. Exercise the actual configured hook ordering.
        text = self.text.replace('<h1>One</h1>',
            '<a href="../../../../learning-packs/index.html">Offline guide</a>')
        self.source.write_text(text, encoding='utf-8')
        self.page.write_text(text, encoding='utf-8')
        guide = self.root / 'learning-packs/index.html'
        guide.parent.mkdir()
        guide.write_text('guide', encoding='utf-8')
        manifest = self.page.parent / 'learning-pack.json'
        manifest.write_text(json.dumps({'schema': 'umicom.learning.pack',
            'resources': [{'path': 'one.html'}]}), encoding='utf-8')
        before = {p: p.read_bytes() for p in (self.source, self.page, manifest)}
        ordinary = self.site / 'courses/ordinary/index.html'
        ordinary.parent.mkdir(parents=True)
        ordinary.write_text(self.text, encoding='utf-8')
        config = dict(self.config, repo_url='https://github.com/umicom-foundation/Bits2Banking')
        LINKS.on_files([SimpleNamespace(src_uri='courses/learning-c/lessons/one.html',
            abs_src_path=str(self.source), abs_dest_path=str(self.page),
            is_documentation_page=lambda: False)], config)
        for unused in range(2):
            LINKS.on_post_build(config)
            BRAND.on_post_build(config)
        for file, data in before.items():
            self.assertEqual(data, file.read_bytes())
        self.assertIn('umicom-wordmark.svg', ordinary.read_text())

    def test_picture_candidates_and_fallback_use_canonical_vectors(self):
        picture = ('<picture><source media="(prefers-color-scheme: dark)" type="image/png" '
                   'srcset="../../old/umicom-logo-on-dark.svg 1x, ../old/umicom-logo-on-dark.svg 2x">'
                   '<img src="../old/umicom-logo.png" alt="Umicom" width="160"></picture>')
        output = self.render(self.text.replace('<strong>Learning C</strong>', picture))
        self.assertIn('type="image/svg+xml"', output)
        self.assertIn('srcset="../../../assets/branding/umicom-wordmark-on-dark.svg 1x, '
                      '../../../assets/branding/umicom-wordmark-on-dark.svg 2x"', output)
        self.assertIn('src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="160"', output)
        self.assertNotIn('class="umicom-brand-mark"', output)
        self.assertEqual(output, self.render(output))

    def test_img_density_candidates_preserve_sizes_and_alt(self):
        logo = ('<img src="umicom-logo.svg" srcset="umicom-logo.png .5x, umicom-logo.svg 2x" '
                'sizes="(max-width: 500px) 100px, 180px" alt="Umicom">')
        output = self.render(self.text.replace('<strong>Learning C</strong>', logo))
        self.assertIn('umicom-wordmark.svg .5x, ../../../assets/branding/umicom-wordmark.svg 2x', output)
        self.assertIn('sizes="(max-width: 500px) 100px, 180px" alt="Umicom"', output)

    def test_width_candidates_keep_their_descriptors(self):
        logo = '<img src="umicom-icon.png" srcset="umicom-icon.png 128w, umicom-icon.svg 256w">'
        output = self.render(self.text.replace('<strong>Learning C</strong>', logo))
        self.assertIn('src="../../../assets/branding/umicom-icon.svg"', output)
        self.assertIn('umicom-icon.svg 128w, ../../../assets/branding/umicom-icon.svg 256w', output)

    def test_nonbrand_or_external_candidate_lists_remain_unchanged(self):
        lists = ('diagram.svg 1x, chart.svg 2x',
                 'umicom-logo.svg 1x, diagram.svg 2x',
                 'https://example.org/umicom-logo.svg 1x',
                 'data:image/svg+xml;base64,PHN2Zz4= 1x')
        for candidates in lists:
            with self.subTest(candidates=candidates):
                text = self.text.replace('<h1>One</h1>',
                    '<picture><source srcset="' + candidates + '"><img src="diagram.svg"></picture>')
                output = self.render(text)
                self.assertIn('srcset="' + candidates + '"', output)
                self.assertIn('<img src="diagram.svg">', output)

    def test_unsupported_descriptors_are_not_reinterpreted(self):
        for candidates in ('umicom-logo.svg 0x', 'umicom-logo.svg 0w',
                           'umicom-logo.svg 1x, umicom-logo.svg 1.0x',
                           'umicom-logo.svg 1x, umicom-logo.svg 200w',
                           'umicom-logo.svg 1e2x', 'umicom-logo.svg bad'):
            with self.subTest(candidates=candidates):
                self.assertIsNone(BRAND.brand_srcset(candidates, lambda name: '/brand/' + name))
        self.assertIsNone(BRAND.brand_srcset('umicom-logo.svg ' + '9' * 400 + 'x',
                                            lambda name: '/brand/' + name))

    def test_media_source_outside_picture_is_unchanged(self):
        source = '<video><source srcset="umicom-logo.svg" type="video/example"></video>'
        output = self.render(self.text.replace('<h1>One</h1>', source))
        self.assertIn(source, output)

    def test_self_closed_picture_source_and_escaped_sample(self):
        source = '<picture><source srcset="umicom-icon-on-dark.svg"/><img src="umicom-icon.svg"></picture>'
        sample = '<pre>&lt;source srcset="umicom-logo.svg"&gt;</pre>'
        output = self.render(self.text.replace('<h1>One</h1>', source + sample))
        self.assertIn('srcset="../../../assets/branding/umicom-icon-on-dark.svg"/>', output)
        self.assertIn(sample, output)

    def test_native_responsive_payload_is_not_rewritten(self):
        text = self.text.replace('<h1>One</h1>',
            '<picture><source srcset="umicom-logo-on-dark.svg"><img src="umicom-logo.png"></picture>')
        self.page.write_text(text, encoding='utf-8')
        manifest = self.page.parent / 'learning-pack.json'
        manifest.write_text(json.dumps({'schema': 'umicom.learning.pack',
            'resources': [{'path': 'one.html'}]}), encoding='utf-8')
        before = self.page.read_bytes()
        BRAND.on_post_build(self.config)
        self.assertEqual(before, self.page.read_bytes())

    def test_template_identity_does_not_suppress_active_branding(self):
        inert = ('<template><header><img src="umicom-logo.svg"></header>'
                 '<link rel="icon" href="umicom.ico">'
                 '<link rel="stylesheet" href="umicom-brand.css"></template>')
        output = self.render(self.text.replace('<h1>One</h1>', inert))
        self.assertIn(inert, output)
        self.assertEqual(1, output.count('class="umicom-brand-mark"'))
        self.assertIn('href="../../../assets/branding/umicom.ico"', output)
        self.assertIn('href="../../../assets/branding/umicom-brand.css"', output)
        self.assertEqual(output, self.render(output))

    def test_nested_templates_leave_active_header_available(self):
        inert = '<template><template><img src="umicom-logo.svg"></template><header>Archive</header></template>'
        text = self.text.replace('<header>', inert + '<header>', 1)
        output = self.render(text)
        self.assertIn(inert, output)
        self.assertIn('</template><header><picture class="umicom-brand-mark">', output)

    def test_template_picture_cannot_capture_later_media_source(self):
        inert = '<template><picture><img src="umicom-logo.svg"></picture></template>'
        source = '<video><source srcset="umicom-logo.svg" type="video/example"></video>'
        output = self.render(self.text.replace('<h1>One</h1>', inert + source))
        self.assertIn(inert + source, output)
        self.assertEqual(1, output.count('class="umicom-brand-mark"'))

    def test_text_containers_preserve_apparent_brand_markup(self):
        for tag in ('textarea', 'xmp', 'iframe', 'noembed', 'noframes', 'noscript'):
            with self.subTest(tag=tag):
                sample = '<' + tag + '><img src="umicom-logo.svg"><link rel="icon" href="umicom.ico"></' + tag + '>'
                output = self.render(self.text.replace('<h1>One</h1>', sample))
                self.assertIn(sample, output)
                self.assertEqual(1, output.count('class="umicom-brand-mark"'))

    def test_title_text_does_not_supply_branding(self):
        title = '<title>Example <img src="umicom-logo.svg"></title>'
        output = self.render(self.text.replace('<title>Lesson</title>', title))
        self.assertIn(title, output)
        self.assertEqual(1, output.count('class="umicom-brand-mark"'))

    def test_text_example_cannot_open_or_close_a_template(self):
        example = '<textarea><template><img src="umicom-logo.svg"></template></textarea>'
        logo = '<img src="old/umicom-icon.svg" alt="Umicom">'
        output = self.render(self.text.replace('<strong>Learning C</strong>', example + logo))
        self.assertIn(example, output)
        self.assertIn('src="../../../assets/branding/umicom-icon.svg"', output)
        self.assertNotIn('class="umicom-brand-mark"', output)

    def test_template_title_does_not_anchor_an_unrelated_fragment(self):
        fragment = '<template><title>Archive</title><main>Old page</main></template><p>Fragment</p>'
        self.assertEqual(fragment, self.render(fragment))

    def test_implicit_head_can_still_use_its_active_title(self):
        text = '<!doctype html><title>Lesson</title><main><h1>One</h1></main>'
        output = self.render(text)
        self.assertIn('</title><link rel="icon"', output)
        self.assertIn('<main><picture class="umicom-brand-mark">', output)

    def test_theme_keywords_in_inert_examples_do_not_select_dark_artwork(self):
        css = '@media(prefers-color-scheme:dark){body{color:white}}'
        samples = ('<template><style>' + css + '</style></template>',
                   '<textarea><style>' + css + '</style></textarea>',
                   '<noscript><style>' + css + '</style></noscript>',
                   '<script>const lesson = "prefers-color-scheme";</script>',
                   '<p>Read about prefers-color-scheme.</p>',
                   '<!-- ' + css + ' -->')
        for sample in samples:
            with self.subTest(sample=sample):
                self.assertFalse(BRAND.uses_adaptive_theme(sample, self.page, self.site))
        self.assertTrue(BRAND.uses_adaptive_theme('<style>' + css + '</style>', self.page, self.site))

    def test_inert_stylesheet_reference_does_not_select_adaptive_theme(self):
        sheet = self.site / 'course.css'
        sheet.write_text('@media(prefers-color-scheme:dark){body{color:white}}')
        link = '<link rel="stylesheet" href="../../../course.css">'
        self.assertFalse(BRAND.uses_adaptive_theme('<template>' + link + '</template>', self.page, self.site))
        self.assertFalse(BRAND.uses_adaptive_theme('<textarea>' + link + '</textarea>', self.page, self.site))
        self.assertTrue(BRAND.uses_adaptive_theme(link, self.page, self.site))

    def test_real_stylesheet_after_inert_text_still_applies(self):
        text = '<template><style>example</style></template><style>@media(prefers-color-scheme:dark){}</style>'
        self.assertTrue(BRAND.uses_adaptive_theme(text, self.page, self.site))

    def test_publication_preserves_template_bytes_and_source(self):
        inert = '<template><picture><source srcset="umicom-logo.svg"><img src="umicom-logo.png"></picture></template>'
        text = self.text.replace('<h1>One</h1>', inert)
        self.source.write_text(text, encoding='utf-8')
        self.page.write_text(text, encoding='utf-8')
        BRAND.on_post_build(self.config)
        output = self.page.read_text(encoding='utf-8')
        self.assertIn(inert, output)
        self.assertIn('class="umicom-brand-mark"', output)
        self.assertEqual(text, self.source.read_text(encoding='utf-8'))
        BRAND.on_post_build(self.config)
        self.assertEqual(output, self.page.read_text(encoding='utf-8'))



    def test_missing_favicon_formats_are_added_independently(self):
        output = self.render()
        self.assertIn('<link rel="icon" type="image/svg+xml" href="../../../assets/branding/umicom-icon.svg">', output)
        self.assertIn('<link rel="alternate icon" type="image/x-icon" href="../../../assets/branding/umicom.ico">', output)
        self.assertEqual(output, self.render(output))

    def test_existing_svg_keeps_variant_and_gains_ico(self):
        icon = '<link rel="icon" type="image/png" href="old/umicom-icon-on-dark.svg">'
        output = self.render(self.text.replace('</head>', icon + '</head>'))
        self.assertIn('type="image/svg+xml" href="../../../assets/branding/umicom-icon-on-dark.svg"', output)
        self.assertEqual(1, output.count('umicom-icon-on-dark.svg'))
        self.assertEqual(1, output.count('umicom.ico'))
        self.assertEqual(output, self.render(output))

    def test_existing_ico_gains_svg_without_duplicate_ico(self):
        icon = '<link rel="icon" type="image/png" href="old/umicom.ico">'
        output = self.render(self.text.replace('</head>', icon + '</head>'))
        self.assertIn('type="image/x-icon" href="../../../assets/branding/umicom.ico"', output)
        self.assertEqual(1, output.count('umicom.ico'))
        self.assertEqual(1, output.count('umicom-icon.svg'))
        self.assertEqual(output, self.render(output))

    def test_inert_icon_links_do_not_satisfy_either_format(self):
        links = '<link rel="icon" href="umicom.ico"><link rel="icon" href="umicom-icon.svg">'
        for container in ('template', 'textarea', 'noscript'):
            inert = '<' + container + '>' + links + '</' + container + '>'
            output = self.render(self.text.replace('</head>', inert + '</head>'))
            self.assertIn(inert, output)
            self.assertIn('href="../../../assets/branding/umicom.ico"', output)
            self.assertIn('href="../../../assets/branding/umicom-icon.svg"', output)
            self.assertEqual(output, self.render(output))

    def test_external_and_malformed_icon_urls_remain_unchanged(self):
        for href in ('https://example.org/umicom.ico', 'https://example.org/umicom-icon.svg',
                     'http://[invalid/umicom.ico'):
            icon = '<link rel="icon" href="' + href + '">'
            output = self.render(self.text.replace('</head>', icon + '</head>'))
            self.assertIn(icon, output)
            self.assertIn('href="../../../assets/branding/umicom.ico"', output)
            self.assertIn('href="../../../assets/branding/umicom-icon.svg"', output)
            self.assertEqual(output, self.render(output))


class OfflineBrandAssets(unittest.TestCase):
    """Source HTML must carry approved artwork without running a site publisher."""

    @staticmethod
    def load(name):
        from xml.etree import ElementTree
        return ElementTree.parse(ROOT / 'content/assets/branding' / name).getroot()

    @staticmethod
    def paint_nodes(element):
        tag = element.tag.rsplit('}', 1)[-1]
        # Historical text is deliberately preserved inside definitions. It is
        # not visible artwork and must not cause a false regression failure.
        if tag in ('defs', 'title', 'desc', 'metadata'):
            return []
        nodes = [] if tag in ('svg', 'g') else [element]
        for child in element:
            nodes.extend(OfflineBrandAssets.paint_nodes(child))
        return nodes

    def test_offline_light_alias_uses_approved_geometry(self):
        alias = self.load('umicom-logo.svg')
        master = self.load('umicom-wordmark.svg')
        signature = lambda e: (e.tag, sorted(e.attrib.items()))
        self.assertEqual(list(map(signature, self.paint_nodes(master))),
                         list(map(signature, self.paint_nodes(alias))))
        self.assertEqual('0 0 1064 261', alias.get('viewBox'))

    def test_offline_dark_alias_uses_approved_geometry(self):
        alias = self.load('umicom-logo-on-dark.svg')
        master = self.load('umicom-wordmark-on-dark.svg')
        signature = lambda e: (e.tag, sorted(e.attrib.items()))
        self.assertEqual(list(map(signature, self.paint_nodes(master))),
                         list(map(signature, self.paint_nodes(alias))))
        self.assertEqual('0 0 1064 261', alias.get('viewBox'))

    def test_offline_aliases_do_not_draw_text_or_load_an_external_image(self):
        for name in ('umicom-logo.svg', 'umicom-logo-on-dark.svg'):
            with self.subTest(name=name):
                nodes = self.paint_nodes(self.load(name))
                self.assertGreater(len(nodes), 0)
                self.assertFalse(any(e.tag.rsplit('}', 1)[-1] in ('text', 'image', 'foreignObject')
                                     for e in nodes))
                self.assertTrue(any(e.tag.rsplit('}', 1)[-1] == 'path' for e in nodes))

    def test_offline_aliases_retain_the_superseded_font_implementation(self):
        for name in ('umicom-logo.svg', 'umicom-logo-on-dark.svg'):
            with self.subTest(name=name):
                root = self.load(name)
                definitions = [e for e in root if e.tag.rsplit('}', 1)[-1] == 'defs']
                self.assertTrue(definitions)
                self.assertTrue(any(e.tag.rsplit('}', 1)[-1] == 'text'
                                    for d in definitions for e in d.iter()))

    def test_all_standalone_course_pages_declare_approved_local_icons(self):
        from hashlib import sha256
        from html.parser import HTMLParser
        from urllib.parse import unquote, urlsplit

        class IconLinks(HTMLParser):
            def __init__(self):
                super().__init__()
                self.markup = BRAND.ActiveMarkup()
                self.in_head = False
                self.complete = False
                self.links = []

            def handle_starttag(self, tag, attrs):
                if not self.markup.start(tag):
                    return
                if tag == 'head':
                    self.in_head = True
                    self.complete = True
                values = dict(attrs)
                if self.in_head and tag == 'link' and 'icon' in (values.get('rel') or '').lower().split():
                    self.links.append(values.get('href') or '')

            def handle_startendtag(self, tag, attrs):
                self.handle_starttag(tag, attrs)

            def handle_endtag(self, tag):
                if self.markup.end(tag) and tag == 'head':
                    self.in_head = False

        # Hashes identify approved local payloads, not filenames that another
        # image could accidentally reuse. The compact historical icon is an
        # approved derivative; the geometry check below protects that exception.
        digest = lambda p: sha256(p.read_bytes().replace(b'\r\n', b'\n') if p.suffix == '.svg'
                                  else p.read_bytes()).hexdigest()
        approved_svg = {digest(ROOT / 'content/assets/branding' / name)
                        for name in ('umicom-icon.svg', 'umicom-icon-on-dark.svg')}
        approved_svg.add(digest(ROOT / 'content/courses/assets/branding/umicom-icon-on-dark.svg'))
        approved_ico = digest(ROOT / 'content/assets/branding/umicom.ico')
        checked = 0
        for page in sorted((ROOT / 'content/courses').rglob('*.html')):
            observer = IconLinks()
            observer.feed(page.read_text(encoding='utf-8'))
            observer.close()
            if not observer.complete:
                continue
            with self.subTest(page=str(page.relative_to(ROOT))):
                identities = set()
                for href in observer.links:
                    url = urlsplit(href)
                    self.assertFalse(url.scheme or url.netloc or url.path.startswith('/'))
                    target = (page.parent / unquote(url.path)).resolve()
                    self.assertTrue(target.is_relative_to(ROOT))
                    self.assertTrue(target.is_file())
                    self.assertFalse(target.is_symlink())
                    identities.add(digest(target))
                self.assertTrue(identities & approved_svg)
                self.assertIn(approved_ico, identities)
            checked += 1
        self.assertGreater(checked, 0)

    def test_compact_course_icon_retains_the_master_visible_geometry(self):
        from xml.etree import ElementTree
        compact = ElementTree.parse(
            ROOT / 'content/courses/assets/branding/umicom-icon-on-dark.svg').getroot()
        master = self.load('umicom-icon-on-dark.svg')
        # The master also contains transparent coordinate-envelope paths.
        # Compare only painted paths; the compact derivative intentionally omits
        # those invisible shapes while retaining all visible geometry and colour.
        signature = lambda node: (node.tag, *( ' '.join(node.get(key, '').split())
                                              for key in ('d', 'fill', 'transform')))
        visible = lambda image: [node for node in self.paint_nodes(image)
                                 if node.get('fill') != 'none']
        self.assertEqual(4, len(visible(master)))
        self.assertEqual(list(map(signature, visible(master))),
                         list(map(signature, visible(compact))))

if __name__ == '__main__':
    unittest.main()
