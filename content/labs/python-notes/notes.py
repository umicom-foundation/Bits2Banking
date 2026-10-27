#-----------------------------------------------------------------------------
# Bits2Banking
# File: content/labs/python-notes/notes.py
#
# PURPOSE:
#   Teach note persistence with bounded input and explicit record validation.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
import json
from pathlib import Path

DATA_FILE = Path("notes.json")



# These bounds make file and identifier expectations visible to learners.
MAX_FILE_BYTES = 256 * 1024
MAX_NOTES = 1000
MAX_NOTE_CHARACTERS = 1000
MAX_NOTE_ID = (1 << 63) - 1


def validate_notes(value):
    """Validate known fields without dropping extra fields from older records."""
    if not isinstance(value, list) or len(value) > MAX_NOTES:
        raise ValueError("Notes must be a list within the note-count limit")
    identifiers = set()
    for note in value:
        if not isinstance(note, dict):
            raise ValueError("Each note must be an object")
        identifier = note.get("id")
        text = note.get("text")
        # bool is a subclass of int in Python; it is not an acceptable note id.
        if type(identifier) is not int or not 1 <= identifier <= MAX_NOTE_ID:
            raise ValueError("A note id must be a positive bounded integer")
        if identifier in identifiers:
            raise ValueError("Note ids must be unique")
        if not isinstance(text, str) or not text.strip() or len(text) > MAX_NOTE_CHARACTERS:
            raise ValueError("A note must contain text within the character limit")
        identifiers.add(identifier)
    return value


# The original loader is retained for review. JSON parsing alone did not prove
# that the result was a list of usable notes. The active loader below bounds
# input before parsing and validates the fields consumed by add_note.
if False:
    def load_notes():
        if not DATA_FILE.exists():
            return []
        return json.loads(DATA_FILE.read_text(encoding="utf-8"))


def load_notes():
    try:
        with DATA_FILE.open("rb") as source:
            data = source.read(MAX_FILE_BYTES + 1)
    except FileNotFoundError:
        return []
    if len(data) > MAX_FILE_BYTES:
        raise ValueError("The notes file exceeds the byte limit")
    try:
        value = json.loads(data.decode("utf-8"))
    except RecursionError as error:
        raise ValueError("The notes file is nested too deeply") from error
    return validate_notes(value)


def save_notes(notes):
    # Reject malformed records before opening the existing file for writing.
    # This remains a single-writer teaching lab, not an atomic database.
    validate_notes(notes)
    text = json.dumps(notes, indent=2, ensure_ascii=False)
    if len((text + "\n").encode("utf-8")) > MAX_FILE_BYTES:
        raise ValueError("The serialized notes exceed the byte limit")
    DATA_FILE.write_text(text + "\n", encoding="utf-8")


def add_note(text):
    if not isinstance(text, str) or len(text) > MAX_NOTE_CHARACTERS:
        raise ValueError("A note must be text within the character limit")
    text = text.strip()
    if not text:
        raise ValueError("A note cannot be empty")

    notes = load_notes()
    if len(notes) >= MAX_NOTES:
        raise ValueError("The note-count limit has been reached")
    next_id = max((note["id"] for note in notes), default=0) + 1
    if next_id > MAX_NOTE_ID:
        raise ValueError("The note identifier limit has been reached")
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
