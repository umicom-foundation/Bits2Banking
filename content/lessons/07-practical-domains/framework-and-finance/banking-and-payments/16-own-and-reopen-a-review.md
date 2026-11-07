<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/16-own-and-reopen-a-review.md

PURPOSE:
Own and reopen a review

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Own and reopen a review

Learn how a banking client turns imported observations into a review that can be explained, checked and reopened. Follow one small program that calls the shared Framework services.

This laboratory is a small C program. A compiler translates its source into an executable; CMake describes the build and Ninja runs the required build steps. Use an installed Umicom Framework SDK containing the bank_feed component, a C23 compiler, CMake and Ninja from the same toolchain. On Windows, open PowerShell and use the UCRT64 tools. An SDK is a set of headers and libraries used by another program; these commands consume it rather than rebuild Framework.

1. Open PowerShell.
2. Enter the commands below, using your installed SDK directory if it differs.
3. Read the configure result before building. If CMake cannot find UmicomFrameworkConfig.cmake or the bank_feed component, install the matching SDK first; do not replace the library with a local imitation.
4. Run the executable, then the registered laboratory check. A failing check prints its source line and exits with a nonzero status.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\statement-review"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/applications" -DBUILD_TESTING=ON
cmake --build build --parallel 2
& ".\build\btb-statement-review.exe"
ctest --test-dir build --output-on-failure --no-tests=error
```
On Linux, use the same source and an SDK built for Linux. In Bash, run cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/your/sdk/path -DBUILD_TESTING=ON, then cmake --build build, ./build/btb-statement-review and ctest --test-dir build --output-on-failure --no-tests=error. Replace /your/sdk/path with the actual installation directory. Windows libraries cannot be linked into a Linux executable.

Open main.c in a text editor to follow the calls. The program uses fictional observations held in memory; it does not connect to a bank or change any account. The [Learning C course](../../../../courses/learning-c/index.html) explains declarations and control flow in more depth.

## A snapshot keeps a stable review

An archive is a stored representation of data. In this API, UmiBankStatementArchiveCreate first creates an owned in-memory snapshot containing imported observations and the review assumptions. Owned means it has its own required data and does not depend on the original feed remaining alive.

The lab deliberately destroys feed immediately after creating archive. It then encodes the archive into JSON bytes. JSON is a text format containing named fields, numbers, strings and structured values. The encoding is versioned so a reader can recognize the expected format.

## Follow the lifetime chain

1. Import creates feed.
2. ArchiveCreate copies the feed and stores the account, currency, dates and supplied balances.
3. Destroy(feed) releases the original; assigning NULL makes the local variable visibly empty.
4. ArchiveEncode allocates encoded bytes and reports their length.
5. Destroy(archive) releases the original archive object.
6. ArchiveDecode reads the encoded bytes into reopened.
7. ArchiveFree releases the encoded buffer.
8. ArchiveRead copies a snapshot for inspection.
9. ArchiveCloneFeed makes an independent feed copy. Destroying reopened does not invalidate that copy.

Each successful allocation has a matching release function. Different object types use different release functions because their internal storage can differ. Never use free on an opaque handle unless its API explicitly requires that.

## Recalculate when reopening

The archive stores the inputs needed to review the observations. It does not trust a serialized green match flag as the result. Decode validates the archive and recalculates through the existing review logic. A result should follow from retained evidence, not from a label that can be edited independently.

The source format is marked as statement CSV. The digest string remains empty because this lab has not calculated one. A digest is a fingerprint of bytes, not proof of who created them. An unverified digest supplied inside a file cannot authenticate that file by itself.

## Exercise

Draw one box for each object and cross out the box at each destroy call. Check that every later call uses a still-live object. This is a practical way to reason about dangling pointers: a pointer must not be used after the storage it refers to has been released.

The program stays in memory. A real application should ask the user where to save its archive and explain that the archive contains all imported accounts, including observations outside the currently selected review scope.

## Read the source

[Open the example source](../../../../../labs/framework/statement-review/main.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Investigate a statement difference](15-investigate-a-statement-difference.md) · [Next: Refuse a partial statement import](17-refuse-a-partial-statement-import.md)
