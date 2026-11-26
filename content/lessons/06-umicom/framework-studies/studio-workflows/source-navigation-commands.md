![Umicom](../../../../assets/branding/umicom-wordmark.svg)

# Connect source navigation menus to shared document services

[Next lesson](trace-a-native-library-link.md)

Lesson 3 of the Studio documents course. You need the ideas of a saved file and an in-memory draft from the first lesson. Reading requires no compiler or language server. The optional native exercise uses a locally built Studio and a language server you choose.

## A menu label is only the beginning

A command identifier is a stable name for an action, such as `navigate.definition`. A menu row displays a caption and stores this identifier. A router decides which service receives the action. Declaring the row does not connect it to a service: an application can show a convincing menu whose action is unavailable. This is why a source audit must trace the identifier through availability, dispatch, the actual service and the resulting window or document state.

Studio has three related actions. Go to Symbol opens a searchable outline of the captured document. Go to Definition asks for the declaration or definition at the captured caret, according to the server. Find References asks for uses of that source position. A review window opens first. The Request button starts the language-server work separately. A successful window-opening call proves neither that a server is installed nor that it returned a correct location.

## Keep one source owner

The document coordinator owns the current draft, selection and saving state. Framework creates an inspection request from that owner. Inspection is read-only, so a read-only source can still be explored. The request captures a particular source version. If the user later edits the draft or moves its caret, the review must apply its existing freshness checks before opening a result.

The shared GTK command boundary recognises exactly `navigate.symbol`, `navigate.definition` and `navigate.references`. It does not guess from prefixes. The menu and editor toolbar call the same boundary. Studio contributes the open project folder and the `Studio` settings namespace; Framework retains the language protocol, source capture, native dialog and destination-opening logic.

~~~c
#include "umicom/ui/gtk4/document_commands.h"

/* Call on the GTK owner thread with a live, document-bound adapter.
 * The host owns adapter and all source state. */
static UmiStatus inspect_definition(UmiGtk4Adapter *adapter,
                                    const char *project_folder)
{
    return UmiGtk4AdapterSourceNavigationCommand(
        adapter, "navigate.definition", project_folder, "Studio", NULL);
}
~~~

This function composes an existing application. It is not a standalone program and does not create a GTK application or document binding. `NULL` for the last argument selects the normal preference location; tests can pass an isolated base directory. Borrowed path strings only need to remain valid during the call. Opening the review may synchronously invoke window observers, so the host must use its weak owner binding before accessing the window again.

## Availability is a question, not a promise

`UmiGtk4AdapterSourceNavigationCommandEnabled` captures and validates the current draft, then releases its temporary request. It checks that the editing owner exists, the source coordinates are valid, the source is below the native message capacity and another document operation is not busy. It neither opens a window nor reads preferences, saves source or launches a process. Capturing costs bounded memory, so query on the UI owner thread rather than from an arbitrary worker.

~~~c
int enabled = UmiGtk4AdapterSourceNavigationCommandEnabled(
    adapter, "navigate.definition");
gtk_widget_set_sensitive(definition_button, enabled);
~~~

A true answer can become stale immediately: another command may open a review before the user clicks. Execution therefore repeats admission. Disabling a widget is useful feedback, but it is not the service's sole protection. A retained button or direct command call must not start a second review while one owns the document operation.

## Try the workflow

1. Open Studio with a locally built version that contains these commands. Create a C draft containing two functions. Leave an unsaved change so that preservation is easy to observe.
2. Open Navigate > Go to Symbol. Expect the existing Document symbols window and a Cancel default action. Confirm that merely opening it has not started a request.
3. Cancel, place the caret on a function name and choose Navigate > Go to Definition. Expect Definition locations. Repeat with Find References and expect Reference locations.
4. Choose a trusted local language server and review its executable, arguments and project folder. Only then select Request. The server can inspect the project folder; a source-inspection workflow is not a process sandbox.
5. Inspect returned locations before choosing the explicit Open action. If the server lacks the required capability or returns no results, record that outcome rather than treating the open review as a successful lookup.
6. Return to the draft. Confirm its unsaved text and selection were preserved when you cancelled. Repeat through the editor's Symbols, Definition and References controls.

## Build regression evidence

The Framework test target `umicom-navigation-commands-gtk4-test` covers three command identifiers with nine scenarios each. It checks empty, multiline and read-only drafts, unknown IDs, missing documents, oversized sources, unbinding and an already-open review. The Studio target `umicom-studio-navigation-menu-test` checks real menu rows, toolbar parity, invalid arguments, cancellation, parent closure and retained controls. These fixtures do not activate Request; they cannot qualify a real language server.

~~~powershell
cmake --build <framework-build> --target umicom-navigation-commands-gtk4-test
ctest --test-dir <framework-build> --output-on-failure -R '^framework[.]document[.]navigation_commands[.]'

cmake --build <applications-build> --target umicom-studio-navigation-menu-test
ctest --test-dir <applications-build> --output-on-failure -R '^studio[.]language[.]navigation_menu[.]'
~~~

Replace the angle-bracket placeholders with already configured build directories that enable GTK and tests. Stop if a command fails. Configuration registers targets; it does not execute them. A test exit code of 77 indicates that GTK initialization was unavailable and must remain a skip in your report. Record the source revision, toolchain, runtime and actual passed, failed and skipped counts.

## Diagnose a disabled or unsuccessful action

1. If the menu is disabled, open a source draft and finish any Save All, Close, replacement, proposal or source-review operation. Recheck the active document rather than inferring it from a filename shown elsewhere.
2. If the menu opens nothing, compare its stored command ID with the exact recognised IDs. Trace the same identifier through Studio's availability query and command router. A generic registered-command check does not create a missing native adapter.
3. If a large source is refused, use a smaller representative file. The raw draft must be below 65536 bytes, but JSON escaping and the protocol envelope can still make the later request too large. An enabled menu is not a guarantee that transport will accept every response.
4. If closing a parent window leaves a retained control, verify that its callback resolves a weak owner and becomes inert. Never keep using a cached runtime pointer after window publication or result notification.
5. If Request fails, review server capabilities, project configuration and diagnostics separately from command routing. Preserve the original failure and its environment identity before changing code.

## Check your understanding

A test finds the menu row and confirms its caption. Has it proved Go to Definition works? No. It has established presentation only. A stronger offline test opens the expected review through the real row, checks that no request started and verifies that source state is unchanged. A separate controlled server test checks returned locations, and an interactive exercise checks the complete user workflow.

Exercise: explain why the Enabled query and execution both inspect the current document. Then design a test that enables the menu, opens a different review and invokes the old menu control. The expected result is refusal of the competing operation with the original review and draft preserved.

[Previous: shared designer model](designer-model.md) · [Course overview](../../../../courses/framework-and-finance/studio-workflows/index.html)
