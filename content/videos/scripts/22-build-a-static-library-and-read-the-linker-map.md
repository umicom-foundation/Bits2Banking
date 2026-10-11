# Episode 22 — Build a C23 library and read the linker map

**Running time:** approximately 12–16 minutes.  
**Companion lessons:** [77. Static archives](../../lessons/05-engineering/77-understand-static-archives.md), [78. Symbols and link maps](../../lessons/05-engineering/78-symbol-visibility-and-linker-map.md).  
**Working example:** [`labs/native/static-library-map`](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/static-library-map).

## 00:00–01:20 — Why libraries matter

**Narration**

Imagine that we are developing several Umicom applications: an education programme, a note-taking application and a simulated financial ledger. All three may need to validate amounts, handle errors and format output. If each programme copies the same source code, small differences soon appear. One application is corrected while the others keep an older mistake.

A library gives us a more maintainable design. It holds a reusable implementation behind a public interface. Applications depend on that interface rather than copying the implementation. In the Umicom ecosystem, reusable behaviour belongs in Umicom Framework; a product connects those services to the user experience.

In this demonstration we will build a tiny but realistic library. It totals fictional amounts using whole pence, protects against unsigned overflow and returns a clear result to its caller. We will use C23, CMake and Ninja. Then we will examine the static archive and ask the linker why it selected one of its members.

**On screen:** Show the Umicom Framework and Bits2Banking repository links, then open `labs/native/static-library-map/include/btb/ledger.h`.

## 01:20–03:10 — Separate declaration and implementation

**Narration**

Look at `ledger.h`. This public header introduces `BtbLedgerStatus` and the declarations of `BtbLedgerTotalPence` and `BtbLedgerFormatPence`. These are promises to applications. They specify what parameters the caller supplies and how a result is returned.

Now open `src/ledger.c`. Here is the code that fulfils those promises. The total function accepts a borrowed array and its length. It adds entries only after checking for overflow. It calculates the full result in a temporary local variable, then writes the answer to the caller's output only when every addition has succeeded.

This is an example of failure-atomic behaviour: a failed calculation does not leave the caller with a partially updated total.

Notice another function, `AddChecked`. It is declared `static`. In C, a file-scope `static` function has internal linkage. Another source file cannot link to it as an external function. The helper is private to this implementation and is not listed in the public header.

**On screen:** Highlight the two public declarations, the `static` helper and the final assignment to `*outTotal`.

## 03:10–05:00 — Compile and test

**Narration**

Open PowerShell in the Bits2Banking repository. We will configure the laboratory using CMake and choose the UCRT64 GCC compiler. Ninja then builds the targets that CMake defines.

**On screen — PowerShell:**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\static-library-map" `
    -B ".\output\learning-build\static-library-map" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\static-library-map" --parallel 2
ctest --test-dir ".\output\learning-build\static-library-map" --output-on-failure
```

**Narration**

CMake configures the work; the compiler translates C into machine-code objects; Ninja coordinates the build steps; and CTest runs the executable tests. These are separate responsibilities.

Run the demo programme. It reports GBP 504.00 in fictional learning-fund contributions. The important detail is that our code uses integer pence. It has no floating-point rounding surprise.

**On screen:** Run `btb-ledger-demo.exe`; show the output.

## 05:00–07:00 — Open the static archive

**Narration**

The build produced a static archive, usually called `libbtb_ledger.a`. An archive is a container for object files. Each object was produced by a compiler, and the linker can select individual members when they provide missing definitions.

A normal `ar` file begins with the eight-byte signature `!<arch>` followed by a newline. Every member has a fixed header describing its name and length. Some archives also include a symbol index or long-name table.

Our new Umicom Education command inspects this structure using native C23 code, without extracting the contents or running any member. It understands ordinary GNU and BSD archive name encodings. It deliberately refuses thin archives, which do not contain all their members inside the archive file.

**On screen — PowerShell:**

```powershell
Set-Location "C:\umicom\Umicom-Applications"
& ".\build\umicom-education\bin\umicom-education.exe" archive `
    --file "C:\umicom\Umicom-Bits2Banking\output\learning-build\static-library-map\libbtb_ledger.a"
```

**Narration**

Read the member count and the object-file name. Notice that the tool distinguishes regular objects from archive metadata. It also enforces file boundaries before trusting declared sizes. Those checks are vital when reading any binary format supplied by another process.

## 07:00–09:30 — Follow the linker map

**Narration**

Now we will answer a different question: *why did the linker include the ledger implementation?*

CMake requested a map file during the application link. Open `btb-ledger-demo.map` under the laboratory's build directory and search for the archive name.

**On screen — PowerShell:**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
Select-String -Path `
    ".\output\learning-build\static-library-map\btb-ledger-demo.map" `
    -Pattern "btb_ledger"
```

**Narration**

The application object refers to `BtbLedgerTotalPence`. The linker finds an object in the static library that defines it. The map can show the archive member included to satisfy that reference. The linker may also need runtime-library functions for formatting the printed output.

This is why a programme can compile successfully but fail at link time: type checking only needs declarations. A working executable additionally needs definitions for the referenced functions.

Use `nm` to inspect the symbols in the archive. Public functions often appear with a capital `T` in GNU `nm`; local functions can appear with a lowercase `t`. Those letters depend on the tool and target. The key concept is the difference between a definition available to other object files and an internal implementation detail.

## 09:30–11:30 — Install a package into a private folder

**Narration**

We have compiled and linked the application. Next we will install the selected build products into a private directory. The laboratory's CMake rules install its executable, library archive and public header.

**On screen — PowerShell:**

```powershell
cmake --install ".\output\learning-build\static-library-map" `
    --prefix "C:\umicom\Umicom-Bits2Banking\output\learning-install\static-library-map"
```

**Narration**

Open the install folder. The public header appears under `include/btb`; the static library appears under the install library directory; and the application appears under `bin`. The implementation source file is not installed as a public API.

For a real application, packaging also needs runtime dependencies, licences and an appropriate installer or distribution method. The educational example is intentionally smaller. It teaches the compile, link and install boundaries without pretending that a ZIP of build files is a production installer.

## 11:30–End — Exercise and connection to Umicom

**Narration**

Now try one change independently. Add another fictional entry to the application and rebuild. Its total will change. The CTest output-expectation test should report that change until you deliberately update the test. Investigate the difference rather than disabling the check.

The next episode will take these same ideas into cross-compilation. We will use one host computer to produce object files for a different processor, RISC-V64, and see how that relates to the original Umicom Kernel.

Read Lessons 77 and 78 on the Bits2Banking website, inspect the source on GitHub and share any corrections with other learners. A clear explanation or tested contribution is another way to help someone else progress.
