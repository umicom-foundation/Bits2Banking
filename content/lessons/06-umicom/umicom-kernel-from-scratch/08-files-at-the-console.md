# Create a file and run a program at the Kernel console

Connect a terminal command to the actual Kernel services you have been reading. This optional exercise uses an emulated machine and a RAM-only file.

## Before you start

You need the prepared Kernel toolchain and a successfully built `umicom-console.elf`. Read `umicom-kernel/docs/USER_GUIDE.md`, then `docs/CONSOLE_LEARNING_GUIDE.md` for exact Windows commands and log paths. Reading this lesson does not require installation. A terminal is a window where you enter text commands; the guest prompt belongs to the emulated Kernel, not to the host shell.

 <svg viewbox="0 0 700 110" role="img" aria-label="The console parses a bounded line and asks the existing virtual filesystem to change its own RAM storage." style="width:100%;max-width:700px"><title>The console parses a bounded line and asks the existing virtual filesystem to change its own RAM storage.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Typed command</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Kernel file service</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">RAM-backed file</text></svg>

The console parses a bounded line and asks the existing virtual filesystem to change its own RAM storage.

## Prepare a small, predictable file

```text
create /notes/lesson.txt
write /notes/lesson.txt "Kernel services use explicit requests"
cat /notes/lesson.txt
stat /notes/lesson.txt
```

Enter one line at a time after `umicom>`. The leading slash names an absolute guest path. Quotes keep the spaces inside one argument. These commands are not C code and must not be pasted at a PowerShell prompt.

`create` refuses an existing name. `write` replaces the existing content by truncating first, so it is not an atomic save. `cat` displays the bytes; `stat` reports metadata. For the exact ASCII sentence above, expect 37 bytes. A **virtual filesystem** gives a common file interface; this particular provider stores data in RAM.

## Change and predict

```text
append /notes/lesson.txt "."
cat /notes/lesson.txt
```

Predict the new length before running: one period adds one byte to this ASCII text, giving 38. The next display should end with a period. Text commands do not automatically add a newline to the file.

## Cross the program boundary

```text
run /bin/umicom-diagnostic.elf 4
```

The shell loads an ELF file through its filesystem. ELF is an executable file format describing code, data and memory requirements. The separately loaded program calls the native contract reader from the previous lesson. Its report should say `state=exited` and `calls=10`.

Count those calls: one identity request, one copy request, seven contract queries and one exit. The program computes its exit value as its identity plus 37. Do not mistake that deliberate diagnostic value for the host QEMU process's success code.

## Find each owner in the source

1. `platform/qemu-riscv64/serial.c` reads UART bytes.
2. `kernel/console_line.c` collects a bounded complete line.
3. `kernel/console_shell.c` chooses a command and calls existing services.
4. `programs/diagnostic/main.c` executes as the loaded program.
5. `tests/console_session/session_tests.c` checks the complete serial conversation rather than calling the parser directly.

## Finish and reflect

Enter `poweroff`. The Kernel closes its RAM filesystem and the emulator exits. Restarting gives a new RAM filesystem; the lesson file does not persist. This is not evidence of durable disk storage.

Exercise: explain why a parser unit test can pass while a real terminal exchange still fails.

<details>

<summary>Answer</summary>

The unit test may supply bytes directly to a function. A real exchange also depends on the host terminal, emulator serial backend and UART receive path. Both kinds of coverage are useful, but they check different boundaries.

</details>

If an arrow key damages a line, clear it with Ctrl-U and type again. The current editor deliberately rejects escape sequences. Keep failure logs; do not weaken bounds or execute a damaged prefix to make an exercise appear successful.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/08-files-at-the-console.html) · [Learning sequence](../../../start/learning-sequence.md)
