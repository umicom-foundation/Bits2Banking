<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/storage-exclusive-directory-reservation.md

PURPOSE:
Distinguish ensuring a directory from creating a new name

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Distinguish ensuring a directory from creating a new name

Prepare the installed-SDK lab using its README. The following command is a qualification step, not a recorded execution result.

~~~powershell
& .\build\framework-filesystem-clients\filesystem-clients.exe exclusive-directory C:/umicom/Umicom-Bits2Banking/build/framework-filesystem-clients/qualification/exclusive-directory
~~~

## Choose the operation from the workflow

Preparing a cache directory and creating a brand-new project are different requests. Ensure accepts an ordinary existing directory, which is useful for repeated preparation. Create requires the final component to be new. Both reuse the same portable path policy and checked parent traversal. A new-project frontend should choose that exclusive contract directly instead of first asking whether a name appears to be available.

~~~c
UmiRootedDirectoryCreation progress;
UmiStatus first = UmiRootedDirectoryCreate(root, "project", &progress);
/* First success reports one new final directory. */
UmiStatus second = UmiRootedDirectoryCreate(root, "project", &progress);
/* The same existing final name is refused. */
~~~

## Follow the three observations

The exclusive-directory exercise creates project, repeats Create, then calls Ensure. It expects success with one creation, ALREADY_EXISTS with zero creations, then success with zero creations. Read files.c and identify which observation belongs to each call. An existing directory is therefore neither a universal success nor a universal error; the answer depends on the operation the caller requested.

## Avoid a check-then-create decision

Another writer can change a destination between an existence query and a later create. The shared Create operation lets the native final-directory creation make the existence decision. The earlier availability of a name is not used as authority to reuse it. A collision tells the application to preserve the destination and choose another name. It does not authorize switching silently to Ensure or the overwrite generator.

## Do not promise an indefinite reservation

The operation releases its handles before returning. A successful final-name creation describes what that attempt did; it does not reserve the path forever. Subsequent file operations need their own checked ownership rules. Prevent external destination mutation during a project workflow, and distinguish a narrowly protected native create from a multi-file transaction or a claim about privileged processes.

| Result | Appropriate response |
| --- | --- |
| OK and complete | Continue within the documented ownership limits |
| ALREADY_EXISTS | Preserve the destination; select another name |
| Failure with a nonzero count | Retain partial directories and diagnose |
| Invalid argument | Correct the request before retrying |

## Practice explaining the distinction

Write a two-sentence message for a project picker that encounters an existing destination. Include the destination identity and a useful next action without suggesting deletion. Then explain why a preview shown earlier cannot guarantee creation will succeed. The lab should exit zero only after all three operation-specific expectations match.

## Source and next steps

[Lab build and source guide](../../../labs/native/framework-filesystem-clients/README.md) · [Qualification record](../../../labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-exclusive-directory-reservation.html)

[Previous lesson](storage-existing-parent-ownership.md) · [Course index](index.md) · [Next lesson](storage-exclusive-file-publication.md)
