import tempfile
import unittest
from pathlib import Path

import notes


class NotesTests(unittest.TestCase):
    def test_empty_note_is_rejected(self):
        with self.assertRaises(ValueError):
            notes.add_note("   ")

    def test_note_is_saved(self):
        with tempfile.TemporaryDirectory() as folder:
            original_file = notes.DATA_FILE
            try:
                notes.DATA_FILE = Path(folder) / "notes.json"
                saved_id = notes.add_note("Write project notes")
                self.assertEqual(saved_id, 1)
                self.assertEqual(notes.load_notes()[0]["text"], "Write project notes")
            finally:
                notes.DATA_FILE = original_file


if __name__ == "__main__":
    unittest.main()
