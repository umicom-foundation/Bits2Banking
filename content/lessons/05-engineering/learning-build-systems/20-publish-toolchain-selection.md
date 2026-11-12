![Umicom](../../../assets/branding/umicom-logo.svg)

# Publish the selected profile only after its environment is ready

Imagine an IDE displaying compiler B while its next build still receives compiler A through CC. Each field may look reasonable on its own, but together they describe different execution contexts. A reliable selection operation prepares the dependent values before making the new selection visible.

## Use the shared publication operation

~~~c
UmiStatus status = umi_toolchain_catalogue_select_with_environment(
    catalogue, "first", selected_profile, child_environment);
if (status != UMI_STATUS_OK) return status;
~~~

This fragment assumes a created catalogue, an inserted profile and separate receiving owners. Framework stages a profile copy and child environment. It changes the explicit catalogue selection only after preparation succeeds, then publishes the prepared values and binds the process pointers to their receiving storage.

## Define exactly what failure preserves

For this operation, refusal preserves the catalogue selection and both receiving objects. It does not undo earlier catalogue insertions, discovery observations or unrelated application work. Discovery remains a separate operation that can probe tools and update records incrementally. Do not describe a whole discovery-and-selection workflow as atomic merely because its final selection step preserves its outputs.

## Inspect both sides of the boundary

The Selection lab inserts first and refused profiles before taking its snapshot. It successfully selects first, saves both owners, and attempts refused, whose compiler path contains a newline. The later comparison checks unchanged owner bytes, unchanged catalogue revision and the first identifier. Checking only the error code would miss a partial mutation.

## Respect caller ownership

The output profile and environment must not overlap each other or catalogue storage. Callers also serialize readers and writers across the operation. Preparation on temporary storage does not add a lock or make unsynchronized access safe. A process crash is a separate concern; this in-memory operation is not durable database commit machinery.

## Exercise

Draw the sequence as prepare profile, prepare environment, select catalogue, publish owners. Mark every step that can refuse. Then explain why publishing selected_profile before environment preparation would break the advertised failure guarantee. Extend your review notes with the state that must remain unchanged after an invalid identifier and after malformed environment text. Execute the supplied scenario only in a qualified installed-client environment.

## Source and practice

Use the [installed C23 lab guide](../../../../labs/native/framework-toolchain-selection/README.md) and [complete source](../../../../labs/native/framework-toolchain-selection/main.c). The examples are authored; no build or execution result is implied.

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Prepare a child environment without changing the parent shell](19-child-environments-and-path.md) · [Next: Keep borrowed process pointers inside their receiving owner](21-environment-pointer-ownership.md)

[HTML lesson](../../../courses/learning-build-systems/lessons/20-publish-toolchain-selection.html)

Sammy Hegab · Umicom Foundation · MIT
