#-----------------------------------------------------------------------------
# Bits2Banking
# File: content/labs/python-notes/test_note_validation.py
#
# PURPOSE:
#   Check malformed note files and rejected saves preserve existing content.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
import json
import tempfile
import unittest
from pathlib import Path

import notes


class NoteValidationTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.original = notes.DATA_FILE
        notes.DATA_FILE = Path(self.directory.name) / "notes.json"

    def tearDown(self):
        notes.DATA_FILE = self.original
        self.directory.cleanup()

    def write_value(self, value):
        notes.DATA_FILE.write_text(json.dumps(value), encoding="utf-8")

    def test_wrong_shapes_are_rejected(self):
        for value in (42, None, {}, "notes", [None], [{"text": "Read"}],
                      [{"id": True, "text": "Read"}], [{"id": "1", "text": "Read"}],
                      [{"id": 0, "text": "Read"}], [{"id": 1, "text": []}],
                      [{"id": 1, "text": "   "}]):
            with self.subTest(value=value):
                self.write_value(value)
                before = notes.DATA_FILE.read_bytes()
                with self.assertRaises(ValueError):
                    notes.add_note("New note")
                self.assertEqual(notes.DATA_FILE.read_bytes(), before)

    def test_duplicate_ids_are_rejected(self):
        self.write_value([{"id": 1, "text": "First"}, {"id": 1, "text": "Second"}])
        with self.assertRaises(ValueError):
            notes.load_notes()

    def test_invalid_utf8_and_json_are_rejected(self):
        for content in (b"\xff", b"{", b"[" * 2000):
            with self.subTest(content=content[:4]):
                notes.DATA_FILE.write_bytes(content)
                with self.assertRaises(ValueError):
                    notes.load_notes()

    def test_byte_limit_is_checked_before_parsing(self):
        notes.DATA_FILE.write_bytes(b" " * (notes.MAX_FILE_BYTES + 1))
        with self.assertRaises(ValueError):
            notes.load_notes()

    def test_rejected_save_preserves_existing_file(self):
        original = b"[]\n"
        notes.DATA_FILE.write_bytes(original)
        with self.assertRaises(ValueError):
            notes.save_notes([{"id": 1, "text": ""}])
        self.assertEqual(notes.DATA_FILE.read_bytes(), original)

    def test_extra_fields_survive_a_valid_update(self):
        self.write_value([{"id": 7, "text": "Read", "topic": "Kernel"}])
        self.assertEqual(notes.add_note("Practise"), 8)
        loaded = notes.load_notes()
        self.assertEqual(loaded[0]["topic"], "Kernel")
        self.assertEqual(loaded[1], {"id": 8, "text": "Practise"})

    def test_identifier_exhaustion_does_not_write(self):
        self.write_value([{"id": notes.MAX_NOTE_ID, "text": "Last id"}])
        before = notes.DATA_FILE.read_bytes()
        with self.assertRaises(ValueError):
            notes.add_note("Next")
        self.assertEqual(notes.DATA_FILE.read_bytes(), before)

    def test_count_and_text_limits(self):
        with self.assertRaises(ValueError):
            notes.validate_notes([{}] * (notes.MAX_NOTES + 1))
        for value in (None, 7, "x" * (notes.MAX_NOTE_CHARACTERS + 1)):
            with self.subTest(value=type(value).__name__):
                with self.assertRaises(ValueError):
                    notes.add_note(value)
        self.assertFalse(notes.DATA_FILE.exists())


if __name__ == "__main__":
    unittest.main()
