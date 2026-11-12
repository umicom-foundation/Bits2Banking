<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/compiler-preview-driver-identity.md

PURPOSE:
Keep the complete compiler driver identity

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Keep the complete compiler driver identity

## A path is part of the requested operation

Suppose a caller supplies a long executable path and a convenience constructor copies only its beginning. The resulting string may still look like a valid path, yet it no longer identifies what the caller chose. A later process service cannot reconstruct the missing characters. This is why a compiler preview must refuse over-capacity identities instead of silently shortening them.

The shared provider factory validates its strings before construction. All eight convenience providers use that boundary. The native CLI currently exposes GCC, Clang and MSVC; the broader factory set does not imply that every language or action is exposed in the command. Keep those two surfaces distinct when documenting support.

## Recognize the refusal value

~~~c
UmiCompilerProvider provider = umi_compiler_gcc_provider(
    requested_driver, NULL);
if (provider.revision == 0U) {
    /* Correct the complete input; do not trim it to make it fit. */
    return UMI_STATUS_INVALID_ARGUMENT;
}
~~~

The factory returns a value rather than a separate status. Invalid text produces an invalid zero-initialized provider, whose revision is zero. A valid constructed provider starts at revision one. Null or empty executable text remains a supported way to describe an unavailable provider. A nonempty executable sets the availability field without probing the filesystem.

## Distinguish storage from reality

The executable array accepts at most 2,047 bytes followed by its terminating zero. A target accepts at most 191 bytes followed by its terminator. These are byte capacities; they do not promise that every operating system accepts such a path or that the driver understands the target. UTF-8 characters can occupy more than one byte.

Run the identity scenario. It first supplies an overlong driver and checks the invalid result. It then uses a short name that is deliberately not installed and observes a declared provider. Neither step starts a process. That second observation teaches why the word available in a metadata record must not be presented as verified toolchain health.

## Practice

Design three separate interface messages: input exceeds storage, driver identity accepted, and driver successfully qualified. List the evidence needed for each. Then explain how truncation could make a later log misleading even if no process ran during planning. Preserve the original requested value in the caller so the user can correct it.

## Source and practice

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Compiler preview laboratory and owner commands](../../../labs/native/framework-compiler-preview/README.md) · [Browser edition](../../courses/umicom-development/lessons/compiler-preview-driver-identity.html)
-->
[Compiler preview laboratory and owner commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-compiler-preview/README.md) · [Browser edition](../../courses/umicom-development/lessons/compiler-preview-driver-identity.html)

[Previous lesson](compiler-preview-actions.md) · [Next lesson](compiler-preview-json-arguments.md) · [Written course contents](index.md) · [Course index](../../courses/umicom-development/index.html)
