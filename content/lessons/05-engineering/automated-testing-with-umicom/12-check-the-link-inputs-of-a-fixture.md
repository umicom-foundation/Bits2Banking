<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/12-check-the-link-inputs-of-a-fixture.md

PURPOSE:
Check the link inputs of a fixture

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check the link inputs of a fixture

A fixture is a small program built to check one part of a product. Its executable has its own list of link inputs. The linker combines compiled pieces into a program and needs a definition for every function the fixture calls. A working application gives evidence for its own executable. The fixture still needs a successful link before its checks can run.

## Trace two executables on paper

1. Draw two boxes labelled **Reader**, the application, and **Probe**, the test fixture. Each uses a decoder that reads a small structured message. Draw a **Trees** library card containing the definition of `open_tree`, a function the decoder calls.
2. Connect Reader to Trees. In Probe, draw the decoder inside the box because the fixture includes the real decoder source. Probe can then make a selected memory request fail and observe how the decoder responds. Give Probe a link list with only its support library.
3. Follow Probe’s call to `open_tree`. Its linker cannot find the definition in the inputs it received. Write **link failed** on Probe’s new executable card. The decoder check has no result from that attempted build.
4. Add Trees to Probe’s link list and draw a fresh build-plan card. Predict what changes. The linker can now find the definition. To record a test pass, you still need a successful link and an observed test result for the resulting executable.

## Follow the same boundary in Umicom Framework

The local chat allocation fixture includes the production codec directly and substitutes its own memory allocation functions. This lets the fixture check what happens when a chosen allocation fails. The health decoder calls shared JSON tree functions such as `UmiJsonTreeCreate`, whose definition comes from `Umicom::protocol`. The fixture therefore names Protocol in its own link inputs.

In the saved owner case, the working build instructions already listed Protocol. The earlier generated plan and the failed link command still omitted it. Keep both observations with their build identities. A source edit and the command an earlier build actually used describe different points in time.

A separate focused mirror build used the corrected link inputs and passed all six fixture checks. It covered the chat, health and delta cases at each of two allocation failure positions. The owner rerun was still pending in the saved evidence. For each attempt, write down which executable linked successfully and which tests actually produced outcomes.

[Course contents](index.md) · [Previous lesson · Keep startup evidence with its test attempt](11-keep-startup-evidence-with-its-test-attempt.md) · [Next lesson · Match the selector to the test executable](13-match-the-selector-to-the-test-executable.md) · [See which library Ninja will link](../learning-build-systems/29-see-which-library-ninja-will-link.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/12-check-the-link-inputs-of-a-fixture.html)
