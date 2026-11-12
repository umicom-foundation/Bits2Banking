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

# Load by the adjacent file identity: MkDocs and standalone checks need not run
# with the repository root on sys.path. Both adapters use the same ownership rule.
import runpy
native_pack_resources = runpy.run_path(
    str(Path(__file__).with_name('publication_artifacts.py')))['native_pack_resources']

_files = ()
# Read complete attribute values so text such as href= inside a title cannot
# be mistaken for the anchor's own destination. Retain original quote style.
_attribute = re.compile(r'''\s+([^\s"'<>/=]+)(?:\s*=\s*(?:"([^"]*)"|'([^']*)'|([^\s"'=<>`]+)))?''')



def repository_source_link(url, target, repository):
    """Publish only known public source folders, retaining local source links."""
    if repository is None:
        return None
    root, source_base = repository
    try:
        relative = target.relative_to(root)
    except ValueError:
        return None
    # Personal notes, hidden configuration and arbitrary neighbouring files are
    # never exposed by this adapter. A symlink was resolved before this check.
    if not relative.parts or relative.parts[0] not in ('labs', 'learning-packs'):
        return None
    if any(part.startswith('.') for part in relative.parts):
        return None
    if not target.is_file():
        return None
    route = source_base + quote(relative.as_posix(), safe='/')
    return escape(urlunsplit(('https', 'github.com', route, url.query, url.fragment)), quote=True)


def repository_context(config, docs):
    """Recognise the configured GitHub source identity without guessing hosts."""
    configured = urlsplit(config.get('repo_url', ''))
    if configured.scheme != 'https' or configured.netloc != 'github.com':
        return None
    if configured.query or configured.fragment:
        return None
    repository_path = configured.path.rstrip('/')
    if repository_path.endswith('.git'):
        repository_path = repository_path[:-4]
    if not re.fullmatch(r'/[A-Za-z0-9_.-]+/[A-Za-z0-9_.-]+', repository_path):
        return None
    if any(part in ('.', '..') for part in repository_path.split('/')[1:]):
        return None
    return (docs.parent.resolve(), repository_path + '/blob/main/')


def publication_link(value, source, destination, documents, repository=None):
    """Use known document identities, never guess a route from its extension."""
    url = urlsplit(unescape(value))
    if url.scheme or url.netloc or not url.path or url.path.startswith('/'):
        return value
    target = (source.parent / unquote(url.path)).resolve()
    published = documents.get(target)
    if published is None:
        # Standalone source HTML keeps repository-relative links for offline use.
        # Publication maps only admitted public repository files to GitHub.
        source_link = repository_source_link(url, target, repository)
        if source_link is not None:
            return source_link
        return value
    route = quote(os.path.relpath(published, destination.parent).replace('\\', '/'), safe='/')
    return escape(urlunsplit(('', '', route, url.query, url.fragment)), quote=True)


class CourseLinks(HTMLParser):
    """Replace only anchor href values; retain all other text of the page."""

    def __init__(self, text, source, destination, documents, repository=None):
        super().__init__(convert_charrefs=False)
        self.text = text
        self.source = source
        self.destination = destination
        self.documents = documents
        self.repository = repository
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
        replacement = publication_link(match[group], self.source, self.destination, self.documents, self.repository)
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
    # Resolve every pack before any page write so a malformed pack cannot leave
    # a partially rewritten publication. Exact payload bytes remain native-owned.
    native_resources = native_pack_resources(site)
    repository = repository_context(config, docs)
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
        if destination in native_resources:
            continue
        if destination.is_file():
            old = destination.read_text(encoding='utf-8')
            # Manuscript routing remains unchanged; the optional repository
            # context also resolves source files omitted from docs_dir.
            new = CourseLinks(old, source, destination, documents, repository).result()
            if new != old:
                destination.write_text(new, encoding='utf-8', newline='\n')
