# Move from small programs to OS and Kernel source

Choose the next prerequisite deliberately and recognise the limits of a hosted lab.

**Before you begin:** Read [Test what you promised and understand failures](07-check-results-and-errors.md), or return to it for a refresher.

## Keep the pieces you now understand

You have met a hosted entry point, values, expressions, choices, loops, function contracts and checks. You can follow a small result from source through compilation and linking to a run. These are useful foundations, not a requirement to memorise every detail before continuing.

The next challenge is to keep those ideas visible when a file is larger. Start with one function and its declaration. Identify its inputs, outputs and rejected cases. Follow the code called by that function only when you need it. Reading an entire repository in alphabetical order is rarely a useful first exercise.

## Prepare for memory and input

An array groups elements of a common type. A pointer represents a location used to access an object or function under C's rules. A buffer is storage reserved to hold data temporarily. These concepts need careful practice because a location alone does not tell you whether the object is still alive or how much data is valid.

The safer-C and borrowed-memory chapters explain bounds and lifetime before the Kernel input labs use them. Lifetime is the period during which an object exists. Ownership describes who must release or otherwise manage a resource. Read those chapters before changing pointer arithmetic, allocation or firmware readers.

## Follow the OS route

The Umicom OS course studies a Linux-based foundation and its user-space services. User space is the execution environment for ordinary processes above the kernel. A service is a program that performs a system responsibility, such as supervising another process or checking startup conditions.

Begin with the OS overview and system-boundaries lesson. The hosted parser lab exercises startup-plan validation without booting an image. Later lessons examine recovery, image identity and service ownership. A successful parser test does not show that firmware, a boot loader, a kernel and an image work together; guest boot is separate qualification.

## Follow the native Kernel route

Umicom Kernel is a separate research implementation. It has a machine-specific entry path rather than relying on the hosted main environment used here. Its target compiler and emulator may differ from the compiler that builds this lab.

Start with the native-kernel-and-host-models lesson, then bounded input after studying arrays and pointers. Compare the familiar idea of rejecting an invalid count with refusing a malformed byte span. A byte span includes a starting location and an explicit length. It is not automatically a text string with an ending marker.

## Use the existing library of lessons

The connected learning map links the original chapters with the newer courses. Use it as a route, not a test of loyalty to one order. Return to an earlier explanation when a source file introduces a word you cannot yet explain.

The original note-saving C chapter adds file streams and input. It remains useful after this smaller introduction. The build-and-tests chapter expands how CMake prepares projects. The OS and Kernel chapters connect those practices to real source. A topic appearing in both a lesson and a course can provide a different perspective rather than requiring duplicate completion.

## Plan one reviewable exercise

Choose a single change in a personal lab copy: a greeting, one accepted count or one loop bound. State its expected result, rebuild the affected target and run the relevant check. If you intentionally change demonstration output, first explain why the old expected output should change.

Do not begin by modifying a live operating system, deleting partitions or replacing a boot configuration. The early exercises need none of those actions. When you reach an emulator exercise, read its machine profile and recovery instructions first. The aim is to understand a controlled experiment and its evidence.

## Try it step by step

1. Choose the next route: note-saving C, safer memory, OS services or native Kernel.
2. List the unfamiliar terms in that route's first lesson and find their prerequisite chapters.
3. Write one small exercise with an expected result and a way to check it.
4. Keep your last completed activity and next action in a private notebook or bookmark.

## Check your understanding

Does passing first-c-programs prove that an Umicom OS image can boot?

**Explanation:** No. It checks the small hosted programs and count contract. Booting an image depends on additional software, configuration, target hardware or emulator, and separate evidence.

## Before you continue

You can choose a next lesson and describe what its checks would and would not establish.

[Course contents](index.md) · [Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Test what you promised and understand failures](07-check-results-and-errors.md).

**Next:** [Keep several values in an array](09-arrays-and-valid-positions.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
