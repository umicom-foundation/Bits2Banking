#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/test_studio_learning_pack.py
#
# PURPOSE:
#   Check portable native-pack publication and refusal without overwriting work.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#---------------------------------------------------------------------------
import importlib.util
import hashlib
import json
from pathlib import Path
import pytest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("prepare_studio_learning_pack", ROOT / "tools/prepare_studio_learning_pack.py")
pack = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(pack)


@pytest.fixture
def collection(tmp_path):
    (tmp_path / "guide.html").write_bytes(b"<h1>Read before running</h1>\n")
    metadata = {
        "schema": "bits2banking.learning.collection", "version": 1,
        "id": "example.course", "title": "Learning", "product": "bits2banking",
        "locale": "en", "revision": 1,
        "compatibility": {"minimum": [0, 9, 0], "maximum": [0, 9, 0]},
        "resources": [{"id": "intro", "title": "Introduction", "topic": "learning",
                       "kind": "guide", "path": "guide.html"}],
    }
    def save():
        (tmp_path / "collection.json").write_text(json.dumps(metadata), encoding="utf-8")
    save()
    return tmp_path, metadata, save


def test_native_schema_and_exact_hash(collection):
    root, _, _ = collection
    published = json.loads(pack.render_manifest(root))
    assert published["schema"] == "umicom.learning.pack"
    assert published["resources"][0]["sha256"] == hashlib.sha256((root / "guide.html").read_bytes()).hexdigest()
    assert published["compatibility"] == {"minimum": [0, 9, 0], "maximum": [0, 9, 0]}


def test_changed_lesson_requires_explicit_publication(collection):
    root, _, _ = collection
    assert pack.publish(root, write=True)
    original = (root / "learning-pack.json").read_bytes()
    (root / "guide.html").write_bytes(b"<h1>Changed</h1>\r\n")
    with pytest.raises(pack.PackError, match="stale"):
        pack.publish(root)
    assert (root / "learning-pack.json").read_bytes() == original
    assert pack.publish(root, write=True)
    assert not pack.publish(root)


@pytest.mark.parametrize("name", ["../outside.html", "/absolute", "a//b", "a/./b", "C:/file", "CON.txt", "a\\b", ".git/config"])
def test_unsafe_resource_paths(collection, name):
    root, metadata, save = collection
    metadata["resources"][0]["path"] = name
    save()
    with pytest.raises(pack.PackError):
        pack.render_manifest(root)


def test_duplicate_id_and_case_alias(collection):
    root, metadata, save = collection
    metadata["resources"].append(dict(metadata["resources"][0]))
    save()
    with pytest.raises(pack.PackError, match="Duplicate"):
        pack.render_manifest(root)
    metadata["resources"][1]["id"] = "other"
    metadata["resources"][1]["path"] = "GUIDE.HTML"
    save()
    with pytest.raises(pack.PackError, match="Duplicate"):
        pack.render_manifest(root)


def test_missing_resource_keeps_previous_manifest(collection):
    root, _, _ = collection
    pack.publish(root, write=True)
    original = (root / "learning-pack.json").read_bytes()
    (root / "guide.html").unlink()
    with pytest.raises(OSError):
        pack.publish(root, write=True)
    assert (root / "learning-pack.json").read_bytes() == original


def test_byte_bound_and_utf8_capacity(collection):
    root, metadata, save = collection
    metadata["title"] = "é" * 128
    save()
    with pytest.raises(pack.PackError, match="capacity"):
        pack.render_manifest(root)
    metadata["title"] = "Learning"
    save()
    (root / "guide.html").write_bytes(b"x" * (pack.MAX_RESOURCE_BYTES + 1))
    with pytest.raises(pack.PackError, match="byte limit"):
        pack.render_manifest(root)


@pytest.mark.parametrize("resources", [[], [None] * 257])
def test_resource_count_bounds(collection, resources):
    root, metadata, save = collection
    metadata["resources"] = resources
    save()
    with pytest.raises(pack.PackError, match="1 to 256"):
        pack.render_manifest(root)


def test_duplicate_json_key_is_not_silently_accepted(collection):
    root, _, _ = collection
    (root / "collection.json").write_text('{"schema":1,"schema":2}', encoding="utf-8")
    with pytest.raises(pack.PackError, match="Duplicate JSON"):
        pack.render_manifest(root)


def test_links_are_not_followed(collection):
    root, metadata, save = collection
    linked = root / "linked.html"
    try:
        linked.symlink_to(root / "guide.html")
    except OSError as error:
        pytest.skip(f"Host cannot create symlinks: {error}")
    metadata["resources"][0]["path"] = linked.name
    save()
    with pytest.raises(pack.PackError, match="Linked"):
        pack.render_manifest(root)


def test_failed_replace_keeps_old_manifest_and_cleans_temporary(collection, monkeypatch):
    root, _, _ = collection
    pack.publish(root, write=True)
    original = (root / "learning-pack.json").read_bytes()
    (root / "guide.html").write_bytes(b"<h1>Another edition</h1>\n")
    def refuse(*_):
        raise OSError("simulated write refusal")
    monkeypatch.setattr(pack.os, "replace", refuse)
    with pytest.raises(OSError):
        pack.publish(root, write=True)
    assert (root / "learning-pack.json").read_bytes() == original
    assert list(root.glob(".learning-pack-*.tmp")) == []


def test_published_course_collection_is_current():
    root = ROOT / "content/courses/framework-and-finance"
    assert pack.render_manifest(root) == (root / "learning-pack.json").read_bytes()


def test_course_links_resolve_to_declared_resources():
    from html.parser import HTMLParser
    import posixpath
    from urllib.parse import urlsplit

    class Links(HTMLParser):
        def __init__(self):
            super().__init__()
            self.links, self.anchors = [], set()

        def handle_starttag(self, tag, attributes):
            attrs = dict(attributes)
            if "id" in attrs:
                self.anchors.add(attrs["id"])
            if tag == "a" and "href" in attrs:
                self.links.append(attrs["href"])

    root = ROOT / "content/courses/framework-and-finance"
    metadata = json.loads((root / "learning-pack.json").read_text(encoding="utf-8"))
    pages = {}
    for resource in metadata["resources"]:
        parser = Links()
        parser.feed((root / resource["path"]).read_text(encoding="utf-8"))
        pages[resource["path"]] = parser
    for current, page in pages.items():
        for href in page.links:
            link = urlsplit(href)
            assert not link.scheme and not link.netloc and not link.query
            target = posixpath.normpath(posixpath.join(posixpath.dirname(current), link.path)) if link.path else current
            assert target in pages, (current, href, target)
            if link.fragment:
                assert link.fragment in pages[target].anchors, (current, href)
