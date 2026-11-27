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
from functools import lru_cache
from html import escape, unescape
from html.parser import HTMLParser
import os
from pathlib import Path
import re
from urllib.parse import quote, unquote, urlsplit, urlunsplit

# Load by the adjacent file identity: MkDocs and standalone checks need not run
# with the repository root on sys.path. Both adapters use the same ownership rule.
import runpy
_publication = runpy.run_path(str(Path(__file__).with_name('publication_artifacts.py')))
native_pack_resources = _publication['native_pack_resources']
public_repository_file = _publication['public_repository_file']

_files = ()
# Read complete attribute values so text such as href= inside a title cannot
# be mistaken for the anchor's own destination. Retain original quote style.
_attribute = re.compile(r'''\s+([^\s"'<>/=]+)(?:\s*=\s*(?:"([^"]*)"|'([^']*)'|([^\s"'=<>`]+)))?''')



def repository_source_link(url, target, repository):
    """Publish only known public source folders, retaining local source links."""
    if repository is None:
        return None
    root, source_base = repository
    # Share the reviewed public source rule with validation. Keep the earlier
    # standalone path rules here as a record of the original publication scope.
    if False:
        try:
            relative = target.relative_to(root)
        except ValueError:
            return None
        if not relative.parts or relative.parts[0] not in ('labs', 'learning-packs'):
            return None
        if any(part.startswith('.') for part in relative.parts):
            return None
        if not target.is_file():
            return None
    relative = public_repository_file(target, root)
    if relative is None:
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


def publication_reference_target(directory, path):
    """Resolve a publication link against its manuscript's source directory."""
    return (directory / unquote(path)).resolve()


def cached_publication_reference_targets():
    """Reuse source identities for repeated navigation within one site render."""
    return lru_cache(maxsize=16384)(publication_reference_target)


def publication_link(value, source, destination, documents, repository=None,
                     resolve_target=publication_reference_target):
    """Use known document identities, never guess a route from its extension."""
    url = urlsplit(unescape(value))
    if url.scheme or url.netloc or not url.path or url.path.startswith('/'):
        return value
    # The earlier direct read is retained for review. The injected resolver
    # applies the same normalization and can share its result within a build.
    if False:
        target = (source.parent / unquote(url.path)).resolve()
    target = resolve_target(source.parent, url.path)
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

    def __init__(self, text, source, destination, documents, repository=None,
                 resolve_target=publication_reference_target):
        super().__init__(convert_charrefs=False)
        self.text = text
        self.source = source
        self.destination = destination
        self.documents = documents
        self.repository = repository
        self.resolve_target = resolve_target
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
        # Preserve the earlier invocation for review. A shared source target
        # still goes through this page's destination and public link policy.
        if False:
            replacement = publication_link(match[group], self.source, self.destination, self.documents, self.repository)
        replacement = publication_link(
            match[group], self.source, self.destination, self.documents,
            self.repository, resolve_target=self.resolve_target)
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



# MkDocs renders one page at a time immediately after on_page_markdown.
# Its Markdown extension gets the active source path before it sees any links.
_markdown_scope = None


def on_config(config):
    """Register the website-only rewrite before MkDocs validates relative links."""
    # Keep standalone HTML tests usable without importing the MkDocs toolchain.
    from markdown.extensions import Extension
    from markdown.treeprocessors import Treeprocessor

    class PublicRepositoryLinks(Treeprocessor):
        def run(self, root):
            if _markdown_scope is None:
                return root
            source, repository = _markdown_scope
            for anchor in root.iter('a'):
                href = anchor.get('href')
                if href is None:
                    continue
                # Use the same checked repository mapping as the HTML adapter.
                # Empty document identities leave ordinary MkDocs routes alone.
                replacement = publication_link(href, source, source, {}, repository)
                if replacement != href:
                    # The tree serializer escapes attribute values itself.
                    anchor.set('href', unescape(replacement))
            return root

    class PublicRepositoryExtension(Extension):
        umicom_repository_links = True

        def extendMarkdown(self, md):
            # Inline links already exist at priority 2. MkDocs validates
            # relative paths at priority 0 and accepts recognised public URLs.
            md.treeprocessors.register(PublicRepositoryLinks(md), 'umicom_repository_links', 2)

    extensions = config['markdown_extensions']
    if not any(getattr(extension, 'umicom_repository_links', False) for extension in extensions):
        extensions.append(PublicRepositoryExtension())
    return config


def on_page_markdown(markdown, page, config, files):
    global _markdown_scope
    docs = Path(config['docs_dir']).resolve()
    repository = repository_context(config, docs)
    path = page.file.abs_src_path
    _markdown_scope = (Path(path).resolve(), repository) if repository and path else None
    # The checked-in Markdown stays useful when read directly in a clone.
    return markdown


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
    # Each build observes its own source tree. A bounded cache shares target
    # resolution between pages without carrying source identities into rebuilds.
    resolve_target = cached_publication_reference_targets()
    documents = {}
    for entry in _files:
        if entry.is_documentation_page() and entry.abs_src_path:
            target = Path(entry.abs_dest_path).resolve()
            if target.is_relative_to(site) and target.is_file():
                documents[Path(entry.abs_src_path).resolve()] = target
    for entry in _files:
        manuscript = entry.is_documentation_page()
        course_html = entry.src_uri.startswith('courses/') and entry.src_uri.endswith('.html')
        if not manuscript and not course_html:
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
            # Rendered Markdown already has MkDocs' internal document URLs.
            # Apply public source redirects there without rerouting those links.
            destinations = {} if manuscript else documents
            # The earlier per-page call is retained for review. The active
            # call shares only source resolution across the generated pages.
            if False:
                new = CourseLinks(old, source, destination, destinations, repository).result()
            new = CourseLinks(
                old, source, destination, destinations, repository,
                resolve_target=resolve_target).result()
            if new != old:
                destination.write_text(new, encoding='utf-8', newline='\n')
