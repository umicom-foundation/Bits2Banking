<!--
Umicom Bits2Banking
File: labs/web/student-help/README.md

PURPOSE:
Explain how to update and check the student help router and its browser asset.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Maintain student help

![Umicom Foundation](../../../content/assets/branding/umicom-wordmark.svg)

The [student help page](../../../content/community/student-help/index.md) contains the public answers and links. The C23 router receives up to 256 UTF-8 bytes and returns an answer identifier, or zero when none matches. It looks at whole words and short phrases in English. The browser loads the router as a WebAssembly file served by the same site.

The router is specific to this course collection and builds without a standard library or operating-system services. The small JavaScript module is needed to connect the browser's document, form events and WebAssembly API. It passes text to the router and displays one existing answer. Learners can open every answer on the page if the module is unavailable.

## Update an answer

1. Edit the corresponding answer section in the student help page and link to the lesson that supplies the steps.
2. If the questions that find it change, update the matching rules in `router.c`. Keep the answer identifier in C and its page section aligned.
3. Rebuild the WebAssembly companion when C changes. From the Bits2Banking checkout, use Clang with WebAssembly support and the LLVM linker.

```powershell
clang --target=wasm32 -std=c23 -O2 -Wall -Wextra -Wconversion -Wshadow -Werror -ffreestanding -fno-builtin -nostdlib '-Wl,--no-entry' '-Wl,--export-memory' '-Wl,--export=BtbStudentHelpQuery' '-Wl,--export=BtbStudentHelpCapacity' '-Wl,--export=BtbStudentHelpAnswer' '-Wl,--strip-all' labs/web/student-help/router.c -o content/assets/javascripts/student-help.wasm
node --check content/assets/javascripts/student-help.mjs
node --test tests/student_help.test.mjs
```

4. Build the normal site preview and open **Ask about your next step** from the site navigation. Ask about installing PowerShell 7, then updating it. Each answer should link to the corresponding steps. Try an unrelated question, then open one of the answers directly from the page.
5. Open the page again from another page of the preview. Check that the form enables after the local module loads. Disable JavaScript and check that **Browse the answers** still works.

For a question such as “How do I install/update PowerShell 7?”, look for the answer that starts by checking the current version and links to both paths. Include “from Windows PowerShell 5.1” and check that the installation steps appear. The matching logic treats the slash as a separator.

The committed WebAssembly companion lets the existing static site publish without installing a compiler. Keep it alongside its C source and the focused tests when the router changes. The command-line checks exercise the compiled module and a form-event fixture. Assess the actual layout, keyboard navigation and screen-reader behavior in the site preview.
