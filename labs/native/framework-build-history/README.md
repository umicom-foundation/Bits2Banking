![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Observe build preparation history with an installed SDK

This C23 client uses real Framework build-runner and history APIs. It deliberately leaves the Run program empty, so launch-plan preparation returns `INVALID_STATE` before any compiler, test runner or application can start. It demonstrates a failed attempt recorded as evidence; it does not manufacture a passing build.

The client belongs with the Framework development course's build-history module. Read `main.c` beside the public `umicom/build/runner.h` and `umicom/build/history.h` contracts. Product orchestration remains in Framework.

## Prepare the SDK

1. Integrate and qualify the matching Framework source through its owner workflow.
2. Install that Framework into the SDK prefix used below.
3. Use the UCRT64 C compiler and CMake on PATH.
4. Run the following commands separately and stop on errors. Replace the SDK prefix if your installed location differs.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-build-history"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure
.\build\btb-framework-build-history.exe single
~~~

These are owner-run commands. They have not been executed for this authored client. The expected CTest result is six passing scenarios.

## Explore each observation

| Argument | Expected retained history | What it teaches |
| --- | --- | --- |
| `single` | ID 1 | An admitted preparation refusal completes an operation. |
| `rolling` | IDs 2 and 3 | Capacity two evicts the oldest of three completed attempts. |
| `shared` | IDs 1 and 2 | Two runners borrow one identity-allocating history. |
| `no-history` | Empty | The caller still receives ID 1 and failure without history. |
| `invalid` | Empty | A null runner admits nothing and preserves caller output. |
| `copy` | ID 1 | Reinitialising caller storage cannot rewrite the retained copy. |

~~~powershell
.\build\btb-framework-build-history.exe rolling
.\build\btb-framework-build-history.exe shared
.\build\btb-framework-build-history.exe no-history
.\build\btb-framework-build-history.exe invalid
.\build\btb-framework-build-history.exe copy
~~~

For `rolling`, expected output is:

~~~text
Scenario: rolling
Operation: 1; status: INVALID_STATE; exit: -1
Operation: 2; status: INVALID_STATE; exit: -1
Operation: 3; status: INVALID_STATE; exit: -1
Retained records: 2
History[0]: 2
History[1]: 3
Preparation observations only; no compiler, test runner or application launched.
~~~

Exit zero means the laboratory observed its expected refusal and history. It does not turn those failed Run attempts into successful application launches. The checker compares the complete output, exit status and empty error stream, including exact operation identities.

## Follow ownership in the source

The history owns copies of completed results. Each runner borrows the history pointer. The client separately allocates result, retained and saved records on the heap, because build records contain bounded output and diagnostic storage and need not consume a small thread stack.

Both runners must be destroyed before their shared history. Caller result buffers are independent; reusing one after a synchronous call returns is safe. The `copy` scenario demonstrates this separation without exposing private history fields.

The absolute source path is illustrative and is never created. All valid scenarios keep Run's program empty. Do not add a program merely to make a refusal disappear: that changes the laboratory into an execution workflow and needs separate process, toolchain and application checks.

## Branding and installed resources

The executable uses `umicom_apply_application_branding` from the installed Framework package. The helper stages approved SVG assets and embeds the approved Windows ICO through the resource compiler. `NO_RUNTIME_DEPLOYMENT` keeps this console lab from requesting GTK runtime deployment. Lesson pages use the shared approved learning stylesheet and its Segoe UI and Cascadia Code font families.

Inspect executable metadata and packaged assets after building. Source references and matching asset hashes alone do not prove installed icon rendering or font selection on another machine.

## Troubleshoot honestly

If CMake cannot find Framework, check the installed prefix and that its build component was installed. If the runner returns the expected failure but history stays empty, inspect whether the installed SDK contains the preparation-history fix; do not change the checker to accept an older observation. Rebuild and reinstall Framework through its owner workflow, then reconfigure this client against that same prefix.

A build error is different from a scenario mismatch. Preserve the complete logs, Framework revision, compiler identity and SDK location. Do not execute an old client binary after a failed rebuild and report its result as qualification of the new source.

The client and six scenarios are authored and statically reviewed. Installed-SDK compilation, linking, execution, resource staging and native appearance remain unverified.
