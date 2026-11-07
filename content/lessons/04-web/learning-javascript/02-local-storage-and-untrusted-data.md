# Local storage and untrusted data

Keeping a value on screen and saving it for a later visit are separate operations. The task-board lab uses browser-local storage, not a shared collaboration service.

## Encode an array as text

```text
localStorage.setItem(storageKey, JSON.stringify(tasks));
```

`localStorage` stores string values for a browser origin. An origin normally includes scheme, host and port. `JSON.stringify` converts the array into JSON text. JSON is a data format; it is not a program to execute. A key identifies which stored value belongs to the lab.

 <svg viewbox="0 0 700 110" role="img" aria-label="Serialisation changes a live value into text that can be saved and later read." style="width:100%;max-width:700px"><title>Serialisation changes a live value into text that can be saved and later read.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Array in memory</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">JSON text</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Browser-local value</text></svg>

Serialisation changes a live value into text that can be saved and later read.

## Loading is another boundary

The existing lab uses `JSON.parse` inside a `try` block, checks that the result is an array, and keeps only non-empty strings. The following is its shape in explanatory pseudocode:

```text
read saved text
try to decode JSON
if the decoded value is an array:
    keep entries that are non-empty strings
otherwise:
    start with an empty task list
```

A previously saved value can be missing, damaged or edited through browser tools. Parsing can fail, and valid JSON can still have the wrong shape. A number, object or nested array is not a valid task title merely because it is legal JSON.

## Handle storage failure honestly

Browser settings, storage quotas or privacy modes can prevent saving. The lab catches a failure and writes a warning to the browser console while retaining the current in-memory tasks. Reloading can lose those unsaved changes. This is a teaching lab with limited feedback; a production application needs a visible saved/unsaved state and a recovery path.

Opening a page through a local `file:` address can also have browser-specific storage behaviour. The lab does not establish a reliable portable storage service for every browser or device.

## Private and shared are different

Local storage is not an encrypted vault and is not a database shared by contributors. Scripts running with access to the same origin may access it. Do not store passwords, patient details or financial credentials there. A future hosted Umicom board needs server-side identity, access checks, validation, conflict handling and persistence. Hiding an Edit button is not access control.

## What the example does and does not prove

The lab demonstrates event handling, rendering and basic recovery from invalid saved JSON. It does not limit every stored length, coordinate concurrent editors or verify an authenticated owner. Framework's native persistence services have separate ownership contracts; they cannot be replaced by assuming that browser storage has the same guarantees.

## Exercise

Imagine that the save operation throws an error after a new task appears. Which statement is accurate: “the task is permanently saved” or “the task is visible in this session, but persistence failed”?

<details>

<summary>Answer</summary>

The second. The UI state and the persistence result must be reported separately. This same distinction matters when Studio edits a document and when Bank prepares a transaction.

</details>

---

[Read this lesson in HTML](../../../courses/learning-javascript/lessons/02-local-storage-and-untrusted-data.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: Separate visible state from saved state](03-separate-visible-state-from-saved-state.md)

[Previous: Events and visible state](01-events-and-visible-state.md)
