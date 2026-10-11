# Video 9 — Building a book manuscript in C23

**Duration:** Approximately 15–20 minutes

**Related reading:** [Assemble a book from Markdown using C23](../../lessons/05-engineering/44-native-book-manuscripts.md)

## Why a manifest matters: 0:00–3:00

**Narration:**

A book has a title, chapters and a reading order. We can keep every chapter in a separate source file and use a manifest to say which chapters belong in a particular edition. This helps writers work on smaller documents without losing the structure of the complete book.

**On screen:** Open `dropzone/documents/islam_blueprint_for_life/volume.yml`. Highlight the title and the `chapters` sequence. Show the ten original Markdown files in the same folder.

## Listing the available volumes: 3:00–6:00

**Narration:**

Our native Umicom Education command can examine a volume manifest without starting Python. The command checks that the filenames are safe and the chapters exist, then prints the volume's title and chapter count.

**On screen:** Run `umicom-education book list --repo C:\umicom\Umicom-Bits2Banking` and inspect the output. Open `framework/src/education/book.c` and point out the manifest-loading function.

## Assembling the manuscript: 6:00–10:30

**Narration:**

Now build the combined Markdown manuscript. The program reads the original chapters in the order given by the manifest, writes a temporary output, compares it with any previous edition, and publishes only after the complete operation succeeds.

**On screen:** Run `book assemble --volume islam_blueprint_for_life`. Open `output/native-books/islam_blueprint_for_life.md` and scroll through the joined chapters. Explain that this is an intermediate review copy, not yet the final formatted book.

## Safe updates: 10:30–15:00

**Narration:**

If a writer changes a chapter, we do not want a background tool to overwrite earlier generated work without permission. The assembler detects a difference and preserves the existing output. After review, a deliberate `--refresh` replaces that generated copy. The original manuscripts remain where they were.

**On screen:** Show the regression test in `framework/tests/education/test_book.c`. Explain its two-chapter fixture and the missing-file and unsafe-path cases. Show the `DIFFERENT (preserved)` message without editing a real published book.

## What comes next: 15:00–18:00

**Narration:**

The next development stages will add output manifests and checked adapters to produce HTML, PDF and DOCX editions. We will keep the existing publishing tools in service while validating their replacements. In software publishing, preserving source material and explaining how an output was built are as important as the final page design.

**On screen:** Show the *Bits to Banking* roadmap and the related CMake and C programming chapters.
