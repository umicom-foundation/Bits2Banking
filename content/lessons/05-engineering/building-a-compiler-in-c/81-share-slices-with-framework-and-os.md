<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/81-share-slices-with-framework-and-os.md

PURPOSE:
Share slices with Framework and OS

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Share slices with Framework and OS

[Course contents](index.md)
A compiler runtime, an editor and an operating-system tool need different responsibilities. Umicom C validates and executes bytecode. Framework owns the source-facing debug session. The OS preview tool reuses that Framework service. Keeping one execution engine prevents each product from inventing different arithmetic, fuel or error behavior.


## 1. Read the session states

~~~text
start -> PAUSED
resume -> PAUSED or COMPLETE or FAILED
cancel(PAUSED) -> CANCELLED
start again -> a fresh admitted session
~~~

PAUSED means the program may continue. COMPLETE means RETURN succeeded and a result is available. FAILED means an operation was refused. CANCELLED means the owner chose not to resume. These are states, not progress percentages. A cancelled session cannot be resumed as though nothing happened.


## 2. Use the shared resume boundary

~~~c
UmcStatus status = umi_cvm_debug_resume(
    &session, sizeof session, 16);
if (status == UMC_OK && session.phase == UMI_CVM_DEBUG_COMPLETE) {
    /* Display session.result.value. */
}
/* A PAUSED session can be scheduled for a later event. */
~~~

Initialize session with umi_cvm_debug_start first. The exact sizeof value helps reject incompatible caller storage. The service retains source coordinates, so the source buffer can be released after a successful start. It does not retain a live editable document, and changing the editor text does not change the already admitted program.


## 3. Configure the OS consumer explicitly

~~~powershell
Set-Location C:/umicom/umicomOS
cmake -S tools/cvm-preview -B build/cvm-preview-debug -G Ninja -DCMAKE_C_COMPILER=gcc -DUMICOM_OS_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework -DUMICOM_C_PREVIEW_SOURCE=C:/umicom/umicom-c -DBUILD_TESTING=ON
cmake --build build/cvm-preview-debug --parallel 2
ctest --test-dir build/cvm-preview-debug --output-on-failure --no-tests=error
& ./build/cvm-preview-debug/framework-preview/umicom-cvm-preview.exe --slice 2 'int main(void){return 6*7;}'
~~~

These commands select the primary Framework checkout explicitly. Run them separately and stop on errors. An integrated OS checkout can instead use its reviewed Framework dependency once that dependency includes the same API. Never copy a newer header over an older library and assume the package is compatible.


## 4. Recognize stale dependency errors

If configuration says the bounded resume API is missing, inspect UMICOM_OS_FRAMEWORK_SOURCE in CMakeCache.txt. A cache stores earlier configuration choices. Confirm that it names the intended checkout, and check that its cvm_debug.h declares umi_cvm_debug_resume. If linking reports a missing umc_machine_run_slice symbol, the Umicom C headers and library may come from different revisions. Rebuild the selected SDK or use the explicit source path above.


## 5. Keep product claims precise

The console demonstration drains slices synchronously. It proves that a shared consumer can use the API; it does not prove an editor remains responsive under load. Native breakpoints, source replacement, GUI event scheduling and background-worker lifetime need their own integration and tests. The OS wrapper is a user-space tool; it is not the Kernel's freestanding guest interpreter.

Exercise: design a Cancel button handler in words. It should mark a paused session cancelled, remove any pending scheduling callback that owns it, and avoid freeing session storage while another callback is still using it. Cancellation between slices is straightforward only when ownership and callback lifetime are explicit.


[Previous lesson](80-preserve-progress-when-a-slice-fails.md)

[Next: Give branch locals a lexical scope without changing the VM](82-give-branch-locals-a-lexical-scope.md)
