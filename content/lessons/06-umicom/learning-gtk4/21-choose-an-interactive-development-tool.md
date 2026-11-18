<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/21-choose-an-interactive-development-tool.md

PURPOSE:
Choose an interactive development tool

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Choose an interactive development tool

[Course contents](index.md)
A fast experiment begins with a precise question. Do you want to calculate a value, inspect the current program, change a layout, or run newly compiled behaviour? These are different operations. In this module you will follow a small C program and a real Framework service, then decide which evidence is still needed for a GTK window. Start with the earlier lessons on functions, pointers and window state if those terms are new.


## Follow the representations

~~~text
C source text
  -> compiler -> object files -> linker -> executable
                                         -> running process
                                                -> debugger

C input -> interpreter or incremental compiler -> evaluation
UI data -> a host that supports reload -> refreshed widgets
~~~

Source text is what you edit. An object file holds compiled code and information the linker needs. The executable is the combined program. A process is one running instance of it. Editing the text does not change the instructions already loaded into that process. A debugger can pause those instructions and inspect their state; Continue normally resumes the loaded code.

REPL means Read, Evaluate, Print, Loop. It accepts complete input, processes it, shows a result or diagnostic when appropriate, and accepts another input. A physical line is not necessarily a complete C statement. A function body can span many lines. A tool must understand the syntax and retain supported declarations between submissions. A JIT compiler produces machine code during execution. An interpreter executes an internal representation. Both can support a REPL, but the interface alone does not prove either execution strategy.


## Choose and verify a tool

1. For compiler warnings, compile the small target with its real include paths, definitions and language mode. Read diagnostics before running anything.
2. For a wrong value in existing behaviour, use the project's debugger and stop at the relevant callback. Record the executable path and build identity.
3. For layout or colour experiments, use a host that explicitly supports the relevant UI or CSS data. Confirm that it actually reloaded the edited file.
4. For C experiments, examine the installed interpreter or incremental compiler's supported language and platform. A C23 command-line option is not a complete conformance result.

Clang-Repl, TinyCC and small educational interpreters have different language coverage, APIs and deployment requirements. Do not replace the production compiler merely because an experiment is quick. Umicom's bounded CVM preview provides an existing integer execution path; it is not a complete C23 interpreter, a GTK object runtime or a general garbage collector.


## Check your understanding

You pause a counter, edit its increment function and press Continue. Which version runs? Normally the previously loaded executable. Rebuild and restart, or use a specifically supported replacement mechanism. Next, explain why seeing a Save button in a layout preview does not prove that saving a document works.


[Previous lesson](20-diagnose-a-button-journey.md) · [Next lesson](22-build-a-small-framework-preview-lab.md)
