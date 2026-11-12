<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/storage-portable-path-admission.md

PURPOSE:
Admit portable paths before touching the filesystem

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Admit portable paths before touching the filesystem

Prepare the installed-SDK lab using its README. The following command is a qualification step, not a recorded execution result.

~~~powershell
& .\build\framework-filesystem-clients\filesystem-clients.exe path-relations C:/umicom/Umicom-Bits2Banking/build/framework-filesystem-clients/qualification/path-relations
~~~

## Separate a name from an object

A file name is a request to locate an object. Checking the spelling of that name cannot establish which object a filesystem will return later. Begin this module by reading names.c and running path-admission, path-relations and invalid-path. These exercises call the shared Framework policy without opening directories. They give every application the same rules instead of allowing a GUI, command line and importer to disagree about a generated destination.

~~~c
UmiRootedPathRelation relation;
UmiStatus status = UmiRootedFileCompareRelativePaths(
    "Src/Main.c", "src\\main.c", &relation);
/* On success, this portable comparison reports EQUAL. */
~~~

## Understand the conservative comparison

The comparison normalizes slash and backslash separators and folds ASCII letter case. A generator can therefore refuse two recipe files that would use the same portable name even on a host that permits differently cased names. Parent relationships require a component boundary: src is a parent of src/main.c, but it is not a parent of src-old/main.c. The lab checks both cases so a prefix test cannot quietly replace the shared rule.

| Input | Expected lexical result | Reason |
| --- | --- | --- |
| source/main.c | Admitted | Ordinary portable components |
| new/../outside | Invalid argument | Traversal component |
| new/.git/config | Permission denied | Repository metadata boundary |
| new/CON.txt | Invalid argument | Reserved device spelling |

## Keep failure outputs meaningful

The invalid-path scenario initializes the relation to a known value and passes a refused second path. The shared comparison must leave the previous value unchanged. Only inspect a newly computed relation after the returned status is OK. This is the same publication discipline used for larger plans: a failed attempt must not make an old result look like a new accepted result.

## Extend the exercise carefully

Add a pair of sibling paths with a common prefix and explain why they remain disjoint. Then add a non-ASCII case pair and record the narrower contract: this API does not implement full Unicode case folding or resolve filesystem aliases. Do not change the expected result merely to match a particular disk. Actual links, access permissions, short names and concurrent changes belong to native qualification after lexical admission.

## Expected observation

The scenario should finish with its scoped portable-name message and exit zero. No file or directory is created by these three name exercises. If an API symbol is missing, check the selected installed SDK and its headers together. If the returned relation differs, retain the exact pair and Framework revision before changing the client.

## Source and next steps

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Lab build and source guide](../../../labs/native/framework-filesystem-clients/README.md) · [Qualification record](../../../labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-portable-path-admission.html)
-->
[Lab build and source guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-clients/README.md) · [Qualification record](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-portable-path-admission.html)

[Previous lesson](project-branding-and-sdk-qualification.md) · [Course index](index.md) · [Next lesson](storage-existing-parent-ownership.md)
