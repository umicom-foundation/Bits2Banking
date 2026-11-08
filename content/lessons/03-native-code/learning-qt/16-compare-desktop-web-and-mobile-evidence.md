<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/16-compare-desktop-web-and-mobile-evidence.md

PURPOSE:
Compare desktop, web and mobile release evidence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Compare desktop, web and mobile release evidence

## Before starting

Collect the source revisions, tool versions and outputs from the target exercises you actually ran. Keep unrun targets visible in the record. This lesson produces a reviewable comparison, not an installer or a public release. The lab still validates names only.

## Build an evidence table

For each target, record Framework and Bits2Banking revisions, local edits, Qt kit, compiler, configuration, build result, package result and the actual interaction result. Use separate rows for desktop offscreen tests, native desktop observation, browser, Android emulator/device and iOS simulator/device. A blank cell means missing evidence; write unrun rather than pass.

~~~text
Target | Source identity | Toolchain | Build | Package | Interaction | Limits
Desktop event test | captured | captured | observed | n/a | observed | offscreen only
Browser | captured | captured | unrun | unrun | unrun | no browser evidence
~~~

## Explain disagreements

If every target rejects a name unexpectedly, inspect the common C policy and exact byte input. If only one target displays stale text, inspect its event route and presentation. If the browser does not load at all, inspect generated resources and delivery first. These are different failure locations even though the user sees one form. Preserve the first error and the smallest reproducing input.

## Prepare a reviewable handoff

List the complete files changed and explain why the portable target exists. Identify the old implementation retained for review. Include the exact commands used, their exit results, and which manual actions were observed. Package source separately from generated binaries so a reviewer can distinguish authored logic from target artifacts. Before any distribution, review the chosen Qt licence, required notices, runtime deployment and signing for that product.

## Exercise and worked answer

Desktop tests pass and Android packaging succeeds, but the APK has never been installed. What can the report say? It can say those desktop tests ran and the Android package was produced under the recorded toolchain. It cannot say Android launch, input, lifecycle or accessibility passed. Give the next tester the package identity and the explicit interaction journey.

## Continue learning

Compare this Qt client with the C web and Wt courses. Wt moves its application logic to a server process; Qt Wasm executes this form in the browser. The shared C naming contract stays useful in both. Use the native Android and iPhone courses when studying platform-specific bridges, and keep the same ownership and evidence questions.

## Read the source

[labs/framework/qt-profile/README.md](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/README.md). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Observe mobile input and application lifetime](15-observe-mobile-lifecycle-and-input.md)
