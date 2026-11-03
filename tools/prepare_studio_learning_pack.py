#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tools/prepare_studio_learning_pack.py
#
# PURPOSE:
#   Publish reviewed course files as a bounded Framework learning-pack manifest.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#---------------------------------------------------------------------------
"""Course publishing only; native admission, reading and progress stay in Framework."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import stat
import sys
import tempfile

MAX_RESOURCE_BYTES = 1024 * 1024
MAX_MANIFEST_BYTES = 256 * 1024
IDENTIFIER = re.compile(r"[A-Za-z0-9][A-Za-z0-9_.-]*\Z")
PORTABLE_PART = re.compile(r"[A-Za-z0-9][A-Za-z0-9_.-]*\Z")
RESERVED = {"CON", "PRN", "AUX", "NUL", "CONIN$", "CONOUT$"}
RESERVED.update(f"{prefix}{number}" for prefix in ("COM", "LPT") for number in range(1, 10))


class PackError(ValueError):
    """A collection cannot be published without changing its reviewed inputs."""


def unique_object(pairs):
    result = {}
    for key, value in pairs:
        if key in result:
            raise PackError(f"Duplicate JSON member: {key}")
        result[key] = value
    return result


def fields(value, expected, label):
    if not isinstance(value, dict) or set(value) != set(expected):
        raise PackError(f"{label}: expected fields {', '.join(expected)}")


def text(value, capacity, label, identifier=False):
    if not isinstance(value, str) or not value.strip():
        raise PackError(f"{label}: nonempty text required")
    if len(value.encode("utf-8")) >= capacity or any(ord(c) < 32 or ord(c) == 127 for c in value):
        raise PackError(f"{label}: text exceeds the native capacity or contains controls")
    if identifier and not IDENTIFIER.fullmatch(value):
        raise PackError(f"{label}: invalid identifier")
    return value


def plain_path(root, relative):
    """Admit a conservative portable subset; never follow links or junctions."""
    text(relative, 512, "resource path")
    parts = relative.split("/")
    if any(not PORTABLE_PART.fullmatch(p) or p.endswith(".") or
           p.split(".")[0].upper() in RESERVED for p in parts):
        raise PackError(f"Non-portable resource path: {relative}")
    candidate = root
    for part in parts:
        candidate /= part
        info = candidate.lstat()
        if stat.S_ISLNK(info.st_mode) or (
            getattr(info, "st_file_attributes", 0) &
            getattr(stat, "FILE_ATTRIBUTE_REPARSE_POINT", 0x400)
        ):
            raise PackError(f"Linked resource is not admitted: {relative}")
    if not candidate.is_file():
        raise PackError(f"Resource is not a regular file: {relative}")
    return candidate


def root_path(directory):
    root = Path(os.path.abspath(directory))
    # Resolve neither the root nor a parent through a junction. The publisher
    # is an authoring tool for an owner-controlled tree, not an untrusted server.
    for candidate in (root, *root.parents):
        info = candidate.lstat()
        if stat.S_ISLNK(info.st_mode) or (
            getattr(info, "st_file_attributes", 0) &
            getattr(stat, "FILE_ATTRIBUTE_REPARSE_POINT", 0x400)
        ):
            raise PackError("The collection root must not pass through a linked directory")
    if not root.is_dir():
        raise PackError("The collection root must be a directory")
    return root


def bounded_bytes(file, limit):
    with file.open("rb") as stream:
        data = stream.read(limit + 1)
    if len(data) > limit:
        raise PackError(f"{file.name}: exceeds the byte limit")
    return data


def render_manifest(directory):
    root = root_path(directory)
    collection = json.loads(
        bounded_bytes(plain_path(root, "collection.json"), MAX_MANIFEST_BYTES).decode("utf-8"),
        object_pairs_hook=unique_object,
    )
    fields(collection, ("schema", "version", "id", "title", "product", "locale",
                        "revision", "compatibility", "resources"), "collection")
    if collection["schema"] != "bits2banking.learning.collection" or type(collection["version"]) is not int or collection["version"] != 1:
        raise PackError("Unsupported collection schema")
    result = {"schema": "umicom.learning.pack", "version": 1}
    for key, capacity in (("id", 96), ("title", 256), ("product", 96), ("locale", 32)):
        result[key] = text(collection[key], capacity, key, key in ("id", "product"))
    if not re.fullmatch(r"[A-Za-z0-9]+(?:-[A-Za-z0-9]+)*", result["locale"]):
        raise PackError("Invalid locale")
    revision = collection["revision"]
    if type(revision) is not int or not 1 <= revision <= (1 << 63) - 1:
        raise PackError("Revision must be a positive signed 64-bit integer")
    result["revision"] = revision
    compatibility = collection["compatibility"]
    fields(compatibility, ("minimum", "maximum"), "compatibility")
    for version in compatibility.values():
        if not isinstance(version, list) or len(version) != 3 or any(
            type(part) is not int or not 0 <= part <= 65535 for part in version
        ):
            raise PackError("Compatibility versions require three unsigned 16-bit integers")
    if compatibility["minimum"] > compatibility["maximum"]:
        raise PackError("Compatibility range is reversed")
    result["compatibility"] = compatibility
    resources = collection["resources"]
    if not isinstance(resources, list) or not 1 <= len(resources) <= 256:
        raise PackError("A native learning pack requires 1 to 256 resources")
    ids, paths, published = set(), set(), []
    for item in resources:
        fields(item, ("id", "title", "topic", "kind", "path"), "resource")
        row = {}
        for key, capacity in (("id", 96), ("title", 256), ("topic", 96), ("path", 512)):
            row[key] = text(item[key], capacity, key, key in ("id", "topic"))
        if item["kind"] not in ("guide", "lesson", "example", "image"):
            raise PackError("Invalid resource kind")
        row["kind"] = item["kind"]
        if row["id"] in ids or row["path"].casefold() in paths:
            raise PackError("Duplicate resource identity or portable path")
        ids.add(row["id"])
        paths.add(row["path"].casefold())
        data = bounded_bytes(plain_path(root, row["path"]), MAX_RESOURCE_BYTES)
        row["sha256"] = hashlib.sha256(data).hexdigest()
        published.append(row)
    result["resources"] = published
    encoded = (json.dumps(result, ensure_ascii=False, indent=2) + "\n").encode("utf-8")
    if len(encoded) > MAX_MANIFEST_BYTES:
        raise PackError("Manifest exceeds the native byte limit")
    return encoded


def publish(directory, write=False):
    root = root_path(directory)
    data = render_manifest(root)
    destination = root / "learning-pack.json"
    # Refuse a linked destination even in check mode. The default only compares;
    # reviewed content is published solely when the maintainer supplies --write.
    if destination.exists() or destination.is_symlink():
        plain_path(root, "learning-pack.json")
        if bounded_bytes(destination, MAX_MANIFEST_BYTES) == data:
            return False
    if not write:
        raise PackError("Manifest is missing or stale; review the content, then use --write")
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(dir=root, prefix=".learning-pack-", suffix=".tmp", delete=False) as stream:
            temporary = Path(stream.name)
            stream.write(data)
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary, destination)
        temporary = None
    finally:
        if temporary is not None:
            temporary.unlink()
    return True


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("collection", type=Path, help="Folder containing collection.json")
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--write", action="store_true", help="Publish reviewed resource hashes")
    mode.add_argument("--check", action="store_true", help="Compare only (the default)")
    args = parser.parse_args()
    try:
        changed = publish(args.collection, args.write)
    except (PackError, OSError, UnicodeError, ValueError) as error:
        print(f"Learning pack: {error}", file=sys.stderr)
        return 1
    print("Published learning-pack.json." if changed else "Learning pack matches the declared file bytes.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
