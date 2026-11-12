<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/build-history-copy-and-lifetime.md

PURPOSE:
Keep retained build evidence independent of caller storage

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Keep retained build evidence independent of caller storage

## Draw the ownership relationships

The laboratory has one history, one or two runners, and three caller-owned result records. A runner borrows the history pointer. The history owns copies of completed results. The caller owns the result buffer passed to the synchronous run function and the buffers used to read retained records. These roles explain both the destruction order and why an application may reuse a completed output buffer.



A build result contains bounded output text and diagnostic arrays. Allocating those records through umi_build_result_create avoids placing several large values on a small worker stack. Allocation is not execution: if any allocation fails, the client releases everything it already owns and exits with a laboratory failure. It never reports a synthetic successful operation to compensate for missing storage.



## Follow the copy scenario

~~~c
if (umi_build_history_latest(history, retained) == UMI_STATUS_OK) {
    *saved = *retained;
    umi_build_result_init(result, 99U, UMI_BUILD_PHASE_BUILD, "local-reuse");
    /* Reading history again must still return the completed Run observation. */
}
~~~



Here, reinitialising result changes only caller storage. The code does not submit operation 99, append it to history or change the history allocator. The saved record provides an independent comparison value. The laboratory reads the latest record again and checks that it is byte-for-byte unchanged. The comparison is appropriate because these records are initialised and copied by the same API; arbitrary uninitialised C structures would require more careful treatment of padding.



## Release borrowers before owners

- Wait until the synchronous operation and its callbacks have returned.
- Destroy the second runner, if created, then the first runner.
- Destroy their shared history.
- Destroy the independent caller-owned result records.



Destroying history while a runner can still append would leave a borrowed pointer to dead storage. Likewise, a UI should not free its result buffer while a worker is using it. A synchronous API provides a clear return boundary, but calling it on a worker does not automatically solve host shutdown. The earlier native-project lifetime module explains captured requests and host authority in that wider setting.



## Exercise: separate mutation from observation

Run copy through the owner procedure and locate the retained ID in its output. Explain why the locally assigned ID 99 is absent. Then review the no-history scenario: its standalone history stays empty because the runner was configured with a null history pointer. The completed result still belongs to the caller. The runner does not create an implicit global history or borrow the unrelated laboratory history.



## Limits and recovery

A copied result remains an observation of one attempt. It is not durable storage, proof of current source identity or a guarantee that the diagnostic text is complete. If a consumer needs persistent evidence, it must own and check that separate sink. Preserve allocation or read errors rather than replacing missing evidence with empty success. The next lesson adds bounded retention and multiple identity producers.



## Source and practice

[Build-history laboratory and owner commands](../../../labs/native/framework-build-history/README.md) · [HTML edition](../../courses/umicom-development/lessons/build-history-copy-and-lifetime.html)

[Previous lesson](build-history-admitted-preparation.md) · [Next lesson](build-history-bounded-identities.md) · [Course index](index.md)
