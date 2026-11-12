<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/compiler-preview-qualification.md

PURPOSE:
Qualify preview behavior without claiming a build

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Qualify preview behavior without claiming a build

## Choose an observation that can fail

A useful preview regression does more than look for a success message. It should detect lost arguments, changed identities, partial output and unsupported actions. The laboratory prints observations only after checking their conditions. Its CTest wrapper requires the expected exit status, complete standard output and empty standard error.

Run the refusal scenario after installing the matching SDK. The first call gives the serializer a buffer too small for the document. The second damages an active argument with invalid UTF-8. Both calls must refuse and leave every prior output byte unchanged. Comparing only the first character would miss a partial write farther into the buffer.

## Preserve the previous in-memory result

~~~c
memcpy(saved_json, json, sizeof(json));
UmiStatus status = umi_compiler_plan_json(&plan, json, 8U);
/* Expect CAPACITY_EXCEEDED and compare all sizeof(json) bytes. */
~~~

This guarantee applies to the serializer and its caller-owned memory. A later terminal or pipe write can fail after emitting part of the document. A consuming program therefore needs complete JSON parsing and a successful producer exit. Buffer publication and stream delivery are different boundaries; do not transfer one guarantee to the other without evidence.

## Qualify each layer

First build and run the installed C client to check public headers, exported dependency links and library behavior. Then qualify the native Umicom executable to check command routing, option admission and argument conversion. The native regression matrix covers three providers, two actions and two languages using deliberately nonexistent driver names. Those cases validate presentation, not compilation.

Finally, use a separate controlled project if you intend to qualify a real compiler. Record the tool version, source and SDK revisions, environment, exact command, diagnostics and exit status. A check-only compiler result still does not establish linking, installation, application launch or Studio UI behavior. Each requires its own observation.

## Practice

Create an evidence table with columns for source review, installed client, native CLI, compiler process and application runtime. Mark which rows this laboratory can exercise and which remain pending. If a case fails, keep its complete output and correct the narrow failing boundary before advancing to the next layer. Authored tests remain unexecuted until their results are collected.

## Source and practice

[Compiler preview laboratory and owner commands](../../../labs/native/framework-compiler-preview/README.md) · [Browser edition](../../courses/umicom-development/lessons/compiler-preview-qualification.html)

<!-- Previous end-of-module navigation, retained for review:
[Previous lesson](compiler-preview-json-arguments.md) · [Written course contents](index.md) · [Course index](../../courses/umicom-development/index.html)
-->
[Previous lesson](compiler-preview-json-arguments.md) · [Next lesson](compiler-publication-metadata-keys.md) · [Written course contents](index.md) · [Course index](../../courses/umicom-development/index.html)
