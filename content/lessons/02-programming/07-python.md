# 7. Python: build a note-taking program

So far, PowerShell and Bash have helped us create files and inspect the computer. Python lets us express a larger set of rules in a readable program. We will build a command-line note collection that keeps its information in a JSON file.

**JSON** (JavaScript Object Notation) is a text format for data. It represents structures such as arrays and objects in a way that many languages can read. A note will contain an identifier and its text.

## Prepare Python and your project

Check that Python is available:

```powershell
python --version
```

In PowerShell, make a folder for this exercise:

```powershell
New-Item -ItemType Directory -Force -Path "$HOME\UmicomLearning\python-notes" | Out-Null
Set-Location "$HOME\UmicomLearning\python-notes"
```

Open this folder in a text editor. Create a file named **`notes.py`** containing the complete program below:

```python
import json
from pathlib import Path

DATA_FILE = Path("notes.json")


def load_notes():
    if not DATA_FILE.exists():
        return []
    return json.loads(DATA_FILE.read_text(encoding="utf-8"))


def save_notes(notes):
    text = json.dumps(notes, indent=2, ensure_ascii=False)
    DATA_FILE.write_text(text + "\n", encoding="utf-8")


def add_note(text):
    text = text.strip()
    if not text:
        raise ValueError("A note cannot be empty")

    notes = load_notes()
    next_id = max((note["id"] for note in notes), default=0) + 1
    notes.append({"id": next_id, "text": text})
    save_notes(notes)
    return next_id


def show_notes():
    for note in load_notes():
        print(f'{note["id"]}: {note["text"]}')


if __name__ == "__main__":
    new_text = input("Write a note: ")
    try:
        note_id = add_note(new_text)
        print(f"Saved note {note_id}")
        show_notes()
    except (OSError, ValueError, json.JSONDecodeError) as error:
        print(f"Unable to save note: {error}")
```

## Run the program

```powershell
python .\notes.py
```

When prompted, enter `Review Umicom Studio commands`. The result should include:

```text
Saved note 1
1: Review Umicom Studio commands
```

Run the program a second time and enter another note. Both should appear: they have been saved in `notes.json`, so they survive after Python exits.

## Read the important parts

`import` loads a library. `Path` represents a file location. The `load_notes` **function** reads data, while `save_notes` writes it. `[]` is an empty **list** and `{...}` creates a **dictionary** containing keys such as `id` and `text`. The `for` loop examines each saved note.

`text.strip()` removes leading and trailing whitespace. `if not text` rejects an empty note. `raise ValueError` signals that the input does not meet the application's rule. The `try`/`except` statement prevents an expected input or file error from producing an unexplained traceback to the learner.

`max(..., default=0) + 1` chooses a new number greater than the largest stored identifier. This is suitable for a small single-user demonstration; a concurrent application requires a stronger mechanism to avoid duplicate identifiers.

## Test the behaviour

Create **`test_notes.py`** in the same folder:

```python
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
```

Run the tests without needing an external package:

```powershell
python -m unittest -v
```

The test uses a temporary directory so it does not overwrite your real notes. Both tests should pass. A **unit test** checks one small behaviour: here, rejecting an empty note or saving a valid one.

## Improve it

Add a function that marks a note as completed. Think about the rules first: the note must exist, and other notes must stay unchanged. This is the foundation of the Kanban board we build later.

The sample JSON file is not a multi-user database. We will return to storage, concurrent updates and reliable transactions in the database chapter.

**Next:** [See how Assembly relates to your code](../03-native-code/08-assembly.md).
