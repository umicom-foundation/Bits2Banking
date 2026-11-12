<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/project-select-a-new-destination.md

PURPOSE:
Choose a destination without confusing it with write authority

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Choose a destination without confusing it with write authority

After preparing the installed-SDK lab in its README, run this scenario. Commands below are qualification instructions, not recorded results.

~~~powershell
& .\build\framework-project-recipes\project-recipes.exe destination
~~~

## Separate selection from effects

A file chooser can select an existing parent directory and ask for one new folder name. UmiDeveloperProjectChooseDestination combines those values under shared path rules. It is useful in Studio, a terminal command or another application because all clients can apply the same naming boundary. The function prepares a string; it neither creates the folder nor confirms that the eventual destination is unused.

~~~c
char destination[UMI_DEVELOPER_PROJECT_PATH_CAPACITY];
UmiStatus status = UmiDeveloperProjectChooseDestination(
    "C:/learning", "recipe-study", destination, sizeof destination);
~~~

## Observe two different outcomes

The destination scenario expects C:/learning/recipe-study. The reserved-folder scenario supplies CON and requires refusal with the previous output unchanged. The shared rooted-file profile rejects portable-device-name hazards on every host, so a project recipe does not become acceptable merely because it was prepared on a host with different filename rules. The lab does not need the selected parent to exist because this operation performs lexical validation only.

## Explain lexical validation

Lexical means examining the spelling of a path without asking the filesystem which object it identifies. Rejecting a parent traversal or an absolute child path is valuable, but it does not resolve symbolic links, junctions, case-insensitive aliases or changes made by another process. <!-- Earlier exact-spelling explanation retained for review: Current project plan duplicate detection compares path text. Do not claim that two different accepted strings necessarily identify different filesystem objects. -->Current project plans also reject ASCII case/separator aliases and file/parent conflicts through shared portable name admission. Unicode folding, links and actual filesystem object identity remain separate. A disjoint lexical result does not prove that two paths identify different filesystem objects.

| Stage | What it establishes | What remains |
| --- | --- | --- |
| Choose destination | An admitted parent/folder path string | Existence and object identity |
| Build plan | Rendered relative paths and content | Filesystem effects |
| Create new | An attempt to create at a new destination | Partial-write recovery and later build |
| Compile and test | Evidence for selected generated source | Installation and runtime behavior |

## Design the application response

When selection is refused, keep the user’s entered folder visible and show the reason. Do not silently strip punctuation or choose another folder. Before explicit creation, present the complete destination and current recipe identity. Avoid concurrent edits to the destination during creation; the existing service does not provide a filesystem-wide transaction or a race-proof reservation contract.

## Extend and recover

Try one nested folder string and a parent-traversal string in a learner copy. Both should be refused by the one-component destination interface. Then choose a different ordinary single-component name. For a later real creation failure, preserve partial new files for inspection and review the report rather than deleting the destination automatically. Path-selection success alone cannot tell you whether a retry is safe or whether a different process has created files there.

## Source and next steps

[Lab build and source guide](../../../labs/native/framework-project-recipes/README.md) · [Qualification record](../../../labs/native/framework-project-recipes/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/project-select-a-new-destination.html)

[Previous lesson](project-refused-preview-preserves-state.md) · [Course index](../../courses/umicom-development/index.html) · [Next lesson](project-native-cli-explicit-creation.md)
