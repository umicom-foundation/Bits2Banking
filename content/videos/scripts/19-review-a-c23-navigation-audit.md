# Episode 19 — Review a learning website with C23

**Length:** approximately 10–14 minutes. **Demonstration:** the Framework-owned `umicom-education audit` command. **Related chapters:** [70](../../lessons/05-engineering/70-check-website-navigation-in-c23.md) and [71](../../lessons/05-engineering/71-compiler-diagnostics-and-static-analysis.md).

## Opening — a broken link (0:00–2:30)

**Narration:**

“A website can contain every lesson file and still disappoint the reader if its navigation points to the wrong place. A page title might look correct while the file name has changed. Our next task is to find these mistakes before publishing, using a small native programme written in C23.”

**Screen:** Show a navigation example with a path that points to a missing chapter. Show that the real Markdown file has a different name.

## Follow the data (2:30–5:30)

**Narration:**

“The command reads the existing `mkdocs.yml`, looks for the local Markdown paths, and checks that those files exist beneath the website's content directory. We must also reject parent-directory traversal and duplicates. The checker does not modify the files or attempt to decide what the author meant. It reports a precise problem for a human to review.”

**Screen:** Open `include/umicom/education/nav_audit.h` and `src/education/nav_audit.c`. Show the public report fields, then trace a single safe path through the validation.

**Narration:**

“This is a deliberately narrow check. General YAML is a structured language with rules for quoting, indentation and much more. Reading a few navigation lines is not a substitute for a full YAML parser. MkDocs is still needed to validate and render the actual website.”

## Build and test (5:30–9:30)

**Screen:** Open the `Umicom-Applications` directory, configure and build the Framework education tool, then run CTest. Show the additional navigation-audit test.

**Narration:**

“A useful test suite must include failure cases. We will check a valid navigation file, then a missing file, a duplicated target, an attempt to leave the content directory, and a malformed quoted entry. Each invalid input must produce a failure result without changing any original document.”

**Demonstration:** Run `umicom-education audit --repo C:\umicom\Umicom-Bits2Banking`. Explain the count of pages and failures. In a disposable copy of `mkdocs.yml`, introduce and then correct a broken path.

## Compile warnings and finish (9:30–14:00)

**Narration:**

“We now have two complementary checks: the C compiler checks the source code of our tool, while the tool checks navigation targets in the educational repository. Neither one proves that the full website is valid. The final step is still to build the website with MkDocs and open it as a reader would.”

**Screen:** Show the compiler warning flags, the native audit, a successful MkDocs build and the local C web server. End with the Umicom Framework and Bits2Banking source links.
