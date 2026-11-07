# Lab: Follow an Identity and Session Lifecycle

This small C program uses the existing Framework identity, credential-reference and session registries. A registry is an in-memory collection that manages records. A credential reference identifies where a separate secret provider would find a secret; the reference is not the secret itself.

The program creates synthetic records, rejects a malformed reference, issues a synthetic session, disables its identity, revokes the session, and checks the exact expiration boundary. It does not accept a password, contact a broker or create a web account.

## Before starting

Install a C23 compiler, CMake 3.26 or newer and Ninja. Install a matching Umicom Framework SDK with the security component. The SDK must include bounded credential-field validation. Keep this source beside the other Bits2Banking labs.

Open PowerShell. `Set-Location` changes the current directory. Replace the SDK path if it is installed elsewhere.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\identity-lifecycle"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build build --parallel 2
& ".\build\btb-identity-lifecycle.exe"
ctest --test-dir build --output-on-failure --no-tests=error
```

On a Unix-like system, use the SDK prefix supplied by its installer:

```bash
cd /path/to/Umicom-Bits2Banking/labs/framework/identity-lifecycle
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/framework-sdk -DBUILD_TESTING=ON
cmake --build build --parallel 2
./build/btb-identity-lifecycle
ctest --test-dir build --output-on-failure --no-tests=error
```

Stop if a command fails. Expected successful output has five descriptive messages and exit status zero. The last message is `Local lifecycle exercise complete; no login service was contacted.` A missing SDK is a configuration problem; a failed contract check identifies a source line to compare with the installed Framework revision.

## Read the code in order

1. Three opaque registry pointers start as `NULL`. Opaque means the client uses public functions without depending on the private structure.
2. Fixed arrays receive synthetic text. Each copy includes a terminating zero byte.
3. Registration stores complete metadata. The malformed copy deliberately has no terminator in its reference array; admission must fail before registry mutation.
4. Session issuance uses a synthetic clock value of 100 and a lifetime of 50. These tiny values are for repeatable arithmetic, not a production timeout policy.
5. The identity is disabled. The client checks current identity state and revokes the existing session.
6. A new synthetic session issued at 200 is valid at 249 and expired at 250.
7. Cleanup removes inactive records. The final block destroys every registry, including after earlier failures.

Session handles stay inside the process and are never printed. Failure diagnostics print the source line, not secret values. Review the linked [security course](../../../content/courses/learning-cyber-security/index.html) before designing a real login flow.

## Exercise

Change the final observation from 250 to 249 and predict which assertion will fail. Restore it, then add a check at 251. Explain why a valid session alone cannot authorize a transfer or give a user permission to read another user's documents.

## Scope and extension

A production registration system also needs a trusted identity provider or password-verification service, abuse controls, transport security, recovery rules, persistent storage and operation-specific authorization. This lab deliberately reuses Framework primitives without pretending that metadata registration implements those services. Registries are destroyed when the process ends.

Source: [identity](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/security/identity.h), [credentials](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/security/credential.h), [sessions](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/security/session.h).
