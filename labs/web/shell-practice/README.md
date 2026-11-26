<!--
Umicom Bits2Banking
File: labs/web/shell-practice/README.md

PURPOSE:
Explain how to rebuild and verify the browser shell practice module.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Maintain the browser shell exercise

![Umicom Foundation](../../../content/assets/branding/umicom-wordmark.svg)

The [learner page](../../../content/practice/shell/index.md) has a form and a written fallback. The C23 module owns the fixed paths, accepted command forms and previous status. It can run without a standard library and exports a short input buffer and an output view.

The browser adapter uses JavaScript for document events, UTF-8 conversion and loading WebAssembly. The command rules and practice folder state stay in C. The adapter fetches the module from the site and displays results through text nodes.

1. Make one change to the C table or command behavior. Add a focused test for the behavior and then update the learner's worked steps.
2. Open PowerShell in the Bits2Banking checkout. Build the companion with a Clang installation that includes the WebAssembly linker.

~~~powershell
clang --target=wasm32 -std=c23 -O2 -Wall -Wextra -Wconversion -Wshadow -Werror -ffreestanding -fno-builtin -nostdlib '-Wl,--no-entry' '-Wl,--export-memory' '-Wl,--export=BtbShellInput' '-Wl,--export=BtbShellCapacity' '-Wl,--export=BtbShellOutput' '-Wl,--export=BtbShellOutputLength' '-Wl,--export=BtbShellSubmit' '-Wl,--export=BtbShellReset' '-Wl,--strip-all' labs/web/shell-practice/shell.c -o content/assets/javascripts/shell-practice.wasm
node --test tests/shell_practice.test.mjs
~~~

3. Confirm that every test passes. If the linker is missing, check `clang --version` and the matching `wasm-ld` installation. Keep the prior companion until the changed C source builds and passes.
4. In the site preview, choose Bash and run `cd reports`. Switch to PowerShell and run `Get-Location`. The two practice folders are independent. Disable JavaScript and confirm that the table still gives a complete worked exercise.

An unknown command changes the simulated previous status. It does not invoke a host shell. New curriculum about pipelines or mounted host folders needs its own product design and test scope.

The desktop sample compiles the same model with the small standard-input adapter in `shell_cli.c`. The learner page gives matching commands and output for both clients.
