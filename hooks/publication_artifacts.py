#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: hooks/publication_artifacts.py
#
# PURPOSE:
#   Identify immutable native learning payloads before any website adapter writes output.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

"""Shared MkDocs publication ownership; native pack bytes belong to their author.

Python is required by MkDocs. This adapter only identifies files: Framework's
native learning service remains responsible for accepting and reading a pack.
"""
import json
from pathlib import Path, PurePosixPath


def native_pack_resources(site):
    """Return immutable payload identities, refusing ambiguous local paths first."""
    site = Path(site).resolve()
    resources = set()
    for manifest in sorted(site.rglob('learning-pack.json')):
        if manifest.is_symlink() or not manifest.resolve().is_relative_to(site):
            raise ValueError('Linked native learning manifest: ' + str(manifest))
        metadata = json.loads(manifest.read_text(encoding='utf-8'))
        if not isinstance(metadata, dict):
            raise ValueError('Native learning manifest must be an object: ' + str(manifest))
        if metadata.get('schema') != 'umicom.learning.pack':
            continue
        entries = metadata.get('resources')
        if not isinstance(entries, list):
            raise ValueError('Native learning resources must be a list: ' + str(manifest))
        pack = manifest.parent.resolve()
        for entry in entries:
            relative = entry.get('path') if isinstance(entry, dict) else None
            if not isinstance(relative, str) or not relative or '\x00' in relative:
                raise ValueError('Native learning resource needs a nonempty path')
            # The manifest uses portable forward-slash paths. Reject drive names,
            # alternate separators and parent traversal before platform resolution.
            parts = relative.split('/')
            if ('\\' in relative or ':' in relative or PurePosixPath(relative).is_absolute()
                    or any(part in ('', '.', '..') for part in parts)):
                raise ValueError('Native learning resource escapes or ambiguously names its pack')
            target = pack.joinpath(*parts)
            cursor = pack
            for part in parts:
                cursor = cursor / part
                if cursor.is_symlink():
                    raise ValueError('Linked native learning resource: ' + str(target))
            target = target.resolve()
            if not target.is_relative_to(pack):
                raise ValueError('Native learning resource escapes its pack')
            if not target.is_file():
                raise ValueError('Missing native learning resource: ' + str(target))
            resources.add(target)
    return resources
