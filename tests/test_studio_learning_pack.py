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


# Checked-in catalogues bypass the collection publisher, so they need their
# own native-capacity guard. Keep the reader's bounds instead of enlarging
# them to admit an ever-growing combined HTML/Markdown curriculum.
@pytest.mark.parametrize("manifest", sorted((ROOT / "learning-packs").glob("*.json")),
                         ids=lambda path: path.stem)
def test_checked_in_pack_obeys_native_capacity(manifest):
    data = manifest.read_bytes()
    value = json.loads(data.decode("utf-8"), object_pairs_hook=pack.unique_object)
    assert value["schema"] == "umicom.learning.pack"
    assert len(data) <= pack.MAX_MANIFEST_BYTES
    assert 1 <= len(value["resources"]) <= 256
    ids = [row["id"] for row in value["resources"]]
    paths = [row["path"].casefold() for row in value["resources"]]
    assert len(ids) == len(set(ids))
    assert len(paths) == len(set(paths))


@pytest.mark.parametrize("slug", ["umicom-development", "llm-from-scratch"])
def test_split_course_preserves_html_and_manuscript_coverage(slug):
    course_path = ROOT / "content" / "courses" / slug
    course = json.loads((course_path / "course.json").read_text(encoding="utf-8"))
    primary = json.loads((ROOT / "learning-packs" / (slug + ".json")).read_text(encoding="utf-8"))
    companion = json.loads((ROOT / "learning-packs" / (slug + "-manuscripts.json")).read_text(encoding="utf-8"))
    assert primary["id"] != companion["id"]
    primary_paths = {row["path"] for row in primary["resources"]}
    companion_paths = {row["path"] for row in companion["resources"]}
    for lesson in course["lessons"]:
        html = (course_path / lesson["path"]).resolve().relative_to(ROOT).as_posix()
        manuscript = (course_path / lesson["manuscript"]).resolve().relative_to(ROOT).as_posix()
        assert html in primary_paths, html
        assert manuscript in companion_paths, manuscript
    # Relocation between packs must never relax content identity checks.
    for catalogue in (primary, companion):
        for resource in catalogue["resources"]:
            source = pack.plain_path(ROOT, resource["path"])
            assert hashlib.sha256(source.read_bytes()).hexdigest() == resource["sha256"]


def test_checked_in_pack_identities_are_unique():
    manifests = sorted((ROOT / "learning-packs").glob("*.json"))
    identities = [json.loads(path.read_text(encoding="utf-8"))["id"] for path in manifests]
    assert len(identities) == len(set(identities))


def _course_lesson_count(manifest_name):
    slug = manifest_name.removesuffix(".json").removesuffix("-manuscripts")
    course = ("framework-and-finance/" + slug.removeprefix("framework-and-finance-")
              if slug.startswith("framework-and-finance-") else slug)
    value = json.loads((ROOT / "content/courses" / course / "course.json").read_text(encoding="utf-8"))
    return len(value["lessons"])


def test_offline_html_catalogue_uses_current_lesson_counts():
    from html.parser import HTMLParser

    class Rows(HTMLParser):
        def __init__(self):
            super().__init__()
            self.rows, self.row, self.cell = [], None, None
            self.inert = 0

        def handle_starttag(self, tag, attrs):
            if tag == "template":
                self.inert += 1
            if self.inert:
                return
            if tag == "tr":
                self.row = []
            elif tag == "td" and self.row is not None:
                self.cell = ""

        def handle_data(self, data):
            if not self.inert and self.cell is not None:
                self.cell += data

        def handle_endtag(self, tag):
            if tag == "template" and self.inert:
                self.inert -= 1
                return
            if self.inert:
                return
            if tag == "td" and self.row is not None and self.cell is not None:
                self.row.append(self.cell.strip())
                self.cell = None
            elif tag == "tr" and self.row is not None:
                self.rows.append(self.row)
                self.row = None

    parser = Rows()
    parser.feed((ROOT / "learning-packs/index.html").read_text(encoding="utf-8"))
    listed = set()
    for row in parser.rows:
        if len(row) == 3 and row[1].startswith("learning-packs/"):
            name = row[1].removeprefix("learning-packs/")
            assert int(row[2]) == _course_lesson_count(name), row
            listed.add(name)
    assert listed == {p.name for p in (ROOT / "learning-packs").glob("*.json")}


def test_offline_markdown_catalogue_remains_one_current_table():
    import re
    text = (ROOT / "learning-packs/README.md").read_text(encoding="utf-8")
    # Retained historical rows must stay outside the active Markdown table:
    # a comment or blank line between rows terminates the table in Markdown.
    active = re.sub(r"<!--[\s\S]*?-->", "", text)
    start = active.index("| Course | Manifest path | Lessons |")
    end = active.index("## Keep native packs stable", start)
    lines = active[start:end].strip().splitlines()
    assert all(line.startswith("|") for line in lines)
    rows = re.findall(r"^\|[^\n]*?\x60learning-packs/([^\x60]+)\x60\s*\|\s*(\d+)\s*\|$", active, re.M)
    assert {name for name, _ in rows} == {p.name for p in (ROOT / "learning-packs").glob("*.json")}
    for name, count in rows:
        assert int(count) == _course_lesson_count(name), name

@pytest.mark.parametrize("manifest", sorted((ROOT / "learning-packs").glob("*.json")),
                         ids=lambda path: path.stem)
def test_every_checked_in_pack_resource_matches_source_bytes(manifest):
    """Every edition binds exact bytes, including ordinary manuscript packs.

    The split-course checks above verify discovery for those specific courses.
    This independent content check covers the complete catalogue so a navigation
    edit cannot silently leave another course with stale offline checksums.
    """
    value = json.loads(manifest.read_text(encoding="utf-8"),
                       object_pairs_hook=pack.unique_object)
    for resource in value["resources"]:
        source = pack.plain_path(ROOT, resource["path"])
        actual = hashlib.sha256(source.read_bytes()).hexdigest()
        assert actual == resource["sha256"], (
            str(manifest.relative_to(ROOT)) + ": " + resource["path"])

