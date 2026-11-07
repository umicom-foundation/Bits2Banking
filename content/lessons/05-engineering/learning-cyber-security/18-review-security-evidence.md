<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/18-review-security-evidence.md

PURPOSE:
Review security changes with tests and explicit limits

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Review security changes with tests and explicit limits

An identity names a person or service. Authentication establishes who is requesting access; authorization decides which action that identity may perform. A session lets a program associate later requests with an earlier authentication result. This module follows these ideas using synthetic local records and the existing Umicom Framework C interfaces.

Open `labs/framework/identity-lifecycle/README.md` in the Bits2Banking checkout. It contains complete PowerShell and Bash configure, build, run and test commands. Start in that lab directory, use `cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/framework-sdk -DBUILD_TESTING=ON`, then `cmake --build build` and `ctest --test-dir build --output-on-failure --no-tests=error`. The SDK path names your installed Framework. Stop on the first command error. The executable is `build/btb-identity-lifecycle.exe` on Windows and `build/btb-identity-lifecycle` on Unix-like systems. The lab creates no accounts or network connections.

## Evidence has a scope

Reading a function can reveal a missing boundary check. A regression test can demonstrate that specific inputs now produce the intended result on a particular build. Neither establishes that an entire application is secure.

The credential regression program has named scenarios. Each scenario checks a public contract: malformed fields are rejected, maximum complete strings are accepted, invalid lookups preserve outputs, duplicates do not replace records, and capacity remains bounded.

## Reproduce a focused check

After building the matching Framework source in its configured build directory, run:

```powershell
ctest --test-dir build/windows-ucrt64-debug -R "^framework.security.credential.boundaries\." --output-on-failure --no-tests=error
```

The build directory must match the configuration you actually used. If testing through Umicom Applications, use that repository's configured build directory instead. `--no-tests=error` prevents an empty selection from looking like a successful check.

## Write an engineering record

Record the source revision, compiler, build directory, selected tests, exit status and any skipped coverage. Describe the defect in terms of input and state: an unterminated fixed field previously reached string processing. Describe the repair: bounded admission before lookup and storage. Do not put real credentials in the record.

## Review beyond the happy path

1. Null pointer and empty field.
2. Largest accepted field.
3. Capacity-sized field with no terminator.
4. Existing ID with changed metadata.
5. Full registry and another insertion.
6. Failed operation followed by retrieval of the original record.

The Framework regression keeps important setup and checks active in optimized builds; it does not rely on disabled assertions to perform required operations.

## Exercise

Design one additional failure case for the lab without duplicating a scenario already present. State the invariant it protects and the exact observation that would prove the invariant was broken. Keep a passing test distinct from an authored test that has not yet been run.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/security/test_credential_boundaries.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Use the same security boundary from desktop and mobile](17-desktop-and-mobile-sign-in.md)
