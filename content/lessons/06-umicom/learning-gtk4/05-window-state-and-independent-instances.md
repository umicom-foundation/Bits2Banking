<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/05-window-state-and-independent-instances.md

PURPOSE:
Explain the lesson: Keep window state independent.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep window state independent

## State belongs somewhere

A state object contains values that must survive between callbacks. A local variable inside a callback disappears when that call returns. A global variable survives, but can accidentally make unrelated windows share one value.

The activity example allocates an ActivityWindow for each created window. It contains the completed count and a label pointer. GTK keeps that state attached to the window and releases it through the registered destroy function.

## Setup recap

Read and build the optional GTK4 target using the [Framework activity guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/README.md). Work in a disposable practice checkout for source experiments. Reading the ownership trace needs only window.c and the ability to recognise a pointer as a reference to an object.

## Draw the ownership

~~~text
application -> window -> widget tree -> label
                  |
                  +-> ActivityWindow state
                      count
                      borrowed label pointer
~~~

The state does not independently own the label. The window's widget tree does. The callback temporarily holds a reference to the window while updating its label, then releases it. The source explains why notifications and object lifetime must be considered together.

g_signal_connect_object also associates the signal connection with the target window's lifetime. A raw callback data pointer without a lifetime plan would require separate disconnection management.

## Lab

1. Launch two independent processes of the teaching application.
2. Click the first window twice and the second once.
3. Expect separate counts.
4. Close one process and continue using the other.
5. Read the allocation and release code together.
6. In your notes, distinguish the state owner from the pointer borrowed by the state.

Two processes are an initial independence check, not a complete test of several windows within one process. If you add a New Window command later, test that case separately.

## Exercise and explanation

Should the callback free the ActivityWindow after each click? No. Later clicks still need it. The registered window-data cleanup releases it when its owner is finalized.

## Extend carefully

A background worker must not use a widget after its window closes. It needs cancellation, a valid reference or weak-reference strategy, and a main-thread handoff for GTK updates. This synchronous example does not establish those additional guarantees.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/window.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-trace-a-button-through-a-callback.md)


[Next: Create and own a window's state](06-create-and-own-window-state.md)
