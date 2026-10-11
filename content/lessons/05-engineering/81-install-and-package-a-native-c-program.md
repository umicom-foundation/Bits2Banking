# 81. Install and package a native C23 programme

Building a programme is not the same as making it convenient for someone else to use. A complete delivery must put the executable, libraries, public headers and required runtime resources in predictable locations.

CMake supports an **install step** that copies specified build products to a selected destination. We will use a private folder inside Bits2Banking rather than change the Windows system directory.

## 1. Identify the outputs

Our static-library laboratory produces three important kinds of material:

- An executable: `btb-ledger-demo.exe` on Windows.
- A static library: commonly `libbtb_ledger.a` with GCC.
- A public API header: `include/btb/ledger.h`.

A user who only wants to run the demonstration needs its executable and the runtime libraries required by the chosen Windows toolchain. A developer who wants to compile another programme against the library also needs its public header and the static archive.

The CMake file explicitly declares which outputs should be installed:

```cmake
install(TARGETS btb_ledger ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS btb-ledger-demo RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES include/btb/ledger.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/btb)
```

`GNUInstallDirs` provides conventional directory variables such as `bin`, `lib` and `include`. These names can differ by operating system or package policy.

## 2. Build and test before installing

In PowerShell:

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

Do not package a build whose tests have failed. A package should represent a known, reviewed build result.

## 3. Install to a private folder

```powershell
cmake --install ".\output\learning-build\static-library-map" `
    --prefix "C:\umicom\Umicom-Bits2Banking\output\learning-install\static-library-map"
```

Now inspect the destination:

```powershell
Get-ChildItem ".\output\learning-install\static-library-map" -Recurse
```

You should find `bin`, `lib` and `include/btb` containing the installed products. The exact static-library filename depends on the compiler.

## 4. Create a portable archive

If you only need a local training ZIP, use PowerShell to compress the *staged output*:

```powershell
Compress-Archive `
    -Path ".\output\learning-install\static-library-map\*" `
    -DestinationPath ".\output\learning-install\static-library-map.zip" `
    -Force
```

This command is a packaging step, not another application's implementation. It does not modify the source code. The ZIP is not an installer, and it should not be described as one.

## 5. Check what the package does not include

A compiled Windows executable may rely on runtime DLLs that exist on the developer's computer but are absent from another user's computer. For a real Umicom application, deployment must account for those dependencies, licences and architecture compatibility.

The Umicom Framework repository already has Windows runtime and installer engineering. A learning ZIP is not a replacement for that system. This exercise teaches the boundary between *compiled output* and *deliverable product*.

A release should also record the source revision, build configuration, compiler, target architecture, tests and file checksums. A hash identifies whether bytes changed; it does not prove authorship or provide a digital signature.

## 6. Use library metadata honestly

The educational archive inspector can tell us how many ordinary object members a static archive contains. It cannot prove whether its contents are safe or whether a licence permits redistribution. Those questions require source provenance, licence review and software supply-chain controls.

For native applications, useful future topics include CMake package configuration files, installed targets, `pkg-config`, SBOM generation, signing and reproducible release builds. Do not claim these capabilities are implemented by this small laboratory.

## 7. Practical exercise

Open the installed `include/btb/ledger.h` and compare it with the source header. Confirm that installation did not copy private implementation helpers from `src/ledger.c` into the public API. Then review the installed archive using `umicom-education archive --file`.

Continue with [the development roadmap](../../umicom/native-education-tools.md) and the Umicom Framework packaging documentation for larger applications.
