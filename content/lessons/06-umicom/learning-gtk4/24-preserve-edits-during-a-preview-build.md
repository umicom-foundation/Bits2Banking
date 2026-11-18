<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/24-preserve-edits-during-a-preview-build.md

PURPOSE:
Preserve edits during a preview build

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Preserve edits during a preview build

[Course contents](index.md)
A revision identifies one version of content. A generation identifies one successfully acknowledged batch in this service. They are separate numbers: several paths can belong to one batch, and one path can change again while that batch is being processed. Reusing a revision for changed content defeats the comparison, so the caller must assign meaningful revisions.


## Follow the native example

~~~text
Capture: counter.c revision 10 + theme.css revision 20
               |
               | another edit arrives
               v
Queue: counter.c revision 11 + theme.css revision 20 + dialog.ui revision 30
               |
               | acknowledge the captured batch
               v
Keep:  counter.c revision 11 + dialog.ui revision 30
Remove: theme.css revision 20
~~~

The batch holds copies of the admitted path/revision pairs. Capturing it does not remove anything. After the host has successfully applied that exact work, acknowledgement compares each queued path with the captured version. Only equal pairs are consumed. A newer counter edit and a newly added dialog remain pending.

~~~c
umi_frontend_hot_reload_capture(reload, batch);
/* The host processes this exact batch and checks its result. */
umi_frontend_hot_reload_acknowledge(reload, batch, &receipt);
~~~

This fragment shows the relationship, not complete error handling. The supplied main.c checks every status before continuing. The receipt reports the new generation, how many paths were acknowledged, and how many remain. A result with zero remaining work describes this queue at that moment; it is not proof of UI correctness.


## Predict before running

1. Write down the two paths captured at generation 1 in main.c.
2. Find the later call that changes counter.c from revision 10 to 11. Explain why the old completion must not remove it.
3. Predict the receipt: generation 2, acknowledged 1, pending 2.
4. Run the CTest walkthrough from the previous chapter and compare the complete output.
5. Follow the second capture and acknowledgement. Both remaining revisions now match, producing generation 3 with pending 0.

The objects use fixed capacities and do not allocate memory during queue operations. The batch is large because it owns bounded path copies; the example allocates it explicitly rather than placing it on a small thread stack. Allocation failure is handled before use. The host owns and eventually frees the batch and queue.


## Limits

Calls require serial ownership. The service does not make unsynchronised access from multiple threads safe. Keep the batch unchanged and alive until completion, then discard it. It must not survive reinitialisation or movement of its owner. The owner pointer is a process-local identity, not a security token or a serialised handle.

Exercise: change every captured path to a new revision before acknowledgement. The old batch can finish successfully with zero paths acknowledged. All newer work remains pending; the preview still needs another update.


[Previous lesson](23-separate-layout-refresh-from-c-rebuilds.md) · [Next lesson](25-diagnose-an-unexpected-full-rebuild.md)
