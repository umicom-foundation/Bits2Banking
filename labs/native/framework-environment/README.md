<!--
Umicom Bits2Banking
File: labs/native/framework-environment/README.md

PURPOSE:
Teach installed environment composition and ownership.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->



# Compose an environment without changing your shell

![Umicom](../../../content/assets/branding/umicom-wordmark-on-dark.svg)

A child process can receive a list of named values such as MODE=debug. This exercise prepares that list in memory. It starts no child, changes no global environment and writes no file. The application owns the input records; Umicom Framework validates, combines and projects them.

## Build against an installed SDK

1. Install a matching Framework SDK with the toolchain component and the shared branding helper. Headers, libraries and the compiler must use the same architecture and compatible runtime. The toolchain component is larger than this example; do not replace it with a copied environment.c.
2. Substitute your actual SDK prefix for C:/umicom/installed/framework below. Run each command separately and stop on errors. PowerShell does not automatically stop after a failed native command.
3. Compile, run CTest and inspect the example. These are commands for you to execute, not recorded results.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-environment -B .\build\framework-environment -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-environment --parallel 2
ctest --test-dir .\build\framework-environment --output-on-failure --no-tests=error
.\build\framework-environment\btb-framework-environment.exe compose
~~~

On Linux, use the matching native C23 compiler and SDK prefix and omit the .exe suffix. Framework supplies the approved SVG resources and Windows ICO/version metadata. The console inherits the terminal's installed font; this lab supplies no font files.

## Predict each result

| Mode | Expected output | What it teaches |
| --- | --- | --- |
| compose | COURSE=practice, then MODE=release | Overlay replaces an existing name; the base stays unchanged. |
| alias | Same two lines | A destination may also be the base input. |
| refusal | refused malformed overlay; previous=retained | Invalid input must not erase a previously valid destination. |
| borrow | COURSE=practice, then MODE=lease | Replacement text may come from the destination's existing value. |
| kit | Kit ID, profile ID, target triple and compiler | A kit adds its non-empty overrides through Framework. |
| kit-refusal | refused malformed kit override; previous=retained | A bad late override must not publish earlier values. |
| cross-partial | partial discovery retained; target=synthetic-cross-target; not ready | UNAVAILABLE can describe a published diagnostic snapshot. |
| kit-revision | revision exhausted; sysroot=sdk/target | A revision identity must not wrap. |
| kit-overlap | overlapping replacement; sysroot=target | A text setter can read a slice of its own destination. |

All nine scenarios return zero only when the demonstrated contract holds. The CMake checker compares the exact output, exit and empty error stream. A crash is a failure. These synthetic values are safe to display; real environment values may contain secrets and should not be logged indiscriminately.

## Follow the lifetime

A UmiEnvironmentPlan contains inline character arrays and process-entry pointers into those arrays. A plain structure copy duplicates the pointers as well as the text. Those pointers still refer to the old address until they are rebound. Use umi_environment_plan_variables on a valid destination when obtaining a process view; keep that plan alive and unchanged until the synchronous process consumer returns. Do not retain a pointer after freeing the plan.

The compose service builds a temporary candidate. Only after every input fits does it publish the candidate into the caller's destination and rebind the pointers. This permits exact input/output aliasing and preserves the previous destination when allocation, validation or capacity fails. The service reports allocation failure; the program must not continue as if composition succeeded.

A plan holds at most 24 entries. Names have space for 127 bytes plus a terminator and values for 8191 bytes plus a terminator. These are byte counts, not Unicode character counts. Empty values are allowed; empty names, equals signs in names, line breaks and unterminated stored fields are refused. Names remain case-sensitive in this service. A host-specific process adapter may impose additional rules.

## Extend the exercise

Add a synthetic FEATURE=enabled overlay. Predict that compose now prints three lines, then update the exact expected output in check.cmake. Next fill the base to 24 distinct names and add a new overlay name. Confirm CAPACITY_EXCEEDED and unchanged destination contents. Replacing an existing name at capacity should still succeed. Keep both checks so a later change cannot silently weaken one half of the contract.

If CMake cannot find UmicomFramework, check the install prefix rather than copying headers. If linking fails, compare installed header and library identities. If a scenario reports an unexpected result, retain its stdout, stderr, exit code, compiler and SDK revision. A passing memory-only exercise does not establish shell startup, CMake execution or GUI launch behaviour.

## Add a selected developer kit

A kit groups a compiler, target and related tool settings. The kit scenario uses a synthetic target and no profile, so it demonstrates data preparation only. It does not discover or validate an installed compiler. A real client may supply a compatible profile; non-empty kit fields override its prepared values. The shared service validates every inline kit string, stages all overrides, then publishes one complete plan. A malformed late Java compiler value therefore preserves PREVIOUS instead of exposing earlier partial edits. Read the kit-refusal branch alongside the ordinary refusal branch and explain why both callers depend on the same final publication rule.

## Update a kit without losing the previous selection

A revision identifies an observed kit state. Each accepted setter advances it once. If the counter reaches UINT64_MAX, the service returns CAPACITY_EXCEEDED and keeps the previous record. Do not force the counter back to zero on the same stored identity. Decide explicitly how your application creates a replacement identity and how it preserves history. This exercise reaches the limit directly; normal callers do not need billions of updates to check the boundary.

The cross-partial case illustrates a different contract. A valid discovery with missing tools is useful evidence, so apply_cross_toolchain records it, changes the kit to DEGRADED and returns UNAVAILABLE. A malformed field, incompatible version or allocation failure instead leaves the old kit unchanged. Empty optional tool paths retain their previous selections. Read status and state together; a compiler path or capability flag does not prove that a cross-target binary can run on the host.

The kit-overlap case passes a pointer four bytes into the current sysroot. The setter checks bounds and revision capacity before using overlap-safe copying. The program owns the kit and must not retain that borrowed pointer across later mutation or destruction.

Run the three added scenarios from the same installed-consumer build:

~~~powershell
.\build\framework-environment\btb-framework-environment.exe cross-partial
.\build\framework-environment\btb-framework-environment.exe kit-revision
.\build\framework-environment\btb-framework-environment.exe kit-overlap
~~~

Predict each line first, then compare the recorded result. These commands do not discover a real compiler, start Python, build a target, write media or prove that an operating system will boot.
