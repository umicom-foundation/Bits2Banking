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
