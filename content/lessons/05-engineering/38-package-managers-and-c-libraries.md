# Package managers and useful C libraries

A software library is reusable code that another program can call. A package manager helps install the library, its headers and sometimes its build tools. Learning to separate your own source code from external dependencies is an important part of building reliable applications.

We will use SQLite, a small embedded database, as the first example. A Notes application might initially hold data only while it is running. To preserve notes after closing, it needs a durable storage mechanism. SQLite provides one possible implementation without requiring a separate database server.

## 1. Know what a dependency includes

A typical C library provides a **header** file declaring functions and types, and a compiled library containing the implementation. A project must find the appropriate header and link against a library built for the correct platform and ABI.

```text
Notes application
      │
      ├─ Public application code: notes.c, notes.h
      │
      └─ Database adapter uses SQLite
               ├─ sqlite3.h     (public declarations)
               └─ sqlite3     (compiled library)
```

Applications should not copy a third-party library's source into their own codebase without examining its licence, version, provenance and security-update policy.

## 2. Windows: MSYS2 and UCRT64

Umicom Framework is developed with the MSYS2 UCRT64 toolchain on Windows. The UCRT64 environment contains packages for GCC, Clang, CMake, Ninja, GTK4 and other libraries.

Open **MSYS2 UCRT64** from the Start menu for package-management commands. The command below is intended for that environment, not ordinary PowerShell:

```bash
pacman -Syu
pacman -S --needed \
  mingw-w64-ucrt-x86_64-toolchain \
  mingw-w64-ucrt-x86_64-cmake \
  mingw-w64-ucrt-x86_64-ninja \
  mingw-w64-ucrt-x86_64-pkgconf \
  mingw-w64-ucrt-x86_64-sqlite3
```

If `pacman -Syu` requests that the terminal be closed, close it and reopen MSYS2 UCRT64 before updating again. To confirm a library is visible to the build tools, run:

```bash
pkg-config --modversion sqlite3
pkg-config --cflags --libs sqlite3
```

The version and flags displayed depend on the installed packages. `pkg-config` does not compile the application by itself; it reports the configuration needed to use the selected library.

## 3. Linux package managers

The library name can differ between distributions. On Debian or Ubuntu, development headers for SQLite typically come from `libsqlite3-dev`:

```bash
sudo apt update
sudo apt install build-essential cmake ninja-build pkg-config libsqlite3-dev
pkg-config --modversion sqlite3
```

On Fedora the development package is commonly named `sqlite-devel`. Never assume a package installed for one compiler environment can safely be linked into an incompatible runtime environment.

## 4. Portable library managers

Two further approaches are useful in C and C++ projects:

**vcpkg** can provide a manifest describing libraries required by a project and integrate with CMake through a toolchain file. It is especially useful when the same CMake project needs packages on several operating systems.

**Conan** uses recipes, dependency graphs and profiles to build or retrieve packages for a selected compiler, architecture and build configuration. It is commonly used in C/C++ projects needing precise package versions and binary settings.

You do not need to install every package manager. First choose the one supported by the repository you are contributing to. Mixing installations without understanding ABI compatibility can create hard-to-diagnose build failures.

## 5. Frequently useful C libraries

| Library | Typical use in a real application |
|---|---|
| **SQLite** | Embedded database, transactions and query storage. |
| **GLib** | Common data structures, events, object support and platform utilities. |
| **GTK4** | Native graphical windows, controls and layouts. |
| **libcurl** | HTTP and other network-client protocols. |
| **OpenSSL** | Cryptography and TLS, where the chosen platform and licence permit its use. |
| **zlib** | Compressed data streams. |
| **libgit2** | Inspecting and modifying Git repositories through a library API. |
| **PCRE2** | Pattern matching and regular expressions. |
| **json-c** | Reading and writing JSON objects. |
| **libuv** | Event loops, non-blocking I/O and platform process support. |

A reusable Umicom Framework service owns a general capability, such as persistence, process control or HTTP access. A product-specific application uses that service instead of creating another parallel implementation. A third-party library may sit behind a Framework adapter so the public Umicom contract remains stable.

## 6. An example CMake dependency

A small standalone program can request SQLite through CMake's `PkgConfig` discovery:

```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLITE3 REQUIRED IMPORTED_TARGET sqlite3)

target_link_libraries(my_notes PRIVATE PkgConfig::SQLITE3)
```

This fragment assumes that a target named `my_notes` was already created and the SQLite development package installed. It belongs after `add_executable(my_notes ...)` in a complete project. Do not paste an isolated fragment into a blank file and expect a program to be built.

In Umicom Framework applications, direct database calls should normally remain inside the authorised Data Server implementation or adapter. Business and GUI modules use the Data Server's documented contracts instead of opening SQLite independently.

## 7. Keep dependency evidence

For a reproducible build, record the selected library version, source or package repository, licence, important build flags and known platform restrictions. A **software bill of materials (SBOM)** is a structured list of software components and dependencies used to construct a product.

When a library fixes a security defect, the dependency must be updated and tested. Vendoring old code without an update plan makes maintenance more difficult, not easier.

### Exercises

Check the compiler version, then inspect the reported SQLite include and link flags. Find one library already used in Umicom Framework's CMake source and explain which module is allowed to call it. Finally, decide whether a Notes model really needs a database at all, or whether saving a single file would be sufficient for the first iteration.

Next: [How to build and inspect a C web server](39-build-a-c-web-server.md).
