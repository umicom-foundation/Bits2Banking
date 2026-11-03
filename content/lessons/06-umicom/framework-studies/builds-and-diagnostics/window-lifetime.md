# Investigate callbacks and window lifetime

Distinguish configure, compile, link and runtime evidence, then investigate shared dependency failures.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **callback** is a function registered to be called when something happens. A button click, timer or input-method event may invoke one later. The object it refers to must still exist when that call occurs.

An **input method** helps a person enter text, including characters not directly represented by a keyboard key. An input context may register callbacks with the operating system. If the context is destroyed while a callback remains registered, a later event may refer to invalid state.

```text
create object → register callback → handle events
                    ↓
            disconnect callback → destroy object
```

The important question is ownership: which component owns the registration, and which path removes it? Closing a window, cancelling an operation and normal application shutdown may all need to converge on the same safe release logic.

## Collect useful evidence

1. Record the application and exact runtime library version.
2. Describe the steps: open a window, focus an editor, close it, then repeat.
3. Save the diagnostic without removing the warning from source.
4. Check whether the fix belongs in application code, Framework or an external dependency.
5. After an authorised repair, repeat the same workflow and record the tested binaries.

The supplied runtime-repair material illustrates a dependency problem. It is not permission to apply an old patch to every current installation. A vendor may already include a backport, or a later release may have changed the code. Verify package provenance and the actual fix before rebuilding a dependency.

Framework's runtime diagnostics module records an advisory. Suppressing that message does not repair a callback lifetime defect. Likewise, a successful configure step cannot prove the input-method path is safe; that needs native execution evidence.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\cmake\UmicomGtkRuntimeDiagnostics.cmake`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
function(umicom_gtk_runtime_advisories version target_system out_advisories)
    set(_advisories)
    if(NOT version MATCHES "^[0-9]+[.][0-9]+[.][0-9]+([.-][A-Za-z0-9.-]+)?$")
        list(APPEND _advisories gtk.runtime.version-unavailable)
    elseif(target_system STREQUAL "Windows" AND version MATCHES "^4[.]24[.](0|1)($|[.-])")
        # The 4.24.0 and 4.24.1 release sources lack disposal-time removal of
        # the Win32 IME callback. Vendor suffixes alone cannot establish a fix.
        list(APPEND _advisories gtk.win32.ime-disposal)
    endif()
    set(${out_advisories} "${_advisories}" PARENT_SCOPE)
endfunction()

function(umicom_report_gtk_runtime_advisories version target_system)
    umicom_gtk_runtime_advisories("${version}" "${target_system}" _advisories)
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read the GTK diagnostics module's conditions and advisory text. Separate what its version check observes from what native window-lifetime qualification must establish.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Why can a warning disappear without the underlying bug being fixed?

### Worked answer

The diagnostic may have been disabled or its trigger changed. Only source/package evidence and a suitable runtime check can support the repair claim.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/builds-and-diagnostics/lessons/window-lifetime.html) · [Learning sequence](../../../../start/learning-sequence.md)
