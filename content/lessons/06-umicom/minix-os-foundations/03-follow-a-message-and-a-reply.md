# Follow a message and its reply

## Sending is not completing

IPC means inter-process communication. In a request/reply protocol, delivery of a request and completion of the requested operation are separate events. A caller waiting for a reply must distinguish a valid result from failure or a service that never responds.

MINIX exposes several message operations. The [message-passing guide](https://wiki.minix3.org/doku.php?id=developersguide:messagepassing) describes blocking send, receive, combined send/receive and notifications. Check the [v3.3.0 IPC declarations](https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/v3.3.0/minix/include/minix/ipc.h) for the actual message layout and names used by that release.

## Trace a small protocol on paper

Design an original status request with an operation, sequence and reply status. This is a classroom schema, not a reserved MINIX message number. The server validates the operation before reading operation-specific fields. It then produces either a defined result or a defined refusal.

Draw what happens if the caller exits before the reply. Next draw two services that synchronously call one another while both wait. The second drawing reveals why ordering and deadlock rules matter.

## Worked example

Client A sends request 12 and later sees a response tagged 11. A result with plausible bytes is still the wrong response. Reject the mismatch rather than treating data shape as identity.

## Exercise and answer

Can a server read a sender's raw pointer from a message and dereference it? Answer: not as a general cross-process operation. The address belongs to another virtual address space and requires a supported transfer boundary.

## Source exercise

Locate the send/receive declarations, message source field and notification test in your release. Record their types. Do not memorize a payload size from a tutorial and apply it to another architecture or version.

A source trace demonstrates understanding. A host simulation can test your schema logic. Only a guest exercise with the real IPC mechanisms can qualify the operating-system interaction, and no such execution is claimed here.

[Course contents](index.md)
