<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/12-reference-fields-and-string-bounds.md

PURPOSE:
Keep credential references inside their buffers

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep credential references inside their buffers

An identity names a person or service. Authentication establishes who is requesting access; authorization decides which action that identity may perform. A session lets a program associate later requests with an earlier authentication result. This module follows these ideas using synthetic local records and the existing Umicom Framework C interfaces.

Open `labs/framework/identity-lifecycle/README.md` in the Bits2Banking checkout. It contains complete PowerShell and Bash configure, build, run and test commands. Start in that lab directory, use `cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/framework-sdk -DBUILD_TESTING=ON`, then `cmake --build build` and `ctest --test-dir build --output-on-failure --no-tests=error`. The SDK path names your installed Framework. Stop on the first command error. The executable is `build/btb-identity-lifecycle.exe` on Windows and `build/btb-identity-lifecycle` on Unix-like systems. The lab creates no accounts or network connections.

## Bytes and text

A C character array has a fixed number of bytes. A C string uses a zero byte, written `'\0'`, to mark its end. An array can contain nonzero bytes in every position; that array is not a complete C string.

The credential record has four arrays: credential ID, principal ID, provider ID and secret reference. The reference describes where a separate provider would look up a secret. Do not put the password itself in that field.

## Follow the boundary check

The Framework checks that a field is non-empty and finds a terminator before reaching its capacity. It performs this check before looking for duplicate IDs or storing the record. Checking only the first byte would accept an unterminated array and leave later string operations without a safe stopping point.

In the lab:

1. Copy the valid reference to `malformed`.
2. Fill its complete `secret_reference` array with `'x'` using `memset`.
3. Register it and require `UMI_STATUS_INVALID_ARGUMENT`.
4. Check the registry count remains one.

`sizeof malformed.secret_reference` obtains the array's byte capacity. It does not measure how many characters were typed. The failure must preserve the existing registry.

## Try the accepted boundary

Make a separate reference with exactly capacity minus one text bytes and a final zero byte. Give it a distinct valid ID. Registration should accept the complete fields if other constraints are satisfied. Use synthetic data and never print real secret references into shared logs.

## Readable memory still matters

A length check cannot make an arbitrary pointer safe. The caller must provide readable storage. For a malformed lookup test, supply the whole declared identifier-capacity array, not a pointer to a smaller unterminated allocation.

## Review question

Would truncating two different long IDs into the same shorter string preserve their identity? It would not. Reject values that cannot fit the contract instead of silently changing the key. Read the Framework regression file `tests/security/test_credential_boundaries.c` to compare empty, maximum, unterminated and duplicate cases.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/security/credential.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Read an identity lifecycle from start to finish](11-read-an-identity-lifecycle.md) · [Next: Issue and observe a session without exposing its handle](13-issue-and-observe-a-session.md)
