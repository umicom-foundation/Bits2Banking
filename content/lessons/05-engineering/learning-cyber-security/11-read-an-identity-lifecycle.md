<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/11-read-an-identity-lifecycle.md

PURPOSE:
Read an identity lifecycle from start to finish

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read an identity lifecycle from start to finish

An identity names a person or service. Authentication establishes who is requesting access; authorization decides which action that identity may perform. A session lets a program associate later requests with an earlier authentication result. This module follows these ideas using synthetic local records and the existing Umicom Framework C interfaces.

Open `labs/framework/identity-lifecycle/README.md` in the Bits2Banking checkout. It contains complete PowerShell and Bash configure, build, run and test commands. Start in that lab directory, use `cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/framework-sdk -DBUILD_TESTING=ON`, then `cmake --build build` and `ctest --test-dir build --output-on-failure --no-tests=error`. The SDK path names your installed Framework. Stop on the first command error. The executable is `build/btb-identity-lifecycle.exe` on Windows and `build/btb-identity-lifecycle` on Unix-like systems. The lab creates no accounts or network connections.

## What the program owns

A pointer stores the address of another object. The three registry pointers in `main.c` initially contain `NULL`, meaning they refer to no object. Each `create` function allocates one registry and writes its address through an output pointer. Its return value says whether creation succeeded. A successful allocation must eventually have a matching `destroy`.

The identity record contains an ID, a display name, a kind, an enabled flag and a revision. An ID is a stable key; a display name is presentation text. Renaming a displayed person should not accidentally create a different identity.

## Trace the calls

1. Read the assignments to `learner`. The strings describe a synthetic learner.
2. Find `umi_identity_registry_create`. The ampersand in `&identities` passes the address of the pointer so the function can update it.
3. Find `umi_identity_registry_register`. It receives a pointer to a complete record, validates it and copies it into the registry.
4. Follow the `EXPECT` macro. A failed condition prints a line number and jumps to `finish`.
5. At `finish`, the program destroys all three registries. Their destruction functions accept a null pointer, so earlier setup failures still reach safe cleanup.

The macro is a small test aid. It does not catch a crash or recover arbitrary invalid pointers. Its value is making every required operation explicit in the example.

## Draw the lifetime

```text
NULL pointer -> create -> owned registry -> use -> destroy
caller record ----------register copy----> stored record
```

The record on the caller's stack and the stored record are different objects. Change the caller's display name after registration, retrieve the stored record, and predict whether it changes. Verify your prediction using the registry's public API.

## Check your understanding

Why is registering `learning.reader` insufficient to prove that a real person is that reader? Registration creates metadata. Authentication needs independent evidence checked by a trusted provider. This lab starts after that production boundary and deliberately uses synthetic values.

## Read the source

[Open the example source](../../../../labs/framework/identity-lifecycle/main.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Next: Keep credential references inside their buffers](12-reference-fields-and-string-bounds.md)
