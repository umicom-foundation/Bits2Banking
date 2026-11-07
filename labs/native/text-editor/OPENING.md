# Open an existing document

This extension adds `open PATH` to the small terminal editor. It accepts up to 1,024 bytes of normalized text. The teaching format is printable ASCII, tabs and newlines. Windows CRLF line endings become LF. A lone carriage return, embedded zero byte or non-ASCII text is rejected.

Framework's production document services cover broader application requirements. This exercise isolates validation and state publication so the whole algorithm can be read in one sitting.

## Prepare the lab

Use a C23 toolchain, CMake 3.24 or newer and Ninja. From the Bits2Banking root, PowerShell and Bash use the same build commands:

```text
cmake -S labs/native/text-editor -B build/text-editor -G Ninja -DBUILD_TESTING=ON
cmake --build build/text-editor
ctest --test-dir build/text-editor --output-on-failure --no-tests=error
```

Launch in PowerShell with `& .\build\text-editor\btb-text-editor.exe`. On a Unix-like host use `./build/text-editor/btb-text-editor`. These commands assume a single-configuration Ninja build.

## Try a complete round trip

1. Choose a practice directory you can find again.
2. Launch the editor and enter `append Hello from the editor`.
3. Enter `save C:/practice/first-note.txt`, replacing the path with an existing parent directory. The destination file must not already exist.
4. Enter `quit`.
5. Launch the editor again and enter `open C:/practice/first-note.txt`.
6. Enter `show`. Expect `TEXT: Hello from the editor`.
7. Enter `append !`, then try opening the original file again. Expect refusal because the current document has unsaved work.
8. Save to a different new filename before opening another document.

For Bash, choose a path such as /home/learner/practice/first-note.txt. Paths after open or save are used literally by this program; do not add shell-style quote characters to its own prompt. Spaces are accepted as part of the remaining path.

## Understand what is preserved

Loading reads into a private candidate. The old document remains untouched if reading, validation or closing fails. A successful load publishes the candidate, marks it clean and begins a new undo history.

The tests exercise empty files, the exact capacity, one byte too many, CRLF, invalid bytes, a missing path and unsaved-work refusal. They also inspect the previous undo snapshot after rejected input.

A failed load never writes the source file. A failed save can leave a partial newly created file, as described in the original guide. The editor still refuses overwriting existing files.

## Scope

This is a bounded ASCII teaching editor. It does not yet implement Unicode, multiple documents, durable replacement saves or a graphical text surface. The authored checks require execution with the chosen compiler and operating system before claiming a validated result.

