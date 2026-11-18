<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/26-qualify-a-current-interactive-preview.md

PURPOSE:
Qualify a current interactive preview

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Qualify a current interactive preview

[Course contents](index.md)
A preview is useful when its identity and behaviour are clear. A visible window alone is weak evidence. This final exercise combines the earlier GTK callback study with the revision lab. It produces a repeatable checklist for an eventual Studio preview integration; it does not claim that integration already exists.


## Define the evidence

1. Choose one existing approved window or control from the earlier GTK lab. Record its initial state and the action to test.
2. Record the exact source revision, build directory, executable path and candidate batch. Keep the identity of the currently running preview separately.
3. Perform one real action, such as clicking the counter button. Observe the model change and the displayed value.
4. Introduce a controlled error in a separate learning copy. Confirm that the compiler or layout loader reports failure and the existing preview remains identified as older.
5. Correct the error, build the small target and start or refresh it through a supported host operation.
6. Close the window during a pending operation. Verify that a late completion cannot access destroyed widgets or falsely report the new preview as current.


## Distinguish the stages

~~~text
Edited source -> candidate batch -> build/load result -> applied runtime
                      |                    |
                      | failure            | success
                      v                    v
                 retain pending       acknowledge matching revisions
                 keep older identity  retain newer pending revisions
~~~

The current Framework service implements the last bookkeeping boundary. Its focused tests cover later edits, failed-work retention, competing completions, invalid bounded state and generation limits. They do not prove GTK rendering, main-context scheduling, child-process supervision, debugger integration or SDK installation. Those need their own integration checks.

A stale completion is one whose assumptions no longer match the current owner state. A second successful completion advances the generation, so a competing batch from the old generation is refused. This prevents an older result from silently clearing newer work. Do not acknowledge a failed build merely to make the queue look empty.


## Assess memory deliberately

C gives control over allocation and layout; it does not automatically prevent leaks or invalid access. Track who owns each resource, which callbacks borrow it and when those callbacks stop. Check each failure path as carefully as the successful path. Measure process memory over repeated open, edit, refresh and close cycles with a fixed workload. Different model sizes and allocator caches can change memory use without establishing a leak.

Use compiler warnings and suitable analysis or sanitizers when supported by the actual toolchain. A warning-free build and a passing test are useful observations, not a proof that all executions are safe. Keep measurements, the exact operation and the source identity together so another contributor can reproduce the result.


## Completion exercise

Explain the difference between source-study qualification, installed-SDK qualification and GUI qualification. Then draw the ownership chain for the chosen callback. You have completed this module when you can build the small lab, predict its output and identify what remains untested in a proposed native preview.


## Further reading

This module develops ideas from C GTK and Interactive Development, especially its chapters on callbacks, preview boundaries and Ninja rebuilds. Consult GTK's GtkBuilder, signals and threading documentation, the CMake manual and the Ninja manual for the exact installed versions. External REPL tool support remains version and platform dependent.


[Previous lesson](25-diagnose-an-unexpected-full-rebuild.md)

- [GTK signals and handler lifetime](https://docs.gtk.org/gobject/signals.html)
- [GTK threading and main context](https://docs.gtk.org/gtk4/section-threading.html)
- [GtkBuilder](https://docs.gtk.org/gtk4/class.Builder.html)
- [Clang-Repl](https://clang.llvm.org/docs/ClangRepl.html)
- [Ninja manual](https://ninja-build.org/manual.html)
- [CMake command-line manual](https://cmake.org/cmake/help/latest/manual/cmake.1.html)
