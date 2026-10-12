# Build and use the Umicom native education tools

Umicom Framework includes a small C23 command-line program named `umicom-education`. It prepares original Bits to Banking chapters for the website, checks required assets, builds the website with the currently supported publishing engine and serves the generated pages over local HTTP.

The source belongs to Umicom Framework. It runs against the Bits2Banking repository without modifying the Framework repository or needing to copy the source into the book project.

## Build on Windows

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
      -B ".\build\umicom-education" `
      -G Ninja `
      -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
      -DBUILD_TESTING=ON

cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure
```

The binary appears at `C:\umicom\Umicom-Applications\build\umicom-education\bin\umicom-education.exe`. The isolated build does not require rebuilding all Umicom applications.

## Check and prepare the learning website

```powershell
Set-Location "C:\umicom\Umicom-Applications"

$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"

& $Education doctor --repo $Books
& $Education prepare --repo $Books
& $Education verify --repo $Books
```

`prepare` publishes approved copies of ten historic Islam manuscript chapters, thirteen existing illustrations and seven official Umicom branding resources. It does not change the originals. If a published page differs from the manuscript, it prints `DIFFERENT (preserved)` instead of overwriting it. The `--refresh` option permits a deliberate replacement after the difference has been reviewed.

For branding in a separate location, specify `--brand "C:\path\to\framework\resources\brand"`.

## Generate and preview HTML

First, install the website dependencies into a project-local environment:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
py -3 -m venv .venv
& ".\.venv\Scripts\python.exe" -m pip install -r ".\requirements-docs.txt"
```

With the updated native command, the repository's `.venv` is selected before
MSYS2's `python.exe` on `PATH`. You can select it explicitly with `--python`.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
& $Education build --repo $Books
if ($LASTEXITCODE -ne 0) { throw "The website build failed." }
& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/` in a web browser. Stop the preview with Ctrl+C.

`build` invokes the existing MkDocs renderer and still requires Python and the packages in `requirements-docs.txt`. It verifies that the selected interpreter can load MkDocs and Material, then checks for `site/index.html` after the child process returns successfully. By contrast, `serve`, `verify` and `prepare` run as native C code without launching Python. The native preview reads the existing generated site, not Markdown source files.

## Assemble the original Markdown book in C23

No Python interpreter is needed to inspect volume manifests or assemble the
review manuscript. The original chapters remain untouched:

```powershell
& $Education book list --repo $Books
& $Education book check --repo $Books --volume islam_blueprint_for_life
& $Education book assemble --repo $Books --volume islam_blueprint_for_life
```

`book check` reads the original title and chapter list and verifies that
all named source files are present. It does not create a manuscript or modify
published content. The check accepts the existing bounded manifest subset,
not arbitrary YAML.

The generated result is `output/native-books/islam_blueprint_for_life.md`.
A different existing result is preserved unless a deliberate `--refresh` is
requested. Final PDF/DOCX production remains with the established book tools.

On MSYS2 Windows, a child probe must reach Python as one complete command-line
argument. The renderer now uses the whitespace-free expression
`__import__('mkdocs');__import__('material')`. If a previous binary reported
`SyntaxError: Expected one or more names after 'import'`, rebuild
`umicom-education` before retrying. The old probe is preserved in a disabled
review block in `site_renderer.c`.

The [build-tool diagnostic lesson](../lessons/05-engineering/46-diagnose-a-failing-build-tool.md)
shows how to test the project-local interpreter directly, and the
[CTest process lesson](../lessons/05-engineering/47-test-child-processes-with-ctest.md)
explains the regression that catches split arguments and abrupt fixture failures.

Read [Prepare a reliable website build environment](../lessons/05-engineering/43-prepare-a-website-build-environment.md)
and [Assemble a book from Markdown using C23](../lessons/05-engineering/44-native-book-manuscripts.md)
for complete exercises.

## Build on Linux

Assuming you have checked out both projects under `~/umicom`:

```bash
cd "$HOME/umicom/Umicom-Applications"
cmake -S framework/tools/umicom-education -B build/umicom-education -G Ninja -DBUILD_TESTING=ON
cmake --build build/umicom-education --parallel 2
ctest --test-dir build/umicom-education --output-on-failure

./build/umicom-education/bin/umicom-education doctor --repo "$HOME/umicom/Umicom-Bits2Banking" --brand "$HOME/umicom/Umicom-Applications/framework/resources/brand"
./build/umicom-education/bin/umicom-education prepare --repo "$HOME/umicom/Umicom-Bits2Banking" --brand "$HOME/umicom/Umicom-Applications/framework/resources/brand"
./build/umicom-education/bin/umicom-education build --repo "$HOME/umicom/Umicom-Bits2Banking"
./build/umicom-education/bin/umicom-education serve --repo "$HOME/umicom/Umicom-Bits2Banking" --port 8765
```

The server binds only to local IPv4 loopback. It is a development preview, not a general-purpose web host. It supports GET and HEAD, streams normal files, refuses directory listings and does not provide TLS, authentication, CGI or application APIs.

## What remains in the existing toolchain

The original Python BookForge, publishing scripts, PowerShell helpers, MkDocs configuration and historical manuscripts remain available. Native C does not yet create PDF/DOCX books, replace Pandoc or perform GitHub Pages deployment. Those improvements have separate acceptance milestones in the [major roadmap](../roadmap.md).

## Explore the source

Start with [`site.h`](https://github.com/umicom-foundation/umicom-framework/tree/main/include/umicom/education), then inspect `site_content.c` and `site_preview.c`. A website request begins in the socket listener, passes through URL and Host validation, opens one permitted file and streams its bytes. The CLI in `tools/umicom-education/main.c` only chooses which Framework service should perform the work.

Next: [Build and inspect the server](../lessons/05-engineering/39-build-a-c-web-server.md).

## Build and preview in one explicit command

A successful `doctor` check proves that the required input and renderer are available. It does not generate `site/index.html`. If `serve` reports that the home page is missing, build the website first. After rebuilding the native Education tool, you can use:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
$Python = "$Books\.venv\Scripts\python.exe"

& $Education serve --repo $Books --build --python $Python --port 8765
```

`--build` invokes the existing MkDocs adapter before opening the native preview server. It is an opt-in operation: an ordinary `serve` command stays read-only. If MkDocs fails, the HTTP server does not start. The `--directory` option is reserved for an existing export and cannot be combined with `--build`.

Read [Build the website before serving it](../lessons/05-engineering/62-build-and-preview-the-education-site.md) for the full guided exercise.

## Inspect ELF programme headers without loading a programme

After rebuilding Framework Education for Update 12, you can inspect an
ELF executable or Umicom Kernel image using a read-only command:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"

ctest --test-dir ".\build\umicom-education" `
  -R "^framework\.education\.(elf_load_plan|load_plan\.cli)$" -V

& $Education load-plan --file `
  ".\build\umicom-education\education-load-plan-test\fixture with spaces\umicom kernel.elf"
```

The report identifies ELF programme headers of type `PT_LOAD`, their file
ranges, their virtual-memory ranges, permissions and the number of bytes that
would need zero-initialisation. It checks the entry point, rejects overlapping
regions and refuses malformed offsets. It does not execute the inspected file,
create processes or activate an MMU. The fixture is a synthetic example, not a
bootable kernel.

The parser is implemented in the shared Framework files
`include/umicom/education/elf_load_plan.h` and
`src/education/elf_load_plan.c`. Its tests are in
`tests/education/test_elf_load_plan.c`.

Continue with [Chapter 87: ELF load plans](../lessons/05-engineering/87-read-elf-program-headers-and-load-plan.md)
and [Chapter 91: Follow the Umicom Kernel](../lessons/06-umicom/91-follow-umicom-kernel-memory-source.md).


## Inspect executable page permissions (Update 13)

Build the native tool using the existing CMake instructions above, then inspect a verified ELF fixture or a separate executable file:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Fixture = ".\build\umicom-education\education-load-plan-test\fixture with spaces\umicom kernel.elf"
& $Education memory-audit --file $Fixture
```

The result describes the number of virtual pages covered by ELF `PT_LOAD` segments, how many of those pages are writable and executable, and whether multiple segments share a page. No executable code is launched and no memory protections are changed. A review finding returns a nonzero status; this is a conservative page-level analysis, **not** a production loader's approval decision.

Learn how this works in [Lesson 94](../lessons/05-engineering/94-review-executable-memory-protection.md), and use the [page-fault model](../lessons/05-engineering/93-understand-page-faults-in-c23.md) for an independent C23 simulation.

## Inspect a teaching IPC trace without sending messages

A new native C23 command accepts the bounded versioned **teaching format** `UMIIPC1`. It checks record order and payload lengths and models SEND/RECEIVE ownership. This is not the Umicom Kernel IPC ABI and does not execute any system call.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Trace = ".\build\umicom-education\education-ipc-trace-test\fixture with spaces\owned messages.ipc"
& $Education ipc-trace --file $Trace
```

The fixture is written by `framework.education.ipc_trace` during CTest. See [Lesson 99](../lessons/05-engineering/99-inspect-an-ipc-trace-with-c23.md) and [Umicom Kernel message channels](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_channel.c).

## Inspect a C23 classroom scheduling trace

The `schedule-trace` command reads the independent `UMISCH1` teaching format. It
checks ready-queue order, wait-key ownership, task lifetimes and malformed
record boundaries without executing any scheduler or Kernel operation:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
ctest --test-dir ".\build\umicom-education" -R "framework\.education\.schedule_trace" --output-on-failure
& $Education schedule-trace --file ".\build\umicom-education\education-schedule-trace-test\fixture with spaces\round robin.sch"
```

The file is generated by the C23 test. See [the complete lesson](../lessons/05-engineering/105-inspect-a-scheduler-trace-with-c23.md)
for the record layout. The Kernel's own scheduler, IPC and syscall trace
contracts are separate; this teaching format must not be used as a kernel ABI.


## Inspect bounded timer and event traces (Update 16)

The Framework's standalone education tool can inspect an explicitly versioned,
read-only C23 classroom event trace. The parser reconstructs a monotonic logical
clock, deadline-checked waits, early event signals, cancelled waits and timeout
outcomes. It rejects malformed or stale events and preserves an existing report
when the input is invalid.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education timer-trace --file `
    ".\build\umicom-education\education-timer-trace-test\fixture with spaces\clock events.tmr"
```

CTest creates that synthetic file. It is not a recording from a running Kernel.
For the format, full build steps and interpretive examples, see
[Lesson 110](../lessons/05-engineering/110-inspect-a-timer-trace-in-c23.md).
Use the [Umicom Kernel timer and events guides](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/TIMER_DRIVEN_USER_SCHEDULING.md)
for real privileged execution and event ownership.

## Inspect interrupt-source ownership (Update 17)

The new `interrupt-trace` command checks one explicitly versioned classroom trace. It rejects a wrong owner, stale generation, impossible acknowledgement, cancellation after ENTER, release during a fault and malformed or oversized records. All parsing is native C23, read-only and separate from real Umicom Kernel privileged interrupt control.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
ctest --test-dir ".\build\umicom-education" -R "framework\.education\.interrupt_trace" --output-on-failure
& $Education interrupt-trace --file `
    ".\build\umicom-education\education-interrupt-trace-test\fixture with spaces\owned interrupt.irq"
```

CTest produces the fictional file before the CLI consumer through a fixture dependency. See [Lesson 115](../lessons/05-engineering/115-inspect-interrupt-ownership-traces.md) and the actual [Umicom Kernel interrupt ownership guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/INTERRUPT_OWNERSHIP.md).


## Inspect a fictional driver evidence file

The native Framework command `umicom-education evidence-trace --file PATH` checks
a bounded `UMIEVD1` teaching file without executing its contents. A fixed-size
header, checked 80-byte records, strict driver-state transitions, owner and
generation identity, a logical tick and a SHA-256 digest chain are validated
before a complete report is published. The test suite generates an example
file with spaces in its path. It does not read real interrupt state, prove
that a trusted producer authored the file, persist documents or carry out a
real driver recovery.

Learn from [Chapter 120](../lessons/05-engineering/120-inspect-a-chained-evidence-trace.md)
and the [native C23 header contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/education/evidence_trace.h).


## Inspect the device I/O request lifecycle (Update 19)

The Framework-owned command `umicom-education device-io-trace --file PATH`
reads a bounded `UMIDIO1` classroom format. It checks submission identities,
device owner/generation lifetimes, recorded cancellation requests, terminal
completion outcomes, FIFO collection and safe quiescent detach. It does not
execute requests, access hardware, authorise user-space DMA or replace the
Umicom Kernel VirtIO block driver.

The focused CTest parser test prepares the exact 27-record file used by the
independent CLI test, including a path with spaces. Learn from [Lesson 125](../lessons/05-engineering/125-inspect-device-io-traces-in-c23.md)
and the [Framework C23 public contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/education/device_io_trace.h).
