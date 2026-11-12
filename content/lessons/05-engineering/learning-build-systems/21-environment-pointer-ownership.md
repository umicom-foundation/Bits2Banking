![Umicom](../../../assets/branding/umicom-logo.svg)

# Keep borrowed process pointers inside their receiving owner

A structure can contain both owned arrays and pointers into those arrays. Copying its bytes duplicates the pointer values, not their destination ownership. This is a common lifetime trap in C: the copied text looks correct while a process-facing view still points into the old object.

## Trace one variable

UmiEnvironmentPlan stores names and values in entries. Its process_entries view contains pointers used by the process service. For row i, the name pointer must refer to the receiving entries[i].name array and the value pointer to entries[i].value. A pointer into a temporary candidate becomes invalid when that candidate is released.

~~~c
const UmiEnvironmentVariable *variables =
    umi_environment_plan_variables(environment);
if (variables == NULL) return UMI_STATUS_INVALID_ARGUMENT;
/* Keep environment alive and stable while the consumer uses variables. */
~~~

This fragment assumes a valid, writable environment owner. The accessor validates and rebinds its process entries. NULL reports an invalid plan. A borrowed view does not transfer ownership: callers must not free its strings or mutate the plan while a consumer uses them.

## Choose a copy operation with an ownership contract

The selection API already rebinds its receiving environment. For general composition, umi_environment_plan_compose stages a new plan and guarantees receiving pointers on success, including supported input/output aliasing. A raw assignment or memcpy does not provide that semantic guarantee. When reviewing code, find the exact point at which the destination view is rebound.

## Read the regression carefully

The Selection scenario compares process-entry pointers directly with the receiving arrays after successful selection. It then copies the entire environment into saved_environment only as a byte snapshot for failure comparison. That snapshot is never passed to the process service. The distinction matters: saving bytes for a comparison is not constructing another independently usable environment owner.

## Exercise and memory limits

Sketch two boxes for candidate and destination, with arrows for their pointer views. Move the arrays, then redraw the arrows that must change. Calculate the approximate owned text storage from the public capacity constants before choosing automatic storage. The lab uses static serial owners to avoid large stack frames; a multi-document IDE should use explicit per-instance lifetime and synchronization instead of sharing these globals.

## Source and practice

Use the [installed C23 lab guide](../../../../labs/native/framework-toolchain-selection/README.md) and [complete source](../../../../labs/native/framework-toolchain-selection/main.c). The examples are authored; no build or execution result is implied.

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Publish the selected profile only after its environment is ready](20-publish-toolchain-selection.md) · [Next: Replace a compiler provider and profile together](22-synchronize-compiler-selection.md)

[HTML lesson](../../../courses/learning-build-systems/lessons/21-environment-pointer-ownership.html)

Sammy Hegab · Umicom Foundation · MIT
