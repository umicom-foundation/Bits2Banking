# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: hooks/umicom_branding.py
#
# PURPOSE:
#   Apply approved site artwork to generated learning pages without rewriting manuscripts.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
"""A MkDocs publication adapter for the existing Umicom asset collection.

Python is required by the MkDocs hook interface. Native application branding
continues to belong to Framework's resource catalogue. This adapter changes
only generated HTML; it neither redraws artwork nor runs lesson examples.
"""
from html import escape
from html.parser import HTMLParser
from math import isfinite
import os
import json
from pathlib import Path
import re
from urllib.parse import quote, urlsplit

# Load by the adjacent file identity: MkDocs and standalone checks need not run
# with the repository root on sys.path. Both adapters use the same ownership rule.
import runpy
ActiveMarkup = runpy.run_path(
    str(Path(__file__).with_name('active_markup.py')))['ActiveMarkup']
native_pack_resources = runpy.run_path(
    str(Path(__file__).with_name('publication_artifacts.py')))['native_pack_resources']

_ATTRIBUTE = re.compile(r'''\s+([^\s"'<>/=]+)(?:\s*=\s*(?:"([^"]*)"|'([^']*)'|([^\s"'=<>\x60]+)))?''')
_BRAND_IMAGES = frozenset({
    'umicom-logo.svg', 'umicom-logo-on-dark.svg',
    'umicom-wordmark.svg', 'umicom-wordmark-on-dark.svg',
    'umicom-icon.svg', 'umicom-icon-on-dark.svg',
    'umicom-logo.png', 'umicom-icon.png',
})
_ASSETS = ('umicom-wordmark.svg', 'umicom-wordmark-on-dark.svg',
           'umicom-icon.svg', 'umicom-icon-on-dark.svg', 'umicom.ico')


def relative_url(target, page):
    return quote(os.path.relpath(target, page.parent).replace('\\', '/'), safe='/')



def brand_asset_name(value):
    """Map only known local Umicom artwork; leave other images and hosts alone."""
    try:
        url = urlsplit(value or '')
    except ValueError:
        return None
    if url.scheme or url.netloc:
        return None
    name = Path(url.path).name
    if name not in _BRAND_IMAGES:
        return None
    if name.endswith('.png'):
        name = name[:-4] + '.svg'
    if name.startswith('umicom-logo'):
        name = name.replace('umicom-logo', 'umicom-wordmark', 1)
    return name


def brand_srcset(value, asset):
    """Rewrite an all-brand local candidate list without parsing arbitrary media.

    Density and width descriptors remain attached to their candidates. A mixed,
    external, data or unsupported list is left intact for manual review.
    """
    candidates, descriptors, families = [], set(), set()
    for item in (value or '').split(','):
        match = re.fullmatch(r'\s*([^\s,]+)(?:\s+([1-9][0-9]*w|(?:[0-9]+(?:\.[0-9]+)?|\.[0-9]+)x))?\s*', item)
        if not match:
            return None
        name = brand_asset_name(match[1])
        if name is None:
            return None
        descriptor = match[2]
        family = 'w' if descriptor and descriptor.endswith('w') else 'x'
        number = descriptor[:-1] if family == 'w' else float(descriptor[:-1]) if descriptor else 1.0
        if family == 'x' and (not isfinite(number) or number <= 0):
            return None
        if (family, number) in descriptors:
            return None
        descriptors.add((family, number))
        families.add(family)
        if len(families) != 1:
            return None
        candidates.append(asset(name) + (' ' + descriptor if descriptor else ''))
    return ', '.join(candidates) if candidates else None


class BrandPage(HTMLParser):
    """Find real markup positions while leaving code samples and scripts alone."""
    def __init__(self, text, page, site, adaptive=False):
        super().__init__(convert_charrefs=False)
        self.text, self.page, self.site = text, page, site
        self.adaptive = adaptive
        self.offsets = [0] + [m.end() for m in re.finditer('\n', text)]
        self.edits = []
        self.picture_depth = 0
        self.markup = ActiveMarkup()
        self.head_end = self.body_start = self.main_end = self.header_end = self.title_end = None
        self.header_dark = self.branded = self.icon = self.style = False
        # SVG and ICO are separate publication requirements; one cannot stand in for the other.
        self.svg_icon = False

    def position(self):
        line, column = self.getpos()
        return self.offsets[line - 1] + column

    def asset(self, name):
        return relative_url(self.site / 'assets/branding' / name, self.page)

    def replace_attribute(self, raw, name, value):
        match = next((m for m in _ATTRIBUTE.finditer(raw) if m[1].lower() == name), None)
        if match is None:
            return
        group = next((g for g in (2, 3, 4) if match[g] is not None), None)
        if group is None:
            return
        replacement = escape(value, quote=True)
        # A new relative URL has no whitespace, but quote originally unquoted
        # attributes too so unusual Unicode/space-bearing directory names work.
        if group == 4:
            replacement = '"' + replacement + '"'
        if replacement != match[group]:
            start = self.position()
            self.edits.append((start + match.start(group), start + match.end(group), replacement))

    # Responsive candidates can override img src in a browser. Preserve the
    # earlier src-only policy below while the active method admits both paths.
    if False:
        def handle_starttag(self, tag, attrs):
            raw = self.get_starttag_text()
            attrs = dict(attrs)
            position = self.position()
            if tag == 'body' and self.body_start is None:
                self.body_start = position
            if tag == 'main' and self.main_end is None:
                self.main_end = position + len(raw)
            if tag == 'header' and self.header_end is None:
                self.header_end = position + len(raw)
                self.header_dark = 'site' in (attrs.get('class') or '').split()
            if tag == 'img':
                url = urlsplit(attrs.get('src') or '')
                name = Path(url.path).name
                if not url.scheme and not url.netloc and name in _BRAND_IMAGES:
                    self.branded = True
                    if name.startswith('umicom-logo'):
                        name = name.replace('umicom-logo', 'umicom-wordmark')
                    self.replace_attribute(raw, 'src', self.asset(name))
            if tag == 'link':
                rel = (attrs.get('rel') or '').lower().split()
                url = urlsplit(attrs.get('href') or '')
                if 'icon' in rel and Path(url.path).name == 'umicom.ico':
                    self.icon = True
                    self.replace_attribute(raw, 'href', self.asset('umicom.ico'))
                if 'stylesheet' in rel and Path(url.path).name == 'umicom-brand.css':
                    self.style = True
                    self.replace_attribute(raw, 'href', self.asset('umicom-brand.css'))

    # Retained for review: apparent tags inside templates and embedded text
    # formerly counted as page identity. Context admission now preserves that
    # source while requiring branding in the active document.
    if False:
        def handle_starttag(self, tag, attrs):
            raw = self.get_starttag_text()
            attrs = dict(attrs)
            position = self.position()
            if tag == 'picture':
                self.picture_depth += 1
            if tag == 'body' and self.body_start is None:
                self.body_start = position
            if tag == 'main' and self.main_end is None:
                self.main_end = position + len(raw)
            if tag == 'header' and self.header_end is None:
                self.header_end = position + len(raw)
                self.header_dark = 'site' in (attrs.get('class') or '').split()
            if tag == 'img':
                name = brand_asset_name(attrs.get('src'))
                if name is not None:
                    self.branded = True
                    self.replace_attribute(raw, 'src', self.asset(name))
            if tag == 'img' or (tag == 'source' and self.picture_depth):
                candidates = brand_srcset(attrs.get('srcset'), self.asset)
                if candidates is not None:
                    self.replace_attribute(raw, 'srcset', candidates)
                    if tag == 'img':
                        self.branded = True
                    if tag == 'source' and attrs.get('type'):
                        self.replace_attribute(raw, 'type', 'image/svg+xml')
            if tag == 'link':
                rel = (attrs.get('rel') or '').lower().split()
                url = urlsplit(attrs.get('href') or '')
                if 'icon' in rel and Path(url.path).name == 'umicom.ico':
                    self.icon = True
                    self.replace_attribute(raw, 'href', self.asset('umicom.ico'))
                if 'stylesheet' in rel and Path(url.path).name == 'umicom-brand.css':
                    self.style = True
                    self.replace_attribute(raw, 'href', self.asset('umicom-brand.css'))

    # The earlier observer tracked only ICO links. Retain it for review while
    # the active method admits both local formats and preserves external links.
    if False:
        def handle_starttag(self, tag, attrs):
            if not self.markup.start(tag):
                return
            raw = self.get_starttag_text()
            attrs = dict(attrs)
            position = self.position()
            if tag == 'picture':
                self.picture_depth += 1
            if tag == 'body' and self.body_start is None:
                self.body_start = position
            if tag == 'main' and self.main_end is None:
                self.main_end = position + len(raw)
            if tag == 'header' and self.header_end is None:
                self.header_end = position + len(raw)
                self.header_dark = 'site' in (attrs.get('class') or '').split()
            if tag == 'img':
                name = brand_asset_name(attrs.get('src'))
                if name is not None:
                    self.branded = True
                    self.replace_attribute(raw, 'src', self.asset(name))
            if tag == 'img' or (tag == 'source' and self.picture_depth):
                candidates = brand_srcset(attrs.get('srcset'), self.asset)
                if candidates is not None:
                    self.replace_attribute(raw, 'srcset', candidates)
                    if tag == 'img':
                        self.branded = True
                    if tag == 'source' and attrs.get('type'):
                        self.replace_attribute(raw, 'type', 'image/svg+xml')
            if tag == 'link':
                rel = (attrs.get('rel') or '').lower().split()
                url = urlsplit(attrs.get('href') or '')
                if 'icon' in rel and Path(url.path).name == 'umicom.ico':
                    self.icon = True
                    self.replace_attribute(raw, 'href', self.asset('umicom.ico'))
                if 'stylesheet' in rel and Path(url.path).name == 'umicom-brand.css':
                    self.style = True
                    self.replace_attribute(raw, 'href', self.asset('umicom-brand.css'))


    def handle_starttag(self, tag, attrs):
        if not self.markup.start(tag):
            return
        raw = self.get_starttag_text()
        attrs = dict(attrs)
        position = self.position()
        if tag == 'picture':
            self.picture_depth += 1
        if tag == 'body' and self.body_start is None:
            self.body_start = position
        if tag == 'main' and self.main_end is None:
            self.main_end = position + len(raw)
        if tag == 'header' and self.header_end is None:
            self.header_end = position + len(raw)
            self.header_dark = 'site' in (attrs.get('class') or '').split()
        if tag == 'img':
            name = brand_asset_name(attrs.get('src'))
            if name is not None:
                self.branded = True
                self.replace_attribute(raw, 'src', self.asset(name))
        if tag == 'img' or (tag == 'source' and self.picture_depth):
            candidates = brand_srcset(attrs.get('srcset'), self.asset)
            if candidates is not None:
                self.replace_attribute(raw, 'srcset', candidates)
                if tag == 'img':
                    self.branded = True
                if tag == 'source' and attrs.get('type'):
                    self.replace_attribute(raw, 'type', 'image/svg+xml')
        if tag == 'link':
            rel = (attrs.get('rel') or '').lower().split()
            try:
                url = urlsplit(attrs.get('href') or '')
            except ValueError:
                url = None
            # Only known local artwork belongs to this adapter. External or
            # malformed references do not suppress the required local identity.
            name = Path(url.path).name if url is not None and not url.scheme and not url.netloc else None
            if 'icon' in rel and name in ('umicom-icon.svg', 'umicom-icon-on-dark.svg'):
                self.svg_icon = True
                self.replace_attribute(raw, 'href', self.asset(name))
                if attrs.get('type'):
                    self.replace_attribute(raw, 'type', 'image/svg+xml')
            if 'icon' in rel and name == 'umicom.ico':
                self.icon = True
                self.replace_attribute(raw, 'href', self.asset('umicom.ico'))
                if attrs.get('type'):
                    self.replace_attribute(raw, 'type', 'image/x-icon')
            if 'stylesheet' in rel and name == 'umicom-brand.css':
                self.style = True
                self.replace_attribute(raw, 'href', self.asset('umicom-brand.css'))

    def handle_startendtag(self, tag, attrs):
        self.handle_starttag(tag, attrs)

    # Preserve the former closing-tag observer while active context owns anchors.
    if False:
        def handle_endtag(self, tag):
            if tag == 'picture':
                self.picture_depth = max(0, self.picture_depth - 1)
            if tag == 'head' and self.head_end is None:
                self.head_end = self.position()
            if tag == 'title' and self.title_end is None:
                self.title_end = self.position() + len('</title>')

    def handle_endtag(self, tag):
        if not self.markup.end(tag):
            return
        if tag == 'picture':
            self.picture_depth = max(0, self.picture_depth - 1)
        if tag == 'head' and self.head_end is None:
            self.head_end = self.position()
        if tag == 'title' and self.title_end is None:
            self.title_end = self.position() + len('</title>')

    # Preserve the ICO-only publication policy for comparison. The active
    # publisher adds missing SVG and ICO metadata independently and remains idempotent.
    if False:
        def result(self):
            self.feed(self.text)
            self.close()
            head = self.head_end if self.head_end is not None else self.body_start
            if head is None:
                head = self.title_end
            content = self.header_end if self.header_end is not None else self.main_end
            # HTML fragments are not standalone pages and must not gain an invented
            # document shell. The owning page supplies their branding.
            if head is None or content is None:
                return self.text
            links = ''
            if not self.icon:
                links += '<link rel="icon" type="image/x-icon" href="' + escape(self.asset('umicom.ico'), quote=True) + '">\n'
            if not self.style:
                links += '<link rel="stylesheet" href="' + escape(self.asset('umicom-brand.css'), quote=True) + '">\n'
            if links:
                self.edits.append((head, head, links))
            if not self.branded:
                dark = self.asset('umicom-wordmark-on-dark.svg')
                light = self.asset('umicom-wordmark.svg')
                sources = ''
                if self.adaptive and not self.header_dark:
                    sources = '<source media="(prefers-color-scheme: dark)" srcset="' + escape(dark, quote=True) + '">'
                mark = '<picture class="umicom-brand-mark">' + sources + '<img src="' + escape(dark if self.header_dark else light, quote=True) + '" width="180" alt="Umicom"></picture>\n'
                self.edits.append((content, content, mark))
            result = self.text
            for start, end, value in sorted(self.edits, reverse=True):
                result = result[:start] + value + result[end:]
            return result


    def result(self):
        self.feed(self.text)
        self.close()
        head = self.head_end if self.head_end is not None else self.body_start
        if head is None:
            head = self.title_end
        content = self.header_end if self.header_end is not None else self.main_end
        # HTML fragments are not standalone pages and must not gain an invented
        # document shell. The owning page supplies their branding.
        if head is None or content is None:
            return self.text
        links = ''
        if not self.svg_icon:
            links += '<link rel="icon" type="image/svg+xml" href="' + escape(self.asset('umicom-icon.svg'), quote=True) + '">\n'
        if not self.icon:
            links += '<link rel="alternate icon" type="image/x-icon" href="' + escape(self.asset('umicom.ico'), quote=True) + '">\n'
        if not self.style:
            links += '<link rel="stylesheet" href="' + escape(self.asset('umicom-brand.css'), quote=True) + '">\n'
        if links:
            self.edits.append((head, head, links))
        if not self.branded:
            dark = self.asset('umicom-wordmark-on-dark.svg')
            light = self.asset('umicom-wordmark.svg')
            sources = ''
            if self.adaptive and not self.header_dark:
                sources = '<source media="(prefers-color-scheme: dark)" srcset="' + escape(dark, quote=True) + '">'
            mark = '<picture class="umicom-brand-mark">' + sources + '<img src="' + escape(dark if self.header_dark else light, quote=True) + '" width="180" alt="Umicom"></picture>\n'
            self.edits.append((content, content, mark))
        result = self.text
        for start, end, value in sorted(self.edits, reverse=True):
            result = result[:start] + value + result[end:]
        return result


# Retained for review: raw keyword scanning and unrestricted stylesheet tags
# included inert examples. The shared context observer below keeps those bytes
# untouched and inspects active style elements and local linked sheets.
if False:
    class Stylesheets(HTMLParser):
        def __init__(self):
            super().__init__()
            self.urls = []
    
        def handle_starttag(self, tag, attrs):
            attrs = dict(attrs)
            if tag == 'link' and 'stylesheet' in (attrs.get('rel') or '').split():
                self.urls.append(attrs.get('href') or '')
    
    
    def uses_adaptive_theme(text, page, site):
        if 'prefers-color-scheme' in text:
            return True
        parser = Stylesheets()
        parser.feed(text)
        for value in parser.urls:
            url = urlsplit(value)
            if url.scheme or url.netloc or not url.path or url.path.startswith('/'):
                continue
            from urllib.parse import unquote
            sheet = (page.parent / unquote(url.path)).resolve()
            if sheet.is_relative_to(site) and sheet.is_file() and not sheet.is_symlink():
                if 'prefers-color-scheme' in sheet.read_text(encoding='utf-8'):
                    return True
        return False

class Stylesheets(HTMLParser):
    """Observe active stylesheet references and active inline CSS only."""
    def __init__(self):
        super().__init__()
        self.urls = []
        self.inline_css = []
        self.markup = ActiveMarkup()
        self.in_style = False

    def handle_starttag(self, tag, attrs):
        if tag == 'style' and self.markup.outside_text():
            self.in_style = True
        if not self.markup.start(tag):
            return
        attrs = dict(attrs)
        if tag == 'link' and 'stylesheet' in (attrs.get('rel') or '').lower().split():
            self.urls.append(attrs.get('href') or '')

    def handle_startendtag(self, tag, attrs):
        # In HTML, a slash does not make template or raw-text elements void.
        self.handle_starttag(tag, attrs)

    def handle_endtag(self, tag):
        if tag == 'style' and self.in_style:
            self.in_style = False
        self.markup.end(tag)

    def handle_data(self, data):
        if self.in_style:
            self.inline_css.append(data)


def uses_adaptive_theme(text, page, site):
    parser = Stylesheets()
    parser.feed(text)
    parser.close()
    if 'prefers-color-scheme' in ''.join(parser.inline_css):
        return True
    for value in parser.urls:
        url = urlsplit(value)
        if url.scheme or url.netloc or not url.path or url.path.startswith('/'):
            continue
        from urllib.parse import unquote
        sheet = (page.parent / unquote(url.path)).resolve()
        if sheet.is_relative_to(site) and sheet.is_file() and not sheet.is_symlink():
            if 'prefers-color-scheme' in sheet.read_text(encoding='utf-8'):
                return True
    return False


def on_post_build(config):
    docs = Path(config['docs_dir']).resolve()
    site = Path(config['site_dir']).resolve()
    if site == docs or docs in site.parents or site in docs.parents:
        raise ValueError('Brand publication output must be separate from source documents')
    # MkDocs copies these exact source assets. Refuse incomplete or stale asset
    # output rather than publish pages whose branding appears to be available.
    for name in (*_ASSETS, 'umicom-brand.css'):
        source, output = docs / 'assets/branding' / name, site / 'assets/branding' / name
        if source.is_symlink() or output.is_symlink() or not source.is_file() or not output.is_file():
            raise ValueError('Missing or linked Umicom brand asset: ' + name)
        if source.read_bytes() != output.read_bytes():
            raise ValueError('Published Umicom brand asset differs from source: ' + name)
    # Native learning packs bind exact source bytes to checksums. Their native
    # host already owns branding. Do not change those payload pages while
    # composing the browser site; source editions are published separately.
    # The former branding-only admission is retained for engineering review.
    # Shared admission now protects link rewriting and branding consistently.
    if False:
        native_resources = set()
        for manifest in site.rglob('learning-pack.json'):
            if manifest.is_symlink() or not manifest.resolve().is_relative_to(site):
                raise ValueError('Linked native learning manifest: ' + str(manifest))
            metadata = json.loads(manifest.read_text(encoding='utf-8'))
            if metadata.get('schema') == 'umicom.learning.pack':
                for resource in metadata.get('resources', []):
                    target = (manifest.parent / resource['path']).resolve()
                    if not target.is_relative_to(manifest.parent.resolve()):
                        raise ValueError('Native learning resource escapes its pack')
                    native_resources.add(target)
    native_resources = native_pack_resources(site)
    pages = sorted(site.rglob('*.html'))
    for page in pages:
        if page.is_symlink() or not page.resolve().is_relative_to(site):
            raise ValueError('Linked page is outside the publication boundary: ' + str(page))
    for page in pages:
        if page.resolve() in native_resources:
            continue
        old = page.read_text(encoding='utf-8')
        new = BrandPage(old, page, site, uses_adaptive_theme(old, page, site)).result()
        if new != old:
            page.write_text(new, encoding='utf-8', newline='\n')
