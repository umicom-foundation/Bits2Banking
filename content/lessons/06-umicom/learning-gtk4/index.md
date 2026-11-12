# Learning GTK4

Build a small event-driven window and trace its connection to a shared rule.

Complete C functions, pointers and structures. Read the activity example README before the optional build.

[Browser course](../../../courses/learning-gtk4/index.html) · [Choose a subject](../../../start/course-series.md)

## Reading order

1. [Widgets and the event loop](01-widgets-and-the-event-loop.md)
2. [Connect a button to a shared rule](02-connect-a-button-to-a-shared-rule.md)

## Course outline: later topics

Containers, keyboard focus, dialogs, accessibility and safe widget lifetime.

Read one topic at a time. The list above links to available lessons; the outline describes further study. Each practical lesson gives its own tool requirements.

## Continue with a practical source study

A window can outlive the function that created it. Its callbacks therefore need state that remains valid after that function returns. This lesson follows how the activity example creates, attaches and releases that state.

- [Own state for the lifetime of a window](03-own-state-for-a-window.md)
- [Trace a button through a C callback](04-trace-a-button-through-a-callback.md)
- [Keep window state independent](05-window-state-and-independent-instances.md)

- [Create and own a window's state](06-create-and-own-window-state.md)

- [Wire a GTK signal to a C callback](07-wire-a-signal-to-a-callback.md)

- [Compose widgets in a GTK container](08-compose-widgets-in-a-container.md)

- [Present status without changing the model](09-present-status-without-changing-the-model.md)

- [Separate model checks from window checks](10-separate-logic-and-window-checks.md)

- [Follow the application event loop](11-follow-the-application-event-loop.md)


## Inspect and operate GTK controls safely

Follow a small window from control identity to logical discovery, explicit navigation, safe callback lifetime and reproducible user-interface checks. The example uses the shared Framework GTK service.

1. [Identify a control independently of its caption](12-identify-a-control.md)
1. [Understand the logical widget tree](13-understand-the-logical-widget-tree.md)
1. [Read checked lookup results before using a pointer](14-read-checked-lookup-results.md)
1. [Detect duplicate names and keep searches scoped](15-find-ambiguous-controls.md)
1. [Reveal a panel without running its action](16-reveal-without-running-an-action.md)
1. [Distinguish a found control from a usable control](17-distinguish-visible-enabled-and-found.md)
1. [Keep callback state alive for the right lifetime](18-keep-callback-state-alive.md)
1. [Test control discovery at its boundaries](19-test-control-lookup-boundaries.md)
1. [Diagnose a button journey from click to result](20-diagnose-a-button-journey.md)
