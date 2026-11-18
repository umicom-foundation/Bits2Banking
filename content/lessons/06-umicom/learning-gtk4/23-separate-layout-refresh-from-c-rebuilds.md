<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/23-separate-layout-refresh-from-c-rebuilds.md

PURPOSE:
Separate layout refresh from C rebuilds

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate layout refresh from C rebuilds

[Course contents](index.md)
A GTK interface combines data, executable code and live state. Treating every edit as the same kind of reload makes failures hard to understand. Start by writing down which category changed. The earlier control-inspection lab supplies a real window and callbacks to inspect; this chapter does not add a new window layout.


## Classify an edit

~~~text
Edit                          Required host behaviour
External CSS colour           Parse and apply supported CSS
GtkBuilder .ui structure       Recreate/reconcile supported objects
C signal handler              Compile and restart or supported code replacement
Persistent structure layout   Restart or explicit versioned state migration
~~~

GtkBuilder reads structured descriptions of objects. It does not automatically watch the source file. A CSS provider can load style data, but a host must decide when to reload it and what to do with parse errors. Displaying a button proves only that the layout instantiated it. The signal connection, callback, model operation and failure feedback still need a behavioural test.


## Trace state and callbacks

1. Open the existing framework-control-inspection example and identify the object that owns its callback state.
2. Locate a signal connection. Follow its user-data pointer to the state allocation and then to the cleanup path.
3. Identify borrowed widget pointers. Write down which owning object keeps each widget alive and when the callback must stop using it.
4. List any timer, worker completion or signal that could arrive after a window closes. A native implementation must disconnect, cancel or safely reject each late event.

A callback is a function supplied to another component for a later call. Returning from the function that builds a window does not mean its callbacks have finished. A pointer to that function's automatic local state would become invalid after return. Object-associated cleanup, reference ownership and cancellation must agree on when the state ends. GTK operations belong on the appropriate GTK main context; a background compiler worker must deliver completion back through the host's supported main-context mechanism.


## Keep the last usable preview

A candidate layout or executable should be validated before it replaces the current preview. If a candidate fails, keep the last usable preview and show its older identity. Keeping it visible is useful, but labelling it current would mislead the developer. Framework's new reload batch records pending work; it does not itself load GtkBuilder files, restart processes or update a GTK label.

Unloading a DLL is especially different from refreshing CSS. Signal handlers, function pointers, registered types and live objects can still refer to code in that module. Restarting an isolated preview process is a simpler initial boundary. If state must survive, export explicit values with a schema version; never save raw widget addresses as persistent state.


## Exercise and answer

After a failed compile, the old counter still works. Has the edit passed? No. Record the compiler failure and identify the displayed preview as older. Test the replacement only after its build and startup succeed.


[Previous lesson](22-build-a-small-framework-preview-lab.md) · [Next lesson](24-preserve-edits-during-a-preview-build.md)
