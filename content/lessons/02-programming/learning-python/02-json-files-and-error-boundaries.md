# JSON files and error boundaries

A file can outlive a running program. Loading it means accepting bytes from outside the current function, so successful parsing is only the first check.

## 1. Follow the existing path

In [the note lab](../../../labs/python-notes/notes.py), `DATA_FILE = Path("notes.json")` names a relative path. It refers to the current working directory, not automatically the directory containing notes.py. A missing file returns an empty list. An existing file is read as UTF-8, a common way to encode text characters as bytes.

 ```text
return json.loads(DATA_FILE.read_text(encoding="utf-8"))
``` 

```text
with DATA_FILE.open("rb") as source:
    data = source.read(MAX_FILE_BYTES + 1)
if len(data) > MAX_FILE_BYTES:
    raise ValueError("The notes file exceeds the byte limit")
```


The active loader reads bytes first. It asks for one byte beyond the limit so it can detect an oversized file without reading all of it. It then decodes UTF-8, parses JSON and calls `validate_notes`.


Read from the inside outward: read text, then interpret JSON text as values. JSON is a text format for lists, objects, numbers and other simple values. Valid JSON `[]` is an empty list. Valid JSON `42` is a number. Both parse, but only the list has the shape this program expects.

 <svg viewbox="0 0 700 110" role="img" aria-label="Parsing and checking application-specific structure are separate responsibilities." style="width:100%;max-width:700px"><title>Parsing and checking application-specific structure are separate responsibilities.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">file bytes</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">JSON parsing</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">shape validation</text></svg>

Parsing and checking application-specific structure are separate responsibilities. 

## 2. Understand serialization


```text
text = json.dumps(notes, indent=2, ensure_ascii=False)
DATA_FILE.write_text(text + "\n", encoding="utf-8")
```


`dumps` converts values to JSON text. Two-space indentation makes the file easier to read. `ensure_ascii=False` lets non-ASCII characters appear directly in that text; UTF-8 then encodes them for storage. The final newline is useful for text tools. `write_text` replaces the file content, so a failed or interrupted write is not automatically a safe transaction.

 

## 3. Identify the error boundary


The main block catches OSError, ValueError and JSONDecodeError and prints a message. OSError includes many file failures. JSONDecodeError means text could not be parsed as JSON; it is a kind of ValueError. A `try` block marks work whose exceptions the following `except` can handle.

 The current lab does not validate the complete loaded shape, bound the input size, coordinate writers or save through atomic replacement. A valid JSON number, a missing id or an id with the wrong type can fail outside the intended happy path. Treat those as limitations to investigate, not as proof the lab safely accepts arbitrary files. 

The active lab now requires a list of at most 1000 records. Each known record needs a unique integer id from 1 to 263−1 and nonempty text of at most 1000 characters. A boolean is refused as an id even though Python treats bool as a kind of integer. Extra fields survive a valid update. Input files and serialized output are limited to 256 KiB. Deep nesting is reported as a validation error.


The lab remains single-writer and does not save through atomic replacement or guarantee power-loss durability. Its tests are source coverage to run in a prepared environment, not a claim that every runtime has already passed. The earlier unchecked loader remains inactive in the source for comparison.

 

## 4. Design the checks before writing them


```text
READ a bounded text file
PARSE JSON
REQUIRE a list
FOR EACH item: require an object, an integer id and text
REQUIRE unique positive ids
ONLY THEN add and save a new note
```

 This is pseudocode: a description of decisions, not runnable Python. It separates validation from changing persistent data. In Umicom Framework, inspect document and record persistence services for the same separation; the language differs but the ownership problem remains. 

This is pseudocode: a description of decisions, not runnable Python. Find the matching checks in `validate_notes` and `load_notes`. Validation finishes before an existing file is opened for saving. In Umicom Framework, inspect document and record persistence services for the same separation; the language differs but the ownership problem remains.


Read [the regression source](../../../labs/python-notes/test_note_validation.py) for invalid JSON shapes, duplicate ids, byte limits and preservation of the old file after rejection. Optional check from the lab directory: `python -m unittest discover -v`. A failed assertion is evidence to investigate; source reading alone is not a test run.

 

## 5. Exercise with expected results


Classify three files: `[]`, `{}` and `[{"id":1,"text":"Read a guide"}]`. All are valid JSON. The first and third have the intended list shape; the second does not. Even the third still needs its id and text fields checked. Never equate “valid JSON” with “valid note database”. Work on a copy containing invented notes if you later run the lab.

---

[Read this lesson in HTML](../../../courses/learning-python/lessons/02-json-files-and-error-boundaries.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: Validate records before saving](03-validate-records-before-saving.md)

[Previous: Names, lists and note functions](01-names-lists-and-note-functions.md)
