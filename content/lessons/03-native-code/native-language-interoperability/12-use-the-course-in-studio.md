<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/12-use-the-course-in-studio.md

PURPOSE:
Teach use the examples in umicom studio ide.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Use the examples in Umicom Studio IDE

[Course contents](index.md) · [Previous](11-test-errors-and-ownership.md)

## Understand the supported layers
Studio's document controls use shared Framework services. This course extends recognition and language selection for free-form Fortran, Odin and Nim, alongside existing C, C++, assembly, Rust, Zig and D identities. It supplies the appropriate line-comment prefixes for those high-level languages. Assembly commenting depends on dialect and is not guessed automatically.

Recognition is not compilation. Syntax highlighting also depends on the installed syntax descriptions. Completion, diagnostics and debugging require configured compatible tools. No lesson claims that every compiler or language server is bundled with Studio.

## Open and inspect a source file
1. Open a practice workspace or the Bits2Banking lab directory in Studio.
2. Open a source file such as main.f90, main.odin or main.nim. Check its effective language using the document language action.
3. Select a language explicitly if a temporary filename has no recognised extension. Return to automatic detection when the filename is corrected.
4. On a disposable copy, select a line and use Toggle Language Comment. Expect ! for free-form Fortran, // for Odin and # for Nim. Toggle again and confirm the text is restored. Save only after reviewing the change.
5. Use the existing build/task workflow or terminal with the exact commands supplied by the relevant lab. Inspect the selected executable and working directory before execution.

## Read lessons without running code
The Studio learning guide includes Native languages and the C boundary. A separately selected Bits2Banking native-interoperability pack provides this longer course and its source examples. Loading a pack presents content; it does not install a compiler or execute an example.

Choose the Bits2Banking repository as the library root and learning-packs/native-language-interoperability.json as the manifest path, following the lab README. Keep the manifest with the exact hashed files. If admission reports a missing file or digest mismatch, review the source identity and prepare an updated manifest rather than disabling validation. Links outside the admitted pack may require another pack or a browser.

## Exercise and answer
A .nim file opens as text and the compiler command is missing. These are separate questions: inspect the editor's language identity and syntax-description availability, then check the Nim installation and PATH. Installing a compiler does not itself change the editor's language selection.

After each exercise, record what you actually observed. Browser layout, native reader navigation, installed SDK consumption and every foreign compiler need their own checks. An authored lesson or a recognised extension is useful progress, not proof of full IDE support.

## Read the complete source

[labs/languages/native-interoperability/README.md](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-interoperability/README.md)
