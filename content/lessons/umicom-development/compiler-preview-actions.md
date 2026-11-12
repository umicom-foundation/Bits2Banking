<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/compiler-preview-actions.md

PURPOSE:
Choose a compiler action before planning its arguments

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Choose a compiler action before planning its arguments

## Describe the stage you intend

A source file can take part in several stages. A syntax check asks a driver to inspect a translation unit without producing its usual object output. Compilation produces an object for later linking. Archiving groups objects into a library. These intentions need different argument mappings. Changing an action label in an editor is not enough if the generated arguments still request the old stage.

Begin with the preceding compiler ownership module, then read Actions and Prepare in the installed laboratory. The example uses original metadata and a deliberately nonexistent driver name. Its purpose is to make the mapping visible without hiding a compiler launch behind a preview button. Framework owns the mapping; a thin command-line client chooses fields and presents the result.

## Ask about a mapping separately from availability

~~~c
request.action = UMI_COMPILER_ACTION_CHECK;
bool mapped = umi_compiler_provider_can_plan_action(
    &provider, request.language, request.action);
/* mapped describes this planner, not an installed compiler. */
~~~

The query is independent of the availability field. A provider can describe a supported mapping while its executable is unavailable. Conversely, a nonempty executable does not make every action supported. The current C and C++ check mappings cover GCC, Clang and MSVC. Link and archive requests are refused by this provider planner rather than being reported as successful compile plans.

## Read the actual arguments

Run the actions scenario after qualifying the installed SDK. It checks for the GCC syntax-only switch and the absence of object-output switches. It then changes the action to compile and checks the object arguments. Finally it requests archive, expects an unsupported result, and compares the previous plan bytes. The observed refusal is intentional, not a successful archive operation.

The native CLI exposes compile and check with an explicit language standard and working directory. Check refuses output and debug options because it does not use them. A selected standard still needs a compatible installed driver; metadata alone cannot establish that compatibility.

## Practice

Write a three-row table for check, compile and archive. In each row record the requested stage, the planner status and the evidence still missing. Explain why a successful plan should not enable a green build-completed indicator. A later process runner needs its own authorization, environment, output collection and exit-status handling.

## Source and practice

[Compiler preview laboratory and owner commands](../../../labs/native/framework-compiler-preview/README.md) · [Browser edition](../../courses/umicom-development/lessons/compiler-preview-actions.html)

[Previous lesson](compiler-installed-qualification.md) · [Next lesson](compiler-preview-driver-identity.md) · [Written course contents](index.md) · [Course index](../../courses/umicom-development/index.html)
