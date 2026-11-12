<!--
Umicom Bits2Banking
File: labs/native/framework-filesystem-clients/README.md

PURPOSE:
Build and study public Framework storage and project-creation clients.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Build a checked filesystem client

This C23 lab links the installed Umicom::developer target. It teaches portable
name admission, checked directory preparation, exclusive names, owned binary
reads and success-only project-state publication. It uses public Framework
headers and services; it does not include producer implementation files.

Start with [portable path admission](../../../content/courses/umicom-development/lessons/storage-portable-path-admission.html)
and follow the eight lessons. The qualification commands below are instructions,
not recorded execution results.

## Prepare and build

1. Install a Framework revision containing rooted directory creation, relative
   path relations and the checked new-project service.
2. Identify one installed SDK prefix and its producer revision. Replace the
   example prefix consistently if your installation is elsewhere.
3. Select a matching compiler, architecture and runtime. The CMake configuration
   checks package origin, SDK environment metadata and installed developer layout.
4. Run each command separately and stop on the first error. A source checkout
   is not a substitute for the selected installed SDK.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-filesystem-clients -B .\build\framework-filesystem-clients -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-filesystem-clients --parallel 2
ctest --test-dir .\build\framework-filesystem-clients --output-on-failure --no-tests=error
~~~

On Linux, use another build directory, a matching compiler and an absolute
installed prefix. The executable has no .exe suffix. The source never launches
a generated application or initializes Git.

## Understand the effects

The three name scenarios, project-preview and profile-preview perform syntax or
memory operations without native fixture creation. They do not check whether a
preview destination exists or reserve it.

Other scenarios create an exclusive run-NNNN directory under the supplied
existing absolute parent. They retain all directories and files. Repeated runs
choose another unused bounded name; they never recursively delete earlier work.
The selected parent must be an ordinary directory under your control. Native
operations can fail after partial effects, so preserve the printed path and
status when diagnosing an unsuccessful run.

CTest prepares separate parents beneath the consumer build's qualification
folder. For an individual scenario, use its already configured parent:

~~~powershell
& .\build\framework-filesystem-clients\filesystem-clients.exe existing-file C:/umicom/Umicom-Bits2Banking/build/framework-filesystem-clients/qualification/existing-file
& .\build\framework-filesystem-clients\filesystem-clients.exe profile-preview C:/umicom/Umicom-Bits2Banking/build/framework-filesystem-clients/qualification/profile-preview
~~~

| Scenario | Expected scoped observation |
| --- | --- |
| path-admission | Portable separator and Unicode spellings are admitted. |
| path-relations | ASCII/separator aliases compare equal; parent boundaries are exact. |
| invalid-path | Traversal, .git and reserved names are refused; relation output is unchanged. |
| directory-chain | First ensure creates two directories; repeated ensure creates none. |
| exclusive-directory | Create succeeds once, refuses the same name, and Ensure accepts the result. |
| new-file | Binary bytes including an embedded NUL survive an owned bounded read. |
| existing-file | A second exclusive create is refused and original bytes remain. |
| empty-file | Zero content bytes are a valid successful create/read. |
| invalid-directory | Complete lexical refusal precedes creation of an earlier component. |
| project-preview | A two-file plan produces predicted counts without filesystem effects. |
| project-create | A fresh project contains the expected source and README bytes. |
| project-collision | Repeating new-project creation refuses the existing root and retains content. |
| service-create | The service returns a valid model/profile and registers one project. |
| service-refusal | An existing root leaves model/profile bytes unchanged and registers no project. |
| profile-preview | Candidate model/profile values are returned without registration or writes. |

Exit zero means the selected scenario matched its assertions. Exit one identifies
a failed observation or allocation; exit two identifies invalid invocation.
Neither result establishes that a generated application builds or is bootable.

## Read the source boundaries

- main.c owns one heap workspace and always releases it after the selected exercise.
- names.c uses only shared lexical path contracts.
- fixture.c creates exclusive fixture roots and frees owned read buffers.
- files.c demonstrates native directory/file observations.
- projects.c composes plans, project services and copied outputs.
- lab.h declares the teaching client's state and function boundaries.

The two-file generator fixture is source data for a storage exercise, not a full
application package. The built-in service example creates a console starter,
but this lab never builds or runs it.

The shared application-branding helper supplies product metadata and a Windows
icon resource. Verify the resulting executable's metadata/icon separately.
Lesson fonts, wordmarks and favicon assets come from the common Umicom learning
resources; authored references do not establish rendered visual correctness.

## Recover from a failed observation

Keep the complete output and retained fixture. Check the SDK producer revision
before changing client expectations. A missing new symbol often indicates an
older installed library. A missing parent, permission refusal or link boundary
requires checking the selected native environment. Do not switch to an overwrite
API or delete partial results merely to obtain a zero exit code.

Use [QUALIFICATION.md](QUALIFICATION.md) to record evidence and remaining limits.
