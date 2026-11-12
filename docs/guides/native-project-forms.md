<!--
Umicom Bits2Banking
File: docs/guides/native-project-forms.md

PURPOSE:
Follow shared native project forms from captured input to qualified host shutdown.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../content/assets/branding/umicom-logo.svg)

# Native project forms: source ownership and qualification

This guide supports the six native workflow lessons in the existing
[Framework course](../../content/courses/umicom-development/index.html).
They explain real Framework and Studio source. Their C fragments are excerpts
or host-integration sketches, not complete programs that can be compiled alone.

A project form creates source; it does not build or execute that source.
Its asynchronous writer keeps file operations off the GTK event thread.
Successful generation, successful host adoption, compiler qualification and
distribution are separate outcomes.

## 1. Locate the shared implementation

In the Framework checkout, inspect these files together:

| Source | Responsibility |
| --- | --- |
| adapters/gtk4/developer_project_creation_gtk4.inc | Copied request, private worker service, guarded completion |
| adapters/gtk4/developer_dialog_gtk4.c | Controller ownership, native lifetime and public write activity |
| adapters/gtk4/developer_application_gtk4.inc | Existing reviewed application-module source workflow |
| include/umicom/ui/gtk4/developer_dialog.h | Public host contract |
| src/developer_project/new_project.c | Checked creation entry point |
| src/developer_project/generator_create.c | Exclusive native source creation |
| tests/developer_project/test_project_creation_worker_gtk4.c | Held dispatch and injected writer cases |

Studio remains a client. Its runtime_close_guard.inc and interaction/project.inc
consume the shared activity query before host closure or form replacement.
Keep reusable generation, path admission and lifetime behavior in Framework.

## 2. Follow the states

1. **Draft:** the user chooses a recipe, identity and explicit destination.
2. **Admission:** the GTK thread copies and validates all inputs. Notifications
   can still retire the host before a task is constructed.
3. **Writing:** an owned GTask job uses its own project service. It reads no GTK
   widgets and invokes no host callback.
4. **Completion:** the GTK event context receives the result. Live owned forms
   retain successful model/profile values, including when temporarily hidden.
5. **Adoption:** a visible live form asks the host to open the completed project.
   Failure permits an Open Project retry without another source write.
6. **Shutdown:** the host checks WritePending before normal close or replacement.
   It asks for a fresh user close decision after completion.

Destroying a handle retires callback authority. It is not cancellation or
rollback. Forced process termination cannot guarantee a complete source tree.

## 3. Prepare the actual build trees

The following are owner-run qualification commands, not recorded results.
Run each separately and stop on errors. Use an existing configured tree built
from the source under review. A clean source checkout, matching dependency
revisions and a functioning UCRT64 toolchain are prerequisites.

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
Set-Location "C:\umicom\Umicom-Applications\framework"
cmake --build --preset windows-ucrt64-debug --parallel 2 --target umicom-project-creation-worker-gtk4-test umicom-developer-dialog-gtk4-test umicom-simulation-starters-gtk4-test umicom-developer-settings-lifetime-test
ctest --test-dir build/windows-ucrt64-debug --output-on-failure --no-tests=error -R "framework[.]ide_workflow[.](project_creation[.]gtk4[.]|developer_dialog[.]gtk4|starter[.]gtk4[.]|settings[.]gtk4[.]project-)"
~~~

The Framework preset must have testing and the GTK adapter enabled.
If a target is missing, inspect the configure output and source selection.
Do not replace a missing test with a successful empty CTest selection.

Studio uses the Applications parent preset, which compiles its shared Framework
dependency. The Studio module has no standalone preset file.

~~~powershell
Set-Location "C:\umicom\Umicom-Applications"
cmake --build --preset windows-ucrt64-all-debug --parallel 2 --target umicom-studio-first-use-test
ctest --test-dir build/windows-ucrt64-all-debug --output-on-failure --no-tests=error -R "studio[.]first_use[.]gtk4[.]wizard-"
~~~

These scenarios do not build or launch the generated project. Those operations
need their own later qualification. The commands assume the owner has already
configured the intended native GTK build; they do not install dependencies or
change repository state.

## 4. Interpret results

Twenty worker cases use a real GTask thread with a controlled writer that creates
no files. They test capture, reentrancy, admission retirement, hidden completion,
adoption retry and activity observation. Real developer-dialog and starter
fixtures exercise source creation. Three additional Studio wizard cases check
host closure and replacement during actual writing.

A timeout is a failure. Keep its fixture because a writer may still be active.
A capability skip is missing coverage, not a pass. Record source revisions,
compiler, operating system, GTK/GLib runtime, exact commands and complete output.
Keep public examples free of private logs, credentials and machine-specific
diagnostic evidence.

## 5. Review branding and user-visible behavior

The lessons use the approved Umicom SVG wordmark, SVG icon, ICO fallback and
shared learning stylesheet. Interface text uses the approved Segoe UI family
with local fallbacks; code uses Cascadia Code or Consolas with a monospace
fallback. Native forms reuse the existing Framework identity and approved
project workflow rather than introducing an unrelated layout.

After the owner-run build, inspect the actual window identity, icon, text,
progress wording, keyboard interaction and hidden/reopened result. Hash checks
establish asset identity, not rendered appearance. No visual or native behavior
is claimed qualified by this authored guide.

## 6. Continue the course

Start with [copied inputs](../../content/lessons/umicom-development/native-project-captured-inputs.md)
and finish with [qualification evidence](../../content/lessons/umicom-development/native-project-qualification-evidence.md).
For installed-SDK command-line examples, reuse the
[checked filesystem client lab](../../labs/native/framework-filesystem-clients/README.md)
and [project recipe lab](../../labs/native/framework-project-recipes/README.md).

The task-lifetime discussion follows the official
[GTask reference](https://docs.gtk.org/gio/class.Task.html) and
[worker dispatch contract](https://docs.gtk.org/gio/method.Task.run_in_thread.html).
