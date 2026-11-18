<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/25-detect-incomplete-source-before-compilation.md

PURPOSE:
Detect incomplete source before a long compilation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Detect incomplete source before a long compilation

[Course contents](index.md)

## A build needs more than the changed C files

Imagine receiving a new C implementation and its tests, then starting a large build. Much later, the compiler reports that a header cannot be found. The missing file may be small, but the time already spent compiling unrelated targets is real. This lesson explains why headers and implementation files belong to one integration unit, how to identify the earliest useful failure, and how Framework now checks the native training file set before compilation begins.

An integration unit is a set of files that need to be used together for a feature to make sense. It is not necessarily one folder or one executable. A new data reader can require a public header, a C implementation, a build-list entry, a command adapter, tests and an example. Copying only the implementation can leave the checkout incomplete even when the copied file itself is correct. Keep a reviewed file list and preserve local differences when combining work.


## Understand the compiler's missing-header message

~~~c
#include "umicom/ai/training/jsonl_pairs.h"
~~~

The #include directive asks the C preprocessor to read declarations from another file before compilation proceeds. The preprocessor is the part of the toolchain that handles directives such as include and conditional compilation. The path above is relative to a header search root. If that root is C:/Example/Framework/include, the requested complete path ends in include/umicom/ai/training/jsonl_pairs.h. Adding another include flag cannot create a file that is absent at that location.

A header normally describes declarations, types and contracts. A C source file supplies definitions and behavior. A static library or DLL contains compiled code. These are related artifacts but are not interchangeable. Copying a DLL cannot satisfy a preprocessor include. Creating an empty header may remove one missing-file message while causing unknown types, incorrect declarations or later failures. Use the complete matching source or SDK package rather than trying to make individual error messages disappear.


## Read the earliest real diagnostic

1. Open the complete build log as text. Search for fatal error, error, FAILED or the toolchain's equivalent, then read the surrounding command and source location.
2. Identify the source file being compiled and the exact header spelling. Check case and separators, especially when the same source will run on Linux.
3. Read the compiler's include flags. Resolve the requested relative header against the selected include root.
4. Check whether that file actually exists and is a regular nonempty file. A directory with the same name is not a header.
5. Compare the source and header identities with the reviewed delivery or repository revision. Existence is necessary but does not prove they belong together.
6. Preserve the failed log. A later successful configuration should not overwrite the evidence of what originally failed.

A build tool can continue independent jobs after one compilation fails. The last visible line may therefore show a successful link unrelated to the original error. Ninja can eventually report that it cannot make progress due to previous errors. That final message summarizes failure; it is not the underlying compiler diagnosis. Several missing includes in different objects may have one shared cause: the same absent public header.


## Inspect Framework's early file contract

The module cmake/UmicomTrainingSourceInputs.cmake defines umicom_require_training_source_inputs. It checks the native JSONL and denoising source set when the training composition module is configured. The list includes the public headers and their direct C owners. The check reports all missing, empty or non-file entries together, so the user can review the complete integration gap before starting a large compilation.

~~~cmake
include("${CMAKE_CURRENT_LIST_DIR}/UmicomTrainingSourceInputs.cmake")
umicom_require_training_source_inputs(
    "${_umicom_training_data_root}" _umicom_training_inputs)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    ${_umicom_training_inputs})
~~~

These lines are build configuration, not application runtime code. include loads the shared CMake helper. CMAKE_CURRENT_LIST_DIR identifies the directory containing the current module, avoiding dependence on the shell's working directory. The function receives a source root and returns absolute input paths through the named output variable. CMAKE_CONFIGURE_DEPENDS records those files as inputs that can trigger reconfiguration when they change. It does not compile their C contents or install a missing file.

Inside the function, foreach visits each explicit relative path. EXISTS checks whether the path resolves, IS_DIRECTORY distinguishes a directory from a file, and file(SIZE ...) checks for an empty file. Missing entries are appended to a list. A fatal configuration message is emitted after the complete list has been examined. If all entries pass, the absolute path list is returned. The function has no file-write, download or replacement operation.


## Know what the contract cannot prove

A nonempty file can still contain the wrong declaration, an incompatible revision or invalid C. This early guard does not parse C, compare content hashes with a release manifest or prove that the installed SDK contains matching compiled symbols. It also does not certify every source dependency in the whole Framework. Its job is narrower and useful: detect an incomplete native training integration before compilation. Compiler, linker and runtime tests remain necessary afterward.

If a source file changes after configuration, the build may rerun CMake because of the recorded dependency. That improves feedback but is not a substitute for deliberate source review. Do not edit or copy files into a checkout while using its test results as evidence for a fixed source identity. Finish the intended file set, configure, build and test, then record what was actually used.


## Run the configuration fixtures independently

~~~powershell
cmake -S tests/cmake/training_source_inputs -B build/training-input-checks -G Ninja
ctest --test-dir build/training-input-checks --output-on-failure --no-tests=error
~~~

1. Open a terminal in the Framework checkout. Use a separate build directory for this focused exercise.
2. Configure tests/cmake/training_source_inputs. Its CMake project uses LANGUAGES NONE, which means these checks do not compile a C application.
3. Run CTest and inspect any failure output. The fixtures are created below the chosen build directory, never by deleting a real source header.
4. Read check.cmake. It creates an independent list of expected fixture files, starts a child CMake probe and checks the result and diagnostic text.

The fixture cases cover a complete set, each required header and source missing in turn, an empty header, a directory named as a header, several missing paths together and a nonexistent source root. The fixture root contains spaces to check argument boundaries. Existing fixture files are hashed before and after admission, so the check must not silently repair or alter them. A passing fixture means the expected admission or refusal occurred; it does not mean the deliberately missing source set could compile.


## Repair an incomplete integration coherently

1. Stop treating later test failures as new application regressions until the required build succeeds. Keep their logs, but identify any stale or missing executables separately.
2. Compare the reviewed complete-file delivery with the intended primary checkout. Include the public include tree, implementations and composition files, not only src.
3. Preserve locally edited files and resolve differing content deliberately. Do not erase unrelated work or copy repository metadata as a shortcut.
4. Integrate matching complete files. If a header exists but differs, compare its declarations with the implementation and the intended revision rather than choosing by timestamp alone.
5. Configure again in the intended build directory. A successful configure is the next checkpoint, not the final result.
6. Build the relevant targets, run their tests, then record the source identity and toolchain. Qualify independently installed consumers separately.

An earlier executable can remain on disk after a failed build. Starting it may produce a convincing result from an old implementation. Conversely, a new test registration may refer to an executable that was never linked. Both situations are possible when configuration and compilation are confused. Preserve the distinction between a test result and proof that the test exercised the intended source. A file's mere presence is not a build receipt.


## Connect this to your own C project

For a small project, begin with one header declaring a function, one C file defining it, and one program calling it. List all three in your review checklist and build graph. Add a configure-time existence check only when it makes an integration boundary clearer; do not fill a project with scripts that duplicate the compiler. As the project grows, use installed targets to export headers and link dependencies together, and keep source completeness, ABI compatibility and runtime deployment as distinct checks.

The same approach helps long model-training and media builds. It avoids spending hours on unrelated targets before discovering that a small required header never arrived. It does not make training itself faster or establish memory safety. The benefit is earlier, specific feedback about a concrete precondition, with a recoverable error message and focused regression coverage.


## Check your understanding

1. Given include root C:/Example/Framework/include and the relative path in the first code sample, write the exact file path the compiler needs.
2. Explain why a correct include path and a missing header can occur together.
3. Explain why a zero-byte replacement header is not a valid repair.
4. Explain why a failed build can leave both old executables and missing new executables in the same output folder.
5. Name one property the early completeness check verifies and three properties it does not verify.
6. Run the focused fixtures and record their actual result. Then explain why that result is not evidence of a full Framework build.


## Different stages require different repairs

| Failure stage | Typical evidence | First useful question |
| --- | --- | --- |
| Configure | A required source file is missing | Is the source set complete for this feature? |
| Compile | Header not found or invalid declaration | Does the file exist at the reported include root, and does it match? |
| Link | Undefined reference to a function | Does the selected library contain the required symbol? |
| Run | A loader cannot locate a required DLL | Are matching runtime dependencies deployed? |
| Test | An assertion or expected result fails | Which source and executable were actually tested? |

## Further reading

- [Training source admission implementation](https://github.com/umicom-foundation/umicom-framework/blob/main/cmake/UmicomTrainingSourceInputs.cmake)
- [Configuration regression fixtures](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/cmake/training_source_inputs/check.cmake)
- [Training composition and dependency registration](https://github.com/umicom-foundation/umicom-framework/blob/main/cmake/UmicomTrainingData.cmake)

[Previous: Qualify the installed client without confusing plans with execution](24-installed-toolchain-lab-qualification.md)

[Next: Recognize stale tests after a failed build](26-recognize-stale-tests-after-a-failed-build.md)
