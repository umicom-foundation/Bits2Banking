# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: hooks/course_source_links.py
#
# PURPOSE:
#   Resolve course manuscript links in published HTML without editing sources.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
"""Adapt standalone course links to MkDocs' generated document destinations.

Python is used here because MkDocs calls Python publishing hooks. This is a
publication adapter, not another course engine. Local HTML keeps its Markdown
links; generated HTML points to the pages made from those same manuscripts.
"""
from html import escape, unescape
from html.parser import HTMLParser
import os
from pathlib import Path
import re
from urllib.parse import quote, unquote, urlsplit, urlunsplit

_files = ()
# Read complete attribute values so text such as href= inside a title cannot
# be mistaken for the anchor's own destination. Retain original quote style.
_attribute = re.compile(r'''\s+([^\s"'<>/=]+)(?:\s*=\s*(?:"([^"]*)"|'([^']*)'|([^\s"'=<>`]+)))?''')


def publication_link(value, source, destination, documents):
    """Use known document identities, never guess a route from its extension."""
    url = urlsplit(unescape(value))
    if url.scheme or url.netloc or not url.path or url.path.startswith('/'):
        return value
    target = (source.parent / unquote(url.path)).resolve()
    published = documents.get(target)
    if published is None:
        return value
    route = quote(os.path.relpath(published, destination.parent).replace('\\', '/'), safe='/')
    return escape(urlunsplit(('', '', route, url.query, url.fragment)), quote=True)


class CourseLinks(HTMLParser):
    """Replace only anchor href values; retain all other text of the page."""

    def __init__(self, text, source, destination, documents):
        super().__init__(convert_charrefs=False)
        self.text = text
        self.source = source
        self.destination = destination
        self.documents = documents
        self.offsets = [0]
        for match in re.finditer('\n', text):
            self.offsets.append(match.end())
        self.edits = []

    def handle_starttag(self, tag, attrs):
        if tag != 'a':
            return
        raw = self.get_starttag_text()
        match = next((m for m in _attribute.finditer(raw) if m[1].lower() == 'href'), None)
        if match is None:
            return
        group = next((g for g in (2, 3, 4) if match[g] is not None), None)
        if group is None:
            return
        replacement = publication_link(match[group], self.source, self.destination, self.documents)
        if replacement != match[group]:
            line, column = self.getpos()
            start = self.offsets[line - 1] + column
            self.edits.append((start + match.start(group), start + match.end(group), replacement))

    def result(self):
        self.feed(self.text)
        self.close()
        result = self.text
        for start, end, value in reversed(self.edits):
            result = result[:start] + value + result[end:]
        return result


def on_files(files, config):
    global _files
    _files = tuple(files)


def on_post_build(config):
    # MkDocs determines directory-style and flat URLs. Capture its destinations
    # after rendering, including only manuscripts with an actual output file.
    site = Path(config['site_dir']).resolve()
    docs = Path(config['docs_dir']).resolve()
    if site == docs or docs in site.parents or site in docs.parents:
        raise ValueError('Course publication output must be separate from source documents')
    documents = {}
    for entry in _files:
        if entry.is_documentation_page() and entry.abs_src_path:
            target = Path(entry.abs_dest_path).resolve()
            if target.is_relative_to(site) and target.is_file():
                documents[Path(entry.abs_src_path).resolve()] = target
    for entry in _files:
        if not entry.src_uri.startswith('courses/') or not entry.src_uri.endswith('.html'):
            continue
        if not entry.abs_src_path:
            continue
        source = Path(entry.abs_src_path).resolve()
        destination = Path(entry.abs_dest_path).resolve()
        if not source.is_relative_to(docs) or not destination.is_relative_to(site):
            raise ValueError('Course file is outside its declared publication root')
        if destination.is_file():
            old = destination.read_text(encoding='utf-8')
            new = CourseLinks(old, source, destination, documents).result()
            if new != old:
                destination.write_text(new, encoding='utf-8', newline='\n')
