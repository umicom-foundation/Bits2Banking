"""Test the public site compositor with disposable BookForge and MkDocs outputs."""
from pathlib import Path
import importlib.util
import tempfile
import unittest

SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "publish_learning_portal.py"
SPEC = importlib.util.spec_from_file_location("publish_learning_portal", SCRIPT)
assert SPEC and SPEC.loader
portal = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(portal)


class LearningPortalTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        (self.root / "mkdocs.yml").write_text("site_name: Test\n", encoding="utf-8")
        (self.root / "site").mkdir()
        (self.root / "site" / "index.html").write_text("Study here", encoding="utf-8")
        (self.root / "output" / "site" / "vintage").mkdir(parents=True)
        (self.root / "output" / "site" / "index.html").write_text(
            '<a href="vintage/index.html">Past volumes</a>', encoding="utf-8")
        (self.root / "output" / "site" / "vintage" / "index.html").write_text(
            "Original book home", encoding="utf-8")
        (self.root / "output" / "vintage" / "books").mkdir(parents=True)
        (self.root / "output" / "vintage" / "books" / "book.pdf").write_bytes(b"PDF-fixture")

    def test_assemble_preserves_mkdocs_and_legacy_content(self):
        portal.assemble(self.root)
        portal.verify(self.root)
        self.assertEqual((self.root / "site" / "index.html").read_text(), "Study here")
        self.assertEqual((self.root / "site/archive/books/vintage/index.html").read_text(),
                         "Original book home")
        self.assertEqual((self.root / "site/archive/books/downloads/vintage/book.pdf").read_bytes(),
                         b"PDF-fixture")

    def test_second_assembly_requires_explicit_refresh(self):
        portal.assemble(self.root)
        with self.assertRaises(ValueError):
            portal.assemble(self.root)
        (self.root / "output/site/index.html").write_text("Updated catalogue", encoding="utf-8")
        portal.assemble(self.root, refresh=True)
        self.assertEqual((self.root / "site/archive/books/index.html").read_text(),
                         "Updated catalogue")

    def test_missing_source_rejected(self):
        (self.root / "output/site/index.html").unlink()
        with self.assertRaises(ValueError):
            portal.assemble(self.root)

    def test_verify_detects_missing_archived_book(self):
        portal.assemble(self.root)
        (self.root / "site/archive/books/index.html").unlink()
        with self.assertRaises(ValueError):
            portal.verify(self.root)

    def test_symlinked_input_rejected_when_supported(self):
        target = self.root / "outside.md"
        target.write_text("Outside", encoding="utf-8")
        link = self.root / "output/site/linked.md"
        try:
            link.symlink_to(target)
        except (OSError, NotImplementedError):
            self.skipTest("Creating symbolic links is unavailable")
        with self.assertRaises(ValueError):
            portal.assemble(self.root)


if __name__ == "__main__":
    unittest.main()
