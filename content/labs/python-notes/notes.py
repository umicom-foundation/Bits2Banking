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
