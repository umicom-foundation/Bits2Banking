# Read each stage of a build

Distinguish configure, compile, link and runtime evidence, then investigate shared dependency failures.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **build** turns source into a program. Configuration discovers dependencies and writes build instructions. Compilation translates individual source files. Linking connects the translated files and libraries into an executable. Testing runs defined checks. Installation copies selected outputs into a chosen location.

```text
source + configuration → build graph → compiled objects → executable
                                                       ↓
                                                 tests and evidence
```

These stages can fail independently. An unknown CMake command is a configuration problem. An undeclared C function is a compilation problem. An undefined reference can be a linking problem. A window that opens but ignores clicks is a runtime workflow problem. A successful earlier stage does not prove later stages succeeded.

## Classify four observations

1. “Unknown CMake command”: inspect the configure log and module inclusion.
2. “Implicit declaration”: inspect the header visible to that source file.
3. “Undefined reference”: inspect the definition and linked target dependencies.
4. “Button does nothing”: inspect event delivery, command dispatch and the resulting UI state.

An **incremental build** reuses outputs whose recorded inputs have not changed. Correct reuse needs a dependency graph. A shared header can affect many sources, while a comment-only edit may still change a file timestamp and trigger a normal compiler invocation. Do not delete dependencies merely to make the build look faster.

Likewise, a previously passed test is reusable only under a valid policy about its source, dependencies, toolchain and environment. Record failures separately from skipped or unbuilt tests. “Not run” is not a pass.

For a real investigation, save the command, source revision, toolchain identity, complete output and process exit status. Use a distinct timestamped log location for each run. If configure or build fails, do not present an older executable's behaviour as validation of the new source.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\cmake\UmicomAutomaticTestsRun.cmake`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
function(_fingerprint output discovery)
    execute_process(COMMAND "${_ctest}" --test-dir "${_build}" -C "${_config}" --show-only=json-v1
        OUTPUT_FILE "${discovery}" ERROR_FILE "${discovery}.errors.txt" RESULT_VARIABLE _discovered)
    if(NOT _discovered STREQUAL "0")
        message(FATAL_ERROR "CTest discovery failed; read ${discovery}.errors.txt")
    endif()
    file(READ "${discovery}" _json)
    string(JSON _count ERROR_VARIABLE _error LENGTH "${_json}" tests)
    if(NOT _error STREQUAL "NOTFOUND" OR _count EQUAL 0)
        message(FATAL_ERROR "No complete nonempty CTest catalogue was discovered")
    endif()
    file(READ "${_build}/umicom/closed-tests-${_config}.tsv" _registry)
    set(_owners "")
    string(REPLACE "\n" ";" _rows "${_registry}")
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Open the automatic-test runner and locate how it selects or reuses work. Compare the decision inputs with the evidence you would need to trust a previously passed result.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

A test executable is missing after a failed link. Is that evidence that its assertions failed?

### Worked answer

No. It did not run. The link failure blocked qualification. Record the missing executable separately and fix the build before interpreting its test result.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/builds-and-diagnostics/lessons/build-evidence.html) · [Learning sequence](../../../../start/learning-sequence.md)
