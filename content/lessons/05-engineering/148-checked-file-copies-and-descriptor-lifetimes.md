# 148. Checked file copies, descriptor lifetimes and error handling

A successful file service has to do more than locate the right file. It must also ensure that a failed read, write or close does not leave the caller with misleading partial results.

Our Notes file service gives us a small place to examine those rules. The code is in [`labs/native/process-file-services`](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/process-file-services/README.md) and reuses the VFS from Chapter 142.

## 1. Distinguish the request from the result

The request describes an intended operation:

```c
BtbProcessFileRequest request = {
    .operation = BTB_PROCESS_FILE_READ,
    .descriptor = handle,
    .offset = 128U,
    .length = 24U
};
```

The result contains the accepted descriptor or number of bytes actually transferred:

```c
BtbProcessFileReply reply = {0};
```

A read asking for 24 bytes can return fewer bytes when the file is shorter. The request size is a **capacity**, not a promise that 24 bytes exist.

The VFS moves the file position by the actual successful read count. It does not advance the position because the caller merely requested a read.

## 2. Do not publish a half-finished reply

The adapter prepares its reply in a local object:

```c
BtbProcessFileReply candidate = {0};
```

Only after the VFS accepts the operation does it copy the result into the caller's reply:

```c
*outReply = candidate;
```

The tests initialise a reply with recognisable values. A refused operation leaves those exact values in place. This is called **failure-atomic publication**: a caller should not mistake an unaccepted operation for a successful one.

There are limits to this guarantee. A real filesystem can sometimes modify part of a file before reporting an error. An API must distinguish *refused without mutation*, *partially completed*, and *completed* when that distinction matters. Our in-memory provider has a much simpler contract.

## 3. Understand file lifetimes

Four things have separate lifetimes:

1. The pathname is copied only while OPEN is being evaluated.
2. The process-owned descriptor remains valid until CLOSE or process shutdown.
3. The VFS open description contains a position and survives while references remain.
4. The provider's file contents survive according to its own storage and unlink rules.

Duplicating a descriptor shares an open description. Opening the same filename again creates a **new** open description with its own position. These are not interchangeable operations.

Our process adapter tracks at most eight accepted descriptors. The VFS itself has a separate fixed table and generation-tagged tokens. Process shutdown closes the adapter's outstanding handles using the original VFS rather than freeing provider objects behind its back.

## 4. Why stale handles are refused

Imagine that one process closes descriptor slot 2. The VFS may later reuse that slot for a different file. If an old token were just the number 2, it could accidentally refer to the new file.

The VFS therefore combines a slot number and a **generation**. Each successful close advances the slot generation. An old token cannot identify a newly opened file.

This is particularly important in an operating system. A number that once identified a resource must not regain authority over a new resource simply because a storage slot was reused.

A generation tag is not a password. The trusted process identity and rights checks still apply.

## 5. Close in the correct order

Suppose a process opens a note, then a service wants to unmount `/notes`.

If the file still has an open description, unmount must return `BTB_VFS_BUSY`. The provider cannot be removed while clients can still call its operations through existing descriptors.

The process-file adapter closes each tracked descriptor before allowing its process object to end. If a provider refuses final release, the adapter retains the remaining handles instead of silently claiming shutdown succeeded.

This is **reverse-order lifetime cleanup**:

```text
Mount provider → Open description → Client descriptor → Read/write
                               Close descriptor → Release description → Unmount
```

## 6. Run two focused tests

From the repository root:

```powershell
ctest --test-dir ".\output\learning-build\process-file-services" --output-on-failure
```

The `copy_and_access` test checks the copied byte buffer, path validation and output preservation. The `lifetime` test checks descriptor closure, stale-handle refusal, post-shutdown refusal and unmount after cleanup.

If a test fails, read the source location printed by the `CHECK` macro before changing anything.

## 7. Apply the same thinking to a bank-account simulator

Consider a fictional account-report export. The report generator should not receive a raw pointer into an account database, nor should it silently truncate a report when the destination is too small.

A safer design is to create a checked snapshot with an explicit revision and length, verify the requested output capacity, then publish the complete accepted result. Persistent accounting introduces additional transaction and audit requirements, but the principle is the same: **ownership and completion must be explicit**.

## 8. Practise

Describe how you would test a provider that refuses CLOSE once and succeeds on retry. The process service should keep the descriptor in its table after the refusal and remove it only after successful release.

Then explain why the following approach is incorrect:

```c
/* Incorrect: erases evidence of a live resource after a failed close. */
/* owner->owned[index] = 0; */
```

Do not enable that operation in the working laboratory.

**Questions:** What does a generation-tagged descriptor protect against? Why is a provider's file position not stored in the caller's byte buffer? When can shutdown be reported as complete?

Continue with [Chapter 149: TCP/IP and sockets](149-tcp-ip-and-native-c23-sockets.md).
