<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/04-track-buffer-ownership.md

PURPOSE:
Track copied, borrowed and transferred buffers through completion and cancellation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Track buffer ownership

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

The lab copied a three-byte input, so the reader could keep it after the writer changed its own array. Large model tensors and video frames make extra copies expensive. Management messages can carry a bounded description of a buffer while the worker receives the data through a separate channel.

## Decide who can reuse a buffer

| Operation | May the sender reuse its bytes? | Evidence to wait for |
| --- | --- | --- |
| Copy | Yes, once the copy completes. | The receiver owns a separate copy. |
| Borrow for reading | Reuse must wait. | Every borrower has released its view, and any device reads have ended. |
| Move write ownership | Only after ownership is returned. | The receiver finishes or returns the current grant through the owner. |
| Cancel while device work may continue | Keep the buffer reserved. | The provider confirms that device access has ended. |

A descriptor should identify a registered object, offset, length, allowed operations and ownership generation. The receiver verifies the range against the registered size. For example, start at byte 12 in a 64-byte object and lend 16 bytes. Check `offset <= size` before testing `length <= size - offset`. This formulation avoids calculating a sum that might overflow.

## Walk through a cancellation

1. Put one buffer name on paper. Assign it to worker generation 7 and give the worker a read grant.
2. Mark the request as timed out while a device may still be reading. Circle generation 7 as the remaining owner of that access.
3. Offer the buffer to replacement generation 8. Refuse reuse until the provider supplies a completion event or confirms safe device recovery.
4. Try the same exercise with a copied buffer in an ordinary CPU worker. Identify which owner may release each copy after confirmed exit.

A **fence** is a synchronisation operation that can help establish completion in a particular system. A CPU memory-ordering operation serves a different purpose from a device completion event. Keep those facts explicit when teaching zero-copy transfers. [Barrelfish documentation and device queue papers](https://barrelfish.org/documentation.html)
