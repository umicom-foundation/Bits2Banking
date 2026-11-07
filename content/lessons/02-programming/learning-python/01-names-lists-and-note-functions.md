# Names, lists and note functions

Python lets us express a short task using named values and functions. We will trace the actual Bits2Banking note lab, not assume that reading a program has already run it.

## 1. Find the source

Open [notes.py](../../../labs/python-notes/notes.py). A Python interpreter executes the program. `import json` makes JSON conversion tools available, and `from pathlib import Path` imports a type for working with paths. A path identifies a file or folder; it is not the file contents.

## 2. Read values before the full function

```text
text = " Review a lesson "
text = text.strip()
notes = []
notes.append({"id": 1, "text": text})
```

The equals sign assigns a name to a value. Quotation marks create a string of text. `strip()` returns text with surrounding whitespace removed; the second assignment keeps that result. Square brackets create an empty list. A list holds values in order. Curly braces create a dictionary: each key, such as `"id"`, has a corresponding value. `append` adds one value to the end of the list.

 <svg viewbox="0 0 700 110" role="img" aria-label="The lab normalizes surrounding whitespace before adding a note." style="width:100%;max-width:700px"><title>The lab normalizes surrounding whitespace before adding a note.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">input text</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">strip and check</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">append a note</text></svg>

The lab normalizes surrounding whitespace before adding a note.

## 3. Understand indentation and return

 Find `def add_note(text):`. `def` introduces a function. The colon begins its body, and indentation groups the statements. Unlike C braces, spacing is part of Python's grouping rules. `if not text:` handles the empty string. `raise ValueError(...)` reports invalid input and stops this call unless the error is handled by a caller. `return next_id` gives the created identifier back.

Find `def add_note(text):`. `def` introduces a function. The colon begins its body, and indentation groups statements. Unlike C braces, spacing is part of Python grouping rules. The active function first checks that input is text within its character limit. It then trims surrounding spaces and rejects empty text. `raise ValueError(...)` reports invalid input and stops this call unless a caller handles the error. `return next_id` gives the created identifier back.

## 4. Decode the identifier calculation

```text
next_id = max((note["id"] for note in notes), default=0) + 1
```

The expression in parentheses visits each note and selects its id. `max` chooses the greatest value. `default=0` supplies a value when the list is empty. Adding one creates the candidate identifier. Existing ids 2 and 7 produce 8; the empty list produces 1. This is a small local lab, not a safe identifier allocator for multiple simultaneous writers.

## 5. Try a trace

1. Predict what an input containing only spaces becomes after strip.
2. Decide whether it reaches save_notes.
3. Predict the next id for notes with ids 4 and 9.

Answers: empty text; it raises ValueError before saving; next id 10. Explain each step aloud or on paper. The existing [test source](../../../labs/python-notes/test_notes.py) offers another way to read expected behavior without executing it.

For a C23 comparison, the Framework and Kernel return explicit status values instead of relying on Python exceptions. Read `UmicomUserContractDiscover` in the Kernel support source: it publishes a complete result only after validation.

---

[Read this lesson in HTML](../../../courses/learning-python/lessons/01-names-lists-and-note-functions.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: JSON files and error boundaries](02-json-files-and-error-boundaries.md)
